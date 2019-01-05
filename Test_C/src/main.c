#include "derivative.h"

#define PIN_PORT	GPIOE
#define PIN_BIT		LL_GPIO_PIN_9

void InitPin()
{
	/* GPIO Ports Clock Enable */
#ifdef stm32f3
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOE);
#elif defined(stm32f1)
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOE);
#endif
	
	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = PIN_BIT;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_DOWN;
	LL_GPIO_Init(PIN_PORT, &GPIO_InitStruct);
}

int main()
{
	InitPin();
	
	while(1)
	{
		LL_GPIO_TogglePin(PIN_PORT, LL_GPIO_PIN_9);
		for(int i = 0; i<= 200000; i++);
	}
	
	return 0;
}