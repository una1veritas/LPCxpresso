//*****************************************************************************
//   +--+
//   | ++----+
//   +-++    |
//     |     |
//   +-+--+  |
//   | +--+--+
//   +----+    Copyright (c) 2010 Code Red Technologies Ltd.
//
// uda1380.h
// Header file for audio driver code for UDA1380 audio codec used on RDB1768v2
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
//*****************************************************************************

#ifndef UDA1380_H_
#define UDA1380_H_

#define UDA1380_ADDR	0x30	//I2C address of the Codec

// Sub-addresses of registers within the Codec
#define UDA1380_CLKSET_00 0x00
#define UDA1380_I2SSET_01 0x01
#define UDA1380_PWRCTL_02 0x02
#define UDA1380_ANAMIX_03 0x03
#define UDA1380_HPHONE_04 0x04
#define UDA1380_MASVOL_10 0x10
#define UDA1380_MIXVOL_11 0x11
#define UDA1380_TONCTL_12 0x12
#define UDA1380_MUTDEM_13 0x13
#define UDA1380_MIXOVS_14 0x14
#define UDA1380_DECVOL_20 0x20
#define UDA1380_PGAMUT_21 0x21
#define UDA1380_ADCSET_22 0x22
#define UDA1380_AGCSET_23 0x23

#define UDA1380_SW_RESET 0x7F

void UDA1380_vfAudioInit(void);
void UDA1380_I2S_IRQHandler(void);

#endif /*UDA1380_H_*/
