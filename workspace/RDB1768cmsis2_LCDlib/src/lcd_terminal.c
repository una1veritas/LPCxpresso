//*****************************************************************************
//   +--+       
//   | ++----+   
//   +-++    |  
//     |     |  
//   +-+--+  |   
//   | +--+--+  
//   +----+    Copyright (c) 2009,2010  Code Red Technologies Ltd.
//
// lcd_terminal.c - Routines for writing to the LCD as if it were a text terminal.
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
#include <string.h>

// Number of characters that can be printed across terminal screen
#define LCD_TERMINAL_SIZE_X 16
// Number of lines terminal screen can display
#define LCD_TERMINAL_SIZE_Y 8
// Width of each terminal character
#define LCD_TERMINAL_CHARSIZE_X 8
// Height of each terminal character
#define LCD_TERMINAL_CHARSIZE_Y 15
// Offset within LCD screen that terminal text will begin thus
// allowing text to be centred with equal gap top and bottom
#define LCD_TERMINAL_STARTOFFSET_Y 3
// LCD_TERMINAL_WRAP, if defined, will cause the terminal to wrap around
// to the top of the screen once it reaches the bottom. With it undefined,
// the screen will simply scroll up a line.
#undef LCD_TERMINAL_WRAP
//#define LCD_TERMINAL_WRAP 1

// Current position within terminal screen
static int LCD_terminal_current_x;
static int LCD_terminal_current_y;

// Array to store contents of the terminal screen
static char LCD_terminal_text [LCD_TERMINAL_SIZE_Y][LCD_TERMINAL_SIZE_X];

//************************

// Rewrites all of current terminal text (stored in LCD_terminal_text[][])
// to the LCD terminal in the requested color.
void LCD_PrintWholeTerminal (int color ,int bgcolor)
{
	int loopx, loopy;
	for (loopy = 0; loopy < LCD_TERMINAL_SIZE_Y; loopy++)
	{ // For each row....
		for (loopx = 0; loopx < LCD_TERMINAL_SIZE_X; loopx++)
		{	// For each column...
			LCD_PrintChar((loopx * LCD_TERMINAL_CHARSIZE_X),
					LCD_TERMINAL_STARTOFFSET_Y +(loopy * LCD_TERMINAL_CHARSIZE_Y),
					LCD_terminal_text [loopy][loopx],color, bgcolor);			
		}
	}
}
//************************

// Clear terminal window to background color, and reset position to top of window
void LCD_ResetTerminal (int bgcolor)
{
	int loopx, loopy;
	LCD_terminal_current_x = 0;		// Reset position to first column
	LCD_terminal_current_y = 0;		// Reset position to first row
	for (loopy = 0; loopy < LCD_TERMINAL_SIZE_Y; loopy++)
	{ // For each row...
		for (loopx = 0; loopx < LCD_TERMINAL_SIZE_X; loopx++)	
		{ //For each column...
			// Set current character to ' '
			LCD_terminal_text [loopy][loopx] = 32;  // SPACE
		}
	}
	// Clear terminal to requested background colour
	LCD_ClearScreen(bgcolor);  
}
//************************

