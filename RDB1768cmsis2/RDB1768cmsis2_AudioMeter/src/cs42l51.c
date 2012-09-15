//*****************************************************************************
//   +--+       
//   | ++----+   
//   +-++    |  
//     |     |  
//   +-+--+  |   
//   | +--+--+  
//   +----+    Copyright (c) 2010 Code Red Technologies Ltd.
//
// cs42l51.c
// Version of audio driver code for CS42L51 audio codec used on original RDB1768
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
#include "LPC17xx.h"
#include "type.h"
#include "i2c.h"

#include "delay.h"
#include <math.h>
#include <stdlib.h>

extern volatile uint32_t I2CCount;
extern volatile uint8_t I2CMasterBuffer[BUFSIZE];
extern volatile uint32_t I2CCmd, I2CMasterState;
extern volatile uint32_t I2CReadLength, I2CWriteLength;

extern long int gQ31_Peak_L, gQ31_Peak_R;
extern long int gQ31_Peak[2];

extern long int Q31_I2S_Left, Q31_I2S_Right;


// Note this function is not used by the RDB1768 audio level meter
// demo, but may be of use for user-created code. It has hence been
// #ifdef'ed out to prevent compiler warning messages, rather than
// being removed. 
#ifdef NEED_TO_READ_CODEC_REG
// Read a Codec register
static uint8_t BF_ReadCodecReg(uint8_t B_MAP)
{	
	vF_I2C_ClearBuffer();
	I2CWriteLength = 1;
	I2CReadLength = 1;
	I2CMasterBuffer[0] = CS42L51_ADDR;
	I2CMasterBuffer[1] = B_MAP;
	I2CMasterBuffer[2] = CS42L51_ADDR | RD_BIT;

	I2CEngine();
	
	return I2CMasterBuffer[3];
}
#endif


// Write a Codec register
static void vF_WriteCodecReg(uint8_t B_MAP, uint8_t B_Value)
{
	vF_I2C_ClearBuffer();
	I2CWriteLength = 2;
	I2CReadLength = 0;
	I2CMasterBuffer[0] = CS42L51_ADDR;
	I2CMasterBuffer[1] = B_MAP;
	I2CMasterBuffer[2] = B_Value;
	I2CEngine();	
}

// Initialize the Codec so it talks I2S
void vF_cs42l51_CodecInit(void)
{	
	if ( I2CInit( (uint32_t)I2CMASTER ) == FALSE )	/* initialize I2c */
	{
		while ( 1 );				/* Fatal error */
	}
	
	// Have to write to the PDN register to stop it going into 'hardware mode'
	vF_WriteCodecReg(CS42L51_PWRCTL_02, 0x1);
	
	vF_WriteCodecReg(CS42L51_IFCTL_04, 0x0c);
	vF_WriteCodecReg(CS42L51_PCMX_11, 0x00);
	vF_WriteCodecReg(CS42L51_DACCTL_09, 0x00);
	vF_WriteCodecReg(CS42L51_PWRCTL_02, 0x00);
}

#define AUDIO_INIT_DELAY 2000
// Initialize all Audio components
void CS42L41_vfAudioInit(void)
{

	// Put the codec in reset - NCODEC_RESET - P0.10
	LPC_GPIO0->FIODIR |= (1<<10);
	LPC_GPIO0->FIOCLR |= (1<<10);

	delay (AUDIO_INIT_DELAY);

	// Bring it out of reset
	LPC_GPIO0->FIOSET |= (1<<10);

	// Init the ctrl regs in the codec using I2C
	vF_cs42l51_CodecInit();

	// Switch power on I2S
	LPC_SC->PCONP |= (1 << 27);

	// Set Peripheral clock up
	LPC_SC->PCLKSEL1 &= ~(3 << 22);
	LPC_SC->PCLKSEL1 |= (3 << 22);	//CCLK/8

	// Use the I2S fractional divider to create something useful
	// 44.1KHz * 256 = 11.2896MHz
	// 48KHz * 256 = 12.288MHz

	// For something close to Fs=44.1KHz
	// 48MHz/2= 24MHz.
	// 24MHz / 11.2896MHz = 2.12585 ~= 17/8

	// For something close to Fs=48KHz
	// 48MHz/2= 24MHz.
	// 24MHz / 12.288MHz = 1.953125 = 125/64

	LPC_I2S->I2SRXRATE = (1<<8) | (1);
	// P0.7 = I2STX_CLK - the bit clock
	LPC_PINCON->PINSEL0 |= (1<<14);
	// P0.8 = I2STX_WS - the word clock
	LPC_PINCON->PINSEL0 |= (1<<16);
	// P0.9 = I2STX_SD - data to codec
	LPC_PINCON->PINSEL0 |= (1<<18);
	// P0.25 = I2SRX_SDA - data from codec
	LPC_PINCON->PINSEL1 |= (2<<18);

	// Make P4.28 RX_MCLK output
	LPC_PINCON->PINSEL9 |= (1<<24);
	LPC_PINCON->PINSEL9 |= (1<<26);

	// Switch on the RX MCLK
	LPC_I2S->I2SRXMODE = (1<<3);
	// and make TX MCLK sourced from RX MCLK
	LPC_I2S->I2STXMODE = 0x2;
	// 256/4 = 64 bits per frame
	LPC_I2S->I2STXBITRATE = 3;
	LPC_I2S->I2SRXBITRATE = 3;

	// RESET I2S
	LPC_I2S->I2SDAO = (1<<4) | (1<<3);
	LPC_I2S->I2SDAI = (1<<4) | (1<<3);

	// CS codec works in 32-bit mode.
	LPC_I2S->I2SDAI = 0x3 | (0x1f<<6);
	LPC_I2S->I2SDAO = 0x3 | (0x1f<<6);

	// Turn on I2S interrupts in NVIC
	// rx int, rx depth 4, tx depth 4
	LPC_I2S->I2SIRQ = (1<<0) | (4<<8) | (4<<16);
	NVIC_EnableIRQ(I2S_IRQn);

}


void CS42L41_I2S_IRQHandler(void)
{
	long int Q31_I2S_Left, Q31_I2S_Right;
	long int Q31_I2S_abs_L, Q31_I2S_abs_R;
		
	// Read some samples from the FIFO which are 24-bit right-justified
	Q31_I2S_Left = (LPC_I2S->I2SRXFIFO) <<8;
	Q31_I2S_Right = (LPC_I2S->I2SRXFIFO) <<8;
	// Convert back to 24-bit right justified values for the codec
	LPC_I2S->I2STXFIFO = Q31_I2S_Left>>8;
	LPC_I2S->I2STXFIFO = Q31_I2S_Right>>8;

	Q31_I2S_abs_L = abs(Q31_I2S_Left);
	Q31_I2S_abs_R = abs(Q31_I2S_Right);
	
	if(Q31_I2S_abs_L > gQ31_Peak[0])
		gQ31_Peak[0] = Q31_I2S_abs_L;
	
	if(Q31_I2S_abs_R > gQ31_Peak[1])
		gQ31_Peak[1] = Q31_I2S_abs_R;
			
}
