/*
 * TMR0_PROGRAM.c
 *
 * Created: 10/23/2023 11:42:33 AM
 *  Author: MERNA
 */ 

#include "TMR0_REGISTER.h"
#include "TMR0_INTERFACE.h"
#include "TMR0_CONFIG.h"
#include "TMR0_PRIVATE.h"

static void (*Priv_vSetCallBack_OVF) (void) = NULL;
static void (*Priv_vSetCallBack_COMP)(void) = NULL;

volatile static u16 Priv_CtcCounter;
/*************************************************************************************************/
void TMR0_vInit(void)
{
	/******************* Normal Mode *******************/
	#if TMR0_MODE == TMR0_NORMAL_MODE
	// Set Normal Mode: WGM01:0 = 00
	CLR_BIT(TCCR0,WGM00);
	CLR_BIT(TCCR0,WGM01);
	
	// Enable Overflow Interrupt
	SET_BIT(TIMSK,TOIE0);
	
	
	/******************* CTC Mode *******************/
	#elif TMR0_MODE == TMR0_CTC_MODE
	// Set CTC Mode: WGM01:0 = 10
	CLR_BIT(TCCR0,WGM00);
	SET_BIT(TCCR0,WGM01);
	
	// Enable Compare Match Interrupt
	SET_BIT(TIMSK,OCIE0);
	
	
	/******************* Fast PWM Mode *******************/
	// Set Fast PWM Mode: WGM01:0 = 11
	#elif TMR0_MODE == TMR0_FAST_PWM_MODE
	SET_BIT(TCCR0,WGM00);
	SET_BIT(TCCR0,WGM01);
	
	//Set OC0 on compare match, clear OC0 at BOTTOM
	#if TMR0_PWM_MODE == TMR0_PWM_INVERTING
	SET_BIT(TCCR0,COM00);
	SET_BIT(TCCR0,COM01);
	
	//Clear OC0 on compare match, set OC0 at BOTTOM
	#elif TMR0_PWM_MODE == TMR0_PWM_NONINVERTING 
	CLR_BIT(TCCR0,COM00);
	SET_BIT(TCCR0,COM01);
	
	#endif
	
	
	/******************* PWM, Phase Correct Mode *******************/
	// Set Phase Correct Mode: WGM01:0 = 01
	#elif TMR0_MODE == TMR0_PHASE_CORRECT_MODE
	SET_BIT(TCCR0,WGM00);
	CLR_BIT(TCCR0,WGM01);
	
	//Set OC0 on compare match when up-counting. Clear OC0 on compare match when down-counting
	#if TMR0_PWM_MODE == TMR0_PWM_INVERTING
	SET_BIT(TCCR0,COM00);
	SET_BIT(TCCR0,COM01);
	
	//Clear OC0 on compare match when up-counting. Set OC0 on compare match when down-counting.
	#elif TMR0_PWM_MODE == TMR0_PWM_NONINVERTING
	CLR_BIT(TCCR0,COM00);
	SET_BIT(TCCR0,COM01);
	
	#endif
	/*****************************************/
	#endif
	
}

/*************************************************************************************************/
void TMR0_vStart(void)
{
	//CS02:0 = 001
	#if TMR0_PRESCALAR == TMR0_PRESCALAR_1
	SET_BIT(TCCR0,CS00);
	CLR_BIT(TCCR0,CS01);
	CLR_BIT(TCCR0,CS02);
	
	//CS02:0 = 010
	#elif TMR0_PRESCALAR == TMR0_PRESCALAR_8
	CLR_BIT(TCCR0,CS00);
	SET_BIT(TCCR0,CS01);
	CLR_BIT(TCCR0,CS02);
	
	//CS02:0 = 011
	#elif TMR0_PRESCALAR == TMR0_PRESCALAR_64
	SET_BIT(TCCR0,CS00);
	SET_BIT(TCCR0,CS01);
	CLR_BIT(TCCR0,CS02);
	
	//CS02:0 = 100
	#elif TMR0_PRESCALAR == TMR0_PRESCALAR_256
	CLR_BIT(TCCR0,CS00);
	CLR_BIT(TCCR0,CS01);
	SET_BIT(TCCR0,CS02);
	
	//CS02:0 = 101
	#elif TMR0_PRESCALAR == TMR0_PRESCALAR_1024
	SET_BIT(TCCR0,CS00);
	CLR_BIT(TCCR0,CS01);
	SET_BIT(TCCR0,CS02);
	
	#endif
	
}
/*************************************************************************************************/

