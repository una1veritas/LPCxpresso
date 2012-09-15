//*****************************************************************************
//   +--+       
//   | ++----+   
//   +-++    |  
//     |     |  
//   +-+--+  |   
//   | +--+--+  
//   +----+    Code Red Technologies Ltd. 
//
// 
// THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
// OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.

/*
	LPCUSB, an USB device driver for LPC microcontrollers	
	Copyright (C) 2006 Bertrik Sikken (bertrik@sikken.nl)

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are met:

	1. Redistributions of source code must retain the above copyright
	   notice, this list of conditions and the following disclaimer.
	2. Redistributions in binary form must reproduce the above copyright
	   notice, this list of conditions and the following disclaimer in the
	   documentation and/or other materials provided with the distribution.
	3. The name of the author may not be used to endorse or promote products
	   derived from this software without specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
	IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
	OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
	IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, 
	INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
	NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
	DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
	THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
	THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


/**********************************
 * CodeRed - extended version of LPCUSB HID example to provide PC mouse
 **********************************/

//CodeRed
//Added ref to stdio.h to pull in semihosted printf rather than using serial
#include <stdio.h>

#include "usbapi.h"
#include "usbdebug.h"

#include "LPC17xx.h"

// RDB1768 LCD access
#include "lcd.h"

#include <cr_section_macros.h>
#include <NXP/crp.h>

// Variable to store CRP value in. Will be placed automatically
// by the linker when "Enable Code Read Protect" selected.
// See crp.h header for more information
__CRP const unsigned int CRP_WORD = CRP_NO_CRP ;

// Provide function to determine which RDB1768 version code is running on.
#include "whichRDB.h"
#define INTR_IN_EP		0x81

#define MAX_PACKET_SIZE	64

#define LE_WORD(x)		((x)&0xFF),((x)>>8)

// CodeRed
//#define REPORT_SIZE			4
#define REPORT_SIZE			3

// CodeRed
#define JOYSTICK_CLICK 	1 << 4
#define JOYSTICK_UP 	0x8
#define JOYSTICK_DOWN	0x4
#define JOYSTICK_LEFT	0x2
#define JOYSTICK_RIGHT	0x1


uint32_t RDBversion = 0;

// CodeRed
typedef struct {

    unsigned char bmButtons;        /// Bitmap state of three mouse buttons.
    signed char bX;                 /// Pointer displacement along the X axis.
    signed char bY;                 /// Pointer displacement along the Y axis.

} __attribute__ ((packed)) HIDDMouseInputReport; // GCC

HIDDMouseInputReport MouseInputReport;


static U8	abClassReqData[4];
//static U8	abReport[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
static int	_iIdleRate = 0;
static int	_iFrame = 0;

