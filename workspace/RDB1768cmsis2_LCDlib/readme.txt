Code Red Technologies RDB1768 Board - LCDLib
==============================================

[ Note that this project requires the CMSISv2p00_LPC17xx library 
  project to exist in the same workspace. ]
  
This library project provides a set of functions that can be used
to access the LCD screen on the RDB1768 development board.

lcd_driver.c
 - Initialisation function
 - Clear screen function
 - Low level driver functions

lcd_shapes.c
- Line drawing function
- Circle and rectangle plotting functions (filled and unfilled)
- Individual point plotting function

lcd_text.c
- Function to write strings to the LCD
- Function to write individual chars to the LCD
- Related low level functions

lcd_terminal.c
- Functions to print characters and strings to LCD, as if it were
  a terminal window.
- Related low level functions
  
system_fixed_be_8_15.c
- 8x15 font definition used for text functions

lcd_bitmap.c
- Function to plot 24-bit image defined in C char array to the LCD
- Function to plot 16-bit image defined in C char array to the LCD
See bitmap_readme.txt for more information on displaying images.

The associated RDB1768cmsis2_LCDdemo project shows examples of these
functions being invoked.


~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Note that this example project is intended for use with Red Suite /
LPCXpresso IDE v4.0 or later.

Use of this project with earlier versions of the Code Red IDE is 
not recommended or supported.
