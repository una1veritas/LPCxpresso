Code Red Technologies RDB1768 Board - Audio Level Meter (64K)
=======================================================

This project is a modified version of the original 
RDB1768cmsis2_AudioLevel project. The only difference is that this
version has been configured to build to run from address 0x10000
(64KB) so that it is suitable for use with the 
RDB1768cmsis2_usb_bootloader.

-------------------------------------

[ Note that this project requires the CMSISv2p00_LPC17xx library 
  project as well as the LCDLib project to exist in the same 
  workspace. ]
  
This demonstration project provides a simple example that uses
the audio facilities provided by the RDB1768. It also makes use
of the LCD screen to display a meter showing levels for the audio
being received. 

To run the example, you will need to connect an audio source,
such as an MP3 player, to the 3.5mm line-in socket of the RDB1768.

The audio signal received can then be redirected to the built-in
speaker of the RDB1768 by moving switch S2-2 (Audio-SP) to the right.

Alternatively, connected a set of headphones or external speakers to
the 3.5mm headphones socket of the RDB1768.

Note
====
The RDB1768cmsis_AudioMeter project contains a routine called
whichRDB(). This allows the code to determine at runtime whether
it is running on an RDB1768 (v1), or RDB1768v2 board. This check
is done by reading a register in the ethernet phy - which differs
between the two boards.

This check is then used to determine which audio codec needs to
be used by the rest of the application.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Note that this example project is intended for use with Red Suite /
LPCXpresso IDE v4.0 or later.

Use of this project with earlier versions of the Code Red IDE is 
not recommended or supported.