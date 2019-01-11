//
// Created by curiosul on 1/4/19.
//
#ifndef _PUSHBUTTON_H
#define _PUSHBUTTON_H

#include <Derivative.h>
#include "IDriverTimed.h"

#define Vfb_GetMillis()    SysTick_CurrentTicks

enum class PushButtonState
{
	DOWN = 0,
	UP = 1
};

class PushButton : public virtual IDriverTimed
{
	typedef void (*StateChangedCbFunc_t)(PushButtonState);

public:
	PushButtonState PreviousState = PushButtonState::UP, CurrentState = PushButtonState::UP;
	
	PushButton(GPIO_TypeDef *LedPortRegister, uint16_t LedPortBit) : _PortRegister(LedPortRegister), _PortBit(LedPortBit)
	{
		this->Init();
	}
	
	PushButton(GPIO_TypeDef *LedPortRegister, uint16_t LedPortBit, uint32_t DebounceTimeMillis) : _PortRegister(LedPortRegister), _PortBit(LedPortBit), _DebounceMillis(DebounceTimeMillis)
	{
		this->Init();
	}
	
	~PushButton()
	{
		GPIO_DeInit(this->_PortRegister);
	}
	
	void Init()
	{
		assert_param(IS_GPIO_ALL_PERIPH(_PortRegister));
		assert_param(IS_GPIO_PIN(_PortBit));
		
		/* Enable Clock on selected port */
		if( this->_PortRegister == GPIOA )
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		else if( this->_PortRegister == GPIOB )
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		else if( this->_PortRegister == GPIOC )
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
		else if( this->_PortRegister == GPIOD )
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
		else if( this->_PortRegister == GPIOE )
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
		else if( this->_PortRegister == GPIOF )
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
		else if( this->_PortRegister == GPIOG )
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);
		
		/* GPIO Pin configuration */
		GPIO_InitTypeDef GPIO_InitStruct = {0};
		GPIO_InitStruct.GPIO_Pin = _PortBit;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
		GPIO_Init(_PortRegister, &GPIO_InitStruct);
	}
	
	PushButtonState ReadState()
	{
		if( GPIO_ReadInputDataBit(this->_PortRegister, this->_PortBit) )
		{
			return PushButtonState::DOWN;
		}
		else
		{
			return PushButtonState::UP;
		}
	}
	
	void SetCallback(StateChangedCbFunc_t c)
	{
		this->StateChangedCallback = c;
	}
	
	void Tick() override
	{
		CurrentState = this->ReadState();
		if( CurrentState != PreviousState )
		{
			if( Vfb_GetMillis() - _DebounceTimer >= _DebounceMillis )
			{
				OnStateChanged(this->CurrentState);
				PreviousState = this->CurrentState;
				
				_DebounceTimer = Vfb_GetMillis();
			}
		}
		else
		{
			_DebounceTimer = Vfb_GetMillis();
		}
	}

protected:
	virtual void OnStateChanged(PushButtonState NewState)
	{
		if( this->StateChangedCallback != nullptr )
			this->StateChangedCallback(NewState);
	}

private:
	GPIO_TypeDef *_PortRegister;
	uint16_t _PortBit;
	uint32_t _DebounceMillis = 0;
	uint32_t _DebounceTimer = 0;
	
	StateChangedCbFunc_t StateChangedCallback = nullptr;
};/*Class */

#endif //SKELETONCPP_PUSHBUTTON_H
