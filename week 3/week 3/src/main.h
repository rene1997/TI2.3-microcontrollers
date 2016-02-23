/*
 * main.h
 *
 * Created: 23-2-2016 11:28:29
 *  Author: rkeet
 */ 


#ifndef MAIN_H_
#define MAIN_H_

void init_lcd();
void lcd_command(unsigned char);
void lcd_writeChar( unsigned char);
void lcd_writeLine1 ( char text1[] );
void lcd_writeLine2 ( char text2[] );



#endif /* MAIN_H_ */