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



int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	char c[] = "RENÉ";
	init_lcd();
	//board_init();
	
	//lcd_command(0x81);
	_delay_ms(25);
	while(1)
	{
		lcd_command(0x01);
		//lcd_writeChar('A');
		lcd_writeLine1(c);
		_delay_ms(5000);
		lcd_writeLine2(c);
		_delay_ms(5000);
	}
}

void init_lcd(){
	//return home8
	DDRC = 0b11111111;
	_delay_ms(25);
	lcd_command(0x02);
	_delay_ms(25);
	//mode: 4 bits interface data, 2 lines, 5x data
	lcd_command(0x28);
	_delay_ms(25);
	// display: on, cursor off, blinking off 
	lcd_command( 0x0C ); 
	_delay_ms(25);
	//entry mode: cursor to right no shift
	lcd_command(0x06);
	_delay_ms(25);
	//Ram adress: 0, first position, line 1
	lcd_command(0x80);
	_delay_ms(25);
	lcd_command(0x01);
	_delay_ms(25);
}

void lcd_command(unsigned char dat){
	PORTC = dat & 0xF0;		//hoge nibble
	PORTC = PORTC | 0x08;	//data
	_delay_ms(25);
	PORTC = 0x04;			//stop 

	PORTC = (dat & 0x0F) <<4;	//lage nibble
	PORTC = PORTC | 0x08;

	_delay_ms(25);
	PORTC =  0x00;
}

void lcd_writeChar( unsigned char dat)
{
	PORTC = dat & 0xF0;
	PORTC = PORTC | 0x0C;

	_delay_ms(25);
	PORTC = 0x04;

	PORTC = (dat & 0x0F) << 4;
	PORTC = PORTC | 0x0C;

	_delay_ms(25);
	PORTC = 0x00;
}

void lcd_writeLine1 ( char text1[] )
{
	// eerst de eerste 8 karakters = regel 1
	// eerste pos regel 1
	lcd_command(0x80);
	for (int i=0; i<16; i++) {
		lcd_writeChar( text1[i] );
	}
}

void lcd_writeLine2 ( char text2[] )
{
	// dan de eerste 8 karakters = regel 2
	// eerste pos regel 2
	lcd_command(0xC0);
	for (int i=0; i<16; i++) {
		lcd_writeChar( text2[i] );
	}
}