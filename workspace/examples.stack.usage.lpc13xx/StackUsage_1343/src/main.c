/*
===============================================================================
 Name        : main.c
 Author      : NXP Semiconductors
 Version     :
 Copyright   : (C) Copyright 2010
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC13xx.h"
#endif

#include "debug.h"
#include "stack.h"

static int callcount = 0;

// Big struct is initialized to zeros by the C language startup code
struct big_struct {
    long abc123[8][9];
    int i;
} g_bs;


// callme() accepts a structure argument.
//
// Since the structure is passed by value and not as a
// pointer, the C language creates a duplicate copy of it on the stack.
void callme(struct big_struct bs)
{
	volatile int minfree = StackHeapMinFree();
	debug_printf("\t Call(%d) MinRemainingStack: %d; Stack Free: %d\n",
										callcount++,
										minfree,
										(int)StackHeapFree());
    if((bs.i) && (minfree > sizeof(g_bs)))
    {
        bs.i--;
        callme(bs);
    }
}

int main(void)
{
	debug_printf("Starting with %d bytes of stack/heap. max/current usage: %d/%d. Size of one struct: %d\n",
	        (int)StackHeapSize(), (int)StackHeapMinFree(), (int)StackHeapFree(), sizeof(g_bs));

	while(1)
	{
		callcount = 0;
	    callme(g_bs);
	    debug_printf("callme(%d): %d/%d\n", g_bs.i, (int)StackHeapMinFree(), (int)StackHeapFree());
            g_bs.i++;
    }


	// Enter an infinite loop, just incrementing a counter
	volatile static int i = 0 ;
	while(1) {
		i++ ;
	}
	return 0 ;
}
