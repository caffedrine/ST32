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
/* USART Driver */
    #include "stm32f30x_usart.h"

#elif defined(stm32f1)
    #include "stm32f10x.h"
    #include "system_stm32f10x.h"
/* Reset and Clock Controller driver */
    #include <stm32f10x_rcc.h>
/* General Purpose Input/Output Driver */
    #include "stm32f10x_gpio.h"

#elif defined(stm32f4)
    #include "stm32f4xx.h"
    #include "system_stm32f4xx.h"
/* Reset and Clock Controller driver */
    #include <stm32f4xx_rcc.h>
/* General Purpose Input/Output Driver */
    #include "stm32f4xx_gpio.h"
/* USART driver */
    #include "stm32f4xx_usart.h"

#else
    #error "No target family specified!"

#endif/*Target family check*/

#endif/*_DERIVATIVE_H_ */
