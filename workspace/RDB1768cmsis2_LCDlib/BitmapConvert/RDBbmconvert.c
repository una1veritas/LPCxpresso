//*****************************************************************************
//   +--+       
//   | ++----+   
//   +-++    |  
//     |     |  
//   +-+--+  |   
//   | +--+--+  
//   +----+    Copyright (c) 2009 Code Red Technologies Ltd. 
//
// RDBbmconvert.c processes bitmaps saved out from the GIMP image editor in
// 'c source form' into a format suitable for use by the RDB1768 LCD driver
// and example code.
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

// **************************************************

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h> 

// EMBEDDED_VERSION must exist if this code is to be built within RedSuite
// and run on the RDB1768 itself. Running the code in this way requires
// some slight changes to the source, which this define will enable.
//#define EMBEDDED_VERSION 1

// USE_ARGUMENTS must exist if code is to use argc/argv processing
// to obtain input/output filenames
#define USE_ARGUMENTS 1

// Default filenames used if not taken from argc/argv processing
#define IN_FILE "logo.c"
#define OUT_C_FILE "logo_out.c"
#define OUT_H_FILE "logo_out.h"
#define ARRAY_NAME "logo"

#ifdef EMBEDDED_VERSION
#include "NXP\LPC17xx\type.h"
#include "NXP\LPC17xx\target.h"
#endif

// Macro to convert RGB888 colors output by GIMP into RGB565 colors displayed by
// the RDB1768's LCD controller/screen. 
#define TRANSLATE24BIT_TO_RGB565(c)    ((((c) & 0x00ff0000) >> 19) | \
                                 ((((c) & 0x0000ff00) >> 5) & 0x000007e0) | \
                                 ((((c) & 0x000000ff) << 8) & 0x0000f800))

// Function to exit program.
// If run in host mode, this will simply call exit(). But if run in embedded
// mode, the code will simply enter an infinite loop.
void quitconvertor (void)
{
#ifdef EMBEDDED_VERSION
	while (1) {};
#else
	exit (1);
#endif
}
	
// Function to process a string of the form '(<num>)' to remove the brackets 
// from around the number, returning the number as an integer.
int removebrackets (char * numstring)
{	
	int index1 = 0;	// Pointer into input string
	int index2 = 0;	// Pointer into string used to hold number without ()
	int loopquit = 0;	// Flag to control exit from loop
	unsigned char ctemp;	// Variable to hold current char being processed
	unsigned char tempstring [255];	// String to hold number without ()
	
	do {
		ctemp = numstring [index1];	// Read char from input string
	 	if (isdigit(ctemp)) {		// Is it a decimal digit? 
	 		tempstring [index2]= ctemp;	// Yes, copy char into string 
	 		index2++;	
	 	}
	 	if (ctemp == ')')	// Are we at end of input string, ie the closing )
	 		loopquit = 1;	// Yes, set flag
	 	index1++;	// Increment pointer into input string
	 } while (loopquit != 1);	// Loop until flag set
	
	 tempstring [index2] = 0;	// Add terminating zero to string
	 
	 // Call atoi to convert number string into integer, and return value
	 return (atoi(tempstring));	
}

// Function to display help information on the program.
// Execution quits once the information has been displayed.
void display_help (char *prog_name)
{
	printf ("%s - RDB1768 Bitmap conversion utility\n", prog_name);
	printf ("%s -help : displays this message\n", prog_name);
	printf ("Three parameters, infile.c, outfile.c, array_name\n\n");
	// Now quit
	quitconvertor();
}

// Function to check file extension of the filename passed to it
// If the last character in the string does not match 'ext' and
// the last but one character is not a '.', then reports error
// and quits.
void checkfileextension (char *filename, unsigned char ext)
{
  int templen;
  int error = 0;
  templen = strlen (filename);
  if (filename [templen-1] != ext)
  {	error = 1; }
  if (filename [templen-2] != '.')
  {	error = 1; }
  if (error == 1)
  {
    printf ("Error: %s should have .%c extension", filename,ext);
    quitconvertor();
  }
}

