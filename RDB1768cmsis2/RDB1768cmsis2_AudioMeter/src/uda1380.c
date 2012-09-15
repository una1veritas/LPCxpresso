//*****************************************************************************
//   +--+
//   | ++----+
//   +-++    |
//     |     |
//   +-+--+  |
//   | +--+--+
//   +----+    Copyright (c) 2010 Code Red Technologies Ltd.
//
// uda1380.c
// Version of audio driver code for UDA1380 audio codec used on RDB1768v2
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

#include "LPC17xx.h"
#include "type.h"
#include "i2c.h"

#include "delay.h"
#include <math.h>
#include <stdlib.h>
#include <stdint.h>

#include "RDB1768_AUDIO.h"
#include "uda1380.h"

extern volatile uint32_t I2CCount;
extern volatile uint8_t I2CMasterBuffer[BUFSIZE];
extern volatile uint32_t I2CCmd, I2CMasterState;
extern volatile uint32_t I2CReadLength, I2CWriteLength;

extern long int gQ31_Peak_L, gQ31_Peak_R;
extern long int gQ31_Peak[2];

long int Q31_I2S_Left, Q31_I2S_Right;

static void uda1380_CodecInit(void)
{
	uint32_t temp;

	if ( I2CInit( (uint32_t)I2CMASTER ) == FALSE )	/* initialize I2c */
	{
		while ( 1 );				/* Fatal error */
	}

	vF_I2C_ClearBuffer();
	I2CWriteLength = 4;
	I2CReadLength = 0;
	I2CMasterBuffer[0] = UDA1380_ADDR;
	I2CMasterBuffer[1] =  UDA1380_SW_RESET;	//address
	I2CMasterBuffer[2] =  0xff;	//msb data 0x00
	I2CMasterBuffer[3] = 0xff;	//lsb data
	I2CEngine();

	// Power control
	vF_I2C_ClearBuffer();
	I2CWriteLength = 4;
	I2CReadLength = 0;
	I2CMasterBuffer[0] = UDA1380_ADDR;
	I2CMasterBuffer[1] = UDA1380_PWRCTL_02;
	temp = (1 << 13) | (1 << 10) | ( 1 << 8) | (1 << 7) | (1 << 6) | (1 << 3) | (1<<2) | (1 << 1) | (1<<0);
	I2CMasterBuffer[2] = (uint8_t) ((temp >> 8) & 0xff);
	I2CMasterBuffer[3] =(uint8_t)(temp & 0xff);
	I2CEngine();

	
	vF_I2C_ClearBuffer();
	I2CWriteLength = 4;
	I2CReadLength = 0;
	I2CMasterBuffer[0] = UDA1380_ADDR;
	I2CMasterBuffer[1] = UDA1380_I2SSET_01;
	I2CMasterBuffer[2] =  0x00;
	I2CMasterBuffer[3] =  0x00;
	I2CEngine();
	
	
	/* Analog mixer  (AVC) */
	/* the analog mixer is muted initially */
	vF_I2C_ClearBuffer();
	I2CWriteLength = 4;
	I2CReadLength = 0;
	I2CMasterBuffer[0] = UDA1380_ADDR;
	I2CMasterBuffer[1] = UDA1380_ANAMIX_03;
	I2CMasterBuffer[2] =  0x3f;
	I2CMasterBuffer[3] =  0x3f;
	I2CEngine();

	// Mute
	vF_I2C_ClearBuffer();
	I2CWriteLength = 4;
	I2CReadLength = 0;
	I2CMasterBuffer[0] = UDA1380_ADDR;
	I2CMasterBuffer[1] = UDA1380_MUTDEM_13;
	I2CMasterBuffer[2] =  0x00;
	I2CMasterBuffer[3] =  0x00;
	I2CEngine();
	
	vF_I2C_ClearBuffer();
	I2CWriteLength = 4;
	I2CReadLength = 0;
	I2CMasterBuffer[0] = UDA1380_ADDR;
	I2CMasterBuffer[1] = UDA1380_CLKSET_00;
	temp = (1<<11) | (1<<10) | (1<<9) | (1<<8) | (1);
	I2CMasterBuffer[2] = (uint8_t) ((temp >> 8) & 0xff);
	I2CMasterBuffer[3] =(uint8_t)(temp & 0xff);;
//	I2CMasterBuffer[2] = 0x00;
//	I2CMasterBuffer[3] = 0x00;;
	I2CEngine();

	vF_I2C_ClearBuffer();
	I2CWriteLength = 4;
	I2CReadLength = 0;
	I2CMasterBuffer[0] = UDA1380_ADDR;
	I2CMasterBuffer[1] = UDA1380_ADCSET_22;
	temp = (0<<2);
	I2CMasterBuffer[2] = (uint8_t) ((temp >> 8) & 0xff);
	I2CMasterBuffer[3] =(uint8_t)(temp & 0xff);;
	I2CEngine();

	// Note that the ADC must be un-muted in here
	vF_I2C_ClearBuffer();
	I2CWriteLength = 4;
	I2CReadLength = 0;
	I2CMasterBuffer[0] = UDA1380_ADDR;
	I2CMasterBuffer[1] = UDA1380_PGAMUT_21;
	temp = 0;
	I2CMasterBuffer[2] = (uint8_t) ((temp >> 8) & 0xff);
	I2CMasterBuffer[3] =(uint8_t)(temp & 0xff);;
	I2CEngine();

}

