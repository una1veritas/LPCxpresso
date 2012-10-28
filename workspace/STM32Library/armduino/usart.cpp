/*
 * usart.c
 *
 *  Created on: 2012/10/14
 *      Author: sin
 */

#include <stm32f4xx.h>
#include <misc.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_usart.h> // under Libraries/STM32F4xx_StdPeriph_Driver/inc and src

#include "usart.h"


struct ring {
	static const int RINGBUFFER_SIZE = 64;

	uint16 buffer[RINGBUFFER_SIZE];
	uint16 head, tail;
	uint16 count;

	ring() { init(); }

	void init() {
		head = 0;
		tail = 0;
		count = 0;
	}

	uint16 ringin(uint16 c) {
		if ( is_full() ) {
			head++;  head %= RINGBUFFER_SIZE;
			// buffer over run occurred!
		} else
			count++;
		buffer[tail++] = c;
		tail %= RINGBUFFER_SIZE;
		return c;
	}

	uint16 ringout() {
		if ( is_empty() )
			return 0;
		uint16 c = buffer[head++];
		head %= RINGBUFFER_SIZE;
		count--;
		return c;
	}

	uint16 peek() {
		if ( is_empty() )
			return 0;
		return buffer[head];
	}

	bool is_full() {
		return (count > 0) && head == tail;
	}

	bool is_empty() {
		return (count == 0) && head == tail;
	}

	uint16 buffered() {
		return count;
	}

} rx3, tx3;

USARTSerial usart3(rx3, tx3);

void USARTSerial::begin(uint32_t baud) {
//	GPIO_InitTypeDef GPIO_InitStruct; // this is for the GPIO pins used as TX and RX
	USART_InitTypeDef USART_InitStruct; // this is for the USART1 initilization
	NVIC_InitTypeDef NVIC_InitStructure; // this is used to configure the NVIC (nested vector interrupt controller)

//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, (FunctionalState) ENABLE);
	GPIOMode(RCC_AHB1Periph_GPIOB, GPIOB, GPIO_Pin_10 | GPIO_Pin_11,
			GPIO_Mode_AF, GPIO_Speed_50MHz, GPIO_OType_PP, GPIO_PuPd_UP);
	/* USART3 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, (FunctionalState) ENABLE);

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3 ); // TX -- PB10
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3 ); // RX -- PB11

	USART_InitStruct.USART_BaudRate = baud;	// the baudrate is set to the value we passed into this init function
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;// we want the data frame size to be 8 bits (standard)
	USART_InitStruct.USART_StopBits = USART_StopBits_1;	// we want 1 stop bit (standard)
	USART_InitStruct.USART_Parity = USART_Parity_No;// we don't want a parity bit (standard)
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // we don't want flow control (standard)
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; // we want to enable the transmitter and the receiver

	USART_Init(USART3, &USART_InitStruct); // again all the properties are passed to the USART_Init function which takes care of all the bit setting

	USART_ITConfig(USART3, USART_IT_RXNE, (FunctionalState) ENABLE); // enable the USART3 receive interrupt
	USART_ITConfig(USART3, USART_IT_TXE, (FunctionalState) DISABLE);
/*
USART_IT	説明
USART_IT_PE	Parity Error interrupt
USART_IT_TXE	Transmit Data Register empty interrupt
USART_IT_TC	Transmission complete interrupt
USART_IT_RXNE	Receive Data register not empty interrupt
USART_IT_IDLE	Idle line detection interrupt
USART_IT_LBD	LIN break detection interrupt
USART_IT_CTS	CTS change interrupt (not available for UART4 and UART5)
USART_IT_ERR	Error interrupt (Frame error, noise error, overrun error)

NewState	説明
ENABLE	有効にします
DISABLE	無効にします
*/
	 NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	 // we want to configure the USART3 interrupts
	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;// this sets the priority group of the USART3 interrupts
	 NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;// this sets the subpriority inside the group
	 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	// the USART3 interrupts are globally enabled
	 NVIC_Init(&NVIC_InitStructure);	// the properties are passed to the NVIC_Init function which takes care of the low level stuff

	// finally this enables the complete USART3 peripheral
	USART_Cmd(USART3, (FunctionalState) ENABLE);

	rx.init();
	tx.init();
}