// Function to process current line of array data being processed
// to position of the last " character (delimiting the string).
// Also sets the variable pointed to by *endofarray if it detects
// that this line is the last in the array - by spotting the
// terminating sequence of ");
int checklineend (unsigned char *linestring, int *endofarray)
{
  unsigned char ctemp;
  int linelength, count;
  linelength = strlen (linestring);
  count=  linelength;
  ctemp = linestring [count];
  while ((ctemp != '\"') && (ctemp != ';') && (count >= 0))
  {
    count--;
    ctemp = linestring [count];
  }
  if (count < 0)
  {
    printf ("Error in character array\n");
    printf ("%s\n", linestring);
    quitconvertor();
  }
  if (ctemp == ';')
  {
    if ((linestring [count-1] == ')') && (linestring [count-2] == '\"'))
    {
      // Last line of array found
      count -=2;
      *endofarray = 1;
      return (count);
    }
    else
    {
      printf ("Incorrectly formated last line of array found\n");
      printf ("%s\n", linestring);
      quitconvertor ();
    }
  }
  if (ctemp == '\"')
  {
    *endofarray = 0;
    return (count);
  }
  printf ("Incorrectly formated array line found\n");
  printf ("%s\n", linestring);
  quitconvertor ();
  return (-1);  // Should never reach here
}

// Function to detect if character is an octal digit.
// Returns 1 if it is, else 0.
int isoctal (unsigned char c)
{
  int oct = 0;
  switch (c)
  {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
         oct = 1;
  }
  return (oct);
}

// *********************
// *** Main function ***
// *********************

