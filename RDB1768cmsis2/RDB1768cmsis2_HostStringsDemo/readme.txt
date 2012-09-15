Code Red Technologies RDB1768 Board - HostStringsDemo
=====================================================

[ Note that this project requires the CMSISv2p00_LPC17xx library 
  project to exist in the same workspace. ]

This project is designed to show how the Host Strings functionality
of "Red Trace" within Red Suite 4 can be used to display diagnostic
messages as your code is running.

The project is based on the RDB1768cmsis2_SysTick example, with
three Host String outputs added:

HS_DisplayVal - used to periodically output the value of 'msticks'
HS_LedsOn     - used to print a diagnostic when LEDs switch on
HS_LedsOff()  - used to print a diagnostic when LEDs switch on

For more details on using Host Strings and other Red Trace 
functionality, see the "Getting Started with Red Trace" Guide 
provided with Red Suite 4.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Note that this example project is intended for use with Red Suite v4.0
or later. Note that Red Trace functionality is not available within
the LPCXpresso IDE.
