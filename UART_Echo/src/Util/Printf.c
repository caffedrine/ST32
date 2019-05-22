//
// Created by curiosul on 1/17/19.
//

#include <limits.h>
#include <stdarg.h>
#include <stdio.h>

#include "Printf.h"

static USART_TypeDef *pUART = NULL;

void Printf_Init(USART_TypeDef *UART_Channel, uint32_t BaudRate)
{
    pUART = UART_Channel;
    
    if( pUART == USART1 )
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    else if( pUART == USART2 )
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
    else if( pUART == USART3 )
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
    else if( pUART == UART4 )
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
    else if( pUART == UART5 )
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);
    
    USART_InitTypeDef USART_InitStructure;
    
    USART_DeInit(pUART);
    USART_InitStructure.USART_BaudRate = BaudRate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(pUART, &USART_InitStructure);
    
    if( pUART == USART1 || pUART == USART2 || pUART == USART3 )
    {
        USART_ClockInitTypeDef USART_ClockInitStructure;
        USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;
        USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;
        USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;
        USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;
        USART_ClockInit(pUART, &USART_ClockInitStructure);
    }
    
    USART_Cmd(pUART, ENABLE);

//	GPIO_InitTypeDef GPIO_InitStructure;
//	/* Enable GPIOC and GPIOE clock */
//	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA , ENABLE);
//	/* Connect pin to Periph */
//	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_7);
//	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_7);
//	/* Configure pins as AF pushpull */
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    printf("\r\n\r\n");
}

/**
 * @brief  Transmit a char, if you want to use printf(),
 *         you need implement this function
 *
 * @param  pStr	Storage string.
 * @param  c    Character to write.
 */
void PrintChar(char c)
{
    if( pUART != NULL )
    {
        USART_SendData(pUART, c);
        while( USART_GetFlagStatus(pUART, USART_FLAG_TC) == RESET );
    }
}

/** Maximum string size allowed (in bytes). */
#define MAX_STRING_SIZE         255


/** Required for proper compilation. */
//struct _reent r = {0, (FILE *) 0, (FILE *) 1, (FILE *) 0};
//struct _reent *_impure_ptr = &r;

/**
 * @brief  Writes a character inside the given string. Returns 1.
 *
 * @param  pStr	Storage string.
 * @param  c    Character to write.
 */
signed int PutChar(char *pStr, char c)
{
    *pStr = c;
    return 1;
}

/**
 * @brief  Writes a string inside the given string.
 *
 * @param  pStr     Storage string.
 * @param  pSource  Source string.
 * @return  The size of the written
 */
signed int PutString(char *pStr, const char *pSource)
{
    signed int num = 0;
    
    while( *pSource != 0 )
    {
        
        *pStr++ = *pSource++;
        num++;
    }
    
    return num;
}

/**
 * @brief  Writes an unsigned int inside the given string, using the provided fill &
 *         width parameters.
 *
 * @param  pStr  Storage string.
 * @param  fill  Fill character.
 * @param  width  Minimum integer width.
 * @param  value  Integer value.
 */
signed int PutUnsignedInt(
        char *pStr,
        char fill,
        signed int width,
        unsigned int value)
{
    signed int num = 0;
    
    /* Take current digit into account when calculating width */
    width--;
    
    /* Recursively write upper digits */
    if( (value / 10) > 0 )
    {
        
        num = PutUnsignedInt(pStr, fill, width, value / 10);
        pStr += num;
    }
        
        /* Write filler characters */
    else
    {
        
        while( width > 0 )
        {
            
            PutChar(pStr, fill);
            pStr++;
            num++;
            width--;
        }
    }
    
    /* Write lower digit */
    num += PutChar(pStr, (value % 10) + '0');
    
    return num;
}

/**
 * @brief  Writes a signed int inside the given string, using the provided fill & width
 *         parameters.
 *
 * @param pStr   Storage string.
 * @param fill   Fill character.
 * @param width  Minimum integer width.
 * @param value  Signed integer value.
 */
signed int PutSignedInt(
        char *pStr,
        char fill,
        signed int width,
        signed int value)
{
    signed int num = 0;
    unsigned int absolute;
    
    /* Compute absolute value */
    if( value < 0 )
    {
        
        absolute = -value;
    }
    else
    {
        
        absolute = value;
    }
    
    /* Take current digit into account when calculating width */
    width--;
    
    /* Recursively write upper digits */
    if( (absolute / 10) > 0 )
    {
        
        if( value < 0 )
        {
            
            num = PutSignedInt(pStr, fill, width, -(absolute / 10));
        }
        else
        {
            
            num = PutSignedInt(pStr, fill, width, absolute / 10);
        }
        pStr += num;
    }
    else
    {
        
        /* Reserve space for sign */
        if( value < 0 )
        {
            
            width--;
        }
        
        /* Write filler characters */
        while( width > 0 )
        {
            
            PutChar(pStr, fill);
            pStr++;
            num++;
            width--;
        }
        
        /* Write sign */
        if( value < 0 )
        {
            
            num += PutChar(pStr, '-');
            pStr++;
        }
    }
    
    /* Write lower digit */
    num += PutChar(pStr, (absolute % 10) + '0');
    
    return num;
}

