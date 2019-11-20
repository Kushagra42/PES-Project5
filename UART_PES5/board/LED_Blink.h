
/*
 * @file LED_Blink.h
 * author: kushagra Pandey & Vaidehi Salway
 * Date:10/16/2019
 *
 * This is the header file to the LED_Blink.c
 * This contains Function definitions for two modes of operation of the program
 * 1. FB_RUN: to run on KL25Z frdm board
 * 2. PC_RUN: to run on development environment such as windows and linux
 */


#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"



void GREEN_LED_INIT();
void GREEN_LED_ON();
void GREEN_LED_OFF();

void RED_LED_INIT();
void RED_LED_ON();
void RED_LED_OFF();

void BLUE_LED_INIT();
void BLUE_LED_ON();
void BLUE_LED_OFF();



