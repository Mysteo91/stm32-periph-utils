//
// Created by user on 07.05.2025.
//

#ifndef UARTCIRCULARHW_H
#define UARTCIRCULARHW_H

#include "stdbool.h"
#include "stm32h5xx.h"

/**
  * @brief  User Rx Data Callback
  * @note   if Uart Mode is Circular it is possible  the situation of fragmentation data in two blocks
  * so first part data placed in dataStartAddress with len - dataLen , and second part placed in dataContinuesAddress with dataContinuesLen
  * @param  dataStartAddress - first fragment of data
  * @param  dataContinuesAddress - second fragment of data or NULL
  * @note Please do not call this function inside uartRxUserDataCb
  */

typedef void (*uartRxUserDataCb)(uint8_t* dataStartAddress, uint16_t dataLen, uint8_t* dataContinuesAddress,  uint16_t dataContinuesLen);


/**
  * @brief  User Rx Error Callback
  * @note   use this function for notice your application that uart got error.
  * The main program must understand that a problem has occurred and it may be necessary to resend some data to the peripheral device and receive a response.
  * @note Please do not call this function inside uartRxUserDataCb or  uartRxUserErrorCb
  */

typedef void (*uartRxUserErrorCb)(void);

/**
  * @brief  Function for initialization UART
  * @note If dmaRx or dmaTx not using use NULL for this args
  * @param  NVIC_Priority This parameter can be from 0 .. 15. Where 0 - highest priority
  * @param dataCb
  * @param errorCb
  * @note   default priority for DMA Channel is DMA_LOW_PRIORITY_LOW_WEIGHT for change it use @rmtoll uartSetDMAPriority
  * @retval true if init done
  */

bool uartInit(USART_TypeDef *usart, uint32_t baudrate, uint8_t NVIC_Priority, uartRxUserDataCb dataCb, uartRxUserErrorCb errorCb);


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



/**
  * @brief  Function for initiate receive
  * @note  For circular mode please allocate dst buffer with size equal 2 * MAX_SIZE_MESSAGE_FROM_DEVICE
  * For CIRCULAR UART uartStartReceive should be called  :
  * 1. after ready of main program to receive data
  * 2. after got uartError callback and handling it in main app.
  * For NON_CIRCUILAR it should be called:
  * 1. after ready of main program to receive data
  * 2. after got uartError callback and handling it in main app.
  * 3. after got data receive callback and handling it in main app.
  * @note Please do not call this function inside uartRxUserDataCb or  uartRxUserErrorCb
  *
  * @retval true if init done
  */

bool uartStartReceive(USART_TypeDef *usart, const uint8_t* dst, uint16_t size);

bool uartStartTransmit(USART_TypeDef *usart, const uint8_t* dst, uint16_t size);

HAL_UART_StateTypeDef uartGetState(USART_TypeDef *usart);

#endif //UARTCIRCULARHW_H
