/*
 * DIO.c
 *
 * Created: 10/20/2023 10:16:06 AM
 *  Author: MERNA
 */ 
#include "DIO_INTERFACE.h"
/******************************************************************************************/
void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level){	switch(ChannelId/8)	{		/* PortA */		case 0:		if(Level == 1){			SET_BIT(PORTA,ChannelId);		}else {			CLR_BIT(PORTA,ChannelId);		}		break;				/* PortB */		case 1:		if(Level == 1){			SET_BIT(PORTB,ChannelId%8);		}else {			CLR_BIT(PORTB,ChannelId%8);		}		break;				/* PortC */		case 2:		if(Level == 1){			SET_BIT(PORTC,ChannelId%8);		}else {			CLR_BIT(PORTC,ChannelId%8);		}		break;				/* PortD */		case 3:		if(Level == 1){			SET_BIT(PORTD,ChannelId%8);		}else {			CLR_BIT(PORTD,ChannelId%8);		}		break;				default:		break;	}}/******************************************************************************************/
Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId){	/*volatile u8* PINs[4]={0x39,0x36,0x33,0x30};	Dio_LevelType Ret = GET_BIT(*(volatile u8*)PINs[ChannelId/8],ChannelId%8);	return Ret;*/	Dio_LevelType Ret=0;	switch(ChannelId/8)	{		case Dio_PORTA:		Ret = GET_BIT(PINA,ChannelId);		break;				case Dio_PORTB:		Ret = GET_BIT(PINB,ChannelId%8);		break;				case Dio_PORTC:		Ret = GET_BIT(PINC,ChannelId%8);		break;				case Dio_PORTD:		Ret = GET_BIT(PIND,ChannelId%8);		break;				default:		break;	}	return Ret;}/*******************************************************************************************/
Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId){	Dio_PortLevelType Ret;	switch(PortId)	{		case Dio_PORTA:			Ret = PINA;			break;				case Dio_PORTB:			Ret = PINB;			break;					case Dio_PORTC:			Ret = PINC;			break;					case Dio_PORTD:			Ret = PIND;			break;					default:			break;	}}/*******************************************************************************************/
void Dio_WritePort(Dio_PortType PortId,Dio_PortLevelType Level){	switch(PortId)	{		case Dio_PORTA:		PORTA = Level;		break;				case Dio_PORTB:		PORTB = Level;		break;				case Dio_PORTC:		PORTC = Level;		break;				case Dio_PORTD:		PORTD = Level;		break;				default:		break;	}}
/*******************************************************************************************/
Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId){	Dio_LevelType Ret=0;	switch(ChannelId/8)	{		case Dio_PORTA:			TOG_BIT(PORTA,ChannelId);			Ret = GET_BIT(PORTA,ChannelId);			break;				case Dio_PORTB:			TOG_BIT(PORTB,ChannelId%8);			Ret = GET_BIT(PORTB,ChannelId%8);			break;				case Dio_PORTC:			TOG_BIT(PORTC,ChannelId%8);			Ret = GET_BIT(PORTC,ChannelId%8);			break;				case Dio_PORTD:			TOG_BIT(PORTD,ChannelId%8);			Ret = GET_BIT(PORTD,ChannelId%8);			break;				default:			break;	}	return Ret;}
/*******************************************************************************************/
