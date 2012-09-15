/******************************************************************
 *****                                                        *****
 *****  Name: easyweb.c                                       *****
 *****  Ver.: 1.0                                             *****
 *****  Date: 07/05/2001                                      *****
 *****  Auth: Andreas Dannenberg                              *****
 *****        HTWK Leipzig                                    *****
 *****        university of applied sciences                  *****
 *****        Germany                                         *****
 *****        adannenb@et.htwk-leipzig.de                     *****
 *****  Func: implements a dynamic HTTP-server by using       *****
 *****        the easyWEB-API                                 *****
 *****  Rem.: In IAR-C, use  linker option                    *****
 *****        "-e_medium_write=_formatted_write"              *****
 *****                                                        *****
 ******************************************************************/

// Modifications by Code Red Technologies for NXP LPC1768

// CodeRed - removed header for MSP430 microcontroller
//#include "msp430x14x.h"

#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#include <cr_section_macros.h>
#include <NXP/crp.h>

// Variable to store CRP value in. Will be placed automatically
// by the linker when "Enable Code Read Protect" selected.
// See crp.h header for more information
__CRP const unsigned int CRP_WORD = CRP_NO_CRP ;


// CodeRed - added #define extern on next line (else variables
// not defined). This has been done due to include the .h files 
// rather than the .c files as in the original version of easyweb.
#define extern 

#include "easyweb.h"

// CodeRed - removed header for original ethernet controller
//#include "cs8900.c"                              // ethernet packet driver

//CodeRed - added for LPC ethernet controller
#include "ethmac.h"

// CodeRed - include .h rather than .c file
// #include "tcpip.c"                               // easyWEB TCP/IP stack
#include "tcpip.h"                               // easyWEB TCP/IP stack

// CodeRed - added NXP LPC register definitions header
#include "LPC17xx.h"

// CodeRed - added reference to RDB1768 LCD routines
#include "lcd.h"
// Invoke the macro LCD_PRINT_IPADDRESS to display an IP address on the RDB1768's LCD screen
#define LCD_PRINT_IPADDRESS_1(a,b,c,d) \
	LCD_PrintString2Terminal (#a "." #b "." #c "." #d "\n", \
			                  LCD_TERMINAL_NoNL,COLOR_YELLOW, COLOR_BLUE)
#define LCD_PRINT_IPADDRESS(a,b,c,d) LCD_PRINT_IPADDRESS_1(a,b,c,d)


// CodeRed - include renamed .h rather than .c file
// #include "webside.c"                             // webside for our HTTP server (HTML)
#include "webside.h"                             // webside for our HTTP server (HTML)



// CodeRed - added for use in dynamic side of web page
unsigned int aaPagecounter=0;
unsigned int adcValue = 0;

int main (void)
{
// CodeRed - removed init functions as not required for LPC1776
//  InitOsc();
//  InitPorts();
	

	// Code Red : RDB1768 LCD code
	// Initialize the ST7637 LCD Controller/driver for use
	LCDdriver_initialisation();

	// Reset the "terminal" window to be displayed on the RDB1768's LCD
	LCD_ResetTerminal(COLOR_BLUE);

	LCD_PrintString2Terminal ("RDB1768 Easyweb\n", LCD_TERMINAL_NoNL,COLOR_YELLOW, COLOR_BLUE);
	LCD_PrintString2Terminal ("TCP/IP Stack\n", LCD_TERMINAL_NoNL,COLOR_YELLOW,COLOR_BLUE);
	LCD_PrintString2Terminal ("- Initializing\n", LCD_TERMINAL_NoNL,COLOR_YELLOW, COLOR_BLUE );

	LCD_PrintString2Terminal ("- IP addresss = \n", LCD_TERMINAL_NoNL,COLOR_YELLOW, COLOR_BLUE);

	// This macro will expand to call LCD_PrintString2Terminal() to print the IP address to the LCD screen
	LCD_PRINT_IPADDRESS(MYIP_1, MYIP_2, MYIP_3, MYIP_4);
	
	TCPLowLevelInit();

/*
  *(unsigned char *)RemoteIP = 24;               // uncomment those lines to get the
  *((unsigned char *)RemoteIP + 1) = 8;          // quote of the day from a real
  *((unsigned char *)RemoteIP + 2) = 69;         // internet server! (gateway must be
  *((unsigned char *)RemoteIP + 3) = 7;          // set to your LAN-router)

  TCPLocalPort = 2025;
  TCPRemotePort = TCP_PORT_QOTD;

  TCPActiveOpen();

  while (SocketStatus & SOCK_ACTIVE)             // read the quote from memory
  {                                              // by using the hardware-debugger
    DoNetworkStuff();
  }
*/

  HTTPStatus = 0;                                // clear HTTP-server's flag register

  TCPLocalPort = TCP_PORT_HTTP;                  // set port we want to listen to
 
// CodeRed - added info message
  LCD_PrintString2Terminal ("Up and running!\n", LCD_TERMINAL_NoNL,COLOR_YELLOW, COLOR_BLUE);

  
  while (1)                                      // repeat forever
  {
    if (!(SocketStatus & SOCK_ACTIVE)) TCPPassiveOpen();   // listen for incoming TCP-connection
    DoNetworkStuff();                                      // handle network and easyWEB-stack
                                                           // events
    HTTPServer();
  }
}