/**
 * @brief  Writes an hexadecimal value into a string, using the given fill, width &
 *         capital parameters.
 *
 * @param pStr   Storage string.
 * @param fill   Fill character.
 * @param width  Minimum integer width.
 * @param maj    Indicates if the letters must be printed in lower- or upper-case.
 * @param value  Hexadecimal value.
 *
 * @return  The number of char written
 */
signed int PutHexa(
        char *pStr,
        char fill,
        signed int width,
        unsigned char maj,
        unsigned int value)
{
    signed int num = 0;
    
    /* Decrement width */
    width--;
    
    /* Recursively output upper digits */
    if( (value >> 4) > 0 )
    {
        
        num += PutHexa(pStr, fill, width, maj, value >> 4);
        pStr += num;
    }
        /* Write filler chars */
    else
    {
        
        while( width > 0 )
        {
            
            PutChar(pStr, fill);
            pStr++;
            num++;
            width--;
        }
    }
    
    /* Write current digit */
    if( (value & 0xF) < 10 )
    {
        
        PutChar(pStr, (value & 0xF) + '0');
    }
    else if( maj )
    {
        
        PutChar(pStr, (value & 0xF) - 10 + 'A');
    }
    else
    {
        
        PutChar(pStr, (value & 0xF) - 10 + 'a');
    }
    num++;
    
    return num;
}



/* Global Functions ----------------------------------------------------------- */


/**
 * @brief  Stores the result of a formatted string into another string. Format
 *         arguments are given in a va_list instance.
 *
 * @param pStr    Destination string.
 * @param length  Length of Destination string.
 * @param pFormat Format string.
 * @param ap      Argument list.
 *
 * @return  The number of characters written.
 */
signed int vsnprintf(char *pStr, size_t length, const char *pFormat, va_list ap)
{
    char fill;
    unsigned char width;
    signed int num = 0;
    signed int size = 0;
    
    /* Clear the string */
    if( pStr )
    {
        
        *pStr = 0;
    }
    
    /* Phase string */
    while( *pFormat != 0 && size < length )
    {
        
        /* Normal character */
        if( *pFormat != '%' )
        {
            
            *pStr++ = *pFormat++;
            size++;
        }
            /* Escaped '%' */
        else if( *(pFormat + 1) == '%' )
        {
            
            *pStr++ = '%';
            pFormat += 2;
            size++;
        }
            /* Token delimiter */
        else
        {
            
            fill = ' ';
            width = 0;
            pFormat++;
            
            /* Parse filler */
            if( *pFormat == '0' )
            {
                
                fill = '0';
                pFormat++;
            }
            
            /* Parse width */
            while( (*pFormat >= '0') && (*pFormat <= '9') )
            {
                
                width = (width * 10) + *pFormat - '0';
                pFormat++;
            }
            
            /* Check if there is enough space */
            if( size + width > length )
            {
                
                width = length - size;
            }
            
            /* Parse type */
            switch( *pFormat )
            {
                case 'd':
                case 'i':
                    num = PutSignedInt(pStr, fill, width, va_arg(ap, signed int));
                    break;
                case 'u':
                    num = PutUnsignedInt(pStr, fill, width, va_arg(ap, unsigned int));
                    break;
                case 'x':
                    num = PutHexa(pStr, fill, width, 0, va_arg(ap, unsigned int));
                    break;
                case 'X':
                    num = PutHexa(pStr, fill, width, 1, va_arg(ap, unsigned int));
                    break;
                case 's':
                    num = PutString(pStr, va_arg(ap, char *));
                    break;
                case 'c':
                    num = PutChar(pStr, va_arg(ap, unsigned int));
                    break;
                default:
                    return EOF;
            }
            
            pFormat++;
            pStr += num;
            size += num;
        }
    }
    
    /* NULL-terminated (final \0 is not counted) */
    if( size < length )
    {
        
        *pStr = 0;
    }
    else
    {
        
        *(--pStr) = 0;
        size--;
    }
    
    return size;
}

/**
 * @brief  Stores the result of a formatted string into another string. Format
 *         arguments are given in a va_list instance.
 *
 * @param pStr    Destination string.
 * @param length  Length of Destination string.
 * @param pFormat Format string.
 * @param ...     Other arguments
 *
 * @return  The number of characters written.
 */
