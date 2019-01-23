//
// Created by curiosul on 1/17/19.
//

#ifndef _PRINTF_H_
#define _PRINTF_H_

#include <Derivative.h>

void Printf_Init(USART_TypeDef *UART_Channel, uint32_t BaudRate);

signed int Printf(const char *pFormat, ...);
int printf(const char *pFormat, ...);

#endif //_PRINTF_H_
