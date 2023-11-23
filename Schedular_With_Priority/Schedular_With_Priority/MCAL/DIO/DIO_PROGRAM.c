/*
 * DIO.c
 *
 * Created: 10/20/2023 10:16:06 AM
 *  Author: MERNA
 */ 
#include "DIO_INTERFACE.h"
/******************************************************************************************/
void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level)
Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId)
Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId)
void Dio_WritePort(Dio_PortType PortId,Dio_PortLevelType Level)
/*******************************************************************************************/
Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId)
/*******************************************************************************************/