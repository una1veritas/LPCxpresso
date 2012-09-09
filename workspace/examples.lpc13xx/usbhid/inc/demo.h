/*----------------------------------------------------------------------------
 *      Name:    DEMO.H
 *      Purpose: USB HID Demo Definitions
 *      Version: V1.20
 *----------------------------------------------------------------------------
 *      This software is supplied "AS IS" without any warranties, express,
 *      implied or statutory, including but not limited to the implied
 *      warranties of fitness for purpose, satisfactory quality and
 *      noninfringement. Keil extends you a royalty-free right to reproduce
 *      and distribute executable files created using this software for use
 *      on NXP Semiconductors LPC microcontroller devices only. Nothing else 
 *      gives you the right to use this software.
 *
 * Copyright (c) 2009 Keil - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

/* HID Demo Variables */
extern uint8_t InReport;
extern uint8_t OutReport;

/* HID Demo Functions */
extern void GetInReport  (void);
extern void SetOutReport (void);
