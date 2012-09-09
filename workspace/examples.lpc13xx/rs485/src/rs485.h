/*****************************************************************************
 *   rs485.h:  Header file for NXP LPC13xx Family Microprocessors
 *
 *   Copyright(C) 2008, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2008.08.21  ver 1.00    Preliminary version, first Release
 *
******************************************************************************/
#ifndef __RS485_H 
#define __RS485_H

/* TO test RS485, program one board with RS485_RX to 1(RX), one
board with RS485_RX to 0(TX). reset TX board to send out a string
with a RS485 slave address first, and then check the content of 
UARTBuffer in the RX board. */
#define RS485_RX			1		/* 1 is RX, 0 is TX. */
#define DIR_CTRL			0
#define RS485_NMM			1		/* 1 is NMM mode, 0 is AAD mode. */

/*if RS485_ENABLED is set, set RS485 slave address. */
#define	RS485_SLAVE_ADR		0xC0

#define IER_RBR		0x01
#define IER_THRE	0x02
#define IER_RLS		0x04

#define IIR_PEND	0x01
#define IIR_RLS		0x03
#define IIR_RDA		0x02
#define IIR_CTI		0x06
#define IIR_THRE	0x01

#define LSR_RDR		0x01
#define LSR_OE		0x02
#define LSR_PE		0x04
#define LSR_FE		0x08
#define LSR_BI		0x10
#define LSR_THRE	0x20
#define LSR_TEMT	0x40
#define LSR_RXFE	0x80

#define BUFSIZE		0x40

/* RS485 mode definition. */
#define RS485_NMMEN		(0x1<<0)
#define RS485_RXDIS		(0x1<<1)
#define RS485_AADEN		(0x1<<2)
#define RS485_SEL		(0x1<<3)
#define RS485_DCTRL		(0x1<<4)
#define RS485_OINV		(0x1<<5)


void RS485Init(uint32_t Baudrate);
void UART_IRQHandler(void);
void RS485Send(uint8_t *BufferPtr, uint32_t Length);

#endif /* end __RS485_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