#ifdef USE_ARGUMENTS
int main(int argc, char *argv[]) {
#else
int main(void) {
#endif
	
     FILE *fp_in, *fp_out_c, *fp_out_h;
     int i;
     char instring[255];
     char instringval[255];
     char tempstr [255];
     int invalue;
     int width, height;
     unsigned char ctemp;
     int linelenloop;

     char filename_in [255];
     char filename_out_c [255];
     char filename_out_h [255];
     char array_name [255];
     
     unsigned char pixel24 [3];
     unsigned int col24;
     unsigned short col16;
     
     int numpixels, totalpixels;
     int endofarray;
     int inlinelength;
     int lastline;

     int rgbloop;
     int index;
     int templen;
     int skip;

#ifdef USE_ARGUMENTS

     // Check to see if optional "-help" option used in invocation of program
    for (i = 1; i < argc; i++)  // Skip argv[0] (program name)
    {
    	if (strcmp(argv[i], "-help") == 0)
    	{
    		 display_help (argv[0]);
    	}
    }
    
    // If we get here, then, no optional arguments
    // Now check invoked with three options - infile, outfile, array name
    // If not, display help
    if (argc !=4)
    {
		 display_help (argv[0]);	
    }   
 
    // Now store the argument strings
    strcpy (filename_in, argv[1]);
    strcpy (filename_out_c, argv[2]);
    strcpy (filename_out_h, argv[2]);
    strcpy (array_name,argv[3]);
    
    // Check file extensions of filenames given are correct.
    checkfileextension (filename_in, 'c');
    checkfileextension (filename_out_c, 'c');

    // Now set headerfile name. We assume the filename_out_c has a .c
    // extension, so we just replace the 'c' with a 'h'.
    templen = strlen (filename_out_h);
    filename_out_h [templen-1] = 'h';

#else
    // Copy default filenames in if we are not using argc/argv
    // No error checking done on these - assume they correctly
    // set at start of code !
    strcpy (filename_in, IN_FILE);
    strcpy (filename_out_c,OUT_C_FILE );
    strcpy (filename_out_h, OUT_H_FILE );
    strcpy (array_name, ARRAY_NAME);
#endif
    
    // Now check that input and output files are different
    if (strcmp (filename_in, filename_out_c) == 0)
    {
      printf ("Error: Input and outfile filenames should be different\n");
      quitconvertor();
    }


#ifdef EMBEDDED_VERSION
// Call to NXP initialisation code - not essential, but will set clocks
// up so code runs more quickly. Requires NXP target.c code in project
//    TargetResetInit();
#endif
     
     printf ("RDB1768 Bitmap conversion utility\n");
     printf ("=================================\n");
     fp_in = fopen(filename_in,"r"); // Open input file for reading
     if (fp_in == NULL)
     {	// fopen failed
       printf ("Read file open failed - %s\n", filename_in);
       quitconvertor();
     }
     fp_out_c = fopen(filename_out_c,"w"); // Open output c file for writing
     if (fp_out_c == NULL)
     {	 // fopen failed
        printf ("C write file open failed - %s\n", filename_out_c);
        quitconvertor();
     }

// RedSuite semihosting support currently only supports one file for
// writing at once, so if we building an embedded version we restructure
// the code such that the H file is written out after the C file rather
// than in parallel.
     
#ifndef EMBEDDED_VERSION
     fp_out_h = fopen(filename_out_h,"w"); // Open output h file for writing
     if (fp_out_h == NULL)
     {
       // fopen failed
       printf ("H write file open failed - %s\n", filename_out_h);
       quitconvertor();
     }
#endif

    // *******************************************
    // Now start actually processing of input file
    // *******************************************

    // First of all, check first line of input file to ensure it
    // is a C source file of the correct format created by GIMP.

    fgets (instring, 255,fp_in);
    if (strncmp(instring,"/* GIMP RGB C-Source",20 ) != 0)
    {
      printf ("Input file does not appear to be a GIMP C source file\n");
      quitconvertor();
    }

    // We now assume that the file is of the correct format.

    printf ("Processing bitmap width...\n");
    // ** Process image width

    do { // Scan through input file until we reach the 1st #define
       fscanf(fp_in,"%s", instring);
    } while (strncmp(instring,"#define",7 ) !=0);

    // Read the name of the define (which we will ignore)
    fscanf(fp_in,"%s", instring);
    // Read the value of the define - which will be in format '(<num>)'
    fscanf (fp_in,"%s",instringval);
    // Convert '(<num>)' to number
    width = removebrackets (instringval);

    // Check pixel width is not great than width of RDB1768 LCD screen
    if (width > 128)
    {
	printf ("Error - input image width > 128 pixel\n");
	printf ("RDB1768 LCD is only 128 x 128 pixels\n");
	quitconvertor();
    }

    // Write out to C file definition of variable containing array width
    // in format 'array_name'_width. Include value
    fprintf (fp_out_c, "unsigned int %s_width = %d;\n", array_name, width);

#ifndef EMBEDDED_VERSION
    // Write out to H file declaration of variable containing array width
    // in format 'array_name'_width.
    fprintf (fp_out_h, "extern unsigned int %s_width;\n", array_name);
#endif


    printf ("Processing bitmap height...\n");
    // ** Process image height

    do { // Scan through input file until we reach the next #define
   	 fscanf(fp_in,"%s", instring);
    } while (strncmp(instring,"#define",7 ) !=0);

    // Read the name of the define (which we will ignore)
    fscanf(fp_in,"%s", instring);
    // Read the value of the define - which will be in format '(<num>)'
    fscanf (fp_in,"%s",instringval);
    // Convert '(<num>)' to number
    height = removebrackets (instringval);

    // Check pixel height is not great than height of RDB1768 LCD screen
    if (height > 128)
    {
	printf (";Error - input image height > 128 pixel\n");
	printf ("RDB1768 LCD is only 128 x 128 pixels\n");
	quitconvertor();
    }

    // Write out to C file definition of variable containing array height
    // in format 'array_name'height. Include value
    fprintf (fp_out_c,"unsigned int %s_height = %d;\n", array_name, height);

#ifndef EMBEDDED_VERSION
    // Write out to H file declaration of variable containing array height
    // in format 'array_name'_height.
    fprintf (fp_out_h,"extern unsigned int %s_height;\n", array_name);
#endif

    // Skip to end of current line.
    fgets (instring, 255,fp_in);

    // Read next line, which is the define of bytes per pixel
    // which we will skip
    fgets (instring, 255,fp_in); // read next line to skip it
    if (strncmp(instring,"#define",7 ) !=0)	// Just check content
    {
    	printf ("Error, failed to find #define of bytes per pixel at expected\n");
    	printf (" location in input file : %s\n", filename_in);
      	quitconvertor();
    }

    // Read next line, which is the define of cast to array
    // which we will skip
    fgets (instring, 255,fp_in); // read next line to skip it
    if (strncmp(instring,"#define",7 ) !=0) // Just check content
    {
    	printf ("Error, failed to find #define of bytes per pixel at expected\n");
    	printf (" location in input file : %s\n", filename_in);
      	quitconvertor();
    }

    // Following lines will be either 1 or 2 (if user asked GIMP to include a
    // comment) further #defines. Comment may be over couple of lines. We will
    // ignore these. After these #defines should be the array which should begin
    // "static const unsigned....."
    i = 0;
    do
    {
        fgets (instring, 255,fp_in); // read next line
        // Check that we haven't found start of array
        if (strncmp(instring,"static const unsigned",21) !=0)
        { i++; // increment counter for number of lines read
        }
    // Loop until we have either read 4 lines, or we find array start
    } while ((i < 4) && (strncmp(instring,"static const unsigned",21) !=0));

    if (strncmp(instring,"static const unsigned",21) !=0)
    {
    	printf ("Error, failed to find bitmap array definition at expected\n");
    	printf (" location in input file : %s\n", filename_in);
      	quitconvertor();
    }

    // Write out to C file start of definition of bitmap array using width and height
    // previously obtained
    fprintf (fp_out_c, "const unsigned short %s_pixel_data [%d * %d] = \n", array_name, width, height);
    fprintf (fp_out_c, "{");

#ifndef EMBEDDED_VERSION
    // Write out to H file start of declaration of bitmap array
    fprintf (fp_out_h, "extern const unsigned short %s_pixel_data [];\n", array_name);
#endif

    // Now begin processing actual bitmap values
    printf ("Processing contents of bitmap array...\n");

    // Read first line of array contents
    fgets (instring, 255,fp_in);

    // First line of array contents should start with '("'
    if (strncmp(instring,"(\"",2 ) != 0)
    {
    	// Error - we should be at start of 1st line of array data
    	printf ("Error, failed to find bitmap array data at expected\n");
    	printf (" location in input file : %s\n", filename_in);
    	quitconvertor();
    }

    rgbloop = 0;	 // counter to keep track of which bytes in pixel have processed
    numpixels = 0;   // number of pixels processed
    totalpixels = width * height;	// total number of pixels to be processed
    endofarray = 0;	// flag to indicate end of array reached
    linelenloop = 0;	// counter to keep track of how many pixels output on this line
    index =2;	// counter pointing into position on current input line

    inlinelength = checklineend (instring, &lastline);

    while ((endofarray != 1)   && (numpixels < totalpixels))
    {
      skip = 0;  // used to skip pixel setting section if necessary for this iteration
      ctemp = instring [index];	// read next char on current input line

      if (ctemp == '\\') // if the character is a backslash
      {
        switch (instring [index+1])
        {
          case '\\':     // Double backslash used to indicate an actual backslash
                 invalue = '\\';
                 index +=2;
                 break;
          case '"':      // Backslash+quote used to indicate an actual quote
                 invalue = '\"';
                 index +=2;
                 break;
          case '0': // Is it a octal character
          case '1':
          case '2':
          case '3':
          case '4':
          case '5':
          case '6':
          case '7':
    		// An octal number could be 1,2 or 3 characters long
                tempstr [0] = instring [index+1];
    		tempstr [1] = instring [index+2];
    		tempstr [2] = instring [index+3];
    		tempstr [3]= 0;
                if (isoctal(tempstr[1]) == 0)
                {
                  tempstr[1] = 0;
                  index += 2;
                }
                else if  (isoctal(tempstr[2]) == 0)
                {  tempstr[2] = 0;
                  index += 3;
                }
                else
                {
                  index +=4;
                }
    		invalue = (unsigned char) strtoul(tempstr, NULL ,8);
    		break;
          default:
                  printf ("Error - backslash followed by 'normal' character\n");
                  printf ("%s\n", instring);
                  quitconvertor();
                //invalue = (unsigned char)instring [index];
                //index++;
      } // end of switch
     }   // end if //
     else
     {
       if (ctemp == '"')
       {
         if ( index == inlinelength )
         {
           printf ("** Error - reached end of line quote\n");
           printf ("%s\n", instring);
           quitconvertor();
         }
         if ( index == (inlinelength-1) )
         {
           printf ("** Error - erroneous quote at end of line\n");
           printf ("%s\n", instring);
           quitconvertor();
         }
         if (instring [index+1] != '"')
         {
           printf ("** Error - erroneous quote in middle of line\n");
           printf ("%s\n", instring);
           quitconvertor();
         }
          if (instring [index+1] == '"')
         {
           // Found double quote - used to delimit between two other characters
           skip = 1;    // Flag that don't need to process this as part of a pixel
           index +=2;   // Skip the double quote
         }
       }
       else
       {
         // assume char is the direct value of this byte of RGB888 pixel
         invalue = (unsigned char)instring [index];
         index++;
       }
     }
     if (skip == 0)   // If we didn't have a double quote to delimit between elements
     {
       // Copy value for one byte into pixel
       pixel24 [rgbloop] = (unsigned char) invalue;
       // Move onto next byte of pixel
       rgbloop++;
       // Check if we have the 3 bytes for this pixel
       if (rgbloop == 3)
       {
         // We have 3 bytes making up pixel
	 // Merge 3 bytes into single value
	 col24= (pixel24 [0]<<16)|(pixel24 [1]<<8)|pixel24 [2];

	// Convert color from RGB888 to RGB565
	col16 = TRANSLATE24BIT_TO_RGB565(col24);

	// Write pixel value out into array in output C file
	if (linelenloop > 0)
	{
          fprintf (fp_out_c,",");
        }
	fprintf (fp_out_c,"0x%x", col16);
	// Increment number of pixels processed
	numpixels++;
	// Increment number of pixels printed on this line of output C file
	linelenloop++;
	if ((linelenloop == 10)&& (numpixels < totalpixels))
	{	// Start a new line in output C file
	  fprintf (fp_out_c,",\n");
	  linelenloop=0;
	}
	rgbloop = 0; // reset for next pixel
      }  // end if rgbloop == 3
     } // if skip == 0
 
     if (index >= inlinelength)
     {
       if (lastline == 1)
       {
         // we have reached the end of the array
         endofarray = 1;
       }
       else
       {
         // Get next line
         fgets (instring, 255,fp_in);
         inlinelength = checklineend (instring, &lastline);
         index = 2;
       }
     }

    } // of while loop


    // Write out end bracket of array definition
    fprintf(fp_out_c," };\n");

    printf ("C file created\n");
    fclose(fp_in); /* close the file before ending program */
    fclose(fp_out_c); /* close the file before ending program */

#ifdef EMBEDDED_VERSION
    // RedSuite semihosting support currently only supports one file for
    // writing at once, so if we building an embedded version we restructure
    // the code such that the H file is written out after the C file rather
    // than in parallel.

    fp_out_h = fopen(filename_out_h,"w"); // open for writing
    if (fp_out_h == NULL)
    {// fopen failed
     	 printf ("H write file open failed - %s\n", filename_out_h);
     	 quitconvertor();
    }
    fprintf (fp_out_h, "extern unsigned int %s_width;\n", array_name);
    fprintf (fp_out_h,"extern unsigned int %s_height;\n", array_name);
    fprintf (fp_out_h, "extern const unsigned short %s_pixel_data [];\n", array_name);
#endif

    fclose(fp_out_h); /* close the file before ending program */

    printf ("Corresponding H file created\n");

    printf ("Processing complete!\n\n");

    // Final error check to make sure array fully processed.
    // Print message if appears to be problem
    if ((endofarray != 1) || (numpixels != totalpixels))
    {
      printf ("** Note potential issue with processing **\n");
      printf ("endofarray = %d : Should be 1 for end of array detected\n",endofarray);
      printf ("numpixels = %d, totalpixels= %d : Should be equal\n",numpixels,totalpixels);
    }

    return 0 ;
}
