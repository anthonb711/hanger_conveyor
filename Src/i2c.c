/*
 * i2c.c
 *
 *  Created on: Oct 14, 2025
 *      Author: 001501
 */


/*  i2c uses the APB1 buss at max 50Mhz
 *  Locate SDA and SCL lines for I2C1
 *  SCL -- PB8 AltFunction AF05
 *  SDA -- PB9 AltFunction AF05
 */

#include "stm32f411xe.h"
#include "i2c.h"

#define I2C1EN 					(1U<<21)
#define GPIOBEN					(1U<<1)
#define CR2_FREQ				(1U<<4)	// 16Mhz

#define I2C_100KHZ				80			// 0b0101 0000 = decimal 80
#define SD_MODE_MAX_RISE_TIME	17			// 0b0001 0110 = decimal 17 using standard mode
#define CR1_PE					(1U<<0)		// enable i2c
#define SR2_BUSY				(1U<<1)		// i2c busy is busy = 1
#define CR1_START				(1U<<8)		// generated start condition
#define CR1_STOP				(1U<<9)		// generated start condition
#define SR1_SB					(1U<<0)		// start bit  1 = start condition is generated
#define SR1_ADDR				(1U<<1) 	// addr sent flag
#define SR1_TXE					(1U<<7) 	// transmit flag
#define CR1_ACK					(1U<<10)	// acknowledge bit
#define SR1_RXNE				(1U<<6)		// data register not empty
#define SR1_BTF					(1U<<2)		//byte transfer finished  = 1


void I2C1_init(void)
{

	/* enable clock access to GPIOB*/
	RCC->AHB1ENR |= GPIOBEN;

	/* set PB8 & PB9 mode to alt func */
	GPIOB->MODER &=~(1U<<16);
	GPIOB->MODER |= (1U<<17);

	GPIOB->MODER &=~(1U<<18);
	GPIOB->MODER |= (1U<<19);


	/* set PB8 & PB9 output type to open drain */
	GPIOB->OTYPER |= (1U<<8);
	GPIOB->OTYPER |= (1U<<9);

	/* enable the pull-up for PB8 & PB9*/
	GPIOB->PUPDR |= (1U<<16);
	GPIOB->PUPDR &=~(1U<<17);

	GPIOB->PUPDR |= (1U<<18);
	GPIOB->PUPDR &=~(1U<<19);

	/* PB8 SCL - alt function I2C1 */
	GPIOB->AFR[1] &=~(1U<<0);
	GPIOB->AFR[1] &=~(1U<<1);
	GPIOB->AFR[1] |= (1U<<2);
	GPIOB->AFR[1] &=~(1U<<3);

	/* PB9 SDA - alt function I2C1 (AF4)*/
	GPIOB->AFR[1] &=~(1U<<4);
	GPIOB->AFR[1] &=~(1U<<5);
	GPIOB->AFR[1] |= (1U<<6);
	GPIOB->AFR[1] &=~(1U<<7);

	/* enable clock access to I2C1 (AF4)*/
	RCC->APB1ENR |= I2C1EN;

	/*wait while until the bus is not busy */
	while (I2C1->SR2 & SR2_BUSY){}

	/* enter reset mode */
	I2C1->CR1 |= (1U<<15);

	/* come out of reset*/
	I2C1->CR1 &=~(1U<<15);

	/* configure default clock*/
	I2C1->CR2 |= CR2_FREQ;

	/* set I2C clock mode in the CCR standard mode*/
	I2C1->CCR = I2C_100KHZ;

	/*  set the max rise time */
	I2C1->TRISE = SD_MODE_MAX_RISE_TIME;

	/* enable I2C */
	I2C1->CR1 |= CR1_PE;
}

void I2C_byteRead(uint8_t saddr, uint8_t maddr, char* data)
{
	volatile int tmp;

	/*wait while until the bus is not busy */
	while (I2C1->SR2 & SR2_BUSY){}

	/* generate a start condition and wait for the start bit */
	I2C1->CR1 |= CR1_START;
	while(!(I2C1->SR1 & SR1_SB)){}

	/*
	 * transmit slave address + Write
	 * the slave address is 7-bits and it with the R/W (1/0) bit is the the first 8 bits of the frame.
	 * the ACK bit is then sent followed buy the data, another ACK bit and then a stop condition.
	 * so the address needs to be put in the data register along with the actual data to be read/written.
	 * by left shifting a 7-bit addr we are adding the R/W bit to 0 or write. DR receives 8 bits in total
	 */
	I2C1->DR = saddr << 1;

	/* wait for the addr flags is set, then clear it */
	while(!(I2C1->SR1 & SR1_ADDR)){}
	tmp = I2C1->SR2;

	/* send memory addr, this sets the pointer register in slave device for the upcoming read*/
	I2C1->DR = maddr;

	/*  check txe is empty, then should check BTF before restart */
	while(!(I2C1->SR1 & SR1_TXE)){}
	//while(!(I2C1->SR1 & SR1_BTF)){}

	/* generate a restart condition and wait for the start bit to be set */
	I2C1->CR1 |= CR1_START;
	while(!(I2C1->SR1 & SR1_SB)){}

	/* read the data from slave here we are OR-ing the R/W bit to 1 for read*/
	I2C1->DR = saddr << 1 | 1;

	/* wait for the addr flags is set, disable the ACK, then clear it */
	while(!(I2C1->SR1 & SR1_ADDR)){}
	/* disable the acknowledge */
	I2C1->CR1 &=~CR1_ACK;
	tmp = I2C1->SR2;



	/*  should wait for BTF then generate stop*/
	//while(!(I2C1->SR1 & SR1_BTF)){}
	I2C1->CR1 |= CR1_STOP;

	/* wait for data register to be set */
	while(!(I2C1->SR1 & SR1_RXNE)){}

	/* save the byte in master, then increment the pointer to the next index of the buffer */
	*data++ = I2C1->DR;
}

