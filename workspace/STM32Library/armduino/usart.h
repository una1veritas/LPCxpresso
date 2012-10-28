/*
 * usart.h
 *
 *  Created on: 2012/10/14
 *      Author: sin
 */

#ifndef USART_H_
#define USART_H_

#include <stdint.h>

#include "armduino.h"

struct ring;

class USARTSerial {
	// class constants
private:
	static const char nl = '\n';
	static const char cr = '\r';

	// instance variables
	ring & rx, & tx;
public:
	USARTSerial(ring & rxbuf, ring & txbuf) : rx(rxbuf), tx(txbuf) { }

	void begin(uint32_t baud);

	uint16_t write(const uint16_t ch);
	uint16_t write(uint16_t * p, uint16_t length);
	uint16_t read();
	uint16_t available();

	uint16_t print(const char c) { return write((uint16_t)c); }
	uint16_t print(const char * s);
	uint16_t print(const uint32_t val, const uint8_t base = DEC) {
		return printNumber(val, base);
	}
	uint16_t print(const int32_t val, const uint8_t base = DEC) {
		return ( val < 0 ? print('-') : 0) + printNumber(abs(val), base);
	}
	uint16_t print(const float val, uint8_t prec = 2) {
		return printFloat(val, prec);
	}

	uint16_t println() { return print(nl); }
	uint16_t println(const char * s) { return print(s) + println(); }
	uint16_t println(const float val, uint8_t prec = 2) {
		return print(val, prec) + println();
	}
	uint16_t println(const uint32_t val, const uint8_t base = DEC) {
		return printNumber(val, base) + println();
	}
	uint16_t println(const int32_t val, const uint8_t base = DEC) {
		return print(val, base) + println();
	}

	//
private:
	uint16_t printNumber(const uint32_t val, const uint8_t base);
	uint16_t printFloat(const float val, const uint8_t prec);

};

extern USARTSerial usart3;

#ifdef __cplusplus
extern "C" {
#endif

void USART3_IRQHandler(void);

#ifdef __cplusplus
}
#endif

#endif /* USART_H_ */
