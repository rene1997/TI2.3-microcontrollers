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
#include "LCD.h"

#define BIT(x) (1<<(x))	

int TimerPreset = -10;
int count = 0;

ISR( TIMER2_OVF_vect )
{
	TCNT2 = TimerPreset; // Preset value
	if (PIND1)
	{
		count++; // Increment counter
	}
}

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */

	init_lcd();
	_delay_ms(25);
	TIMSK |= BIT(6);// T2 overflow interrupt enable 
	sei();
	TCCR2 = 0b00000111;// counter, normal mode, run
	DDRD &= ~BIT(1); // set PORTD.1 for input
	TCNT2 = 0;
	
	while(1)
	{
		 lcd_command(0x01);
		 _delay_ms(25);
		lcd_writeChar(count);
	}
}
