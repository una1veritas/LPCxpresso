/*
===============================================================================
 Name        : main.c
 Author      : 
 Version     :
 Copyright   : Copyright (C) 
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC18xx.h"
#endif

#include <cr_section_macros.h>
#include <NXP/crp.h>

// Variable to store CRP value in. Will be placed automatically
// by the linker when "Enable Code Read Protect" selected.
// See crp.h header for more information
__CRP const unsigned int CRP_WORD = CRP_NO_CRP ;

#include "lpc18xx_cgu.h"
#include "lpc18xx_sct.h"
#include "lpc18xx_scu.h"
#include "lpc18xx_gpio.h"
#include "sct_fsm.h"
#include "lpc18xx_libcfg_default.h"

/* Example group ----------------------------------------------------------- */
/** @defgroup Sct_SimpleMatch	Sct_SimpleMatch
 * @ingroup SCT_Examples
 * @{
 */

/************************** PRIVATE DEFINITIONS **********************/

/*-------------------------MAIN FUNCTION------------------------------*/
/*********************************************************************//**
 * @brief		Main SCT program body
 * @param[in]	None
 * @return 		int
 **********************************************************************/
int c_entry(void)
{
	SystemInit();
	CGU_Init();

	/* Pin configuration for SCT */
#if 0
	scu_pinmux (4, 2, MD_PUP, FUNC1);   /* P4_2:  SCTOUT0_0 */
	scu_pinmux (4, 1, MD_PLN, FUNC1);   /* P4_1:  SCTOUT0_1 */
	scu_pinmux (4, 4, MD_PLN, FUNC1);   /* P4_4:  SCTOUT0_2 */
	scu_pinmux (4, 3, MD_PLN, FUNC1);   /* P4_3:  SCTOUT0_3 */
#endif
	scu_pinmux (2, 12, MD_PLN, FUNC1);   /* P2_12:  SCTOUT0_4 */
	scu_pinmux (2, 11, MD_PLN, FUNC1);   /* P2_11:  SCTOUT0_5 */
	/* Global configuration of the SCT */
	SCT_Config(SCT_CONFIG_16BIT_COUNTER);
	SCT_ControlSet(SCT_CTRL_CLRCTR_L|SCT_CTRL_HALT_L|SCT_CTRL_PRE_L(100-1)
					|SCT_CTRL_HALT_H|SCT_CTRL_CLRCTR_H|SCT_CTRL_PRE_H(100-1),
					ENABLE);

	/* Now use the FSM code to configure the state machine */
	sct_fsm_init();

	/* Conflict resolution: CLR override for all */
#if 0
	SCT_ConflictResolutionSet(0,SCT_RES_CLEAR_OUTPUT);
	SCT_ConflictResolutionSet(1,SCT_RES_CLEAR_OUTPUT);
	SCT_ConflictResolutionSet(2,SCT_RES_CLEAR_OUTPUT);
	SCT_ConflictResolutionSet(3,SCT_RES_CLEAR_OUTPUT);
#endif
	SCT_ConflictResolutionSet(4,SCT_RES_CLEAR_OUTPUT);
	SCT_ConflictResolutionSet(5,SCT_RES_CLEAR_OUTPUT);
	/* Start the SCT */
	SCT_ControlSet(SCT_CTRL_HALT_L,DISABLE);

	// run cpu in an endless loop
	while (1)
	{
	}
}

/* With ARM and GHS toolsets, the entry point is main() - this will
   allow the linker to generate wrapper code to setup stacks, allocate
   heap area, and initialize and copy code and data segments. For GNU
   toolsets, the entry point is through __start() in the crt0_gnu.asm
   file, and that startup code will setup stacks and data */
int main(void)
{
    return c_entry();
}

#ifdef  DEBUG
/*******************************************************************************
* @brief		Reports the name of the source file and the source line number
* 				where the CHECK_PARAM error has occurred.
* @param[in]	file Pointer to the source file name
* @param[in]    line assert_param error line source number
* @return		None
*******************************************************************************/
void check_failed(uint8_t *file, uint32_t line)
{
	/* User can add his own implementation to report the file name and line number,
	 ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

	/* Infinite loop */
	while(1);
}
#endif
