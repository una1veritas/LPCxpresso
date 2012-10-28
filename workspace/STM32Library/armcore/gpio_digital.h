/*
 * gpio_digital.h
 *
 *  Created on: 2012/09/30
 *      Author: sin
 */

#ifndef _GPIO_DIGITAL_H_
#define _GPIO_DIGITAL_H_


#include "favorites.h"

#ifndef USE_STDPERIPH_DRIVER
#define USE_STDPERIPH_DRIVER 1
#endif

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"


typedef enum {
	PA0 = 1 << 5,
	PB0 = 2 << 5,
	PC0 = 3 << 5,
	PC1, PC2, PC3, PC4, PC5, PC6, PC7, PC8, PC9, PC10, PC11, PC12, PC13, PC14, PC15,
	PD0 = 4 << 5,
	PD1, PD2, PD3, PD4, PD5, PD6, PD7, PD8, PD9, PD10, PD11, PD12, PD13, PD14, PD15,
	PE0 = 5 << 5,
	PF0 = 6 << 5,
	PG0 = 7 << 5, PG1, PG2, PG3, PG4, PG5, PG6, PG7, PG8, PG9, PG10, PG11, PG12, PG13, PG14, PG15,
} Pin;

#define INPUT  	GPIO_Mode_IN
#define OUTPUT 	GPIO_Mode_OUT
#define ALTFUNC GPIO_Mode_AF
#define ANALOG 	GPIO_Mode_AN

#define PUSHPULL 	 GPIO_OType_PP
#define	OPENDRAIN 	 GPIO_OType_OD

#define	NOPULL 	 GPIO_PuPd_NOPULL
#define PULLUP 	 GPIO_PuPd_UP
#define PULLDOWN GPIO_PuPd_DOWN

#define SLOWSPEED 	GPIO_Speed_2MHz
#define MEDSPEED 	GPIO_Speed_25MHz
#define FASTSPEED 	GPIO_Speed_50MHz
#define HIGHSPEED 	GPIO_Speed_100MHz

void pinMode(uint8 pin,	GPIOMode_TypeDef mode,
		GPIOSpeed_TypeDef clk, GPIOPuPd_TypeDef pupd);
//		GPIOSpeed_TypeDef clk = GPIO_Speed_50MHz,
//		GPIOPuPd_TypeDef pupd = GPIO_PuPd_NOPULL );
uint16 digitalRead(uint8 pin);
void digitalWrite(uint8 pin, uint8 val);

uint8 digitalPin(const GPIO_TypeDef * port, uint16 pin);

void GPIOMode(GPIO_TypeDef * port, uint16 pins, GPIOMode_TypeDef mode,
		GPIOSpeed_TypeDef speed, GPIOOType_TypeDef otype, GPIOPuPd_TypeDef pull);
//		GPIOSpeed_TypeDef speed  = GPIO_Speed_50MHz,
//		GPIOOType_TypeDef otype = GPIO_OType_PP,
//		GPIOPuPd_TypeDef pull = GPIO_PuPd_NOPULL);
void GPIOWrite(GPIO_TypeDef * port, uint16 value);


#endif /* _GPIO_DIGITAL_H_ */
