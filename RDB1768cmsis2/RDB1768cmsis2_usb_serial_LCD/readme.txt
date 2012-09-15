Code Red Technologies RDB1768 Board - USB_Serial_LCD Example
============================================================

LPCUSB
------
The USB stack and associated examples provided with RDB1768 board are
based on the open source LPCUSB stack, originally written for the NXP
LPC214x microcontrollers.

The original sources for the USB stack and examples can be found at:

  http://sourceforge.net/projects/lpcusb/

with additional information at:

  http://wiki.sikken.nl/index.php?title=LPCUSB

We have tried to keep the changes to the codebase down to a minimum, and
have commented where changes have been made as much as possible

Support
-------
This example project is based on an open source stack LPCUSB stack.
Code Red can provide support on using this project as supplied to 
users with a valid support contract with us. But if you require 
assistance on the general use of the stack or on extending the 
example, then we would recommend that you raise your questions
to an appropriate community forum, such as....

http://tech.groups.yahoo.com/group/lpc2000/messages


USB_Serial_LCD Example
----------------------
This example is based on the LPCUSB USB_Serial example, but has been 
extended so that the code outputs status messages and characters 
received from the terminal program running on the host PC in a 
"terminal window" on the LCD screen of the RDB1768.

This project requires that a version of the RDB1768cmsis2_LCDlib project 
that implements the LCD terminal functions is available within the
same workspace as this project (in addition to the USB stack 
project).

In order to connect to the board from hyperterminal, or similar, copy the 
usbser.inf file to a temporary location (C:\temp is a good place).

Then plug the USB cable into the USB device port of the RDB1768 and when
requested (after downloading and starting execution of the example) direct
Windows to the temporary directory containing the usbser.inf file. Windows
then creates an extra COMx port that you can open in hyperterminal (or 
similar).

When configuring your terminal program, you should set it to append line
feeds to incoming line ends, and to echo typed characters locally. You 
will then be able to see the character you type, as well as the character
returned by the example running on the board.

By default, this version of the code will not echo the character
back to the host (as evidence of it being received can be seen 
on the LCD).


~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Note that this example project is intended for use with Red Suite /
LPCXpresso IDE v4.0 or later.

Use of this project with earlier versions of the Code Red IDE is 
not recommended or supported.
 