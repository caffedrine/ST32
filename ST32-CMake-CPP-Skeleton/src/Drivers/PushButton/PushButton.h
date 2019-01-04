//
// Created by curiosul on 1/4/19.
//
#ifndef _PUSHBUTTON_H
#define _PUSHBUTTON_H

#include <Derivative.h>

class PushButton
{
	enum PushButtonState
	{
		DOWN = 0,
		UP = 1
	};

public:
	PushButtonState CurrentState;
	
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


#endif //SKELETONCPP_PUSHBUTTON_H
