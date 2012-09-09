/*----------------------------------------------------------------------------
 *      Name:    DEMO.C
 *      Purpose: USB HID Demo
 *      Version: V1.20
 *----------------------------------------------------------------------------
 *      This software is supplied "AS IS" without any warranties, express,
 *      implied or statutory, including but not limited to the implied
 *      warranties of fitness for purpose, satisfactory quality and
 *      noninfringement. Keil extends you a royalty-free right to reproduce
 *      and distribute executable files created using this software for use
 *      on NXP Semiconductors LPC microcontroller devices only. Nothing else 
 *      gives you the right to use this software.
 *
 * Copyright (c) 2009 Keil - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include "LPC13xx.h"                        /* LPC13xx definitions */

#include "usb.h"
#include "usbcfg.h"
#include "usbhw.h"
#include "usbcore.h"
#include "gpio.h"
#include "demo.h"
#include "config.h"

#define     EN_TIMER32_1    (1<<10)
#define     EN_IOCON        (1<<16)
#define     EN_USBREG       (1<<14)


/*
 *  Get HID Input Report -> InReport
 */

void GetInReport ()
{
	InReport = 0;
	/* Check the four input port bits and set the four low bits of
	 * the "InReport" response for the PC.
	 */

	if(INPUT0_CPORT->DATA&INPUT0_BIT)
		InReport |= 1<<0;
	if(INPUT1_CPORT->DATA&INPUT1_BIT)
		InReport |= 1<<1;
	if(INPUT2_CPORT->DATA&INPUT2_BIT)
		InReport |= 1<<2;
	if(INPUT3_CPORT->DATA&INPUT3_BIT)
		InReport |= 1<<3;
}


/*
 *  Set HID Output Report <- OutReport
 */
void SetOutReport ()
{
	if(OutReport&(1<<0))
		GPIOSetValue(OUTPUT0_PORT, OUTPUT0_BIT, 1);
	else
		GPIOSetValue(OUTPUT0_PORT, OUTPUT0_BIT, 0);

	if(OutReport&(1<<1))
		GPIOSetValue(OUTPUT1_PORT, OUTPUT1_BIT, 1);
	else
		GPIOSetValue(OUTPUT1_PORT, OUTPUT1_BIT, 0);

	if(OutReport&(1<<2))
		GPIOSetValue(OUTPUT2_PORT, OUTPUT2_BIT, 1);
	else
		GPIOSetValue(OUTPUT2_PORT, OUTPUT2_BIT, 0);

	if(OutReport&(1<<3))
		GPIOSetValue(OUTPUT3_PORT, OUTPUT3_BIT, 1);
	else
		GPIOSetValue(OUTPUT3_PORT, OUTPUT3_BIT, 0);
}

int main (void)
{
  /* Initialize input port pins */
  GPIOSetDir( INPUT0_PORT, INPUT0_BIT, 0 );
  GPIOSetDir( INPUT1_PORT, INPUT1_BIT, 0 );
  GPIOSetDir( INPUT2_PORT, INPUT2_BIT, 0 );
  GPIOSetDir( INPUT3_PORT, INPUT3_BIT, 0 );
  
  /* Initialize output port pins */
  GPIOSetDir( OUTPUT0_PORT, OUTPUT0_BIT, 1 );
  GPIOSetDir( OUTPUT1_PORT, OUTPUT1_BIT, 1 );
  GPIOSetDir( OUTPUT2_PORT, OUTPUT2_BIT, 1 );
  GPIOSetDir( OUTPUT3_PORT, OUTPUT3_BIT, 1 );

	/* Enable Timer32_1, IOCON, and USB blocks */
	LPC_SYSCON->SYSAHBCLKCTRL |= (EN_TIMER32_1 | EN_IOCON | EN_USBREG);

	/* PLL and pin init function */
	USBIOClkConfig();

	/* USB Initialization */
	USB_Init();

	/* USB Connect (if SoftConnect switch implemented) */
	USB_Connect(1);

	while(1)
		__WFI();
}
