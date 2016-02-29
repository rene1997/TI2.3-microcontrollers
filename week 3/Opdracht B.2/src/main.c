/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>
#include <util/delay.h>
#include <stdio.h>
#include "LCD.h"


#define BIT(x) (1<<(x))	

char numbers[4];
int amountpressed = 0;

ISR( TIMER2_OVF_vect )
{
	sprintf(numbers,"%d",amountpressed);
	lcd_writeLine(numbers, 1);
	amountpressed ++;

	lcd_setCursorPosition(0);
	TCNT2 = -1;
}

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */

	init_lcd();
	_delay_ms(25);
	TCNT2 = -1; // of TCNT2=0xf6
	TIMSK |= BIT(6); // T2 overflow interrupt enable, p. 162
	TCCR2 = 0b00011111; //ext counting, rising

	DDRD &= ~BIT(7);

	sei();
	while(1)
	{
		

	}
}
