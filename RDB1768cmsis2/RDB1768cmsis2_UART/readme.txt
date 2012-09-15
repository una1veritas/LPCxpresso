Code Red Technologies RDB1768 Board - UART Example
==================================================

[ Note that this project requires the CMSISv2p00_LPC17xx library 
  project to exist in the same workspace. ]

This example allows you to send data to/from the board to
your PC to the RDB1768 board over the serial port. To do this
you will need to connect the board to your PC using a serial cable,
and use a terminal program on your PC, such as hyperterminal.

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

As supplied, the example is configured to use the 'semihosting'
option in the debug configuration so that 'printf' messages from
the target are reported in the IDE Console Window. This includes
a startup message, and also the characters sent from the PC. This
behaviour can be changed by undefining SEMIHOSTING_CONSOLE.

When the example begins to execute, it will send a startup message
over the UART for display by your terminal program. It will then wait
for you to press a key within the terminal and then echo everything 
it receives right back to the host PC, but incremented by 1. Thus
if you type 'a' on the host PC, the program will send back 'b'. 

This behaviour can be changed to echoing the same character ('a' is 
sent back when 'a' was received) by undefining INCREMENT_ECHO_BY_1.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Note that this example project is intended for use with Red Suite /
LPCXpresso IDE v4.0 or later.

Use of this project with earlier versions of the Code Red IDE is 
not recommended or supported. 