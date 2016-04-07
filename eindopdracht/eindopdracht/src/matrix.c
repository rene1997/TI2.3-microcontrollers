/*
 * matrix.c
 *
 * Created: 7-4-2016 16:50:08
 *  Author: rene
 */ 

 #include <avr/io.h>
 #include <util/delay.h>
 #include <stdlib.h>

 #include "main.h"
 #include "matrix.h"


 yPositions[8] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
 xPositions[8] = {0x00, 0x02, 0x04, 0x06, 0x08, 0x0A, 0x0C, 0x0E};

 void initMatrix(){
	wait(25);
	twi_init();		// Init TWI interface
	buttoninit();	// Init buttons for snake

	// Init HT16K22. Page 32 datasheet
	twi_start();
	twi_tx(0xE0);	// Display I2C addres + R/W bit
	twi_tx(0x21);	// Internal osc on (page 10 HT16K33)
	twi_stop();
	
	twi_start();
	twi_tx(0xE0);	// Display I2C address + R/W bit
	twi_tx(0xA0);	// HT16K33 pins all output
	twi_stop();

	twi_start();
	twi_tx(0xE0);	// Display I2C address + R/W bit
	twi_tx(0xE3);	// Display Dimming 4/16 duty cycle
	twi_stop();

	twi_start();
	twi_tx(0xE0);	// Display I2C address + R/W bit
	twi_tx(0x81);	// Display OFF - Blink On
	twi_stop();

	twi_clear();
 }

 /******************************************************************/
 void twi_init(void)
 /*
 short:			Init AVR TWI interface and set bitrate
 inputs:
 outputs:
 notes:			TWI clock is set to 100 kHz
 Version :    	DMK, Initial code
 *******************************************************************/
 {
	 TWSR = 0;
	 TWBR = 32;	 // TWI clock set to 100kHz, prescaler = 0
 }



 /******************************************************************/
 void twi_start(void)
 /*
 short:			Generate TWI start condition
 inputs:
 outputs:
 notes:
 Version :    	DMK, Initial code
 *******************************************************************/
 {
	 TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);	//<<< code datasheet
	 //TWCR = (0x80 | 0x20 | 0x04);	//code diederich <<<
	 //while( 0x00 == (TWCR & 0x80) );

	 //wait for TWINT flag set. This indicates that the Start condition has been transmitted
	 while(!(TWCR & (1<<TWINT)));
	 

 }

 /******************************************************************/
 void twi_stop(void)
 /*
 short:			Generate TWI stop condition
 inputs:
 outputs:
 notes:
 Version :    	DMK, Initial code
 *******************************************************************/
 {
	 TWCR = (0x80 | 0x10 | 0x04);
 }

 void twi_clear(void){
	 int i = 0x00;
	 for(; i <= 0x0E; i += 0x02){
		 twi_start();
		 twi_tx(0xE0);	// Display I2C addres + R/W bit
		 twi_tx(i);	// Address
		 twi_tx(0x00);	// data
		 twi_stop();
	 }
 }

 void twi_fill(){
	 int i = 0x00;
	 for(; i <= 0x0E; i += 0x02){
		 twi_start();
		 twi_tx(0xE0);	// Display I2C addres + R/W bit
		 twi_tx(i);	// Address
		 twi_tx(0xFF);	// data
		 twi_stop();
	 }
 }

 void twi_position(POSITION position){
	 

	 twi_start();
	 twi_tx(0xE0);	// Display I2C addres + R/W bit
	 twi_tx(position.x);	// Address
	 int y = position.y;
	 for(int i = 0; i <= snakelength; i++){
		 if(position.x == allPositions[i].x && position.y != allPositions[i].y){
			 y = allPositions[i].y + y;
		}
	 }
	 
	 twi_tx(y);	// data
	 twi_stop();
 }

 void twi_write(char text[])
 {
	 int i = 0x00;
	 for(; i <= 0x0E; i += 0x02){
		 twi_clear();
		 twi_start();
		 twi_tx(0xE0);	// Display I2C addres + R/W bit
		 twi_tx(i);	// Address
		 twi_tx(text[1]);	// data
		 twi_stop();
		 wait(1000);
	 }
 }

 /******************************************************************/
 void twi_tx(unsigned char data)
 /*
 short:			transmit 8 bits data
 inputs:
 outputs:
 notes:
 Version :    	DMK, Initial code
 *******************************************************************/
 {
	 
	 TWDR = data;
	 TWCR = (1<<TWINT) | (1<<TWEN);

	 while(!(TWCR & (1<<TWINT)));

	 //TWCR = (0x80 | 0x04);
	 //while( 0 == (TWCR & 0x80) );
 }