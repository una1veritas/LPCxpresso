//*****************************************************************************
//   +--+       
//   | ++----+   
//   +-++    |  
//     |     |  
//   +-+--+  |   
//   | +--+--+  
//   +----+    Copyright (c) 2009 Code Red Technologies Ltd. 
//
// lcd_text.h  - header for a lcd_text.c - containing functions to write
// text to the LCD screen of the RDB1768 development board.
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

// Routine to write a single character to screen in the font pointed
// to by pBitMap.  This routine is intended to be used via the 
// LCD_PrintChar() and LCD_PrintString() routines, rather than called
// directly from user code.

void LCD_WriteBitMap8x15(int x, int y, int height, int width, 
								unsigned char *pBitMap, int color, int bgcolor);

// Prints the character 'c' to the LCD in the appropriate color.
void LCD_PrintChar(int x, int y, unsigned char c, int color ,int bgcolor );

// Prints the string to the LCD in the appropriate color.
void LCD_PrintString(int x, int y, char *pcString, int color, int bgcolor);
