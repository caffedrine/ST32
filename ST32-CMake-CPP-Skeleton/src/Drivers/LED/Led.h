//
// Created by curiosul on 1/3/19.
//

#ifndef DRIVERS_LEDBASE_H
#define DRIVERS_LEDBASE_H

#include "derivative.h"
#include "IDriverTimed.h"

/*	 _     _____ ____     ____    _    ____  _____
	| |   | ____|  _ \   | __ )  / \  / ___|| ____|
	| |   |  _| | | | |  |  _ \ / _ \ \___ \|  _|
	| |___| |___| |_| |  | |_) / ___ \ ___) | |___
	|_____|_____|____/   |____/_/   \_\____/|_____|
*/
class Led : IDriverTimed
{
	enum class LedWorkMode
	{
		NORMAL, BLINK
	};
	
public:
	Led(GPIO_TypeDef *LedPortRegister, uint16_t LedPortBit) : _PortRegister(LedPortRegister), _PortBit(LedPortBit)
	{
		/* Enable Clock on selected port */
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
		
		/* GPIO Pin configuration */
		GPIO_InitTypeDef GPIO_InitStruct = {0};
		GPIO_InitStruct.GPIO_Pin = _PortBit;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
		GPIO_Init(_PortRegister, &GPIO_InitStruct);
		
		/* Led Off by default */
		this->Off();
	}
	
	~Led()
	{
		GPIO_DeInit(this->_PortRegister);
	}
	
	void On()
	{
		GPIO_WriteBit(this->_PortRegister, this->_PortBit, Bit_SET);
		this->mode = LedWorkMode::NORMAL;
	}
	
	void Off()
	{
		GPIO_WriteBit(this->_PortRegister, this->_PortBit, Bit_RESET);
		this->mode = LedWorkMode::NORMAL;
	}
	
	void Toggle()
	{
		GPIO_WriteBit(this->_PortRegister, this->_PortBit, (BitAction) !GPIO_ReadOutputDataBit(this->_PortRegister, this->_PortBit));
		this->mode = LedWorkMode::NORMAL;
	}
	
	void Blink()
	{
		this->mode = LedWorkMode::BLINK;
	}

protected:
	void Tick() override
	{
		if(mode == LedWorkMode::BLINK)
		{
			this->Toggle();
			return;
		}
	}

private:
	GPIO_TypeDef *_PortRegister;
	uint16_t _PortBit;
	LedWorkMode mode = LedWorkMode::NORMAL;
};/* Class */

#endif //DRIVERS_LEDBASE_H
