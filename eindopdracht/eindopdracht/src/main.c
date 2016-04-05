/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** ledmatrix.c
**
** Beschrijving:	Simple HT16K33 Ledmatix demo.
** Target:			AVR mcu
** Build:			avr-gcc -std=c99 -Wall -O3 -mmcu=atmega128 -D F_CPU=8000000UL -c ledmatrix.c
**					avr-gcc -g -mmcu=atmega128 -o ledmatrix.elf ledmatrix.o
**					avr-objcopy -O ihex ledmatrix.elf ledmatrix.hex 
**					or type 'make'
** Author: 			dkroeske@gmail.com
** -------------------------------------------------------------------------*/


#include <avr/io.h>
#include <util/delay.h>
#include "main.h"

#define BIT(x) (1<<(x))	

POSITION position;

//
int lastPressed = 0;

void buttoninit(){
	DDRB = 0x00;	//set port B complete input
	DDRC = 0x00;	//set port C complete input
}

/*
 *this function checks the buttons for input
 */
void checkinput(void){
	

	if((PINB) & BIT(0)){			//go right
		lastPressed = RIGHT;
	}else if((PINB) & BIT(1)){		//go down
		lastPressed = DOWN;
	}else if((PINB) & BIT(2)){		//go left
		lastPressed = LEFT;
	}else if((PINC) & BIT(1)){		//go up
		lastPressed = UP;
	}

	changePosition(lastPressed);
}

void changePosition(int direction){
	switch(direction)
	{
		case RIGHT:
			if(position.x >0)
				position.x -= 0x02;
			break;
		case DOWN:
			if(position.y < 0x40)
				position.y = (position.y << 1);
			else if(position.y == 0x80)
				position.y = 0x01;
			break;
		case LEFT:
			if(position.x < 0x0E)
				position.x += 0x02;
			break;
		case UP:
			if(position.y == 0x01){		//0x02 == second row
				position.y = 0x80;		//0x80 == first row
			}else if(position.y >=0x02 && position.y != 0x80)
				position.y = (position.y >>1);
			break;
		default:
			break;
	}
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
	twi_tx(position.y);	// data
	twi_stop();
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

/******************************************************************/
void wait( int ms )
/* 
short:			Busy wait number of millisecs
inputs:			int ms (Number of millisecs to busy wait)
outputs:	
notes:			Busy wait, not very accurate. Make sure (external)
				clock value is set. This is used by _delay_ms inside
				util/delay.h
Version :    	DMK, Initial code
*******************************************************************/
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

/******************************************************************/
int main( void )
/* 
short:			main() loop, entry point of executable
inputs:			
outputs:	
notes:			Looping forever, trashing the HT16K33
Version :    	DMK, Initial code
*******************************************************************/
{
	
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

	position.x = 0x08;
	position.y = 0x08;
	twi_position(position);
	while (1)
	{
		
		checkinput();
		twi_clear();
		twi_position(position);
		wait(1000);
		
		/*
		//twi_clear();
		//wait(1000);
		//twi_fill();
		twi_start();
		twi_tx(0xE0);	// Display I2C addres + R/W bit
		twi_tx(0x02);	// Address
		//0b11111111
		twi_tx(0xAA);	// data
		twi_stop();

		wait(1000);	

		twi_start();
		twi_tx(0xE0);	// Display I2C addres + R/W bit
		twi_tx(0x02);	// Address
		twi_tx(0x55);	// data
		//twi_tx(0x00);	// data
		twi_stop();	

		wait(1000);*/
	}

	return 1;
}
