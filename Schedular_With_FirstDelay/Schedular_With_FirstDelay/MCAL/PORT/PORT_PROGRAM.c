/*
 * PORT.c
 *
 * Created: 10/20/2023 2:32:18 PM
 *  Author: MERNA
 */ 
#include "PORT_INTERFACE.h"
#include "PORT_CONFIG.h"
#include "PORT_TYPES.h"

extern Port_ConfigType Port_cngs[MAX_NUMBER_OF_PINS];

/*******************************************************************************************/
void Port_Init(void)
{
	u8 i=0;
	for(i=0 ; i<MAX_NUMBER_OF_PINS ; i++)
	{
		if(Port_cngs[i].Port==-1)
		{
			break;
		}
		switch(Port_cngs[i].Port)
		{
			case Dio_PORTA:
				if(Port_cngs[i].Dir==PORT_PIN_OUT){
					SET_BIT(DDRA,Port_cngs[i].Pin);
				}else {
					CLR_BIT(DDRA,Port_cngs[i].Pin);
				}
				break;
				
			case Dio_PORTB:
				if(Port_cngs[i].Dir==PORT_PIN_OUT){
					SET_BIT(DDRB,Port_cngs[i].Pin);
				}else {
					CLR_BIT(DDRB,Port_cngs[i].Pin);
				}
				break;
				
			case Dio_PORTC:
				if(Port_cngs[i].Dir==PORT_PIN_OUT){
					SET_BIT(DDRC,Port_cngs[i].Pin);
				}else {
					CLR_BIT(DDRC,Port_cngs[i].Pin);
				}
				break;
				
			case Dio_PORTD:
				if(Port_cngs[i].Dir==PORT_PIN_OUT){
					SET_BIT(DDRD,Port_cngs[i].Pin);
				}else {
					CLR_BIT(DDRD,Port_cngs[i].Pin);
				}
				break;
				
			default:
				break;
		}
	}
}
/*******************************************************************************************/
