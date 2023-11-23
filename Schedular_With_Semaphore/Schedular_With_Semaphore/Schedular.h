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
typedef struct{
	u8 create;
	u8 state;
	s16 TimeOut;
}semaphore_t;

/***********************************************************************************/

#define TICK_TIME							1
#define MAX_NUMBER_OF_PRIORITY				10
#define MAX_NUMBER_OF_SAME_PRIORITY			3


#define MAX_SEMAPHORE_NUMBER				3

#define SEMAPHORE_CREATE_YES				1
#define SEMAPHORE_CREATE_NO					2

#define SEMAPHORE_USED						1
#define SEMAPHORE_NOT_USED					2

/**********************************************************************************/

BaseType_t Create_Task(void (*ptr)(void),u8 Priority,u16 priodicity,u16 First_d);

BaseType_t Task_Delete(void(*ptr)(void));

void Schedular(void);

void Start_System(void);


void Create_SemaphoreBinary(semaphore_t* semaphore);

BaseType_t Semaphore_Take(semaphore_t* semaphore,u16 TimeOut);

void Semaphore_Give(semaphore_t* semaphore);

void Semaphore_Delete(semaphore_t* semaphore);

#endif /* SCHEDULAR_H_ */