//*****************************************************************************
//   +--+       
//   | ++----+   
//   +-++    |  
//     |     |  
//   +-+--+  |   
//   | +--+--+  
//   +----+    Copyright (c) 2009 Code Red Technologies Ltd. 
//
// lcd_shapes.h  - header for a lcd_shapes.c - containing functions to display
// a variety of shapes and lines to the LCD screen of the RDB1768.
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


// Routine to draw a filled rectangle to the LCD.
// Two corners of rectangle are at (xmin,ymin) and (xmax,ymax).
// The Rectangle is filled with the RGB565 color specified
void LCD_FilledRect(int xmin,int xmax,int ymin,int ymax,int color);

// Routine to draw an unfilled rectangle to the LCD.
// Two corners of rectangle are at (xmin,ymin) and (xmax,ymax).
// The Rectangle is drawn in the RGB565 color specified
void LCD_Rect(int xmin,int xmax,int ymin,int ymax,int color);

// Plot a point on the screen in the 6:5:6 color format
void LCD_PlotPoint(int x,int y,int color);

// Routine to draw a filled circle to the LCD.
// The centre of the circle is at (x0,y0) and the circle has the 
// specifed radius. The circle is filled with the RGB565 color 
// The circle is drawn using the "Midpoint circle algorithm", 
// also known as "Bresenham's circle algorithm". In order to fill
// the circle, the algorithm has been modifed to draw a line between
// each two points, rather than plotting the two points individually.
void LCD_FilledCircle (int x0, int y0, int radius, int color);

// Routine to draw an unfilled circle to the LCD.
// The centre of the circle is at (x0,y0) and the circle has the 
// specifed radius. The circle is drawn in the RGB565 color 
// The circle is drawn using the "Midpoint circle algorithm", 
// also known as "Bresenham's circle algorithm". 
void LCD_Circle (int x0, int y0, int radius, int color);

// Routine to draw a line in the RGB565 color to the LCD.
// The line is drawn from (xmin,ymin) to (xmax,ymax).
// The algorithm used to draw the line is "Bresenham's line
// algorithm". 
void LCD_Line (int xmin,int xmax,int ymin,int ymax,int color);
