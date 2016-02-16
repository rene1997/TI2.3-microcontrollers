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
#include "main.h"
 
int x = 0;

int main (void)
{
	
	board_init();
	DDRD = 0b11110000;			//set pin 0 - 4 input 
								//set pin 4 - 7 output
	DDRC = 0b11111111;			//set full port c output
	//Init Interrupt hardware
	EICRA |= 0b00111100;		//int 1 rising edge, int 2 rising edge
	EIMSK |= 0b00000110;		//enable INT 1 & INT 2
	sei();						//sets global interrupt enable (page 16 documentation)

	while(1){
		//empty!
		wait(1);
	}
	return 1;
}
void loopLight(){
	PORTC = (1<<x);
	x += 1;
	if(x > 7){
		x = 0;
	}
}

ISR(INT2_vect){
	loopLight();
}

ISR(INT1_vect){
	loopLight();
}


void wait(int milliseconds){
	for(int i = 0; i < milliseconds; i++){
	_delay_ms(1);
	}
}


