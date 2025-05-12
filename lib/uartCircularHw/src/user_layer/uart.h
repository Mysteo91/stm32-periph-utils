//
// Created by user on 07.05.2025.
//

#ifndef UARTCIRCULARHW_H
#define UARTCIRCULARHW_H

#include "stdbool.h"
#include "stm32h5xx.h"

/**
  * @brief  Function for initialization UART
  * @note If dmaRx or dmaTx not using use NULL for this args
  * @param  NVIC_Priority This parameter can be from 0 .. 15. Where 0 - highest priority
  * @note   default priority for DMA Channel is DMA_LOW_PRIORITY_LOW_WEIGHT for change it use @rmtoll uartSetDMAPriority
  * @retval true if init done
  */

bool uartInit(USART_TypeDef *usart, uint32_t baudrate, const
                uint8_t NVIC_Priority);


/**
  * @brief  Function for change DMA_CHANNEL_PRIORITY
  * @note If DMA Ongoing it will be stopped and after configuration rerun
  * @param  DMA_CCR can be 0x00000000U: low priority, low weight
                      * DMA_CCR_PRIO_0 : low priority, mid weight
                      * DMA_CCR_PRIO_1 : low priority, high weight
                      * DMA_CCR_PRIO : high priority
  * @note   default priority for DMA Channel is DMA_LOW_PRIORITY_LOW_WEIGHT for change it use @rmtoll uartSetDMAPriority
  * @retval true if init done
  */

bool uartSetDMAPriority(USART_TypeDef *usart, uint32_t DMA_CCR);

bool uartStartReceive(USART_TypeDef *usart, const uint8_t* dst, uint16_t size);

#endif //UARTCIRCULARHW_H
