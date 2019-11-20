

/*
 * @file UART.h
 * author: kushagra Pandey & Vaidehi Salway
 * Date:11/18/2019
 */

#include <MKL25Z4.H>

#include "CIRCULAR_BUFFER.h"
#include "Delay_Function.h"

//#define Application_Mode
#define Echo_Mode
//#define Unit_Test

#define USE_UART_INTERRUPTS 	(1) // 0 for polled UART communications, 1 for interrupt-driven
#define UART_OVERSAMPLE_RATE 	(16)
#define BUS_CLOCK 				(24e6)
#define SYS_CLOCK				(48e6)

//size of the buffer
#define LENGTH  30


#define START_CRITICAL()  __disable_irq()
#define END_CRITICAL()    __enable_irq()

//Initialize UART
void Init_UART0(uint32_t baud_rate);
void UART0_Transmit_Poll(int8_t data);
int8_t UART0_Receive_Poll(void);

int8_t Receive_Data_Interupt();
void Echo(int8_t d);
void Echo1(int8_t *d,size_t length);

#ifdef Echo_Mode
void Poling_Function();
#endif

//function definations for application mode
#ifdef Application_Mode
int8_t Poling_Function();
void Buffer_Display();
#endif

void Poling_Function1();

void Display_Data(int8_t* data);


//pointers for dynamic allocation of memory
extern Buffer_Parameters* rx_cb;
extern Buffer_Parameters* tx_cb;
extern  Buffer_Parameters* ut_cb;


