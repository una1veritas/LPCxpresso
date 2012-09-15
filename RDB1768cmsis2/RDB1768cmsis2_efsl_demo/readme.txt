Code Red Technologies RDB1768 Board - microSD card / EFSL demo
==============================================================

[ Note that this project requires the CMSISv2p00_LPC17xx library 
  and the RDB1768cmsis2_efsl_lib projects to exist in the same
  workspace. ]

This project gives a basic demonstration of how the Embedded
Filesystems Library (EFSL) can be used on the RDB1768 board.

The EFSL port to RDB1768 is contained in the associated 
RDB1768cmsis2_efsl_lib project.

When executed, the demonstration will initialise the microSD
card interface on the RDB1768, and then read the root 
directory of the microSD card. This will then be displayed
to the console view within the IDE (using the semihosting
mechanism).

Note that the filenames displayed will be in 8.3 format, as 
EFSL does not contain support for long filenames.

More information on EFSL, including the original sources and
the documentation can be found at:

http://efsl.be/
http://sourceforge.net/projects/efsl/

Note that the project defines
 
CR_INTEGER_PRINTF
 - This tells the Redlib C library that the none-floating
   point version of printf family functions can be linked
   in, which reduces the size of the application.

Support
-------
This example project is based on the open source EFSL project.
Code Red can provide support on using this project as supplied to 
users with a valid support contract with us. But if you require 
assistance on the general use of EFSL or on extending the 
example, then we would recommend that you raise your questions
to an appropriate community forum, such as....

http://sourceforge.net/projects/efsl/support
http://tech.groups.yahoo.com/group/lpc2000/messages  


~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Note that this example project is intended for use with Red Suite /
LPCXpresso IDE v4.0 or later.

Use of this project with earlier versions of the Code Red IDE is 
not recommended or supported.   