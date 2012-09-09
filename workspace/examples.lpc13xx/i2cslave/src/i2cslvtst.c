/*****************************************************************************
 *   i2cslvtst.c:  main C entry file for NXP LPC13xx Family Microprocessors
 *
 *   Copyright(C) 2008, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2008.07.20  ver 1.00    Preliminary version, first Release
 *
******************************************************************************/
#include "LPC13xx.h"			/* LPC13xx Peripheral Registers */
#include "type.h"
#include "i2cslave.h"

extern volatile uint8_t I2CWrBuffer[BUFSIZE];
extern volatile uint8_t I2CRdBuffer[BUFSIZE];
extern volatile uint32_t I2CSlaveState;
extern volatile uint32_t I2CReadLength, I2CWriteLength;

/*******************************************************************************
**   Main Function  main()
*******************************************************************************/
int main (void)
{
	  /* Basic chip initialization is taken care of in SystemInit() called
	   * from the startup code. SystemInit() and chip settings are defined
	   * in the CMSIS system_<part family>.c file.
	   */

  uint32_t i;

  for ( i = 0; i < BUFSIZE; i++ )
  {
	I2CRdBuffer[i] = 0x00;
  }
  
  I2CSlaveInit();			/* initialize I2c */
 
  /* When the NACK occurs, the master has stopped the 
  communication. Just check the content of I2CRd/WrBuffer. */
  while ( I2CSlaveState != DATA_NACK );
  return 0;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
