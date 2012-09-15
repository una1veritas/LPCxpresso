//*****************************************************************************
//   +--+
//   | ++----+
//   +-++    |
//     |     |
//   +-+--+  |
//   | +--+--+
//   +----+    Copyright (c) 2010 Code Red Technologies Ltd.
//
// whichRDB.c  - provides a routine to determine at runtime which
//               version of the RDB1768 development board the code
//               is running on.
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
#include "whichRDB.h"

#define PHY_DEF_ADR    0x0100      /* Default PHY device address        */
#define DP83848C_ID         0x20005C90  /* PHY Identifier */
#define LAN8720_ID          0x0007C0F0  /* PHY Identifier                    */

#define MII_WR_TOUT         0x00050000  /* MII Write timeout count           */
#define MII_RD_TOUT         0x00050000  /* MII Read timeout count            */

#define MCMD_READ           0x00000001  /* MII Read  */

#define MAC1_PASS_ALL       0x00000002  /* Pass All Receive Frames           */

#define MAC1_RES_TX         0x00000100  /* Reset TX Logic                    */
#define MAC1_RES_MCS_TX     0x00000200  /* Reset MAC TX Control Sublayer     */
#define MAC1_RES_RX         0x00000400  /* Reset RX Logic                    */
#define MAC1_RES_MCS_RX     0x00000800  /* Reset MAC RX Control Sublayer     */
#define MAC1_SIM_RES        0x00004000  /* Simulation Reset                  */
#define MAC1_SOFT_RES       0x00008000  /* Soft Reset MAC                    */

#define MAC2_CRC_EN         0x00000010  /* Append CRC to every Frame         */
#define MAC2_PAD_EN         0x00000020  /* Pad all Short Frames              */

#define CR_REG_RES          0x00000008  /* Reset Host Registers              */
#define CR_TX_RES           0x00000010  /* Reset Transmit Datapath           */
#define CR_RX_RES           0x00000020  /* Reset Receive Datapath            */
#define CR_PASS_RUNT_FRM    0x00000040  /* Pass Runt Frames                  */

#define MIND_BUSY           0x00000001  /* MII is Busy */

#define CLRT_DEF            0x0000370F  /* Default value                     */

#define IPGR_DEF            0x00000012  /* Recommended value                 */

#define ETH_MAX_FLEN        1536        /* Max. Ethernet Frame Size          */

#define MCFG_CLK_DIV64		0x0000003c

#define MCFG_RES_MII        0x00008000  /* Reset MII Management Hardware     */

#define CR_RMII             0x00000200  /* Reduced MII Interface             */
#define CR_PASS_RX_FILT     0x00000080  /* Pass RX Filter                    */

#define SUPP_SPEED          0x00000100  /* Reduced MII Logic Current Speed   */
#define SUPP_RES_RMII       0x00000800  /* Reset Reduced MII Logic           */

#define PHY_REG_BMCR        0x00        /* Basic Mode Control Register       */
#define PHY_REG_IDR1        0x02        /* PHY Identifier 1                  */
#define PHY_REG_IDR2        0x03        /* PHY Identifier 2                  */

static void write_PHY (uint32_t PhyReg, uint32_t Value)
{
	uint32_t tout;

    LPC_EMAC->MADR = PHY_DEF_ADR | PhyReg;
    LPC_EMAC->MWTD = Value;

    /* Wait until operation completed */
    tout = 0;
    for (tout = 0; tout < MII_WR_TOUT; tout++) {
      if ((LPC_EMAC->MIND & MIND_BUSY) == 0) {
        break;
      }
    }
}

static uint16_t read_PHY (uint8_t PhyReg)
{
	uint32_t tout;

	LPC_EMAC->MADR = PHY_DEF_ADR | PhyReg;
	LPC_EMAC->MCMD = MCMD_READ;

	/* Wait until operation completed */
	tout = 0;
	for (tout = 0; tout < MII_RD_TOUT; tout++) {
		if ((LPC_EMAC->MIND & MIND_BUSY) == 0) {
			break;
		}
	}
	LPC_EMAC->MCMD = 0;
	return (LPC_EMAC->MRDD);
}

/* ************************************************************
 * whichRDB()
 *
 * Returns which version of the RDB1768 code is running on
 * 0 - Unrecognised
 * 1 - Original RDB1768 (v1) - as released 2009
 * 2 - RDB1768v2  - as released Q1 2010
 *
 * Detection of which board is being used is made by switching
 * on the ethernet subsytem and reading the id value of the
 * ethernet PHY.
 *
 * Note that care is needed if your software system actually
 * uses the ethernet subsystem !
 *************************************************************/
uint32_t whichRDB (void)
{
	uint32_t RDBversion = 0;

	uint32_t regv, id1,id2;

	volatile uint32_t tout;
	uint32_t phy_id;

	// Power Up the EMAC controller.
	LPC_SC->PCONP |= 0x40000000;

	// Enable P1 Ethernet Pins.
	LPC_PINCON->PINSEL2 = 0x50150105;
	LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~0x0000000F) | 0x00000005;

	// Reset all EMAC internal modules
	LPC_EMAC->MAC1 = MAC1_RES_TX | MAC1_RES_MCS_TX | MAC1_RES_RX | MAC1_RES_MCS_RX |
	                 MAC1_SIM_RES | MAC1_SOFT_RES;
	LPC_EMAC->Command = CR_REG_RES | CR_TX_RES | CR_RX_RES | CR_PASS_RUNT_FRM;

	// A short delay after reset
	for (tout = 100; tout; tout--);

	// Initialize MAC control registers.
	LPC_EMAC->MAC1 = MAC1_PASS_ALL;
	LPC_EMAC->MAC2 = MAC2_CRC_EN | MAC2_PAD_EN;
	LPC_EMAC->MAXF = ETH_MAX_FLEN;
	LPC_EMAC->CLRT = CLRT_DEF;
	LPC_EMAC->IPGR = IPGR_DEF;


	// Enable Reduced MII interface.
	LPC_EMAC->MCFG = MCFG_CLK_DIV64 | MCFG_RES_MII;
	for (tout = 100; tout; tout--);
	LPC_EMAC->MCFG = MCFG_CLK_DIV64;

	// Enable Reduced MII interface.
	LPC_EMAC->Command = CR_RMII | CR_PASS_RUNT_FRM | CR_PASS_RX_FILT;

	// Reset Reduced MII Logic.
	LPC_EMAC->SUPP = SUPP_RES_RMII | SUPP_SPEED;
	for (tout = 100; tout; tout--);
	LPC_EMAC->SUPP = SUPP_SPEED;

	// Put the PHY in reset mode
	write_PHY (PHY_REG_BMCR, 0x8000);
	for (tout = 1000; tout; tout--);

	// Wait for hardware reset to end. */
	for (tout = 0; tout < 0x100000; tout++)
	{
		regv = read_PHY (PHY_REG_BMCR);

	    if (!(regv & 0x8000))

		{
	      /* Reset complete */
	      break;
	    }
	}
	if (tout >= 0x100000)
	    // Reset failed
	    return 0;

	// Now read the PHY id
	id1 = read_PHY (PHY_REG_IDR1);
	id2 = read_PHY (PHY_REG_IDR2);
	phy_id = ((id1 << 16) | (id2 & 0xFFF0));

	if (phy_id == DP83848C_ID)
		// Original RDB1768 uses a DP83848C phy
		RDBversion = RDBv1;
	else if (phy_id == LAN8720_ID)
		// RDB1768v2 uses a LAN8720 phy
		RDBversion = RDBv2;

	return RDBversion;

}
