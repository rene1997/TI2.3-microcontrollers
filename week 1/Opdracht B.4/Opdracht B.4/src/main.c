/**
 * \file
 *
 * \brief Empty user application template
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

//this method makes a loop at port D
void ledLoop();
void wait(int);


int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */

	board_init();
	DDRD = 0b11111111; //set port D as output
	while(1){
		ledLoop();	
	}
}

void ledLoop(){
	for(int i = 0; i <9; i++)
	{
		PORTD = (1<<i);
		wait(500);
	}
}

void wait(int milliseconds){
	int i = 0;
	for(; i < milliseconds; i++)
		_delay_ms(1);
}