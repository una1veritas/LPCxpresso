usbmsd
=====================
This project implements a USB mass storage device.

To run this example, you must attach a USB cable to the board. See
the "Getting Started Guide" appendix for details. You may also
connect the LPCXpresso board to a base board from a 3rd party tool
partner.

When downloaded to the board and executed, the PC will recognize
a USB mass storage device containing a text file.

One thing we have seen that can cause trouble with the USB examples
is the Windows driver install. Since the example projects all use
the same USB Vendor ID and Product ID, if you try out the HID
example and then try out the Mass Storage example, Windows may try
to use the HID driver it had already installed with the Mass
Storage example code. To fix this, go to the Windows Device Manager,
find the broken "HID" device and select "Uninstall." Then unplug the
device and plug it back in. Windows should correctly identify the
device as being a Mass Storage Class device and install the correct
driver.

The project makes use of code from the following library project:
- CMSISv1p30_LPC13xx : for CMSIS 1.30 files relevant to LPC13xx

This library project must exist in the same workspace in order
for the project to successfully build.

For more details, read the comments in config.h
