//
// Created by curiosul on 1/17/19.
//

#ifndef SKELETONC_PRINTF_H
#define SKELETONC_PRINTF_H

#include <Derivative.h>

void Printf_Init(USART_TypeDef *UART_Channel, uint32_t BaudRate);

signed int Printf(const char *pFormat, ...);
int printf(const char *pFormat, ...);

#endif //SKELETONC_PRINTF_H
