/**
 * All drivers shall be included through this file!
 */

#ifndef _DERIVATIVE_H_
#define _DERIVATIVE_H_

#include <stdbool.h>
#include <stdint.h>

#ifdef  USE_FULL_ASSERT
    #include "stm32_assert.h"
#else
    #define assert_param(expr) ((void)0U)
#endif

/* Common cross-compile headers */
#include "misc.h"
#include "ISR.h"

#if defined(stm32f3)
    #include "stm32f30x.h"
    #include "system_stm32f30x.h"
/* Reset and Clock Controller driver */
    #include <stm32f30x_rcc.h>
/* General Purpose Input/Output Driver */
    #include "stm32f30x_gpio.h"
    #include "stm32f30x_usart.h"

#elif defined(stm32f1)
    #include "stm32f10x.h"
    #include "system_stm32f10x.h"
/* Reset and Clock Controller driver */
    #include <stm32f10x_rcc.h>
/* General Purpose Input/Output Driver */
    #include "stm32f10x_gpio.h"
    #include "stm32f10x_usart.h"

#else
    #error "No target family specified!"
#endif/*Target family check*/

/* Current SysTick */
volatile uint32_t g_SysTick_CurrentMillis;

#endif/*_DERIVATIVE_H_ */
