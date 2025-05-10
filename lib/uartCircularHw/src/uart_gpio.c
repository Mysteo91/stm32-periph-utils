//
// Created by user on 08.05.2025.
//

#include "uart_gpio.h"

/*
 *
 *
 */

int8_t gpioGetAlternateFunction(GPIO_TypeDef *port, uint32_t pin, void *hw_fucntion) {

#if STM32H523xx
    if (hw_fucntion == USART1 ) {
        if (port == GPIOA  &&  ( pin == GPIO_PIN_9 || pin == GPIO_PIN_10 )) {
            return GPIO_AF7_USART1;
        }
        if (port == GPIOB  &&  ( pin == GPIO_PIN_6 || pin == GPIO_PIN_7 )) {
            return GPIO_AF7_USART1;
        }
        if (port == GPIOB && ( pin == GPIO_PIN_14 || pin == GPIO_PIN_15 )) {
            return GPIO_AF4_USART1;
        }
    }
    if (hw_fucntion == USART2 ) {
        if (port == GPIOA  &&  ( pin == GPIO_PIN_2 || pin == GPIO_PIN_3 )) {
            return GPIO_AF7_USART2;
        }
        if (port == GPIOB  &&  ( pin == GPIO_PIN_0 || pin == GPIO_PIN_1 )) {
            return GPIO_AF7_USART2;
        }
        if (port == GPIOD  &&  ( pin == GPIO_PIN_5 || pin == GPIO_PIN_6 )) {
            return GPIO_AF7_USART2;
        }
    }
    if (hw_fucntion == USART3 ) {
        if (port == GPIOB  &&  ( pin == GPIO_PIN_1 || pin == GPIO_PIN_10 )) {
            return GPIO_AF7_USART3;
        }
        if (port == GPIOC && ( pin == GPIO_PIN_4 || pin == GPIO_PIN_10 || pin == GPIO_PIN_11 )) {
            return GPIO_AF7_USART3;
        }
        if (port == GPIOD && ( pin == GPIO_PIN_8 || pin == GPIO_PIN_9 )) {
            return GPIO_AF7_USART3;
        }
    }
    if (hw_fucntion == UART4 ) {
        if (port == GPIOA && ( pin == GPIO_PIN_11 || pin == GPIO_PIN_12)) {
            return GPIO_AF6_UART4;
        }
        if (port == GPIOA && ( pin == GPIO_PIN_11 || pin == GPIO_PIN_12)) {
            return GPIO_AF6_UART4;
        }

    }

#endif

}