// This function implements a very simple dynamic HTTP-server.
// It waits until connected, then sends a HTTP-header and the
// HTML-code stored in memory. Before sending, it replaces
// some special strings with dynamic values.
// NOTE: For strings crossing page boundaries, replacing will
// not work. In this case, simply add some extra lines
// (e.g. CR and LFs) to the HTML-code.

void HTTPServer(void)
{
  if (SocketStatus & SOCK_CONNECTED)             // check if somebody has connected to our TCP
  {
    if (SocketStatus & SOCK_DATA_AVAILABLE)      // check if remote TCP sent data
      TCPReleaseRxBuffer();                      // and throw it away

    if (SocketStatus & SOCK_TX_BUF_RELEASED)     // check if buffer is free for TX
    {
      if (!(HTTPStatus & HTTP_SEND_PAGE))        // init byte-counter and pointer to webside
      {                                          // if called the 1st time
        HTTPBytesToSend = sizeof(WebSide) - 1;   // get HTML length, ignore trailing zero
        PWebSide = (unsigned char *)WebSide;     // pointer to HTML-code
      }

      if (HTTPBytesToSend > MAX_TCP_TX_DATA_SIZE)     // transmit a segment of MAX_SIZE
      {
        if (!(HTTPStatus & HTTP_SEND_PAGE))           // 1st time, include HTTP-header
        {
          memcpy(TCP_TX_BUF, GetResponse, sizeof(GetResponse) - 1);
          memcpy(TCP_TX_BUF + sizeof(GetResponse) - 1, PWebSide, MAX_TCP_TX_DATA_SIZE - sizeof(GetResponse) + 1);
          HTTPBytesToSend -= MAX_TCP_TX_DATA_SIZE - sizeof(GetResponse) + 1;
          PWebSide += MAX_TCP_TX_DATA_SIZE - sizeof(GetResponse) + 1;
        }
        else
        {
          memcpy(TCP_TX_BUF, PWebSide, MAX_TCP_TX_DATA_SIZE);
          HTTPBytesToSend -= MAX_TCP_TX_DATA_SIZE;
          PWebSide += MAX_TCP_TX_DATA_SIZE;
        }
          
        TCPTxDataCount = MAX_TCP_TX_DATA_SIZE;   // bytes to xfer
        InsertDynamicValues();                   // exchange some strings...
        TCPTransmitTxBuffer();                   // xfer buffer
      }
      else if (HTTPBytesToSend)                  // transmit leftover bytes
      {
        memcpy(TCP_TX_BUF, PWebSide, HTTPBytesToSend);
        TCPTxDataCount = HTTPBytesToSend;        // bytes to xfer
        InsertDynamicValues();                   // exchange some strings...
        TCPTransmitTxBuffer();                   // send last segment
        TCPClose();                              // and close connection
        HTTPBytesToSend = 0;                     // all data sent
      }

      HTTPStatus |= HTTP_SEND_PAGE;              // ok, 1st loop executed
    }
  }
  else
    HTTPStatus &= ~HTTP_SEND_PAGE;               // reset help-flag if not connected
}