// CodeRed - replace general by mouse
/*
// see the joystick example from the usb.org HID Descriptor Tool
static U8 abReportDesc[] = {
	0x05, 0x01,
	0x15, 0x00,
	0x09, 0x04,
	0xA1, 0x01,
	0x05, 0x02,
	0x09, 0xBB,
	0x15, 0x81,
	0x25, 0x7F,
	0x75, 0x08,
	0x95, 0x01,
	0x81, 0x02,
	0x05, 0x01,
	0x09, 0x01,
	0xA1, 0x00,
	0x09, 0x30,
	0x09, 0x31,
	0x95, 0x02,
	0x81, 0x02,
	0xC0,
	0x09, 0x39,
	0x15, 0x00,
	0x25, 0x03,
	0x35, 0x00,
	0x46, 0x0E, 0x01,
	0x65, 0x14,
	0x75, 0x04,
	0x95, 0x01,
	0x81, 0x02,
	0x05, 0x09,
	0x19, 0x01,
	0x29, 0x04,
	0x15, 0x00,
	0x25, 0x01,
	0x75, 0x01,
	0x95, 0x04,
	0x55, 0x00,
	0x65, 0x00,
	0x81, 0x02,
	0xC0
};
*/
static U8 abReportDesc[] = {
/*
USAGE_PAGE (Generic Desktop)	05 01
USAGE (Mouse)	09 02
COLLECTION (Application)	A1 01 
  USAGE (Pointer)	09 01
  COLLECTION (Physical)	A1 00 
    USAGE_PAGE (Button)	05 09
    USAGE_MINIMUM (Button 1)	19 01
    USAGE_MAXIMUM (Button 3)	29 03
    LOGICAL_MINIMUM (0)	15 00 
    LOGICAL_MAXIMUM (1)	25 01 
    REPORT_COUNT (3)	95 03 
    REPORT_SIZE (1)	75 01 
    INPUT (Data,Var,Abs)	81 02 
    REPORT_COUNT (1)	95 01 
    REPORT_SIZE (5)	75 05 
    INPUT (Cnst,Var,Abs)	81 03 
    USAGE_PAGE (Generic Desktop)	05 01
    USAGE (X)	09 30
    USAGE (Y)	09 31
    LOGICAL_MINIMUM (-127)	15 81 
    LOGICAL_MAXIMUM (127)	25 7F 
    REPORT_SIZE (8)	75 08 
    REPORT_COUNT (2)	95 02 
    INPUT (Data,Var,Rel)	81 06 
  END_COLLECTION	C0
END_COLLECTION	C0
*/
0x05, 0x01,
0x09, 0x02,
0xA1, 0x01, 
0x09, 0x01,
0xA1, 0x00, 
0x05, 0x09,
0x19, 0x01,
0x29, 0x03,
0x15, 0x00, 
0x25, 0x01, 
0x95, 0x03, 
0x75, 0x01, 
0x81, 0x02, 
0x95, 0x01, 
0x75, 0x05, 
0x81, 0x03, 
0x05, 0x01,
0x09, 0x30,
0x09, 0x31,
0x15, 0x81, 
0x25, 0x7F, 
0x75, 0x08, 
0x95, 0x02, 
0x81, 0x06, 
0xC0,
0xC0,
};
		
		
static const U8 abDescriptors[] = {

/* Device descriptor */
	0x12,              		
	DESC_DEVICE,       		
	LE_WORD(0x0110),		// bcdUSB	
	0x00,              		// bDeviceClass
	0x00,              		// bDeviceSubClass
	0x00,              		// bDeviceProtocol
	MAX_PACKET_SIZE0,  		// bMaxPacketSize
	LE_WORD(0xAFFF),		// idVendor
	LE_WORD(0x0001),		// idProduct
	LE_WORD(0x0100),		// bcdDevice
	0x01,              		// iManufacturer
	0x02,              		// iProduct
	0x03,              		// iSerialNumber
	0x01,              		// bNumConfigurations

// configuration
	0x09,
	DESC_CONFIGURATION,
	LE_WORD(0x22),  		// wTotalLength
	0x01,  					// bNumInterfaces
	0x01,  					// bConfigurationValue
	0x00,  					// iConfiguration
	0x80,  					// bmAttributes
	0x32,  					// bMaxPower

// interface
	0x09,   				
	DESC_INTERFACE,
// CodeRed
	//0x00,  		 			// bInterfaceNumber	
	0x01,  		 			// bInterfaceNumber - from HID doc mouse example
	0x00,   				// bAlternateSetting
	0x01,   				// bNumEndPoints
	0x03,   				// bInterfaceClass = HID
// CodeRed
	//0x00,   				// bInterfaceSubClass	
	//	0x00,   				// bInterfaceProtocol
	0x00,   				// bInterfaceSubClass : 1 = boot class
	0x02,   				// bInterfaceProtocol : 0x2 = Mouse
	
	0x00,   				// iInterface

// HID descriptor
	0x09, 
	DESC_HID_HID, 			// bDescriptorType = HID
	LE_WORD(0x0110),		// bcdHID
	0x00,   				// bCountryCode
	0x01,   				// bNumDescriptors = report
	DESC_HID_REPORT,   		// bDescriptorType
	LE_WORD(sizeof(abReportDesc)),

// EP descriptor
	0x07,   		
	DESC_ENDPOINT,   		
	INTR_IN_EP,				// bEndpointAddress
	0x03,   				// bmAttributes = INT
	LE_WORD(MAX_PACKET_SIZE),// wMaxPacketSize
	10,						// bInterval   		

// string descriptors
	0x04,
	DESC_STRING,
	LE_WORD(0x0409),

	// manufacturer string
	0x0E,
	DESC_STRING,
	'L', 0, 'P', 0, 'C', 0, 'U', 0, 'S', 0, 'B', 0,

	// product string
	0x12,
	DESC_STRING,
	'P', 0, 'r', 0, 'o', 0, 'd', 0, 'u', 0, 'c', 0, 't', 0, 'X', 0,

	// serial number string
	0x12,
	DESC_STRING,
	'D', 0, 'E', 0, 'A', 0, 'D', 0, 'C', 0, '0', 0, 'D', 0, 'E', 0,
	
	// terminator
	0
};


