//*****************************************************************************
//   +--+
//   | ++----+
//   +-++    |
//     |     |
//   +-+--+  |
//   | +--+--+
//   +----+    Copyright (c) 2011-12 Code Red Technologies Ltd.
//
// Microcontroller Startup code for use with Red Suite
//
// Version : 120126
//
// Software License Agreement
//
// The software is owned by Code Red Technologies and/or its suppliers, and is
// protected under applicable copyright laws.  All rights are reserved.  Any
// use in violation of the foregoing restrictions may subject the user to criminal
// sanctions under applicable laws, as well as to civil liability for the breach
// of the terms and conditions of this license.
//
// THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
// OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
// USE OF THIS SOFTWARE FOR COMMERCIAL DEVELOPMENT AND/OR EDUCATION IS SUBJECT
// TO A CURRENT END USER LICENSE AGREEMENT (COMMERCIAL OR EDUCATIONAL) WITH
// CODE RED TECHNOLOGIES LTD.
//
//*****************************************************************************
#if defined (__cplusplus)
#ifdef __REDLIB__
#error Redlib does not support C++
#else
//*****************************************************************************
//
// The entry point for the C++ library startup
//
//*****************************************************************************
extern "C" {
	extern void __libc_init_array(void);
}
#endif
#endif

#define WEAK __attribute__ ((weak))
#define ALIAS(f) __attribute__ ((weak, alias (#f)))

// Code Red - if CMSIS is being used, then SystemInit() routine
// will be called by startup code rather than in application's main()
#if defined (__USE_CMSIS)
#include "stm32f4xx.h"
#endif

