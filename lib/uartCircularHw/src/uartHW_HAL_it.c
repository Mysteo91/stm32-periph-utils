//
// Created by user on 07.05.2025.
//

#include "uartHW_HAL_it.h"

extern UART_HandleTypeDef* getUartHalHandleByUSART (USART_TypeDef* usart);

#ifdef UART1_HW
void USART1_IRQHandler(void)
{
    HAL_UART_IRQHandler(getUartHalHandleByUSART(USART1));
}
#endif

#ifdef UART2_HW
void USART2_IRQHandler(void)
{
    HAL_UART_IRQHandler(getUartHalHandleByUSART(USART2));
}
#endif

#ifdef UART3_HW
void USART3_IRQHandler(void)
{

    HAL_UART_IRQHandler(getUartHalHandleByUSART(USART3));
}
#endif

#ifdef UART4_HW
void UART4_IRQHandler(void)
{

    HAL_UART_IRQHandler(getUartHalHandleByUSART(USART3));
}
#endif

#ifdef UART5_HW

void UART5_IRQHandler(void)
{

    HAL_UART_IRQHandler(getUartHalHandleByUSART(UART5));
}
#endif

#ifdef UART6_HW

void USART6_IRQHandler(void)
{
    HAL_UART_IRQHandler(getUartHalHandleByUSART(USART6));
}
#endif