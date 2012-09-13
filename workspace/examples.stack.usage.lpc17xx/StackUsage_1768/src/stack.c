/*
 * stack.c
 *
 *  Created on: Jul 7, 2010
 *      Author: nxp12832
 */

extern unsigned char *__heaps;
extern const unsigned long _vStackTop;
extern const unsigned char _pvHeapStart;
const unsigned long stackinitconst = 0xDEADBEEF;

void StackHeapInit(void)
{
    register unsigned long *StackPointer asm("sp");
    unsigned long *StackLimit = (unsigned long *)&_pvHeapStart;

    while(StackLimit < StackPointer)
        *(StackLimit++) = stackinitconst;
}

unsigned long StackHeapFree(void)
{
    register unsigned long *StackPointer asm("sp");
    unsigned long *StackLimit;

#if defined (__REDLIB__)
    if(!__heaps)
#endif
        StackLimit = (unsigned long *)&_pvHeapStart;
#if defined (__REDLIB__)
    else
        StackLimit = (unsigned long *)__heaps;

    if((unsigned long)StackLimit&0x3)
    {
        StackLimit += 4 - (((unsigned long)StackLimit)&0x3);
    }
#endif

    return (StackPointer - StackLimit) * 4;
}

unsigned long StackHeapMinFree(void)
{
    unsigned long UnusedCount = 0, MaxUnusedCount = 0;
    register unsigned long *StackPointer asm("sp");
    unsigned long *StackLimit;

#if defined (__REDLIB__)
    if(!__heaps)
#endif
        StackLimit = (unsigned long *)&_pvHeapStart;
#if defined (__REDLIB__)
    else
        StackLimit = (unsigned long *)__heaps;

    if((unsigned long)StackLimit&0x3)
    {
        StackLimit += 4 - (((unsigned long)StackLimit)&0x3);
    }
#endif

    while(StackLimit < StackPointer)
    {
        if((*StackLimit) == stackinitconst)
        {
            UnusedCount++;
        } else
        {
            if(UnusedCount > MaxUnusedCount)
                MaxUnusedCount = UnusedCount;
            UnusedCount = 0;
        }
        StackLimit++;
    }
    if(UnusedCount > MaxUnusedCount)
        MaxUnusedCount = UnusedCount;
    return MaxUnusedCount*4;
}
