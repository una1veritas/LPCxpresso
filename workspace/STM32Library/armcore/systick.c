/*
 * systick.cpp
 *
 *  Created on: 2012/10/08
 *      Author: sin
 */
//#include "stm32f4xx_it.h"
#include "systick.h"

void SysTick_Handler(void) {
	SysTick_counts++; /* increment timeTicks counter */
}

void delay(const uint32_t dlyTicks) {
	uint32_t currTicks = SysTick_counts;

	while ((SysTick_counts - currTicks) < dlyTicks)
		;
}

void SysTick_Start() {
	SysTick_Init(1000);
}

void SysTick_Init(uint32 ticks) {
	RCC_ClocksTypeDef RCC_Clocks;
	RCC_GetClocksFreq(&RCC_Clocks);
	SysTick_Config(RCC_Clocks.HCLK_Frequency / ticks);
}

uint32 systicks() {
	return SysTick_counts;
}

