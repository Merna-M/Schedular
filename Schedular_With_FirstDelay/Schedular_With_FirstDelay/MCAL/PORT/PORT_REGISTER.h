#ifndef _PORT_REGISTER_H
#define _PORT_REGISTER_H



//Data Direction Registers
#define DDRA		*((volatile u8*)(0x3A))
#define DDRB		*((volatile u8*)(0x37))
#define DDRC		*((volatile u8*)(0x34))
#define DDRD		*((volatile u8*)(0x31))


#endif