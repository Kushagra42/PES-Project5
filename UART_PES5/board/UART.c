
/*
 * @file UART.c
 * author: kushagra Pandey & Vaidehi Salway
 * Date:11/18/2019
 */

#include "UART.h"
#include "Counting_Characters.h"
#include "LED_Blink.h"

	Buffer_Parameters* rx_cb=NULL;
	Buffer_Parameters* tx_cb=NULL;

	extern int8_t RX_Interrupt_Flag;
	extern int8_t TX_Interrupt_Flag;
	int8_t ch;

	int8_t full_flag=0;
	int8_t empty_flag=0;


	// Code listing 8.8, p. 231
	void Init_UART0(uint32_t baud_rate)
	{

		uint16_t sbr;
		uint16_t temp;

		// Enable clock gating for UART0 and Port A
		SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
		SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;

		// Make sure transmitter and receiver are disabled before init
		UART0->C2 &= ~UART0_C2_TE_MASK & ~UART0_C2_RE_MASK;

		// Set UART clock to 48 MHz clock
		SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);
		SIM->SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK;

		// Set pins to UART0 Rx and Tx
		PORTA->PCR[1] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2); // Rx
		PORTA->PCR[2] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2); // Tx

		// Set baud rate and oversampling ratio
		sbr = (uint16_t)(((SYS_CLOCK)/2)/(baud_rate * UART_OVERSAMPLE_RATE));
		UART0->BDH &= ~UART0_BDH_SBR_MASK;
		UART0->BDH |= UART0_BDH_SBR(sbr>>8);
		UART0->BDL = UART0_BDL_SBR(sbr);
		UART0->C4 |= UART0_C4_OSR(UART_OVERSAMPLE_RATE-1);

		// Disable interrupts for RX active edge and LIN break detect, select one stop bit
		UART0->BDH |= UART0_BDH_RXEDGIE(0) | UART0_BDH_SBNS(0) | UART0_BDH_LBKDIE(0);

		// Don't enable loopback mode, use 8 data bit mode, don't use parity
		UART0->C1 = UART0_C1_LOOPS(0) | UART0_C1_M(0) | UART0_C1_PE(0);
		// Don't invert transmit data, don't enable interrupts for errors
		UART0->C3 = UART0_C3_TXINV(0) | UART0_C3_ORIE(0)| UART0_C3_NEIE(0)
						| UART0_C3_FEIE(0) | UART0_C3_PEIE(0);

		// Clear error flags
		UART0->S1 = UART0_S1_OR(1) | UART0_S1_NF(1) | UART0_S1_FE(1) | UART0_S1_PF(1);

		// Try it a different way
		UART0->S1 |= UART0_S1_OR_MASK | UART0_S1_NF_MASK |
				UART0_S1_FE_MASK | UART0_S1_PF_MASK;

		// Send LSB first, do not invert received data
		UART0->S2 = UART0_S2_MSBF(0) | UART0_S2_RXINV(0);

	#if USE_UART_INTERRUPTS
		// Enable interrupts. Listing 8.11 on p. 234

		NVIC_SetPriority(UART0_IRQn, 2); // 0, 1, 2, or 3
		NVIC_ClearPendingIRQ(UART0_IRQn);
		NVIC_EnableIRQ(UART0_IRQn);

		// Enable receive interrupts but not transmit interrupts yet
		UART0->C2 |= UART_C2_RIE(1);
	#endif

		// Enable UART receiver and transmitter
		UART0->C2 |= UART0_C2_RE(1) | UART0_C2_TE(1);

		// Clear the UART RDRF flag
		temp = UART0->D;
		UART0->S1 &= ~UART0_S1_RDRF_MASK;

	}

	int8_t ch;

	// UART0 IRQ Handler. Listing 8.12 on p. 235
	void UART0_IRQHandler(void)
	{
		if (UART0->S1 & (UART_S1_OR_MASK |UART_S1_NF_MASK |
				UART_S1_FE_MASK | UART_S1_PF_MASK))
		{
			// clear the error flags
			UART0->S1 |= UART0_S1_OR_MASK | UART0_S1_NF_MASK|
					UART0_S1_FE_MASK | UART0_S1_PF_MASK;
			// read the data register to clear RDRF
			ch = UART0->D;

		}
		if (UART0->S1 & UART0_S1_RDRF_MASK)
		{
			// received a character
			RX_Interrupt_Flag=1;

#ifdef Echo_Mode
			ch = UART0->D;
			RX_Interrupt_Flag=0;
			Echo(ch);

#endif
#ifdef Application_Mode
			Buffer_Display();
#endif
		}

		if ((UART0->C2 & UART0_C2_TIE_MASK) && // transmitter interrupt enabled
				(UART0->S1 & UART0_S1_TDRE_MASK))
		{
			TX_Interrupt_Flag=1;
		}
		else
		{
			// queue is empty so disable transmitter interrupt
			UART0->C2 &= ~UART0_C2_TIE_MASK;
		}

	}

	//function to transmit a chracter to the terminal
	void UART0_Transmit_Poll(int8_t data)
	{
		while (!(UART0->S1 & UART0_S1_TDRE_MASK))
			;
		UART0->D = data;
	}

	//function to receive the vale on the terminal
	int8_t UART0_Receive_Poll(void)
	{

		BLUE_LED_ON();
		Delay_Time(20);
		BLUE_LED_OFF();

		int8_t ch;
		while (!(UART0->S1 & UART0_S1_RDRF_MASK))
			;
		ch = UART0->D;
		Add_Element_To_Buffer(rx_cb,ch);

		return ch;
	}


