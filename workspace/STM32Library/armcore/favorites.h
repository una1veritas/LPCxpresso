/*
 * myfavourites.h
 *
 *  Created on: 2012/10/08
 *      Author: sin
 */

#ifndef MYFAVOURITES_H_
#define MYFAVOURITES_H_

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

#include "stm32f4xx_gpio.h"


typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long    uint64;   // Unsigned 64 bit quantity

typedef uint8 boolean;
typedef uint8 byte;
typedef uint16 word;
typedef uint32 quadword;
typedef uint64 octword;

//typedef unsigned int          boolean;  // Boolean

typedef signed char 	int8;
typedef short 			int16;
typedef int 			int32;
typedef long long 		int64;
typedef double          float64;    // Double precision floating point
typedef float           float32;    // Single precision floating point

//
#ifndef NULL
#define NULL 0
#endif

#define HIGH 0x1
#define LOW  0x0

#define DEC ((uint8)10)
#define HEX ((uint8)16)
#define BIN ((uint8)2)
#define OCT ((uint8)8)

#define max(a, b)  ((a) < (b) ? (b) : (a))
#define min(a, b)  ((a) < (b) ? (a) : (b))
#define abs(x) 		((x) < 0? -(x) : (x))



#endif /* MYFAVOURITES_H_ */