//*****************************************************************************
#if defined (__cplusplus)
extern "C" {
#endif

//*****************************************************************************
//
// Forward declaration of the default handlers. These are aliased.
// When the application defines a handler (with the same name), this will
// automatically take precedence over these weak definitions
//
//*****************************************************************************
     void ResetISR(void);
WEAK void NMI_Handler(void);
WEAK void HardFault_Handler(void);
WEAK void MemManage_Handler(void);
WEAK void BusFault_Handler(void);
WEAK void UsageFault_Handler(void);
WEAK void SVC_Handler(void);
WEAK void DebugMon_Handler(void);
WEAK void PendSV_Handler(void);
WEAK void SysTick_Handler(void);
WEAK void IntDefaultHandler(void);

//*****************************************************************************
//
// Forward declaration of the specific IRQ handlers. These are aliased
// to the IntDefaultHandler, which is a 'forever' loop. When the application
// defines a handler (with the same name), this will automatically take
// precedence over these weak definitions
//
//*****************************************************************************
void WWDG_IRQHandler(void) ALIAS(IntDefaultHandler);
void PVD_IRQHandler(void) ALIAS(IntDefaultHandler);
void TAMP_STAMP_IRQHandler(void) ALIAS(IntDefaultHandler);
void RTC_WKUP_IRQHandler(void) ALIAS(IntDefaultHandler);
void FLASH_IRQHandler(void) ALIAS(IntDefaultHandler);
void RCC_IRQHandler(void) ALIAS(IntDefaultHandler);
void EXTI0_IRQHandler(void) ALIAS(IntDefaultHandler);
void EXTI1_IRQHandler(void) ALIAS(IntDefaultHandler);
void EXTI2_IRQHandler(void) ALIAS(IntDefaultHandler);
void EXTI3_IRQHandler(void) ALIAS(IntDefaultHandler);
void EXTI4_IRQHandler(void) ALIAS(IntDefaultHandler);
void DMA1_Stream0_IRQHandler(void) ALIAS(IntDefaultHandler);
void DMA1_Stream1_IRQHandler(void) ALIAS(IntDefaultHandler);
void DMA1_Stream2_IRQHandler(void) ALIAS(IntDefaultHandler);
void DMA1_Stream3_IRQHandler(void) ALIAS(IntDefaultHandler);
void DMA1_Stream4_IRQHandler(void) ALIAS(IntDefaultHandler);
void DMA1_Stream5_IRQHandler(void) ALIAS(IntDefaultHandler);
void DMA1_Stream6_IRQHandler(void) ALIAS(IntDefaultHandler);
void ADC_IRQHandler(void) ALIAS(IntDefaultHandler);
void CAN1_TX_IRQHandler(void) ALIAS(IntDefaultHandler);
void CAN1_RX0_IRQHandler(void) ALIAS(IntDefaultHandler);
void CAN1_RX1_IRQHandler(void) ALIAS(IntDefaultHandler);
void CAN1_SCE_IRQHandler(void) ALIAS(IntDefaultHandler);
void EXTI9_5_IRQHandler(void) ALIAS(IntDefaultHandler);
void TIM1_BRK_TIM9_IRQHandler(void) ALIAS(IntDefaultHandler);
void TIM1_UP_TIM10_IRQHandler(void) ALIAS(IntDefaultHandler);
void TIM1_TRG_COM_TIM11_IRQHandler(void) ALIAS(IntDefaultHandler);
void TIM1_CC_IRQHandler(void) ALIAS(IntDefaultHandler);
void TIM2_IRQHandler(void) ALIAS(IntDefaultHandler);
void TIM3_IRQHandler(void) ALIAS(IntDefaultHandler);
void TIM4_IRQHandler(void) ALIAS(IntDefaultHandler);
void I2C1_EV_IRQHandler(void) ALIAS(IntDefaultHandler);
void I2C1_ER_IRQHandler(void) ALIAS(IntDefaultHandler);
void I2C2_EV_IRQHandler(void) ALIAS(IntDefaultHandler);
void I2C2_ER_IRQHandler(void) ALIAS(IntDefaultHandler);
void SPI1_IRQHandler(void) ALIAS(IntDefaultHandler);
void SPI2_IRQHandler(void) ALIAS(IntDefaultHandler);
void USART1_IRQHandler(void) ALIAS(IntDefaultHandler);
void USART2_IRQHandler(void) ALIAS(IntDefaultHandler);
void USART3_IRQHandler(void) ALIAS(IntDefaultHandler);
void EXTI15_10_IRQHandler(void) ALIAS(IntDefaultHandler);
void RTC_Alarm_IRQHandler(void) ALIAS(IntDefaultHandler);
void OTG_FS_WKUP_IRQHandler(void) ALIAS(IntDefaultHandler);
void TIM8_BRK_TIM12_IRQHandler(void) ALIAS(IntDefaultHandler);
void TIM8_UP_TIM13_IRQHandler(void) ALIAS(IntDefaultHandler);
void TIM8_TRG_COM_TIM14_IRQHandler(void) ALIAS(IntDefaultHandler);
void TIM8_CC_IRQHandler(void) ALIAS(IntDefaultHandler);
void DMA1_Stream7_IRQHandler(void) ALIAS(IntDefaultHandler);
void FSMC_IRQHandler(void) ALIAS(IntDefaultHandler);
void SDIO_IRQHandler(void) ALIAS(IntDefaultHandler);
void TIM5_IRQHandler(void) ALIAS(IntDefaultHandler);
void SPI3_IRQHandler(void) ALIAS(IntDefaultHandler);
void UART4_IRQHandler(void) ALIAS(IntDefaultHandler);
void UART5_IRQHandler(void) ALIAS(IntDefaultHandler);
void TIM6_DAC_IRQHandler(void) ALIAS(IntDefaultHandler);
void TIM7_IRQHandler(void) ALIAS(IntDefaultHandler);
void DMA2_Stream0_IRQHandler(void) ALIAS(IntDefaultHandler);
void DMA2_Stream1_IRQHandler(void) ALIAS(IntDefaultHandler);
void DMA2_Stream2_IRQHandler(void) ALIAS(IntDefaultHandler);
void DMA2_Stream3_IRQHandler(void) ALIAS(IntDefaultHandler);
void DMA2_Stream4_IRQHandler(void) ALIAS(IntDefaultHandler);
void ETH_IRQHandler(void) ALIAS(IntDefaultHandler);
void ETH_WKUP_IRQHandler(void) ALIAS(IntDefaultHandler);
void CAN2_TX_IRQHandler(void) ALIAS(IntDefaultHandler);
void CAN2_RX0_IRQHandler(void) ALIAS(IntDefaultHandler);
void CAN2_RX1_IRQHandler(void) ALIAS(IntDefaultHandler);
void CAN2_SCE_IRQHandler(void) ALIAS(IntDefaultHandler);
void OTG_FS_IRQHandler(void) ALIAS(IntDefaultHandler);
void DMA2_Stream5_IRQHandler(void) ALIAS(IntDefaultHandler);
void DMA2_Stream6_IRQHandler(void) ALIAS(IntDefaultHandler);
void DMA2_Stream7_IRQHandler(void) ALIAS(IntDefaultHandler);
void USART6_IRQHandler(void) ALIAS(IntDefaultHandler);
void I2C3_EV_IRQHandler(void) ALIAS(IntDefaultHandler);
void I2C3_ER_IRQHandler(void) ALIAS(IntDefaultHandler);
void OTG_HS_EP1_OUT_IRQHandler(void) ALIAS(IntDefaultHandler);
void OTG_HS_EP1_IN_IRQHandler(void) ALIAS(IntDefaultHandler);
void OTG_HS_WKUP_IRQHandler(void) ALIAS(IntDefaultHandler);
void OTG_HS_IRQHandler(void) ALIAS(IntDefaultHandler);
void DCMI_IRQHandler(void) ALIAS(IntDefaultHandler);
void CRYP_IRQHandler(void) ALIAS(IntDefaultHandler);
void HASH_RNG_IRQHandler(void) ALIAS(IntDefaultHandler);
void FPU_IRQHandler(void) ALIAS(IntDefaultHandler);



//*****************************************************************************
//
// The entry point for the application.
// __main() is the entry point for Redlib based applications
// main() is the entry point for Newlib based applications
//
//*****************************************************************************
#if defined (__REDLIB__)
extern void __main(void);
#endif
extern int main(void);
//*****************************************************************************
//
// External declaration for the pointer to the stack top from the Linker Script
//
//*****************************************************************************
extern void _vStackTop(void);

//*****************************************************************************
#if defined (__cplusplus)
} // extern "C"
#endif
//*****************************************************************************
//
// The vector table.
// This relies on the linker script to place at correct location in memory.
//
//*****************************************************************************
extern void (* const g_pfnVectors[])(void);
__attribute__ ((section(".isr_vector")))
void (* const g_pfnVectors[])(void) = {
	// Core Level - CM3
	&_vStackTop, // The initial stack pointer
	ResetISR,								// The reset handler
	NMI_Handler,							// The NMI handler
	HardFault_Handler,						// The hard fault handler
	MemManage_Handler,						// The MPU fault handler
	BusFault_Handler,						// The bus fault handler
	UsageFault_Handler,						// The usage fault handler
	0,										// Reserved
	0,										// Reserved
	0,										// Reserved
	0,										// Reserved
	SVC_Handler,							// SVCall handler
	DebugMon_Handler,						// Debug monitor handler
	0,										// Reserved
	PendSV_Handler,							// The PendSV handler
	SysTick_Handler,						// The SysTick handler

	// Chip Level - STM32F2xx
    WWDG_IRQHandler,                  	// Window WatchDog
    PVD_IRQHandler,                   	// PVD through EXTI Line detection
    TAMP_STAMP_IRQHandler,            	// Tamper and TimeStamps through the EXTI line
    RTC_WKUP_IRQHandler,              	// RTC Wakeup through the EXTI line
    FLASH_IRQHandler,                 	// FLASH
    RCC_IRQHandler,                   	// RCC
    EXTI0_IRQHandler,                 	// EXTI Line0
    EXTI1_IRQHandler,                 	// EXTI Line1
    EXTI2_IRQHandler,                 	// EXTI Line2
    EXTI3_IRQHandler,                 	// EXTI Line3
    EXTI4_IRQHandler,                 	// EXTI Line4
    DMA1_Stream0_IRQHandler,          	// DMA1 Stream 0
    DMA1_Stream1_IRQHandler,          	// DMA1 Stream 1
    DMA1_Stream2_IRQHandler,          	// DMA1 Stream 2
    DMA1_Stream3_IRQHandler,          	// DMA1 Stream 3
    DMA1_Stream4_IRQHandler,          	// DMA1 Stream 4
    DMA1_Stream5_IRQHandler,          	// DMA1 Stream 5
    DMA1_Stream6_IRQHandler,          	// DMA1 Stream 6
    ADC_IRQHandler,                   	// ADC1, ADC2 and ADC3s
    CAN1_TX_IRQHandler,               	// CAN1 TX
    CAN1_RX0_IRQHandler,              	// CAN1 RX0
    CAN1_RX1_IRQHandler,              	// CAN1 RX1
    CAN1_SCE_IRQHandler,              	// CAN1 SCE
    EXTI9_5_IRQHandler,               	// External Line[9:5]s
    TIM1_BRK_TIM9_IRQHandler,         	// TIM1 Break and TIM9
    TIM1_UP_TIM10_IRQHandler,         	// TIM1 Update and TIM10
    TIM1_TRG_COM_TIM11_IRQHandler,    	// TIM1 Trigger and Commutation and TIM11
    TIM1_CC_IRQHandler,               	// TIM1 Capture Compare
    TIM2_IRQHandler,                  	// TIM2
    TIM3_IRQHandler,                  	// TIM3
    TIM4_IRQHandler,                  	// TIM4
    I2C1_EV_IRQHandler,               	// I2C1 Event
    I2C1_ER_IRQHandler,               	// I2C1 Error
    I2C2_EV_IRQHandler,               	// I2C2 Event
    I2C2_ER_IRQHandler,               	// I2C2 Error
    SPI1_IRQHandler,                  	// SPI1
    SPI2_IRQHandler,                  	// SPI2
    USART1_IRQHandler,                	// USART1
    USART2_IRQHandler,                	// USART2
    USART3_IRQHandler,                	// USART3
    EXTI15_10_IRQHandler,             	// External Line[15:10]s
    RTC_Alarm_IRQHandler,             	// RTC Alarm (A and B) through EXTI Line
    OTG_FS_WKUP_IRQHandler,           	// USB OTG FS Wakeup through EXTI line
    TIM8_BRK_TIM12_IRQHandler,        	// TIM8 Break and TIM12
    TIM8_UP_TIM13_IRQHandler,         	// TIM8 Update and TIM13
    TIM8_TRG_COM_TIM14_IRQHandler,    	// TIM8 Trigger and Commutation and TIM14
    TIM8_CC_IRQHandler,               	// TIM8 Capture Compare
    DMA1_Stream7_IRQHandler,          	// DMA1 Stream7
    FSMC_IRQHandler,                  	// FSMC
    SDIO_IRQHandler,                  	// SDIO
    TIM5_IRQHandler,                  	// TIM5
    SPI3_IRQHandler,                  	// SPI3
    UART4_IRQHandler,                 	// UART4
    UART5_IRQHandler,                 	// UART5
    TIM6_DAC_IRQHandler,              	// TIM6 and DAC1&2 underrun errors
    TIM7_IRQHandler,                  	// TIM7
    DMA2_Stream0_IRQHandler,          	// DMA2 Stream 0
    DMA2_Stream1_IRQHandler,          	// DMA2 Stream 1
    DMA2_Stream2_IRQHandler,          	// DMA2 Stream 2
    DMA2_Stream3_IRQHandler,          	// DMA2 Stream 3
    DMA2_Stream4_IRQHandler,          	// DMA2 Stream 4
    ETH_IRQHandler,                   	// Ethernet
    ETH_WKUP_IRQHandler,              	// Ethernet Wakeup through EXTI line
    CAN2_TX_IRQHandler,               	// CAN2 TX
    CAN2_RX0_IRQHandler,              	// CAN2 RX0
    CAN2_RX1_IRQHandler,              	// CAN2 RX1
    CAN2_SCE_IRQHandler,              	// CAN2 SCE
    OTG_FS_IRQHandler,                	// USB OTG FS
    DMA2_Stream5_IRQHandler,          	// DMA2 Stream 5
    DMA2_Stream6_IRQHandler,          	// DMA2 Stream 6
    DMA2_Stream7_IRQHandler,          	// DMA2 Stream 7
    USART6_IRQHandler,                	// USART6
    I2C3_EV_IRQHandler,               	// I2C3 event
    I2C3_ER_IRQHandler,               	// I2C3 error
    OTG_HS_EP1_OUT_IRQHandler,        	// USB OTG HS End Point 1 Out
    OTG_HS_EP1_IN_IRQHandler,         	// USB OTG HS End Point 1 In
    OTG_HS_WKUP_IRQHandler,           	// USB OTG HS Wakeup through EXTI
    OTG_HS_IRQHandler,                	// USB OTG HS
    DCMI_IRQHandler,                  	// DCMI
    CRYP_IRQHandler,                  	// CRYP crypto
    HASH_RNG_IRQHandler,               	// Hash and Rng
    FPU_IRQHandler                      // FPU
};

