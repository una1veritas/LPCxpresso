//*****************************************************************************
//   +--+       
//   | ++----+   
//   +-++    |  
//     |     |  
//   +-+--+  |   
//   | +--+--+  
//   +----+    Copyright (c) 2009 Code Red Technologies Ltd. 
//
// lcd_terminal.h - Routines for writing to the LCD as if it were a text terminal.
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

#ifndef LCD_TERMINAL_H_
#define LCD_TERMINAL_H_

// Used in calls to LCD_PrintString2Terminal for parameter 'startnewline' 
// LCD_TERMINAL_NL - newline at start of line is required
#define LCD_TERMINAL_NL 1
// LCD_TERMINAL_NoNL - no newline at start of line is required
#define LCD_TERMINAL_NoNL 0

/**************************************
 * LCD Terminal Function Declarations *
 * ************************************/

// Rewrites all of current terminal text to the LCD terminal in the appropriate color.
void LCD_PrintWholeTerminal (int color ,int bgcolor);

// Write character to next position in terminal
void LCD_Print2Terminal (char inchar, int color ,int bgcolor);

// Write string out to terminal, in appropriate color, moving to new line first if required
void LCD_PrintString2Terminal (char *pcString, unsigned int startnewline, int color ,int bgcolor);

// Clear terminal window to background color, and reset position to top of window
void LCD_ResetTerminal (int bgcolor);

#endif /*LCD_TERMINAL_H_*/