/*************************************************************************
	HandleClassRequest
	==================
		HID class request handler
		
**************************************************************************/
static BOOL HandleClassRequest(TSetupPacket *pSetup, int *piLen, U8 **ppbData)
{
	U8	*pbData = *ppbData;

	switch (pSetup->bRequest) {
	
   	// get_idle
	case HID_GET_IDLE:
		DBG("GET IDLE, val=%X, idx=%X\n", pSetup->wValue, pSetup->wIndex);
		pbData[0] = (_iIdleRate / 4) & 0xFF;
		*piLen = 1;
		break;

	// set_idle:
	case HID_SET_IDLE:
		DBG("SET IDLE, val=%X, idx=%X\n", pSetup->wValue, pSetup->wIndex);
		_iIdleRate = ((pSetup->wValue >> 8) & 0xFF) * 4;
		break;

	default:
		DBG("Unhandled class %X\n", pSetup->bRequest);
		return FALSE;
	}
	return TRUE;
}


#define BAUD_RATE	115200


/*************************************************************************
	HIDHandleStdReq
	===============
		Standard request handler for HID devices.
		
	This function tries to service any HID specific requests.
		
**************************************************************************/
static BOOL HIDHandleStdReq(TSetupPacket *pSetup, int *piLen, U8 **ppbData)
{
	U8	bType, bIndex;

	if ((pSetup->bmRequestType == 0x81) &&			// standard IN request for interface
		(pSetup->bRequest == REQ_GET_DESCRIPTOR)) {	// get descriptor
		
		bType = GET_DESC_TYPE(pSetup->wValue);
		bIndex = GET_DESC_INDEX(pSetup->wValue);
		switch (bType) {

		case DESC_HID_REPORT:
			// report
			*ppbData = abReportDesc;
			*piLen = sizeof(abReportDesc);
			break;

		case DESC_HID_HID:
		case DESC_HID_PHYSICAL:
		default:
		    // search descriptor space
		    return USBGetDescriptor(pSetup->wValue, pSetup->wIndex, piLen, ppbData);
		}
		
		return TRUE;
	}
	return FALSE;
}

//CodeRed - rewritten to provide real mouse reports
/*
static void HandleFrame(U16 wFrame)
{
	static int iCount;

	_iFrame++;
	if ((_iFrame > 1000)) {
		// send report (dummy data)
		abReport[0] = (iCount >> 8) & 0xFF;
		abReport[1] = (iCount) & 0xFF;
		iCount++;
		USBHwEPWrite(INTR_IN_EP, abReport, REPORT_SIZE);
		_iFrame = 0;
	}
}
*/
static void HandleFrame(U16 wFrame)
{
	static int iCount;

	_iFrame++;
	if ((_iFrame > 100)) {
		iCount++;
		USBHwEPWrite(INTR_IN_EP, (void *)&MouseInputReport, REPORT_SIZE);
		_iFrame = 0;
	}
}

// CodeRed - initial mouse report
void HIDDMouseInputReport_Initialize(HIDDMouseInputReport *report)
{
    report->bmButtons = 0;
    report->bX = 0;
    report->bY = 0;
}


// CodeRed - function to read RDB1768 joystick
void vF_RDB1768_JoystickRead(int *pi_JoystickState)
{
	int i_up, i_dn, i_l, i_r, i_sel;
	int i_State;
	
	if (RDBversion == RDBv2)
	// RDB1768v2 board has joystick up on p0.10
		i_up = (LPC_GPIO0->FIOPIN>>10) & 1;
	else
		// RDB1768 (v1) board has joystick up on p0.4
		i_up = (LPC_GPIO0->FIOPIN>>4) & 1;


	i_dn = (LPC_GPIO0->FIOPIN>>5) & 1;
	i_sel = (LPC_GPIO0->FIOPIN>>6) & 1;
	i_l = (LPC_GPIO0->FIOPIN>>0) & 1;
	i_r = (LPC_GPIO0->FIOPIN>>1) & 1;
	
	i_State = (i_sel<< 4) | (i_up<<3) | (i_dn<<2) | (i_l<<1) | (i_r); 
	i_State = (~i_State) & 0xff;
	*pi_JoystickState = i_State;
}


