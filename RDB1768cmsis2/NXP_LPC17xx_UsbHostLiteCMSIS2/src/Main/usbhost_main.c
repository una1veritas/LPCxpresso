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
* File           : usbhost_main.c
* Programmer(s)  : Ravikanth.P
* Version        :
*
**************************************************************************************************************
*/

/*
**************************************************************************************************************
*                                       INCLUDE HEADER FILES
**************************************************************************************************************
*/

#include  "usbhost_main.h"

#include <cr_section_macros.h>
#include <NXP/crp.h>

// Variable to store CRP value in. Will be placed automatically
// by the linker when "Enable Code Read Protect" selected.
// See crp.h header for more information
__CRP const unsigned int CRP_WORD = CRP_NO_CRP ;


/*
**************************************************************************************************************
*                                          MAIN FUNCTION
*
* Description: This function is the main function where the execution begins
*
* Arguments  : None
*
* Returns    : 
*
**************************************************************************************************************
*/

int main()
{
    USB_INT32S  rc;
	USB_INT32U  numBlks, blkSize;
	USB_INT08U  inquiryResult[INQUIRY_LENGTH];

// Code Red - if CMSIS 1.3 setup is being used, then SystemInit() routine
// will be called by startup code rather than in application's main()
#ifndef __USE_CMSIS
	SystemInit();                               /* initialize clocks */
#endif

 

    UART_Init(115200);         /* Initialize the serial port to view the log messages                       */
    Host_Init();               /* Initialize the lpc17xx host controller                                    */
    rc = Host_EnumDev();       /* Enumerate the device connected                                            */
    if (rc == OK) {
		/* Initialize the mass storage and scsi interfaces */
        rc = MS_Init( &blkSize, &numBlks, inquiryResult );
        if (rc == OK) {
            rc = FAT_Init();   /* Initialize the FAT16 file system                                          */
            if (rc == OK) {
                Main_Copy();   /* Call the application                                                      */
            } else {
				while ( 1 );
                return (0);
            }
        } else {
			while ( 1 );
            return (0);
        }
    } else {							
		while ( 1 );
        return (0);
    }
    while(1);
}

/*
**************************************************************************************************************
*                                      READ DATA FROM DISK
*
* Description: This function is used by the user to read data from the disk
*
* Arguments  : None
*
* Returns    : None
*
**************************************************************************************************************
*/

void  Main_Read (void)
{
    USB_INT32S  fdr;
    USB_INT32U  bytes_read;
    

    fdr = FILE_Open(FILENAME_R, RDONLY);
    if (fdr > 0) {
        PRINT_Log("Reading from %s...\n", FILENAME_R);
        do {
            bytes_read = FILE_Read(fdr, UserBuffer, MAX_BUFFER_SIZE);
        } while (bytes_read);

        FILE_Close(fdr);
        PRINT_Log("Read Complete\n");
    } else {
        PRINT_Log("Could not open file %s\n", FILENAME_R);
        return;
    }
}

/*
**************************************************************************************************************
*                                      WRITE DATA TO DISK
*
* Description: This function is used by the user to write data to disk
*
* Arguments  : None
*
* Returns    : None
*
**************************************************************************************************************
*/

void  Main_Write (void)
{
    USB_INT32S  fdw;
    USB_INT32S  fdr;
    USB_INT32U  tot_bytes_written;
    USB_INT32U  bytes_written;


    fdr = FILE_Open(FILENAME_R, RDONLY);
    if (fdr > 0) {
        FILE_Read(fdr, UserBuffer, MAX_BUFFER_SIZE);
        fdw = FILE_Open(FILENAME_W, RDWR);
        if (fdw > 0) {
            tot_bytes_written = 0;
            PRINT_Log("Writing to %s...\n", FILENAME_W);
            do {
                bytes_written = FILE_Write(fdw, UserBuffer, MAX_BUFFER_SIZE);
                tot_bytes_written += bytes_written;
            } while (tot_bytes_written < WRITE_SIZE);
            FILE_Close(fdw);
            PRINT_Log("Write completed\n");
        } else {
            PRINT_Log("Could not open file %s\n", FILENAME_W);
            return;
        }
        FILE_Close(fdr);
    } else {
        PRINT_Log("Could not open file %s\n", FILENAME_R);
        return;
    }
}

/*
**************************************************************************************************************
*                                    COPYING A FILE
*
* Description: This function is used by the user to copy a file
*
* Arguments  : None
*
* Returns    : None
*
**************************************************************************************************************
*/

void  Main_Copy (void)
{
    USB_INT32S  fdr;
    USB_INT32S  fdw;
    USB_INT32U  bytes_read;


    fdr = FILE_Open(FILENAME_R, RDONLY);
    if (fdr > 0) {
        fdw = FILE_Open(FILENAME_W, RDWR);
        if (fdw > 0) {
            PRINT_Log("Copying from %s to %s...\n", FILENAME_R, FILENAME_W);
            do {
                bytes_read = FILE_Read(fdr, UserBuffer, MAX_BUFFER_SIZE);
                FILE_Write(fdw, UserBuffer, bytes_read);
            } while (bytes_read);
            FILE_Close(fdw);
        } else {
            PRINT_Log("Could not open file %s\n", FILENAME_W);
            return;
        }
        FILE_Close(fdr);
        PRINT_Log("Copy completed\n");
    } else {
        PRINT_Log("Could not open file %s\n", FILENAME_R);
        return;
    }
}
