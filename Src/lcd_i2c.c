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
	// wait for LCD vin rise
	systickDelayMs(50);

	// initialize LCD 4-bit 2 lines
	lcd_eight_bit_write(INIT_VAL);
	systickDelayMs(5);
	lcd_eight_bit_write(INIT_VAL);
	systickDelayMs(1);
	lcd_eight_bit_write(INIT_VAL);
	lcd_eight_bit_write(FOUR_BIT);

	// now in 4-bit mode
	// display off
	lcd_four_bit_write(DSP_SET, CMD);

	// display clear
	lcd_four_bit_write(DSP_CLEAR, CMD);

	// entry mode right
	lcd_four_bit_write(CURSOR_R, CMD);

	// Cursor on
	lcd_four_bit_write(DSP_ON, CMD);


}



void lcd_eight_bit_write(uint8_t cmd)
{
	// HIGH LOW Pulse on E pin
	I2C_byteWrite(LCD_I2C_ADDR, (cmd | EN));
	I2C_byteWrite(LCD_I2C_ADDR,  (cmd & ~EN));
}



void lcd_four_bit_write(uint8_t value, uint8_t mode){
	uint8_t data;

	/* mode = 0 is an lcd cmd write, mode = RS is an lcd write */
	uint8_t ctrl = ((mode & RS) | BKLGHT_ON);

	/* split byte into high_nib and low_nib using mask */
	uint8_t high_nib = value&0xF0;
	uint8_t low_nib = ((value<<4)&0xF0);

	  I2C_byteWrite(LCD_I2C_ADDR, BKLGHT_ON);
	  systickDelayMs(1);

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

	// wait for the lcd to execute the instruction
	systickDelayMs(1);

	// update the position of after a write to the display
	if (mode == RS)
	{
		update_cursor_position();
	}
}

//uint8_t expander_four_bit_read(uint8_t mode){
//	uint8_t data;
//	uint8_t data_mask = 0xF0;
//
//	/* mode = CMD reads address counter &| busy flag, mode = RS reads data from ACG or ADD */
//	uint8_t ctrl_rw = (BKLGHT_ON | RW | (mode & RS));
//	uint8_t ctrl_no_rw = (BKLGHT_ON | (mode & RS));
//	/*  */
//	uint8_t dummy_bits = 0xF0;
//	I2C_byteWrite(LCD_I2C_ADDR, (dummy_bits | ctrl_rw | EN));
//	systickDelayMs(1);
//
//	I2C_four_bit_read(LCD_I2C_ADDR, &data);
//	systickDelayMs(1);
//
//	I2C_byteWrite(LCD_I2C_ADDR, ((dummy_bits | ctrl_rw ) & ~EN));
//	systickDelayMs(1);
//
////	 I2C_byteWrite(LCD_I2C_ADDR, ((0x00) | BKLGHT_ON));
////	 systickDelayMs(1);
//	return data & data_mask;
//
//}

uint8_t lcd_four_bit_read(uint8_t mode)
{
	uint8_t ctrl_read = (BKLGHT_ON | RW |(mode & RS));
	uint8_t ctrl_write = (BKLGHT_ON | (mode & RS));
	uint8_t data_mask = 0xF0;
	uint8_t dummy_bits = 0xF0;
	uint8_t high_nib, low_nib;

	// set pins as inputs
	I2C_byteWrite(LCD_I2C_ADDR, (dummy_bits | ctrl_read));

	// read high nibble
	I2C_byteWrite(LCD_I2C_ADDR, (dummy_bits | ctrl_read | EN));
	systickDelayMs(1);
	I2C_four_bit_read(LCD_I2C_ADDR, &high_nib);
	systickDelayMs(1);
	I2C_byteWrite(LCD_I2C_ADDR, ((dummy_bits | ctrl_read ) & ~EN));

	// read low nibble
	I2C_byteWrite(LCD_I2C_ADDR, (dummy_bits | ctrl_read | EN));
	systickDelayMs(1);
	I2C_four_bit_read(LCD_I2C_ADDR, &low_nib);
	systickDelayMs(1);
	I2C_byteWrite(LCD_I2C_ADDR, ((dummy_bits | ctrl_read ) & ~EN));
	systickDelayMs(1);


	 // set the expander pins back to outputs
	I2C_byteWrite(LCD_I2C_ADDR, (0x00 | (ctrl_write & ~(EN|RW))));
	systickDelayMs(1);


	// return combined byte
	return  (high_nib & data_mask) | ((low_nib & data_mask) >> 4);

}



void set_cursor_position(unsigned int row, unsigned int col)
{
	uint8_t row_offsets[4] = { 0x00, 0x40, 0x14, 0x54 };

	if ((row < 0) || (row > 3))
	{
		return;
	}
	else {

	lcd_four_bit_write((SET_DDRAM | (row_offsets[row] + col)), CMD);
	update_cursor_position();
	}
}

void update_cursor_position(void)
{
	cursor_position = lcd_four_bit_read(CMD);
}


