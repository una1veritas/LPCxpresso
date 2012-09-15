/*
 * systick.h
 *
 *  Created on: 18 Dec 2009
 *      Author: Andy
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

#include <stdint.h>

// ****************
// * systick_delay() - creates a delay of the appropriate number of Systicks
// * (happen every 1 ms)
// ****************
void systick_delay (uint32_t delayTicks);


#endif /* SYSTICK_H_ */