//*****************************************************************************
// Functions to carry out the initialization of RW and BSS data sections. These
// are written as separate functions rather than being inlined within the
// ResetISR() function in order to cope with MCUs with multiple banks of
// memory.
//*****************************************************************************
__attribute__ ((section(".after_vectors")))
void data_init(unsigned int romstart, unsigned int start, unsigned int len) {
	unsigned int *pulDest = (unsigned int*) start;
	unsigned int *pulSrc = (unsigned int*) romstart;
	unsigned int loop;
	for (loop = 0; loop < len; loop = loop + 4)
		*pulDest++ = *pulSrc++;
}

__attribute__ ((section(".after_vectors")))
void bss_init(unsigned int start, unsigned int len) {
	unsigned int *pulDest = (unsigned int*) start;
	unsigned int loop;
	for (loop = 0; loop < len; loop = loop + 4)
		*pulDest++ = 0;
}

#ifndef USE_OLD_STYLE_DATA_BSS_INIT
//*****************************************************************************
// The following symbols are constructs generated by the linker, indicating
// the location of various points in the "Global Section Table". This table is
// created by the linker via the Code Red managed linker script mechanism. It
// contains the load address, execution address and length of each RW data
// section and the execution and length of each BSS (zero initialized) section.
//*****************************************************************************
extern unsigned int __data_section_table;
extern unsigned int __data_section_table_end;
extern unsigned int __bss_section_table;
extern unsigned int __bss_section_table_end;
#else
//*****************************************************************************
// The following symbols are constructs generated by the linker, indicating
// the load address, execution address and length of the RW data section and
// the execution and length of the BSS (zero initialized) section.
// Note that these symbols are not normally used by the managed linker script
// mechanism in Red Suite/LPCXpresso 3.6 (Windows) and LPCXpresso 3.8 (Linux).
// They are provide here simply so this startup code can be used with earlier
// versions of Red Suite which do not support the more advanced managed linker
// script mechanism introduced in the above version. To enable their use,
// define "USE_OLD_STYLE_DATA_BSS_INIT".
//*****************************************************************************
extern unsigned int _etext;
extern unsigned int _data;
extern unsigned int _edata;
extern unsigned int _bss;
extern unsigned int _ebss;
#endif


