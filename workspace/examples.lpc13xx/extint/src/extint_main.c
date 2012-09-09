/*****************************************************************************
 *   gpiotest.c:  main C entry file for NXP LPC13xx Family Microprocessors
 *
 *   Copyright(C) 2008, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2008.07.19  ver 1.00    Preliminary version, first Release
 *
******************************************************************************/
#include "LPC13xx.h"			/* LPC13xx Peripheral Registers */
#include "gpio.h"
#include "config.h"

/*****************************************************************************
**   Main Function  main()
******************************************************************************/
int main (void)
{
  /* Basic chip initialization is taken care of in SystemInit() called
   * from the startup code. SystemInit() and chip settings are defined
   * in the CMSIS system_<part family>.c file.
   */

  /* Initialize GPIO (sets up clock) */
  GPIOInit();

   /* use port2_1 as input event, interrupt test. */
  GPIOSetDir( PORT2, 1, 0 );
  /* port0_1, single edge trigger, active high. */
  GPIOSetInterrupt( PORT2, 1, 0, 0, 0 );
  GPIOIntEnable( PORT2, 1 );

  /* Set LED port line to output */
  GPIOSetDir( LED_PORT, LED_BIT, 1 );
  /* Turn LED on */
  GPIOSetValue( LED_PORT, LED_BIT, LED_OFF );

  while( 1 );
}

/*********************************************************************************
**                            End Of File
*********************************************************************************/
