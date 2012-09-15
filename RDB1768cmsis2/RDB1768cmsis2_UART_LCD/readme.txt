Code Red Technologies RDB1768 Board - UART LCD Example
======================================================

[ Note that this project requires the CMSISv2p00_LPC17xx library 
  project as well as the LCDLib project to exist in the same 
  workspace. ]

This example allows you to send data to/from RDB1768 to
your PC over the serial port. To do this you will need to 
connect the board to your PC using a serial cable, and use a
terminal program on your PC, such as hyperterminal.

Before downloading the example to the board, you should start
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

Characters received by the RDB1768 from the terminal program will
be displayed on the board's LCD screen.

Clicking the joystick on the RDB1768 will cause an appropriate
message to be displayed on the board's LCD screen, and also for
a message to be sent over the UART for display by the terminal
program.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Note that this example project is intended for use with Red Suite /
LPCXpresso IDE v4.0 or later.

Use of this project with earlier versions of the Code Red IDE is 
not recommended or supported.
 