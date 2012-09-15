RDB1768 Bitmap Readme
=====================
The RDB1768 LCD library contains routines that can be used to display
bitmap images onto the board's LCD screen. Such images need to be 
included as C arrays within your application source code.

The library functions have been developed using such C arrays
generated directly from images using the bitmap editor called the
"GNU Image Manipulation Program" (better known as the "GIMP").

For more information on the GIMP, go to http://www.gimp.org/


To create a bitmap in the required format, first of all load your
bitmap into the GIMP, scaling the image if necessary to ensure that
it is of a suitable size (maximum of 128x128 pixels).

You should also ensure that it is being handled as a 'RGB' image
rather than an 'indexed' image, such as a GIF. To convert the image
mode, ensure that the Image -> Mode menu option is set to RGB.

Then to creat a C source file from the image:

1) Select the menu entry "File > Save as".

2) Select "File Type (By Extension)".

3) Select the "C source code" file type.

4) Enter the filename into the name field (for example - "mypic.c"),
   then click Save.

   The Save as C-Source dialog will now appear.

5) Enter a suitable string into the "Prefixed name" field, for 
   example "mypic".

6) Tick the "Use macros instead of struct" entry, and leave the
   other entries blank.

7) Click the save icon within the Save as C-Source dialog.


Your image will now be saved to disk as C code, in a form similar to:

===== vvv =====
/* GIMP RGB C-Source image dump (mypic.c) */

#define MYPIC_WIDTH (48)
#define MYPIC_HEIGHT (67)
#define MYPIC_BYTES_PER_PIXEL (3) /* 3:RGB, 4:RGBA */
#define MYPIC_PIXEL_DATA ((unsigned char*) MYPIC_pixel_data)
static const unsigned char MYPIC_pixel_data[48 * 67 * 3 + 1] =
("\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
   :
   :
 "\363\364\364\363\366\365\364\364\364\363");
===== ^^^ =====

Note that the string array (MYPIC_pixel_data in the above example) 
contains three bytes per pixel - one for each of the three Red,Green
and Blue components making up each pixel. Each component will be of
a value between 0 and 255. They may be represented in the string 
array as either a printable character (for example, 'a', 'b', and so
on), or else an octal representation of the value for non-printable 
characters (for example '\377').


***********************************
* Using the 24-bit image directly *
***********************************

The array contained within the C file created by the GIMP defines
your image in 24-bit (RGB888) format, with 3 bytes per pixel.

However the contents of the C file need tweaking before it is 
suitable for use by the bitmap display functions contained within
the RDB1768 LCD library.

As a minimum, edit the file to:

===== vvv =====
unsigned int MYPIC_WIDTH = 48;
unsigned int MYPIC_HEIGHT = 67;
const unsigned char MYPIC_pixel_data[48 * 67 * 3 + 1] =
("\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
 "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
   :
   :
 "\363\364\364\363\366\365\364\364\364\363");
===== ^^^ =====

Also create a header file, for example mypic.h:
===== vvv =====
extern unsigned int MYPIC_WIDTH;
extern unsigned int MYPIC_HEIGHT;
const unsigned char MYPIC_pixel_data[];
===== ^^^ =====

You can then display your bitmap onto the LCD screen in your 
application code as follows:

===== vvv =====
#include "mypic.h"
#include "lcd.h"
   :
  LCD_PlotBitmap24 (0, 0, MYPIC_pixel_data ,MYPIC_WIDTH, MYPIC_HEIGHT);
   :
===== ^^^ =====

Note that the LCD_PlotBitmap24() will actually display your image 
onto the LCD in 16-bit (RGB565) color, doing the 24-bit to 16-bit
conversion on the fly.



***************************************************
* Using a 16-bit image created from the 24-bit one*
***************************************************

It is possible to pre-process your image such that this color 
conversion is done before building your application. This will both
improve the performance of the LCD accesses carried out by your 
application, and also decrease the amount of memory required to store
your image (as each pixel will only require two bytes of memory, 
rather than the original three bytes of the 24-bit image).

The supplied application, RDBbmconvert.exe will carry out this 
conversion, and also generate appropriately formated .c and .h files
from the original .c file created by GIMP. 

In order to use RDBbmconvert.exe, copy it out of the BitmapConvert
folder of the RedSuite RDB1768cmsis_LCDlib project and into a convenient
working folder, where you have placed the image files to be 
processed. Then open a Command prompt window and navigate into the
working folder. To invoke RDBbmconvert.exe, use the following 
command:

  RDBbmconvert infile.c outfile.c arrayname

This will take the file 'infile.c' created by the GIMP, process
it - creating the files 'outfile.c' and a matching 'outfile.h',
and will use the string 'arrayname' as a prefix for the width, 
height and pixel_data.

Thus if we invoked the convertor using:

  RDBbmconvert pic24.c pic16.c pic16

this would result in the output C and H files similar to:

===== C file =====
unsigned int pic16_width = 48;
unsigned int pic16_width = 67;
const unsigned short pic16_pixel_data[48 * 67] =
{0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,
0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,
   :
   :
0xffff,0xffff,0xffff,0xffff,0xffff,0xffff };
===== ^^^^^^ =====

===== H file =====
extern unsigned int pic16_width;
extern unsigned int pic16_height;
const unsigned short pic16_pixel_data[];
===== ^^^^^^ =====

Note that the above array now contains a single 16-bit value for each
pixel, rather than 3 8-bit values as the original 24-bit image did.


You could then display your image in your application code thus:

===== vvv =====
#include "pic16.h"
#include "lcd.h"
   :
  LCD_PlotBitmap (0,0,pic16_pixel_data,pic16_width,pic16_height);
   :
===== ^^^ =====



