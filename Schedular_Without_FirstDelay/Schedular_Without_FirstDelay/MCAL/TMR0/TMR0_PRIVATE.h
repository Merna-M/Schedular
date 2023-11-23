/*
 * TMR0_PRIVATE.h
 *
 * Created: 10/23/2023 11:44:59 AM
 *  Author: MERNA
 */ 


#ifndef TMR0_PRIVATE_H_
#define TMR0_PRIVATE_H_

/** Timer0 Modes **/
#define TMR0_NORMAL_MODE				1
#define TMR0_CTC_MODE					2
#define TMR0_FAST_PWM_MODE				3
#define TMR0_PHASE_CORRECT_MODE			4

/** Timer0 Prescalar Values **/
#define TMR0_PRESCALAR_1				1
#define TMR0_PRESCALAR_8				2
#define TMR0_PRESCALAR_64				3
#define TMR0_PRESCALAR_256				4
#define TMR0_PRESCALAR_1024				5

/** Timer0 PWM modes **/
#define TMR0_PWM_INVERTING				1
#define TMR0_PWM_NONINVERTING			2

#endif /* TMR0_PRIVATE_H_ */