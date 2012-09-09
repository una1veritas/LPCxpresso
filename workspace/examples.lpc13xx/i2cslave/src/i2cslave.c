/*****************************************************************************
 *   i2cslave.c:  I2CSlave C file for NXP LPC13xx Family Microprocessors
 *
 *   Copyright(C) 2008, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2008.07.19  ver 1.00    Preliminary version, first Release
 *
*****************************************************************************/
#include "LPC13xx.h"			/* LPC134x Peripheral Registers */
#include "type.h"
#include "i2cslave.h"

volatile uint32_t I2CMasterState = I2C_IDLE;
volatile uint32_t I2CSlaveState = I2C_IDLE;

volatile uint32_t I2CMode;

volatile uint8_t I2CWrBuffer[BUFSIZE];
volatile uint8_t I2CRdBuffer[BUFSIZE];
volatile uint32_t I2CReadLength;
volatile uint32_t I2CWriteLength;

volatile uint32_t RdIndex = 0;
volatile uint32_t WrIndex = 0;

/* 
From device to device, the I2C communication protocol may vary, 
in the example below, the protocol uses repeated start to read data from or 
write to the device:
For master read: the sequence is: STA,Addr(W),offset,RE-STA,Addr(r),data...STO 
for master write: the sequence is: STA,Addr(W),offset,RE-STA,Addr(w),data...STO
Thus, in state 8, the address is always WRITE. in state 10, the address could 
be READ or WRITE depending on the I2C command.
*/   

/*****************************************************************************
** Function name:		I2C_IRQHandler
**
** Descriptions:		I2C interrupt handler, deal with master mode only.
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
void I2C_IRQHandler(void) 
{
  uint8_t StatValue;

  /* this handler deals with master read and master write only */
  StatValue = LPC_I2C->STAT;
  switch ( StatValue )
  {
	case 0x60:					/* An own SLA_W has been received. */
	case 0x68:
	RdIndex = 0;
	LPC_I2C->CONSET = I2CONSET_AA;	/* assert ACK after SLV_W is received */
	LPC_I2C->CONCLR = I2CONCLR_SIC;
	I2CSlaveState = I2C_WR_STARTED;
	break;
	
	case 0x80:					/*  data receive */
	case 0x90:
	if ( I2CSlaveState == I2C_WR_STARTED )
	{
	  I2CRdBuffer[RdIndex++] = LPC_I2C->DAT;
	  LPC_I2C->CONSET = I2CONSET_AA;	/* assert ACK after data is received */
	}
	else
	{
	  LPC_I2C->CONCLR = I2CONCLR_AAC;	/* assert NACK */
	}
	LPC_I2C->CONCLR = I2CONCLR_SIC;
	break;
		
	case 0xA8:					/* An own SLA_R has been received. */
	case 0xB0:
	RdIndex = 0;
	LPC_I2C->CONSET = I2CONSET_AA;	/* assert ACK after SLV_R is received */
	LPC_I2C->CONCLR = I2CONCLR_SIC;
	I2CSlaveState = I2C_RD_STARTED;
	WrIndex = I2CRdBuffer[0];	/* The 1st byte is the index. */
	break;
	
	case 0xB8:					/* Data byte has been transmitted */
	case 0xC8:
	if ( I2CSlaveState == I2C_RD_STARTED )
	{
	  LPC_I2C->DAT = I2CRdBuffer[WrIndex+1];/* write the same data back to master */
	  WrIndex++;							/* Need to skip the index byte in RdBuffer */
	  LPC_I2C->CONSET = I2CONSET_AA;		/* assert ACK  */
	}
	else
	{
	  LPC_I2C->CONCLR = I2CONCLR_AAC;		/* assert NACK  */
	}	
	LPC_I2C->CONCLR = I2CONCLR_SIC;
	break;

	case 0xC0:					/* Data byte has been transmitted, NACK */
	LPC_I2C->CONCLR = I2CONCLR_AAC;			/* assert NACK  */
	LPC_I2C->CONCLR = I2CONCLR_SIC;
	I2CSlaveState = DATA_NACK;
	break;

	case 0xA0:					/* Stop condition or repeated start has */
	LPC_I2C->CONSET = I2CONSET_AA;	/* been received, assert ACK.  */
	LPC_I2C->CONCLR = I2CONCLR_SIC;
	I2CSlaveState = I2C_IDLE;
	break;

	default:
	LPC_I2C->CONCLR = I2CONCLR_SIC;
	LPC_I2C->CONSET = I2CONSET_I2EN | I2CONSET_SI;	
	break;
  }
  return;
}

/*****************************************************************************
** Function name:		I2CSlaveInit
**
** Descriptions:		Initialize I2C controller
**
** parameters:			I2c mode is either MASTER or SLAVE
** Returned value:		true or false, return false if the I2C
**				interrupt handler was not installed correctly
** 
*****************************************************************************/
void I2CSlaveInit( void ) 
{
  /* It seems to be bit0 is for I2C, different from
  UM. To be retested along with SSP reset. SSP and I2C
  reset are overlapped, a known bug, for now, both SSP 
  and I2C use bit 0 for reset enable. Once the problem
  is fixed, change to "#if 1". */
#if 1
  LPC_SYSCON->PRESETCTRL |= (0x1<<1);
#else
  LPC_SYSCON->PRESETCTRL |= (0x1<<0);
#endif
  LPC_SYSCON->SYSAHBCLKCTRL |= (1<<5);
  LPC_IOCON->PIO0_4 &= ~0x3F;	/*  I2C I/O config */
  LPC_IOCON->PIO0_4 |= 0x01;		/* I2C SCL */
  LPC_IOCON->PIO0_5 &= ~0x3F;	
  LPC_IOCON->PIO0_5 |= 0x01;		/* I2C SDA */

  /*--- Clear flags ---*/
  LPC_I2C->CONCLR = I2CONCLR_AAC | I2CONCLR_SIC | I2CONCLR_STAC | I2CONCLR_I2ENC;    

  /*--- Reset registers ---*/
#if FAST_MODE_PLUS
  LPC_IOCON->PIO0_4 |= (0x1<<9);
  LPC_IOCON->PIO0_5 |= (0x1<<9);
  LPC_I2C->SCLL   = I2SCLL_HS_SCLL;
  LPC_I2C->SCLH   = I2SCLH_HS_SCLH;
#else
  LPC_I2C->SCLL   = I2SCLL_SCLL;
  LPC_I2C->SCLH   = I2SCLH_SCLH;
#endif

  LPC_I2C->ADR0 = PCF8594_ADDR;    
  I2CSlaveState = I2C_IDLE;
  
  /* Enable the I2C Interrupt */
  NVIC_EnableIRQ(I2C_IRQn);

  LPC_I2C->CONSET = I2CONSET_I2EN | I2CONSET_SI;
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/

