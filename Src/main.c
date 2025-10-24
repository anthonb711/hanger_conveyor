
#include "lcd_i2c.h"
#include "systick.h"

//
int main(void)
{

	lcd_i2c_init();
	systickDelayMs(2500);
	lcd_four_bit_write((DSP_ON | CURSOR_ON| CURSOR_BLINK) , CMD);


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


	/* Loop forever */
	while(1){}
}
