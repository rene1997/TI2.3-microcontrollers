/*
 * IncFile1.h
 *
 * Created: 5-4-2016 10:26:21
 *  Author: rkeet
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_


#define BIT(x) (1<<(x))	

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

typedef enum {MENU, PLAYING, GAMEOVER} gameStatus; 

POSITION allPositions[64];
char stringline[16];

extern int snakelength;
extern int lastPressed;


//extern char MatrixText[3];

//functions:
void buttoninit(void);
void checkinput(void);
void changePosition(int, int);
void setLootPosition();
void addSmaleLength();
void checkColission();
int checkPositions(POSITION a, POSITION b);
void wait(int ms);



#endif /* INCFILE1_H_ */