#include <asf.h>

//initialize ADC: 10 bits, free running, single ended, continuous mode
void adcInit(){

	//channel 1 at PF1
	ADMUX = 0b01100001;

	//free running, division by 64
	ADCSRA = 0b11100110;
}


int main (void)
{
	board_init();

	//init adc

	
}
