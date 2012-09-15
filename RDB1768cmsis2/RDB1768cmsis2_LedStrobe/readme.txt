Code Red Technologies RDB1768 Board - LedStrobe Demo
====================================================

[ Note that this project requires the CMSISv2p00_LPC17xx library 
  project to exist in the same workspace. ]

This demonstration project show how the user leds, LED_2 to
LED_5, of the RDB1768 be accessed to provide a strobing effect.

When executed, the code will set up the Systick timer (built into 
the Cortex-M3 CPU) so that a timer tick takes place every 
1/1000th of a second.

The code strobe though LED_2 to LED_5, flashing each on, then 
off in turn. The period of this flash will start off relatively
slowly, get faster, and then slow down.

If you stop the code whilst it is running, you can modify how
fast and slow the flashing gets, and how quickly it changes by
modifying the variables 'maxflashval', 'minflashval' and 
'changeval'.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Note that this example project is intended for use with Red Suite /
LPCXpresso IDE v4.0 or later.

Use of this project with earlier versions of the Code Red IDE is 
not recommended or supported.