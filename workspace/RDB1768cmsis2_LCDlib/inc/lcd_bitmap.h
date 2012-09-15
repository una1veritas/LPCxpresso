//*****************************************************************************
//   +--+       
//   | ++----+   
//   +-++    |  
//     |     |  
//   +-+--+  |   
//   | +--+--+  
//   +----+    Copyright (c) 2009 Code Red Technologies Ltd. 
//
// lcd_bitmap.h  - header for a lcd_bitmap.c - containing functions to display
// 24bit and 16bit images on the LCD screen of the RDB1768.
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

// Displays the 24bit (RGB888) bitmap pointed to by *pixels, and of
// size (xlen * ylen) at the location (x,y). Conversion to 16bit color
// is carried out on the fly.
// The routine assumes that the bitmap will fit on the LCD screen.
void LCD_PlotBitmap24 (int x, int y, const unsigned char *pixels, int xlen, int ylen);

// Displays the 16bit (RGB565) bitmap pointed to by *pixels, and of size 
// (lenx * leny) at the location (x,y).
// The routine assumes that the bitmap will fit on the LCD screen.
void LCD_PlotBitmap (int x, int y, const unsigned short *pixeldata, int xlen, int ylen);


