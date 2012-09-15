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
// Include headers for various bitmaps used in demo
#include "arm98x45.h"
#include "codered128x37.h"
#include "cortex128x57.h"
#include "crlogo35x51.h"
#include "crlogo69x102.h"
#include "nxp128x38.h"






void cycle_graphics (void)
{
	LCD_PlotBitmap (29, 4, crlogo69x102_pixel_data ,crlogo69x102_width, crlogo69x102_height);
	LCD_PrintString(0,110,"RDB1768 LCD Demo", COLOR_RED, COLOR_YELLOW);

	main_delay(PAUSE_SHORT);
	// Print a countdown on screen using individual characters
	LCD_PrintChar(110,10, '3',COLOR_YELLOW, COLOR_BLACK);	
	main_delay(PAUSE_SHORT);			// Small delay
	LCD_PrintChar(110,10, '2',COLOR_YELLOW, COLOR_BLACK);	
	main_delay(PAUSE_SHORT);			// Small delay
	LCD_PrintChar(110,10, '1',COLOR_YELLOW, COLOR_BLACK);
	main_delay(PAUSE_SHORT);			// Small delay
	
	LCD_ClearScreen(0);	// Clear screen ready for next part of demo

	
	LCD_PrintString(10,10,"Featuring the", COLOR_RED, COLOR_BLACK);
	LCD_PrintString(14,30,"LPC1768 MCU", COLOR_RED, COLOR_BLACK);
	LCD_PrintString(40,50,"from", COLOR_RED, COLOR_BLACK);
	LCD_PlotBitmap (0, 80, nxp128x38_pixel_data ,nxp128x38_width, nxp128x38_height);
		
	main_delay(PAUSE_LONG);
	LCD_ClearScreen(0);

	LCD_PrintString(10,15,"Containing the", COLOR_RED, COLOR_BLACK);
	LCD_PrintString(14,35,"Cortex-M3 CPU", COLOR_RED, COLOR_BLACK);
	LCD_PlotBitmap (0, 60, cortex128x57_pixel_data, cortex128x57_width, cortex128x57_height);	

	main_delay(PAUSE_LONG);
	LCD_ClearScreen(0);
	
	LCD_PrintString(36,80,"Powered !", COLOR_BLUE, COLOR_BLACK);	
	LCD_PlotBitmap (15,30, arm98x45_pixel_data ,arm98x45_width, arm98x45_height);
	
	
	main_delay(PAUSE_LONG);
	LCD_ClearScreen(0);

	LCD_PlotBitmap (0, 0, codered128x37_pixel_data ,codered128x37_width, codered128x37_height);	

	LCD_PrintString(35,45,"Software", COLOR_RED, COLOR_BLACK);
	LCD_PrintString(35,65,"compiled", COLOR_RED, COLOR_BLACK);	
	LCD_PrintString(45,85,"using", COLOR_RED, COLOR_BLACK);
	LCD_PrintString(10,105,"Code Red tools", COLOR_RED, COLOR_BLACK);

	main_delay(PAUSE_LONG);	
	LCD_ClearScreen(0);

}


void bounce_logo (void)
{
	int yloc, topy, boty, leftx, rightx;
	
	LCD_PrintString(0,0,"Simple animation",COLOR_RED, COLOR_YELLOW);
	
	// Print logo in initial position underneath text
	LCD_PlotBitmap (46, 20, crlogo35x51_pixel_data ,crlogo35x51_width, crlogo35x51_height);

	main_delay(PAUSE_SHORT);

	// Now repeatedly print logo to screen, each time one line
	// lower down the screen, and each time erasing the top line
	// of the previous copy of the logo (the other lines will be 
	// overwritten by the new version. Repeat until we are at the
	// bottom of the screen (allowing for logo height, and last 
	// line of screen = 127).
	// Then print logo coming back up the screen


	topy = 21;
	boty = 127-crlogo35x51_height;
	leftx = (127 - crlogo35x51_width) / 2;
	rightx = leftx + crlogo35x51_width; 

	for (yloc = topy; yloc < boty; yloc++)  
	{
		LCD_FilledRect (leftx,rightx,yloc-1,yloc-1,COLOR_BLACK);			
		LCD_PlotBitmap (leftx, yloc, crlogo35x51_pixel_data ,crlogo35x51_width, crlogo35x51_height);
		main_delay(PAUSE_ANIM);
	}

	main_delay(PAUSE_SHORT);		// Small delay

	// Now repeatedly print the logo moving back up the screen

	for (yloc = boty-1; yloc > topy; yloc--)
	{
		LCD_FilledRect (leftx,rightx,yloc+crlogo35x51_height+1,yloc+crlogo35x51_height+1,COLOR_BLACK);
		LCD_PlotBitmap (leftx, yloc, crlogo35x51_pixel_data ,crlogo35x51_width, crlogo35x51_height);
		main_delay(PAUSE_ANIM);
		
	}

	main_delay(PAUSE_SHORT);		// Small delay

	LCD_ClearScreen(0);
}
		