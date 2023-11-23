/*
 * LCD.c
 *
 * Created: 10/21/2023 2:10:12 PM
 *  Author: MERNA
 */ 
#include "LCD_INTERFACE.h"
#include "LCD_CONFIG.h"

void LCD_Init(void)
{
	_delay_ms(150);
	LCD_SendCMD(RETURN_HOME);
	_delay_ms(10);
	LCD_SendCMD(FOUR_BIT);
	_delay_ms(1);
	LCD_SendCMD(DISPLAY_ON_CURSOR_ON);
	_delay_ms(1);
	LCD_SendCMD(CLR_SCREEN);
	_delay_ms(10);
	LCD_SendCMD(ENTRY_MODE);
	_delay_ms(1);
}

void LCD_SendCMD(u8 Command)
{
	Dio_WriteChannel(LCD_D4,GET_BIT(Command,4));
	Dio_WriteChannel(LCD_D5,GET_BIT(Command,5));
	Dio_WriteChannel(LCD_D6,GET_BIT(Command,6));
	Dio_WriteChannel(LCD_D7,GET_BIT(Command,7));
	Dio_WriteChannel(LCD_RS,STD_LOW);
	LCD_SendTrigger();
	Dio_WriteChannel(LCD_D4,GET_BIT(Command,0));
	Dio_WriteChannel(LCD_D5,GET_BIT(Command,1));
	Dio_WriteChannel(LCD_D6,GET_BIT(Command,2));
	Dio_WriteChannel(LCD_D7,GET_BIT(Command,3));
	Dio_WriteChannel(LCD_RS,STD_LOW);
	LCD_SendTrigger();
}


void LCD_SendData(u8 Data)
{
	Dio_WriteChannel(LCD_D4,GET_BIT(Data,4));
	Dio_WriteChannel(LCD_D5,GET_BIT(Data,5));
	Dio_WriteChannel(LCD_D6,GET_BIT(Data,6));
	Dio_WriteChannel(LCD_D7,GET_BIT(Data,7));
	Dio_WriteChannel(LCD_RS,STD_HIGH);
	LCD_SendTrigger();
	Dio_WriteChannel(LCD_D4,GET_BIT(Data,0));
	Dio_WriteChannel(LCD_D5,GET_BIT(Data,1));
	Dio_WriteChannel(LCD_D6,GET_BIT(Data,2));
	Dio_WriteChannel(LCD_D7,GET_BIT(Data,3));
	Dio_WriteChannel(LCD_RS,STD_HIGH);
	LCD_SendTrigger();
}

static void LCD_SendTrigger(void)
{
	Dio_WriteChannel(LCD_EN,STD_HIGH);
	_delay_ms(2);
	Dio_WriteChannel(LCD_EN,STD_LOW);
	_delay_ms(2);
}

void LCD_SendString(char* String)
{
	while(*String != '\0')
	{
		LCD_SendData(*String);
		String++;
	}
}

void LCD_Send_XY(u8 X,u8 Y,char* String)
{
	u8 LOC;
	if(X==1 || X>4)
	{
		LOC = ROW1_START+Y-1;
	}
	else if(X==2)
	{
		LOC = ROW1_START+(0x40)+Y-1;	
	}
	else if(X==3)
	{
		LOC = ROW1_START+(0x14)+Y-1;
	}
	else
	{
		LOC = ROW1_START+(0x54)+Y-1;
	}
	LCD_SendCMD(LOC);
	LCD_SendString(String);
}


void LCD_vSendNumber(u16 Copy_u16Number)
{
	u8 LOC_Arr[10];
	u8 LOC_i=0;
	if(Copy_u16Number == 0)
	{
		LCD_SendData('0');
	}
	else
	{
		while(Copy_u16Number != 0)
		{
			LOC_Arr[LOC_i] = Copy_u16Number%10;
			Copy_u16Number /= 10;
			LOC_i++;
		}
		while(LOC_i>0)
		{
			LOC_i--;
			LCD_SendData(LOC_Arr[LOC_i]+48);
		}
	}
}