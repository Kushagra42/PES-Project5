/*
 * @file Delay_Function.h
 * author: kushagra Pandey & Vaidehi Salway
 * Date:10/14/2019
 *
 * This .h file includes all the header files required for the Delay_Function.c file
 */

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"



// defining the delay function
void Delay_Time(uint32_t milli_sec_val);
uint8_t TimeOut_Counter(uint8_t Time_out);
void Init_Systick(void);
uint64_t Current_Timer();
void Time_Stamp();