//*****************************************************************************
// Reset entry point for your code.
// Sets up a simple runtime environment and initializes the C/C++
// library.
//*****************************************************************************
__attribute__ ((section(".after_vectors")))
void
ResetISR(void) {

#ifndef USE_OLD_STYLE_DATA_BSS_INIT
    //
    // Copy the data sections from flash to SRAM.
    //
	unsigned int LoadAddr, ExeAddr, SectionLen;
	unsigned int *SectionTableAddr;

	// Load base address of Global Section Table
	SectionTableAddr = &__data_section_table;

    // Copy the data sections from flash to SRAM.
	while (SectionTableAddr < &__data_section_table_end) {
		LoadAddr = *SectionTableAddr++;
		ExeAddr = *SectionTableAddr++;
		SectionLen = *SectionTableAddr++;
		data_init(LoadAddr, ExeAddr, SectionLen);
	}
	// At this point, SectionTableAddr = &__bss_section_table;
	// Zero fill the bss segment
	while (SectionTableAddr < &__bss_section_table_end) {
		ExeAddr = *SectionTableAddr++;
		SectionLen = *SectionTableAddr++;
		bss_init(ExeAddr, SectionLen);
	}
#else
	// Use Old Style Data and BSS section initialization.
	// This will only initialize a single RAM bank.
	unsigned int * LoadAddr, *ExeAddr, *EndAddr, SectionLen;

    // Copy the data segment from flash to SRAM.
	LoadAddr = &_etext;
	ExeAddr = &_data;
	EndAddr = &_edata;
	SectionLen = (void*)EndAddr - (void*)ExeAddr;
	data_init((unsigned int)LoadAddr, (unsigned int)ExeAddr, SectionLen);
	// Zero fill the bss segment
	ExeAddr = &_bss;
	EndAddr = &_ebss;
	SectionLen = (void*)EndAddr - (void*)ExeAddr;
	bss_init ((unsigned int)ExeAddr, SectionLen);
#endif


#if defined (__VFP_FP__) && !defined (__SOFTFP__)
/*
 * Code to enable the Cortex-M4 FPU only included
 * if appropriate build options have been selected.
 * Code taken from Section 7.1, Cortex-M4 TRM (DDI0439C)
 */
//	asm(".syntax unified");
	  // CPACR is located at address 0xE000ED88
	asm("LDR.W R0, =0xE000ED88");
	  // Read CPACR
	asm("LDR R1, [R0]");
	  // Set bits 20-23 to enable CP10 and CP11 coprocessors
	asm(" ORR R1, R1, #(0xF << 20)");
	  // Write back the modified value to the CPACR
	asm("STR R1, [R0]");
//	asm(".syntax divided");
#endif // (__VFP_FP__) && !(__SOFTFP__)



#ifdef __USE_CMSIS
	SystemInit();
#endif

#if defined (__cplusplus)
	//
	// Call C++ library initialisation
	//
	__libc_init_array();
#endif

#if defined (__REDLIB__)
	// Call the Redlib library, which in turn calls main()
	__main() ;
#else
	main();
#endif

	//
	// main() shouldn't return, but if it does, we'll just enter an infinite loop
	//
	while (1) {
		;
	}
}

