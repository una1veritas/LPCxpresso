/*
 * Memory linkscript for RDB1768cmis_usb_bootloader project.
 * This script has been modified from the original generated
 * by the Code Red tools to
 *
 * 1) Reserve the top 32 bytes of RAMLoc32 for use by the IAP
 *    programming routines, as described in the LPC17xx User
 *    Manual.
 *
 * 2) Reduce the size of the flash memory available, to ensure
 *    that it never overflows into the flash reserved for use
 *    as a memory drive (starting at 64KB / 0x10000).
 */

MEMORY
{
  /* Define each memory region */
  MFlash512 (rx) : ORIGIN = 0x0, LENGTH = 0x10000 /* 64k */
  RamLoc32 (rwx) : ORIGIN = 0x10000000, LENGTH = 0x7FE0 /* 32k - 32bytes */
  RamAHB32 (rwx) : ORIGIN = 0x2007c000, LENGTH = 0x8000 /* 32k */

}
  /* Define a symbol for the top of each memory region */
  __top_MFlash512 = 0x0 + 0x10000;
  __top_RamLoc32 = 0x10000000 + 0x7FE0;
  __top_RamAHB32 = 0x2007c000 + 0x8000;

