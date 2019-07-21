#include <Derivative.h>
#include "SysTick.h"

#define LED_PORT    GPIOD
#define LED_PIN     GPIO_Pin_14

void Led_Init(GPIO_TypeDef *LedPortRegister, uint16_t LedPortBit)
{
    assert_param(IS_GPIO_ALL_PERIPH(LedPortRegister));
    assert_param(IS_GPIO_PIN(LedPortBit));
    
    /* Enable Clock on selected port */
    if( LedPortRegister == GPIOA )
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    else if( LedPortRegister == GPIOB )
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    else if( LedPortRegister == GPIOC )
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
    else if( LedPortRegister == GPIOD )
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    else if( LedPortRegister == GPIOE )
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
    else if( LedPortRegister == GPIOF )
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
    else if( LedPortRegister == GPIOG )
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
    
    /* GPIO Pin configuration */
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.GPIO_Pin = LedPortBit;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LedPortRegister, &GPIO_InitStruct);
}

void Task1Ms()
{
    static uint32_t PrevMillis = 0;
    if( g_SysTick_CurrentTicks - PrevMillis >= 1000 )    /* is 1ms elapsed */
    {
        PrevMillis = g_SysTick_CurrentTicks;
        GPIO_WriteBit(LED_PORT, LED_PIN, (BitAction) !GPIO_ReadOutputDataBit(LED_PORT, LED_PIN));
    }
}

int main()
{
    /* Configure system clock */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);
    /* Config SysTick */
    SysTick_Init(1000);
    
    Led_Init(LED_PORT, LED_PIN);
    
    uint64_t StartTaskMillis, EndTaskMillis, PrevMillis = 0;
    while( true )
    {
        if( g_SysTick_CurrentTicks - PrevMillis >= 1 )    /* is 1ms elapsed */
        {
            PrevMillis = g_SysTick_CurrentTicks;
            StartTaskMillis = g_SysTick_CurrentTicks;
            {
                Task1Ms();
            }
            EndTaskMillis = g_SysTick_CurrentTicks;
            
            /* If task took more than 1ms */
            if( (EndTaskMillis - StartTaskMillis) > 1 )
            {
                while( true )
                {
                    ;
                }
            }
        }
    }/*while*/
}/*Main*/