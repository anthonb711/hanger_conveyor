#include "stm32f411xe.h"


#define SYSTICK_LOAD_VAL		16000
#define CTRL_ENABLE				(1U<<0)
#define CTRL_CLKSOURCE			(1U<<2)
#define CTRL_COUNTFLAG			(1U<<16)



void systickDelayMs (int delay)
{
	/* configure Systick */

	/* reload with number of clocks per millisecond */
	SysTick->LOAD = SYSTICK_LOAD_VAL;
	/* clear the current value register */
	SysTick->VAL = 0;
	/* enable systick and select internal clock source */
	SysTick->CTRL |= CTRL_ENABLE | CTRL_CLKSOURCE;

	for(int i = 0; i < delay; i++)
	{
		/* wait until the count flag is set*/
		while(!(SysTick->CTRL & CTRL_COUNTFLAG)) {}
	}

	/* disable systick and clear the config */
	SysTick->CTRL = 0;
}
