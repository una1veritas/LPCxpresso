/*****************************************************************************
 *   adctest.c:  main C entry file for NXP LPC13xx Family Microprocessors
 *
 *   Copyright(C) 2008, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2008.07.19  ver 1.00    Preliminary version, first Release
 *
******************************************************************************/
#include "LPC13xx.h"                        /* LPC13xx definitions */
#include "adc.h"
#ifdef ADC_DEBUG
#include "stdio.h"
#endif

extern volatile uint32_t ADCValue[ADC_NUM];
extern volatile uint32_t ADCIntDone;

#ifdef ADC_DEBUG
uint8_t ConvertDigital ( uint8_t digital )
{
  uint8_t ascii_char;

  if ( (digital >= 0) && (digital <= 9) )
  {
	ascii_char = digital + 0x30;	/* 0~9 */
  }
  else
  {
	ascii_char = digital - 0x0A;
	ascii_char += 0x41;				/* A~F */
  }
  return ( ascii_char );
}
#endif

#ifdef ADC_DEBUG
#define BAR_OUTPUT_LENGTH 60
#define ADC_COUNT_MAX 1023
#define CHANNEL_WIDTH 2
#define VOLT_WIDTH 4
#define MAX_BAR_LENGTH (BAR_OUTPUT_LENGTH-CHANNEL_WIDTH-1-VOLT_WIDTH-1-2)
#define SUPPLY_VOLTAGE 3.30

void FillString(char *s, char c, uint32_t len)
{
	if(!len)
		goto empty;
	while(--len)
		*s++ = c;
empty:
	*s = 0;
}
void ADCBar(int32_t Channel, uint32_t Counts)
{
	uint32_t ValueBarLen = Counts*MAX_BAR_LENGTH/ADC_COUNT_MAX;
	char ValueBarBuf[BAR_OUTPUT_LENGTH+1];
	float ValueVolts = Counts*SUPPLY_VOLTAGE/ADC_COUNT_MAX;

	if(Channel == 0)
	{
		FillString(ValueBarBuf, '-', MAX_BAR_LENGTH+2);
		printf("%-9s%s\n", "", ValueBarBuf);
	}

	if(Channel >= 0)
	{
		FillString(ValueBarBuf, '#', ValueBarLen);
		printf("%2d %d.%02dV |%s%-*s|\n", Channel,
				(int)ValueVolts, (int)((ValueVolts-(int)ValueVolts)*100),
				ValueBarBuf, MAX_BAR_LENGTH-ValueBarLen, "");
	}
	else
	{
		FillString(ValueBarBuf, '-', MAX_BAR_LENGTH+2);
		printf("%-9s%s\n", "", ValueBarBuf);
	}
}
#endif

/******************************************************************************
**   Main Function  main()
******************************************************************************/
int main (void)
{
	 /* Basic chip initialization is taken care of in SystemInit() called
	   * from the startup code. SystemInit() and chip settings are defined
	   * in the CMSIS system_<part family>.c file.
	   */

  uint32_t i;

  /* Initialize ADC  */
  ADCInit( ADC_CLK );

#if BURST_MODE				/* Interrupt driven only */
  ADCBurstRead();
  while ( !ADCIntDone );
  ADCIntDone = 0;
#else
  for ( i = 0; i < ADC_NUM; i++ )
  {
#if ADC_INTERRUPT_FLAG				/* Interrupt driven */
	ADCRead( i );
	while ( !ADCIntDone );
	ADCIntDone = 0;
#else
	ADCValue[i] = ADCRead( i );	/* Polling */
#endif
#ifdef ADC_DEBUG
	// Note: a single printf call can add 10k to code size
	ADCBar(i, ADCValue[i]);
//	printf("ADC[%d] = %05d\r\n", i, ADCValue[i]);
#endif
  }
#ifdef ADC_DEBUG
  ADCBar(-1, 0);
#endif
#endif
  while(1);
}

/******************************************************************************
**                            End Of File
******************************************************************************/

