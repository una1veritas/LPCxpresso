/*
===============================================================================
 Name        : main.c
 Author      : 
 Version     :
 Copyright   : Copyright (C) 
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC18xx.h"
#endif

#include <cr_section_macros.h>
#include <NXP/crp.h>

// Variable to store CRP value in. Will be placed automatically
// by the linker when "Enable Code Read Protect" selected.
// See crp.h header for more information
__CRP const unsigned int CRP_WORD = CRP_NO_CRP ;

#include <string.h>
#include "LPC18xx.H"                        /* LPC23xx definitions */
#include "lpc_types.h"
#include "lpc18xx_scu.h"
#include "lpc18xx_uart.h"
#include <stdio.h>

#include "usb.h"
#include "usbcfg.h"
#include "usbhw.h"
#include "usbcore.h"
#include "usbuser.h"
#include "mscuser.h"

#include "lpc18xx_cgu.h"
#include "lpc18xx_libcfg_default.h"
#include "debug_frmwrk.h"

/* Example group ----------------------------------------------------------- */
/** @defgroup USBDEV_USBMSC	USBMSC
 * @ingroup USBDEV_Examples
 * @{
 */

/***********************************************************************/
/* Select USB0 or USB1 device in usb.h                                 */

volatile uint32_t systicks=0;

extern DQH_T ep_QH[EP_NUM_MAX];
extern DTD_T ep_TD[EP_NUM_MAX];
extern uint32_t DevStatusFS2HS;

extern void USB_EndPoint0 (uint32_t event);


void IOInit(void);

/* Main Program */

int main (void) {
	LPC_USBDRV_INIT_T usb_cb;

	SystemInit();
	CGU_Init();

	/* initilize call back structures */
	memset((void*)&usb_cb, 0, sizeof(LPC_USBDRV_INIT_T));
	usb_cb.USB_Reset_Event = USB_Reset_Event;
	usb_cb.USB_P_EP[0] = USB_EndPoint0;
	usb_cb.USB_P_EP[1] = USB_EndPoint1;
	usb_cb.ep0_maxp = USB_MAX_PACKET0;

	/* USB Initialization */
	USB_Init(&usb_cb);
	USB_Connect(TRUE);                        /* USB Connect */
	while (!USB_Configuration) ;              // wait until USB is configured

	while (1);                                /* Loop forever */

}


/*----------------------------------------------------------------------------
  SysTick IRQ: Executed periodically
 *----------------------------------------------------------------------------*/
void SysTick_Handler (void) 					// SysTick Interrupt Handler @ 500Hz
{
	static uint32_t cnt;
	systicks++;

	if ( cnt < systicks )	   					// 0.5s
	{
	  	cnt = systicks +50;
	}
}


#ifdef  DEBUG
/*******************************************************************************
* @brief		Reports the name of the source file and the source line number
* 				where the CHECK_PARAM error has occurred.
* @param[in]	file Pointer to the source file name
* @param[in]    line assert_param error line source number
* @return		None
*******************************************************************************/
void check_failed(uint8_t *file, uint32_t line)
{
	/* User can add his own implementation to report the file name and line number,
	 ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

	/* Infinite loop */
	while(1);
}
#endif
