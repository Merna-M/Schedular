/*
 * Schedular.h
 *
 * Created: 11/17/2023 1:02:06 PM
 *  Author: MERNA
 */ 


#ifndef SCHEDULAR_H_
#define SCHEDULAR_H_

#include "UTIL/STD_TYPES.h"
/**********************************************************************************/
typedef enum{
	Dormant,
	Ready,
	Running,
	Waiting
}state_t;

/**********************************************************************************/
typedef struct{
	u16 Periodicity;
	u16 First_delay;
	state_t state;
	void (*func)(void);
}Task_t;
/***********************************************************************************/
typedef enum{
	pdTRUE,
	pdFALSE
}BaseType_t;
/***********************************************************************************/

#define TICK_TIME							1
#define MAX_NUMBER_OF_PRIORITY				10
#define MAX_NUMBER_OF_SAME_PRIORITY			3

/**********************************************************************************/

BaseType_t Create_Task(void (*ptr)(void),u8 Priority,u16 priodicity,u16 First_d);

BaseType_t Task_Delete(void(*ptr)(void));

void Schedular(void);

void Start_System(void);



#endif /* SCHEDULAR_H_ */