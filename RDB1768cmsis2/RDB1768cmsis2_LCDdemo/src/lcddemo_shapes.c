//*****************************************************************************
//   +--+       
//   | ++----+   
//   +-++    |  
//     |     |  
//   +-+--+  |   
//   | +--+--+  
//   +----+    Copyright (c) 2009 Code Red Technologies Ltd. 
//
// lcddemo_shapes.c demonstrates the use of the shape drawing routines for the
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



void main_delay (int);

void draw_shapes (void)
{
	LCD_PrintString(35,25,"Demo of",COLOR_BLUE, COLOR_YELLOW);
	LCD_PrintString(20,45,"LCD Library", COLOR_BLUE, COLOR_YELLOW);
	LCD_PrintString(10,65,"Shape and Line" ,COLOR_BLUE, COLOR_YELLOW);
	LCD_PrintString(0,85,"Drawing routines",COLOR_BLUE, COLOR_YELLOW);

	main_delay(PAUSE_LONG); 			// Small delay
	LCD_ClearScreen(0);
	
	// Draw an unfilled rectangle
	LCD_PrintString(0,0,"Rectangle",COLOR_BLUE, COLOR_BLACK);
	LCD_Rect (0, 127, 20, 55, COLOR_RED);	
	main_delay(PAUSE_MEDIUM); 			// Small delay
	
	// Draw a filled rectangle
	LCD_PrintString(0,60,"Filled Rectangle",COLOR_BLUE, COLOR_BLACK);
	LCD_FilledRect (0,127,80,115,COLOR_WHITE);		
	
	main_delay(PAUSE_LONG); 			// Small delay
	LCD_ClearScreen(0);
	
	// Draw an unfilled circle
	LCD_PrintString(0,0,"Circle",COLOR_BLUE, COLOR_BLACK);
	LCD_Circle (96, 32, 30, COLOR_BLUE);
	main_delay(PAUSE_MEDIUM); 			// Small delay

	// Draw a filled circle
	LCD_PrintString(0,64,"Filled",COLOR_BLUE, COLOR_BLACK);
	LCD_PrintString(0,84,"Circle",COLOR_BLUE, COLOR_BLACK);
	LCD_FilledCircle (96, 96, 30, COLOR_BLUE);

	main_delay(PAUSE_LONG); 			// Small delay
	LCD_ClearScreen(0);
	
	// Draw lines
	LCD_PrintString(0,0,"And lines...",COLOR_BLUE, COLOR_BLACK);	
	main_delay(PAUSE_MEDIUM);
	LCD_Line (0,64,16,16,COLOR_RED);
	LCD_Line (64,64,16,72,COLOR_RED);
	LCD_Line (64,127,72,72,COLOR_RED);	
	LCD_Line (127,127,72,127,COLOR_RED);

	main_delay(PAUSE_MEDIUM);
	
	LCD_Line (64,127,127,127,COLOR_RED);
	LCD_Line (64,64,72,127,COLOR_RED);
	LCD_Line (0,64,72,72,COLOR_RED);
	LCD_Line (0,0,16,72,COLOR_RED);
	
	main_delay(PAUSE_MEDIUM);	
	
	LCD_Line (0,127,16,127,COLOR_BLUE);

	main_delay(PAUSE_LONG);
		
	LCD_ClearScreen(0);	// Clear screen ready for next part of demo
}
