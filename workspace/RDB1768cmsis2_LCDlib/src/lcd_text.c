//*****************************************************************************
//   +--+       
//   | ++----+   
//   +-++    |  
//     |     |  
//   +-+--+  |   
//   | +--+--+  
//   +----+    Copyright (c) 2009 Code Red Technologies Ltd. 
//
// lcd.c contains various routines to print text to the LCD display on the 
// RDB1768 development board.
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

//#define USE_STRLEN 1

#ifdef USE_STRLEN
#include <string.h>
#endif

// Routine to write a single character to screen in the font pointed
// to by pBitMap.  This routine is intended to be used via the 
// LCD_PrintChar() and LCD_PrintString() routines, rather than called
// directly from user code.
void LCD_WriteBitMap8x15(int x, int y, int height, int width, 
							unsigned char *pBitMap, int color, int bgcolor)
{
	int xmax = x + width - 1;	// start at zero
	int ymax = y + height - 1;	// start at zero
	int iRow, iCol;
	unsigned char ucRowData;
	
    LCDdriver_WriteCom(DD_CASET);	// Column address set
    LCDdriver_WriteData(x);		// Start column
    LCDdriver_WriteData(xmax);		// End column
    LCDdriver_WriteCom(DD_RASET);	// Row address set
	// Screen is offset by 1 in Y axis in relation to controller RAM buffer
    LCDdriver_WriteData(y+1);		// Start row
    LCDdriver_WriteData(ymax+1);		// End row
    LCDdriver_WriteCom(DD_RAMWR);	// Memory write
    
    
    for(iRow=0;iRow<height;iRow++)
    {
    	ucRowData = *pBitMap++;
    	
    	for(iCol=0;iCol<width;iCol++)
    	{

    		// Look at each input bitmap bit
    		// and write as a black-pixel or
    		// a color-pixel.
    		
    		if(ucRowData & 0x80)  // 'color pixel'
    		{
            	LCDdriver_WriteData(color >> 8); 
            	LCDdriver_WriteData(color);
    		}
    		else				// background pixel
    		{
    			LCDdriver_WriteData(bgcolor >> 8);
            	LCDdriver_WriteData(bgcolor);
    		}
        	
        	ucRowData = ucRowData<<1;
    	}
    }

}


// Prints the character 'c' to the LCD in the appropriate color.
void LCD_PrintChar(int x, int y, unsigned char c, int color, int bgcolor )
{
    const unsigned char index = font_index_table[c];
    const unsigned int offset = index * 15;
    unsigned char *pData = (unsigned char *)&font_data_table[offset];	

    LCD_WriteBitMap8x15(x, y, 15, 8, pData, color, bgcolor);
}



// Prints the 0 terminated string to the LCD in the appropriate color.
void LCD_PrintString(int x, int y, char *pcString, int color, int bgcolor)
{
    unsigned char index;
    unsigned int offset;
    unsigned char *pData;
    unsigned char c;
	int i;
#ifdef USE_STRLEN
    int iStrLen;	
 	iStrLen = strlen (pcString);
		
 		for(i=0;i<iStrLen;i++)
 		{
 			if(c==0)
 				break;
 			index = font_index_table[c];
 		    offset = index * 15;
 		    pData = (unsigned char *)&font_data_table[offset];

 		    LCD_WriteBitMap8x15(x, y, 15, 8, pData, color, bgcolor);	
 		    x += 8;
 		}
 #else
	i = 0;
	c = pcString[i++];

	if (c != 0)
	{ 
		do {
			index = font_index_table[c];
		    offset = index * 15;
		    pData = (unsigned char *)&font_data_table[offset];

		    LCD_WriteBitMap8x15(x, y, 15, 8, pData, color, bgcolor);	
		    x += 8;
			c = pcString[i++];			
		} while (c != 0);
	}
#endif		

}