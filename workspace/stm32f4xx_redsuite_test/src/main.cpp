/*
===============================================================================
 Name        : main.cpp
 Author      : 
 Version     :
 Copyright   : Copyright (C)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "stm32f4xx.h"
#endif

#include "gpio.h"
// TODO: insert other include files here

// TODO: insert other definitions and declarations here

int main(void) {
	
	// TODO: insert code here
	
	pinMode(PD12, GPIO_Mode_OUT);
	// force the counter to be placed into memory
	volatile static int i = 0 ;

	// Enter an infinite loop, just incrementing a counter
	while(1) 
		i++;
	return 0 ;
}