// Write character to next position in terminal
void LCD_Print2Terminal (char inchar, int color ,int bgcolor)
{
	unsigned int loop;

	// Check to see if we have reached the bottom of the terminal screen
	if (LCD_terminal_current_y == LCD_TERMINAL_SIZE_Y)
	{
	// Yes? Then need to take action before we can print another character

#ifdef LCD_TERMINAL_WRAP
		// If LCD_TERMINAL_WRAP is defined, the terminal will wrap around
		// to the top of the screen once it reaches the bottom.
		LCD_terminal_current_y = 0;
#else
		// If LCD_TERMINAL_WRAP is not defined, the terminal will scroll
		// text up 1 line, loosing the previous top row.
		for (loop = 1; loop < LCD_TERMINAL_SIZE_Y; loop ++)
		{
			// Overwrite text in row 'loop-1' with text from row 'loop'
			memmove (&LCD_terminal_text [loop-1], &LCD_terminal_text [loop],LCD_TERMINAL_SIZE_X);
		}
		LCD_terminal_current_y --;	// Set current row pointer back 1
		for (loop = 0; loop < LCD_TERMINAL_SIZE_X; loop ++)
			LCD_terminal_text [LCD_terminal_current_y][loop] = 32;		// Fill last line with spaces
		// Reprint terminal contents after moving all the lines up 1
		LCD_PrintWholeTerminal(color, bgcolor);

#endif // LCD_TERMINAL_WRAP
	}

	if (inchar == 9) inchar = 32;	// Replace TAB by SPACE
	
	if ((inchar >= 32) && (inchar < 127))	// Printable character
	{
		// Store character into terminal array (used when terminal reprinted)
		LCD_terminal_text [LCD_terminal_current_y][LCD_terminal_current_x] = inchar;
		// Print the character at the next location
		LCD_PrintChar((LCD_terminal_current_x *LCD_TERMINAL_CHARSIZE_X),
				LCD_TERMINAL_STARTOFFSET_Y +(LCD_terminal_current_y * LCD_TERMINAL_CHARSIZE_Y),
				inchar,color, bgcolor);
		// Increment column pointer
		LCD_terminal_current_x++;
		// Have we reached the end of the current line ?
		if (LCD_terminal_current_x == LCD_TERMINAL_SIZE_X)
		{
			// Yes, then reset pointer to 1st column and move down a line
			LCD_terminal_current_x = 0;
			LCD_terminal_current_y++;			
		}
	}
	
	if (inchar == '\n') //newline
	{
		// Pad out rest of line with spaces and print them
		// (This helps with keeping background colours correct)
		for (loop = LCD_terminal_current_x; loop < LCD_TERMINAL_SIZE_X; loop ++)		
		{
			LCD_terminal_text [LCD_terminal_current_y][loop] = 32;
			LCD_PrintChar((loop * LCD_TERMINAL_CHARSIZE_X),
					LCD_TERMINAL_STARTOFFSET_Y + (LCD_terminal_current_y * LCD_TERMINAL_CHARSIZE_Y),
					32,color, bgcolor);			
		}
		// Move to start of next line
		LCD_terminal_current_x = 0;
		LCD_terminal_current_y++;					
	}

	if (inchar == '\r')	// carriage return
	{
		// Do nothing - carriage returns ignored
	}

	// Now check to see if we have now reached the bottom of the 
	// terminal screen
	if (LCD_terminal_current_y == LCD_TERMINAL_SIZE_Y)
	{
	// Yes? Then need to take action before we can print another character
	
#ifdef LCD_TERMINAL_WRAP
		// If LCD_TERMINAL_WRAP is defined, the terminal will wrap around
		// to the top of the screen once it reaches the bottom.
		LCD_terminal_current_y = 0;	
#else
		// If LCD_TERMINAL_WRAP is not defined, the terminal will scroll
		// text up 1 line, loosing the previous top row.
		for (loop = 1; loop < LCD_TERMINAL_SIZE_Y; loop ++)
		{
			// Overwrite text in row 'loop-1' with text from row 'loop'
			memmove (&LCD_terminal_text [loop-1], &LCD_terminal_text [loop],LCD_TERMINAL_SIZE_X);
		}
		LCD_terminal_current_y --;	// Set current row pointer back 1
		for (loop = 0; loop < LCD_TERMINAL_SIZE_X; loop ++)
			LCD_terminal_text [LCD_terminal_current_y][loop] = 32;		// Fill last line with spaces
		// Reprint terminal contents after moving all the lines up 1
		LCD_PrintWholeTerminal(color, bgcolor);
		
#endif // LCD_TERMINAL_WRAP
	}

	
}
//************************

// Write string out to terminal, in appropriate color, moving to new line first if required
// (startnewline == LCD_TERMINAL_NL (1))
void LCD_PrintString2Terminal(char *pcString, unsigned int startnewline, int color ,int bgcolor)
{
    unsigned int loop, middleofstring;
    unsigned char c;
    int iStrLen, i;
	
    // Calculate length of string to be displayed
	iStrLen = strlen (pcString);

	middleofstring = 0;  // Will be set to 1 once we have reached a printable character
	
	// First of all check to see if user has requested that string begins on a  new line
	// (and we aren't already at the start of a line....)
	if ((startnewline == LCD_TERMINAL_NL) && (LCD_terminal_current_x > 0))
	{
		// Pad out rest of line with spaces and print them
		// (This helps with keeping background colours correct)
		for (loop = LCD_terminal_current_x; loop < LCD_TERMINAL_SIZE_X; loop ++)		
		{
			LCD_terminal_text [LCD_terminal_current_y][loop] = 32;
			LCD_PrintChar((loop * LCD_TERMINAL_CHARSIZE_X),
					LCD_TERMINAL_STARTOFFSET_Y + (LCD_terminal_current_y * LCD_TERMINAL_CHARSIZE_Y),
					32,color, bgcolor);			
		}
		// Move to start of next line
		LCD_terminal_current_x = 0;
		LCD_terminal_current_y++;					
	}		

	// For each character in the string.....
	for(i=0;i<iStrLen;i++)
	{
		c = pcString[i];
		if(c==0)		// We have reached the end of the (0-terminated) string
			break;		
		if (c == '\n')	// New line character
		{
			// If we are in the middle of the string, and at the 1st column in a row,
			// then we will skip any additional newline characters.
			if (!((middleofstring == 1) && (LCD_terminal_current_x == 0)))
			{
				// Pad out rest of line with spaces and print them
				// (This helps with keeping background colours correct)
				for (loop = LCD_terminal_current_x; loop < LCD_TERMINAL_SIZE_X; loop ++)		
				{
					LCD_terminal_text [LCD_terminal_current_y][loop] = 32;
					LCD_PrintChar((loop * LCD_TERMINAL_CHARSIZE_X),
							LCD_TERMINAL_STARTOFFSET_Y + (LCD_terminal_current_y * LCD_TERMINAL_CHARSIZE_Y),
							32,color, bgcolor);			
				}
								
				// Move to start of next line
				LCD_terminal_current_x = 0;
				LCD_terminal_current_y++;					
			}
		}
		if ((c >= 32) && (c < 127))		// Printable character
		{
			middleofstring = 1;
			LCD_Print2Terminal (c, color, bgcolor);			
		}
	}
	
}
