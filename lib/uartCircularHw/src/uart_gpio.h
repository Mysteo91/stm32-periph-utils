//
// Created by user on 08.05.2025.
//

#ifndef GPIO_CHECK_H
#define GPIO_CHECK_H

#include <stdbool.h>


#if defined(UARTHW_APP_CONFIG)
#include UARTHW_APP_CONFIG
#else
#error "please define UARTHW_APP_CONFIG path"
#endif

#if STM32H523xx
#include "stm32h5xx.h"

        #ifdef UART1_HW

                #if defined UART1_HW_CTS_PIN || defined UART1_HW_RTS_PIN

                        #if defined UART1_HW_CTS_PIN

                                #if UART1_HW_CTS_PORT == GPIOA_BASE_NS

                                        #if UART1_HW_CTS_PIN == PIN_11

                                                #define UART1_HW_CTS_ALTERNATE_FUNC GPIO_AF7_USART1
                                                #undef UART1_HW_CTS_PIN
                                                #define UART1_HW_CTS_PIN ((uint16_t)PIN_11)

                                        #else
                                                #error UART1_HW_CTS_PIN HAVE WRONG PIN NUMBER
                                        #endif
                                #else
                                        #error "Wrong UART1_HW_CTS_PORT "
                                #endif
                        #endif

                        #if defined UART1_HW_RTS_PIN

                                #if UART1_HW_RTS_PORT == GPIOA_BASE_NS

                                        #if UART1_HW_RTS_PIN == PIN_1

                                                #define UART1_HW_RTS_ALTERNATE_FUNC GPIO_AF7_USART1
                                                #undef UART1_HW_RTS_PIN
                                                #define UART1_HW_RTS_PIN ((uint16_t)PIN_12)

                                        #else
                                                #error UART1_HW_RTS_PIN HAVE WRONG PIN NUMBER
                                        #endif
                                #else
                                        #error "Wrong UART1_HW_RTS_PORT "
                                #endif
                        #endif


                        #if defined UART1_HW_RTS_PIN && defined UART1_HW_CTS_PIN
                                #define UART1_HW_FLOW_CONTROL (USART_CR3_RTSE | USART_CR3_CTSE)
                        #elif defined UART1_HW_RTS_PIN && !defined UART1_HW_CTS_PIN
                                #define UART1_HW_FLOW_CONTROL USART_CR3_RTSE
                        #elif !defined UART1_HW_RTS_PIN && defined UART1_HW_CTS_PIN
                                #define UART1_HW_FLOW_CONTROL USART_CR3_CTSE
                        #endif

                #else
                        #define UART1_HW_FLOW_CONTROL 0x00000000U
                #endif

                #if !defined UART1_HW_RX_PORT && defined UART1_HW_RX_PIN
                        #error "Your are foggot define UART1_RX_PORT in UART_HW_CONFIG.h "
                #elif defined UART1_HW_RX_PORT && !defined UART1_HW_RX_PIN
                        #error "Your are foggot define UART1_RX_PIN in UART_HW_CONFIG.h "
                #endif

                #if !defined UART1_HW_TX_PORT && defined UART1_HW_TX_PIN
                        #error "Your are foggot define UART1_TX_PORT in UART_HW_CONFIG.h "
                #elif defined UART1_HW_RX_PORT && !defined UART1_HW_RX_PIN
                        #error "Your are foggot define UART1_TX_PIN in UART_HW_CONFIG.h "
                #endif

                #if  !defined UART2_HW_RX_PORT && !defined UART2_HW_TX_PORT || !defined UART2_HW_TX_PIN && !defined UART2_HW_RX_PIN
                #error "please define  TX_PORT || RX_PORT || TX_PIN || RX_PIN of UART1 in UART_HW_CONFIG.h "
                #endif

                #if defined UART1_HW_RX_PORT
                        #if UART_HW1_RX_PORT == GPIOA_BASE_NS

                                #if UART1_HW_RX_PIN == PIN_10

                                        #define UART1_HW_RX_ALTERNATE_FUNC GPIO_AF7_USART1
                                        #undef UART1_HW_RX_PIN
                                        #define UART1_HW_RX_PIN ((uint16_t)PIN_10)

                                #else
                                        #error UART1_HW_RX_PIN HAVE WRONG PIN NUMBER
                                #endif


                        #elif UART1_HW_RX_PORT == GPIOB_BASE_NS

                                #if UART1_HW_RX_PIN == PIN_15

                                        #define UART1_HW_RX_ALTERNATE_FUNC GPIO_AF4_USART1
                                        #undef UART1_HW_RX_PIN
                                        #define UART1_HW_RX_PIN ((uint16_t)PIN_15)

                                #elif UART1_HW_RX_PIN == PIN_7

                                        #define UART1_HW_RX_ALTERNATE_FUNC GPIO_AF7_USART1
                                        #undef UART1_HW_RX_PIN
                                        #define UART1_HW_RX_PIN ((uint16_t)PIN_7)

                                #else
                                        #error UART1_HW_RX_PIN HAVE WRONG PIN NUMBER
                                #endif
                        #else
                                #error "Wrong UART1_HW_RX_PORT "
                        #endif
                #endif

                #if defined UART1_HW_TX_PORT && defined UART1_HW_TX_PIN

                        #if UART1_HW_TX_PORT == GPIOA_BASE_NS

                                #if UART1_HW_TX_PIN == PIN_9
                                        #define UART1_HW_TX_ALTERNATE_FUNC GPIO_AF7_USART1
                                        #undef UART1_HW_TX_PIN
                                        #define UART1_HW_TX_PIN ((uint16_t)PIN_9)
                                #elif (UART1_HW_TX_PIN == PIN_15)
                                        #define UART1_HW_TX_ALTERNATE_FUNC GPIO_AF7_USART1
                                        #undef UART1_HW_TX_PIN
                                        #define UART1_HW_TX_PIN ((uint16_t)PIN_15)
                                #else
                                        #error UART1_HW_TX_PIN HAVE WRONG PIN NUMBER
                                #endif


                        #elif UART1_HW_TX_PORT == GPIOB_BASE_NS

                                #if UART1_HW_TX_PIN == PIN_6

                                        #define UART1_HW_TX_ALTERNATE_FUNC GPIO_AF4_USART1
                                        #undef UART1_HW_TX_PIN
                                        #define UART1_HW_TX_PIN ((uint16_t)PIN_6)

                                #elif UART1_HW_TX_PIN == PIN_14

                                        #define UART1_HW_TX_ALTERNATE_FUNC GPIO_AF4_USART1
                                        #undef UART1_HW_TX_PIN
                                        #define UART1_HW_TX_PIN ((uint16_t)PIN_14)

                                #else
                                        #error UART1_HW_TX_PIN HAVE WRONG PIN NUMBER
                                #endif
                        #else
                                #error "Wrong UART1_HW_RX_PORT "
                        #endif

                #endif

                #if defined UART1_HW_RX_PORT && defined UART1_HW_TX_PORT
                        #define UART1_HW_MODE (USART_CR1_TE |USART_CR1_RE)
                #elif defined UART1_HW_RX_PORT && !defined UART1_HW_TX_PORT
                        #define UART1_HW_MODE USART_CR1_RE)
                #elif defined !UART1_HW_RX_PORT && defined UART1_HW_TX_PORT
                        #define UART1_HW_MODE (USART_CR1_TE)
                #endif

        #endif

        #ifdef UART2_HW

                #if defined UART2_HW_CTS_PIN || defined UART2_HW_RTS_PIN

                        #if defined UART2_HW_CTS_PIN

                                #if UART2_HW_CTS_PORT == GPIOA_BASE_NS

                                        #if UART2_HW_CTS_PIN == PIN_0

                                                #define UART2_HW_CTS_ALTERNATE_FUNC GPIO_AF7_USART2
                                                #undef UART2_HW_CTS_PIN
                                                #define UART2_HW_CTS_PIN ((uint16_t)PIN_0)

                                        #else
                                                #error UART2_HW_CTS_PIN HAVE WRONG PIN NUMBER
                                        #endif
                                #elif UART2_HW_CTS_PORT == GPIOD_BASE_NS

                                        #if UART2_HW_CTS_PIN == PIN_3

                                                #define UART2_HW_CTS_ALTERNATE_FUNC GPIO_AF7_USART2
                                                #undef UART2_HW_CTS_PIN
                                                #define UART2_HW_CTS_PIN ((uint16_t)PIN_3)

                                        #else
                                                #error UART2_HW_CTS_PIN HAVE WRONG PIN NUMBER
                                        #endif
                                #else
                                        #error "Wrong UART2_HW_CTS_PORT "
                                #endif
                        #endif

                        #if defined UART2_HW_RTS_PIN

                                #if UART2_HW_RTS_PORT == GPIOA_BASE_NS

                                        #if UART2_HW_RTS_PIN == PIN_1

                                                #define UART2_HW_RTS_ALTERNATE_FUNC GPIO_AF7_USART2
                                                #undef UART2_HW_RTS_PIN
                                                #define UART2_HW_RTS_PIN ((uint16_t)PIN_1)

                                        #else
                                                #error UART2_HW_RTS_PIN HAVE WRONG PIN NUMBER
                                        #endif
                                #elif UART2_HW_RTS_PORT == GPIOD_BASE_NS

                                        #if UART2_HW_RTS_PIN == PIN_4

                                                #define UART2_HW_RTS_ALTERNATE_FUNC GPIO_AF7_USART2
                                                #undef UART2_HW_RTS_PIN
                                                #define UART2_HW_RTS_PIN ((uint16_t)PIN_4)

                                        #else
                                                #error UART2_HW_RTS_PIN HAVE WRONG PIN NUMBER
                                        #endif
                                #else
                                        #error "Wrong UART2_HW_RTS_PORT "
                                #endif
                        #endif


                        #if defined UART2_HW_RTS_PIN && defined UART2_HW_CTS_PIN
                                #define UART2_HW_FLOW_CONTROL (USART_CR3_RTSE | USART_CR3_CTSE)
                        #elif defined UART2_HW_RTS_PIN && !defined UART2_HW_CTS_PIN
                                #define UART2_HW_FLOW_CONTROL USART_CR3_RTSE
                        #elif !defined UART2_HW_RTS_PIN && defined UART2_HW_CTS_PIN
                                #define UART2_HW_FLOW_CONTROL USART_CR3_CTSE
                        #endif

                #else
                        #define UART2_HW_FLOW_CONTROL 0x00000000U
                #endif

                #if defined UART2_HW_RX_PORT && defined UART2_HW_RX_PIN
                        #if UART2_HW_RX_PORT == GPIOA_BASE_NS // UART2 RX - PA3 PD6

                                #if UART2_HW_RX_PIN == PIN_3

                                        #define UART2_HW_RX_ALTERNATE_FUNC GPIO_AF7_USART2
                                        #undef UART2_HW_RX_PIN
                                        #define UART2_HW_RX_PIN ((uint16_t)PIN_3)

                                #else
                                        #error UART2_HW_RX_PIN HAVE WRONG PIN NUMBER
                                #endif


                        #elif UART2_HW_RX_PORT == GPIOD_BASE_NS

                                #if UART2_HW_RX_PIN == PIN_6

                                        #define UART2_HW_RX_ALTERNATE_FUNC GPIO_AF7_USART2
                                        #undef UART2_HW_RX_PIN
                                        #define UART2_HW_RX_PIN ((uint16_t)PIN_6)

                                #else
                                        #error UART2_HW_RX_PIN HAVE WRONG PIN NUMBER
                                #endif
                        #else
                                #error "Wrong UART2_HW_RX_PORT "
                        #endif
                #endif

                #if defined UART2_HW_TX_PORT && defined UART2_HW_TX_PIN

                        #if UART2_HW_TX_PORT == GPIOA_BASE_NS // TX - PA2  PB0  PD5

                                #if UART2_HW_TX_PIN == PIN_2

                                        #define UART2_HW_TX_ALTERNATE_FUNC GPIO_AF7_USART2
                                        #undef UART2_HW_TX_PIN
                                        #define UART2_HW_TX_PIN ((uint16_t)PIN_2)

                                #else
                                        #error UART2_HW_TX_PIN HAVE WRONG PIN NUMBER
                                #endif


                        #elif UART2_HW_TX_PORT == GPIOB_BASE_NS

                                #if UART2_HW_TX_PIN == PIN_0

                                        #define UART2_HW_TX_ALTERNATE_FUNC GPIO_AF7_USART2
                                        #undef UART2_HW_TX_PIN
                                        #define UART2_HW_TX_PIN ((uint16_t)PIN_0)

                                #else
                                    #error UART2_HW_TX_PIN HAVE WRONG PIN NUMBER
                                #endif
                        #elif UART2_HW_TX_PORT == GPIOD_BASE_NS
                                #if UART2_HW_TX_PIN == PIN_5

                                        #define UART2_HW_TX_ALTERNATE_FUNC GPIO_AF7_USART2
                                        #undef UART2_HW_TX_PIN
                                        #define UART2_HW_TX_PIN ((uint16_t)PIN_5)

                                #else
                                #error UART2_HW_TX_PIN HAVE WRONG PIN NUMBER
                                #endif
                        #else
                                #error "Wrong UART2_HW_TX_PORT "
                        #endif
                #endif

                #if defined UART2_HW_RX_PORT && defined UART2_HW_TX_PORT
                        #define UART2_HW_MODE (USART_CR1_TE |USART_CR1_RE)
                #elif defined UART2_HW_RX_PORT && !defined UART2_HW_TX_PORT
                        #define UART2_HW_MODE USART_CR1_RE)
                #elif defined !UART2_HW_RX_PORT && defined UART2_HW_TX_PORT
                        #define UART2_HW_MODE (USART_CR1_TE)
                #endif
        #endif



        #ifdef UART3_HW
                #if defined UART3_HW_CTS_PIN || defined UART3_HW_RTS_PIN

                        #if defined UART3_HW_CTS_PIN

                                #if UART3_HW_CTS_PORT == GPIOB_BASE_NS

                                        #if UART3_HW_CTS_PIN == PIN_13

                                                #define UART3_HW_CTS_ALTERNATE_FUNC GPIO_AF7_USART3
                                                #undef UART3_HW_CTS_PIN
                                                #define UART3_HW_CTS_PIN ((uint16_t)PIN_13)

                                        #else
                                                #error UART3_HW_CTS_PIN HAVE WRONG PIN NUMBER
                                        #endif
                                #elif UART3_HW_CTS_PORT == GPIOD_BASE_NS

                                        #if UART3_HW_CTS_PIN == PIN_11

                                                #define UART3_HW_CTS_ALTERNATE_FUNC GPIO_AF7_USART3
                                                #undef UART3_HW_CTS_PIN
                                                #define UART3_HW_CTS_PIN ((uint16_t)PIN_11)

                                        #else
                                                #error UART3_HW_CTS_PIN HAVE WRONG PIN NUMBER
                                        #endif
                                #else
                                        #error "Wrong UART3_HW_CTS_PORT "
                                #endif
                        #endif

                        #if defined UART3_HW_RTS_PIN

                                #if UART3_HW_RTS_PORT == GPIOB_BASE_NS

                                        #if UART3_HW_RTS_PIN == PIN_14

                                                #define UART3_HW_RTS_ALTERNATE_FUNC GPIO_AF7_USART3
                                                #undef UART3_HW_RTS_PIN
                                                #define UART3_HW_RTS_PIN ((uint16_t)PIN_14)

                                        #else
                                                #error UART3_HW_RTS_PIN HAVE WRONG PIN NUMBER
                                        #endif
                                #elif UART3_HW_RTS_PORT == GPIOD_BASE_NS

                                        #if UART3_HW_RTS_PIN == PIN_12

                                                #define UART3_HW_RTS_ALTERNATE_FUNC GPIO_AF7_USART3
                                                #undef UART3_HW_RTS_PIN
                                                #define UART3_HW_RTS_PIN ((uint16_t)PIN_12)

                                        #else
                                                #error UART3_HW_RTS_PIN HAVE WRONG PIN NUMBER
                                        #endif
                                #else
                                        #error "Wrong UART3_HW_RTS_PORT "
                                #endif
                        #endif


                        #if defined UART3_HW_RTS_PIN && defined UART3_HW_CTS_PIN
                                #define UART3_HW_FLOW_CONTROL (USART_CR3_RTSE | USART_CR3_CTSE)
                        #elif defined UART3_HW_RTS_PIN && !defined UART3_HW_CTS_PIN
                                #define UART3_HW_FLOW_CONTROL USART_CR3_RTSE
                        #elif !defined UART3_HW_RTS_PIN && defined UART3_HW_CTS_PIN
                                #define UART3_HW_FLOW_CONTROL USART_CR3_CTSE
                        #endif

                #else
                        #define UART3_HW_FLOW_CONTROL 0x00000000U
                #endif

                #if defined UART3_HW_RX_PORT && defined UART3_HW_RX_PIN

                        #if UART3_HW_RX_PORT == GPIOB_BASE_NS // UART3 RX - PB1  PC4 PC11 PD9

                                #if UART3_HW_RX_PIN == PIN_1

                                        #define UART3_HW_RX_ALTERNATE_FUNC GPIO_AF7_USART3
                                        #undef UART3_HW_RX_PIN
                                        #define UART3_HW_RX_PIN ((uint16_t)PIN_1)

                                #else
                                        #error UART3_HW_RX_PIN HAVE WRONG PIN NUMBER
                                #endif


                        #elif UART3_HW_RX_PORT == GPIOC_BASE_NS

                                #if UART3_HW_RX_PIN == PIN_4

                                        #define UART3_HW_RX_ALTERNATE_FUNC GPIO_AF7_USART3
                                        #undef UART3_HW_RX_PIN
                                        #define UART3_HW_RX_PIN ((uint16_t)PIN_4)

                                #elif UART3_HW_RX_PIN == PIN_11
                                        #define UART3_HW_RX_ALTERNATE_FUNC GPIO_AF7_USART3
                                        #undef UART3_HW_RX_PIN
                                        #define UART3_HW_RX_PIN ((uint16_t)PIN_11)
                                #else
                                        #error UART3_HW_RX_PIN HAVE WRONG PIN NUMBER
                                #endif

                        #elif UART3_HW_RX_PORT == GPIOD_BASE_NS

                                #if UART3_HW_RX_PIN == PIN_9

                                        #define UART3_HW_RX_ALTERNATE_FUNC GPIO_AF7_USART3
                                        #undef UART3_HW_RX_PIN
                                        #define UART3_HW_RX_PIN ((uint16_t)PIN_9)

                                #else
                                #error UART3_HW_RX_PIN HAVE WRONG PIN NUMBER
                                #endif

                        #else
                                #error "Wrong UART3_HW_RX_PORT "
                        #endif
                #endif


                #if defined UART3_HW_TX_PORT && defined UART3_HW_TX_PIN

                        #if UART3_HW_TX_PORT == GPIOB_BASE_NS // TX - PB10  PC10 PD8

                                #if UART3_HW_TX_PIN == PIN_10

                                        #define UART3_HW_TX_ALTERNATE_FUNC GPIO_AF7_USART3
                                        #undef UART3_HW_TX_PIN
                                        #define UART3_HW_TX_PIN ((uint16_t)PIN_10)

                                #else
                                        #error UART3_HW_TX_PIN HAVE WRONG PIN NUMBER
                                #endif


                        #elif UART3_HW_TX_PORT == GPIOC_BASE_NS

                                #if UART3_HW_TX_PIN == PIN_10

                                        #define UART3_HW_TX_ALTERNATE_FUNC GPIO_AF7_USART3
                                        #undef UART3_HW_TX_PIN
                                        #define UART3_HW_TX_PIN ((uint16_t)PIN_10)

                                #else
                                    #error UART3_HW_TX_PIN HAVE WRONG PIN NUMBER
                                #endif

                        #elif UART3_HW_TX_PORT == GPIOD_BASE_NS
                                #if UART3_HW_TX_PIN == PIN_8

                                        #define UART3_HW_TX_ALTERNATE_FUNC GPIO_AF7_USART3
                                        #undef UART3_HW_TX_PIN
                                        #define UART3_HW_TX_PIN ((uint16_t)PIN_8)

                                #else
                                #error UART3_HW_TX_PIN HAVE WRONG PIN NUMBER
                                #endif
                        #else
                                #error "Wrong UART3_HW_TX_PORT "
                        #endif
                #endif

                #if defined UART3_HW_RX_PORT && defined UART3_HW_TX_PORT
                        #define UART3_HW_MODE (USART_CR1_TE |USART_CR1_RE)
                #elif defined UART3_HW_RX_PORT && !defined UART3_HW_TX_PORT
                        #define UART3_HW_MODE USART_CR1_RE)
                #elif defined !UART3_HW_RX_PORT && defined UART3_HW_TX_PORT
                        #define UART3_HW_MODE (USART_CR1_TE)
                #endif

        #endif

        #ifdef UART4_HW

                #if defined UART4_HW_CTS_PIN || defined UART4_HW_RTS_PIN

                        #if defined UART4_HW_CTS_PIN

                                #if UART4_HW_CTS_PORT == GPIOB_BASE_NS

                                        #if UART4_HW_CTS_PIN == PIN_0

                                                #define UART4_HW_CTS_ALTERNATE_FUNC GPIO_AF8_UART4
                                                #undef UART4_HW_CTS_PIN
                                                #define UART4_HW_CTS_PIN ((uint16_t)PIN_0)
                                        #elif UART4_HW_CTS_PIN == PIN_15
                                                #define UART4_HW_CTS_ALTERNATE_FUNC GPIO_AF8_UART4
                                                #undef UART4_HW_CTS_PIN
                                                #define UART4_HW_CTS_PIN ((uint16_t)PIN_15)
                                        #else
                                                #error UART4_HW_CTS_PIN HAVE WRONG PIN NUMBER
                                        #endif
                                #else
                                        #error "Wrong UART4_HW_CTS_PORT "
                                #endif
                        #endif

                        #if defined UART4_HW_RTS_PIN

                                #if UART4_HW_RTS_PORT == GPIOA_BASE_NS

                                        #if UART4_HW_RTS_PIN == PIN_15

                                                #define UART4_HW_RTS_ALTERNATE_FUNC GPIO_AF8_UART4
                                                #undef UART4_HW_RTS_PIN
                                                #define UART4_HW_RTS_PIN ((uint16_t)PIN_15)

                                        #else
                                                #error UART4_HW_RTS_PIN HAVE WRONG PIN NUMBER
                                        #endif
                                #elif UART4_HW_RTS_PORT == GPIOB_BASE_NS

                                        #if UART4_HW_RTS_PIN == PIN_14

                                                #define UART4_HW_RTS_ALTERNATE_FUNC GPIO_AF8_UART4
                                                #undef UART4_HW_RTS_PIN
                                                #define UART4_HW_RTS_PIN ((uint16_t)PIN_14)

                                        #else
                                                #error UART4_HW_RTS_PIN HAVE WRONG PIN NUMBER
                                        #endif
                                #else
                                        #error "Wrong UART4_HW_RTS_PORT "
                                #endif
                        #endif


                        #if defined UART4_HW_RTS_PIN && defined UART4_HW_CTS_PIN
                                #define UART4_HW_FLOW_CONTROL (USART_CR3_RTSE | USART_CR3_CTSE)
                        #elif defined UART4_HW_RTS_PIN && !defined UART4_HW_CTS_PIN
                                #define UART4_HW_FLOW_CONTROL USART_CR3_RTSE
                        #elif !defined UART4_HW_RTS_PIN && defined UART4_HW_CTS_PIN
                                #define UART4_HW_FLOW_CONTROL USART_CR3_CTSE
                        #endif

                #else
                        #define UART4_HW_FLOW_CONTROL 0x00000000U
                #endif

                #if defined UART4_HW_RX_PORT && defined UART4_HW_RX_PIN

                        #if UART4_HW_RX_PORT == GPIOA_BASE_NS // UART4 RX - PA11 PA1 PB8 PC11 PD0 PD11

                                #if UART4_HW_RX_PIN == PIN_11

                                        #define UART4_HW_RX_ALTERNATE_FUNC GPIO_AF6_UART4
                                        #undef UART4_HW_RX_PIN
                                        #define UART4_HW_RX_PIN ((uint16_t)PIN_11)

                                #elif UART4_HW_RX_PIN == PIN_1
                                        #define UART4_HW_RX_ALTERNATE_FUNC GPIO_AF8_UART4
                                        #undef UART4_HW_RX_PIN
                                        #define UART4_HW_RX_PIN ((uint16_t)PIN_1)

                                #else
                                        #error UART4_HW_RX_PIN HAVE WRONG PIN NUMBER
                                #endif


                        #elif UART4_HW_RX_PORT == GPIOB_BASE_NS

                                #if UART4_HW_RX_PIN == PIN_8

                                        #define UART4_HW_RX_ALTERNATE_FUNC GPIO_AF8_UART4
                                        #undef UART4_HW_RX_PIN
                                        #define UART4_HW_RX_PIN ((uint16_t)PIN_8)
                                #else
                                        #error UART4_HW_RX_PIN HAVE WRONG PIN NUMBER
                                #endif

                        #elif UART4_HW_RX_PORT == GPIOC_BASE_NS

                                #if UART4_HW_RX_PIN == PIN_11

                                        #define UART4_HW_RX_ALTERNATE_FUNC GPIO_AF8_UART4
                                        #undef UART4_HW_RX_PIN
                                        #define UART4_HW_RX_PIN ((uint16_t)PIN_11)

                                #else
                                        #error UART4_HW_RX_PIN HAVE WRONG PIN NUMBER
                                #endif

                        #elif UART4_HW_RX_PORT == GPIOD_BASE_NS

                                #if UART4_HW_RX_PIN == PIN_0

                                        #define UART4_HW_RX_ALTERNATE_FUNC GPIO_AF8_UART4
                                        #undef UART4_HW_RX_PIN
                                        #define UART4_HW_RX_PIN ((uint16_t)PIN_0)

                                #elif UART4_HW_RX_PIN == PIN_11

                                        #define UART4_HW_RX_ALTERNATE_FUNC GPIO_AF8_UART4
                                        #undef UART4_HW_RX_PIN
                                        #define UART4_HW_RX_PIN ((uint16_t)PIN_11)

                                #else
                                        #error UART4_HW_RX_PIN HAVE WRONG PIN NUMBER
                                #endif

                        #else
                                #error "Wrong UART4_HW_RX_PORT "
                        #endif
                #endif

                #if defined UART4_HW_TX_PORT && defined UART4_HW_TX_PIN


                        #if UART4_HW_TX_PORT == GPIOA_BASE_NS // UART4 TX - PA12 PA0 PB9 PC10 PD1 PD12

                                #if UART4_HW_TX_PIN == PIN_12

                                        #define UART4_HW_TX_ALTERNATE_FUNC GPIO_AF6_UART4
                                        #undef UART4_HW_TX_PIN
                                        #define UART4_HW_TX_PIN ((uint16_t)PIN_12)

                                #elif UART4_HW_TX_PIN == PIN_0

                                      #define UART4_HW_RX_ALTERNATE_FUNC GPIO_AF8_UART4
                                      #undef UART4_HW_RX_PIN
                                      #define UART4_HW_RX_PIN ((uint16_t)PIN_0)

                                #else
                                        #error UART4_HW_TX_PIN HAVE WRONG PIN NUMBER
                                #endif


                        #elif UART4_HW_TX_PORT == GPIOB_BASE_NS

                                #if UART4_HW_TX_PIN == PIN_9

                                        #define UART4_HW_TX_ALTERNATE_FUNC GPIO_AF8_UART4
                                        #undef UART4_HW_TX_PIN
                                        #define UART4_HW_TX_PIN ((uint16_t)PIN_9)

                                #else
                                    #error UART4_HW_TX_PIN HAVE WRONG PIN NUMBER
                                #endif

                        #elif UART4_HW_TX_PORT == GPIOC_BASE_NS
                                #if UART4_HW_TX_PIN == PIN_10

                                        #define UART4_HW_TX_ALTERNATE_FUNC GPIO_AF8_UART4
                                        #undef UART4_HW_TX_PIN
                                        #define UART4_HW_TX_PIN ((uint16_t)PIN_10)

                                #else
                                        #error UART4_HW_TX_PIN HAVE WRONG PIN NUMBER
                                #endif

                        #elif UART4_HW_TX_PORT == GPIOD_BASE_NS
                                #if UART4_HW_TX_PIN == PIN_1

                                        #define UART4_HW_TX_ALTERNATE_FUNC GPIO_AF8_UART4
                                        #undef UART4_HW_TX_PIN
                                        #define UART4_HW_TX_PIN ((uint16_t)PIN_1)

                                #elif UART4_HW_TX_PIN == PIN_12
                                        #define UART4_HW_TX_ALTERNATE_FUNC GPIO_AF8_UART4
                                        #undef UART4_HW_TX_PIN
                                        #define UART4_HW_TX_PIN ((uint16_t)PIN_12)

                                #else
                                        #error UART4_HW_TX_PIN HAVE WRONG PIN NUMBER
                                #endif
                        #else
                                #error "Wrong UART4_HW_TX_PORT "
                        #endif
                #endif

                #if defined UART4_HW_RX_PORT && defined UART4_HW_TX_PORT
                        #define UART4_HW_MODE (USART_CR1_TE |USART_CR1_RE)
                #elif defined UART4_HW_RX_PORT && !defined UART4_HW_TX_PORT
                        #define UART4_HW_MODE USART_CR1_RE)
                #elif defined !UART4_HW_RX_PORT && defined UART4_HW_TX_PORT
                        #define UART4_HW_MODE (USART_CR1_TE)
                #endif

        #endif

        #ifdef UART5_HW

                #if defined UART5_HW_CTS_PIN || defined UART5_HW_RTS_PIN

                        #if defined UART5_HW_CTS_PIN

                                #if UART5_HW_CTS_PORT == GPIOC_BASE_NS

                                        #if UART5_HW_CTS_PIN == PIN_9

                                                #define UART5_HW_CTS_ALTERNATE_FUNC GPIO_AF8_UART5
                                                #undef UART5_HW_CTS_PIN
                                                #define UART5_HW_CTS_PIN ((uint16_t)PIN_9)
                                        #else
                                                #error UART5_HW_CTS_PIN HAVE WRONG PIN NUMBER
                                        #endif
                                #else
                                        #error "Wrong UART5_HW_CTS_PORT "
                                #endif
                        #endif

                        #if defined UART5_HW_RTS_PIN

                                #if UART5_HW_RTS_PORT == GPIOC_BASE_NS

                                        #if UART5_HW_RTS_PIN == PIN_8

                                                #define UART5_HW_RTS_ALTERNATE_FUNC GPIO_AF8_UART5
                                                #undef UART5_HW_RTS_PIN
                                                #define UART5_HW_RTS_PIN ((uint16_t)PIN_8)

                                        #else
                                                #error UART5_HW_RTS_PIN HAVE WRONG PIN NUMBER
                                        #endif
                                #else
                                        #error "Wrong UART5_HW_RTS_PORT "
                                #endif
                        #endif


                        #if defined UART5_HW_RTS_PIN && defined UART5_HW_CTS_PIN
                                #define UART5_HW_FLOW_CONTROL (USART_CR3_RTSE | USART_CR3_CTSE)
                        #elif defined UART5_HW_RTS_PIN && !defined UART5_HW_CTS_PIN
                                #define UART5_HW_FLOW_CONTROL USART_CR3_RTSE
                        #elif !defined UART5_HW_RTS_PIN && defined UART5_HW_CTS_PIN
                                #define UART5_HW_FLOW_CONTROL USART_CR3_CTSE
                        #endif

                #else
                        #define UART5_HW_FLOW_CONTROL 0x00000000U
                #endif

                #if defined UART5_HW_RX_PORT && defined UART5_HW_RX_PIN

                        #if UART5_HW_RX_PORT == GPIOB_BASE_NS // UART5 RX - PB5  PB12 PB15 PD2

                                #if UART5_HW_RX_PIN == PIN_5

                                        #define UART5_HW_RX_ALTERNATE_FUNC GPIO_AF14_UART5
                                        #undef UART5_HW_RX_PIN
                                        #define UART5_HW_RX_PIN ((uint16_t)PIN_5)

                                #elif UART5_HW_RX_PIN == PIN_12
                                        #define UART5_HW_RX_ALTERNATE_FUNC GPIO_AF14_UART5
                                        #undef UART5_HW_RX_PIN
                                        #define UART5_HW_RX_PIN ((uint16_t)PIN_12)

                                #elif UART5_HW_RX_PIN == PIN_15
                                        #define UART5_HW_RX_ALTERNATE_FUNC GPIO_AF14_UART5
                                        #undef UART5_HW_RX_PIN
                                        #define UART5_HW_RX_PIN ((uint16_t)PIN_15)

                                #else
                                        #error UART5_HW_RX_PIN HAVE WRONG PIN NUMBER
                                #endif


                        #elif UART5_HW_RX_PORT == GPIOD_BASE_NS

                                #if UART5_HW_RX_PIN == PIN_2
                                        #define UART5_HW_RX_ALTERNATE_FUNC GPIO_AF8_UART5
                                        #undef UART5_HW_RX_PIN
                                        #define UART5_HW_RX_PIN ((uint16_t)PIN_2)
                                #else
                                        #error UART5_HW_RX_PIN HAVE WRONG PIN NUMBER
                                #endif

                        #else
                                #error "Wrong UART5_HW_RX_PORT "
                        #endif
                #endif

                #if defined UART5_HW_TX_PORT && defined UART5_HW_TX_PIN

                        #if UART5_HW_TX_PORT == GPIOB_BASE_NS // UART5  TX - PB3  PB6 PB13 PC12

                                #if UART5_HW_TX_PIN == PIN_3

                                        #define UART5_HW_TX_ALTERNATE_FUNC GPIO_AF14_UART5
                                        #undef UART5_HW_TX_PIN
                                        #define UART5_HW_TX_PIN ((uint16_t)PIN_3)

                                #elif UART5_HW_TX_PIN == PIN_6

                                      #define UART5_HW_TX_ALTERNATE_FUNC GPIO_AF14_UART5
                                      #undef UART5_HW_TX_PIN
                                      #define UART5_HW_TX_PIN ((uint16_t)PIN_6)

                                #elif UART5_HW_TX_PIN == PIN_13

                                      #define UART5_HW_TX_ALTERNATE_FUNC GPIO_AF14_UART5
                                      #undef UART5_HW_TX_PIN
                                      #define UART5_HW_TX_PIN ((uint16_t)PIN_13)

                                #else
                                        #error UART5_HW_TX_PIN HAVE WRONG PIN NUMBER
                                #endif


                        #elif UART5_HW_TX_PORT == GPIOC_BASE_NS

                                #if UART5_HW_TX_PIN == PIN_12

                                        #define UART5_HW_TX_ALTERNATE_FUNC GPIO_AF8_UART5
                                        #undef UART5_HW_TX_PIN
                                        #define UART5_HW_TX_PIN ((uint16_t)PIN_12)

                                #else
                                    #error UART5_HW_TX_PIN HAVE WRONG PIN NUMBER
                                #endif

                        #else
                                #error "Wrong UART5_HW_TX_PORT "
                        #endif
                #endif

                #if defined UART5_HW_RX_PORT && defined UART5_HW_TX_PORT
                        #define UART5_HW_MODE (USART_CR1_TE |USART_CR1_RE)
                #elif defined UART5_HW_RX_PORT && !defined UART5_HW_TX_PORT
                        #define UART5_HW_MODE USART_CR1_RE)
                #elif defined !UART5_HW_RX_PORT && defined UART5_HW_TX_PORT
                        #define UART5_HW_MODE (USART_CR1_TE)
                #endif

        #endif

        #ifdef UART6_HW

                #if defined UART6_HW_CTS_PIN || defined UART6_HW_RTS_PIN

                        #if defined UART6_HW_CTS_PIN

                                #if UART6_HW_CTS_PORT == GPIOB_BASE_NS

                                        #if UART6_HW_CTS_PIN == PIN_7

                                                #define UART6_HW_CTS_ALTERNATE_FUNC GPIO_AF6_USART6
                                                #undef UART6_HW_CTS_PIN
                                                #define UART6_HW_CTS_PIN ((uint16_t)PIN_7)

                                        #else
                                                #error UART6_HW_CTS_PIN HAVE WRONG PIN NUMBER
                                        #endif

                                #elif UART6_HW_CTS_PORT == GPIOG_BASE_NS

                                        #if UART6_HW_CTS_PIN == PIN_13

                                               #define UART6_HW_CTS_ALTERNATE_FUNC GPIO_AF7_USART6
                                               #undef UART6_HW_CTS_PIN
                                               #define UART6_HW_CTS_PIN ((uint16_t)PIN_13)

                                        #elif UART6_HW_CTS_PIN == PIN_15

                                               #define UART6_HW_CTS_ALTERNATE_FUNC GPIO_AF7_USART6
                                               #undef UART6_HW_CTS_PIN
                                               #define UART6_HW_CTS_PIN ((uint16_t)PIN_15)

                                        #else
                                               #error UART6_HW_CTS_PIN HAVE WRONG PIN NUMBER
                                        #endif

                                #else
                                        #error "Wrong UART6_HW_CTS_PORT "
                                #endif
                        #endif

                        #if defined UART6_HW_RTS_PIN

                                #if UART6_HW_RTS_PORT == GPIOG_BASE_NS

                                        #if UART6_HW_RTS_PIN == PIN_8

                                                #define UART6_HW_RTS_ALTERNATE_FUNC GPIO_AF7_USART6
                                                #undef UART6_HW_RTS_PIN
                                                #define UART6_HW_RTS_PIN ((uint16_t)PIN_8)

                                        #elif UART6_HW_RTS_PIN == PIN_12

                                                #define UART6_HW_RTS_ALTERNATE_FUNC GPIO_AF7_USART6
                                                #undef UART6_HW_RTS_PIN
                                                #define UART6_HW_RTS_PIN ((uint16_t)PIN_12)

                                        #else
                                                #error UART6_HW_RTS_PIN HAVE WRONG PIN NUMBER
                                        #endif
                                #else
                                        #error "Wrong UART6_HW_RTS_PORT "
                                #endif
                        #endif


                        #if defined UART6_HW_RTS_PIN && defined UART6_HW_CTS_PIN
                                #define UART6_HW_FLOW_CONTROL (USART_CR3_RTSE | USART_CR3_CTSE)
                        #elif defined UART6_HW_RTS_PIN && !defined UART6_HW_CTS_PIN
                                #define UART6_HW_FLOW_CONTROL USART_CR3_RTSE
                        #elif !defined UART6_HW_RTS_PIN && defined UART6_HW_CTS_PIN
                                #define UART6_HW_FLOW_CONTROL USART_CR3_CTSE
                        #endif

                #else
                        #define UART6_HW_FLOW_CONTROL 0x00000000U
                #endif

                #if defined UART6_HW_RX_PORT && defined UART6_HW_RX_PIN

                        #if UART6_HW_RX_PORT == GPIOB_BASE_NS // // UART6 RX - PB6 PC7 PG9

                                #if UART6_HW_RX_PIN == PIN_6

                                        #define UART6_HW_RX_ALTERNATE_FUNC GPIO_AF6_USART6
                                        #undef UART6_HW_RX_PIN
                                        #define UART6_HW_RX_PIN ((uint16_t)PIN_6)

                                #else
                                        #error UART6_HW_RX_PIN HAVE WRONG PIN NUMBER
                                #endif


                        #elif UART6_HW_RX_PORT == GPIOC_BASE_NS

                                #if UART6_HW_RX_PIN == PIN_7
                                        #define UART6_HW_RX_ALTERNATE_FUNC GPIO_AF7_USART6
                                        #undef UART6_HW_RX_PIN
                                        #define UART6_HW_RX_PIN ((uint16_t)PIN_7)
                                #else
                                        #error UART6_HW_RX_PIN HAVE WRONG PIN NUMBER
                                #endif

                        #elif UART6_HW_RX_PORT == GPIOG_BASE_NS

                                #if UART6_HW_RX_PIN == PIN_9
                                        #define UART6_HW_RX_ALTERNATE_FUNC GPIO_AF7_USART6
                                        #undef UART6_HW_RX_PIN
                                        #define UART6_HW_RX_PIN ((uint16_t)PIN_9)
                                #else
                                        #error UART6_HW_RX_PIN HAVE WRONG PIN NUMBER
                                #endif

                        #else
                                #error "Wrong UART6_HW_RX_PORT "
                        #endif
                #endif

                #if defined UART6_HW_TX_PORT && defined UART6_HW_TX_PIN

                        #if UART6_HW_TX_PORT == GPIOB_BASE_NS // TX - PB5 PC6 PG14

                                #if UART6_HW_TX_PIN == PIN_5

                                        #define UART6_HW_TX_ALTERNATE_FUNC GPIO_AF6_USART6
                                        #undef UART6_HW_TX_PIN
                                        #define UART6_HW_TX_PIN ((uint16_t)PIN_5

                                #else
                                        #error UART6_HW_TX_PIN HAVE WRONG PIN NUMBER
                                #endif


                        #elif UART6_HW_TX_PORT == GPIOC_BASE_NS

                                #if UART6_HW_TX_PIN == PIN_6

                                        #define UART6_HW_TX_ALTERNATE_FUNC GPIO_AF7_USART6
                                        #undef UART6_HW_TX_PIN
                                        #define UART6_HW_TX_PIN ((uint16_t)PIN_6)

                                #else
                                    #error UART6_HW_TX_PIN HAVE WRONG PIN NUMBER
                                #endif

                        #elif UART6_HW_TX_PORT == GPIOG_BASE_NS

                                #if UART6_HW_TX_PIN == PIN_14

                                        #define UART6_HW_TX_ALTERNATE_FUNC GPIO_AF7_USART6
                                        #undef UART6_HW_TX_PIN
                                        #define UART6_HW_TX_PIN ((uint16_t)PIN_14)

                                #else
                                    #error UART6_HW_TX_PIN HAVE WRONG PIN NUMBER
                                #endif

                        #else
                                #error "Wrong UART6_HW_TX_PORT "
                        #endif
                #endif

                #if defined UART6_HW_RX_PORT && defined UART6_HW_TX_PORT
                #define UART6_HW_MODE (USART_CR1_TE |USART_CR1_RE)
                #elif defined UART6_HW_RX_PORT && !defined UART6_HW_TX_PORT
                #define UART6_HW_MODE USART_CR1_RE)
                #elif defined !UART6_HW_RX_PORT && defined UART6_HW_TX_PORT
                #define UART6_HW_MODE (USART_CR1_TE)
                #endif

        #endif

#else
#error "this MCU not supported"
#endif


/** @brief Check if GPIO have alternate functions or not
  * @param port - i.e GPIOA, GPIOB .... GPIOH
  * @note  This macro should be used for get alternate function of GPIO pin.
  * @retval number of alternate function if retval < 0 this GPIO pin cant be used like choosed hw function
  */


#endif //GPIO_CHECK_H
