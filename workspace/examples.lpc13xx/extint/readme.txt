extint
=====================
This project contains an external interrupt example for the LPCXpresso
board mounted with an LPC1343 Cortex-M3 part.

When downloaded to the board and executed, LED2 will be illuminated.
Then each time an external interrupt is triggered - by connecting P2.1
to ground - the state of LED2 will toggle.

The project makes use of code from the following library project:
- CMSISv1p30_LPC13xx : for CMSIS 1.30 files relevant to LPC13xx

This library project must exist in the same workspace in order
for the project to successfully build.

For more details, read the comments in config.h
