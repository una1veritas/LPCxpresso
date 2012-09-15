RDB1768cmsis2_usb_bootloader
===========================
This project provides a flash-based USB secondary bootloader for
the RDB1768 development board fitted with NXP LPC1768 MCU. 

The bootloader is based on the LPCUSB mass storage example
(RDB1768cmsis2_usb_msc) with a new block driver level to access the
LPC1768's flash rather than the micro-SD interface. When executed,
RDB1768cmsis2_usb_bootloader treats the top 448KB of the LPC1768's
512KB of flash as a memory drive.

The principles of the bootloader itself are based on NXP's bootloader
application note for the LPC1768 - AN10866 - available from:

  http://ics.nxp.com/support/documents/microcontrollers/?type=appnote

However unlike the NXP bootloader, RDB1768cmsis2_usb_bootloader does
not implement "Code Read Protection" (CRP) functionality described in
AN10866, though if required this could be added by the user.

Requirements for building bootloader project
--------------------------------------------
The project makes use of code from the following library projects:
- CMSISv2p00_LPC17xx    : for CMSIS 2.00 files relevant to LPC17xx
- RDB1768cmsis2_LCDLib   : for RDB1768 LCD driver files
- RDB1768cmsis2_usbstack : for RDB1768 build of LPCUSB stack

These three library projects must exist in the same workspace in order
for the project to successfully build.

In addition, the RDB1768cmsis2_usb_bootloader sources will check 
during a build that RDB1768cmsis2_usbstack is configured such that
it does not emit semihosted debug messages.  If you encounter a build
error, then check in the file 'usbdebug.h' in 
RDB1768cmsis2_usbstack/inc that you have the symbol 'DBG' defined as

  #define DBG(x ...)
  
rather than, for example, mapping onto printf. This can be done by
simply undefining the 'DEBUG_MESSAGES' symbol.

Using the bootloader
--------------------
Build the bootloader within the IDE and then load it into flash over
the RDB usb debug connection (by selecting the Debug option within 
IDE).

Once the bootloader has been downloaded into the flash by the IDE,
you can then terminate the debug session within the IDE and 
disconnect the usb debug connection from the RDB1768.

Now connect the RDB1768 to your PC via the USB device mini-B 
connector. The RDB1768 will then power up and the bootloader
will execute:

1) If the bootloader detects that a valid user application exists in
   the flash, then
   
   a) If the bootloader detects the joystick button is not being
      pressed, then the bootloader will invoke the user 
      application.
   b) If the bootloader detects the joystick button is being
      pressed, the user application will be ignored and the 
      bootloader will enter USB mass storage mode.

2) If the bootloader cannot detect a user application in flash,
   then the bootloader will enter USB mass storage mode.
   
The bootloader will display appropriate messages to the RDB1768's
LCD screen at each stage of the above process (though if it invokes
a user application which uses the LCD, you may not see these
messages.)

What is a 'valid' user application
----------------------------------
When the bootloader is checking if a user application exists in the
flash, it will do this in two steps:

First of all it will check to see if the first sector being used as
flash drive (at 64KB/0x10000 in the address map) is blank. If it is
blank, then there is obviously no valid user application.

Secondly, if the sector is not blank, then it will carry out a
checksum operation on the first 8 locations of the start of user
flash. This is the same check that is carried out by the LPC1768's
built-in serial bootloader, as documented in the LPC1768's User
Manual. This checksum evaluation is carried out in the function 
"user_code_present()" in the file "sbl_iap.c". It can be disabled by
undefining the symbol "COMPUTE_BINARY_CHECKSUM".

For details of how to create binary applications in the correct
format to pass this checksum test, please see the section 
"Creating applications to upload via the bootloader" below.

Uploading a binary
------------------
Once the bootloader enters USB mass storage mode, the connected PC
should detect the board as a USB removable drive.

If you open a Windows explorer view onto this drive, you will see
a single file called "firmware.bin" which fills the whole of the 
flash drive.

To upload a new user application binary, first of all delete 
"firmware.bin", then copy the application binary to the drive 
(see below on how to create the binary). Remember to dismount
the RDB1768 drive from within Windows, to ensure the write has
actually taken place.

Also note that the usb mass storage interface to the bootloader
is not intended to provide a generic flash drive. Thus, for 
example, copying multiple files to the RDB1768 flash, and then 
deleting some of them, may not give the behavior that you expect -
either from Windows, or by the bootloader itself. Note also that
the bootloader will not preserve file information between resets.
The next time the board boots in USB mode, you will always see
just a single file 'firmware.bin' filling the drive.

Recommended usage is to: 
1) Delete "firmware.bin"
2) Upload only a single valid binary image 
3) Dismount the drive from within Windows
4) Reset the board to execute the uploaded binary.

In particular if you upload files other than binaries suitable for
running on the RDB1768/LPC1768, you may get very unexpected behavior
the next time you reset the board and the bootloader tries to execute
them. This is a good reason as to why to not to disable the checksum
comparison that the bootloader carries out by default!


Creating applications to upload via the bootloader
--------------------------------------------------
The bootloader uses the top 448KB of the LPC1768's 512KB of flash as
a memory drive. This means that it occupies all 14 of the 32KB 
sectors in the flash, running from address 0x10000 (64KB) in the 
memory map. This avoids a number of pitfalls and issues that would be
caused by using 4KB sectors as well as the 32KB ones (a disk is not 
expected to have sectors of differing sizes!).

Thus applications that you upload via the bootloader need to be built
slightly differently to normal, as they will be executed from a 
non-zero address in the memory map. This is done by modifying the 
scripts used by the linker to control code and data placement.

