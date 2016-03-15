/*
 * Author			: rene
 * Revision History	: 20160315: - initial release;
 * Test configuration:
     MCU:             ATmega128
     Dev.Board:       BIGAVR6
     Oscillator:      External Clock 08.0000 MHz
     Ext. Modules:    -
     SW:              AVR-GCC
 * NOTES:
     - Turn ON switch 12, PEO/PE1 tot RX/TX
*/

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "uart0.h"

char character;

void usart0_init( void )						// initialize USART0 - receive/transmit
{
	int	ubrr = MYUBRR;
	UBRR0H = ubrr>>8;						// baudrate register, hoge byte
	UBRR0L = ubrr;							// baudrate register, lage byte
	UCSR0C = 0b00000110;					// asynchroon, 8 data - 1 stop - no parity
	UCSR0B = 0b00000000;					// receiver & transmitter enable
}

void usart0_start( void )					// receiver & transmitter enable
{
	UCSR0B |= BIT(RXEN0)|BIT(TXEN0);			// set bit RXEN = Receiver enable and TXEN = Transmitter enable
}

int uart0_sendChar( char ch )
{
	while (!(UCSR0A & BIT(UDRE0))) ;		// wait until UDRE0 is set: transmit buffer is ready
	UDR0 = character;								// send ch
	return 0;								// OK
}

char uart0_receiveChar( void )
{
	while (!(UCSR0A & BIT(RXC0))) ;			// if RX0 is set: unread data present in buffer
	return UDR0;							// read ch
}

// UART0: receive string until LF
int uart0_receiveString( char* string)
{
	for(int i = 0; i < LF; i++){
		while(!(UCSR0A & BIT(RXC0)));
		string[i] = UDR0;
	}
}

