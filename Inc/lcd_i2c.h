/*
 * lcd_i2c.h
 *
 *  Created on: Oct 14, 2025
 *      Author: Anthon Brown
 */

#ifndef LCD_I2C_H_
#define LCD_I2C_H_

#include <stdint.h>
#include "i2c.h"


/**********************************************
 Byte Mapping to the I2C back pack.
 LCD must init in 4-bit mode
  ┌────┬────┬────┬────┬────┬────┬────┬────┐
  │ 7  │ 6  │ 5  │ 4  │ 3  │ 2  │ 1  │ 0  │
  ├────┼────┼────┼────┼────┼────┼────┼────┤
  │ D7 │ D6 │ D5 │ D4 │ Vo │ EN │ RW │ RS │
  └────┴────┴────┴────┴────┴────┴────┴────┘
**********************************************/




#define LCD_I2C_ADDR	(0x27)	//default address for PCF8574T with no A0-A1-A2 jumpers

/* lcd control pins */
#define RS 				(1U<<0)
#define CMD				(0x0)
#define RW				(1U<<1)
#define EN				(1U<<2)
#define BKLGHT_ON		(1U<<3)


/* 2004 cmd defines */
#define SET_DDRAM		(0x80) // base of display memory addr
#define SET_CGRAM		(0x40)
#define INIT_VAL		(0x30) // used to initialize the lcd
#define FOUR_BIT        (0x20)
#define TWO_LINES		(0x80)
#define FIVE_BY_EIGHT	(0x40)
#define DSP_CLEAR		(0x01) // homes cursor
#define DSP_SET			(0x08)
#define DSP_ON			(0x0C)
#define CURSOR_MOVE		(0x80)
#define CURSOR_ON		(0xE)
#define	CURSOR_BLINK	(0xF) // turns on display and blinks cursor
#define	CURSOR_R		(0x06) //

static uint8_t cursor_position;


void lcd_i2c_init				(void								);
void lcd_eight_bit_write		(uint8_t cmd						);
void lcd_four_bit_write			(uint8_t value, uint8_t mode		);
uint8_t lcd_four_bit_read		(uint8_t mode						);
uint8_t expander_four_bit_read	(uint8_t mode						);

void set_cursor_position		(unsigned int row, unsigned int col	);
void update_cursor_position		(void								);



#endif /* LCD_I2C_H_ */
