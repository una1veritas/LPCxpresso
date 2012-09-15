LPC1768 USB host Mass Storage Demo - CMSIS 2.0 version
======================================================

[ Note that this project requires CMSISv2p00_LPC17xx library 
  project to exist in the same workspace. ]

NXP Semiconductors and OnChip Technologies have partnered to 
provide USBHostLite software for the LPC1000, LPC2000, and LPC3000
families of microcontrollers with USB host capability.

USBHostLite provides a USB host mass storage class (MSC) example.
Further details, including the original source code and a 
supporting application note, can be found at: 

  http://www.standardics.nxp.com/support/software/usb.host.msc/
  
This project provides a build of USBHostLite which will run on
the RDB1768 development board. The code itself is basically
unchanged from the original implementation by NXP for the Keil 
MCB1700 board. The main change is the replacement of the original
"startup_LPC17xx.s" file with Red Suite's "cr_startup_lpc17.c"

When executed, the code will read the flash pen drive plugged 
into the USB host port of the RDB1768 board, looking for a file 
called msread.txt. It will then copy the contents of this file into
a file on the flash pen drive called mswrite.txt

Status information from the program is output via the UART of the
board, thus requiring a terminal program to be run on your PC 
configured to 115200 baud.

The executable produced by this project has been tested on the
RDB1768 board. However we would expect that it should still 
function on the Keil MCB1700 board - see the "NXP_Readme.txt"
file contained in within this project for more information.


Note that this example makes use of the CMSIS system and processor
core code and header files. For more information on CMSIS, please
see the "Cortex Microcontroller Software Interface Standard" pages
at:

  http://www.onarm.com/

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Note that this example project is intended for use with Red Suite /
LPCXpresso IDE v4.0 or later.

Use of this project with earlier versions of the Code Red IDE is 
not recommended or supported.



