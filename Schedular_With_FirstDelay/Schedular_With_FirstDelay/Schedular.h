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
	u16 First_Delay;
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

#define MAX_NUMBER_OF_TASKS					10


/**********************************************************************************/

BaseType_t Create_Task(void (*ptr)(void),u16 priodicity,u16 FirstDelay);

u8 Task_Delete(void(*ptr)(void));

void Schedular(void);

void Start_System(void);

#endif /* SCHEDULAR_H_ */