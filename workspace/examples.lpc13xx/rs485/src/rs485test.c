/*****************************************************************************
 *   rs485test.c:  UART RS485 mode test C file for NXP LPC13xx Family 
 *                 Microprocessors
 *
 *   Copyright(C) 2008, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2008.08.20  ver 1.00    Preliminary version, first Release
 *
******************************************************************************/
#include "LPC13xx.h"
#include "rs485.h"

extern volatile uint32_t UARTCount;
extern volatile uint8_t UARTBuffer[BUFSIZE];
volatile uint8_t UARTTxBuffer[BUFSIZE];

int main (void) {
	  /* Basic chip initialization is taken care of in SystemInit() called
	   * from the startup code. SystemInit() and chip settings are defined
	   * in the CMSIS system_<part family>.c file.
	   */

  uint8_t i;

  /* Clear receive buffer, handled inside ISR. */
  for ( i = 0; i < BUFSIZE; i++ )
  {
	UARTBuffer[i] = 0x00;	
  }
  
  /* NVIC is installed inside UARTInit file. */
  RS485Init(115200);

  /* To test RS485 mode, connect two boards, one is set to TX and
  the other is RX. The test is conducted on the inter-board communication. */
#if RS485_RX
  /* If RX, do nothing, check the content of UARTBuffer */
  /* To get the test result, program the boards with both TX and RX program, 
  power up the board with the RX program first, start the debugger on the
  board with the RX program, power up the board with the TX program, stop 
  the debugger, and check the content of the UARTBuffer on the RX program,
  it should be the same as seen on UARTTxBuffer, 0x01-0x02-0x03.... */ 
  while ( 1 );

#else
  /* If TX. send a string out start with RS485 slave address */
  UARTTxBuffer[0] = RS485_SLAVE_ADR;
  for ( i = 1; i < BUFSIZE; i++ )
  {
	UARTTxBuffer[i] = i;	
  }
  RS485Send((uint8_t *)UARTTxBuffer, BUFSIZE);
  while ( 1 );
#endif			/* #endif RS485_RX */

}
