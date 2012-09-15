//*****************************************************************************
//   +--+       
//   | ++----+   
//   +-++    |  
//     |     |  
//   +-+--+  |   
//   | +--+--+  
//   +----+    Copyright (c) 2011 Code Red Technologies Ltd.
//
// hoststring_main.c provides an example of how to use Host String
// functionality of 'Red Trace' in Red Suite 4.
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

#include "leds.h"

#include <cr_section_macros.h>
#include <NXP/crp.h>

#include "hoststrings.h"

// Variable to store CRP value in. Will be placed automatically
// by the linker when "Enable Code Read Protect" selected.
// See crp.h header for more information
__CRP const unsigned int CRP_WORD = CRP_NO_CRP ;

volatile uint32_t msTicks = 0; // counter for 1ms SysTicks

// ****************
//  SysTick_Handler - just increment SysTick counter
void SysTick_Handler(void) {
	static uint32_t counter = 0;
	msTicks++;
	if (++counter == 10000 ) {
		counter = 0;
		HS_DisplayVal (msTicks); // Host Strings diagnostic message
	}
}

// ****************
// ms_delay - creates a delay of the appropriate number of Systicks (happens every 1 ms)
__INLINE static void ms_delay (uint32_t delayTicks) {
  uint32_t currentTicks;

  currentTicks = msTicks;	// read current tick counter
  // Now loop until required number of ticks passes.
  while ((msTicks - currentTicks) < delayTicks);
}

// ****************
int main(void) {
	
	leds_init();	// Setup GPIO for user leds	
	leds_all_on();	// Turn the user leds all on

	// Setup SysTick Timer to interrupt at 1 msec intervals
	if (SysTick_Config(SystemCoreClock / 1000)) { 
	    while (1);  // Capture error
	}

	
	// Enter an infinite loop, just incrementing a counter and toggling leds every second
	volatile static int i = 0 ;
	while(1) {
		i++;
	    ms_delay (2000); // wait 2 seconds (2000ms)
	    HS_LedsOff();    // Host Strings diagnostic message
	    leds_invert();	 // Toggle state of user leds

		i++;
	    ms_delay (2000); // wait 2 seconds (2000ms)
	    HS_LedsOn();     // Host Strings diagnostic message
	    leds_invert();	 // Toggle state of user leds

	}
	return 0 ;
}
