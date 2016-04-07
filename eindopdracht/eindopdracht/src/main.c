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
#include <stdlib.h>
#include "main.h"
#include "matrix.h"
#include "LCD.h"

gameStatus status = MENU;
snakelength = 1;
lastPressed = -1;

//MatrixText[3] = {0xff, 0x55, 0xaa};
//last button pressed by user


unsigned int score = 0;
unsigned int seed = 0;

void buttoninit(){
	DDRB = 0x00;	//set port B complete input
	DDRC = 0x00;	//set port C complete input
}

/*
 *this function checks the buttons for input
 */
void checkinput(){
	//make seed for random loot
	seed ++;
	if(seed > 10000)
		seed = 0;

	if((PINA) & BIT(0)){			//go right
		lastPressed = RIGHT;
	}else if((PINA) & BIT(1)){		//go down
		lastPressed = DOWN;
	}else if((PINA) & BIT(2)){		//go left
		lastPressed = LEFT;
	}else if((PINB) & BIT(1)){		//go up
		lastPressed = UP;
	}else if((PINB) & BIT(0)){
		if(status != PLAYING)
		{
			status = PLAYING;
		}
	}
}

void changePosition(int index, int direction){
	if(index != HEAD){
		allPositions[index].x = allPositions[index-1].x;
		allPositions[index].y = allPositions[index -1].y;
	}else if(index == LOOT){
		return;
	}else{
		switch(direction)
		{
			case RIGHT:
				if(allPositions[index].x >0)
					allPositions[index].x -= 0x02;
				break;
			case DOWN:
				if(allPositions[index].y < 0x40)
					allPositions[index].y = (allPositions[HEAD].y << 1);
				else if(allPositions[index].y == 0x80)
					allPositions[index].y = 0x01;
				break;
			case LEFT:
				if(allPositions[index].x < 0x0E)
					allPositions[index].x += 0x02;
				break;
			case UP:
				if(allPositions[index].y == 0x01){		//0x02 == second row
					allPositions[index].y = 0x80;		//0x80 == first row
				}else if(allPositions[index].y >=0x02 && allPositions[index].y != 0x80)
					allPositions[index].y = (allPositions[index].y >>1);
				break;
			default:
				break;
		}
	}
	
}

void addSnakeLength(){
	snakelength ++;
}


void checkColission()
{
	if(checkPositions(allPositions[HEAD], allPositions[LOOT]) ==1)
	{
		addSnakeLength();
		setLootPosition();
		
		score++;
		return;
	}

	for(int i = 1; i <= snakelength; i++){
		for(int j = 1; j <= snakelength; j ++){
			if(checkPositions(allPositions[i],allPositions[j]) && i != j){
				//game over:
				status = GAMEOVER;	
			}
		}
	}

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

void setLootPosition(){
	srand(seed);
	int done = 0;
	while(! done){
		//x value of the loot
		allPositions[LOOT].x = xPositions[rand() % 8]; //random index from xPositions array
		//y value of the loot
		allPositions[LOOT].y = yPositions[rand() % 8]; //random index from yPositions array
		done = 1;
		for(int i = 1; i <=snakelength; i ++){
			if(checkPositions(allPositions[LOOT], allPositions[i]) == 1)
				done = 0;
		}
	}
	
}

//checks if two positions are on the same dot:
int checkPositions(POSITION a, POSITION b){
	if(a.x == b.x){
		if(a.y == b.y)
			return 1;
	}
	return 0;
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
	//init dot
	initMatrix();

	//init lcd
	init_lcd();

	//set position of head snake
	allPositions[HEAD].x = 0x08;
	allPositions[HEAD].y = 0x08;

	//set position of first body
	//allPositions[HEAD +1].x = 0x06;
	//allPositions[HEAD +1].y = 0x08;
	//snakelength ++;

	//set loot at random position
	setLootPosition();
	//twi_position(allPositions[HEAD]);
	lcd_writeLine("b0 to start", 0);
	lcd_writeLine("ctrl:A0,A1,A2,B1", 2);
	while (1)
	{
		switch(status)
		{
			case MENU:
				
				checkinput();
				wait(250);
				//twi_write(MatrixText);
				break;

			case PLAYING:
				lcd_writeLine("in game         ", 0);
				//refresh locations of the snake:
				for(int i = snakelength; i > 0; i--)
					changePosition(i, lastPressed);
				//check for collision
				checkColission();

				//clear the screen
				twi_clear();

				//fill the screen
				for(int i = 0; i <=snakelength; i ++)
					twi_position(allPositions[i]);
				
				for(int i = 0; i < 20; i++){
					checkinput();
					wait(100);
				}
					
				break;

			case GAMEOVER:
				lcd_writeLine("GAME OVER!  s:", 0);
				lcd_writeChar('0' + score/10);
				lcd_writeChar('0' + score %10);

				snakelength = 1;
				lastPressed = -1;
				allPositions[HEAD].y = 0x08;
				allPositions[HEAD].x = 0x08;
				score = 0;
				for(int i = 0; i <5; i++){
					twi_fill();
					wait(1000);
					twi_clear();
					wait(1000);
				}
				status = MENU;
				//checkinput()
				break;
		}
	}

	return 1;
}
