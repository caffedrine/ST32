//
// Created by curiosul on 12/31/18.
//

#ifndef FIXTURETACO_LED_H
#define FIXTURETACO_LED_H

#include <stdbool.h>
#include <stddef.h>

#include "derivative.h"


typedef struct led_config
{
	GPIO_TypeDef *PortRegister;
	uint32_t PortBit;
	
}led_config_t;

/* */
typedef struct led_access_interface
{
	void (*Init)(led_config_t *ConfigPtr);
	void (*On)(led_config_t *ConfigPtr);
	void (*Off)(led_config_t *ConfigPtr);
	void (*Toggle)(led_config_t *ConfigPtr);
}led_t;

/* */
void LED_Init(led_config_t *ConfigPtr);
void LED_On(led_config_t *ConfigPtr);
void LED_Off(led_config_t *ConfigPtr);
void LED_Toggle(led_config_t *ConfigPtr);

void InitLed(led_t *instance)
{
	instance->Init = &LED_Init;
	instance->On = &LED_On;
	instance->Off = &LED_Off;
	instance->Toggle = &LED_Toggle;
};


//led_t test_led =
//		{
//			.Init =
//		};

#endif //FIXTURETACO_LED_H
