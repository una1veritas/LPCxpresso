//*****************************************************************************
//   +--+       
//   | ++----+   
//   +-++    |  
//     |     |  
//   +-+--+  |   
//   | +--+--+  
//   +----+    Copyright (c) 2009-11 Code Red Technologies Ltd.
//
// UART example project for RDB1768 development board
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
//
//*****************************************************************************

#include "uart0.h"

#include <cr_section_macros.h>
#include <NXP/crp.h>

// Variable to store CRP value in. Will be placed automatically
// by the linker when "Enable Code Read Protect" selected.
// See crp.h header for more information
__CRP const unsigned int CRP_WORD = CRP_NO_CRP ;

// Control how the character received by the board is echoed back to the host
// Set to true to increment character ('a' echoed as 'b')
#define INCREMENT_ECHO_BY_1 TRUE

// Control whether debug printf are displayed via semihosting to the 
// debugger console window
#define SEMIHOSTING_CONSOLE TRUE

#ifdef SEMIHOSTING_CONSOLE
#include <stdio.h>
#define DBG	printf
#else
#define DBG(x ...)
#endif

int main(void)
{	
	char c;
	volatile static int i = 0 ;
	
	UART0_Init(57600); // Setup UART0 to 57600 baud

	// Startup message for display in debugger console window
	// {displayed only if SEMIHOSTING_CONSOLE define is set).
	DBG("RDB1768 UART Demonstration\n");
	DBG("==========================\n\n");
	DBG("Press a key within your terminal\n");
	DBG("And the board will echo it back\n");	
#ifdef INCREMENT_ECHO_BY_1
	DBG("incremented by 1 ('a'->'b')\n");
#endif	
	DBG("Debugger console will display keys pressed\n");
	DBG("when buffer flushed by pressing 'enter'\n\n");	
	
	
	// Startup message for display in PC's terminal window.
	// You must make sure the terminal program is already
	// running when this code is executed if you want to
	// see it !
	
	UART0_PrintString("RDB1768 UART Demonstration\r\n");
	UART0_PrintString("==========================\r\n\n");
	UART0_PrintString("Press a key within your terminal\r\n");
	UART0_PrintString("and the board will echo it back");	
#ifdef INCREMENT_ECHO_BY_1
	UART0_PrintString(",\r\nincremented by 1 ('a'->'b')");
#endif
	UART0_PrintString(".\r\n\n");
	
	// Enter an infinite loop, accessing UART and incrementing a counter

	while(1) {

		c = UART0_Getchar();	// wait for next character from terminal
		if (c != EOF) {
			// show on debugger console
			if ((c == 9) || (c == 10) || (c == 13) || ((c >= 32) && (c <= 126))) {
				DBG("%c", c);
				
				// Some terminal programs can be configured to send both
				// newline and carriage return when 'enter' key is pressed.
				// However not all can. As semihosting requires a newline
				// in order to flush its buffer, we add one just in case
				// the terminal doesn't send one.
				if (c==13) { DBG("\n"); } 
			}
			else {
				DBG(".");	// non-printable character
			}
		 
// Echo character back over UART as is, or incremented by 1, as per #define.
#ifdef INCREMENT_ECHO_BY_1
			if ((c >= 32) && (c <= 126)) {
				c++;			// only increment "standard" characters
			}
#endif	
		// resend received character back over UART to host		
			if ((c == 9) || (c == 10) || (c == 13) || ((c >= 32) && (c <= 126))) {
				UART0_Sendchar(c);
				
				// Some terminal programs can be configured to print both
				// a newline and a carriage return when they receive a carriage
				// return character. However not all can, so here we send a
				// newline in case. Otherwise the output for the next line will
				// be "staggered" part way across the screen.
				if (c==13) { UART0_Sendchar('\n'); } 
			}
			else {
				UART0_Sendchar('.'); // non-printable character
			}		
	
			i++ ;
		}
	}
	return 0;
}
