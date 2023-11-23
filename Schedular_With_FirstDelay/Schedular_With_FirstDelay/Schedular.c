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

/****************************************************************************/
void TMR0_ISR(void)
{
	Schedular();
}
/******************************************************************************/
/* 2D array to handle tasks with the same priority */
Task_t Task_arr[MAX_NUMBER_OF_TASKS];
u8 Number_of_Tasks ;


/******************************************************************************/
BaseType_t Create_Task(void (*ptr)(void),u16 priodicity,u16 FirstDelay)
{
	if(ptr != NULL)
	{
		Task_arr[Number_of_Tasks].func = ptr;
		Task_arr[Number_of_Tasks].Periodicity = priodicity;
		Task_arr[Number_of_Tasks].state = Ready;
		Task_arr[Number_of_Tasks].First_Delay = FirstDelay;
		Number_of_Tasks++;
		return pdTRUE;	
	}
	return pdFALSE;
}

/******************************************************************************/
BaseType_t Task_Delete(void(*ptr)(void))
{
	u8 i;
	for(i=0 ; i<MAX_NUMBER_OF_TASKS ; i++)
	{
		if(Task_arr[i].func == ptr)
		{
			Task_arr[i].state = Dormant;
			Task_arr[i].func = NULL;
			return pdTRUE;
		}
	}
	return pdFALSE;
}

/******************************************************************************/
void Schedular(void)
{
	static u32 counter = 0;
	u8 i;
	for(i=0 ; i<Number_of_Tasks ; i++)
	{
		if(Task_arr[i].func != NULL)
		{
			if(Task_arr[i].First_Delay == 0)
			{
				Task_arr[i].func();
				Task_arr[i].First_Delay = Task_arr[i].Periodicity-1;
			}
			else
			{
				Task_arr[i].First_Delay--;
			}
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
}

/******************************************************************************/
