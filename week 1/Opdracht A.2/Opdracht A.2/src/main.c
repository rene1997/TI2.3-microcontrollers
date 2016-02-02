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

void wait(int milliseconds )
{
	for(int i = 0; i < milliseconds; i++)
	{
		_delay_ms(1);
	}
}

int main (void)
{

	board_init();
	DDRA = 0b11111111;				//all pins are set to output

	while(1)
	{
		PORTA = 0b00001111;			//light 4 / 8 led
		wait(1000);					//wait 1000 milliseconds
		PORTA = 0b11110000;			//light other 4 leds
		wait(1000);					//wait 1000 milliseconds

	}

	return 1;
}
