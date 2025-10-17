/*
 * lcd_i2c.c
 *
 *  Created on: Oct 14, 2025
 *      Author: Anthon Brown
 */

#include "lcd_i2c.h"
#include "systick.h"


void lcd_i2c_init(void)
{
	I2C1_init();
	/* wait for LCD vin rise */
	systickDelayMs(50);

	/* initialize LCD 4-bit 2 lines  */
	lcd_eight_bit_write(INIT_VAL);
	systickDelayMs(5);
	lcd_eight_bit_write(INIT_VAL);
	systickDelayMs(1);
	lcd_eight_bit_write(INIT_VAL);
	lcd_eight_bit_write(FOUR_BIT);

	/* now in 4-bit mode */
	/* display off */
	lcd_four_bit_write(DSP_SET, CMD);
	systickDelayMs(1);

	/* display clear */
	lcd_four_bit_write(DSP_CLEAR, CMD);
	systickDelayMs(1);

	/* entry mode right */
	lcd_four_bit_write(CURSOR_R, CMD);
	systickDelayMs(1);

	/* Cursor on */
	lcd_four_bit_write(DSP_ON, CMD);
	systickDelayMs(1);

}




void lcd_eight_bit_write(uint8_t cmd)
{
	uint8_t data;
	data = (cmd | EN);
	/* HIGH LOW Pulse on E pin */
	I2C_byteWrite(LCD_I2C_ADDR,  data);
	data = (cmd & ~EN);
	I2C_byteWrite(LCD_I2C_ADDR,  data);

}



void lcd_four_bit_write(uint8_t value, uint8_t mode){
	uint8_t data;

	/* mode = 0 is an lcd cmd write, mode = RS is an lcd write */
	uint8_t ctrl = ((mode & RS) | BKLGHT_ON);

	/* split byte into high_nib and low_nib using mask */
	uint8_t high_nib = value&0xF0;
	uint8_t low_nib = ((value<<4)&0xF0);

	/* put first 4-bits on wire and pulse E */
	data = ((high_nib | ctrl)  | EN);
	I2C_byteWrite(LCD_I2C_ADDR, data);
	systickDelayMs(1);
	data = (data & ~EN);
	I2C_byteWrite(LCD_I2C_ADDR, data);

	/* put last 4-bits on wire and pulse E */
	data = ((low_nib | ctrl) | EN);
	I2C_byteWrite(LCD_I2C_ADDR, data);
	systickDelayMs(1);
	data = (data & ~EN);
	I2C_byteWrite(LCD_I2C_ADDR, data);

}


