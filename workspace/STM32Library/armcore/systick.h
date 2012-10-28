/*
 * systick.h
 *
 *  Created on: 2012/10/08
 *      Author: sin
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx.h"
#include "favorites.h"

static volatile uint32 SysTick_counts;

void SysTick_Handler(void);

void delay(const uint32_t dlyTicks);

void SysTick_Start();
void SysTick_Init(uint32 ticks);

uint32 systicks();

#ifdef __cplusplus
	}
#endif

#endif /* SYSTICK_H_ */
