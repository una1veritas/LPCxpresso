//*****************************************************************************
//   +--+       
//   | ++----+   
//   +-++    |  
//     |     |  
//   +-+--+  |   
//   | +--+--+  
//   +----+    Copyright (c) 2009 Code Red Technologies Ltd. 
//
// lcddemoh.c - header file for RDB1768 development board LCD demo project
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

#ifndef __LCDDEMO_H
#define __LCDDEMO_H

// From lcddemo_main.c
void main_delay (int);

// From lcddemo_graphics.c
void cycle_graphics(void);
void bounce_logo (void);

// From lcddemo_shapes.c
void draw_shapes (void);

// From lcddemo_terminal.c
void text_terminal (void);

#define PAUSE_ANIM	250
#define PAUSE_SHORT	2000
#define PAUSE_MEDIUM 4000
#define PAUSE_LONG  8000

#endif  // __LCDDEMO_H