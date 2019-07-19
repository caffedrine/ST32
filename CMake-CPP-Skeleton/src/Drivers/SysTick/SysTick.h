//
// Created by curiosul on 05.01.19.
//

#ifndef _SYSTICK_H
#define _SYSTICK_H

#include <Derivative.h>

/* Store tickcount globally */
extern volatile uint64_t g_SysTick_CurrentTicks;

void SysTick_Init(uint64_t ReloadMicros);

/** MACROS **/
#define Vfb_GetMillis()    g_SysTick_CurrentTicks

#endif //_SYSTICK_H
