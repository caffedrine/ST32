//
// Created by curiosul on 1/17/19.
//

#include "TacoBus.h"

uint8_t GetFctCommand[10] = {0x5c, 0x00, 0xCC, 0x00, 0x0A, 0x00, 0xFF, 0x00, 0x00, 0x00};
uint8_t LowVoltageFctConfigACommand[14] = {0x5C, 0x00, 0xC6, 0x00, 0x0E, 0x00, 0xEE, 0x00, 0x00, 0x00, 0xFF, 0x02, 0x00, 0x00};
uint8_t LowVoltageFctConfigBCommand[14] = {0x5C, 0x00, 0xD3, 0x00, 0x0E, 0x00, 0xEE, 0x00, 0x00, 0x00, 0xFF, 0x02, 0x01, 0x00};

uint8_t TacoRxBuffer[40];
USART_TypeDef *pUART;

/* Private functions */
void ProcessTacoPacket();
uint8_t SendUartData(uint8_t *data, uint8_t len);
uint8_t ReceiveUartData(uint8_t *recv_buffer);

void TacoBus_Init()
{
    pUART = USART2;
    uint32_t BaudRate = 115200;
    
    /* Enable GPIOC and GPIOE clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    /* Configure pins as AF pushpull */
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    USART_InitTypeDef USART_InitStructure;
    USART_ClockInitTypeDef USART_ClockInitStructure;
    USART_InitStructure.USART_BaudRate = BaudRate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;
    USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;
    USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;
    USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;
    
    USART_Init(pUART, &USART_InitStructure);
    USART_ClockInit(pUART, &USART_ClockInitStructure);
    USART_Cmd(pUART, ENABLE);
}

uint8_t TacoBus_SendCommand(uint8_t *data, uint8_t len)
{
    for( int i = 0; i < 10; i++ )
    {
        uint8_t SendBytes = SendUartData(data, len);
        if( SendBytes <= 0 )
            continue;
        
        uint8_t RecvBytes = ReceiveUartData(TacoRxBuffer);
        if( RecvBytes > 0 )
            return RecvBytes;
    }
    return 0;
}

uint8_t TacoBus_GetFctInfo()
{
    uint8_t SendBytes = TacoBus_SendCommand(GetFctCommand, sizeof(GetFctCommand));
    if( SendBytes > 0 )
    {
        ProcessTacoPacket();
        return SendBytes;
    }
    return SendBytes;
}

uint8_t TacoBus_LowVoltageFctConfigA()
{
    uint8_t SendBytes = TacoBus_SendCommand(LowVoltageFctConfigACommand, sizeof(LowVoltageFctConfigACommand));
    return SendBytes;
}

uint8_t TacoBus_LowVoltageFctConfigB()
{
    uint8_t SendBytes = TacoBus_SendCommand(LowVoltageFctConfigBCommand, sizeof(LowVoltageFctConfigBCommand));
    return SendBytes;
}

void ProcessTacoPacket()
{
    FctInfo.FCT_cStatus = TacoRxBuffer[12];
    FctInfo.MAIN_cPumpStatus = TacoRxBuffer[13];
    FctInfo.sr_u16_GlobAlrm = (uint16_t) (TacoRxBuffer[14] << 8);
    FctInfo.sr_u16_GlobAlrm |= (uint16_t) (TacoRxBuffer[15]);
    FctInfo.sr_u16_RecAlrm = (uint16_t) (TacoRxBuffer[16] << 8);
    FctInfo.sr_u16_RecAlrm |= (uint16_t) (TacoRxBuffer[17]);
    FctInfo.ADC_sdwVrms = (uint16_t) (TacoRxBuffer[18] << 8);
    FctInfo.ADC_sdwVrms |= (uint16_t) (TacoRxBuffer[19]);
    FctInfo.sr_s16_ACurSam = (uint16_t) (TacoRxBuffer[20] << 8);
    FctInfo.sr_s16_ACurSam |= (uint16_t) (TacoRxBuffer[21]);
    FctInfo.sr_s16_BCurSam = (uint16_t) (TacoRxBuffer[22] << 8);
    FctInfo.sr_s16_BCurSam |= (uint16_t) (TacoRxBuffer[23]);
    FctInfo.RIFE_RifExt_wFlt = (uint16_t) (TacoRxBuffer[24] << 8);
    FctInfo.RIFE_RifExt_wFlt |= (uint16_t) (TacoRxBuffer[25]);
    FctInfo.iamf = TacoRxBuffer[26];
    FctInfo.ibmf = TacoRxBuffer[27];
    FctInfo.vbusf = TacoRxBuffer[28];
    FctInfo.mbus = TacoRxBuffer[29];
    FctInfo.ium_off = TacoRxBuffer[30];
    FctInfo.ivm_off = TacoRxBuffer[31];
    FctInfo.Debug_Power = TacoRxBuffer[32];
    FctInfo.Temp = TacoRxBuffer[33];
}

uint8_t SendUartData(uint8_t *data, uint8_t len)
{
    #ifdef DEBUG
    printf("[TACOBUS] SEND: ");
    #endif
    
    for( int i = 0; i < len; i++ )
    {
        uint16_t ch = data[i];
        
        /* Send data */
        USART_SendData(pUART, ch);
        /* Wait for data to be send */
        while( USART_GetFlagStatus(pUART, USART_FLAG_TC) == RESET );
        
        #ifdef DEBUG
        printf("%c", 'a');
        #endif
    }
    #ifdef DEBUG
    printf("\r\n");
    #endif
    
    return len;
}

uint8_t ReceiveUartData(uint8_t *recv_buffer)
{
    uint32_t TimeoutMs = 1000;
    uint32_t StartRecvMillis = g_SysTick_CurrentMillis;
    uint8_t i = 0;
    
    #ifdef DEBUG
    printf("[TACOBUS] RECV: ");
    #endif
    
    while( true )
    {
        if( USART_GetFlagStatus(pUART, USART_FLAG_RXNE) == SET )
        {
            recv_buffer[i] = (uint8_t) USART_ReceiveData(pUART);
            USART_ClearFlag(pUART, USART_FLAG_RXNE);
            
            #ifdef DEBUG
            printf("0x%02x ", recv_buffer[i]);
            #endif
            i++;
        }
        
        /* If timeout reached */
        if( (g_SysTick_CurrentMillis - StartRecvMillis) >= TimeoutMs )
        {
            USART_ClearFlag(pUART, USART_FLAG_RXNE);
            #ifdef DEBUG
            printf("TIMEOUT\r\n");
            #endif
            return i;
        }
        
        /* Buffer is full? */
        if( i >= (sizeof(TacoRxBuffer) - 1) )
        {
            USART_ClearFlag(pUART, USART_FLAG_RXNE);
            #ifdef DEBUG
            printf("BUFF FULL\r\n");
            #endif
            return i;
        }
    }
    return i;
}