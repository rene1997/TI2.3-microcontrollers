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

#include "uart0.h"
#include "lcd.h"

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


// send/receive uart - dB-meter
int main( void )
{
	char buffer[16];						// declare string buffer 
	char c[] = "Test";
	DDRB = 0xFF;							// set PORTB for output

	init_lcd();								// initialize LCD-display
	wait(25);
	usart0_init();							// initialize USART0
	usart0_start();

	while (1)
	{
		
		wait(5000);							// every 50 ms (busy waiting)
		lcd_command(0x01);
		PORTB ^= BIT(7);					// toggle bit 7 for testing

		uart0_receiveString(buffer);		// receive string from uart
		lcd_writeLine(c, 1);
		
		// write string to LCD display
	}
}