void I2C_burstRead(uint8_t saddr, uint8_t maddr, int n, char* data)
{
	volatile int tmp;

	/*wait while the bus is busy make sure the I2C bus is not busy*/
	while (I2C1->SR2 & SR2_BUSY){}

	/* generate a start condition and wait for the start bit */
	I2C1->CR1 |= CR1_START;
	while(!(I2C1->SR1 & SR1_SB)){}

	/* transmit slave address + Write
	 * the slave address is 7-bits and it with the R/W (1/0) bit is the the first 8 bits of the frame.
	 * the ACK bit is then sent followed buy the data, another ACK bit and then a stop condition.
	 * so the address needs to be put in the data register along with the actual data to be read/written.
	 *
	 * By left shifting a 7-bit addr we are adding the R/W bit to 0 or write. DR receives 8 bits in total */
	I2C1->DR = saddr << 1;

	/* wait for the addr flags is set, then clear it */
	while(!(I2C1->SR1 & SR1_ADDR)){}
	tmp = I2C1->SR2;

	/*  check txe is empty */
	while(!(I2C1->SR1 & SR1_TXE)){}

	/* send memory addr, this sets the pointer register in slave device for the upcoming read*/
	I2C1->DR = maddr;

	/*  check txe is empty, then should check BTF before restart */
	while(!(I2C1->SR1 & SR1_TXE)){}
	//while(!(I2C1->SR1 & SR1_BTF)){}

	/* generate a start condition and wait for the start bit */
	I2C1->CR1 |= CR1_START;
	while(!(I2C1->SR1 & SR1_SB)){}

	/* read the data from slave here we are OR-ing the R/W bit to 1 for read*/
	I2C1->DR = saddr << 1 | 1;

	/* wait for the addr flags is set, then clear it */
	while(!(I2C1->SR1 & SR1_ADDR)){}
	tmp = I2C1->SR2;

	/* enable the acknowledge */
	I2C1->CR1 |= CR1_ACK;

	/* now read the bytes */
	while(n > 0U)
	{
		/* check if one byte is left */
		if (n == 1U)
		{
			/* disable the acknowledge */
			I2C1->CR1 &=~CR1_ACK;

			/*  should wait for BTF then generate stop*/
			//while(!(I2C1->SR1 & SR1_BTF)){}
			I2C1->CR1 |= CR1_STOP;

			/* wait for data register to be set */
			while(!(I2C1->SR1 & SR1_RXNE)){}

			/* save the byte in master, then increment the pointer to the next index of the buffer */
			*data++ = I2C1->DR;
			break;
		}
		else
		{
			/* wait for data register to be set */
			while(!(I2C1->SR1 & SR1_RXNE)){}

			/* save the byte in master, then increment the pointer to the next index of the buffer */
			*data++ = I2C1->DR;

			n--;
		}
	}
}

void I2C_byteWrite(uint8_t saddr,  char* data)
{
	volatile int tmp;

		/*wait while the bus is busy make sure the I2C bus is not busy*/
		while (I2C1->SR2 & SR2_BUSY){}

		/* generate a start condition and wait for the start bit */
		I2C1->CR1 |= CR1_START;
		while(!(I2C1->SR1 & SR1_SB)){}

		/* send slave addr + write */
		I2C1->DR = saddr << 1;

		/* wait for the addr flags is set, then clear it */
		while(!(I2C1->SR1 & SR1_ADDR)){}
		tmp = I2C1->SR2;

		/*  wait until data register is empty*/
		while(!(I2C1->SR1 & SR1_TXE)){}

		/* send they byte addr */
		I2C1->DR = *data;

		/*  should wait for BTF then generate stop*/
		while(!(I2C1->SR1 & SR1_BTF)){}
		I2C1->CR1 |= CR1_STOP;
}

void I2C_burstWrite(uint8_t saddr, uint8_t maddr, int n, char* data)
{
	volatile int tmp;

		/*wait while the bus is busy make sure the I2C bus is not busy*/
		while (I2C1->SR2 & SR2_BUSY){}

		/* generate a start condition and wait for the start bit */
		I2C1->CR1 |= CR1_START;
		while(!(I2C1->SR1 & SR1_SB)){}

		/* send slave addr + write */
		I2C1->DR = saddr << 1;

		/* wait for the addr flags is set, then clear it */
		while(!(I2C1->SR1 & SR1_ADDR)){}
		tmp = I2C1->SR2;

		/*  wait until data register is empty*/
		while(!(I2C1->SR1 & SR1_TXE)){}

		/* send memory addr */
		I2C1->DR = maddr;

		/* send data to slave */
		for(int i = 0; i < n; i ++){
			/*  wait until data register is empty*/
			while(!(I2C1->SR1 & SR1_TXE)){}

			/* send memory addr */
			I2C1->DR = *data++;
			i++;
		}

		/*  should wait for BTF then generate stop*/
		while(!(I2C1->SR1 & SR1_BTF)){}
		I2C1->CR1 |= CR1_STOP;
}








































