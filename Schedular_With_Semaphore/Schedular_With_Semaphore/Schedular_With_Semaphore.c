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
#include "HAL/LCD/LCD_INTERFACE.h"

extern volatile u8 chosen_task;
extern volatile BaseType_t choose_Done;
extern Task_t Task_arr[MAX_NUMBER_OF_PRIORITY][MAX_NUMBER_OF_SAME_PRIORITY];

semaphore_t sema_task;

/****************************************************************************/
void Task1(void)
{
	LCD_SendCMD(CLR_SCREEN);
	LCD_Send_XY(1,1,"Ask For Semaphore");
	while(pdFALSE == Semaphore_Take(&sema_task,100));
	Dio_FlipChannel(PA_4);

}

/****************************************************************************/
void Task2(void)
{	
	Dio_FlipChannel(PA_5);
	LCD_Send_XY(2,1,"Give Semaphore");
	Semaphore_Give(&sema_task);
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
	LCD_Init();
	/* Three Tasks with the same priority (1)
	Task1: has periodicity = 2000 tick , First Delay = 0 , asks for semaphore
	Task2: has periodicity = 1000 tick , First Delay = 500 , gives semaphore
	Task3: has periodicity = 100 tick , First Delay = 2000
	*/
	Create_Task(Task1,0,2000,0);
	Create_Task(Task2,1,1000,500);
	Create_Task(Task3,2,100,2000);
	
	Create_SemaphoreBinary(&sema_task);

	Start_System();
	u8 row,col;
    while(1)
    {
		
    }
}