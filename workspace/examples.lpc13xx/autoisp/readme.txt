autoisp
=====================
This project contains a USB ISP (In System Programming) example for a
USB-modified LPCXpresso board mounted with an LPC1343 Cortex-M3 part.

When downloaded to the board and executed, the USB mass-storage-device
bootloader in ROM will be started. After a 45 second delay, the MCU will
reset and begin executing the new code that was downloaded.
 
The project makes use of code from the following library project:
- CMSISv1p30_LPC13xx : for CMSIS 1.30 files relevant to LPC13xx

This library project must exist in the same workspace in order
for the project to successfully build.

For more details, read the comments in config.h
