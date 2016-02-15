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

#define BIT(x) (1<<(x))	

//deze enum bevat alle states die mogelijk zijn
enum
{
	startState,
	s1State,
	s2State,
	s3State,
	endState
}CurrentState;

void start(int state);
void s1(int state);
void s2(int state);
void s3(int state);
void end(int state);

void wait(int milliseconds);

int main (void)
{
	int state;
	DDRD = 0b0000000; //Port D is input
	DDRC = 0b11111111; //Port C is output

	board_init();

	//hier wordt gecontroleerd welke knop is ingedrukt, en welke state actief is
	state = startState;
	while (1)
	{
		if(PIND5 && (state == startState || state == s1State))
		{
			s2(state);
		}
		else if(PIND5 && state == s2State)
		{
			s3(state);
		}
		else if(PIND5 && state == s3State)
		{
			end(state);
		}
		if(PIND6 && (state == s2State || state == startState))
		{
			s1(state);
		}
		else if(PIND6 && state == s3State)
		{
			end(state);
		}
		if(PIND7 && !state == startState)
		{
			start(state);
		}
	}
}

void start(int state)
{
	state = startState;
	PORTC ^= BIT(1);
	wait(1000); 
	PORTC = 0b00000000;
}

void s1(int state)
{
	state = s1State;
	PORTC ^= BIT(2);
	wait(1000); 
	PORTC = 0b00000000;
}

void s2(int state)
{
	state = s2State;
	PORTC ^= BIT(3);
	wait(1000);
	PORTC = 0b00000000;
}

void s3(int state)
{
	state = s3State;
	PORTC ^= BIT(4);
	wait(1000);
	PORTC = 0b00000000;
}

void end(int state){
	state = endState;
	PORTC ^= BIT(5);
	wait(1000);
	PORTC = 0b00000000;
}

void wait(int milliseconds){
	for(int i = 0; i<milliseconds; i++)
	_delay_ms(1);
}