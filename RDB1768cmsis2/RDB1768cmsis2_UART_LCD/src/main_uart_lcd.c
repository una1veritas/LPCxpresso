//*****************************************************************************
//   +--+       
//   | ++----+   
//   +-++    |  
//     |     |  
//   +-+--+  |   
//   | +--+--+  
//   +----+    Copyright (c) 2009-11 Code Red Technologies Ltd.
//
// UART with LCD example project for RDB1768 development board
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
#include "uart0.h"
#include "stdio.h"
#include "lcd.h"

#include <cr_section_macros.h>
#include <NXP/crp.h>

// Variable to store CRP value in. Will be placed automatically
// by the linker when "Enable Code Read Protect" selected.
// See crp.h header for more information
__CRP const unsigned int CRP_WORD = CRP_NO_CRP ;

// Header for Code Red logo displayed on LCD
#include "codered128x37.h"

#define SERIAL_BAUD_RATE 57600

char strbuf[20];




int main(void)
{
	volatile static unsigned i = 0 ;

	int waiting_4_first_char = 1;

	unsigned char uart_in = 0;
	int joystick_clicked =0;

	
	// Initialize the ST7637 LCD Controller/driver for use
	LCDdriver_initialisation();

	 // Initialise UART0 to required baud rate
	UART0_Init(SERIAL_BAUD_RATE);

	// Plot Code Red logo at top of screen
	LCD_PlotBitmap (0, 0, codered128x37_pixel_data ,codered128x37_width, codered128x37_height);

	// Startup message for display on RDB1768's LCD screen.
	LCD_PrintString(15,40,"RDB1768 UART", COLOR_WHITE, COLOR_BLACK);
	sprintf (strbuf,"(%d)", SERIAL_BAUD_RATE);
	LCD_PrintString(30,55,strbuf, COLOR_WHITE, COLOR_BLACK);
	LCD_PrintString(0,75,"Type text in", COLOR_RED, COLOR_BLACK);
	LCD_PrintString(0,90,"PC's terminal or", COLOR_RED, COLOR_BLACK);
	LCD_PrintString(0,105,"click joystick", COLOR_RED, COLOR_BLACK);
	
	// Startup message for display in PC's terminal window.
	// You must make sure the terminal program is already
	// running when this code is executed if you want to
	// see it !
	UART0_PrintString("\r\nRDB1768 UART LCD Demonstration\r\n");
	UART0_PrintString("==============================\r\n\n");
	UART0_PrintString("Press a key within your terminal ");
	UART0_PrintString("and you will see it appear on the LCD.\r\n");
	UART0_PrintString("Click the joystick on the board ");
	UART0_PrintString("and you will see a message here.\r\n\n");


	// Enter loop, waiting for 1st character from PC (or joystick click)
	while (waiting_4_first_char == 1)
	{
		if ( (LPC_UART0->LSR & LSR_RDR) != 0 )
			{
			waiting_4_first_char = 0;	// Flag that we can exit while loop
			uart_in = LPC_UART0->RBR; 	// Read Receiver buffer register
			}

		if(((LPC_GPIO0->FIOPIN>>6) & 1) == 0)
		{
			joystick_clicked = 1; 		// Set flag to indicate joystick clicked
			waiting_4_first_char = 0;	// Flag that we can exit while loop
			while (((LPC_GPIO0->FIOPIN>>6) & 1) == 0); // Debounce joystick
		}
	}

	// Now switch to main terminal window from 'title' screen
	LCD_ResetTerminal(COLOR_BLACK);
	LCD_PrintString2Terminal ("Comms started:\n", LCD_TERMINAL_NoNL, COLOR_RED, COLOR_YELLOW);

	// Enter infinite loop
	while(1) {
		// Check if we have a character received over UART to display
		if ((uart_in == 10) || (uart_in == 13)|| ((uart_in >= 32) && (uart_in <= 126)))
		{
			LCD_Print2Terminal (uart_in, COLOR_RED, COLOR_YELLOW);
			uart_in = 0;
		}
		// Check if a joystick click has been detected
		if (joystick_clicked == 1)
		{
			UART0_PrintString ("\n\r<<JOYSTICK CLICK>>\n\r");
			LCD_PrintString2Terminal ("<JOYSTICK CLICK>\n", LCD_TERMINAL_NL, COLOR_RED, COLOR_YELLOW);
			joystick_clicked = 0;
		}

		// Check if there is another character from the PC to read over the UART
		if ( (LPC_UART0->LSR & LSR_RDR) != 0 )
			{
			uart_in = LPC_UART0->RBR; // Read Receiver buffer register
			}

		// Check for a joystick click being detected
		if(((LPC_GPIO0->FIOPIN>>6) & 1) == 0)
		{
			joystick_clicked = 1;
			while (((LPC_GPIO0->FIOPIN>>6) & 1) == 0); // Debounce joystick
		}

		i++;	// increment counter for iterations through infinite loop

	}
	return 0;
}
