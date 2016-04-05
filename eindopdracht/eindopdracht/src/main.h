/*
 * IncFile1.h
 *
 * Created: 5-4-2016 10:26:21
 *  Author: rkeet
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_

#define UP		0
#define RIGHT	1
#define DOWN	2
#define LEFT	3

typedef struct {
	unsigned char x;
	unsigned char y;
}POSITION;

//functions:
void buttoninit(void);
void checkinput(void);
void changePosition(int);
void twi_init(void);
void twi_start(void);
void twi_stop(void);
void twi_clear(void);
void twi_fill(void);
void twi_tx(unsigned char);
void wait(int ms);



#endif /* INCFILE1_H_ */