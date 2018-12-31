#include "derivative.h"

class PushButton
{
	enum PushButtonState
	{
		DOWN = 0,
		UP = 1
	};
	
public:
	PushButton(GPIO_TypeDef *LedPortRegister, uint32_t LedPortBit) : _PortRegister(LedPortRegister), _PortBit(LedPortBit)
	{
	}
	
	PushButtonState ReadState()
	{
		return PushButtonState::DOWN;
	}
	
	void Tick()
	{
	
	}
	
protected:
	/// TODO: Implement
	virtual void OnStateChanged(PushButtonState NewState) {}
private:
	GPIO_TypeDef *_PortRegister;
	uint32_t _PortBit;
};

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
		
		/* Led Off by default */
		this->Off();
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
	Led LedBlue(GPIOE, LL_GPIO_PIN_8);
	Led LedRed(GPIOE, LL_GPIO_PIN_9);
	Led LedOrange(GPIOE, LL_GPIO_PIN_10);
	Led LedGreen (GPIOE, LL_GPIO_PIN_11);
	
	Led LedBlue2(GPIOE, LL_GPIO_PIN_12);
	Led LedRed2(GPIOE, LL_GPIO_PIN_13);
	Led LedOrange2(GPIOE, LL_GPIO_PIN_14);
	Led LedGreen2(GPIOE, LL_GPIO_PIN_15);
	
	LedRed.On();
	LedBlue.On();
	LedOrange.On();
	LedGreen.On();
	LedRed2.Off();
	LedBlue2.Off();
	LedOrange2.Off();
	LedGreen2.Off();
	
	while(true)
	{
		LedRed.Toggle();
		LedBlue.Toggle();
		LedOrange.Toggle();
		LedGreen.Toggle();
		LedRed2.Toggle();
		LedBlue2.Toggle();
		LedOrange2.Toggle();
		LedGreen2.Toggle();
		
		for(int i = 0; i<= 100000; i++);
	}
}