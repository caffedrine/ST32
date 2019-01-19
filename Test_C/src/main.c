#include <Derivative.h>
#include "SysTick.h"
#include "Printf.h"

#define DEBUG_UART		USART1
#define DEBUG_UART_BAUD	115200

#define LED_PORT	GPIOE
#define LED_PIN		GPIO_Pin_9

void Led_Init(GPIO_TypeDef *LedPortRegister, uint16_t LedPortBit)
{
	assert_param( IS_GPIO_ALL_PERIPH(LedPortRegister));
	assert_param( IS_GPIO_PIN(LedPortBit) );
	
	/* Enable Clock on selected port */
	if( LedPortRegister == GPIOA )
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	else if( LedPortRegister == GPIOB )
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	else if( LedPortRegister == GPIOC )
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
	else if( LedPortRegister == GPIOD )
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);
	else if( LedPortRegister == GPIOE )
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);
	else if( LedPortRegister == GPIOF )
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);
	else if( LedPortRegister == GPIOG )
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOG, ENABLE);
	
	/* GPIO Pin configuration */
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.GPIO_Pin = LedPortBit;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(LedPortRegister, &GPIO_InitStruct);
}

int main()
{
	SysTick_Init(1000);
	Led_Init(LED_PORT, LED_PIN);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	/* Enable GPIOC and GPIOE clock */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA , ENABLE);
	/* Connect pin to Periph */
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_7);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_7);
	/* Configure pins as AF pushpull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	Printf_Init(DEBUG_UART, DEBUG_UART_BAUD);
	uint32_t PrevMillis = 0;
	while(true)
	{
		if( g_SysTick_CurrentMillis - PrevMillis >= 200 )	/* is 1ms elapsed */
		{
			PrevMillis = g_SysTick_CurrentMillis;
			uint32_t start_task_millis, end_task_millis;
			start_task_millis = g_SysTick_CurrentMillis;
			{
				GPIO_WriteBit(LED_PORT, LED_PIN, (BitAction) !GPIO_ReadOutputDataBit(LED_PORT, LED_PIN));
				{
					static int i = 0;
					printf("%d\r\n", i++);
				}
			}
			end_task_millis = g_SysTick_CurrentMillis;

			if( (end_task_millis - start_task_millis) > 1 )
			{
				while(true)
				{
					;
				}
			}
		}
	}/*while*/
}/*Main*/