#ifdef Application_Mode
	//adding elements received on terminal to the circular buffer in application mode
	int8_t Receive_Data_Interupt()
	{
		ch = UART0->D;
		Add_Element_To_Buffer(rx_cb,ch);

		return ch;
	}
#endif

//get the value in the receive buffer of UART in Echo_mode
#ifdef Echo_Mode

	int8_t Receive_Data_Interupt()
	{

		GREEN_LED_ON();

		ch = UART0->D;

		return ch;
	}

#endif


#ifdef Echo_Mode
	//retransmit the value received to the terminal in Echo mode
	void Echo(int8_t d)
	{
		char sp=' ';

		GREEN_LED_ON();


//check if the buffer is full, if yes then stop echoing
		if(!(full_flag))
		{
			UART0_Transmit_Poll(d);
		}
		else
		{
			UART0_Transmit_Poll(sp);
		}
	}
#endif


//get the value in the receive buffer of UART in Apllication_Mode
#ifdef Application_Mode
	void Echo(int8_t d)
	{
		char sp=' ';

		GREEN_LED_ON();
		Delay_Time(20);
		GREEN_LED_OFF();

//check if the buffer is full, if yes then stop echoing
		if(!(full_flag))
		{
			UART0_Transmit_Poll(d);

		}
		else
		{
			UART0_Transmit_Poll(sp);
		}

	}
#endif


#ifdef Echo_Mode
	void Poling_Function()
	{
		int8_t c;

		Check_Buffer(rx_cb,LENGTH);
		c = UART0_Receive_Poll();
		Echo(c);

		//wrap around condition while removing
		if(full_flag)
		{
			Remove_Element_From_Buffer(rx_cb,6);
		}

	}
#endif

#ifdef Application_Mode
//receiving and retransmitting the value to the terminal
	int8_t Poling_Function()
	{
		Time_Stamp();
		BLUE_LED_ON();
		Delay_Time(20);
		BLUE_LED_OFF();
		int8_t c;
		c = UART0_Receive_Poll();
		Echo(c);

		return c;
	}

//receiving and retransmitting the value to the terminal in the buffer_expand mode
#if Buffer_Expand==1
	void Buffer_Display()
	{
		Time_Stamp();

		int8_t Val[LENGTH]={0};
		Log_String(0,1,"Buffer:");
		int z=1;


		for(int i=0; i<LENGTH; i++)
		{
			Val[i]=Poling_Function();
			PRINTF("\n\rASCII Value:%d\n\r",Val[i]);
			Count_Characters(Val,z);
			z++;
		}

	}



#elif Buffer_Expand==0
//get the chracter count in application mode
	void Buffer_Display()
	{
		Time_Stamp();
		Poling_Function();
		if(full_flag)
		{
			Expand_Buffer(rx_cb,6);
			full_flag=0;
		}
	}
#endif

#endif




