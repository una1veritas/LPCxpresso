Code Red Technologies RDB1768 Board - USB_HID_Mouse Example
===========================================================

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

USB_HID_Mouse
-------------
This example is based on the LPCUSB USB_HID example, but has been extended
so that the RDB1768 will act as a mouse to the connected PC. To move the 
cursor, use the joystick on the RDB1768 board. Clicking on the joystick will 
act as pressing the mouse's left button.

Note
====
The RDB1768cmsis2_usb_hidmouse project contains a routine called
whichRDB(). This allows the code to determine at runtime whether
it is running on an RDB1768 (v1), or RDB1768v2 board. This check
is done by reading a register in the ethernet phy - which differs
between the two boards.

This check is then used to determine how to read the "up click" 
of the joystick, which differs between the two boards.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Note that this example project is intended for use with Red Suite /
LPCXpresso IDE v4.0 or later.

Use of this project with earlier versions of the Code Red IDE is 
not recommended or supported. 