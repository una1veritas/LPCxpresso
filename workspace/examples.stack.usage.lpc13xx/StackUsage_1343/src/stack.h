/*
 * stack.h
 *
 *  Created on: Jul 7, 2010
 *      Author: nxp12832
 */

#ifndef STACK_H_
#define STACK_H_

extern unsigned char *__heaps;
extern const unsigned long _vStackTop;
extern const unsigned char _pvHeapStart;

#define StackHeapSize() (((unsigned long)&_vStackTop) - ((unsigned long)&_pvHeapStart))
unsigned long StackHeapMinFree(void);
unsigned long StackHeapFree(void);
#define DEBUG_OUTPUT_BUFFER_SIZE 82
#define DEBUG_INPUT_BUFFER_SIZE 22

void StackHeapInit(void);

#endif /* STACK_H_ */
