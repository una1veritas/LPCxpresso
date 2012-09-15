//*****************************************************************************
//   +--+       
//   | ++----+   
//   +-++    |  
//     |     |  
//   +-+--+  |   
//   | +--+--+  
//   +----+    Copyright (c) 2010-11 Code Red Technologies Ltd.
//
// led_strobe.c demonstrates the use of the "user LEDs" on the
// RDB1768 development board (LEDs 2-5).
//
//
// Software License Agreement
// 
// The software is owned by Code Red Technologies and/or its suppliers, and is 
// protected under applicable copyright laws.  All rights are reserved.  Any 
// use in violation of the foregoing restrictions may subject the user to criminal 
// sanctions under applicable laws, as well as to civil liability for the breach 
// of the terms and conditions of this license.
// 
// THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
// OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
// USE OF THIS SOFTWARE FOR COMMERCIAL DEVELOPMENT AND/OR EDUCATION IS SUBJECT
// TO A CURRENT END USER LICENSE AGREEMENT (COMMERCIAL OR EDUCATIONAL) WITH
// CODE RED TECHNOLOGIES LTD. 

// CMSIS headers required for setting up SysTick Timer
#include "LPC17xx.h"

// Header for RDB1768 led routines and constants
#include "leds.h"

#include <cr_section_macros.h>
#include <NXP/crp.h>

// Variable to store CRP value in. Will be placed automatically
// by the linker when "Enable Code Read Protect" selected.
// See crp.h header for more information
__CRP const unsigned int CRP_WORD = CRP_NO_CRP ;

// Time period to wait between toggling LED. 1000 msecs = 1 secs.
#define DELAY_LEN_MAX 200
#define DELAY_LEN_MIN 20
#define DELAY_CHANGE 20


uint32_t flashval; // current length of led flash

// The following variables are used to store the maximum and minimum led flash
// periods, and the amount the period changes by each iteration.
// These do no strictly need to be variables, but having them as globals means
// that the behaviour of the application code be easily changed from the debugger
// when the code is being run.
uint32_t maxflashval, minflashval, changeval;

// If set to none-zero, then speed of flash will stay constant
uint32_t constflash = 0;

// Controls whether flash period change is a decrease or increase
int32_t sign = +1 ;


volatile uint32_t msTicks; // counter for 1ms SysTicks

// ****************
//  SysTick_Handler - just increment SysTick counter
void SysTick_Handler(void) {
  msTicks++;
}

// ****************
// ms_delay - creates a delay of the appropriate number of Systicks (happens every 1 ms)
__INLINE static void ms_delay (uint32_t delayTicks) {
  uint32_t currentTicks;

  currentTicks = msTicks;	// read current tick counter
  // Now loop until required number of ticks passes.
  while ((msTicks - currentTicks) < delayTicks);
}


int main(void) {

	// Set up initial flash period, max and min flash periods, and change value
	flashval = DELAY_LEN_MAX;
	maxflashval = DELAY_LEN_MAX;
	minflashval = DELAY_LEN_MIN;
	changeval = DELAY_CHANGE;

	// Initialise GPIO to access user LEDs
	leds_init();

	// Setup SysTick Timer to interrupt at 1 msec intervals
	if (SysTick_Config(SystemCoreClock / 1000)) {
	    while (1);  // Capture error
	}
	
	// Enter an infinite loop, cycling through led strobe sequence
	while(1) {

		// Turn each led on (and then off) in turn
		// Pattern is 3,2,5,4 because of order leds are
		// laid out on board

		led_on (LED_3);
		ms_delay(flashval);
		led_off (LED_3);
		led_on (LED_2);
		ms_delay(flashval);
		led_off (LED_2);
		led_on (LED_5);
		ms_delay(flashval);
		led_off (LED_5);
		led_on (LED_4);
		ms_delay(flashval);
		led_off (LED_4);

		// Now go back again
		led_on (LED_5);
		ms_delay(flashval);
		led_off (LED_5);
		led_on (LED_2);
		ms_delay(flashval);
		led_off (LED_2);

		// Check to see if changing flash period is required
		if (constflash  == 0)
		{
		// Check to see if the flash period is at min or max point
		  if (flashval <= minflashval)
		  {	  // Reverse direction of change
			  sign = +1;
			  flashval = minflashval;
		  }
		  else if (flashval >= maxflashval)
		  {
			  sign = -1;
			  flashval = maxflashval;
		  }

		  // Modify the flash period (either increase or decrease
		  // depending on sign)
		  flashval = flashval + (sign * changeval);
		}
	}
	return 0 ;
}
