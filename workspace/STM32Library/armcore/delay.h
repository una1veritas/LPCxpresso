/*
 * delay.h
 *
 *  Created on: 2012/10/08
 *      Author: sin
 */

#ifndef DELAY_H_
#define DELAY_H_

#include <stm32f4xx.h>
#include "favorites.h"

#define __delay()						\
do {							\
  volatile uint32 i;				\
  for (i = 0; i < 10000; ++i)				\
    __asm__ __volatile__ ("nop\n\t":::"memory");	\
} while (0)

inline void _delay_ms(uint32 t) {
	while (t-- > 0) {
		__delay();
	}
}

#endif /* DELAY_H_ */
