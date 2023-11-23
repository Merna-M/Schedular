/*
 * GIE.c
 *
 * Created: 10/22/2023 1:29:25 PM
 *  Author: MERNA
 */ 

#include "GIE_INTERFACE.h"
#include "GIE_REGISTER.h"

/********************************************************************************/
void GI_vEnable(void)
{
	SET_BIT(SREG,I_BIT);
}
/********************************************************************************/
void GI_vDisable(void)
{
	CLR_BIT(SREG,I_BIT);
}
/********************************************************************************/