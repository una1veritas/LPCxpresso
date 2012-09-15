//*****************************************************************************
//   +--+       
//   | ++----+   
//   +-++    |  
//     |     |  
//   +-+--+  |   
//   | +--+--+  
//   +----+    Copyright (c) 2009 Code Red Technologies Ltd. 
//
// lcddemo_graphics.c demonstrates the use of the bitmap routines for the
// LCD display on the RDB1768 development board.
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

#include "lcd.h"
#include "lcddemo.h"
#include "string.h"


char individual[]="individual\ncharacters\n";

void print_dots (unsigned int numdots)
{
	unsigned int loop;
	for (loop = 1; loop <= numdots; loop++)
	{
		LCD_Print2Terminal ('.', COLOR_BLUE, COLOR_YELLOW);
		main_delay(PAUSE_SHORT >> 1);		
	}
}

void text_terminal (void)
{
	int iStrLen, loop;
	char c;
	iStrLen = strlen (individual);

	LCD_ResetTerminal(COLOR_YELLOW);
	LCD_PrintString2Terminal ("LCD Terminal\n", LCD_TERMINAL_NoNL,COLOR_RED, COLOR_BLACK);
	
	main_delay(PAUSE_MEDIUM);
	LCD_PrintString2Terminal ("\nPrint strings or\n", LCD_TERMINAL_NoNL,COLOR_BLUE, COLOR_YELLOW);

	main_delay(PAUSE_SHORT >> 1);
	for(loop=0; loop<iStrLen; loop++)
	{
		c = individual[loop];
		if(c==0)
			break;		// We have reached the end of the (0-terminated) string
		else
		{
			LCD_Print2Terminal (c, COLOR_BLUE, COLOR_YELLOW);
			main_delay(PAUSE_SHORT >> 1);
		}
	}
	main_delay(PAUSE_SHORT >> 1);
	LCD_PrintString2Terminal ("\nTerminal scrolls\nwhen end of", LCD_TERMINAL_NL,COLOR_BLUE, COLOR_YELLOW);	
	print_dots(5);

	LCD_PrintString2Terminal ("screen is", LCD_TERMINAL_NL,COLOR_BLUE, COLOR_YELLOW);	
	print_dots(7);	
	
	LCD_PrintString2Terminal ("reached", LCD_TERMINAL_NL,COLOR_BLUE, COLOR_YELLOW);		

	
	main_delay(PAUSE_LONG);	

	LCD_ClearScreen(0);
}
	
		