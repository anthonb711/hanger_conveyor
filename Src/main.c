
#include "lcd_i2c.h"
#include "systick.h"



int main(void)
{
	lcd_i2c_init();
	systickDelayMs(2500);
	lcd_four_bit_write((DSP_ON | CURSOR_ON) , CMD);
	lcd_four_bit_write('C', RS);
	lcd_four_bit_write('U', RS);
	lcd_four_bit_write('R', RS);
	lcd_four_bit_write('R', RS);
	lcd_four_bit_write('E', RS);
	lcd_four_bit_write('N', RS);
	lcd_four_bit_write('T', RS);
	lcd_four_bit_write(' ', RS);
	lcd_four_bit_write('H', RS);
	lcd_four_bit_write('A', RS);
	lcd_four_bit_write('N', RS);
	lcd_four_bit_write('G', RS);
	lcd_four_bit_write('E', RS);
	lcd_four_bit_write('R', RS);
	lcd_four_bit_write(':', RS);
	lcd_four_bit_write(' ', RS);
	lcd_four_bit_write(' ', RS);
	lcd_four_bit_write('8', RS);
	lcd_four_bit_write('3', RS);
	lcd_four_bit_write('0', RS);

	/* move cursor to the beginning of the second line addr 0x40*/
	lcd_four_bit_write((CURSOR_MOVE | 0x40), CMD);

	lcd_four_bit_write('T', RS);
	lcd_four_bit_write('A', RS);
	lcd_four_bit_write('R', RS);
	lcd_four_bit_write('G', RS);
	lcd_four_bit_write('E', RS);
	lcd_four_bit_write('T', RS);
	lcd_four_bit_write(' ', RS);
	lcd_four_bit_write(' ', RS);
	lcd_four_bit_write('H', RS);
	lcd_four_bit_write('A', RS);
	lcd_four_bit_write('N', RS);
	lcd_four_bit_write('G', RS);
	lcd_four_bit_write('E', RS);
	lcd_four_bit_write('R', RS);
	lcd_four_bit_write(':', RS);
	lcd_four_bit_write(' ', RS);
	lcd_four_bit_write(' ', RS);

	/* set cursor to the right of row 2 addr0x053 */
	lcd_four_bit_write((CURSOR_MOVE | 0x53), CMD);

	/* set entry mode left */
	lcd_four_bit_write(0x4, CMD);

	/* write the number for show and turn the cursor off */
	systickDelayMs(2500);
	lcd_four_bit_write('1', RS);
	systickDelayMs(2500);
	lcd_four_bit_write('0', RS);
	systickDelayMs(2500);
	lcd_four_bit_write('0', RS);




	/* move to row 4 and set entry to right */
	lcd_four_bit_write((CURSOR_MOVE | 0x54), CMD);
	lcd_four_bit_write(0x6, CMD);

	/*  */
	lcd_four_bit_write('P', RS);
	lcd_four_bit_write('R', RS);
	lcd_four_bit_write('E', RS);
	lcd_four_bit_write('S', RS);
	lcd_four_bit_write('S', RS);
	lcd_four_bit_write(' ', RS);
	lcd_four_bit_write('\'', RS);
	lcd_four_bit_write('*', RS);
	lcd_four_bit_write('\'', RS);
	lcd_four_bit_write(' ', RS);
	lcd_four_bit_write('T', RS);
	lcd_four_bit_write('O', RS);
	lcd_four_bit_write(' ', RS);
	lcd_four_bit_write('E', RS);
	lcd_four_bit_write('N', RS);
	lcd_four_bit_write('T', RS);
	lcd_four_bit_write('E', RS);
	lcd_four_bit_write('R', RS);
	lcd_four_bit_write(' ', RS);


	/* Loop forever */
	while(1){}
}
