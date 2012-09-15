Code Red Technologies RDB1768 Board - SysTick Demo
==================================================

[ Note that this project requires the CMSISv2p00_LPC17xx library 
  project to exist in the same workspace. ]
  
This simple project shows how the SysTick timer built in
to the NVIC of the Cortex-M3 processor core contained within
the LPC1768 microcontroller can be set up.

Download the project to the board and run it. The state of
the user leds will toggle every second.

The code to access the LEDs (leds.h and leds.c) is taken from the
RDB1768cmsis2_LedFlash project. See that project for more examples of 
how to use this code.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Note that this example project is intended for use with Red Suite /
LPCXpresso IDE v4.0 or later.

Use of this project with earlier versions of the Code Red IDE is 
not recommended or supported.