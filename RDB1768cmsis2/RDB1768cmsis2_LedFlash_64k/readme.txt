Code Red Technologies RDB1768 Board - User Leds Demo (64KB)
====================================================

This project is a modified version of the original 
RDB1768cmsis2_LedFlash project. The only difference is that this
version has been configured to build to run from address 0x10000
(64KB) so that it is suitable for use with the 
RDB1768cmsis2_usb_bootloader.

-------------------------------------

[ Note that this project requires the CMSISv2p00_LPC17xx library 
  project to exist in the same workspace. ]

This demonstration project show how the user leds, LED_2 to
LED_5, of the RDB1768 be accessed.

The project defines a number of functions to switch the leds
on and off, individually and as a group, and also to invert the
current state of the leds. The demonstration itself then calls
these functions to flash the leds in various combinations.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Note that this example project is intended for use with Red Suite /
LPCXpresso IDE v4.0 or later.

Use of this project with earlier versions of the Code Red IDE is 
not recommended or supported.