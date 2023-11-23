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
Task_t Task_arr[MAX_NUMBER_OF_PRIORITY][MAX_NUMBER_OF_SAME_PRIORITY];
u8 Number_of_Tasks ;

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
				if(Task_arr[i][j].First_delay == 0)
				{
					Task_arr[i][j].func();
					Task_arr[i][j].First_delay = Task_arr[i][j].Periodicity-1;
					break;
				}
				else
				{
					Task_arr[i][j].First_delay --;
				}
			}
		}
		if(j != MAX_NUMBER_OF_SAME_PRIORITY) //A task has been chosen 
		{
			break;
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
