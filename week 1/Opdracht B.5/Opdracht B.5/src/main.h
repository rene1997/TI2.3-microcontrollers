/*
 * main.h
 *
 * Created: 10-2-2016 12:10:58
 *  Author: rene
 */ 

#include <util/delay.h>

#ifndef MAIN_H_
#define MAIN_H_


/**
 * \brief 
 * program waits for given amount of millisecond
 * make sure util/deley.h is included
 * 
 * \param int: amount of millisceconds programs wait
 * 
 * \return void
 */
void wait(int);


/**
 * \brief 
 * this method is called when board starts
 * 
 * \return int: never reached, dont ask why necessary;
 */
int main();


#endif /* MAIN_H_ */