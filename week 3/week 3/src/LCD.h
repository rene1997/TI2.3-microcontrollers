/*
 * LCD.h
 *
 * Created: 27-2-2016 19:51:53
 *  Author: Arjen
 */ 


#ifndef LCD_H_
#define LCD_H_

void init_lcd();
void lcd_command(unsigned char);
void lcd_writeChar( unsigned char);
void lcd_writeLine1 ( char text1[], int length );
void lcd_writeLine2 ( char text2[], int length );

#endif /* LCD_H_ */