Code Red Technologies RDB1768 Board - microSD card / EFSL library
=================================================================

[ Note that this project requires the CMSISv2p00_LPC17xx library 
  project to exist in the same workspace. ]

This library project contains a port to the RDB1768 of the 
Embedded Filesystems Library (EFSL) version 0.2.8 (the latest 
version at the time of writing on the stable branch of EFSL).

EFSL is a library for filesystems intended to be used in 
embedded projects. The library currently supports FAT12/16/32
reading & writing on SD-cards, and is easily expandable for 
use with other devices on any platform.

More information on EFSL, including the original sources and
the documentation can be found at:

http://efsl.be/
http://sourceforge.net/projects/efsl/


Note that the project defines
 
CR_INTEGER_PRINTF
 - This tells the Redlib C library that the none-floating
   point version of printf family functions can be linked
   in, which reduces the size of the application.

HW_ENDPOINT_RDB1768_SD
 - This is defined in config.h, and controls the usage of
   RDB1768 specifics within the library project.
   
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
   