/*
 * TMR0_REGISTER.h
 *
 * Created: 10/23/2023 11:44:28 AM
 *  Author: MERNA
 */ 


#ifndef TMR0_REGISTER_H_
#define TMR0_REGISTER_H_

#define TCCR0	*((volatile u8*)(0x53))
#define TCNT0	*((volatile u8*)(0x52))
#define TIMSK	*((volatile u8*)(0x59))
#define TIFR	*((volatile u8*)(0x58))
#define OCR0	*((volatile u8*)(0x5C))

/* TCCR0 Register */
#define CS00	0
#define CS01	1
#define CS02	2
#define WGM01	3
#define COM00	4
#define COM01	5
#define WGM00	6
#define FOC0	7

/* TIMSK Register */
#define TOIE0	0
#define OCIE0	1

/* TIFR Register */
#define TOV0	0
#define OCF0	1


#endif /* TMR0_REGISTER_H_ */