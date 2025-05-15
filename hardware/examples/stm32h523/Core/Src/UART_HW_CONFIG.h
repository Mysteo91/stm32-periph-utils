//
// Created by user on 08.05.2025.
//

#ifndef UART_HW_CONFIG_H
#define UART_HW_CONFIG_H

#if STM32H523xx
#include "stm32h523xx.h"

/**
  ******************************************************************************
  * @file    UART_HW_CONFIG_template.h
  * @brief   This file provides defines for the configuration
  *          of the UARTs.
  ******************************************************************************
  * @attention
  *
  * NON_CIRCULAR mode recommended for devices that using Protocol with fixed data size
  * and for which the request-response mode is clearly implemented
  *
  * For other situation please use Circular-Mode. This mode provides non-stop data reception until the user stops the receiving
  * or until an error occurs in the communication protocol.
  *
  ******************************************************************************
  */


#define PIN_0                 0x0001
#define PIN_1                 0x0002
#define PIN_2                 0x0004
#define PIN_3                 0x0008
#define PIN_4                 0x0010
#define PIN_5                 0x0020
#define PIN_6                 0x0040
#define PIN_7                 0x0080
#define PIN_8                 0x0100
#define PIN_9                 0x0200
#define PIN_10                0x0400
#define PIN_11                0x0800
#define PIN_12                0x1000
#define PIN_13                0x2000
#define PIN_14                0x4000
#define PIN_15                0x8000

/* Uncomment required lines for using UART
 * for PORT choose GPIOx_BASE_NS matching the pin port
 * for PIN choose PIN_x matching pin number
 * i.e for UART1 RX PB7
 * #define UART1_HW_RX_PORT GPIOB_BASE_NS
 * #define UART1_HW_RX_PIN PIN_7
 *
 * if some part GPIO of UART not using please not define it
 */

#define UART1_HW   // UART1 RX - PA10  PB7  PB15; TX - PA9 PA15 PB6 PB14
#define UART1_HW_RX_PORT GPIOB_BASE_NS
#define UART1_HW_RX_PIN  PIN_15
#define UART1_HW_TX_PORT GPIOB_BASE_NS
#define UART1_HW_TX_PIN  PIN_14
//#define UART1_HW_CTS_PORT GPIOx_BASE_NS
//#define UART1_HW_CTS_PIN  PIN_x
//#define UART1_HW_RTS_PORT GPIOx_BASE_NS
//#define UART1_HW_RTS_PIN  PIN_x
#define UART1_HW_DMA_RX_CHANNEL GPDMA1_Channel0_BASE_NS
#define UART1_HW_DMA_TX_CHANNEL GPDMA1_Channel1_BASE_NS
#define UART1_HW_CIRCULAR



#define UART2_HW   // UART2 RX - PA3 PD6 ; TX - PA2  PB0  PD5
#define UART2_HW_RX_PORT GPIOA_BASE_NS
#define UART2_HW_RX_PIN  PIN_3
#define UART2_HW_TX_PORT GPIOA_BASE_NS
#define UART2_HW_TX_PIN  PIN_2
#define UART2_HW_CTS_PORT GPIOA_BASE_NS
#define UART2_HW_CTS_PIN  PIN_0
#define UART2_HW_RTS_PORT GPIOA_BASE_NS
#define UART2_HW_RTS_PIN  PIN_1
#define UART2_HW_DMA_RX_CHANNEL  GPDMA1_Channel2_BASE_NS
#define UART2_HW_DMA_TX_CHANNEL  GPDMA1_Channel3_BASE_NS
#define UART2_HW_CIRCULAR



//#define UART3_HW   // UART3 RX - PB1  PC4 PC11 PD9; TX - PB10  PC10 PD8
//#define UART3_HW_RX_PORT GPIOx_BASE_NS
//#define UART3_HW_RX_PIN  PIN_x
//#define UART3_HW_TX_PORT GPIOx_BASE_NS
//#define UART3_HW_TX_PIN  PIN_x
//#define UART3_HW_CTS_PORT GPIOx_BASE_NS
//#define UART3_HW_CTS_PIN  PIN_x
//#define UART3_HW_RTS_PORT GPIOx_BASE_NS
//#define UART3_HW_RTS_PIN  PIN_x
//#define UART3_HW_DMA_RX_CHANNEL GPDMAx_Channelx_BASE_NS
//#define UART3_HW_DMA_TX_CHANNEL GPDMAx_Channelx_BASE_NS
//#define UART3_HW_CIRCULAR



//#define UART4_HW  // UART4 RX - PA11 PA1 PB8 PC11 PD0 PD11; TX - PA12 PA0 PB9 PC10 PD1 PD12
//#define UART4_HW_RX_PORT GPIOx_BASE_NS
//#define UART4_HW_RX_PIN  PIN_x
//#define UART4_HW_TX_PORT GPIOx_BASE_NS
//#define UART4_HW_TX_PIN  PIN_x
//#define UART4_HW_CTS_PORT GPIOx_BASE_NS
//#define UART4_HW_CTS_PIN  PIN_x
//#define UART4_HW_RTS_PORT GPIOx_BASE_NS
//#define UART4_HW_RTS_PIN  PIN_x
//#define UART4_HW_DMA_RX_CHANNEL GPDMAx_Channelx_BASE_NS
//#define UART4_HW_DMA_TX_CHANNEL GPDMAx_Channelx_BASE_NS
//#define UART4_HW_CIRCULAR


#define UART5_HW   // UART5 RX - PB5  PB12 PB15 PD2; TX - PB3  PB6 PB13 PC12
#define UART5_HW_RX_PORT GPIOB_BASE_NS
#define UART5_HW_RX_PIN  PIN_12
#define UART5_HW_TX_PORT GPIOB_BASE_NS
#define UART5_HW_TX_PIN  PIN_13
//#define UART5_HW_CTS_PORT GPIOx_BASE_NS
//#define UART5_HW_CTS_PIN  PIN_x
//#define UART5_HW_RTS_PORT GPIOx_BASE_NS
//#define UART5_HW_RTS_PIN  PIN_x
#define UART5_HW_DMA_RX_CHANNEL GPDMA1_Channel4_BASE_NS
#define UART5_HW_DMA_TX_CHANNEL GPDMA1_Channel5_BASE_NS
#define UART5_HW_CIRCULAR

//#define UART6_HW   // UART6 RX - PB6 PC7 PG9; TX - PB5 PC6 PG14
//#define UART6_HW_RX_PORT GPIOx_BASE_NS
//#define UART6_HW_RX_PIN  PIN_x
//#define UART6_HW_TX_PORT GPIOx_BASE_NS
//#define UART6_HW_TX_PIN  PIN_x
//#define UART6_HW_CTS_PORT GPIOx_BASE_NS
//#define UART6_HW_CTS_PIN  PIN_x
//#define UART6_HW_RTS_PORT GPIOx_BASE_NS
//#define UART6_HW_RTS_PIN  PIN_x
//#define UART6_HW_DMA_RX_CHANNEL GPDMAx_Channelx_BASE_NS
//#define UART6_HW_DMA_TX_CHANNEL GPDMAx_Channelx_BASE_NS
//#define UART6_HW_CIRCULAR


#include "uart_gpio_check.h"
#include "uart_dma.h"

#else
#error "This MCU not supported"
#endif


#endif //UART_HW_CONFIG_H
