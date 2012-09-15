//*****************************************************************************
//   +--+
//   | ++----+
//   +-++    |
//     |     |
//   +-+--+  |
//   | +--+--+
//   +----+    Copyright (c) 2010 Code Red Technologies Ltd.
//
// rdb1768_spi.c - This file contains the functions needed to use EFSL for
//                 accessing files on a micro SD-card connected to the
//                 RDB1768 /LPC1768.
//               - This is based on the original lpc2000_spi.c file from EFSL
//
// Software License Agreement
//
// The software is owned by Code Red Technologies and/or its suppliers, and is
// protected under applicable copyright laws.  All rights are reserved.  Any
// use in violation of the foregoing restrictions may subject the user to criminal
// sanctions under applicable laws, as well as to civil liability for the breach
// of the terms and conditions of this license.
//
// THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
// OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
// USE OF THIS SOFTWARE FOR COMMERCIAL DEVELOPMENT AND/OR EDUCATION IS SUBJECT
// TO A CURRENT END USER LICENSE AGREEMENT (COMMERCIAL OR EDUCATIONAL) WITH
// CODE RED TECHNOLOGIES LTD.
//

#include "LPC17xx.h"
#include "rdb1768_spi.h"
#include "sd.h"
#include "config.h"
/*****************************************************************************/

// SP0SPCR  Bit-Definitions
#define CPHA    3
#define CPOL    4
#define MSTR    5
// SP0SPSR  Bit-Definitions
#define SPIF	7

#define SPI_IODIR			LPC_GPIO0->FIODIR
#define SPI_SCK_PIN			15		/* Clock		P0.15 out		(PINSEL0) */
#define SPI_SSEL_PIN		16		/* Card-Select	P0.16 GPIO out	(PINSEL1) */
#define SPI_MISO_PIN		17		/* from Card	P0.17 in		(PINSEL1) */
#define SPI_MOSI_PIN		18		/* to Card		P0.18 out		(PINSEL1) */

#define SPI_PINSEL			LPC_PINCON->PINSEL1
#define SPI_SCK_FUNCMASK	(3 << 30) // P0.15 - PINSEL0 [31:30]
#define SPI_SSEL_FUNCMASK	(3 << 0)  // P0.16 - PINSEL1 [1:0]
#define SPI_MISO_FUNCMASK	(3 << 2)  // P0.17 - PINSEL1 [3:2]
#define SPI_MOSI_FUNCMASK	(3 << 4)  // P0.18 - PINSEL1 [5:4]

#define SPI_SCK_FUNCBIT		(3 << 30)
#define SPI_SSEL_FUNCBIT	(0 << 0) // Note - SSEL needed as GPIO
#define SPI_MISO_FUNCBIT	(3 << 2)
#define SPI_MOSI_FUNCBIT	(3 << 4)

#define SPI_PRESCALE_REG	LPC_SPI->SPCCR

#define SPI_PRESCALE_MIN  8

#define SELECT_CARD()   LPC_GPIO0->FIOCLR = (1 << SPI_SSEL_PIN)
#define UNSELECT_CARD() LPC_GPIO0->FIOSET = (1 << SPI_SSEL_PIN)


esint8 if_initInterface(hwInterface* file, eint8* opts)
{
	euint32 sc;
	
	if_spiInit(file); /* init at low speed */
	
	if(sd_Init(file)<0)	{
		DBG((TXT("Card failed to init, breaking up...\n")));
		return(-1);
	}
	if(sd_State(file)<0){
		DBG((TXT("Card didn't return the ready state, breaking up...\n")));
		return(-2);
	}
	
	// file->sectorCount=4; /* FIXME ASAP!! */
	
	sd_getDriveSize(file, &sc);
	file->sectorCount = sc/512;
	if( (sc%512) != 0) {
		file->sectorCount--;
	}
	DBG((TXT("Drive Size is %lu Bytes (%lu Sectors)\n"), sc, file->sectorCount));
	
	if_spiSetSpeed(SPI_PRESCALE_MIN);
	// if_spiSetSpeed(100); /* debug - slower */
	
	DBG((TXT("Init done...\n")));
	return(0);
}
/*****************************************************************************/ 

