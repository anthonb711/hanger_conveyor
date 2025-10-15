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
	I2C_init();

	/* wait for LCD vin rise */
	systickDelayMs(30);

	/* initialize LCD 4-bit 2 lines  */
	lcd_cmd(INIT_VAL);

	systickDelayMs(1);
	lcd_cmd(INIT_VAL);

	systickDelayMs(1);
	lcd_cmd(INIT_VAL);

	/* function set 4-bit 2 lines */

	/* clear screen and set cursor home */

}




void lcd_cmd(uint8_t cmd)
{
	uint8_t data;

	data = cmd | EN;
	/* HIGH LOW Pulse on E pin */
	I2C_byteWrite(LCD_I2C_ADDR,  data);

	data = (cmd & ~EN) | LED_BL;
	I2C_byteWrite(LCD_I2C_ADDR,  data);


}

lcd_cmd(0x30);
