/*
 * @file Logger.c
 * author: kushagra Pandey & Vaidehi Salway
 * Date:10/18/2019
 *
 * This .c file contains the logger statements for cross-platform
 * There are two modes of operating this file
 * 1. Logger Enable
 * 2. Logger Disable
 *
 * Enable or Disable the logger by un-commenting #define logging_init or #define logging_notinit respectively from Logger.h
 *
 # Enum to string Conversion-https://stackoverflow.com/questions/3168306/print-text-instead-of-value-from-c-enum
 *
 *
 */

#include "Logger.h"
#include "UART.h"

uint8_t log_status;


// Function log enable, when called in main returns log_status 1
void Log_Enabled()
{
	log_status=1;
}

// Function log disable, when called in main returns log status 0
void Log_Disabled()
{
	PRINTF("\nLOGGERS ARE DISABLED");
	log_status=0;
}

// checking condition to enable logging
// Status function called when logging_init is defined in logger.h
#ifdef logging_init

// Function Status calls log_Enabled
uint8_t Status()
{
	Log_Enabled();
	return log_status;
}
#endif

//enums defined for different LOG Values
enum LogLevel
{
	TEST,
	DEBUGG,
	STATUS,
	 I
};

//enums defined for different FUNCTION values
enum Functions
{
	FN_Delay_Time,//0
	FN_Init_UART0,//1
	FN_UART0_Transmit_Poll,//2
	FN_UART0_Receive_Poll,//3
	FN_UART_send1,//4
	FN_UART_receive1,//5
	FN_UART_send_n1,//6
	FN_UART_receive_n1,//7
	FN_Receive_Data_Interupt,//8
	FN_Echo,//9
	FN_Echo1,//10
	FN_Poling_Function,//11
	FN_Buffer_Display,//12
	FN_Init_Buffer,//13
	FN_Check_Buffer,//14
	FN_Add_Element_To_Buffer,//15
	FN_Add_String_To_Buffer,//16
	FN_Remove_Element_From_Buffer,//17
	FN_Destroy_Buffer,//18
	II//19

};



// checking condition to disable logging
// Status function called when logging_notinit is defined in logger.h
#ifdef logging_notinit

//Function Status calls log_Disabled
uint8_t Status()
{
	Log_Disabled();
	return log_status;
}
#endif


//converting the enum in log levels to string
const char* getloglevel(enum LogLevel log_level)
{
switch (log_level)
{
case 0 : return "Test";
case 1 : return "Debug";
case 2 : return "Status";
case 3 : return " I";
}
};

//converting the enum in function types to string
const char* getFunctions(enum Functions Function)
{
switch (Function)
{
case 0 : return "Delay_Time";
case 1 : return "Init_UART0";
case 2 : return "UART0_Transmit_Poll";
case 3 : return "UART0_Receive_Poll";
case 4 : return "UART_send1";
case 5 : return "UART_receive1";
case 6 : return "UART_send_n1";
case 7 : return "UART_receive_n1";
case 8 : return "Receive_Data_Interupt";
case 9 : return "Echo";
case 10 : return "Echo1";
case 11 : return "Poling_Function";
case 12 : return "Buffer_Display";
case 13 : return "Init_Buffer";
case 14 : return "Check_Buffer";
case 15 : return "Add_Element_To_Buffer";
case 16 : return "Check_Buffer";
case 17 : return "Remove_Element_From_Buffer";
case 18 : return "Destroy_Buffer";
case 19 : return "I";;


}
};

// Log Data function enables printing data on the terminal when running in freedom board
void Log_Data(int x,int y,int8_t data)
	{
		Status();
		if(log_status==1)
			{
						//only prints if log type is test,all three log types will work
						if(level==0)
						{
					     PRINTF("\n\r%s:%s:%d",getloglevel(x),getFunctions(y),data);
						}
						//only prints if log type is debug,debug and status log types will work

						else if(level==1)
						{
							if(x!=0)
						    {
							PRINTF("\n\r%s:%s:%u",getloglevel(x),getFunctions(y),data);
							}

						}
						//only prints if log type is status,status log types will work

						else if(level==2)
						{
							if(x==2 )
						    {
							PRINTF("\n\r%s:%s:%u",getloglevel(x),getFunctions(y),data);
							}

						}
			}

	}


// Log Data function enables printing Strings on the terminal when running in freedom board
void Log_String(int x,int y,char *statement)
	{


		Status();

		if(log_status==1)//LOG-STRING(TEST,2,HI);//define Z DEBUG
			{
			//only prints if log type is test,all three log types will work

				if(level==0)
				{
					Send_String_Poll(getloglevel(x),getFunctions(y),statement);
				}
				//only prints if log type is debug,debug and status log types will work

				else if(level==1)
				{
					if(x!=0)
				    {
						Send_String_Poll(getloglevel(x),getFunctions(y),statement);
					}

				}
				//only prints if log type is status,status log types will work

				else if(level==2)
				{
					if(x==2 )
				    {
						Send_String_Poll(getloglevel(x),getFunctions(y),statement);
					}

				}

			}

	}


// Log Data function enables printing integer values on the terminal when running in freedom board
void Log_Integer(int x,int y,int integer_value)
	{
		Status();

		if(log_status==1)
			{
						//only prints if log type is test,all three log types will work
						if(level==0)
						{
					     PRINTF("\n\r%s:%s:%d",getloglevel(x),getFunctions(y),integer_value);
						}

						//only prints if log type is debug,debug and status log types will work

						else if(level==1)
						{
							if(x!=0)
						    {
							PRINTF("\n\r%s:%s:%d",getloglevel(x),getFunctions(y),integer_value);
							}

						}
						//only prints if log type is status,status log types will work

						else if(level==2)
						{
							if(x==2 )
						    {
							PRINTF("\n\r%s:%s:%d",getloglevel(x),getFunctions(y),integer_value);
							}
						}

			}

	}



void UART_send(int8_t * data)
{
	if(data !=NULL)
	{
      while(!(UART0->S1 & UART0_S1_TDRE_MASK));

      UART0->D = *data;
	}

}


int8_t* UART_receive(int8_t *data)
{
	if(data!=NULL)
	{
		while (!(UART0->S1 & UART0_S1_RDRF_MASK))
			;
		data = UART0->D;
		return data;
	}
	else return 0;
}



void UART_send_n(int8_t* src, size_t length)
{
	int j=0;
	if(src!=NULL && length >0)
	{

		for(j=0;j<length;j++)
		{
			UART_send((src+j));
		}

	}
}

int8_t * UART_receive_n(int8_t* data, size_t length)
{
	int j=0;
	if(data!=NULL && length >0)
	{
		for(j=0;j<length;j++)
		{
			UART_receive((data+j));
		}
		return data;
	}
	else return 0;
}


void Send_String_Poll(const char* str1,const char* str2,char* str)
{

int8_t sp=' ';
	while(*str1 != '\0' )
	{
		UART0_Transmit_Poll(*str1++);
	}
	UART0_Transmit_Poll(sp);

	while(*str2 != '\0' )
	{
		UART0_Transmit_Poll(*str2++);

	}
	UART0_Transmit_Poll(sp);

	while (*str != '\0' )
	{
		UART0_Transmit_Poll(*str++);

	}


}


void Log_Uart_Data(int8_t* data, size_t length)
{
	START_CRITICAL();
	if(data!=NULL)
	{
		UART_send_n(data,length);
	}
	END_CRITICAL();

}


