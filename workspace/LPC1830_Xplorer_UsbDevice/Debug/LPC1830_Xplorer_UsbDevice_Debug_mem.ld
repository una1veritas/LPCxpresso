/*
 * GENERATED FILE - DO NOT EDIT
 * (C) Code Red Technologies Ltd, 2008-2012
 * Linker script memory definitions
 * Created from LinkMemoryTemplate
 * By LPCXpresso v4.2.3 [Build 292] [30/05/2012]  on Fri Jun 22 15:15:20 IST 2012)
*/

MEMORY
{
  /* Define each memory region */
  RamLoc96 (rwx) : ORIGIN = 0x10000000, LENGTH = 0x18000 /* 96k */
  RamLoc40 (rwx) : ORIGIN = 0x10080000, LENGTH = 0xa000 /* 40k */
  RamAHB32 (rwx) : ORIGIN = 0x20000000, LENGTH = 0x8000 /* 32k */
  RamAHB16 (rwx) : ORIGIN = 0x20008000, LENGTH = 0x4000 /* 16k */
  RamAHB_ETB16 (rwx) : ORIGIN = 0x2000c000, LENGTH = 0x4000 /* 16k */

}
  /* Define a symbol for the top of each memory region */
  __top_RamLoc96 = 0x10000000 + 0x18000;
  __top_RamLoc40 = 0x10080000 + 0xa000;
  __top_RamAHB32 = 0x20000000 + 0x8000;
  __top_RamAHB16 = 0x20008000 + 0x4000;
  __top_RamAHB_ETB16 = 0x2000c000 + 0x4000;

