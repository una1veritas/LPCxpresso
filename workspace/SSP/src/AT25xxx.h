/****************************************************************************
 *   $Id:: ssp.h 4102 2010-08-02 20:53:05Z usb00423                         $
 *   Project: NXP LPC11xx SSP example
 *
 *   Description:
 *     This file contains SSP code header definition.
 *
 ****************************************************************************
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 * NXP Semiconductors assumes no responsibility or liability for the
 * use of the software, conveys no license or title under any patent,
 * copyright, or mask work right to the product. NXP Semiconductors
 * reserves the right to make changes in the software without
 * notification. NXP Semiconductors also make no representation or
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.
****************************************************************************/
#ifndef __AT25xxx_H__
#define __AT25xxx_H__

/* ATMEL SEEPROM command set */
#define WREN            0x06		/* MSB A8 is set to 0, simplifying test */
#define WRDI            0x04
#define RDSR            0x05
#define WRSR            0x01
#define READ            0x03
#define WRITE           0x02

/* ATMEL 25DF041 extra commands */
#define BLOCK_ERASE		0x20
#define CHIP_ERASE		0x60
#define PROTECT_SEC		0x36
#define UNPROTECT_SEC	0x39

/* RDSR status bit definition */
#define RDSR_RDY        (0x01<<0)
#define RDSR_WEN        (0x01<<1)
#define RDSR_EPE        (0x01<<5)


#endif  /* __AT25xxx_H__ */
/*****************************************************************************
**                            End Of File
******************************************************************************/

