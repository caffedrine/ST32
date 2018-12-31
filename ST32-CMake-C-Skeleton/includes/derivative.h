#ifndef _DERIVATIVE_H_
#define _DERIVATIVE_H_

/* Compile time message */
#define STRING2(x) #x
#define STRING(x) STRING2(x)
// #pragma message(STRING(Target family: FAMILY))

/* Convert preprocessor to string */
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define AT __FILE__ ":" TOSTRING(__LINE__)

#ifdef  USE_FULL_ASSERT
	#include "stm32_assert.h"
#else
	#define assert_param(expr) ((void)0U)
#endif

#if defined(stm32f3)
	/* System files */
	#include <stm32f3xx.h>
	/* Low-Layer Drivers */
	#include <stm32f3xx_ll_gpio.h>
	#include <stm32f3xx_ll_bus.h>

#elif defined(stm32f1)
/* System files */
	#include <stm32f1xx.h>
	/* Low-Layer Drivers */
	#include <stm32f1xx_ll_gpio.h>
	#include <stm32f1xx_ll_bus.h>
#else
	#error "No target family specified!"
#endif	/* Target family check */

#endif /*_DERIVATIVE_H_ */