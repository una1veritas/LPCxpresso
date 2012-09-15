//*****************************************************************************
//   +--+
//   | ++----+
//   +-++    |
//     |     |
//   +-+--+  |
//   | +--+--+
//   +----+    Copyright (c) 2010 Code Red Technologies Ltd.
//
// rdb1768_spi.h - Headerfile for rdb1768_spi.c
//               - This is based on the original lpc2000_spi.h file from EFSL
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

#ifndef __RDB1768_SPI_H_
#define __RDB1768_SPI_H_

#ifndef FALSE
#define FALSE	0x00
#define TRUE	0x01
#endif

#include "debug.h"
#include "config.h"


/*************************************************************\
              hwInterface
               ----------
* FILE* 	imagefile		File emulation of hw interface.
* long		sectorCount		Number of sectors on the file.
\*************************************************************/
struct  hwInterface{
	/*FILE 	*imageFile;*/
	eint32  	sectorCount;
};
typedef struct hwInterface hwInterface;

esint8 if_initInterface(hwInterface* file,eint8* opts);
esint8 if_readBuf(hwInterface* file,euint32 address,euint8* buf);
esint8 if_writeBuf(hwInterface* file,euint32 address,euint8* buf);
esint8 if_setPos(hwInterface* file,euint32 address);

void if_spiInit(hwInterface *iface);
void if_spiSetSpeed(euint8 speed);
euint8 if_spiSend(hwInterface *iface, euint8 outgoing);

#endif
