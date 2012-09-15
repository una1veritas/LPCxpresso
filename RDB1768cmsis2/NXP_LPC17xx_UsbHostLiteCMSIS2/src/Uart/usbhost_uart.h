/*
**************************************************************************************************************
*                                                 NXP USB Host Stack
*
*                                     (c) Copyright 2008, NXP SemiConductors
*                                     (c) Copyright 2008, OnChip  Technologies LLC
*                                                 All Rights Reserved
*
*                                                  www.nxp.com
*                                               www.onchiptech.com
*
* File           : usbhost_uart.h
* Programmer(s)  : Prasad.K.R.S.V
* Version        :
*
**************************************************************************************************************
*/

#ifndef USBHOST_UART_H
#define USBHOST_UART_H

/*
**************************************************************************************************************
*                                           INCLUDE HEADER FILES
**************************************************************************************************************
*/

#include <stdarg.h>
#include <stdio.h>
#include "usbhost_inc.h"

/*
**************************************************************************************************************
*                                             UART DEFINITIONS
**************************************************************************************************************
*/	   
//#define Fcclk	48000000
//#define Fpclk	(Fcclk / 2)

/*
**************************************************************************************************************
*                                             FUNCTION PROTOTYPES
**************************************************************************************************************
*/

void  UART_Init  (      USB_INT32U   baudrate);
void  UART_PrintChar (      USB_INT08U   ch);
void  UART_PrintStr  (const USB_INT08U  *str);
void  UART_Printf(const USB_INT08U  *format, ...);

#endif
