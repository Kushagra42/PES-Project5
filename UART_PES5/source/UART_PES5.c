
/*
 * Created By : Vaidehi Salway & Kushagra Pandey
 * Date : 04/11/2019
 * TMP102 interfaced to KL25Z freedom board Using I2C
 * main.c
 *
 *
 */
#include "Unit_Testing.h"
#include "UART.h"

//echo mode code
#ifdef Echo_Mode
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "Logger.h"
#include "LED_Blink.h"

int8_t RX_Interrupt_Flag=0;
int8_t TX_Interrupt_Flag=0;

//unit testing fucntion calls
#ifdef Unit_Test
	Test_Data_Access();
	Wrap_Remove();
	Wrap_Add();
	Buffer_OverFill();
	Buffer_OverEmpty();
	Buffer_Destroy();
#endif


int main()
{

	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
	/* Init FSL debug console. */
	BOARD_InitDebugConsole();
	BOARD_InitPins();
	BOARD_BootClockRUN();
//init UART with a baudrate
	Init_UART0(115200);

	//initialize all the LEDS
	RED_LED_INIT();
	BLUE_LED_INIT();
	GREEN_LED_INIT();


	BLUE_LED_ON();
	Delay_Time(1000);
	BLUE_LED_OFF();
	Delay_Time(200);

	//code block for the interrupt mode
#if USE_UART_INTERRUPTS==0 // Polling version of code

	rx_cb=malloc(LENGTH*sizeof(Buffer_Parameters));
	Init_Buffer(rx_cb,LENGTH);

	while (1)
	{

		//Poling_Function();
		int8_t ch;
		while (!(UART0->S1 & UART0_S1_RDRF_MASK))
			;
		ch = UART0->D;
		Echo(ch);
	}


//code block for the Polling mode
#elif USE_UART_INTERRUPTS==1 // Interrupt version of code

	tx_cb=malloc(LENGTH*sizeof(Buffer_Parameters));
	Init_Buffer(tx_cb,LENGTH);
	int8_t ch;

	while (1)
	{

 		UART0->C2 &= ~(UART0_C2_TIE(1));

		if(RX_Interrupt_Flag==1)
		{
			ch = UART0->D;
			RX_Interrupt_Flag=0;
			Echo(ch);

		}

		//enable TX
		if (!(UART0->C2 & UART0_C2_TIE_MASK))
		{
			UART0->C2 |= UART0_C2_TIE(1);
		}

	}

#endif

	return 0;

}
#endif

//Application mode code
#ifdef Application_Mode

#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "Logger.h"
#include "Delay_Function.h"
#include "LED_Blink.h"

int8_t RX_Interrupt_Flag=0;
int8_t TX_Interrupt_Flag=0;



int main()
{

	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
	/* Init FSL debug console. */
	BOARD_InitDebugConsole();
	BOARD_InitPins();
	BOARD_BootClockRUN();

	Init_UART0(115200);
	Init_Systick();

	//initialize all the LEDS
	RED_LED_INIT();
	BLUE_LED_INIT();
	GREEN_LED_INIT();


	BLUE_LED_ON();
	Delay_Time(200);
	BLUE_LED_OFF();
	Delay_Time(100);


//unitt test function calls
#ifdef Unit_Test
	Test_Data_Access();
	Wrap_Remove();
	Wrap_Add();
	Buffer_OverFill();
	Buffer_OverEmpty();
	Buffer_Destroy();
#endif

#if USE_UART_INTERRUPTS==0 // Polling version of code

	rx_cb=malloc(LENGTH*sizeof(Buffer_Parameters));
	Init_Buffer(rx_cb,LENGTH);

	Log_String(0,1,"POLLING_MODE");

	while (1)
	{
		Buffer_Display();

	}

#elif USE_UART_INTERRUPTS==1 // Interrupt version of code


	rx_cb=malloc(LENGTH*sizeof(Buffer_Parameters));
	Init_Buffer(rx_cb,LENGTH);

	Log_String(0,1,"INTERRUPT_MODE");
	while (1)
	{
		START_CRITICAL();

 		//disabling transmitter
		UART0->C2 &= ~(UART0_C2_TIE(1));

		if(RX_Interrupt_Flag==1)
		{
			Buffer_Display();
			RX_Interrupt_Flag=0;
		}

		//enable TX
		if (!(UART0->C2 & UART0_C2_TIE_MASK))
		{
			UART0->C2 |= UART0_C2_TIE(1);
		}
		END_CRITICAL();
	}

#endif

	return 0;
}
#endif