// Code Red - GetAD7Val function replaced
// Rather than using the AD convertor, in this version we simply increment
// a counter the function is called, wrapping at 1024. 
volatile unsigned int aaScrollbar = 400;

unsigned int GetAD7Val(void)
{
  aaScrollbar = (aaScrollbar +16) % 1024;
  adcValue = (aaScrollbar / 10) * 1000/1024;
  return aaScrollbar;
}

// Code Red - Original MSP430 version of GetAD7Val() removed
/*
// samples and returns the AD-converter value of channel 7
// (associated with Port P6.7)

unsigned int GetAD7Val(void)
{
  ADC12CTL0 = ADC12ON | SHT0_15 | REF2_5V | REFON;   // ADC on, int. ref. on (2,5 V),
                                                     // single channel single conversion
  ADC12CTL1 = ADC12SSEL_2 | ADC12DIV_7 | CSTARTADD_0 | SHP;// MCLK / 8 = 1 MHz

  ADC12MCTL0 = SREF_1 | INCH_7;                  // int. ref., channel 7
  
  ADC12CTL0 |= ENC;                              // enable conversion
  ADC12CTL0 |= ADC12SC;                          // sample & convert
  
  while (ADC12CTL0 & ADC12SC);                   // wait until conversion is complete
  
  ADC12CTL0 &= ~ENC;                             // disable conversion

  return ADC12MEM0 / 41;                         // scale 12 bit value to 0..100%
}

// End of Original MSP430 version of GetAD7Val()
*/


// Code Red - Original GetTempVal() removed
// Function no longer used
/*
// samples and returns AD-converter value of channel 10
// (MSP430's internal temperature reference diode)
// NOTE: to get a more exact value, 8-times oversampling is used

unsigned int GetTempVal(void)
{
  unsigned long ReturnValue;

  ADC12CTL0 = ADC12ON | SHT0_15 | MSH | REFON;   // ADC on, int. ref. on (1,5 V),
                                                 // multiple sample & conversion
  ADC12CTL1 = ADC12SSEL_2 | ADC12DIV_7 | CSTARTADD_0 | CONSEQ_1 | SHP;   // MCLK / 8 = 1 MHz

  ADC12MCTL0 = SREF_1 | INCH_10;                 // int. ref., channel 10
  ADC12MCTL1 = SREF_1 | INCH_10;                 // int. ref., channel 10
  ADC12MCTL2 = SREF_1 | INCH_10;                 // int. ref., channel 10
  ADC12MCTL3 = SREF_1 | INCH_10;                 // int. ref., channel 10
  ADC12MCTL4 = SREF_1 | INCH_10;                 // int. ref., channel 10
  ADC12MCTL5 = SREF_1 | INCH_10;                 // int. ref., channel 10
  ADC12MCTL6 = SREF_1 | INCH_10;                 // int. ref., channel 10
  ADC12MCTL7 = EOS | SREF_1 | INCH_10;           // int. ref., channel 10, last seg.
  
  ADC12CTL0 |= ENC;                              // enable conversion
  ADC12CTL0 |= ADC12SC;                          // sample & convert
  
  while (ADC12CTL0 & ADC12SC);                   // wait until conversion is complete
  
  ADC12CTL0 &= ~ENC;                             // disable conversion

  ReturnValue = ADC12MEM0;                       // sum up values...
  ReturnValue += ADC12MEM1;
  ReturnValue += ADC12MEM2;
  ReturnValue += ADC12MEM3;
  ReturnValue += ADC12MEM4;
  ReturnValue += ADC12MEM5;
  ReturnValue += ADC12MEM6;
  ReturnValue += ADC12MEM7;

  ReturnValue >>= 3;                             // ... and divide by 8

  if (ReturnValue < 2886) ReturnValue = 2886;    // lower bound (0% = 20�C)
  ReturnValue = (ReturnValue - 2886) / 2.43;     // convert AD-value to a temperature from
                                                 // 20�C...45�C represented by a value
                                                 // of 0...100%
  if (ReturnValue > 100) ReturnValue = 100;      // upper bound (100% = 45�C)

  return ReturnValue;
}
// End of Original MSP430 version of GetTempVal()
*/


// searches the TX-buffer for special strings and replaces them
// with dynamic values (AD-converter results)

