//*****************************************************************************
//   +--+
//   | ++----+
//   +-++    |
//     |     |
//   +-+--+  |
//   | +--+--+
//   +----+    Copyright (c) 2010-11 Code Red Technologies Ltd.
//
// timers_main.c sets up the 4 timers to be found in the LPC1768 MCU fitted
// to the RDB1768 development board, and flashes the LEDs based on when the
// timers trigger interrupts.
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

#include "LPC17xx.h"
#include "timer.h"
#include "leds.h"

#include <cr_section_macros.h>
#include <NXP/crp.h>

// Variable to store CRP value in. Will be placed automatically
// by the linker when "Enable Code Read Protect" selected.
// See crp.h header for more information
__CRP const unsigned int CRP_WORD = CRP_NO_CRP ;


#define TIMER0_INTERVAL	((2 * (4 *(SystemCoreClock/10))) - 1)
#define TIMER1_INTERVAL	((2 *(4 *(SystemCoreClock/10))/3) - 1)
#define TIMER2_INTERVAL	((2 *(4 *(SystemCoreClock/10))/5) - 1)
#define TIMER3_INTERVAL	((2 *(4 *(SystemCoreClock/10))/7) - 1)

#define PCTIM0_POWERON (1 << 1)
#define PCTIM1_POWERON (1 << 2)
#define PCTIM2_POWERON (1 << 22)
#define PCTIM3_POWERON (1 << 23)

// The timerX_toggle variables allow the behaviour of the code to be
// modified at run time. When timerX_toggle is set by the user, via
// the debugger, the corresponding timer will be enabled/disabled,
// depending on its current state.
// As bss data items, these will all be set to 0 by the startup code
uint32_t timer0_toggle, timer1_toggle, timer2_toggle, timer3_toggle;

int main (void)
{
	// When the application starts, all timers will be set to running.
	uint32_t timer0_running = 1;
	uint32_t timer1_running = 1;
	uint32_t timer2_running = 1;
	uint32_t timer3_running = 1;

	leds_init();	// Setup GPIO for user leds
	leds_all_on();	// Turn the user leds all on

	// Turn on power to TIMER2 and TIMER3
	// (TIMER0 and TIMER1 on by default)
	LPC_SC->PCONP |=  PCTIM2_POWERON | PCTIM3_POWERON;

	// Initialise all timers
	init_timer( 0, TIMER0_INTERVAL );
	init_timer( 1, TIMER1_INTERVAL );
	init_timer( 2, TIMER2_INTERVAL );
	init_timer( 3, TIMER3_INTERVAL );

	// Enable all timers
	enable_timer( 0 );
	enable_timer( 1 );
	enable_timer( 2 );
	enable_timer( 3 );

	// Loop forever
	while (1)
	{
		// The main work of the application - ie toggling leds based on the
		// timers - is actually all done in the interrupt handlers.
		//
		// In this loop, the code simply checks if the user has requested
		// that the state of one of the timers is changed (done via the
		// debugger, not in the application code). If a toggle request is
		// detected, then the state of the corresponding timer is inverted
		// ie changed from  enabled to disabled, or disabled to enabled.
		//

		if (timer0_toggle == 1)
		{
			  timer0_toggle = 0;
			  if (timer0_running == 1)
			  {
				  timer0_running = 0;
				  disable_timer (0);
			  }
			  else
			  {
				  timer0_running = 1;
				  enable_timer (0);
			  }
		}
		if (timer1_toggle == 1)
		{
			  timer1_toggle = 0;
			  if (timer1_running == 1)
			  {
				  timer1_running = 0;
				  disable_timer (1);
			  }
			  else
			  {
				  timer1_running = 1;
				  enable_timer (1);
			  }
		}
		if (timer2_toggle == 1)
		{
			  timer2_toggle = 0;
			  if (timer2_running == 1)
			  {
				  timer2_running = 0;
				  disable_timer (2);
			  }
			  else
			  {
				  timer2_running = 1;
				  enable_timer (2);
			  }
		}
		if (timer3_toggle == 1)
		{
			  timer3_toggle = 0;
			  if (timer3_running == 1)
			  {
				  timer3_running = 0;
				  disable_timer (3);
			  }
			  else
			  {
				  timer3_running = 1;
				  enable_timer (3);
			  }
		}
	} // end of while (1)
} // end of main()
