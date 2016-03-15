/*
 * Project name		: Demo5_1 : UART - send / receive characters with waiting
 * Author			: Avans-TI, JW
 * Revision History	: 20110227: - initial release;
 * Description		: This program receive a character, and sends it back
 * Test configuration:
     MCU:             ATmega128
     Dev.Board:       BIGAVR6
     Oscillator:      External Clock 08.0000 MHz
     Ext. Modules:    -
     SW:              AVR-GCC
 * NOTES:
     - Turn ON switch 12, PEO/PE1 tot RX/TX
*/

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <ctype.h>							//include for made char upercase
#include "uar"

#define BIT(x)		(1 << (x))
#define UART0_BAUD	4800					// Baud rate USART0
#define MYUBRR		F_CPU/16/UART0_BAUD - 1	// My USART Baud Rate Register


char character;

// wait(): busy waiting for 'ms' millisecond
// Used library: util/delay.h
void wait( int ms )
{
	for (int tms=0; tms<ms; tms++)
	{
		_delay_ms( 1 );						// library function (max 30 ms at 8MHz)
	}
}


// Main program: USART0: send & receive
int main( void )
{
	DDRB = 0xFF;							// set PORTB for output, for testing
	DDRA = 0xFF;							// set PORTA for output, for testing
	usart0_init();							// initialize USART0
	usart0_start();							// uart0: start send & receive

	while (1)
	{
		wait(50);							// every 50 ms (busy waiting)
		PORTB ^= BIT(7);					// toggle bit 7 for testing

		char tempchar = uart0_receiveChar();// read char
		character = toupper(tempchar);		// character to upper case

		PORTA = character;					// show read character, for testing

		uart0_sendChar(character);			// send back
	}
}
