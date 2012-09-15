//*****************************************************************************
//   +--+       
//   | ++----+   
//   +-++    |  
//     |     |  
//   +-+--+  |   
//   | +--+--+  
//   +----+    Copyright (c) 2010 Code Red Technologies Ltd.
//
// RDB1768_AUDIO.c
// Top level audio driver code. Calls appropriate audio codec code depending
// upon which version of the RDB1768 the code is running on.
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

#include "RDB1768_AUDIO.h"
#include "cs42l51.h"
#include "uda1380.h"
#include "LPC17xx.h"
#include "i2c.h"
#include "whichRDB.h"


extern volatile uint32_t I2CCount;
extern volatile uint8_t I2CMasterBuffer[BUFSIZE];
extern volatile uint32_t I2CCmd, I2CMasterState;
extern volatile uint32_t I2CReadLength, I2CWriteLength;

extern uint32_t RDBversion;

long int gQ31_Peak_L, gQ31_Peak_R;
long int gQ31_Peak[2];

// Clear the I2C buffer
void vF_I2C_ClearBuffer(void)
{
	int i;
	
	for ( i = 0; i < BUFSIZE; i++ )	/* clear buffer */
	{
		I2CMasterBuffer[i] = 0;
	}
}

// Initialize all Audio components
void vfAudioInit(void)
{
	if (RDBversion == RDBv1)
		CS42L41_vfAudioInit();
	else
		UDA1380_vfAudioInit();
}


void I2S_IRQHandler(void)
{
	if (RDBversion == RDBv1)
		CS42L41_I2S_IRQHandler();
	else
		UDA1380_I2S_IRQHandler();
}
