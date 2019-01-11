#include <Derivative.h>
#include "SysTick.h"

#define LED_PORT	GPIOE
#define LED_PIN		GPIO_Pin_9

void Led_Init(GPIO_TypeDef *LedPortRegister, uint16_t LedPortBit)
{
	assert_param( IS_GPIO_ALL_PERIPH(LedPortRegister));
	assert_param( IS_GPIO_PIN(LedPortBit) );
	
	/* Enable Clock on selected port */
	if( LedPortRegister == GPIOA )
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	else if( LedPortRegister == GPIOB )
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	else if( LedPortRegister == GPIOC )
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	else if( LedPortRegister == GPIOD )
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	else if( LedPortRegister == GPIOE )
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
	else if( LedPortRegister == GPIOF )
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
	else if( LedPortRegister == GPIOG )
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);
	
	/* GPIO Pin configuration */
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.GPIO_Pin = LedPortBit;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(LedPortRegister, &GPIO_InitStruct);
}

int main()
{
	SysTick_Init(1000);
	Led_Init(LED_PORT, LED_PIN);
	
	uint32_t PrevMillis = 0;
	while(true)
	{
		if( g_SysTick_CurrentMillis - PrevMillis >= 1000 )	/* is 1ms elapsed */
		{
			PrevMillis = g_SysTick_CurrentMillis;
			uint32_t start_task_millis, end_task_millis;
			
			start_task_millis = g_SysTick_CurrentMillis;
			GPIO_WriteBit(LED_PORT, LED_PIN, (BitAction) !GPIO_ReadOutputDataBit(LED_PORT, LED_PIN));
			end_task_millis = g_SysTick_CurrentMillis;

			if( (end_task_millis - start_task_millis) > 1 )
			{
				while(true)
				{
					;
				}
			}
		}
	}
}