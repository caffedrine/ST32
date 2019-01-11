//
// Created by curiosul on 05.01.19.
//

#include "SysTick.h"

void SysTick_Init(uint32_t ReloadMicros)
{
	/* Configure SysTick */
	RCC_ClocksTypeDef RCC_Clocks;
	RCC_GetClocksFreq (&RCC_Clocks);
	(void) SysTick_Config (RCC_Clocks.HCLK_Frequency / ReloadMicros);	/* Reload every 1ms */
}