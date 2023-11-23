/*
 * PORT_config.h
 *
 * Created: 10/20/2023 3:10:04 PM
 *  Author: K I N G
 */ 


#ifndef PORT_CONFIG_H_
#define PORT_CONFIG_H_

#define MAX_NUMBER_OF_PINS		32

/********************************************************************************/
typedef struct{
	Dio_PortType Port;
	Port_PinType Pin;
	Port_PinDirectionType Dir;
}Port_ConfigType;

#endif /* PORT_CONFIG_H_ */