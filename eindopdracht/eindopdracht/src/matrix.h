/*
 * matrix.h
 *
 * Created: 7-4-2016 16:51:30
 *  Author: rene
 */ 


#ifndef MATRIX_H_
#define MATRIX_H_


extern int yPositions[8];
extern int xPositions[8];

extern void initMatrix(void);
extern void twi_position(POSITION position);
extern void twi_init(void);
extern void twi_start(void);
extern void twi_stop(void);
extern void twi_clear(void);
extern void twi_fill(void);
extern void twi_write(char text[]);
extern void twi_tx(unsigned char);




#endif /* MATRIX_H_ */