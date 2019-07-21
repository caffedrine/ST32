//
// Created by curiosul on 05.01.19.
//

#ifndef _SYSTICK_H_
#define _SYSTICK_H_

#include <Derivative.h>

/* Current SysTick */
extern volatile uint64_t g_SysTick_CurrentTicks;

void SysTick_Init(uint32_t ReloadMicros);

/** MACROS **/
#define Vfb_GetMillis()    g_SysTick_CurrentTicks
#endif //_SYSTICK_H
