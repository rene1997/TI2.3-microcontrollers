/*
 * LCD.c
 *
 * Created: 27-2-2016 19:51:39
 *  Author: Arjen
 */ 
 #include <asf.h>
 #include <util/delay.h>
 #include "LCD.h"

 void init_lcd()
 {
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

 void lcd_command(unsigned char dat)
 {
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

 void lcd_writeLine1 ( char text1[], int length)
 {
	 // eerst de eerste 8 karakters = regel 1
	 // eerste pos regel 1
	 lcd_command(0x80);
	 for (int i=0; i<length - 1; i++) {
		 lcd_writeChar( text1[i] );
	 }
 }

 void lcd_writeLine2 ( char text2[], int length )
 {
	 // dan de eerste 8 karakters = regel 2
	 // eerste pos regel 2
	 lcd_command(0xC0);
	 for (int i=0; i<length - 1; i++) {
		 lcd_writeChar( text2[i] );
	 }
 }
