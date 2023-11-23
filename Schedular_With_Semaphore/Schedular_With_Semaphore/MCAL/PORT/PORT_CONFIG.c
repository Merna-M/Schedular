/*
 * PORT_config.c
 *
 * Created: 10/21/2023 9:52:22 AM
 *  Author: MERNA
 */ 

#include "PORT_INTERFACE.h"
#include "PORT_CONFIG.h"

Port_ConfigType Port_cngs[]={

//led
{Dio_PORTA,DIO_Pin4,PORT_PIN_OUT},
{Dio_PORTA,DIO_Pin5,PORT_PIN_OUT},
{Dio_PORTA,DIO_Pin6,PORT_PIN_OUT},
	
{Dio_PORTA,DIO_Pin2,PORT_PIN_OUT},
{Dio_PORTA,DIO_Pin3,PORT_PIN_OUT},
{Dio_PORTB,DIO_Pin0,PORT_PIN_OUT},
{Dio_PORTB,DIO_Pin1,PORT_PIN_OUT},
{Dio_PORTB,DIO_Pin2,PORT_PIN_OUT},
{Dio_PORTB,DIO_Pin4,PORT_PIN_OUT},
{-1,-1,-1}
};
