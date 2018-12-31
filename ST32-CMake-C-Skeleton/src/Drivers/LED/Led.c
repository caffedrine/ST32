//
// Created by curiosul on 12/31/18.
//

#include "Led.h"





void LED_Init(led_config_t *ConfigPtr)
{
	/* GPIO Ports Clock Enable */
#ifdef stm32f3
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOE);
#elif defined(stm32f1)
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOE);
#endif
	
	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = ConfigPtr->PortBit;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_DOWN;
	LL_GPIO_Init(ConfigPtr->PortRegister, &GPIO_InitStruct);
}
