/*
 * TMR0_INTERFACE.h
 *
 * Created: 10/23/2023 11:43:40 AM
 *  Author: MERNA
 */ 


#ifndef TMR0_INTERFACE_H_
#define TMR0_INTERFACE_H_


/************************************ Includes ***************************************/
#include "../../UTIL/STD_TYPES.h"
#include "../../UTIL/BIT_MATH.h"


/************************************ Prototypes *************************************/

void TMR0_vInit(void);

void TMR0_vStart(void);

void TMR0_vStop(void);

void TMR0_vSetCompareMatchValue(u8 Copy_u8OCRValue);

void TMR0_vSetDutyCycle_PWM(u8 Copy_u8DutyCycle);

void TMR0_vSetCallBack_OVF(void (*ptr)(void));

void TMR0_vSetCallBack_COMP(void (*ptr)(void));

void TMR0_vSetDelay_ms_UsingCTC(u16 Copy_u16Delay_ms);


#endif /* TMR0_INTERFACE_H_ */