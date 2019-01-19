#include <Derivative.h>
#include "SysTick.h"
#include "Printf.h"

#define DEBUG_UART          USART1
#define DEBUG_UART_BAUD     115200

#define LED_PORT            GPIOE
#define LED_PIN             GPIO_Pin_9

void Led_Init(GPIO_TypeDef *LedPortRegister, uint16_t LedPortBit)
{
    assert_param(IS_GPIO_ALL_PERIPH(LedPortRegister));
    assert_param(IS_GPIO_PIN(LedPortBit));
    
    /* Enable Clock on selected port */
    if( LedPortRegister == GPIOA )
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    else if( LedPortRegister == GPIOB )
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    else if( LedPortRegister == GPIOC )
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    else if( LedPortRegister == GPIOD )
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    else if( LedPortRegister == GPIOE )
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    else if( LedPortRegister == GPIOF )
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    else if( LedPortRegister == GPIOG )
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
    /* GPIO Pin configuration */
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.GPIO_Pin = LedPortBit;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(LedPortRegister, &GPIO_InitStruct);
}

int main()
{
    SysTick_Init(1000);
    Led_Init(LED_PORT, LED_PIN);
    
    GPIO_InitTypeDef GPIO_InitStructure;
    /* Enable GPIOC and GPIOE clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    /* Configure pins as AF pushpull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    Printf_Init(DEBUG_UART, DEBUG_UART_BAUD);
    uint32_t PrevMillis = 0;
    while( true )
    {
        if( g_SysTick_CurrentMillis - PrevMillis >= 0 )    /* is 1ms elapsed */
        {
            PrevMillis = g_SysTick_CurrentMillis;
            uint32_t start_task_millis, end_task_millis;
            start_task_millis = g_SysTick_CurrentMillis;
            {
                if( USART_GetFlagStatus(DEBUG_UART, USART_FLAG_RXNE) == SET )
                {
                    GPIO_WriteBit(LED_PORT, LED_PIN, Bit_SET);
                    
                    uint16_t RecvByte = USART_ReceiveData(DEBUG_UART);
                    USART_ClearFlag(DEBUG_UART, USART_FLAG_RXNE);
                    /* Send back echo */
                    printf("0x%02x ", RecvByte);
    
                    GPIO_WriteBit(LED_PORT, LED_PIN, Bit_RESET);
                }
            }
            end_task_millis = g_SysTick_CurrentMillis;
            
        }
    }/*while*/
}/*Main*/