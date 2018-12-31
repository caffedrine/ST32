#include "derivative.h"

class Led
{
public:
	Led(GPIO_TypeDef *LedPortRegister, uint32_t LedPortBit) : _PortRegister(LedPortRegister), _PortBit(LedPortBit)
	{
		/* GPIO Ports Clock Enable */
#ifdef stm32f3
		LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOE);
#elif defined(stm32f1)
		LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOE);
#endif

		LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
		GPIO_InitStruct.Pin = _PortBit;
		GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
		GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
		GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
		GPIO_InitStruct.Pull = LL_GPIO_PULL_DOWN;
		LL_GPIO_Init(_PortRegister, &GPIO_InitStruct);
	}

	void On()
	{
		LL_GPIO_ResetOutputPin(this->_PortRegister, this->_PortBit);
	}

	void Off()
	{
		LL_GPIO_SetOutputPin(this->_PortRegister, this->_PortBit);
	}

	void Toggle()
	{
		LL_GPIO_TogglePin(this->_PortRegister, this->_PortBit);
	}

private:
	GPIO_TypeDef *_PortRegister;
	uint32_t _PortBit;
};

int main()
{
	Led led(GPIOE, LL_GPIO_PIN_9);
	
	while(true)
	{
		led.Toggle();
		for(int i = 0; i<= 100000; i++);
	}
}