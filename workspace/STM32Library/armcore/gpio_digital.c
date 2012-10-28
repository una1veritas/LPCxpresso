/*
 * gpio_digital.c
 *
 *  Created on: 2012/09/30
 *      Author: sin
 */

#include "gpio_digital.h"


const uint32_t GPIOPeripheral[] = {
		0, // Arduino Headers
		RCC_AHB1Periph_GPIOA, RCC_AHB1Periph_GPIOB, RCC_AHB1Periph_GPIOC,
		RCC_AHB1Periph_GPIOD, RCC_AHB1Periph_GPIOE, RCC_AHB1Periph_GPIOF,
		RCC_AHB1Periph_GPIOG, RCC_AHB1Periph_GPIOH, RCC_AHB1Periph_GPIOI };

const GPIO_TypeDef * GPIOPort[] =
		{ 0, GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG, GPIOH, GPIOI };

const uint16_t GPIOPin[] = { GPIO_Pin_0, GPIO_Pin_1, GPIO_Pin_2, GPIO_Pin_3,
		GPIO_Pin_4, GPIO_Pin_5, GPIO_Pin_6, GPIO_Pin_7, GPIO_Pin_8, GPIO_Pin_9,
		GPIO_Pin_10, GPIO_Pin_11, GPIO_Pin_12, GPIO_Pin_13, GPIO_Pin_14,
		GPIO_Pin_15, GPIO_Pin_All };

#define digitalPinToGPIOPeriph(p) 	(GPIOPeripheral[ (p) >> 5 & 0x07])
#define digitalPinToGPIOPort(p) 	(GPIOPort[ (p) >> 5 & 0x07])
#define digitalPinToGPIOPin(p) 		(GPIOPin[ (p) & 0x1f])

//#define digitalPinHasPWM(p)         ((p) == 4 || (p) == 5 || (p) == 6 || (p) == 7 || (p) == 9 || (p) == 10)

#define NUM_DIGITAL_PINS            32
//#define NUM_ANALOG_INPUTS           8
//#define analogInputToDigitalPin(p)  ((p < 8) ? (p) + 24 : -1)


uint8 GPIOPort_number(GPIO_TypeDef * port) {
	uint8 ith;
	for (ith = 0 ; ith < 10 ; ith++ ) {
		if ( GPIOPort[ith] == port )
			return ith;
	}
	return 0;
}

/*
 static const uint8_t SDA = 16; // PC1
 static const uint8_t SCL = 17; // PC0

 // Map SPI port
 static const uint8_t SS   = 10; // PB4
 static const uint8_t MOSI = 11;
 static const uint8_t MISO = 12;
 static const uint8_t SCK  = 13; // PB7
 static const uint8_t LED_BUILTIN = 14;
 */

void GPIOMode(GPIO_TypeDef * port, uint16 pins,
		GPIOMode_TypeDef mode,
		GPIOSpeed_TypeDef speed,
		GPIOOType_TypeDef otype,
		GPIOPuPd_TypeDef pull) {

	GPIO_InitTypeDef GPIO_InitStructure;

	// enum GPIOMode_TypeDef =
	//	  GPIO_Mode_IN   = 0x00, /*!< GPIO Input Mode */
	//	  GPIO_Mode_OUT  = 0x01, /*!< GPIO Output Mode */
	//	  GPIO_Mode_AF   = 0x02, /*!< GPIO Alternate function Mode */
	//	  GPIO_Mode_AN   = 0x03  /*!< GPIO Analog Mode */

	//typedef enum {
	//  GPIO_OType_PP = 0x00, // push-pull
	//  GPIO_OType_OD = 0x01 // open drain ?
	// }GPIOOType_TypeDef;

	//typedef enum {
	//  GPIO_PuPd_NOPULL = 0x00,
	//  GPIO_PuPd_UP     = 0x01,
	//  GPIO_PuPd_DOWN   = 0x02
	// }GPIOPuPd_TypeDef;

	if ( mode == GPIO_Mode_IN )
		pull = GPIO_PuPd_UP;

//	typedef enum	{
// 	  GPIO_Speed_2MHz   = 0x00, /*!< Low speed */
//	  GPIO_Speed_25MHz  = 0x01, /*!< Medium speed */
//	  GPIO_Speed_50MHz  = 0x02, /*!< Fast speed */
//	  GPIO_Speed_100MHz = 0x03  /*!< High speed on 30 pF (80 MHz Output max speed on 15 pF) */
//	}GPIOSpeed_TypeDef;

	// wake up the port
	RCC_AHB1PeriphClockCmd(GPIOPeripheral[GPIOPort_number(port)], (FunctionalState)ENABLE);
	//
	GPIO_InitStructure.GPIO_Pin = pins;
	GPIO_InitStructure.GPIO_Mode = mode;
	GPIO_InitStructure.GPIO_Speed = speed;
	GPIO_InitStructure.GPIO_PuPd = pull;
	GPIO_InitStructure.GPIO_OType = otype;
	//
	GPIO_Init(port, &GPIO_InitStructure);
}


