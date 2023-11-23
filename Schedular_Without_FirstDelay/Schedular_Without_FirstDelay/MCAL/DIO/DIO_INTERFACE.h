/*
 * DIO.h
 *
 * Created: 10/20/2023 10:15:13 AM
 *  Author: MERNA
 */ 


#ifndef DIO_H_
#define DIO_H_

/******************************** Includes ***************************************/
#include "../../UTIL/STD_TYPES.h"
#include "../../UTIL/BIT_MATH.h"
#include "DIO_TYPES.h"
#include "DIO_REGISTER.h"


/******************************** Prototypes ***************************************/
void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level);

Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId);

Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId);

void Dio_WritePort(Dio_PortType PortId,Dio_PortLevelType Level);

Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId);

#endif /* DIO_H_ */