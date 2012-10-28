/*
 * usart.h
 *
 *  Created on: 2012/10/14
 *      Author: sin
 */

#ifndef USART_H_
#define USART_H_

#include "favorites.h"

void usart_begin(uint32 baud);
size_t usart_write(uint8 ch);
size_t usart_print(const char * s);
//size_t usart_printInt(uint32 val, uint8 base);
size_t usart_printNumber(uint32 val);
size_t usart_printFloat(float val, uint8 prec);

#endif /* USART_H_ */
