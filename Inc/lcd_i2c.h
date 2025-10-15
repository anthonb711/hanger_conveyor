/*
 * lcd_i2c.h
 *
 *  Created on: Oct 14, 2025
 *      Author: Anthon Brown
 */

#ifndef LCD_I2C_H_
#define LCD_I2C_H_

#include "i2c.h"


/* This is the structure of the each byte sent
 * to the I2C back pack. LCD must init in 4-bit mode
  ┌────┬────┬────┬────┬────┬────┬────┬────┐
  │ 7  │ 6  │ 5  │ 4  │ 3  │ 2  │ 1  │ 0  │
  ├────┼────┼────┼────┼────┼────┼────┼────┤
  │ D7 │ D6 │ D5 │ D4 │ Vo │ EN │ RW │ RS │
  └────┴────┴────┴────┴────┴────┴────┴────┘
*
*/




#define LCD_I2C_ADDR	(0x27)	//default address for PCF8574T with no A0-A1-A2 jumpers

/* lcd control pins */
#define RS 				(1U<<0)
#define RW				(1U<<1)
#define EN				(1U<<2)
#define LED_BL			(1U<<3)


/* 2004 cmd defines */
#define SET_DDRAM		(0x80) // start of display memory addr
#define S		(0x38) // used to initialize the lcd with delays
#define EIGHT_BIT_FUN	(0x38) // this is for 8 bit, 5x8 char, 2 lines
#define	CURSOR_R		(0x06) //
#define CLEAR_DSP		(0x01) // homes cursor
#define	CURSOR_BLINK	(0x0F) // turns on display and blinks cursor



#endif /* LCD_I2C_H_ */
