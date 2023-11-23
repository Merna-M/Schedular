/*
 * LCD.h
 *
 * Created: 10/21/2023 2:10:27 PM
 *  Author: MERNA
 */ 


#ifndef LCD_H_
#define LCD_H_

/* ################################# Includes ##################################*/
#define F_CPU	16000000UL
#include "util/delay.h"
#include "../../MCAL/DIO/DIO_INTERFACE.h"

/* ################################## Macros ####################################*/


/* Commands */
#define EIGHT_BIT			  0x38
#define FOUR_BIT			  0x28
#define CLR_SCREEN			  0x01
#define DISPLAY_ON_CURSOR_ON  0x0E
#define DISPLAY_ON_CURSOR_OFF 0x0C
#define ENTRY_MODE			  0x06
#define RETURN_HOME			  0x02
#define ROW1_START			  0x80
#define ROW2_START			  0xC0 //0x80 + 0x40


void LCD_Init(void);

static void LCD_SendTrigger(void);

void LCD_SendCMD(u8 Command);

void LCD_SendData(u8 Data);

void LCD_SendString(char* String);

void LCD_Send_XY(u8 X,u8 Y,char* String);

void LCD_vSendNumber(u16 Copy_u16Number);

#endif /* LCD_H_ */