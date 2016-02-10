/*
 * main.c
 *
 * Created: 10-2-2016 12:10:58
 *  Author: rene
 */ 
#include <asf.h>
#include <util/delay.h>
#include "main.h"



/**
 * \brief 
 * 
 * \param 
 * 
 * \return int
 */
int main (void)
{
	board_init();

}


void wait(int milliseconds){
	int i = 0;
	for(; i < milliseconds; i ++)
		_delay_ms(1);
}