void pinMode(uint8 pin,
		GPIOMode_TypeDef mode,
		GPIOSpeed_TypeDef clk,
		GPIOPuPd_TypeDef pupd) {
	GPIO_InitTypeDef GPIO_InitStructure;
//	GPIOPuPd_TypeDef gpio_pupd;

	// enum GPIOMode_TypeDef =
	//	  GPIO_Mode_IN   = 0x00, /*!< GPIO Input Mode */
	//	  GPIO_Mode_OUT  = 0x01, /*!< GPIO Output Mode */
	//	  GPIO_Mode_AF   = 0x02, /*!< GPIO Alternate function Mode */
	//	  GPIO_Mode_AN   = 0x03  /*!< GPIO Analog Mode */

	//typedef enum {
	//  GPIO_OType_PP = 0x00, // push-pull
	//  GPIO_OType_OD = 0x01 // open drain ?
	// }GPIOOType_TypeDef;

	//typedef enum {
	//  GPIO_PuPd_NOPULL = 0x00,
	//  GPIO_PuPd_UP     = 0x01,
	//  GPIO_PuPd_DOWN   = 0x02
	// }GPIOPuPd_TypeDef;

	if (pin >= NUM_DIGITAL_PINS) {
		// wake up the port
		RCC_AHB1PeriphClockCmd(digitalPinToGPIOPeriph(pin), (FunctionalState) ENABLE);
		//
		GPIO_InitStructure.GPIO_Pin   = digitalPinToGPIOPin(pin);
		GPIO_InitStructure.GPIO_Mode  = mode;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd  = pupd;
		GPIO_InitStructure.GPIO_Speed = clk;
		//
		GPIO_Init((GPIO_TypeDef*) digitalPinToGPIOPort(pin), &GPIO_InitStructure);
	} else {
		// mapping from arduino pins to original pins must be implemented.
	}
}

/*
 static void turnOffPWM(uint8_t timer) {
 }
 */
void digitalWrite(uint8 pin, uint8 val) {
	if ( val ) {
		//? Bit_SET : Bit_RESET ));
		GPIO_SetBits((GPIO_TypeDef*) digitalPinToGPIOPort(pin), digitalPinToGPIOPin(pin));
	} else {
		GPIO_ResetBits((GPIO_TypeDef*) digitalPinToGPIOPort(pin), digitalPinToGPIOPin(pin));
	}
}

void GPIOWrite(GPIO_TypeDef * port, uint16 portValue) {
	GPIO_Write(port, portValue);
}

uint16_t digitalRead(uint8 pin) {
	uint8 mode = (digitalPinToGPIOPort(pin)->MODER) >> ((uint16_t)digitalPinToGPIOPin(pin) * 2);
	if ( mode == GPIO_Mode_OUT )
		return (GPIO_ReadOutputDataBit((GPIO_TypeDef*)digitalPinToGPIOPort(pin),
				(uint16_t) digitalPinToGPIOPin(pin)) ?
				HIGH : LOW );
	return (GPIO_ReadInputDataBit((GPIO_TypeDef*)digitalPinToGPIOPort(pin),
			(uint16_t)digitalPinToGPIOPin(pin)) ?
			HIGH : LOW );
}

uint8_t digitalPin(const GPIO_TypeDef * port, uint16 pin) {
	uint8_t portNo;
	for(portNo = 0; portNo < 7; portNo++) {
		if ( GPIOPort[portNo] == port )
			break;
	}
	return ((portNo<<5) + pin);

}

/*
 void togglePin(uint8 pin) {
 if (pin >= BOARD_NR_GPIO_PINS) {
 return;
 }

 GPIO_ToggleBit(PIN_MAP[pin].gpio_device, PIN_MAP[pin].gpio_bit);
 }
 */

/*
 void ConfigPin(GPIO_TypeDef *myGPIO, uint32_t PIN, uint32_t MODE, uint32_t SPEED, uint32_t PUPD) {

//         myGPIO: The GPIOx port for the selected pin
//         MODE: 0 = INPUT .... 1 = OUTPUT .... 2 = ALTERNATE FUNCTION .... 3 = ANALOG
//         SPEED: 0 = 2MHz (Low Speed) .... 1 = 25MHz (Med. Speed) .... 2 = 50MHz (Fast Speed) .... 3 = 100MHz/80MHz (High Speed)(100MHz(30pf) - 80MHz(15pf))
//         PUPD: 0 = No Pull-Up / No Pull-Down .... 1 = Pull-Up Enabled .... 2 = Pull-Down Enabled .... 3 = Reserved

myGPIO->MODER |= (MODE << (PIN * 2));//OUTPUT
myGPIO->OSPEEDR |= (SPEED << (PIN * 2));//50MHz
myGPIO->PUPDR |= (PUPD << (PIN * 2)); //Set it for NO PUPD
}
 */
