
/*
 * @file  Unit_Testing.c
 * author: kushagra Pandey & Vaidehi Salway
 * Date:10/16/2019
 */

#include "Unit_Testing.h"
#include "UART.h"

// Code for random generator
// Reference:   https://rosettacode.org/wiki/Linear_congruential_generator
//

//flags set to check NULL, FULL and EMPTY Conditions in the buffer
int8_t Null_ptr=0;
int8_t flag_full_ut=0;
int8_t flag_empty_ut=0;

//buffer size
#define LENGTH4  30

Buffer_Parameters* ut_cb;


//testing the data access for the buffer
void Test_Data_Access()
{
	START_CRITICAL();
	ut_cb=malloc(LENGTH4*sizeof(Buffer_Parameters));

	UCUNIT_Init();
	uint8_t test_log;
	uint8_t ideal=0;

	UCUNIT_TestcaseBegin("BUFFER TEST DATA ACCESS BEGIN");
	Init_Buffer(ut_cb,LENGTH4);
	Check_Buffer(ut_cb,LENGTH4);
	test_log=Null_ptr;

	UCUNIT_CheckIsEqual(test_log,ideal);


	UCUNIT_TestcaseEnd();
	UCUNIT_WriteSummary();
	END_CRITICAL();
}

//checking the wrap around remove condition
void Wrap_Remove()
{

		UCUNIT_Init();
		int8_t test_log;


		UCUNIT_TestcaseBegin("WRAP REMOVE TEST BEGIN");
		test_log=0;

		UCUNIT_CheckIsEqual(test_log,0);
		UCUNIT_CheckIsInRange(0,0,4);

		UCUNIT_TestcaseEnd();
		UCUNIT_WriteSummary();


}

//testin the wrap around add condition
void Wrap_Add()

{

			UCUNIT_Init();

			int8_t test_log=3;

			UCUNIT_TestcaseBegin("WRAP ADD TEST BEGIN");

			UCUNIT_CheckIsEqual(test_log,3);
			UCUNIT_CheckIsInRange(test_log,0,4);

			UCUNIT_TestcaseEnd();
			UCUNIT_WriteSummary();

}


//testing the full condition in the buffer
void Buffer_OverFill()

{
	START_CRITICAL();
			UCUNIT_Init();
			int8_t test_log;
			int8_t ideal=0;

			UCUNIT_TestcaseBegin("OVER FULL TEST BEGIN");
			test_log=flag_full_ut;

			UCUNIT_CheckIsEqual(test_log,ideal);

			UCUNIT_TestcaseEnd();
			UCUNIT_WriteSummary();
			END_CRITICAL();
}

//testing the empty condition in the buffer
void Buffer_OverEmpty()
{
	START_CRITICAL();

				UCUNIT_Init();
				int8_t test_log;
				int8_t ideal=0;

				UCUNIT_TestcaseBegin("OVER EMPTY TEST BEGIN");
				test_log=flag_empty_ut;

				UCUNIT_CheckIsEqual(test_log,ideal);

				UCUNIT_TestcaseEnd();
				UCUNIT_WriteSummary();
				END_CRITICAL();

}
//testing the destroy condition of the buffer
void Buffer_Destroy()
{
	START_CRITICAL();
	 ut_cb=malloc(LENGTH4*sizeof(Buffer_Parameters));

					UCUNIT_Init();

					UCUNIT_TestcaseBegin("BUFFER DESTROY TEST BEGIN");
					Destroy_Buffer(ut_cb);
					UCUNIT_CheckIsNull(ut_cb);

					UCUNIT_TestcaseEnd();
					UCUNIT_WriteSummary();

					END_CRITICAL();
}



