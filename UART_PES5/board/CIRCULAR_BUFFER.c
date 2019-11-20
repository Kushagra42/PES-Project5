/*
 * @file CIRCULAR_BUFFER.c
 * author: kushagra Pandey & Vaidehi Salway
 * Date:11/18/2019
 */

#include "CIRCULAR_BUFFER.h"
#include "fsl_uart.h"
#include "fsl_debug_console.h"
#include "LED_Blink.h"


extern int8_t full_flag;
extern int8_t empty_flag;

extern int8_t Null_ptr;
extern int8_t flag_full_ut;
extern int8_t flag_empty_ut;



//Initializing the pointer for Circular buffer by allocating memory.
BUFFER_STATUS Init_Buffer(Buffer_Parameters *Buffer_Ptr, int8_t Buffer_Length)

{


	if(Buffer_Ptr==NULL || Buffer_Length<=0)
	{
		Null_ptr=1;
		return BUFFER_POINTER_NULL;
	}

	else
	{

		Buffer_Ptr->Buffer_Base_Pointer=(int8_t*)malloc(Buffer_Length*(sizeof(char)));

		Buffer_Ptr->Buffer_Head=Buffer_Ptr->Buffer_Base_Pointer;
		Buffer_Ptr->Buffer_Tail=Buffer_Ptr->Buffer_Head;
		Buffer_Ptr->Buffer_Length=Buffer_Length;
		Buffer_Ptr->Range=Buffer_Ptr->Buffer_Base_Pointer+(Buffer_Length-1);
		Buffer_Ptr->Buffer_Count=0;

		return BUFFER_INIT_SUCCESS;

	}
}
//Checking if the Circular buffer is EMPTY or is FULL
BUFFER_STATUS Check_Buffer(Buffer_Parameters *Buffer_Ptr, int8_t Buffer_Length)

{
//check if the buffer counter is null
	if(Buffer_Ptr==NULL)
	{
		Null_ptr=1;
		RED_LED_ON();
		Delay_Time(20);
		RED_LED_OFF();



		return BUFFER_POINTER_NULL;
	}

	//check if the buffer is empty
	if(Buffer_Ptr->Buffer_Count==0)
	{
		RED_LED_ON();
		Delay_Time(20);
		RED_LED_OFF();


		empty_flag=1;
		flag_empty_ut=1;
		return BUFFER_IS_EMPTY;
	}
	//check if the buffer is full
	else if(Buffer_Ptr->Buffer_Count>=Buffer_Ptr->Buffer_Length)
	{
		Log_String(0,1," BUFFER IS FULL");
		full_flag=1;
		flag_full_ut=1;
		RED_LED_ON();
		Delay_Time(20);
		RED_LED_OFF();

		return BUFFER_IS_FULL;

	}
	return BUFFER_INIT_SUCCESS;

}

//Adding a single element to the Circular buffer
BUFFER_STATUS Add_Element_To_Buffer(Buffer_Parameters *Buffer_Ptr, int8_t Value)

{

	//check if the buffer counter is null
	if(Buffer_Ptr==NULL)
	{
		Null_ptr=1;
		RED_LED_ON();
		Delay_Time(20);
		RED_LED_OFF();

		return BUFFER_POINTER_NULL;
	}

	else
	{
		//check if the buffer is full
		if(Buffer_Ptr->Buffer_Count>=Buffer_Ptr->Buffer_Length)
		{
			Log_String(0,1,"BUFFER IS FULL");
			full_flag=1;
			flag_full_ut=1;
			RED_LED_ON();
			Delay_Time(20);
			RED_LED_OFF();


			return BUFFER_IS_FULL;
		}

		else
		{
			BLUE_LED_ON();
			Delay_Time(20);
			BLUE_LED_OFF();


			if(Buffer_Ptr->Buffer_Tail==Buffer_Ptr->Range)
			{

				*(Buffer_Ptr->Buffer_Head)=Value;
				Buffer_Ptr->Buffer_Head+=1;

			}
			else
			{
				*(Buffer_Ptr->Buffer_Head)=Value;
				Buffer_Ptr->Buffer_Head+=1;
			}

		}
		Buffer_Ptr->Buffer_Count++;
		PRINTF("\n\rcount %d\n\r",Buffer_Ptr->Buffer_Count);

		return BUFFER_INIT_SUCCESS;
	}

}


