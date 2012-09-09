/*****************************************************************************
 *   i2ctest.c:  main C entry file for NXP LPC13xx Family Microprocessors
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
#include "i2c.h"

extern volatile uint32_t I2CCount;
extern volatile uint8_t I2CMasterBuffer[BUFSIZE];
extern volatile uint8_t I2CSlaveBuffer[BUFSIZE];
extern volatile uint32_t I2CMasterState;
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

  if ( I2CInit( (uint32_t)I2CMASTER ) == FALSE )	/* initialize I2c */
  {
	while ( 1 );				/* Fatal error */
  }

  /* In order to start the I2CEngine, the all the parameters 
  must be set in advance, including I2CWriteLength, I2CReadLength,
  I2CCmd, and the I2cMasterBuffer which contains the stream
  command/data to the I2c slave device. 
  (1) If it's a I2C write only, the number of bytes to be written is 
  I2CWriteLength, I2CReadLength is zero, the content will be filled 
  in the I2CMasterBuffer. 
  (2) If it's a I2C read only, the number of bytes to be read is 
  I2CReadLength, I2CWriteLength is 0, the read value will be filled 
  in the I2CMasterBuffer. 
  (3) If it's a I2C Write/Read with repeated start, specify the 
  I2CWriteLength, fill the content of bytes to be written in 
  I2CMasterBuffer, specify the I2CReadLength, after the repeated 
  start and the device address with RD bit set, the content of the 
  reading will be filled in I2CMasterBuffer index at 
  I2CMasterBuffer[I2CWriteLength+2]. 
  
  e.g. Start, DevAddr(W), WRByte1...WRByteN, Repeated-Start, DevAddr(R), 
  RDByte1...RDByteN Stop. The content of the reading will be filled 
  after (I2CWriteLength + two devaddr) bytes. */

  /* Write SLA(W), address and one data byte */
  I2CWriteLength = 6;
  I2CReadLength = 0;
  I2CMasterBuffer[0] = PCF8594_ADDR;
  I2CMasterBuffer[1] = 0x00;		/* address */
  I2CMasterBuffer[2] = 0x55;		/* Data0 */
  I2CMasterBuffer[3] = 0xAA;		/* Data1 */
  I2CMasterBuffer[4] = 0x12;		/* Data0 */
  I2CMasterBuffer[5] = 0x34;		/* Data1 */
  I2CEngine();

  /* Be careful with below fixed delay. From device to device, or
  even same device with different write length, or various I2C clock, 
  below delay length may need to be changed accordingly. Having 
  a break point before Write/Read start will be helpful to isolate 
  the problem. */
  for ( i = 0; i < 0x200000; i++ );	/* Delay after write */

  for ( i = 0; i < BUFSIZE; i++ )
  {
	I2CSlaveBuffer[i] = 0x00;
  }
  /* Write SLA(W), address, SLA(R), and read one byte back. */
  I2CWriteLength = 2;
  I2CReadLength = 4;
  I2CMasterBuffer[0] = PCF8594_ADDR;
  I2CMasterBuffer[1] = 0x00;		/* address */
  I2CMasterBuffer[2] = PCF8594_ADDR | RD_BIT;
  I2CEngine();
  return 0;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