/*************************************************************************
	main
	====
**************************************************************************/
int main(void)
{
	
// CodeRed
	HIDDMouseInputReport_Initialize (&MouseInputReport);
	int i_JoystickState;

	// Initialize the ST7637 LCD Controller/driver for use
	LCDdriver_initialisation();

	// Reset the "terminal" window to be displayed on the RDB1768's LCD
	LCD_ResetTerminal(COLOR_YELLOW);

	// Check which version of RDB1768 board code is running on.
	RDBversion = whichRDB();

	if (RDBversion == RDBv2)
		LCD_PrintString2Terminal ("RDB1768v2\n", LCD_TERMINAL_NoNL,COLOR_BLUE, COLOR_YELLOW);
	else
		LCD_PrintString2Terminal ("RDB1768 (v1)\n", LCD_TERMINAL_NoNL,COLOR_BLUE, COLOR_YELLOW);

	LCD_PrintString2Terminal ("USB mouse\n", LCD_TERMINAL_NoNL,COLOR_BLUE, COLOR_YELLOW);
	LCD_PrintString2Terminal ("- Initialising\n  USB stack\n", LCD_TERMINAL_NoNL,COLOR_BLUE, COLOR_YELLOW);

// CodeRed - deleted ref to ConsoleInit	
	// init DBG
//	ConsoleInit(60000000 / (16 * BAUD_RATE));

	DBG("Initialising USB stack\n");
	
	// initialise stack
	USBInit();
	
	// register device descriptors
	USBRegisterDescriptors(abDescriptors);

	// register HID standard request handler
	USBRegisterCustomReqHandler(HIDHandleStdReq);

	// register class request handler
	USBRegisterRequestHandler(REQTYPE_TYPE_CLASS, HandleClassRequest, abClassReqData);

	// register endpoint
	USBHwRegisterEPIntHandler(INTR_IN_EP, NULL);

	// register frame handler
	USBHwRegisterFrameHandler(HandleFrame);
	
	DBG("Starting USB communication\n");

	LCD_PrintString2Terminal ("- Starting USB\n  communication\n", LCD_TERMINAL_NoNL,COLOR_BLUE, COLOR_YELLOW);
	LCD_PrintString2Terminal ("Use joystick\nas PC's mouse\n", LCD_TERMINAL_NoNL,COLOR_BLUE, COLOR_YELLOW);

	// connect to bus
	USBHwConnect(TRUE);

	// call USB interrupt handler continuously
	
	// CodeRed - either read mouse, or provide "fake mouse readings"
	while (1)
	{
#ifdef NOJOYSTICK		  
		for (i=0; i<10000;  i++) {
		  USBHwISR();
		  if (i < 5000) {
			  MouseInputReport.bX = 10;	
		  }
		  else {
			  MouseInputReport.bX = 0;
		  }
#else
		  USBHwISR();
		  vF_RDB1768_JoystickRead(&i_JoystickState);
		  if(i_JoystickState & JOYSTICK_UP)
		  {
			  MouseInputReport.bY = -10;
			  MouseInputReport.bX = 0;
			  MouseInputReport.bmButtons = 0;
		  }
		  else if((i_JoystickState & JOYSTICK_DOWN))
		  {
			  MouseInputReport.bY = 10;
			  MouseInputReport.bX = 0;
			  MouseInputReport.bmButtons = 0;
		  }
		  else if((i_JoystickState & JOYSTICK_LEFT))
		  {
			  MouseInputReport.bX = -10;
			  MouseInputReport.bY = 0;
			  MouseInputReport.bmButtons = 0;
		  }
		  else if((i_JoystickState & JOYSTICK_RIGHT))
		  {
			  MouseInputReport.bX = 10;
			  MouseInputReport.bY = 0;
			  MouseInputReport.bmButtons = 0;
		  }
		  else if((i_JoystickState & JOYSTICK_CLICK))
		  {
			  MouseInputReport.bX = 0;
			  MouseInputReport.bY = 0;
			  MouseInputReport.bmButtons = 1 ; // left-click of mouse
		  }
		  else
		  {
			  MouseInputReport.bX = 0;
			  MouseInputReport.bY = 0;
			  MouseInputReport.bmButtons = 0;
			  
		  }
			  
#endif
		
	}
	
	return 0;
}

