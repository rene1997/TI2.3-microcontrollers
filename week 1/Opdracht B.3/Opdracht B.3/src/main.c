/*
*Author = René Keijzer
*Date = 3-2-2016
*This program light led 7 from Port D when button 0 of Port D is pressed 
*/
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>
#include <util/delay.h>

#define BIT(x) (1<<(x))	

void wait(int);

int main (void)
{
	DDRC = 0b0000000;	//Port C is input
	DDRD = 0b11111111;	//Port D is output
	PORTD = 0b00000000;
	board_init();

	while (1)
	{
		if((PINC) & BIT(0))		//check if PIN C Button 0 is pressed
		{
			PORTD ^= BIT(7);	//toggle Port D led 7
			wait(750); 
		}
		else
			PORTD = 0b00000000; //set leds off
	}
	return 1;

}

void wait(int milliseconds){
	for(int i = 0; i<milliseconds; i++)
		_delay_ms(1);
}