#define AUDIO_INIT_DELAY 2000
// Initialize all Audio components
void UDA1380_vfAudioInit(void)
{
	// Put the codec in reset - NCODEC_RESET - P0.10
	LPC_GPIO0->FIODIR |= (1<<10);
	LPC_GPIO0->FIOCLR |= (1<<10);

	delay (AUDIO_INIT_DELAY);

	// Bring it out of reset
	LPC_GPIO0->FIOSET |= (1<<10);

	// Init the ctrl regs in the codec using I2C
//	vF_CodecInit();

//	uda1380_init();

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


	// P0.7 = I2STX_CLK - the bit clock
	LPC_PINCON->PINSEL0 |= (1<<14);
	// P0.8 = I2STX_WS - the word clock
	LPC_PINCON->PINSEL0 |= (1<<16);
	// P0.9 = I2STX_SD - data to codec
	LPC_PINCON->PINSEL0 |= (1<<18);
	// P0.25 = I2SRX_SD - data from codec
	LPC_PINCON->PINSEL1 |= (2<<18);

	// P4.28 RX_MCLK - now an output
	LPC_PINCON->PINSEL9 |= (1<<24);

	// P4.29 TX_MCLK
	LPC_PINCON->PINSEL9 |= (1<<26);


	//new for r3
	// P0.4 = I2SRX_CLK - the bit clock
	LPC_PINCON->PINSEL0 |= (1<<8);
	// P0.24 = I2SRX_WS - the word clock
	LPC_PINCON->PINSEL1 |= (0x2<<16);


#ifdef CODEC16BIT

	LPC_I2S->I2SRXRATE = (1<<8) | (1);
	LPC_I2S->I2STXRATE = (1<<8) | (1);

	// MCLK for RX
	LPC_I2S->I2SRXMODE = (2);	//from TX MCLK

	// MCLK for TX
	LPC_I2S->I2STXMODE = (1<<3);	// generated

	// MCLK is 256xFs
	// Bitclock rate is 32xFs = MCLK/8
	LPC_I2S->I2STXBITRATE = 7;
	LPC_I2S->I2SRXBITRATE = 7;

	// RESET I2S
	LPC_I2S->I2SDAO = (1<<4) | (1<<3);
	LPC_I2S->I2SDAI = (1<<4) | (1<<3);

	// Codec works in 16-bit per channel mode.
	LPC_I2S->I2SDAI = 0x1 | (15<<6);
	LPC_I2S->I2SDAO = 0x1 | (15<<6);

#else
	// Codec works in 32-bits per channel mode.

	// MCLK rates
	LPC_I2S->I2SRXRATE = (1<<8) | (1);
	LPC_I2S->I2STXRATE = (1<<8) | (1);

	// MCLK for RX
	LPC_I2S->I2SRXMODE = (1<<3);		//from TX MCLK

	// MCLK for TX
	LPC_I2S->I2STXMODE = (1<<3);	// generated

	// MCLK is 256xFs
	// Bitclock rate is 64xFs = MCLK/4
	LPC_I2S->I2STXBITRATE = 3;
	LPC_I2S->I2SRXBITRATE = 3;

	// Codec works in 32-bit per channel mode.
	LPC_I2S->I2SDAI = 0x3 | (31<<6);
	LPC_I2S->I2SDAO = 0x3 | (31<<6);

	// RESET I2S
	LPC_I2S->I2SDAO |= (1<<4) | (1<<3);
	LPC_I2S->I2SDAI |= (1<<4) | (1<<3);
	LPC_I2S->I2SDAO &= ~((1<<4) | (1<<3));
	LPC_I2S->I2SDAI &= ~((1<<4) | (1<<3));

#endif

	// It appears that the I2S MCLK must be running before the codec will talk
	// on the I2C!
	uda1380_CodecInit();

	// Turn on I2S interrupts in NVIC
	// rx int, rx depth 4, tx depth 4
	LPC_I2S->I2SIRQ = (1<<0) | (4<<8) | (4<<16);
	NVIC_EnableIRQ(I2S_IRQn);

}

void UDA1380_I2S_IRQHandler(void)
{
	long int Q31_I2S_abs_L, Q31_I2S_abs_R;

#ifdef CODEC16BIT
	long int li_PackedI2S;
	li_PackedI2S = LPC_I2S->I2SRXFIFO;
	Q31_I2S_Left = li_PackedI2S << 16;

	Q31_I2S_Right = LPC_I2S->I2SRXFIFO >> 16;
	Q31_I2S_Right <<=16;
#else
	// Codec works in 32-bits per channel mode.
	Q31_I2S_Left = (LPC_I2S->I2SRXFIFO);
	Q31_I2S_Right = (LPC_I2S->I2SRXFIFO);
#endif

	// Convert back to 24-bit right justified values for the codec
	LPC_I2S->I2STXFIFO = Q31_I2S_Left;
	LPC_I2S->I2STXFIFO = Q31_I2S_Right;
//	LPC_I2S->I2STXFIFO = 0xaaaaaaaa;
//	LPC_I2S->I2STXFIFO = 0x0;

	Q31_I2S_abs_L = abs(Q31_I2S_Left);
	Q31_I2S_abs_R = abs(Q31_I2S_Right);

	if(Q31_I2S_abs_L > gQ31_Peak[1])
		gQ31_Peak[1] = Q31_I2S_abs_L;

	if(Q31_I2S_abs_R > gQ31_Peak[0])
		gQ31_Peak[0] = Q31_I2S_abs_R;

}



