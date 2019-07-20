//
// Created by curiosul on 05.01.19.
//

#ifndef _SYSTICK_H_
#define _SYSTICK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <Derivative.h>

/* Store tickcount globally */
extern volatile uint64_t g_SysTick_CurrentTicks;

extern void SysTick_Init(uint64_t ReloadMicros);

/** MACROS **/
#define Vfb_GetMillis()    g_SysTick_CurrentTicks

#ifdef __cplusplus
}
#endif

#endif //_SYSTICK_H_
