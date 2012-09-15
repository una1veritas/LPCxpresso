//*****************************************************************************
//   +--+       
//   | ++----+   
//   +-++    |  
//     |     |  
//   +-+--+  |   
//   | +--+--+  
//   +----+    Copyright (c) 2009-11 Code Red Technologies Ltd.
//
// systick_main.c provides an example of how to use the SysTick timer
// built in to the Cortex-M3 core of the LPC1768 MCU on the RDB1768 
// development board. The example will cause the state of the user LEDs
// (LEDs 2-5) to toggle every second.
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
#include "core_cm3.h"

#include "leds.h"

#include <cr_section_macros.h>
#include <NXP/crp.h>

// Variable to store CRP value in. Will be placed automatically
// by the linker when "Enable Code Read Protect" selected.
// See crp.h header for more information
__CRP const unsigned int CRP_WORD = CRP_NO_CRP ;

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
	    ms_delay (1000); // wait a second (1000ms)
	    leds_invert();	// Toggle state of user leds
	}
	return 0 ;
}