// Code Red - new version of InsertDynamicValues()
void InsertDynamicValues(void)
{
  unsigned char *Key;
           char NewKey[6];
  unsigned int i;
  
  if (TCPTxDataCount < 4) return;                     // there can't be any special string
  
  Key = TCP_TX_BUF;
  
  for (i = 0; i < (TCPTxDataCount - 3); i++)
  {
    if (*Key == 'A')
     if (*(Key + 1) == 'D')
       if (*(Key + 3) == '%')
         switch (*(Key + 2))
         {
           case '8' :                                 // "AD8%"?
           {
             sprintf(NewKey, "%04d", GetAD7Val());     // insert pseudo-ADconverter value
             memcpy(Key, NewKey, 4);                  
             break;
           }
           case '7' :                                 // "AD7%"?
           {
             sprintf(NewKey, "%3u", adcValue);     // copy saved value from previous read
             memcpy(Key, NewKey, 3);                 
             break;
           }
		   case '1' :                                 // "AD1%"?
           {
 			 sprintf(NewKey, "%4u", ++aaPagecounter);    // increment and insert page counter
             memcpy(Key, NewKey, 4);  
//			 *(Key + 3) = ' ';  
             break;
           }
         }
    Key++;
  }
}


// Code Red - commented out original InsertDynamicValues()
/*
void InsertDynamicValues(void)
{
  unsigned char *Key;
  unsigned char NewKey[5];
  unsigned int i;
  
  if (TCPTxDataCount < 4) return;                     // there can't be any special string
  
  Key = TCP_TX_BUF;
  
  for (i = 0; i < (TCPTxDataCount - 3); i++)
  {
    if (*Key == 'A')
     if (*(Key + 1) == 'D')
       if (*(Key + 3) == '%')
         switch (*(Key + 2))
         {
           case '7' :                                 // "AD7%"?
           {
             sprintf(NewKey, "%3u", GetAD7Val());     // insert AD converter value
             memcpy(Key, NewKey, 3);                  // channel 7 (P6.7)
             break;
           }
           case 'A' :                                 // "ADA%"?
           {
             sprintf(NewKey, "%3u", GetTempVal());    // insert AD converter value
             memcpy(Key, NewKey, 3);                  // channel 10 (temp.-diode)
             break;
           }
         }
    Key++;
  }
}

// Code Red - End of original InsertDynamicValues ()
*/

// Code Red - Deleted InitOsc() and InitPorts() as not required
// by LPC 1776

/*
// enables the 8MHz crystal on XT1 and use
// it as MCLK

void InitOsc(void)
{
  WDTCTL = WDTPW | WDTHOLD;                      // stop watchdog timer

  BCSCTL1 |= XTS;                                // XT1 as high-frequency
  _BIC_SR(OSCOFF);                               // turn on XT1 oscillator
                          
  do                                             // wait in loop until crystal is stable 
    IFG1 &= ~OFIFG;
  while (IFG1 & OFIFG);

  BCSCTL1 |= DIVA0;                              // ACLK = XT1 / 2
  BCSCTL1 &= ~DIVA1;
  
  IE1 &= ~WDTIE;                                 // disable WDT int.
  IFG1 &= ~WDTIFG;                               // clear WDT int. flag
  
  WDTCTL = WDTPW | WDTTMSEL | WDTCNTCL | WDTSSEL | WDTIS1; // use WDT as timer, flag each
                                                           // 512 pulses from ACLK
                                                           
  while (!(IFG1 & WDTIFG));                      // count 1024 pulses from XT1 (until XT1's
                                                 // amplitude is OK)

  IFG1 &= ~OFIFG;                                // clear osc. fault int. flag
  BCSCTL2 = SELM0 | SELM1;                       // set XT1 as MCLK
}  

void InitPorts(void)
{
  P1SEL = 0;                                     // switch all unused ports to output
  P1OUT = 0;                                     // (rem.: ports 3 & 5 are set in "cs8900.c")
  P1DIR = 0xFF;

  P2SEL = 0;
  P2OUT = 0;
  P2DIR = 0xFF;

  P4SEL = 0;
  P4OUT = 0;
  P4DIR = 0xFF;

  P6SEL = 0x80;                                  // use P6.7 for the ADC module
  P6OUT = 0;
  P6DIR = 0x7F;                                  // all output except P6.7
}

*/