void TMR0_vStop(void)
{
	//CS02:0 = 000, No clock source (Timer/Counter stopped).
	TCCR0 &= ~(0x07);
}
/*************************************************************************************************/

void TMR0_vSetDutyCycle_PWM(u8 Copy_u8DutyCycle)
{
	if(Copy_u8DutyCycle <= 100)
	{
		// Fast PWM Mode
		#if TMR0_MODE == TMR0_FAST_PWM_MODE
		
		//Inverting mode, Set OC0 on compare match, clear OC0 at BOTTOM
		#if TMR0_PWM_MODE == TMR0_PWM_INVERTING
		Copy_u8DutyCycle = 100 - Copy_u8DutyCycle;
		OCR0 = ((u16)(Copy_u8DutyCycle*256)/100)-1;
		
		//Non Inverting mode, Clear OC0 on compare match, set OC0 at BOTTOM
		#elif TMR0_PWM_MODE == TMR0_PWM_NONINVERTING
		OCR0 = ((u16)(Copy_u8DutyCycle*256)/100)-1;
		
		#endif
		
		// Phase Correct Mode
		#elif TMR0_MODE == TMR0_PHASE_CORRECT_MODE
		
		//Inverting Mode, Set OC0 on compare match when up-counting. Clear OC0 on compare match when down-counting.

		#if TMR0_PWM_MODE == TMR0_PWM_INVERTING
		Copy_u8DutyCycle = 100 - Copy_u8DutyCycle;
		OCR0 = ((u16)(Copy_u8DutyCycle*255)/100)-1;
		
		//Non Inverting Mode, Clear OC0 on compare match when up-counting. Set OC0 on compare match when down-counting.
		#elif TMR0_PWM_MODE == TMR0_PWM_NONINVERTING
		OCR0 = ((u16)(Copy_u8DutyCycle*255)/100)-1;
		
		#endif
		
		#endif
	}
}
/*************************************************************************************************/

void TMR0_vSetCompareMatchValue(u8 Copy_u8OCRValue)
{
	OCR0 = Copy_u8OCRValue;
}
/*************************************************************************************************/

void TMR0_vSetDelay_ms_UsingCTC(u16 Copy_u16Delay_ms)
{
	#if TMR0_PRESCALAR == TMR0_PRESCALAR_1
	//under condition -> tick time = 0.0625 uSec. 
	OCR0 = 249 ;
	Priv_CtcCounter = Copy_u16Delay_ms*64;
	
	#elif TMR0_PRESCALAR == TMR0_PRESCALAR_8
	//under condition -> tick time = 0.5 uSec. 
	OCR0 = 249 ;
	Priv_CtcCounter = Copy_u16Delay_ms*8;
	
	#elif TMR0_PRESCALAR == TMR0_PRESCALAR_64
	//under condition -> tick time = 4 uSec. 
	OCR0 = 249 ;
	Priv_CtcCounter = Copy_u16Delay_ms;
	
	#elif TMR0_PRESCALAR == TMR0_PRESCALAR_256
	
	#elif TMR0_PRESCALAR == TMR0_PRESCALAR_1024
	
	#endif
	
	
}
/*************************************************************************************************/

void TMR0_vSetCallBack_OVF(void (*ptr)(void))
{
	Priv_vSetCallBack_OVF = ptr;
}
/*************************************************************************************************/

void TMR0_vSetCallBack_COMP(void (*ptr)(void))
{
	Priv_vSetCallBack_COMP = ptr;
}
/*************************************************************************************************/

void __vector_11(void) __attribute__((signal));
void __vector_11(void)
{
	static u16 Local_u16OVFCounter = 0;
	Local_u16OVFCounter++;
	if(Local_u16OVFCounter == TMR0_OVF_COUNTER)
	{
		TCNT0 = TMR0_PRELOAD_VALUE;
		Local_u16OVFCounter = 0;
		if(Priv_vSetCallBack_OVF != NULL)
		{
			Priv_vSetCallBack_OVF();	//call the action
		}
	}
}

/*************************************************************************************************/
void __vector_10(void) __attribute__((signal));
void __vector_10(void)
{
	static u16 Local_u16COMPCounter = 0;
	Local_u16COMPCounter++;
	if(Local_u16COMPCounter == Priv_CtcCounter)
	{
		Local_u16COMPCounter = 0;
		if(Priv_vSetCallBack_COMP != NULL)
		{
			Priv_vSetCallBack_COMP();	//call the action
		}
	}
}

/*************************************************************************************************/