/* This function is used to transmit a string of characters via
 * the USART specified in USARTx.
 *
 * It takes two arguments: USARTx --> can be any of the USARTs e.g. USART1, USART2 etc.
 * 						   (volatile) char *s is the string you want to send
 *
 * Note: The string has to be passed to the function as a pointer because
 * 		 the compiler doesn't know the 'string' data type. In standard
 * 		 C a string is just an array of characters
 *
 * Note 2: At the moment it takes a volatile char because the received_string variable
 * 		   declared as volatile char --> otherwise the compiler will spit out warnings
 * */

uint16_t USARTSerial::write(const uint16_t ch) {
	while (USART_GetFlagStatus(USART3, USART_FLAG_TC )
				== RESET);
	tx3.ringin(ch);
	USART_ITConfig(USART3, USART_IT_TXE, (FunctionalState) ENABLE);
	return 1;
}

/*
 * basic unbuffered write
uint16_t USARTSerial::write(uint8_t ch) {
//	usart3tx.ringin(ch);
	while (!(USART3->SR & 0x00000040))
	;
//	ch = usart3tx.ringout();
	USART_SendData(USART3, (uint16_t) ch);
	// Loop until the end of transmission
	while (USART_GetFlagStatus(USART3, USART_FLAG_TC )
			== RESET) {
	}
	return 1;
	return buffered_write(ch);
}
*/

uint16_t USARTSerial::write(uint16_t * p, uint16_t length) {
	uint16_t n = 0;
	while (n++ < length)
		write(*p++);
	return n;
}


uint16_t USARTSerial::print(const char * s) {
	uint16_t n = 0;
	while ( *s ) {
		write(*s);
		s++;
		n++;
	}
	return n;
}


uint16_t USARTSerial::printNumber(uint32_t val, const uint8_t base) {
	uint16_t n = 0;
	bool msd = false;
	uint32_t divider = ( base == 2 ? 1<<31 :
		( base == 16 ? 0x10000000L : 1000000000L ) );

	uint8_t digit;
	while ( divider > 0 ) {
		digit = (val / divider) % base;
		if ( digit || msd || (!msd && (divider%base)) ) {
			write('0' + ( digit > 9 ? digit + 7 : digit));
			msd = true;
			n++;
		}
		divider /= base;
	}
	return n;
}

uint16_t USARTSerial::printFloat(float val, uint8_t prec) {
	uint16_t n = 0;
	if ( val < 0 ) {
		write('-');
		val = -val;
		n++;
	}
	uint32_t intpart = (uint32_t) val;
	val -= intpart;
	n += printNumber(intpart, DEC);
	int i;
	if ( val > 0 ) {
		write('.');
		n++;
		for(i = 0; i < prec; i++) {
			val *= 10;
			printNumber((uint32_t)val, DEC);
			val -= (uint32_t)val;
			n++;
		}
	}
	return n;
}

/**
 * @brief  Waits for then gets a char from the USART.
 * @param  none
 * @retval char
 */

uint16_t USARTSerial::available() {
	return rx3.buffered();
	//if (USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == SET)
	//	return 1;
	//return 0;
}

uint16_t USARTSerial::read() {
	return rx3.ringout();
	//return USART_ReceiveData(USART3);
}

// this is the interrupt request handler (IRQ) for ALL USART3 interrupts

void USART3_IRQHandler(void) {
	// check if the USART1 receive interrupt flag was set
	if (USART_GetITStatus(USART3, USART_IT_RXNE)) {
		rx3.ringin(USART_ReceiveData(USART3));
	}
	if (USART_GetITStatus(USART3, USART_IT_TXE)) {
		if ( tx3.is_empty() ) {
			USART_ITConfig(USART3, USART_IT_TXE, (FunctionalState) DISABLE);
			USART_ClearITPendingBit(USART3, USART_IT_TXE);
		} else {
			USART_SendData(USART3, tx3.ringout());
		}
	}
}

