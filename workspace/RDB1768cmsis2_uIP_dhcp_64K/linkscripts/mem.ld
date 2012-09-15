/*
 * Modified linker script file, suitable for creating an image
 * that will run from 64K into the LPC1768's flash (0x10000).
 * This means that the maximum size of the image is 448KB 
 *(512KB - 64KB)
 */
 
MEMORY
{
  /* Define each memory region */
  MFlash512 (rx) : ORIGIN = 0x10000, LENGTH = 0x70000 /* 512k -64K*/
  RamLoc32 (rwx) : ORIGIN = 0x10000000, LENGTH = 0x8000 /* 32k */
  RamAHB32 (rwx) : ORIGIN = 0x2007c000, LENGTH = 0x8000 /* 32k */

}
  /* Define a symbol for the top of each memory region */
  __top_MFlash512 = 0x10000 + 0x70000;
  __top_RamLoc32 = 0x10000000 + 0x8000;
  __top_RamAHB32 = 0x2007c000 + 0x8000;

