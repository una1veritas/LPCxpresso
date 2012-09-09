/*****************************************************************************
 *   crp_main.c:  Code Read Protect for NXP LPC13xx Family Microprocessors
 *
 *   Copyright(C) 2010, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2010.02.02  ver 1.00    Preliminary version, first Release
 *
******************************************************************************/
#include "LPC13xx.h"                        /* LPC13xx definitions */
#include "timer32.h"
#include "clkconfig.h"
#include "gpio.h"
#include "config.h"

extern volatile uint32_t timer32_0_counter;
#define BLINK_TIME 50

#define NO_CRP          0xFFFFFFFF

// Disables UART and USB In System Programming (reads and writes)
// Leaves SWD debugging, with reads and writes, enabled
#define NO_ISP_MAGIC    0x4E697370

// Disables SWD debugging & JTAG, leaves ISP with with reads and writes enabled
// You will need UART connectivity and FlashMagic (flashmagictool.com) to reverse
// this. Don't even try this without these tools; most likely the SWD flash
// programming will not even complete.
// Allows reads and writes only to RAM above 0x10000300 and flash other than
// sector 0 (the first 4 kB). Full erase also allowed- again only through UART
// and FlashMagic (NO JTAG/SWD)
#define CRP1_MAGIC      0x12345678

// Disables SWD debugging & JTAG, leaves UART ISP with with only full erase
// enabled. You must have UART access and FlashMagic before setting this
// option.
// Don't even try this without these tools; most likely the SWD flash
// programming will not even complete.
#define CRP2_MAGIC      0x87654321

/************************************************************/
/**** DANGER CRP3 WILL LOCK PART TO ALL READS and WRITES ****/
/*********** #define CRP3_MAGIC xxxx 0x43218765 *************/
/************************************************************/

// This value is placed in flash at 0x000002FC by the script LPC1343_Flash_CRP.icf or crp_enabled.ld
#define CURRENT_CRP_SETTING NO_CRP

#ifdef __GNUC__
__attribute__ ((section(".crp"))) const uint32_t CRP_WORD = CURRENT_CRP_SETTING;
#endif
#ifdef __IAR_SYSTEMS_ICC__
const __root uint32_t CRP_WORD @ ".crp" = CURRENT_CRP_SETTING;
#endif

int main (void) {
  /* Basic chip initialization is taken care of in SystemInit() called
   * from the startup code. SystemInit() and chip settings are defined
   * in the CMSIS system_<part family>.c file.
   */

  /* Initialize 32-bit timer 0. TIME_INTERVAL is defined as 10mS */
  /* You may also want to use the Cortex SysTick timer to do this */
  init_timer32(0, TIME_INTERVAL);
  /* Enable timer 0. Our interrupt handler will begin incrementing
   * the TimeTick global each time timer 0 matches and resets.
   */
  enable_timer32(0);

  /* Initialize GPIO (sets up clock) */
  GPIOInit();
  /* Set LED port pin to output */
  GPIOSetDir( LED_PORT, LED_BIT, 1 );

  while (1)                                /* Loop forever */
  {
	/* Each time we wake up... */
	/* Check TimeTick to see whether to set or clear the LED I/O pin */
	if ( (timer32_0_counter%LED_TOGGLE_TICKS) < (LED_TOGGLE_TICKS/2) )
	{
	  GPIOSetValue( LED_PORT, LED_BIT, LED_OFF );
	} else
	{
	  GPIOSetValue( LED_PORT, LED_BIT, LED_ON );
	}
    /* Go to sleep to save power between timer interrupts */
    __WFI();
  }
}
