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
	Create_Task(Task1,100);
	Create_Task(Task2,500);
	Create_Task(Task3,1000);
	
	
	Start_System();
	
    while(1)
    {
				
    }
}