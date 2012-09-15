//*****************************************************************************
//   +--+
//   | ++----+
//   +-++    |
//     |     |
//   +-+--+  |
//   | +--+--+
//   +----+    Copyright (c) 2010-11 Code Red Technologies Ltd.
//
// efsl_demo.c - demonstrates how the Embedded Filesystems Library (EFSL) can
//               be used on the RDB1768 board
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
//
//*****************************************************************************

#include "LPC17xx.h"

#include <cr_section_macros.h>
#include <NXP/crp.h>

// Variable to store CRP value in. Will be placed automatically
// by the linker when "Enable Code Read Protect" selected.
// See crp.h header for more information
__CRP const unsigned int CRP_WORD = CRP_NO_CRP ;

#include <stdio.h>
#include "efs.h"
#include "ls.h"
#include "mkfs.h"

EmbeddedFileSystem efs;
EmbeddedFile filer, filew;
DirList list;
unsigned short e;
unsigned char buf[513];

#include <stdio.h>
#include "efs.h"
#include "ls.h"
#include "mkfs.h"

EmbeddedFileSystem efs;
EmbeddedFile filer, filew;
DirList list;
unsigned short e;
unsigned char buf[513];

#define MESSAGE printf

int main(void)
{
	int8_t res;

	MESSAGE("\nRDB1768 EFSL / microSD card Demonstration\n");
	MESSAGE("=========================================\n");

	MESSAGE("CARD init...");
	if ( ( res = efs_init( &efs, 0 ) ) != 0 ) {
		MESSAGE("failed with %i\n",res);
	}
	else {
		MESSAGE("ok\n");
		MESSAGE("Directory of 'root':\n");
		ls_openDir( &list, &(efs.myFs) , "/");
		while ( ls_getNext( &list ) == 0 ) {
			list.currentEntry.FileName[LIST_MAXLENFILENAME-1] = '\0';
			MESSAGE( "%s ( %li bytes )\n" ,
				list.currentEntry.FileName,
				list.currentEntry.FileSize ) ;
		}


		fs_umount( &efs.myFs ) ;
	}

	MESSAGE("** Finished directory listing - entering infinite loop **\n");
	while (1);

	return 0; /* never reached */
}
