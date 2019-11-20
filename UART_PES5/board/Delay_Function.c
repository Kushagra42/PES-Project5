/*
 * @file Delay_Function.c
 * author: kushagra Pandey & Vaidehi Salway
 * Date:10/14/2019
 *
 * This .c file contains a function to generate a delay
 */

#include "Delay_Function.h"
#include "Logger.h"
#include "UART.h"

// Constant multiplier based on the clock frequency of frdm board
uint32_t cons_val=4000000;
uint32_t j=0;
extern uint32_t milli_sec_val;
int count=0;
int Timer=0;
/* This is a delay function with a parameter milli_sec_val
 * delay calculations are based on the clock frequency to
 * generate a delay equivalent to user input through delay function.
 */
void Delay_Time(uint32_t milli_sec_val)
{
	uint32_t Ticks_value= (cons_val * milli_sec_val)/(500);

	for( j=0;j<=Ticks_value;j++);

}


uint8_t TimeOut_Counter(uint8_t Time_out)
{
	uint8_t count1=0;
	for(count=0;count<(Time_out);count++)
	{
		count1=count1+1;
	}

return count1;

}

void Init_Systick(void)
{
SysTick->LOAD = (48000000L/100);
NVIC_SetPriority(SysTick_IRQn,3);
NVIC_EnableIRQ(SysTick_IRQn);
SysTick->VAL = 0;
SysTick->CTRL = SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
}

void SysTick_Handler()
{
	Timer++;
}

uint64_t Current_Timer()
{
return Timer;
}

void Time_Stamp()
{
	START_CRITICAL();
static char Clock[2048] = {0};
for (int i=0; i<2048;i++) Clock[i]= '\0';

uint64_t TENTHS_SEC = Current_Timer();

float Time_Div = TENTHS_SEC / 10;

uint64_t SECONDS = (uint64_t)(Time_Div)%60;
uint64_t MINUTES = (uint64_t)(Time_Div/60)%60;
uint64_t HOURS = (uint64_t)(Time_Div/3600)%60;


sprintf(Clock, "%02d:", HOURS);
Log_String(3,19,Clock);

sprintf(Clock, "%02d:", MINUTES);
Log_String(3,19,Clock);

sprintf(Clock, "%02d:", SECONDS);
Log_String(3,19,Clock);

sprintf(Clock, ".%01d\n\r", TENTHS_SEC%10);
Log_String(3,19,Clock);
END_CRITICAL();
}



