/*
===============================================================================
 Name        : main.c
 Author      : David Donley
 Version     :
 Copyright   : (C) Copyright 2009 NXP Semiconductors
 ==============================================================================
*/

#include "LPC13xx.h"
#include "gpio.h"
#include "clkconfig.h"
#include "config.h"

volatile uint32_t TimeTick = 0;

#define SYSTICK_TICKSPERSEC 100
#define SYSTICK_DELAY_CYCLES (SystemCoreClock/SYSTICK_TICKSPERSEC)
#define INTERNAL_RC_HZ 12000000

#define WDTCLK_SRC_IRC_OSC			0
#define WDTCLK_SRC_MAIN_CLK			1
#define WDTCLK_SRC_WDT_OSC			2


/* SysTick interrupt happens every 10 ms */
/* Note- The SysTick timer is in the Cortex CPU core and does not
 * run during sleep mode.
 */
void SysTick_Handler(void)
{
  /* Count 10ms periods */
  TimeTick++;
}

void SetWDTResetMS(uint32_t ms)
{
  /* make sure WDT config clock is turned on */
  LPC_SYSCON->SYSAHBCLKCTRL |= 0x08000;

  /* Enable internal RC clock */
  LPC_SYSCON->PDRUNCFG &= ~(1);

  /* Select internal RC for watchdog */
  LPC_SYSCON->WDTCLKSEL = WDTCLK_SRC_IRC_OSC;
  /* Toggle WDTCLKUEN to latch clock selection */
  LPC_SYSCON->WDTCLKUEN = 0;
  LPC_SYSCON->WDTCLKUEN = 1;

  /* We are using the internal RC clock to drive the watchdog because it is
     independent of PLL settings. The "System Clock" option routes the clock
     after the PLL to the watchdog. The "System Clock" could vary depending
     on what CPU speed is configured with the PLL. */

  /* Set watchdog counter value */
  LPC_WDT->TC = ((INTERNAL_RC_HZ/4)/1000) * ms;

  /* Set up watchdog clock "divide" by one (default state is gated off) */
  LPC_SYSCON->WDTCLKDIV = 1;

  /* Enable watchdog, and arm it to generate a reset upon timeout */
  LPC_WDT->MOD = 0x3;

  /* Send watchdog "feed" sequence- final step to begin the timeout */
  LPC_WDT->FEED = 0xAA;
  LPC_WDT->FEED = 0x55;
}

/* This data must be global so it is not read from the stack */
typedef void (*IAP)(uint32_t [], uint32_t []);
IAP iap_entry = (IAP)0x1fff1ff1;
uint32_t command[5], result[4];

/* This function resets some microcontroller peripherals to reset
   hardware configuration to ensure that the USB In-System Programming module
   will work properly. It is normally called from reset and assumes some reset
   configuration settings for the MCU.
   Some of the peripheral configurations may be redundant in your specific
   project.
*/
void ReinvokeISP(void)
{
  /* make sure USB clock is turned on before calling ISP */
  LPC_SYSCON->SYSAHBCLKCTRL |= 0x04000;
  /* make sure 32-bit Timer 1 is turned on before calling ISP */
  LPC_SYSCON->SYSAHBCLKCTRL |= 0x00400;
  /* make sure GPIO clock is turned on before calling ISP */
  LPC_SYSCON->SYSAHBCLKCTRL |= 0x00040;
  /* make sure IO configuration clock is turned on before calling ISP */
  LPC_SYSCON->SYSAHBCLKCTRL |= 0x10000;
  /* make sure AHB clock divider is 1:1 */
  LPC_SYSCON->SYSAHBCLKDIV = 1;

  /* Send Reinvoke ISP command to ISP entry point*/
  command[0] = 57;

  /* Set stack pointer to ROM value (reset default) This must be the last
     piece of code executed before calling ISP, because most C expressions
     and function returns will fail after the stack pointer is changed. */
  __set_MSP(*((uint32_t *)0x1FFF0000)); /* inline asm function */

  /* Enter ISP. We call "iap_entry" to enter ISP because the ISP entry is done
     through the same command interface as IAP. */
  iap_entry(command, result);
  // Not supposed to come back!
}

/* Main Program */
int main()
{
  /* Basic chip initialization is taken care of in SystemInit() called
   * from the startup code. Chip settings are defined in the CMSIS
   * system_<part family>.c file.
   */

  /* Initialize GPIO (sets up clock) */
  GPIOInit();
  /* Set LED port pin as output */
  GPIOSetDir( LED_PORT, LED_BIT, 1 );

  /* Configure SYSTICK timer to generate interrupt every 10ms */
  SysTick_Config(SYSTICK_DELAY_CYCLES);

  while(1)
  {
    /* Blink LED at 1 Hz rate while delaying PRE_ISP_DELAY_SECS */
    GPIOSetValue( LED_PORT, LED_BIT, (TimeTick/(SYSTICK_TICKSPERSEC/2))&1);

    if(TimeTick >= PRE_ISP_DELAY_SECS*SYSTICK_TICKSPERSEC)
    {
      /* Configure watchdog timer to reset the CPU ISP_SECS after ISP entry */
      /* After reset, the CPU will enter the new ISP programmed code */
      SetWDTResetMS(ISP_SECS*1000);

      /* Disable SYSTICK timer and interrupt before calling into ISP */
      SysTick->CTRL &= ~(SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_TICKINT_Msk);

      /* Turn on LED to indicate ISP is active */
      GPIOSetValue( LED_PORT, LED_BIT, LED_ON);

      /* Start ISP */
      ReinvokeISP();
    }
    /* Go to sleep to save power between SYSTICK interrupts */
    __WFI();
  }
}
