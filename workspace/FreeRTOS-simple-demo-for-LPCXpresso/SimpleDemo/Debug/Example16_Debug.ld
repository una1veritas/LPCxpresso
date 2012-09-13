/*
 * GENERATED FILE - DO NOT EDIT
 * (C) Code Red Technologies Ltd, 2008-9    
 * Generated C linker script file for LPC1768 
 * (created from nxp_lpc13_c.ld (v3.4.0 (201006231119)) on Fri Oct 15 16:43:00 BST 2010)
*/

INCLUDE "Example16_Debug_lib.ld"
INCLUDE "Example16_Debug_mem.ld"

ENTRY(ResetISR)

SECTIONS
{
	.text :
	{
		KEEP(*(.isr_vector))
		*(.text*)
		*(.rodata*)

	} > MFlash512


	/* for exception handling/unwind - some Newlib functions (in common with C++ and STDC++) use this. */
	
	.ARM.extab : 
	{
		*(.ARM.extab* .gnu.linkonce.armextab.*)
	} > MFlash512

	__exidx_start = .;
	.ARM.exidx :
	{
		*(.ARM.exidx* .gnu.linkonce.armexidx.*)
	} > MFlash512
	__exidx_end = .;

	_etext = .;
		
	.data :
	{
		_data = .;
		*(vtable)
		*(.data*)
		_edata = .;
	} > RamLoc32 AT>MFlash512

	/* zero initialized data */
	.bss :
	{
		_bss = .;
		*(.bss*)
		*(COMMON)
		_ebss = .;
	} > RamLoc32
	
	/* Where we put the heap with cr_clib */
	.cr_heap :
	{
		end = .;
		_pvHeapStart = .;
	} > RamLoc32

/*
	Note: (ref: M0000066)
	Moving the stack down by 16 is to work around a GDB bug.
	This space can be reclaimed for Production Builds.
*/	
	_vRamTop = __top_RamLoc32 ;
	_vStackTop = _vRamTop - 16;
}
