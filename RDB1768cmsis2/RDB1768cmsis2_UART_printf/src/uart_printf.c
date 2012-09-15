//*****************************************************************************
//   +--+
//   | ++----+
//   +-++    |
//     |     |
//   +-+--+  |
//   | +--+--+
//   +----+    Copyright (c) 2010-11 Code Red Technologies Ltd.
//
// uart_printf.c - printf/scanf over UART example project for RDB1768
 //                development board
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
#include <stdio.h>

#include <cr_section_macros.h>
#include <NXP/crp.h>

// Variable to store CRP value in. Will be placed automatically
// by the linker when "Enable Code Read Protect" selected.
// See crp.h header for more information
__CRP const unsigned int CRP_WORD = CRP_NO_CRP ;

char str[30];

int main(void) {

	UART0_Init(57600); // Setup UART0 to 57600 baud

	UART0_PrintString ("\r\nRDB1768 UART retargeted printf/scanf\r\n");
	UART0_PrintString ("====================================\r\n");
	UART0_PrintString ("First of all, sending output using direct UART printstring routine\r\n");

	printf ("Now using printf/scanf retargeted through UART...\r\n");

	printf("Enter your name : ");

	scanf ("%s",str);
	printf("Hello %s !\r\n", str);
	
	printf(" ** Finished - entering infinite loop **\r\n");

	// Enter an infinite loop, just incrementing a counter
	volatile static int i = 0 ;
	while(1) {
		i++ ;
	}
	return 0 ;
}
