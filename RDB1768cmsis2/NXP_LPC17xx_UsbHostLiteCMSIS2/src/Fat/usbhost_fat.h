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
* File           : usbhost_fat.h
* Programmer(s)  : Ravikanth.P
* Version        :
*
**************************************************************************************************************
*/

#ifndef  USBHOST_FAT_H
#define  USBHOST_FAT_H

/*
**************************************************************************************************************
*                                       INCLUDE HEADER FILES
**************************************************************************************************************
*/

#include  "usbhost_inc.h"

/*
**************************************************************************************************************
*                                      FAT DEFINITIONS
**************************************************************************************************************
*/

#define    FAT_16                   1

#define    LAST_ENTRY               1
#define    FREE_ENTRY               2
#define    LFN_ENTRY                3
#define    SFN_ENTRY                4

#define    RDONLY                   1
#define    RDWR                     2

/*
**************************************************************************************************************
*                                       TYPE DEFINITIONS
**************************************************************************************************************
*/

typedef struct boot_sec {
    USB_INT32U    BootSecOffset;             /* Offset of the boot sector from sector 0                     */
    USB_INT16U    BytsPerSec;                /* Bytes per sector                                            */
    USB_INT08U    SecPerClus;                /* Sectors per cluster                                         */
    USB_INT32U    BytsPerClus;               /* Bytes per cluster                                           */
    USB_INT16U    RsvdSecCnt;                /* Reserved sector count                                       */
    USB_INT08U    NumFATs;                   /* Number of FAT copies                                        */
    USB_INT16U    RootEntCnt;                /* Root entry count                                            */
    USB_INT16U    TotSec16;                  /* Total sectors in the disk. !=0 if TotSec32 = 0              */
    USB_INT32U    TotSec32;                  /* Total sectors in the disk. !=0 if TotSec16 = 0              */
    USB_INT16U    FATSz16;                   /* Sectors occupied by single FAT table                        */
    USB_INT08U    FATType;                   /* File system type                                            */
    USB_INT32U    RootDirSec;                /* Sectors occupied by root directory                          */
    USB_INT32U    RootDirStartSec;           /* Starting sector of the root directory                       */
    USB_INT32U    FirstDataSec;              /* Starting sector of the first data cluster                   */
} BOOT_SEC;

typedef  struct  file_entry {
    USB_INT32U  FileSize;                    /* Total size of the file                                      */
    USB_INT16U  CurrClus;                    /* Current cluster of the cluster offset                       */
    USB_INT32U  CurrClusOffset;              /* Current cluster offset                                      */
    USB_INT32U  EntrySec;                    /* Sector where the file entry is located                      */
    USB_INT32U  EntrySecOffset;              /* Offset in the entry sector from where the file is located   */
	USB_INT08U  FileStatus;                  /* File's open status                                          */
} FILE_ENTRY;

/*
**************************************************************************************************************
*                                       FUNCTION PROTOTYPES
**************************************************************************************************************
*/

USB_INT32S  FAT_Init        (void);

USB_INT08U  FAT_GetFATType  (void);
void        PrintBootSec    (void);

USB_INT32S  FILE_Open       (          USB_INT08U  *file_name,
                                       USB_INT08U   flags);

USB_INT32S  FAT_FindEntry   (          USB_INT08U  *ent_name_given,
                                       FILE_ENTRY  *entry);

void        FAT_GetSFN      (volatile  USB_INT08U  *entry,
                                       USB_INT08U  *name);

void        FAT_GetSfnName  (volatile  USB_INT08U  *entry,
                                       USB_INT08U  *name);

void        FAT_GetSfnExt   (volatile  USB_INT08U  *entry,
                                       USB_INT08U  *ext_ptr);

USB_INT32S  FAT_StrCaseCmp  (          USB_INT08U  *str1,
                                       USB_INT08U  *str2);

USB_INT32U  FAT_ChkEntType  (volatile  USB_INT08U  *ent);

USB_INT32U  FAT_ClusRead    (          USB_INT16U   curr_clus,
                                       USB_INT32U   clus_offset,
                             volatile  USB_INT08U  *buffer,
                                       USB_INT32U   num_bytes);

USB_INT32U  FILE_Read       (          USB_INT32S   fd,
                             volatile  USB_INT08U  *buffer,
                                       USB_INT32U   num_bytes);
USB_INT16U  FAT_GetNextClus (          USB_INT16U   clus_no);

USB_INT32U  FAT_ClusWrite   (          USB_INT16U   curr_clus,
                                       USB_INT32U   clus_offset,
                             volatile  USB_INT08U  *buffer,
                                       USB_INT32U   num_bytes);
USB_INT32U  FILE_Write      (          USB_INT32S   fd,
                             volatile  USB_INT08U  *buffer,
                                       USB_INT32U   num_bytes);

void        FAT_UpdateEntry (          FILE_ENTRY  *entry);

void        FAT_UpdateFAT   (          USB_INT16U   curr_clus,
                                       USB_INT16U   value);

USB_INT16U  FAT_GetFreeClus (void);

USB_INT32S  FAT_GetFreeEntry(          FILE_ENTRY  *entry);

void        FAT_PutSFN      (          USB_INT08U  *ent_name_given,
                                       FILE_ENTRY  *entry);

USB_INT32S  FAT_CreateEntry (          USB_INT08U  *ent_name_given,
                                       FILE_ENTRY  *entry);

void        FILE_Close      (          USB_INT32S   fd);

USB_INT16U  FAT_GetEndClus  (          USB_INT16U   clus_no);

#endif