//Adding a single element to the Circular buffer
BUFFER_STATUS Add_String_To_Buffer(Buffer_Parameters *Buffer_Ptr, int8_t * Data, int8_t Length)
{
	//check if the buffer counter is null
	if(Buffer_Ptr==NULL)
	{
		Null_ptr=1;
		RED_LED_ON();
		Delay_Time(20);
		RED_LED_OFF();


		return BUFFER_POINTER_NULL;
	}

	else
	{
		int i;
		BUFFER_STATUS Last_Data;
		for(i=0;i<Length;i++)
		{
			Last_Data=Add_Element_To_Buffer(Buffer_Ptr,*(Data+i));

		}
		return Last_Data;

	}

}



//Removing elements from the Circular Buffer
BUFFER_STATUS Remove_Element_From_Buffer(Buffer_Parameters *Buffer_Ptr, int8_t Value)
{
	//check if the buffer counter is null
	if(Buffer_Ptr==NULL)
	{
		Null_ptr=1;
		RED_LED_ON();
		Delay_Time(20);
		RED_LED_OFF();

		return BUFFER_POINTER_NULL;
	}

	else
	{
		//check if the buffer is empty
		if(Buffer_Ptr->Buffer_Count==0)
		{
			empty_flag=1;
			flag_empty_ut=1;
			RED_LED_ON();
			Delay_Time(20);
			RED_LED_OFF();

			Log_String(0,1," BUFFER IS EMPTY");
			return BUFFER_IS_EMPTY;
		}

		Value=*(Buffer_Ptr->Buffer_Tail);

		if(Buffer_Ptr->Buffer_Tail==Buffer_Ptr->Range)
		{
			Buffer_Ptr->Buffer_Tail=Buffer_Ptr->Buffer_Base_Pointer;

		}
		else
		{
			Buffer_Ptr->Buffer_Tail++;
		}

		Buffer_Ptr->Buffer_Count--;
		PRINTF("\n\rcount:%d\n\r",Buffer_Ptr->Buffer_Count);

		return BUFFER_INIT_SUCCESS;
	}


}

BUFFER_STATUS Destroy_Buffer(Buffer_Parameters *Buffer_Ptr)
{

	//check if the buffer counter is null
	if(Buffer_Ptr==NULL)
	{
		Null_ptr=1;
		RED_LED_ON();
		Delay_Time(20);
		RED_LED_OFF();

		return BUFFER_POINTER_NULL;
	}

	else
	{
		free(Buffer_Ptr->Buffer_Base_Pointer);
		return BUFFER_INIT_SUCCESS;
	}


}

#ifdef Buffer_Expand
//fucntion to expand the buffer size once the bufefr is full, using realloc().
BUFFER_STATUS Expand_Buffer(Buffer_Parameters *Buffer_Ptr, int8_t Buffer_Length)
{

	Log_String(0,1," expanding buffer size");

	Buffer_Ptr->Buffer_Base_Pointer=(int8_t*)realloc(Buffer_Ptr->Buffer_Base_Pointer,Buffer_Length);

			Buffer_Ptr->Buffer_Head=Buffer_Ptr->Buffer_Base_Pointer;
			Buffer_Ptr->Buffer_Tail=Buffer_Ptr->Buffer_Head;
			Buffer_Ptr->Buffer_Length=Buffer_Length;
			Buffer_Ptr->Range=Buffer_Ptr->Buffer_Base_Pointer+(Buffer_Length-1);
			Buffer_Ptr->Buffer_Count=0;

			return BUFFER_INIT_SUCCESS;

}
#endif