signed int snprintf(char *pString, size_t length, const char *pFormat, ...)
{
    va_list ap;
    signed int rc;
    
    va_start(ap, pFormat);
    rc = vsnprintf(pString, length, pFormat, ap);
    va_end(ap);
    
    return rc;
}

/**
 * @brief  Stores the result of a formatted string into another string. Format
 *         arguments are given in a va_list instance.
 *
 * @param pString  Destination string.
 * @param length   Length of Destination string.
 * @param pFormat  Format string.
 * @param ap       Argument list.
 *
 * @return  The number of characters written.
 */
signed int vsprintf(char *pString, const char *pFormat, va_list ap)
{
    return vsnprintf(pString, MAX_STRING_SIZE, pFormat, ap);
}

/**
 * @brief  Outputs a formatted string on the given stream. Format arguments are given
 *         in a va_list instance.
 *
 * @param pStream  Output stream.
 * @param pFormat  Format string
 * @param ap       Argument list.
 */
signed int vfprintf(FILE *pStream, const char *pFormat, va_list ap)
{
    char pStr[MAX_STRING_SIZE];
    char pError[] = "stdio.c: increase MAX_STRING_SIZE\n\r";
    
    /* Write formatted string in buffer */
    if( vsprintf(pStr, pFormat, ap) >= MAX_STRING_SIZE )
    {
        
        fputs(pError, stderr);
        while( 1 ); /* Increase MAX_STRING_SIZE */
    }
    
    /* Display string */
    return fputs(pStr, pStream);
}

/**
 * @brief  Outputs a formatted string on the DBGU stream. Format arguments are given
 *         in a va_list instance.
 *
 * @param pFormat  Format string.
 * @param ap  Argument list.
 */
signed int vprintf(const char *pFormat, va_list ap)
{
    return vfprintf(stdout, pFormat, ap);
}

/**
 * @brief  Outputs a formatted string on the given stream, using a variable
 *         number of arguments.
 *
 * @param pStream  Output stream.
 * @param pFormat  Format string.
 */
signed int fprintf(FILE *pStream, const char *pFormat, ...)
{
    va_list ap;
    signed int result;
    
    /* Forward call to vfprintf */
    va_start(ap, pFormat);
    result = vfprintf(pStream, pFormat, ap);
    va_end(ap);
    
    return result;
}

/**
 * @brief  Outputs a formatted string on the DBGU stream, using a variable number of
 *         arguments.
 *
 * @param  pFormat  Format string.
 */
signed int Printf(const char *pFormat, ...)
{
    va_list ap;
    signed int result;
    
    /* Forward call to vprintf */
    va_start(ap, pFormat);
    result = vprintf(pFormat, ap);
    va_end(ap);
    
    return result;
}
int printf(const char *pFormat, ...)
{
    va_list ap;
    signed int result;
    
    /* Forward call to vprintf */
    va_start(ap, pFormat);
    result = vprintf(pFormat, ap);
    va_end(ap);
    
    return result;
}

/**
 * @brief  Writes a formatted string inside another string.
 *
 * @param pStr     torage string.
 * @param pFormat  Format string.
 */
signed int sprintf(char *pStr, const char *pFormat, ...)
{
    va_list ap;
    signed int result;
    
    // Forward call to vsprintf
    va_start(ap, pFormat);
    result = vsprintf(pStr, pFormat, ap);
    va_end(ap);
    
    return result;
}

/**
 * @brief  Outputs a string on stdout.
 *
 * @param pStr  String to output.
 */
signed int puts(const char *pStr)
{
    signed int i = fputs(pStr, stdout);
    fputc('\n', stdout);
    
    return i + 1;
}

/**
 * @brief  Implementation of fputc using the DBGU as the standard output. Required
 *         for printf().
 *
 * @param c        Character to write.
 * @param pStream  Output stream.
 * @param The character written if successful, or -1 if the output stream is
 *        not stdout or stderr.
 */
signed int fputc(signed int c, FILE *pStream)
{
    if( (pStream == stdout) || (pStream == stderr) )
    {
        
        PrintChar(c);
        
        return c;
    }
    else
    {
        
        return EOF;
    }
}

/**
 * @brief  Implementation of fputs using the DBGU as the standard output. Required
 *         for printf().
 *
 * @param pStr     String to write.
 * @param pStream  Output stream.
 *
 * @return  Number of characters written if successful, or -1 if the output
 *          stream is not stdout or stderr.
 */
signed int fputs(const char *pStr, FILE *pStream)
{
    signed int num = 0;
    
    while( *pStr != 0 )
    {
        
        if( fputc(*pStr, pStream) == -1 )
        {
            
            return -1;
        }
        num++;
        pStr++;
    }
    
    return num;
}

/* --------------------------------- End Of File ------------------------------ */
