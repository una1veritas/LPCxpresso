/*****************************************************************************
 *   config.h:  config file for usbhid example for NXP LPC13xx Family
 *   Microprocessors
 *
 *   Copyright(C) 2008, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2008.07.19  ver 1.00    Preliminary version, first Release
 *
******************************************************************************/

/*
Overview:
	This example shows how to use the USB driver to implement a simple HID
	(Human Interface Device) class USB peripheral.
	To run this example, you must attach a USB cable to the board. See
	the "Getting Started Guide" appendix for details.

User #defines:
   LED_PORT	I/O port driving an LED
   LED_BIT  I/O port bit driving an LED
   LED_ON   Value to set the bit to turn on the LED
   LED_OFF  Value to set the bit to turn off the LED
   LED_TOGGLE_TICKS
		    Number of timer ticks per flash. The timer is configured to generate
		    an interrupt 100 times a second or every 10mS.

How to use:
   Click the debug toolbar button.
   Click the go button.
   Plug the LPCXpresso's target side into a PC using a USB cable retrofit
   or a 3rd party base board.

   * You should be able to control the LED with LPC1343 HID Demonstration.exe
*/

 /* Note: Our HID Demonstration software only works with our VID */
#define NXP_VID		  0x1FC9
#define MY_VID	  	  0x????

#define USB_VENDOR_ID NXP_VID 	// Vendor ID
#define USB_PROD_ID   0x0003	// Product ID
#define USB_DEVICE    0x0100	// Device ID

#define LED_PORT 0		// Port for led
#define LED_BIT 7		// Bit on port for led

/* Define the output pins controlled by the USB HID client */
#define OUTPUT0_PORT	LED_PORT
#define OUTPUT0_BIT		LED_BIT

#define OUTPUT1_PORT	PORT1
#define OUTPUT1_BIT		1

#define OUTPUT2_PORT	PORT2
#define OUTPUT2_BIT		1

#define OUTPUT3_PORT	PORT3
#define OUTPUT3_BIT		1

/* Define the input pins controlled by the USB HID client */
#define INPUT0_PORT		PORT0
#define INPUT0_CPORT	LPC_GPIO0
#define INPUT0_BIT		2

#define INPUT1_PORT		PORT1
#define INPUT1_CPORT	LPC_GPIO1
#define INPUT1_BIT		2

#define INPUT2_PORT		PORT2
#define INPUT2_CPORT	LPC_GPIO2
#define INPUT2_BIT		2

#define INPUT3_PORT		PORT3
#define INPUT3_CPORT	LPC_GPIO3
#define INPUT3_BIT		2


/*********************************************************************************
**                            End Of File
*********************************************************************************/
