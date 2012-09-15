//*****************************************************************************
//   +--+       
//   | ++----+   
//   +-++    |  
//     |     |  
//   +-+--+  |   
//   | +--+--+  
//   +----+    Copyright (c) 2009-11 Code Red Technologies Ltd.
//
// main_adcmeter.c  - demonstrates the use of the ADC potentiometer
//                    on the RDB1768 development board.
//
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

#include "LPC17xx.h"
#include <stdio.h>
#include "lcd.h"
#include "systick.h"

#include <cr_section_macros.h>
#include <NXP/crp.h>

// Variable to store CRP value in. Will be placed automatically
// by the linker when "Enable Code Read Protect" selected.
// See crp.h header for more information
__CRP const unsigned int CRP_WORD = CRP_NO_CRP ;


// Header for Code Red logo displayed on LCD
#include "codered128x37.h"

// ***********
// * Defines used for drawing the meter
// ***********
// Top left corner of meters (including outer rectangle)
#define METER_X_OFFSET 45
#define METER0_Y_OFFSET 90
// Top left corner of top meter (excluding outer rectangle)
#define METER_X_INN_OS (METER_X_OFFSET+1)
#define METER0_Y_INN_OS (METER0_Y_OFFSET+1)
// Width of meter (excluding outer rectangle)
#define METER_X_INNERWIDTH 64
// Height of meter (excluding outer rectangle)
#define METER_Y_INNERWIDTH 20
	// Width of meter (inccluding outer rectangle)
#define METER_X_OUTERWIDTH (METER_X_INNERWIDTH+2)
// Height of meter (including outer rectangle)
#define METER_Y_OUTERWIDTH (METER_Y_INNERWIDTH+2)
// Vertical position of bottom meter (including outer rectangle)

// ***********
// * Defines related to ADC
// ***********
// PCADC / PCAD
#define ADC_POWERON (1 << 12) 
#define PCLK_ADC 24
#define PCLK_ADC_MASK (3 << 24)

// AD0.0 - P0.23, PINSEL1 [15:14] = 01
#define SELECT_ADC0 (0x1<<14)

// ADOCR constants
#define START_ADC (1<<24)
#define OPERATIONAL_ADC (1 << 21)
#define SEL_AD0 (1 <<0)
#define ADC_DONE_BIT	(1 << 31)

// Buffer to contain string version of value read from ADC
// 4 character, plus zero terminator
char strbuf [5];

// **************
// * main routine
// **************
int main(void) {

	volatile static int i = 0 ;
	int adval, adval_64;

	// *******************
	// * SET UP LCD SCREEN
	// *******************

	// Initialize the ST7637 LCD Controller/driver for use
	LCDdriver_initialisation();
	
	// Plot Code Red logo at top of screen
	LCD_PlotBitmap (0, 0, codered128x37_pixel_data ,codered128x37_width, codered128x37_height);

	// Print 'title' text
	LCD_PrintString(20,50,"RDB1768 ADC", COLOR_WHITE, COLOR_BLACK);
	LCD_PrintString(12,66,"Potentiometer", COLOR_WHITE, COLOR_BLACK);

	// Draw outer rectangle for holding adc potentiometer meter
	LCD_Rect (METER_X_OFFSET, METER_X_OFFSET + METER_X_OUTERWIDTH,
			METER0_Y_OFFSET, METER0_Y_OFFSET + METER_Y_OUTERWIDTH,
			COLOR_WHITE);

	// ************
	// * Set up ADC
	// ************

	// Turn on power to ADC block 
	LPC_SC->PCONP |=  ADC_POWERON;

	// Turn on ADC peripheral clock
	LPC_SC->PCLKSEL0 &= ~(PCLK_ADC_MASK);
	LPC_SC->PCLKSEL0 |=  (3 << PCLK_ADC);
		
	// Set P0.23 to AD0.0 in PINSEL1
	LPC_PINCON->PINSEL1	|= SELECT_ADC0; 


	// *****************************************
	// * Set up SysTick - used to provide delays
	// *****************************************
	
	// Setup SysTick Timer to interrupt at 1 msec intervals
	if (SysTick_Config(SystemCoreClock / 1000)) {
	    while (1);  // Capture error
	}


	// ****************************************************
	// * Enter main loop - reading ADC pot and updating LCD
	// ****************************************************
	while(1) {

		// Start A/D conversion for on AD0.0
		LPC_ADC->ADCR = START_ADC | OPERATIONAL_ADC | SEL_AD0 ;

		do {
			adval = LPC_ADC->ADGDR;            // Read A/D Data Register
		} while ((adval & ADC_DONE_BIT) == 0); // Wait for end of A/D Conversion

		// Stop A/D Conversion
		LPC_ADC->ADCR &= ~(START_ADC | OPERATIONAL_ADC | SEL_AD0) ;
		
		// Extract AD0.0 value - 12 bit result in bits [15:4]
		adval = (adval >> 4) & 0x0FFF ;            

		//Convert integer ADC value to string
		sprintf (strbuf, "%04d", adval);

		//Display ADC value on LCD
		LCD_PrintString(8,95,strbuf, COLOR_RED, COLOR_BLACK);

		// Scale ADC value from range of 0-4095 down to 0-63
		// for use in drawing meter on LCD
		adval_64 = adval >> 6;

		// Draw red bar in meter
		if (adval_64 > 1)
			// Don't draw if we have zero length bar
			LCD_FilledRect (METER_X_INN_OS, METER_X_INN_OS + adval_64 +1,
				METER0_Y_INN_OS, METER0_Y_INN_OS + METER_Y_INNERWIDTH,
				COLOR_RED);

		// Overwrite previous 'extra' red in case where bar has shrunk
		if (adval_64 < METER_X_INNERWIDTH-1)
			// Don't need to overwrite if bar at max
			LCD_FilledRect (METER_X_INN_OS+1+adval_64,
				METER_X_INN_OS + METER_X_INNERWIDTH, METER0_Y_INN_OS,
				METER0_Y_INN_OS + METER_Y_INNERWIDTH, COLOR_BLACK);

	    systick_delay (250); // wait a 1/4 of a second (250ms)

	    i++ ;	// increment loop counter

	}	//	end of while(1) infinite loop

	return 0 ;
}