esint8 if_readBuf(hwInterface* file,euint32 address,euint8* buf)
{
	return(sd_readSector(file,address,buf,512));
}
/*****************************************************************************/

esint8 if_writeBuf(hwInterface* file,euint32 address,euint8* buf)
{
	return(sd_writeSector(file,address, buf));
}
/*****************************************************************************/ 

esint8 if_setPos(hwInterface* file,euint32 address)
{
	return(0);
}
/*****************************************************************************/ 

// Utility-functions which does not toogle CS.
// Only needed during card-init. During init
// the automatic chip-select is disabled for SSP

static euint8 my_if_spiSend(hwInterface *iface, euint8 outgoing)
{
	LPC_SPI->SPDR = outgoing;
	while (!(LPC_SPI->SPSR & (1 << SPIF)));
	return LPC_SPI->SPDR;
}
/*****************************************************************************/ 

void if_spiInit(hwInterface *iface)
{
	int i;

	DBG((TXT("spiInit for SPI(0)\n")));

	// Turn on the power
	LPC_SC->PCONP |= (1<<8); // PCSPI

	// Clock
	LPC_SC->PCLKSEL0 &= ~(3<<16);  // PCLK_SPI
	LPC_SC->PCLKSEL0 |=  (1<<16);  // PCLK_periph = CCLK

	// setup GPIO
	SPI_IODIR |= (1 << SPI_SCK_PIN) | (1 << SPI_MOSI_PIN) | (1 << SPI_SSEL_PIN);
	SPI_IODIR &= ~(1 << SPI_MISO_PIN);

	//// reset Pin-Functions
	// P0.15 set to SCK
	LPC_PINCON->PINSEL0 &= ~SPI_SCK_FUNCMASK;
	LPC_PINCON->PINSEL0 |=  SPI_SCK_FUNCBIT;
	// P0.16, P0.17, P0.18 set to SSEL,MISI, MOSI
	SPI_PINSEL &= ~(SPI_MOSI_FUNCMASK | SPI_MISO_FUNCMASK | SPI_SSEL_FUNCMASK);
	SPI_PINSEL |=  (SPI_MOSI_FUNCBIT | SPI_MISO_FUNCBIT | SPI_SSEL_FUNCBIT);

	// enable SPI-Master
	LPC_SPI->SPCR = (1 << MSTR) | (0 << CPOL);	// TODO: check CPOL

	UNSELECT_CARD();

	// Code for GPIO setup
    /* Switch the SSI TX line to a GPIO and drive it high too. */
    // P0.18 back to GPIO
	LPC_PINCON->PINSEL1 &= ~(SPI_MOSI_FUNCMASK);
	LPC_GPIO0->FIODIR |= (1<<SPI_MOSI_PIN);
	LPC_GPIO0->FIOSET = (1<<SPI_MOSI_PIN);

	// low speed during init
	if_spiSetSpeed(254); 

	/* Send 20 spi commands with card not selected */
	for(i=0;i<21;i++)
		my_if_spiSend(iface,0xff);

    // P0.18 back to SPI
	LPC_PINCON->PINSEL1 |= (SPI_MOSI_FUNCBIT);

}
/*****************************************************************************/

void if_spiSetSpeed(euint8 speed)
{
	speed &= 0xFE;
	if ( speed < SPI_PRESCALE_MIN  ) speed = SPI_PRESCALE_MIN ;
	SPI_PRESCALE_REG = speed;
}

/*****************************************************************************/

euint8 if_spiSend(hwInterface *iface, euint8 outgoing)
{
	euint8 incoming;

	SELECT_CARD();
	LPC_SPI->SPDR = outgoing;
	while (!(LPC_SPI->SPSR & (1 << SPIF)));
	incoming = LPC_SPI->SPDR;
	UNSELECT_CARD();

	return(incoming);
}
/*****************************************************************************/

