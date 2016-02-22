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

//array with values to view numbers on 7 segements display
unsigned char segments[] = {
0x3f, 0x06, 0x5B,0x4F,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71 }; 


//segment info: 
/*
https://en.wikipedia.org/wiki/Seven-segment_display
0 = 0x3f
1 = 0x06
2 = 0x5b
3 = 

*/

int INDEX;

void wait(int milliseconds){
	for(int i = 0; i < milliseconds; i++){
		_delay_ms(1);
	}
}

valueUP(){
	if(INDEX <15)
		INDEX ++;
	PORTC = segments[INDEX];
	wait(250);
}

valueDown(){
	if(INDEX > 0)
	INDEX --;
	PORTC = segments[INDEX];
	wait(250);
}

//when pin d2 is pressed
ISR(INT2_vect){
	valueDown();
}

//when pin d1 is pressed
ISR(INT1_vect){
	valueUP();
	
}

int main (void)
{
	DDRD = 0b11110000;			//set pin 0 - 4 input
								//set pin 4 - 7 output
	DDRC = 0b11111111;			// PORTC all output 

	//Init Interrupt hardware
	EICRA |= 0b00111100;		//int 1 rising edge, int 2 rising edge
	EIMSK |= 0b00000110;		//enable INT 1 & INT 2
	sei();
	board_init();
	INDEX = 0;
	PORTC = segments[INDEX];
	while(1){
		if(PIND == 0b00000110){  //check if pin d1 and d2 are pressed
			INDEX = 0;
			PORTC = segments[INDEX];
			wait(500);			
		}
	}
	
}


