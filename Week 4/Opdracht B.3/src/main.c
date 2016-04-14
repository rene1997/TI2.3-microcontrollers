#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "LCD.h"

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


// Initialize ADC: 10-bits (left justified), free running
void adcInit( void )
{
	ADMUX = 0b01100001;			// AREF=VCC, result left adjusted, channel1 at pin PF1
	ADCSRA = 0b11100110;		// ADC-enable, no interrupt, start, free running, division by 64
}

int binary_decimal(int n) /* Function to convert binary to decimal.*/

{
	int decimal=0, i=0, rem;
	while (n!=0)
	{
		rem = n%10;
		n/=10;
		decimal += rem*pow(2,i);
		++i;
	}
	return decimal;
}

// Main program: ADC at PF1
int main( void )
{
	DDRF = 0x00;				// set PORTF for input (ADC)
	DDRA = 0xFF;				// set PORTA for output 
	DDRB = 0xFF;				// set PORTB for output
	adcInit();					// initialize ADC
	init_lcd();
	char str[20];

	while (1)
	{
		PORTB = ADCL;			// Show MSB/LSB (bit 10:0) of ADC
		PORTA = ADCH;
		wait(100);				// every 100 ms (busy waiting)
		sprintf(str, "Temperatuur: %d",	binary_decimal(ADCL)); //converteer binair to decimal and put it in a char array
		lcd_writeLine(str, 1);
		wait(1000);
	}
}