You will also need to create a plain binary version of your 
application (and add a checksum to it if your build of the 
bootloader carries out the checksum comparison).

Modifying your linker scripts
-----------------------------
The Code Red tools suite by default uses a "managed linker script" 
mechanism to create a script for each Build configuration that is 
suitable for the MCU selected for the project, and the C libraries 
being used.

It will create (and at times modify) three linker script files for
each build configuration of your project:

<projname>_<buildconfig>_lib.ld
<projname>_<buildconfig>_mem.ld
<projname>_<buildconfig>.ld

This set of hierarchical files are used to define the C libraries
being used, the memory map of the system and the way your code and
data is placed in memory. These files will be located in the build
configuration subdirectories of your project (Debug and Release).

When creating applications to be uploaded with the bootloader, you 
need to bypass the managed linker script mechanism and create your
own bespoke linker scripts.

One very important point though is that you are advised not to simply
modify the managed linker scripts in place, but instead to copy them
to another location and modify them there. This will prevent any 
chance of the tools overwritting them at some point in the future.

The following steps detail the simplest way of creating linker 
scripts suitable for creating bootload'able image for the project
"myproj".

1) Create a new subdirectory within your project called, say, 
   "linkscripts".

2) Build the application for debug. This will create the three
   managed link script (.ld) files in the Debug subdirectory of
   your project.

3) Copy the three managed linker script (.ld) files into the 
   linkscripts directory.

4) Modify the filenames of the linker script files in your 
   linkscripts directory to remove the word "Debug". Thus
   "myproj_Debug.ld" would become "myproj.ld", and similarly
   for the other two .ld files.

5) Open the file "myproj.ld". Near the top of this file you will
   see two INCLUDE statements. Modify these to remove the word 
   "Debug" and to insert path information. Thus they will become:
   
   INCLUDE "..linkscripts/myproj_lib.ld "
   INCLUDE "..linkscripts/myproj_mem.ld "
   
   Save the updated "myproj.ld"

6) Now open the file "myproj_mem.ld". You need to change two lines
   in this file, such that the base address used for the image is 
   64KB (0x10000) rather than 0x0, and the the length of the flash
   is 448KB (0x70000) rather than 512KB (0x80000). Thus you will need
   to change the MFlash512 and __top_MFlash512 lines as follows:

   MFlash512 (rx) : ORIGIN = 0x10000, LENGTH = 0x70000

   __top_MFlash512 = 0x10000 + 0x70000;
   
   Save the updated "myproj_mem.ld".
   
Having created your own linker script files, you now need to turn off
the managed linker script mechanism. To do this:

1) Open the Project properties. 
2) In the left-hand list of the Properties window, open "C/C++ Build"
   and select "Settings" and then the "Tool Settings" tab.
3) Now choose "MCU Linker - Target" and untick the Manage linker 
   script box.
4) Now enter the name of the your linker script into the Linker script
   field. This will need to include relative path information, so that
   the linker can find the script (relative to the current build 
   configuration directory (i.e. Debug or Release). For the project
   "myproj", with your linker scripts stored in the "linkscripts"
   subdirectory, the required entry will be:
   
      "../linkscripts/myproj.ld" 
    
   Note that the quote marks are required.

5) Now switch to editing the properties for the Release build
   configuration, and repeat the previous steps to change this to
   use you own linker script instead of the managed link script.

Creating a binary image
-----------------------
By default, the Code Red tools suite creates an ELF image (Executable 
Linkable Format) which is suitable for downloading via the debugger.
However to use the bootloader, you need to convert this into a plain
binary file suitable for the processor to execute directly from 
memory.

To do this automatically each time you carry out a build, you can 
modify you projects post-build steps. To do this:

1) Open the Project properties.
 
2) Select "C/C++ Build" -> "Settings" and switch to the "Build Steps"
   tab.

3) In the "Post-build steps" box, you need to add the following two
   commands:
 
   arm-none-eabi-objcopy -O binary ${BuildArtifactFileName} ${BuildArtifactFileBaseName}.bin
   checksum ${BuildArtifactFileBaseName}.bin;
   
   Note that commands you add to the list need to be separate by 
   semi-colons (";") and that the hash ("#") is comment character
   that will cause the rest of the line to be ignored.

4) Now switch to the Release build configuration and add to the 
   above commands to the post-build steps.
       
[ Some old versions of the Code Red tools may not have the checksum
[ program installed. If you encounter problems then copy the
[ executable contained in the "checksum" subdirectory of the 
[ RDB1768_usb_bootloader project to the "bin" subdirectory at the
[ top level of your Code Red tools installation directory.
  
Now, when you build your project, a .bin file should be created in the
Debug or Release directory which is suitable for downloading via the
usb bootloader.

 
Aside
-----
Note that the reason that RDB1768cmsis_usb_bootloader is strictly a
"secondary" bootloader is because it sits behind the LPC1768's built
in flash bootloader - which works over the serial interface. For 
more details on the built-in bootloader, please see the "LPC17xx 
Flash memory interface and programming" chapter of the NXP LPC17xx
User Manual.

The usb secondary bootloader makes use of the joystick button on the
RDB1768 in order for the user to request entry into the bootloader,
rather than the "ISP" button on the board. This is because the 
"ISP" button is used by the built-in serial bootloader.


~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Note that this example project is intended for use with Red Suite /
LPCXpresso IDE v4.0 or later.

Use of this project with earlier versions of the Code Red IDE is 
not recommended or supported.