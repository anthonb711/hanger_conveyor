
#include "lcd_i2c.h"
#include "systick.h"

//
int main(void)
{

	lcd_i2c_init();
	systickDelayMs(2500);
	lcd_four_bit_write((DSP_ON | CURSOR_ON| CURSOR_BLINK) , CMD);
	lcd_four_bit_write('0', RS);
	lcd_four_bit_write('1', RS);
	lcd_four_bit_write('2', RS);
	lcd_four_bit_write('3', RS);
	lcd_four_bit_write('4', RS);
	lcd_four_bit_write('5', RS);
	lcd_four_bit_write('6', RS);
	lcd_four_bit_write('7', RS);
	lcd_four_bit_write('8', RS);
	lcd_four_bit_write('9', RS);
	lcd_four_bit_write('A', RS);
	lcd_four_bit_write('B', RS);
	lcd_four_bit_write('C', RS);
	lcd_four_bit_write('D', RS);
	lcd_four_bit_write('E', RS);
	lcd_four_bit_write('F', RS);

	lcd_four_bit_write('G', RS);
	lcd_four_bit_write('H', RS);
	lcd_four_bit_write('I', RS);
	lcd_four_bit_write('J', RS);
	lcd_four_bit_write('K', RS);
	lcd_four_bit_write('L', RS);
	lcd_four_bit_write('M', RS);
	lcd_four_bit_write('N', RS);
	lcd_four_bit_write('O', RS);
	lcd_four_bit_write('P', RS);
	lcd_four_bit_write('Q', RS);
	lcd_four_bit_write('R', RS);
	lcd_four_bit_write('S', RS);
	lcd_four_bit_write('T', RS);
	lcd_four_bit_write('U', RS);
	lcd_four_bit_write('V', RS);
	lcd_four_bit_write('W', RS);
	lcd_four_bit_write('X', RS);
	lcd_four_bit_write('Y', RS);
	lcd_four_bit_write('Z', RS);
	lcd_four_bit_write('a', RS);
	lcd_four_bit_write('b', RS);
	lcd_four_bit_write('c', RS);
	lcd_four_bit_write('d', RS);
	lcd_four_bit_write('e', RS);
	lcd_four_bit_write('f', RS);
	lcd_four_bit_write('g', RS);
	lcd_four_bit_write('h', RS);
	lcd_four_bit_write('i', RS);

	// Testing cursor moves and position reads
	set_cursor_position(0,0);
	set_cursor_position(1,0);
	set_cursor_position(2,0);
	set_cursor_position(3,0);

	set_cursor_position(0,9);
	set_cursor_position(1,9);
	set_cursor_position(2,9);
	set_cursor_position(3,9);

	set_cursor_position(0,19);
	set_cursor_position(1,19);
	set_cursor_position(2,19);
	set_cursor_position(3,19);

	systickDelayMs(1);

	lcd_four_bit_write('A', RS);




//
//	lcd_four_bit_write('T', RS);
//	lcd_four_bit_write('A', RS);
//	lcd_four_bit_write('R', RS);
//	lcd_four_bit_write('G', RS);
//	lcd_four_bit_write('E', RS);
//	lcd_four_bit_write('T', RS);
//	lcd_four_bit_write(' ', RS);
//	lcd_four_bit_write(' ', RS);
//	lcd_four_bit_write('H', RS);
//	lcd_four_bit_write('A', RS);
//	lcd_four_bit_write('N', RS);
//	lcd_four_bit_write('G', RS);
//	lcd_four_bit_write('E', RS);
//	lcd_four_bit_write('R', RS);
//	lcd_four_bit_write(':', RS);
//	lcd_four_bit_write(' ', RS);
//	lcd_four_bit_write(' ', RS);
//	lcd_four_bit_write(' ', RS);
//
//	/* set cursor to the right of row 2 addr0x053 */
//	lcd_four_bit_write((CURSOR_MOVE | 0x53), CMD);
//
//	/* set entry mode left */
//	lcd_four_bit_write(0x4, CMD);
//

//
//
//
//	/* move to row 4 and set entry to right */
//	lcd_four_bit_write((CURSOR_MOVE | 0x54), CMD);
//	lcd_four_bit_write(0x6, CMD);
//
//	/*  */
//	lcd_four_bit_write('P', RS);
//	lcd_four_bit_write('R', RS);
//	lcd_four_bit_write('E', RS);
//	lcd_four_bit_write('S', RS);
//	lcd_four_bit_write('S', RS);
//	lcd_four_bit_write(' ', RS);
//	lcd_four_bit_write('\'', RS);
//	lcd_four_bit_write('*', RS);
//	lcd_four_bit_write('\'', RS);
//	lcd_four_bit_write(' ', RS);
//	lcd_four_bit_write('T', RS);
//	lcd_four_bit_write('O', RS);
//	lcd_four_bit_write(' ', RS);
//	lcd_four_bit_write('E', RS);
//	lcd_four_bit_write('N', RS);
//	lcd_four_bit_write('T', RS);
//	lcd_four_bit_write('E', RS);
//	lcd_four_bit_write('R', RS);
//	lcd_four_bit_write(' ', RS);


	/* Loop forever */
	while(1){}
}
