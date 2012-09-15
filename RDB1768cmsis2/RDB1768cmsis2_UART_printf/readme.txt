Code Red Technologies RDB1768 Board - UART printf/scanf Example
===============================================================

[ Note that this project requires the CMSISv2p00_LPC17xx library 
  project to exist in the same workspace. ]

This example shows how the Redlib C library functions printf and
scanf functions, which normally carry out I/O over the debug 
"semihosting" mechanism to the debugger console window can be
retargeted to instead use the LPC1768/RDB1768 UART instead.

To run this example, you will need to connect the board to your
PC using a serial cable, and use a terminal program on your PC,
such as hyperterminal.

Before executing the example on the board, you should start
up your terminal program on your PC, so that you see the initial
ouput from the example. When configuring your terminal program,
you should set it to:
- 57600 baud
- 8 data bits
- No parity
- 1 stop bit
- No flow control
- Echo typed characters locally. (You will then be able to see
  the character you type, as well as the character returned by
  the code running on the board.)

Note that the symbol "CR_INTEGER_PRINTF" is defined by the 
project. This tells the Redlib C library that the none-floating
point version of printf can be linked in, which reduces the
size of the application.

The symbol "CR_PRINTF_CHAR" is also defined by the project. When
the project is built with a version of the tools that uses 
"Redlib_v2" (see below), this will cause a character based printf
routine to be used, rather than one that prints strings out in one
operation. Although doing this is not essential, it does provide a
small decrease in code size, and also reduces heap usage.

Note about semihosting interface
--------------------------------
With the introduction of 'Redlib_v2', the inteface used by the
semihosting stub layer at the bottom of Redlib changed. Originally
the functions used to write a character and read a character were
__write and __readc. In 'Redlib_v2' (first made available in  
"LPCXpresso for Linux v3.7.x" in September 2010), the interface 
changed slightly, and the equivalent functions are now called 
__sys_write and __sys_readc.

The code in this example that implements these low level functions
(in retarget.c) automatically detects which semihosting interface
is in use by looking at the define __REDLIB_INTERFACE_VERSION__.
This was not defined in the original Redlib, and is defined as 
20000 for Redlib_v2. 

You will need to include one of the standard  C header files for 
this define to be set. Note that the public betas of LPCXpresso
for Linux 3.7.x did not define __REDLIB_INTERFACE_VERSION__. If
you are using such a beta, then it is recommended that you update
to a full release version.

If the wrong semihosted interface is used by your code, then the
most likely result is a hard fault at runtime.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Note that this example project is intended for use with Red Suite /
LPCXpresso IDE v4.0 or later.

Use of this project with earlier versions of the Code Red IDE is 
not recommended or supported.