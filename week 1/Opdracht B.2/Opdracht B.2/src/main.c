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

void wait(int milliseconds)
{
	for(int i = 0; i< milliseconds; i++)
	{
		_delay_ms(1);
	}
}

void cleanLeds(int milliseconds)
{
	PORTA = 0b00000000;
	PORTB = 0b00000000;
	PORTC = 0b00000000;
	PORTD = 0b00000000;
}

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */

	board_init();
	DDRA = 0b11111111;
	DDRB = 0b11111111;
	DDRC = 0b11111111;
	DDRD = 0b11111111;  //all pins are set to output
	DDRE = 0b11111111;
	DDRF = 0b11111111;
	DDRG = 0b11111111;
	

	//while true loop
	while(1)
	{
		for(int i = 0; i <8; i++)
		{
			PORTA = PORTA | (1<<i);
			wait(250);
		}
		for(int i = 0; i <8; i++)
		{
			PORTB = PORTB | (0b10000000>>i);
			wait(250);
		}
		for(int i = 0; i <8; i++)
		{
			PORTC = PORTC | (1<<i);
			wait(250);
		}
		for(int i = 0; i <8; i++)
		{
			PORTD = PORTD | (0b10000000>>i);
			wait(250);
		}
		
		cleanLeds(10);
		
	}

	return 1;
}


void lampsSnake()
{
	for(int i = 0; i <9; i++)
	{
		PORTA = PORTA | (1<<i);
		wait(2500);
	}
}
