/*
 * Schedular.c
 *
 * Created: 11/17/2023 1:01:45 PM
 *  Author: MERNA
 */ 
#include "UTIL/STD_TYPES.h"
#include "MCAL/GIE/GIE_INTERFACE.h"
#include "MCAL/TMR0/TMR0_INTERFACE.h"
#include "Schedular.h"


/* Semaphore array */
semaphore_t* sema_arr[MAX_SEMAPHORE_NUMBER];
u8 Number_of_Semaphores = 0;

/****************************************************************************/
void TMR0_ISR(void)
{
	Schedular();
}
/******************************************************************************/
/* 2D array to handle tasks with the same priority */
Task_t Task_arr[MAX_NUMBER_OF_PRIORITY][MAX_NUMBER_OF_SAME_PRIORITY];
u8 Number_of_Tasks ;

volatile u8 chosen_task = 255;
volatile BaseType_t choose_Done = pdFALSE;
/******************************************************************************/
BaseType_t Create_Task(void (*ptr)(void),u8 Priority,u16 priodicity,u16 First_d)
{
	for(u8 i=0 ; i<MAX_NUMBER_OF_SAME_PRIORITY ; i++)
	{
		if(Task_arr[Priority][i].func==NULL && ptr != NULL)
		{
			Task_arr[Priority][i].func = ptr;
			Task_arr[Priority][i].Periodicity = priodicity;
			Task_arr[Priority][i].First_delay = First_d;
			Task_arr[Priority][i].state = Ready;
			return pdTRUE;
		}
	}
	return pdFALSE;
}

/******************************************************************************/
BaseType_t Task_Delete(void(*ptr)(void))
{
	u8 i,j;
	for(i=0 ; i<MAX_NUMBER_OF_PRIORITY ; i++)
	{
		for(j=0 ; j<MAX_NUMBER_OF_SAME_PRIORITY ; j++)
		{
			if(Task_arr[i][j].func == ptr)
			{
				Task_arr[i][j].func = NULL;
				Task_arr[i][j].state = Dormant;
				return pdTRUE;
			}
		}
	}
	return pdFALSE;
}

/******************************************************************************/
void Schedular(void)
{
	static u32 counter = 0;
	u8 i,j;
	for(i=0 ; i<MAX_NUMBER_OF_PRIORITY ; i++)
	{
		for(j=0 ; j<MAX_NUMBER_OF_SAME_PRIORITY ; j++)
		{
			if(Task_arr[i][j].func != NULL)
			{
				if(Task_arr[i][j].First_delay == 0 && chosen_task == 255)
				{
					Task_arr[i][j].func();
					Task_arr[i][j].First_delay = Task_arr[i][j].Periodicity-1;
				}
				else if(Task_arr[i][j].First_delay != 0)
				{
					Task_arr[i][j].First_delay --;
				}
			}
		}
		
		if(i<Number_of_Semaphores && sema_arr[i]->TimeOut>0)
		{
			sema_arr[i]->TimeOut--;
		}
	}
	counter++;
}

/******************************************************************************/

void Start_System(void)
{
	GI_vEnable();
	TMR0_vInit();
	TMR0_vSetDelay_ms_UsingCTC(TICK_TIME);
	TMR0_vSetCallBack_COMP(TMR0_ISR);
	TMR0_vStart();
	choose_Done == pdFALSE;
}

/******************************************************************************/

/********************************* Semaphore *********************************/

void Create_SemaphoreBinary(semaphore_t* semaphore)
{
	semaphore->create = SEMAPHORE_CREATE_YES;
	semaphore->state = SEMAPHORE_NOT_USED;
	semaphore->TimeOut = 0;
	sema_arr[Number_of_Semaphores] = semaphore;
	Number_of_Semaphores++;
}

/******************************************************************************/

BaseType_t Semaphore_Take(semaphore_t* semaphore,u16 TimeOut)
{
	semaphore->TimeOut = TimeOut;
	while(semaphore->TimeOut > 0)
	{
		if(semaphore->state == SEMAPHORE_NOT_USED)
		{
			semaphore->state = SEMAPHORE_USED;
			semaphore->TimeOut = 0;
			return pdTRUE;
		}
	}
	return pdFALSE;
}

/******************************************************************************/

void Semaphore_Give(semaphore_t* semaphore)
{
	semaphore->state = SEMAPHORE_NOT_USED;
}

/******************************************************************************/
void Semaphore_Delete(semaphore_t* semaphore)
{
	semaphore->create = SEMAPHORE_CREATE_NO;
	semaphore->state = SEMAPHORE_NOT_USED;
	semaphore->TimeOut = 0;
}

/******************************************************************************/
