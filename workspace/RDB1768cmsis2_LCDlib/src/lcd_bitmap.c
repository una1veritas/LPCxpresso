//*****************************************************************************
//   +--+       
//   | ++----+   
//   +-++    |  
//     |     |  
//   +-+--+  |   
//   | +--+--+  
//   +----+    Copyright (c) 2009 Code Red Technologies Ltd. 
//
// logo.c contains a function to print the graphical logo
// defined in logocr.h to the LCD.
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
#include "lcd_driver.h"
#include "lcd_commands.h"

// Displays the 24bit (RGB888) bitmap pointed to by *pixels, and of
// size (xlen * ylen) at the location (x,y). Conversion to 16bit color
// is carried out on the fly.
// The routine assumes that the bitmap will fit on the LCD screen.
void LCD_PlotBitmap24 (int x, int y, const unsigned char *pixels, int xlen, int ylen)
{
	int j,r,g,b,col24, col16;

    LCDdriver_WriteCom(DD_CASET); 	// Set the column address
    LCDdriver_WriteData(x);		// min address
    LCDdriver_WriteData(x+xlen-1);		// max address
    LCDdriver_WriteCom(DD_RASET);	// Set the row address
	// Screen is offset by 1 in Y axis in relation to controller RAM buffer
    LCDdriver_WriteData(y + 1);	// min address
    LCDdriver_WriteData(y+ylen-1 + 1);	// max address
    LCDdriver_WriteCom(DD_RAMWR);	// RAM Write command
	 
    for (j=0; j < xlen*ylen*3; j+=3)
    {
		r= pixels [j];		// Read the red value for pixel
		g= pixels [j+1];	// Read the green value for pixel
		b= pixels [j+2];	// Read the blue value for the pixel
		col24= (r<<16)|(g<<8)|b;	// Merge into 24 bit value
		col16 = TRANSLATE24BIT_TO_RGB565(col24);	// Convert to 16bit
    	LCDdriver_WriteData(col16 >> 8);	// top 8 bits of RGB565 color
    	LCDdriver_WriteData(col16);			// bottom 8 bits of RGB565 color
   	
    }
}

// Displays the 16bit (RGB565) bitmap pointed to by *pixels, and of size 
// (lenx * leny) at the location (x,y).
// The routine assumes that the bitmap will fit on the LCD screen.
void LCD_PlotBitmap (int x, int y, const unsigned short *pixeldata, int xlen, int ylen)
{	
	int j, col16;
	LCDdriver_WriteCom(DD_CASET); 	// Set the column address
	LCDdriver_WriteData(x);		// min address
	LCDdriver_WriteData(x+xlen-1);		// max address
	LCDdriver_WriteCom(DD_RASET);	// Set the row address
	// Screen is offset by 1 in Y axis in relation to controller RAM buffer
	LCDdriver_WriteData(y + 1);	// min address
	LCDdriver_WriteData(y+ylen-1 + 1);	// max address
	LCDdriver_WriteCom(DD_RAMWR);	// RAM Write command
 
    for (j=0; j < xlen*ylen; j++)
    {
		col16 = pixeldata [j];	// Read the pixel data

    	LCDdriver_WriteData(col16 >> 8);	// top 8 bits of RGB565 color
    	LCDdriver_WriteData(col16);			// bottom 8 bits of RGB565 color
    }	
}