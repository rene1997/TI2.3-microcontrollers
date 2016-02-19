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

unsigned char segments[] = {{0x3f}, {0x06}}; 
//segment info: 
/*
https://en.wikipedia.org/wiki/Seven-segment_display
0 = 0x3f
1 = 0x06
2 = 0x5b
3 = 

*/

wait(int milliseconds){
	for (int i = 0; i <milliseconds i++)
	{
		_delay_ms(1);
	}
	
}

int main (void)
{
	DDRD = 0b11111111;					// PORTD all output 
	
	board_init();
	for(int i = 0; i < 10; i++){
		
		PORTD = segments[i];

	}
}
