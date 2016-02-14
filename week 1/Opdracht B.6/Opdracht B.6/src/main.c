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

#define BIT(x) (1<<(x))	

void wait(int);

int main (void)
{
	bool buttonPressed = false; //veranderd van status wanneer portC.0 wordt ingedrukt
	DDRD = 0b11111111; //port D is output
	DDRC = 0b0000000; //port c is input

	board_init();
	
	while (1)
	{
		if (PINC)
		{
			if(buttonPressed)
			{
				buttonPressed = false;
			} 
			else 
			{
				buttonPressed = true;
			}
		}
		if(buttonPressed) 
		{
			PORTD ^= BIT(7);
			wait(250);
			PORTD = 0b00000000;
		}
		else
		{
			PORTD ^= BIT(7);
			wait(1000);
			PORTD = 0b00000000;
		}
	}
}

void wait(int milliseconds)
{
	int i = 0;
	for(; i < milliseconds; i++)
	_delay_ms(1);
}
