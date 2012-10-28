/*
 * usart.c
 *
 *  Created on: 2012/10/14
 *      Author: sin
 */

#include <stm32f4xx.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_usart.h> // under Libraries/STM32F4xx_StdPeriph_Driver/inc and src

#include "favorites.h"
#include "gpio_digital.h"
#include "usart.h"

void usart_begin(uint32 baud) {
//	GPIO_InitTypeDef GPIO_InitStruct; // this is for the GPIO pins used as TX and RX
	USART_InitTypeDef USART_InitStruct; // this is for the USART1 initilization
//	NVIC_InitTypeDef NVIC_InitStructure; // this is used to configure the NVIC (nested vector interrupt controller)

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, (FunctionalState) ENABLE);
	GPIOMode(GPIOB, GPIO_Pin_10 | GPIO_Pin_11, ALTFUNC, FASTSPEED, PUSHPULL, PULLUP);
	/* USART3 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, (FunctionalState) ENABLE);

	digitalWrite(PD12, LOW);
	digitalWrite(PD15, LOW);

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3 ); // TX -- PB10
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3 ); // RX -- PB11

	USART_InitStruct.USART_BaudRate = baud;	// the baudrate is set to the value we passed into this init function
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;// we want the data frame size to be 8 bits (standard)
	USART_InitStruct.USART_StopBits = USART_StopBits_1;	// we want 1 stop bit (standard)
	USART_InitStruct.USART_Parity = USART_Parity_No;// we don't want a parity bit (standard)
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // we don't want flow control (standard)
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; // we want to enable the transmitter and the receiver

	USART_Init(USART3, &USART_InitStruct); // again all the properties are passed to the USART_Init function which takes care of all the bit setting
	/*
	 USART_ITConfig(USART3, USART_IT_RXNE, ENABLE); // enable the USART1 receive interrupt

	 NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	 // we want to configure the USART1 interrupts
	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;// this sets the priority group of the USART1 interrupts
	 NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;// this sets the subpriority inside the group
	 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	// the USART1 interrupts are globally enabled
	 NVIC_Init(&NVIC_InitStructure);	// the properties are passed to the NVIC_Init function which takes care of the low level stuff
	 */

	// finally this enables the complete USART1 peripheral
	USART_Cmd(USART3, (FunctionalState) ENABLE);

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

size_t usart_write(uint8 ch) {
	while (!(USART3->SR & 0x00000040))
	;
	USART_SendData(USART3, (uint16) ch);
	/* Loop until the end of transmission */
	while (USART_GetFlagStatus(USART3, USART_FLAG_TC )
			== RESET) {
	}
	return 1;
}


size_t usart_print(const char * s) {
	size_t n = 0;
	while ( *s ) {
		usart_write(*s);
		s++;
		n++;
	}
	return n;
}


size_t usart_printNumber(uint32 val) {
	size_t n = 0;
	uint8 base = 10;
	uint32 divider = 1000000000;
	uint8 msd = 0;
	uint8 digit;
	while ( divider > 0 ) {
		digit = val / divider % base;
		if ( digit || msd ) {
			usart_write('0'+(digit>10 ? digit+7 : digit));
			msd = 1;
			n++;
		}
		divider /= base;
	}
	return n;
}

size_t usart_printFloat(float val, uint8 prec) {
	size_t n = 0;
	if ( val < 0 ) {
		usart_write('-');
		val = -val;
		n++;
	}
	uint32 intpart = (uint32)val;
	val -= intpart;
	n += usart_printNumber(intpart);
	int i;
	if ( val > 0 ) {
		usart_write('.');
		n++;
		for(i = 0; i < prec; i++) {
			val *= 10;
			usart_printNumber((uint32)val);
			val -= (uint32)val;
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
/*
int usart::usart_getch() {
	int ch;
	while (USART_GetFlagStatus(USART3, USART_FLAG_RXNE )
			== RESET) {
	}
	ch = USART_ReceiveData(USART3);
	//uartPutch(ch);
	return ch;
}
*/
