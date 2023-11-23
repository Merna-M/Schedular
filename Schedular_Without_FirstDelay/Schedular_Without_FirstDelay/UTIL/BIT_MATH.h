/* 
Name    : MERNA
Date    : 17/10/2023
Version : 1.0
SWC     : BIT_MATHs
*/

#ifndef _BIT_MATH_H
#define _BIT_MATH_H

#define SET_BIT(REG,BIT)		(REG |= (1<<BIT))
#define CLR_BIT(REG,BIT)		(REG &=~(1<<BIT))
#define TOG_BIT(REG,BIT)		(REG ^= (1<<BIT))
#define GET_BIT(REG,BIT)		((REG >> BIT)&1)


#endif