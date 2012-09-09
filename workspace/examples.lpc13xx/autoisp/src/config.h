/*****************************************************************************
 *   config.h:  config file for autoisp example for NXP LPC13xx Family
 *   Microprocessors
 *
 *   Copyright(C) 2009, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2009.07.19  ver 1.00    Preliminary version, first Release
 *
******************************************************************************/

/*
Overview:
   This example shows how to trigger the In-Circuit Programming (ISP) and
   execute the new code automatically. It works by configuring the watchdog
   timer to reset the microcontroller after a delay. Then, it calls a ROM
   call to switch the microcontroller into ISP mode.

   After the delay elapses, the microcontroller resets and begins to execute
   the new code that was downloaded through ISP.

User #defines:
   LED_PORT   I/O port driving an LED
   LED_BIT    I/O port bit driving an LED
   LED_ON     Value to set the bit to turn on the led
   LED_OFF    Value to set the bit to turn off the led

   PRE_ISP_DELAY_SECS
              How many seconds to wait before entering ISP mode.
   ISP_SECS
              How many seconds to wait before resetting after ISP mode has
              been entered.

How to use:
   Build, program, run.

   * You should see an LED flashing at a 1 Hz rate.
   * Connect the LPC13xx to a PC using a USB cable.
   * After 10 seconds (or PRE_ISP_DELAY_SECS) you should hear the PC enumerate
     a new device. After a few seconds more, a new disk drive named
     "CRP DISABLD" should appear on the PC in the Windows Explorer. This disk
     drive is the LPC13xx ISP.
   * Delete firmware.bin from this disk drive and copy a new .bin file onto it.
     This overwrites the LPC's flash memory with the new .bin code.
   * After 45 seconds have elapsed (or ISP_SECS) the microcontroller should
     restart and begin running the newly flashed code. If no code was written
     or this Autoboot example was re-programmed, the MCU will repeat this
     sequence.
*/


#define LED_PORT 0		// Port for led
#define LED_BIT 7		// Bit on port for led
#define LED_ON 1		// Level to set port to turn on led
#define LED_OFF 0		// Level to set port to turn off led

#define PRE_ISP_DELAY_SECS 10	// Delay before calling into ROM ISP
#define ISP_SECS 45				// Delay before resetting (using WDT) and starting
								// new program

/*********************************************************************************
**                            End Of File
*********************************************************************************/