//*****************************************************************************
// Default exception handlers. Override the ones here by defining your own
// handler routines in your application code.
//*****************************************************************************
__attribute__ ((section(".after_vectors")))
void NMI_Handler(void)
{
    while(1)
    {
    }
}
__attribute__ ((section(".after_vectors")))
void HardFault_Handler(void)
{
    while(1)
    {
    }
}
__attribute__ ((section(".after_vectors")))
void MemManage_Handler(void)
{
    while(1)
    {
    }
}
__attribute__ ((section(".after_vectors")))
void BusFault_Handler(void)
{
    while(1)
    {
    }
}
__attribute__ ((section(".after_vectors")))
void UsageFault_Handler(void)
{
    while(1)
    {
    }
}
__attribute__ ((section(".after_vectors")))
void SVC_Handler(void)
{
    while(1)
    {
    }
}
__attribute__ ((section(".after_vectors")))
void DebugMon_Handler(void)
{
    while(1)
    {
    }
}
__attribute__ ((section(".after_vectors")))
void PendSV_Handler(void)
{
    while(1)
    {
    }
}
__attribute__ ((section(".after_vectors")))
void SysTick_Handler(void)
{
    while(1)
    {
    }
}

//*****************************************************************************
//
// Processor ends up here if an unexpected interrupt occurs or a specific
// handler is not present in the application code.
//
//*****************************************************************************
__attribute__ ((section(".after_vectors")))
void IntDefaultHandler(void)
{
    while(1)
    {
    }
}
