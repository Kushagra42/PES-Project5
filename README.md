# PES-Project5

#Creted by: Vaidehi Salway & Kushagra Pandey
#Date: 18-Nov-2019

#Refrences: Following refrences were used to gain insghts for some of the 
#functions implemented in this code.

#Counting number of characters: https://www.geeksforgeeks.org/c-program-to-count-the-number-of-characters-in-a-file/
#Uart: GitHub Repo at https://github.com/alexander-g-dean/ESF/tree/master/Code/Chapter_9/DMA_Examples/Source
#Circular Buffer Concept: https://www.geeksforgeeks.org/circular-queue-set-1-introduction-array-implementation/


#Repo Content:

#Soure code - main.c in src foldre other files in board folder
#FMEA excel sheet
#UART png file- showing UART Tx/Rx waveform
#Readme  

#Assignment Description:

#This project connects the KL25Z through USB port to send and receive data from a PC-based terminal program.  
#This setup includes firmware topics such as, including UART communication device drivers, 
#circular buffers, and more on interrupts and timers. 


#The LED run in the following pattern
#Initialized to blue
#Set to blue when the program moves to receiving or waiting to receive
#Set to green when the program moves to transmitting or waiting to transmit
#Red if there is any error condition detected

#We have developed a logger which works in three modes:
#1. Test mode: this prints detailed test messages on mcuxpresso terminal through UART
#2. Debug mode: this prints all the Debug messages on mcuxpresso terminal through UART
#3. Status mode: this only prints the Status messages on mcuxpresso terminal through UART


# In this project we have also implemented micro unit test to test the functionalities of circular buffer used in the project
# We have also implemented resizing of the circular buffer once the allocated buffer is full. 

# Project Execution Instructions
# Choose the application mode or echo mode - UART.h
# Select the logger either as 0,1,2 to choose between status, test and debug messages - Logger.h
# Select expandable mode for circular buffer - CIRCULAR_BUFFER.h
# Select uC Unit test - UART.h
# Set same circular buffer size for:  LENGTH - UART.h, LENGTH2- Logger.h, LENGTH3-Counting_Characters.h 



# Project Execution
# This project runs in two modes
# 1. Echo mode- prints the Data received via UART to the terminal
# 2. Application mode: Stores the data in circular buffer and displays on terminal, also shows the chracter count
# Both the modes run on either interrupt mode or polling mode
# Logger messages are dislayed in three forms: Status, Test and Debug
# uC Unit tests are run for circular buffer
# RED, GREEN and BLUE leds blink to show different stages of program, such as blue for initialization and receive, green for transmission, red for error
# Dynamic resizing of circular buffer is implemnted 


# Difficulties faced
# 1. while running the application mode could not print the data in bulk

# Tried resolving the difficulty by reading from resources online and writing multiple functions to test the outputs

