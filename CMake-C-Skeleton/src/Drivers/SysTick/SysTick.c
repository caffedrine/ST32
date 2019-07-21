//
// Created by curiosul on 05.01.19.
//

#include "SysTick.h"

/* Global Current SysTick */
volatile uint64_t g_SysTick_CurrentTicks = 0;
/* Local var */
bool SysTick_IsInitialized = false;

void SysTick_Init(uint32_t ReloadMicros)
{
    if(SysTick_IsInitialized == true)
    {
        return;
    }

    /* Init counter */
    g_SysTick_CurrentTicks = 0;
    
	/* Configure SysTick */
    RCC_ClocksTypeDef RCC_Clocks;
    RCC_GetClocksFreq (&RCC_Clocks);
    assert_param(SysTick_Config (RCC_Clocks.HCLK_Frequency / ReloadMicros) );
    SysTick_IsInitialized = true;
}