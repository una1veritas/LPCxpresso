Code Red Technologies RDB1768 Board - USB_HID Example
=====================================================

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

USB_HID Example
---------------
This is the standard LPCUSB Human Interface Device example, ported to
the LPC1768/RDB1768.

The example provides a simple HID driver. When executed on the RDB1768,
this will register itself with the connected PC as a joystick (games
controller). This can be seen by looking in the Windows Device Manager
in System Properties.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Note that this example project is intended for use with Red Suite /
LPCXpresso IDE v4.0 or later.

Use of this project with earlier versions of the Code Red IDE is 
not recommended or supported.
 