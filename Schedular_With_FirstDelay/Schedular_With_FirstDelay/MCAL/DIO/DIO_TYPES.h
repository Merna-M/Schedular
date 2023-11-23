#ifndef _DIO_TYPES_H
#define _DIO_TYPES_H

/********************************* Datatypes *************************************/
typedef enum{
	PA_0,
	PA_1,
	PA_2,
	PA_3,
	PA_4,
	PA_5,
	PA_6,
	PA_7,
	PB_0,
	PB_1,
	PB_2,
	PB_3,
	PB_4,
	PB_5,
	PB_6,
	PB_7,
	PC_0,
	PC_1,
	PC_2,
	PC_3,
	PC_4,
	PC_5,
	PC_6,
	PC_7,
	PD_0,
	PD_1,
	PD_2,
	PD_3,
	PD_4,
	PD_5,
	PD_6,
	PD_7
}Dio_ChannelType;
/********************************************************************************/
typedef enum{
	STD_LOW,
	STD_HIGH
}Dio_LevelType;
/********************************************************************************/
typedef enum{
	Dio_PORTA,
	Dio_PORTB,
	Dio_PORTC,
	Dio_PORTD
}Dio_PortType;
/********************************************************************************/
typedef u8 Dio_PortLevelType;
/********************************************************************************/


#endif