/***********************************************************************
 * $Id::                                                               $
 *
 * Project:	uart: Simple UART echo for LPCXpresso 1700
 * File:	uarttest.c
 * Description:
 * 			LPCXpresso Baseboard uses pins mapped to UART3 for
 * 			its USB-to-UART bridge. This application simply echos
 * 			all characters received.
 *
 ***********************************************************************
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 * NXP Semiconductors assumes no responsibility or liability for the
 * use of the software, conveys no license or title under any patent,
 * copyright, or mask work right to the product. NXP Semiconductors
 * reserves the right to make changes in the software without
 * notification. NXP Semiconductors also make no representation or
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.
 **********************************************************************/

/*****************************************************************************
 *   History
 *   2010.07.01  ver 1.01    Added support for UART3, tested on LPCXpresso 1700
 *   2009.05.27  ver 1.00    Prelimnary version, first Release
 *
******************************************************************************/
#include "LPC17xx.h"
#include "type.h"
#include "uart.h"
#include <string.h>
#include <ctype.h>

#include "d3DES.h"

extern volatile uint32_t UART3Count;
extern volatile uint8_t UART3Buffer[BUFSIZE];

/*****************************************************************************
**   Main Function  main()
This program has been test on LPCXpresso 1700.
*****************************************************************************/
int main (void)
{
	uint8_t keycode[] = { 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88 };
	uint8_t bto[8];

	deskey(keycode, EN0);

	const char* welcomeMsg = "UART3 Online:\r\n";
	//SystemInit();	//Called by startup code

	UARTInit(3, 9600);	/* baud rate setting */
	UARTSend(3, (uint8_t *)welcomeMsg , strlen(welcomeMsg) );

	/* Loop forever */
	while (1)
	{
		//if ( UART3Count != 0 )
		if ( UART3Count == 8 )
		{
			LPC_UART3->IER = IER_THRE | IER_RLS;				/* Disable RBR */
			//for(int i = 0; i < UART3Count; i++) {
			//	UART3Buffer[i] = tolower(UART3Buffer[i]);
			//}
			des((uint8_t *)UART3Buffer, bto);

			UARTSend(3, (uint8_t *) UART3Buffer, 8 );
			UARTSend(3, "\r\n", 2 );
			UARTSend(3, (uint8_t *) bto, 8 );
			UARTSend(3, "\r\n", 2 );
			UARTSend(3, "\r\n", 2 );

			UART3Count = 0;
			LPC_UART3->IER = IER_THRE | IER_RLS | IER_RBR;		/* Re-enable RBR */
		}
	}
}

/*****************************************************************************
**                            End Of File
*****************************************************************************/