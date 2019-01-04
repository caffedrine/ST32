//
// Created by curiosul on 1/3/19.
//

#ifndef DRIVERS_LEDBASE_H
#define DRIVERS_LEDBASE_H

#include <Derivative.h>
#include "IDriverTimed.h"

/*	 _     _____ ____     ____    _    ____  _____
	| |   | ____|  _ \   | __ )  / \  / ___|| ____|
	| |   |  _| | | | |  |  _ \ / _ \ \___ \|  _|
	| |___| |___| |_| |  | |_) / ___ \ ___) | |___
	|_____|_____|____/   |____/_/   \_\____/|_____|
*/
class Led : public virtual IDriverTimed
{
	enum class LedWorkMode
	{
		NORMAL, BLINK
	};
	
public:
	Led(GPIO_TypeDef *LedPortRegister, uint16_t LedPortBit) : _PortRegister(LedPortRegister), _PortBit(LedPortBit)
	{
		assert_param( IS_GPIO_ALL_PERIPH(_PortRegister));
		assert_param( IS_GPIO_PIN(_PortBit) );
		
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
	}
	
	void Blink()
	{
		this->mode = LedWorkMode::BLINK;
	}
	
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
