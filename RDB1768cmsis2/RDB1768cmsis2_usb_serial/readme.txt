Code Red Technologies RDB1768 Board - USB_Serial Example
========================================================

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
This example project is based on the open source  LPCUSB stack.
Code Red can provide support on using this project as supplied to 
users with a valid support contract with us. But if you require 
assistance on the general use of the stack or on extending the 
example, then we would recommend that you raise your questions
to an appropriate community forum, such as....

http://tech.groups.yahoo.com/group/lpc2000/messages

USB_Serial Example
------------------
This example provides a minimal implementation of a USB serial port, using
the CDC class. This therefore allows you to connect to the board over USB from
a terminal program, such as hyperterminal.

By default this port of the example will simply echo everything it receives 
right back to the host PC, but incremented by 1. Thus if you type 'a' on the
host PC, the program will send back 'b'. 

The original behaviour of echoing back the same character ('a' is sent back
when 'a' was received) can be restored by changing the value of the #define of
'INCREMENT_ECHO_BY' from '1' to '0'.

In order to connect to the board from hyperterminal, or similar, copy the 
usbser.inf file (provided as part of USB_Serial project) to a temporary 
location (C:\temp is a good place).

Then plug the USB cable into the USB device port of the RDB1768 and when
requested (after downloading and starting execution of the example) direct
Windows to the temporary directory containing the usbser.inf file. Windows
then creates an extra COMx port that you can open in hyperterminal (or 
similar).

When configuring your terminal program, you should set it to append line
feeds to incoming line ends, and to echo typed characters locally. You 
will then be able to see the character you type, as well as the character
returned by the example running on the board.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Note that this example project is intended for use with Red Suite /
LPCXpresso IDE v4.0 or later.

Use of this project with earlier versions of the Code Red IDE is 
not recommended or supported. 