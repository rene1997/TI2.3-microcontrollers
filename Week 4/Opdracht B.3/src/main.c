#include <asf.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BIT(x)	(1 << (x))

// wait(): busy waiting for 'ms' millisecond
// Used library: util/delay.h
void wait( int ms )
{
	for (int tms=0; tms<ms; tms++)
	{
		_delay_ms( 1 );			// library function (max 30 ms at 8MHz)
	}
}


//initialize ADC: 10 bits, free running, single ended, continuous mode
void adcInit(){

	//channel 1 at PF1
	ADMUX = 0b01100001;

	//free running, division by 64
	ADCSRA = 0b11100110;
}


int main (void)
{
	board_init();
	DDRF = 0x00;	//set port F input
	DDRA = 0xFF;	//set port A output
	DDRB = 0xFF;	//set port B output

	//init adc
	adcInit();

	while(1){
		PORTB = ADCL;
		PORTA = ADCH;
	}


	
}
