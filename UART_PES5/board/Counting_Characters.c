
/*
 * @file Counting_Characters.c
 * author: kushagra Pandey & Vaidehi Salway
 * Date:11/18/2019
 */

#include "Counting_Characters.h"
#include "UART.h"

//function to get the count for different characters
void Count_Characters(int8_t Buffer_char[LENGTH3], int count_count)
{

  int c = {0}, count[128] = {0}, x, counted = 0,i=0;
for(int i=0;i<LENGTH3;i++)
{
    if(Buffer_char[i] >= '!' && Buffer_char[i] <= '~')
    {
      x = Buffer_char[i] - 33;
      count[x]++;
    }

    c++;

}
//display only after the buffer is full
 if(count_count==LENGTH3)
 {
  for (c= 0; c < 128; c++)
  {
    if(count[c] > 0)
    {
    	//display the character and its count
    	PRINTF("CHARACTER: %c, COUNT: %d\n\r", c + '!', count[c]);
        counted++;
    }

  }
 }
}





