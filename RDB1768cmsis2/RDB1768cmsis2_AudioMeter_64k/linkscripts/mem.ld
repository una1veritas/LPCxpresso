/*
 * GENERATED FILE - DO NOT EDIT
 * (C) Code Red Technologies Ltd, 2008-9
 * Generated linker script include file for 
 * (created from LinkMemoryTemplate (v3.0.11 (200912011033)) on Thu Dec 03 13:57:38 GMT 2009)
*/

MEMORY
{
  /* Define each memory region */
  MFlash512 (rx) : ORIGIN = 0x10000, LENGTH = 0x70000 /* 512k -64k*/
  RamLoc32 (rwx) : ORIGIN = 0x10000000, LENGTH = 0x8000 /* 32k */
  RamAHB32 (rwx) : ORIGIN = 0x2007c000, LENGTH = 0x8000 /* 32k */

}
  /* Define a symbol for the top of each memory region */
  __top_MFlash512 = 0x10000 + 0x70000;
  __top_RamLoc32 = 0x10000000 + 0x8000;
  __top_RamAHB32 = 0x2007c000 + 0x8000;

