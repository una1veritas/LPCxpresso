Code Red Technologies RDB1768 Board - External Interrupts Demo
==============================================================

[ Note that this project requires the CMSISv2p00_LPC17xx library 
  project to exist in the same workspace. ]
  
This demonstration project show how the ISP button on the RDB1768
can be used to generate external interrupts via pin P2.10 of the 
LPC1768.

When first executed, the program will turn on two of the four LEDs
on the board (2 and 3). Then when the ISP button is pressed, the 
state of the four LEDs will be inverted by the EINT0 interrupt 
handler. Thus the first time the ISP button is pressed, LEDs 2 and
3 will turn off, and LEDs 4 and 5 will turn on.

The code to access the LEDs (leds.h and leds.c) is taken from the
RDB1768cmsis_LedFlash project. See that project for examples of 
how to use this code.


[Note that the external interrupt functionality provided by the ISP
button in this project is separate from the ISP_BOOT functionality 
provided when the ISP button is pressed in conjunction with the 
RST button.]

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Note that this example project is intended for use with Red Suite /
LPCXpresso IDE v4.0 or later.

Use of this project with earlier versions of the Code Red IDE is 
not recommended or supported.