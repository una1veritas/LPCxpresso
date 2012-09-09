//*****************************************************************************
//   +--+
//   | ++----+
//   +-++    |
//     |     |
//   +-+--+  |
//   | +--+--+
//   +----+    Copyright (c) 2009 Code Red Technologies Ltd.
//
// gpio_int.c - Interrupt handler code for GPIO peripheral of LPC13xx
//
// Software License Agreement
//
// The software is owned by Code Red Technologies and/or its suppliers, and is
// protected under applicable copyright laws.  All rights are reserved.  Any
// use in violation of the foregoing restrictions may subject the user to criminal
// sanctions under applicable laws, as well as to civil liability for the breach
// of the terms and conditions of this license.
//
// THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
// OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
// USE OF THIS SOFTWARE FOR COMMERCIAL DEVELOPMENT AND/OR EDUCATION IS SUBJECT
// TO A CURRENT END USER LICENSE AGREEMENT (COMMERCIAL OR EDUCATIONAL) WITH
// CODE RED TECHNOLOGIES LTD.
//
//*****************************************************************************

// Code based on content of NXP gpio.c, to be found in LPC13xx_Lib project.
// Interrupts handlers have been extracted to this file so that the library
// project is then application independent.

#include "LPC13xx.h"			/* LPC13xx Peripheral Registers */
#include "gpio.h"
#include "config.h"

// CodeRed
unsigned int LEDvalue = LED_OFF;

volatile uint32_t gpio2_counter = 0;
volatile uint32_t p2_1_counter  = 0;

/*****************************************************************************
** Function name:		PIOINT2_IRQHandler
**
** Descriptions:		Use one GPIO pin(port2 pin1) as interrupt source
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
void PIOINT2_IRQHandler(void)
{
  uint32_t regVal;

  gpio2_counter++;
  regVal = GPIOIntStatus( PORT2, 1 );
  if ( regVal )
  {
	p2_1_counter++;
	GPIOIntClear( PORT2, 1 );
  }

  // CodeRed - extend original interrupt handler so as to toggle the LED state
  if (LEDvalue == LED_OFF)
  {
	  LEDvalue = LED_ON;
  }
  else
  {
	  LEDvalue = LED_OFF;
  }
  GPIOSetValue( LED_PORT, LED_BIT, LEDvalue );

  return;
}
