/*
 * portpin.h
 *
 *  Created on: 2012/10/17
 *      Author: sin
 */

#ifndef PORTPIN_H_
#define PORTPIN_H_


enum PortNameDef {
	NotAPort = 0,
	PortA = 1,
	PortB,
	PortC,
	PortD,
	PortE,
	PortF,
	PortG,
	PortH,
	PortI
};

#define PinBit(n)  (1<<(n))
enum GPIOPin {
	PA0 = (PortA <<16) | PinBit(0),
	PB0 = (PortB <<16) | PinBit(0),
	PC0 = (PortC <<16) | PinBit(0),
	PD0 = (PortD <<16) | PinBit(0),
	PD1 = (PortD <<16) | PinBit(1),
	PD2 = (PortD <<16) | PinBit(2),
	PD3 = (PortD <<16) | PinBit(3),
	PD4 = (PortD <<16) | PinBit(4),
	PD5 = (PortD <<16) | PinBit(5),
	PD6 = (PortD <<16) | PinBit(6),
	PD7 = (PortD <<16) | PinBit(7),
	PD8 = (PortD <<16) | PinBit(8),
	PD9 = (PortD <<16) | PinBit(9),
	PD10 = (PortD <<16) | PinBit(10),
	PD11 = (PortD <<16) | PinBit(11),
	PD12 = (PortD <<16) | PinBit(12),
	PD13 = (PortD <<16) | PinBit(13),
	PD14 = (PortD <<16) | PinBit(14),
	PD15 = (PortD <<16) | PinBit(15),
	PE0 = (PortE <<16) | PinBit(0),
	PF0 = (PortF <<16) | PinBit(0),
	PG0 = (PortG <<16) | PinBit(0),
	PH0 = (PortH <<16) | PinBit(0),
	PI0 = (PortI <<16) | PinBit(0)
};


#endif /* PORTPIN_H_ */
