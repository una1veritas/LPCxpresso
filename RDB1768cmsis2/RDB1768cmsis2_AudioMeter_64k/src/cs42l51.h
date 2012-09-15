//*****************************************************************************
//   +--+       
//   | ++----+   
//   +-++    |  
//     |     |  
//   +-+--+  |   
//   | +--+--+  
//   +----+    Copyright (c) 2010 Code Red Technologies Ltd.
//
// cs42l51.h
// Header file for audio driver code for CS42L51 audio codec used on original
// RDB1768
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


#ifndef CS42L51_H_
#define CS42L51_H_

#include "type.h"

#define CS42L51_ADDR 0x94			//I2C address of the Codec

// Sub-addresses of registers within the Codec
#define CS42L51_ID_01 0x01
#define CS42L51_PWRCTL_02 0x02
#define CS42L51_BEEPCTL_14 0x14
#define CS42L51_DACCTL_09 0x09
#define CS42L51_IFCTL_04 0x04
#define CS42L51_PCMX_11 0x11

void CS42L41_vfAudioInit(void);
void CS42L41_I2S_IRQHandler(void);

#endif /*CS42L51_H_*/
