
/*
 * @file CIRCULAR_BUFFER.h
 * author: kushagra Pandey & Vaidehi Salway
 * Date:11/18/2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "Logger.h"

#define START_CRITICAL1()  __enable_irq()
#define END_CRITICAL1()    __disable_irq()

#define Buffer_Expand   (1)//1 for non-expandable buffer, 0 for expandable buffer

//returning status of the circular buffer using enums
typedef enum
{
	BUFFER_IS_EMPTY,
	BUFFER_IS_FULL,
	POINTER_INIT_ERROR,
	BUFFER_POINTER_NULL,
	BUFFER_INIT_SUCCESS

}BUFFER_STATUS;

//parameters for the circular bufer are defined in a structure
 typedef struct//pointer, head, tail, length, count
{
	int8_t* Buffer_Base_Pointer;
	int8_t* Buffer_Head ;
	int8_t* Buffer_Tail;
	size_t   Buffer_Length;
	int8_t  Buffer_Count;
	int8_t* Range;

}Buffer_Parameters;


BUFFER_STATUS Init_Buffer(Buffer_Parameters *Buffer_Ptr, int8_t Buffer_Length);

BUFFER_STATUS Check_Buffer(Buffer_Parameters *Buffer_Ptr, int8_t Buffer_Length);

BUFFER_STATUS Add_Element_To_Buffer(Buffer_Parameters *Buffer_Ptr, int8_t Value);

BUFFER_STATUS Add_String_To_Buffer(Buffer_Parameters *Buffer_Ptr, int8_t * Data, int8_t Length);

BUFFER_STATUS Remove_Element_From_Buffer(Buffer_Parameters *Buffer_Ptr, int8_t Value);

BUFFER_STATUS Destroy_Buffer(Buffer_Parameters *Buffer_Ptr);

#ifdef Buffer_Expand
BUFFER_STATUS Expand_Buffer(Buffer_Parameters *Buffer_Ptr, int8_t Buffer_Length);
#endif

