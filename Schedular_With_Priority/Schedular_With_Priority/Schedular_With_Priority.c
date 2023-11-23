/*
 * rtos.c
 *
 * Created: 11/17/2023 1:00:05 PM
 *  Author: MERNA
 */ 

#define F_CPU			16000000UL
#include "util/delay.h"

#include "UTIL/STD_TYPES.h"
#include "Schedular.h"
#include "MCAL/DIO/DIO_INTERFACE.h"
#include "MCAL/PORT/PORT_INTERFACE.h"
#include "MCAL/GIE/GIE_INTERFACE.h"



/****************************************************************************/
void Task1(void)
{
	Dio_FlipChannel(PA_4);
}

/****************************************************************************/
void Task2(void)
{	
	Dio_FlipChannel(PA_5);
}
/****************************************************************************/
void Task3(void)
{
	Dio_FlipChannel(PA_6);	
}

/****************************************************************************/
int main(void)
{
	Port_Init();
	Dio_WriteChannel(PA_4,1);
	/* Three Tasks with the same priority (1)
	Task1: has periodicity = 500 tick , First Delay = 0
	Task2: has periodicity = 1000 tick , First Delay = 1000
	Task3: has periodicity = 100 tick , First Delay = 2000
	*/
	Create_Task(Task1,1,500,0);
	Create_Task(Task2,1,1000,1000);
	Create_Task(Task3,1,100,2000);
	
	Start_System();
	
    while(1)
    {
		
    }
}