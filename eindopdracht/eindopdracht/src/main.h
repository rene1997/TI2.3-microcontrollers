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

#define LOOT	0
#define HEAD	1

typedef struct {
	unsigned char x;
	unsigned char y;
}POSITION;

int yPositions[8] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
int xPositions[8] = {0x00, 0x02, 0x04, 0x06, 0x08, 0x0A, 0x0C, 0x0E};
char scoreText[6] = "Score:"; 

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
void setLootPosition();
void wait(int ms);



#endif /* INCFILE1_H_ */