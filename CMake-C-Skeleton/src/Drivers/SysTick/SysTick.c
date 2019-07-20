//
// Created by curiosul on 05.01.19.
//

#include "SysTick.h"

/* Global Current SysTick */
volatile uint64_t g_SysTick_CurrentTicks = 0;
/* Local var */
bool SysTick_IsInitialized = false;

void SysTick_Init(uint64_t ReloadMicros)
{
    if(SysTick_IsInitialized == true)
    {
        return;
    }

    /* Init counter */
    g_SysTick_CurrentTicks = 0;

	/* Configure SysTick */
    assert_param(SysTick_Config (SystemCoreClock/ 3 /*??*/ / ReloadMicros) );
    SysTick_IsInitialized = true;
}