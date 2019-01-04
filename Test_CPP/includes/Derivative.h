/**
 * All drivers shall be included through this file!
 */

#ifndef _DERIVATIVE_H_
#define _DERIVATIVE_H_


#ifdef  USE_FULL_ASSERT
	#include "stm32_assert.h"
#else
	#define assert_param(expr) ((void)0U)
#endif

#include "misc.h"
#include "ISR.h"

#if defined(stm32f3)
	/* System files */
	#include <stm32f3xx.h>
	/* Low-Layer Drivers */
	#include <stm32f3xx_ll_gpio.h>
	#include <stm32f3xx_ll_bus.h>

#elif defined(stm32f1)
	#include "stm32f10x.h"
	#include "system_stm32f10x.h"
	/* Reset and Clock Controller driver */
	#include <stm32f10x_rcc.h>
	/* General Purpose Input/Output Driver */
	#include "stm32f10x_gpio.h"
	
	
#else
	#error "No target family specified!"
#endif/*Target family check*/


/* Current SysTick */
volatile uint32_t SysTick_CurrentTicks;
void SysTick_Init()
{
	/* Configure SysTick */
	RCC_ClocksTypeDef RCC_Clocks;
	RCC_GetClocksFreq (&RCC_Clocks);
	(void) SysTick_Config (RCC_Clocks.HCLK_Frequency / 1000);	/* Reload every 1ms */
}

#endif/*_DERIVATIVE_H_ */