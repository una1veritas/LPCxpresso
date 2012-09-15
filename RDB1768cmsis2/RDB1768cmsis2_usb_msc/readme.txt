Code Red Technologies RDB1768 Board - USB_MSC Example
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
This example project is based on the open source LPCUSB stack.
Code Red can provide support on using this project as supplied to 
users with a valid support contract with us. But if you require 
assistance on the general use of the stack or on extending the 
example, then we would recommend that you raise your questions
to an appropriate community forum, such as....

http://tech.groups.yahoo.com/group/lpc2000/messages

USB_MSC Example
---------------
This is the standard LPCUSB mass storage device example, ported to
the LPC1768/RDB1768.

This example turns the RDB1768 into a mass storage device, by connecting
the onboard micro-SD card system to USB sub-system via the SPI interface
of the LPC1768. When the example is downloaded and run, the board will
appear within Windows as a mass storage drive, which can be read from and
written to as required.

Note that you will require a micro-SD card to make use of this example. 
This should be inserted into the socket underneath the RDB1768's LCD screen
before executing the example. Hot-plugging of cards is not supported.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Note that this example project is intended for use with Red Suite /
LPCXpresso IDE v4.0 or later.

Use of this project with earlier versions of the Code Red IDE is 
not recommended or supported.