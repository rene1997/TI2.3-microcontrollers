/*
 * Project name:
     Demo4_5 : PWM with timer 1 Fast PWM mode at PORTB.5, PB.6 en PB.7
	 			parallel, 3x, for RGB LED
 * Author: Avans-TI, JW
 * Revision History: 
     20101230: - initial release;
 * Description:
     This program gives an interrupt on each ms
 * Test configuration:
     MCU:             ATmega128
     Dev.Board:       BIGAVR6
     Oscillator:      External Clock 08.0000 MHz
     Ext. Modules:    -
     SW:              AVR-GCC
 * NOTES:
     - Turn ON the PORT LEDs at SW12.1 - SW12.8
*/

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BIT(x)			(1 << (x))

unsigned int sCount=0, minutes=0, hours=0;

// wait(): busy waiting for 'ms' millisecond
// Used library: util/delay.h
void wait( int ms )
{
	for (int tms=0; tms<ms; tms++)
	{
		_delay_ms( 1 );			// library function (max 30 ms at 8MHz)
	}
}

// Initialize timer 1: fast PWM at pin PORTB.6 (hundredth ms)
void timer1Init( void )
{
	OCR1A = 0;					// RED, default, off
	OCR1B = 0;					// GREEN, default, off
	OCR1C = 0;					// BLUE, default, off
	TCCR1A = 0b10101001;		// compare output OC1A,OC1B,OC1C
	TCCR1B = 0b00001011;		// fast PWM 8 bit, prescaler=64, RUN
}

// Set pulse width for RED on pin PB5, 0=off, 255=max
void setRed( unsigned char red )
{
	OCR1A = red;
}

// Set pulse width for Green on pin PB6, 0=off, 255=max
void setGreen( unsigned char green )
{
	OCR1B = green;
}

// Set pulse width for Blue on pin PB7, 0=off, 255=max
void setBlue( unsigned char blue )
{
	OCR1C = blue;
}

// Main program: Counting on T1
int main( void )
{
	DDRB = 0xFF;					// set PORTB for compare output 
	timer1Init();
	wait(100);

	while (1)
	{
		//start values
		int Red = 255;
		int Blue = 1;
		int Green = 1;

		//set values from start
		setRed (Red);
		setGreen(Green);
		setBlue(Blue);

		//first 60 degrees 
		for(; Green <= 254; Green += 2){
			setGreen(Green);
			wait(100);
		}
		for(; Red >= 1; Red -=2){
			setRed(Red);
			wait(100);
		}

		for(; Blue <=254; Blue +=2){
			setBlue(Blue);
			wait(100);
		}

		for(; Green >=1; Green -=2){
			setGreen(Green);
			wait(100);
		}

		for(; Red <=254; Red -=2){
			setRed(Red);
			wait(100);
		}
		for(;Blue >=1; Blue -=2){
			setBlue(Blue);
			wait(100);
		}

		
		// change some colors
		// RED
		
	} 
}
