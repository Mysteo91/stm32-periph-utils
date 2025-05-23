//
// Created by user on 07.05.2025.
//
#include "uart.h"
#include "uart_gpio_check.h"
#include <string.h>
#include "stm32h5xx_hal.h"
#include "uart-it.h"


typedef enum {
    DMA_USING_FOR_NONE,
    DMA_USING_FOR_RX,
    DMA_USING_FOR_TX

} DMA_USING_FOR_Enum;

typedef struct {
    DMA_HandleTypeDef dmaHandleRx;
    DMA_HandleTypeDef dmaHandleTx;
    DMA_NodeTypeDef nodeRx;
    DMA_QListTypeDef listRx;
} dma_t;

typedef struct {
    UART_HandleTypeDef huart;
    uint8_t *lastWrtPnt;
    uint8_t countTC;
    dma_t dma;
    uartRxUserDataCb dataCb;
    uartRxUserErrorCb error_cb;

} uart_t;

#ifdef UART1_HW
uart_t uart1 = {
    .huart.Instance = USART1,
    .huart.Init = {
        .Mode = UART1_HW_MODE,
        .HwFlowCtl = UART1_HW_FLOW_CONTROL
    },
#ifdef UART1_HW_DMA_RX_CHANNEL
    .dma.dmaHandleRx = {
        .Instance = (DMA_Channel_TypeDef *) UART1_HW_DMA_RX_CHANNEL,
#ifdef UART1_HW_CIRCULAR
        .Init.Mode = DMA_LINKEDLIST_CIRCULAR
#else
        .Init.Mode = DMA_NORMAL
#endif
    },
#endif

#ifdef UART1_HW_DMA_TX_CHANNEL
    .dma.dmaHandleTx = {
        .Instance = (DMA_Channel_TypeDef *) UART1_HW_DMA_TX_CHANNEL
    },
#endif
};
#endif

#ifdef UART2_HW
uart_t uart2 = {
    .huart.Instance = USART2,
    .huart.Init = {
        .Mode = UART2_HW_MODE,
        .HwFlowCtl = UART2_HW_FLOW_CONTROL
    },
#ifdef UART2_HW_DMA_RX_CHANNEL
    .dma.dmaHandleRx = {
        .Instance = (DMA_Channel_TypeDef *) UART2_HW_DMA_RX_CHANNEL,
#ifdef UART2_HW_CIRCULAR
        .Init.Mode = DMA_LINKEDLIST_CIRCULAR
#else
        .Init.Mode = DMA_NORMAL
#endif

    },

#endif
#ifdef UART2_HW_DMA_TX_CHANNEL
    .dma.dmaHandleTx = {
        .Instance = (DMA_Channel_TypeDef *) UART2_HW_DMA_TX_CHANNEL
    },
#endif
};
#endif

#ifdef UART3_HW
uart_t uart3 = {

    .huart.Instance = USART3,
    .huart.Init = {
        .Mode = UART3_HW_MODE,
        .HwFlowCtl = UART3_HW_FLOW_CONTROL
    },
#ifdef UART3_HW_DMA_RX_CHANNEL
    .dma.dmaHandleRx = {
        .Instance = (DMA_Channel_TypeDef *) UART3_HW_DMA_RX_CHANNEL,
#ifdef UART3_HW_CIRCULAR
        .Init.Mode = DMA_LINKEDLIST_CIRCULAR
#else
        .Init.Mode = DMA_NORMAL
#endif
    },
#endif
#ifdef UART3_HW_DMA_TX_CHANNEL
    .dma.dmaHandleTx = {
        .Instance = (DMA_Channel_TypeDef *) UART3_HW_DMA_TX_CHANNEL
    },
#endif

};
#endif

#ifdef UART4_HW
uart_t uart4 = {
    .huart.Instance = USART4,
    .huart.Init = {
        .Mode = UART4_HW_MODE,
        .HwFlowCtl = UART4_HW_FLOW_CONTROL
    },
#ifdef UART4_HW_DMA_RX_CHANNEL
    .dma.dmaHandleRx = {
        .Instance = (DMA_Channel_TypeDef *) UART4_HW_DMA_RX_CHANNEL,
#ifdef UART4_HW_CIRCULAR
        .Init.Mode = DMA_LINKEDLIST_CIRCULAR
#else
        .Init.Mode = DMA_NORMAL
#endif
    },
#endif
#ifdef UART4_HW_DMA_TX_CHANNEL
    .dma.dmaHandleTx = {
        .Instance = (DMA_Channel_TypeDef *) UART4_HW_DMA_TX_CHANNEL
    },
#endif
};
#endif

#ifdef UART5_HW
uart_t uart5 = {
    .huart.Instance = UART5,
    .huart.Init = {
        .Mode = UART5_HW_MODE,
        .HwFlowCtl = UART5_HW_FLOW_CONTROL
    },
#ifdef UART5_HW_DMA_RX_CHANNEL
    .dma.dmaHandleRx = {
        .Instance = (DMA_Channel_TypeDef *) UART5_HW_DMA_RX_CHANNEL,
#ifdef UART5_HW_CIRCULAR
        .Init.Mode = DMA_LINKEDLIST_CIRCULAR
#else
        .Init.Mode = DMA_NORMAL
#endif
    },
#endif
#ifdef UART5_HW_DMA_TX_CHANNEL
    .dma.dmaHandleTx = {
        .Instance = (DMA_Channel_TypeDef *) UART5_HW_DMA_TX_CHANNEL
    },
#endif
};
#endif

#ifdef UART6_HW
uart_t uart6 = {
    .huart.Instance = USART6,
    .huart.Init = {
        .Mode = UART2_HW_MODE,
        .HwFlowCtl = UART6_HW_FLOW_CONTROL
    },
#ifdef UART6_HW_DMA_RX_CHANNEL
    .dma.dmaHandleRx = {
        .Instance =  (DMA_Channel_TypeDef *) UART6_HW_DMA_RX_CHANNEL,
#ifdef UART6_HW_CIRCULAR
        .Init.Mode = DMA_LINKEDLIST_CIRCULAR
#else
        .Init.Mode = DMA_NORMAL
#endif
    },
#endif
#ifdef UART6_HW_DMA_TX_CHANNEL
    .dma.dmaHandleTx = {
        .Instance = (DMA_Channel_TypeDef *) UART6_HW_DMA_TX_CHANNEL
    },
#endif
};
#endif


static void deinitUart(uart_t *uart);
static void enableClkGPIO(GPIO_TypeDef *port);
static void initUartGPIO(GPIO_TypeDef *port, uint32_t pin, uint8_t alternateFunction, uint8_t gpioSpeed);
static void initDmaForUART(DMA_HandleTypeDef *dmaHandle, uint32_t DMA_REQUEST, uint32_t DMA_CCR);
static void initDmaCircularForUART(DMA_HandleTypeDef *dmaHandle, uint32_t DMA_REQUEST, uint32_t DMA_CCR);
static void setPriorityDMA(DMA_Channel_TypeDef *dmaChannel, uint8_t priority);
static void resetUART(uart_t *uart);

DMA_HandleTypeDef *getDMAHalHandleByDMA(DMA_Channel_TypeDef *dma);

UART_HandleTypeDef *getUartHalHandleByUSART(USART_TypeDef *usart) {

#ifdef UART1_HW
    if (uart1.huart.Instance == usart) {
        return &uart1.huart;
    }
#endif
#ifdef UART2_HW
    if (uart2.huart.Instance == usart) {
        return &uart2.huart;
    }
#endif
#ifdef UART3_HW
    if (uart3.huart.Instance == usart) {
        return &uart3.huart;
    }
#endif
#ifdef UART4_HW
    if (uart4.huart.Instance == usart) {
        return &uart4.huart;
    }
#endif
#ifdef UART5_HW
    if (uart5.huart.Instance == usart) {
        return &uart5.huart;
    }
#endif
#ifdef UART6_HW
    if (uart6.huart.Instance == usart) {
        return &uart6.huart;
    }
#endif

    return NULL;
}

static UART_HandleTypeDef *getUartHalHandleByDMA(DMA_Channel_TypeDef *dma) {

#ifdef UART1_HW
    if (uart1.dma.dmaHandleRx.Instance == dma) {
        return &uart1.huart;
    }
    if (uart1.dma.dmaHandleTx.Instance == dma) {
        return &uart1.huart;
    }
#endif
#ifdef UART2_HW
    if (uart2.dma.dmaHandleRx.Instance == dma) {
        return &uart2.huart;
    }
    if (uart2.dma.dmaHandleTx.Instance == dma) {
        return &uart2.huart;
    }
#endif
#ifdef UART3_HW
    if(uart3.dma.dmaHandleRx.Instance == dma) {
        return &uart3.huart;
    }
    if (uart3.dma.dmaHandleTx.Instance == dma) {
        return &uart3.huart;
    }
#endif
#ifdef UART4_HW
    if(uart4.dma.dmaHandleRx.Instance == dma) {
        return &uart4.huart;
    }
    if (uart4.dma.dmaHandleTx.Instance == dma) {
        return &uart4.huart;
    }
#endif
#ifdef UART5_HW
    if (uart5.dma.dmaHandleRx.Instance == dma) {
        return &uart5.huart;
    }
    if (uart5.dma.dmaHandleTx.Instance == dma) {
        return &uart5.huart;
    }
#endif
#ifdef UART6_HW
    if(uart6.dma.dmaHandleRx.Instance == dma) {
        return &uart6.huart;
    }
    if (uart6.dma.dmaHandleTx.Instance == dma) {
        return &uart6.huart;
    }
#endif
    while (1) {
        //@todo ERROR_HANDLER for debug only
    }
}

DMA_HandleTypeDef *getDMAHalHandleByDMA(DMA_Channel_TypeDef *dma) {

#ifdef UART1_HW_DMA_RX_CHANNEL
    if (uart1.dma.dmaHandleRx.Instance == dma) {
        return &uart1.dma.dmaHandleRx;
    }
#endif

#ifdef UART2_HW_DMA_RX_CHANNEL
    if (uart2.dma.dmaHandleRx.Instance == dma) {
        return &uart2.dma.dmaHandleRx;
    }
#endif

#ifdef UART3_HW_DMA_RX_CHANNEL
        if(uart3.dma.dmaHandleRx.Instance == dma) {
            return &uart3.dma.dmaHandleRx;
        }
#endif

#ifdef UART4_HW_DMA_RX_CHANNEL
        if(uart4.dma.dmaHandleRx.Instance == dma) {
            return &uart4.dma.dmaHandleRx;
        }
#endif

#ifdef UART5_HW_DMA_RX_CHANNEL
    if (uart5.dma.dmaHandleRx.Instance == dma) {
        return &uart5.dma.dmaHandleRx;
    }
#endif

#ifdef UART6_HW_DMA_RX_CHANNEL
        if(uart6.dma.dmaHandleRx.Instance == dma) {
            return &uart6.dma.dmaHandleRx;
        }
#endif

#ifdef UART1_HW_DMA_TX_CHANNEL
    if (uart1.dma.dmaHandleTx.Instance == dma) {
        return &uart1.dma.dmaHandleTx;
    }
#endif

#ifdef UART2_HW_DMA_TX_CHANNEL
    if (uart2.dma.dmaHandleTx.Instance == dma) {
        return &uart2.dma.dmaHandleTx;
    }
#endif

#ifdef UART3_HW_DMA_TX_CHANNEL
    if(uart3.dma.dmaHandleTx.Instance == dma) {
        return &uart3.dma.dmaHandleTx;
    }
#endif

#ifdef UART4_HW_DMA_TX_CHANNEL
    if(uart4.dma.dmaHandleTx.Instance == dma) {
        return &uart4.dma.dmaHandleTx;
    }
#endif

#ifdef UART5_HW_DMA_TX_CHANNEL
    if (uart5.dma.dmaHandleTx.Instance == dma) {
        return &uart5.dma.dmaHandleTx;
    }
#endif

#ifdef UART6_HW_DMA_TX_CHANNEL
    if(uart6.dma.dmaHandleTx.Instance == dma) {
        return &uart6.dma.dmaHandleTx;
    }
#endif

    while (1) {
        //@todo ERROR_HANDLER for debug only
    }
}


static DMA_USING_FOR_Enum dmaUsingFor(DMA_Channel_TypeDef *dma) {

#ifdef UART1_HW
    if (uart1.dma.dmaHandleRx.Instance == dma) {
        return DMA_USING_FOR_RX;
    }
    if (uart1.dma.dmaHandleTx.Instance == dma) {
        return DMA_USING_FOR_TX;
    }
#endif
#ifdef UART2_HW
    if (uart2.dma.dmaHandleRx.Instance == dma) {
        return DMA_USING_FOR_RX;
    }
    if (uart2.dma.dmaHandleTx.Instance == dma) {
        return DMA_USING_FOR_TX;
    }
#endif
#ifdef UART3_HW
    if(uart3.dma.dmaHandleRx.Instance == dma) {
        return DMA_USING_FOR_RX;
    }
    if (uart3.dma.dmaHandleTx.Instance == dma) {
        return DMA_USING_FOR_TX;
    }
#endif
#ifdef UART4_HW
    if(uart4.dma.dmaHandleRx.Instance == dma) {
        return DMA_USING_FOR_RX;
    }
    if (uart4.dma.dmaHandleTx.Instance == dma) {
        return DMA_USING_FOR_TX;
    }
#endif
#ifdef UART5_HW
    if (uart5.dma.dmaHandleRx.Instance == dma) {
        return DMA_USING_FOR_RX;
    }
    if (uart5.dma.dmaHandleTx.Instance == dma) {
        return DMA_USING_FOR_TX;
    }
#endif
#ifdef UART6_HW
    if(uart6.dma.dmaHandleRx.Instance == dma) {
        return DMA_USING_FOR_RX;
    }
    if (uart6.dma.dmaHandleTx.Instance == dma) {
        return DMA_USING_FOR_TX;
    }
#endif
    return DMA_USING_FOR_NONE;

}


static uart_t *getUartByHalHandle(UART_HandleTypeDef *huart) {
#ifdef UART1_HW
    if (&uart1.huart == huart) {
        return &uart1;
    }
#endif
#ifdef UART2_HW
    if (&uart2.huart == huart) {
        return &uart2;
    }
#endif
#ifdef UART3_HW
    if (&uart3.huart == huart) {
        return &uart3;
    }
#endif
#ifdef UART4_HW
    if (&uart4.huart == huart) {
        return &uart4;
    }
#endif
#ifdef UART5_HW
    if (&uart5.huart == huart) {
        return &uart5;
    }
#endif
#ifdef UART6_HW
    if (&uart6.huart == huart) {
        return &uart6;
    }
#endif
    while (1) {
        //@todo ERROR_HANDLER for debug only
    }
}


bool uartStartReceive(USART_TypeDef *usart, const uint8_t *dst, uint16_t size) {
    UART_HandleTypeDef *huart = getUartHalHandleByUSART(usart);
    if (huart->hdmarx->Init.Mode == DMA_NORMAL) {
        __HAL_DMA_DISABLE_IT(huart->hdmarx, DMA_IT_HT);
        __HAL_DMA_ENABLE_IT(huart->hdmarx, DMA_IT_TC);
        return HAL_UART_Receive_DMA(huart, (uint8_t *) dst, size) == HAL_OK;
    } else {
        uart_t *uart = getUartByHalHandle(huart);
        uart->lastWrtPnt = dst;
        return HAL_UARTEx_ReceiveToIdle_DMA(huart, (uint8_t *) dst, size) == HAL_OK;
    }
}

bool uartStartTransmit(USART_TypeDef *usart, const uint8_t *dst, uint16_t size) {
    UART_HandleTypeDef *huart = getUartHalHandleByUSART(usart);

}

HAL_UART_StateTypeDef uartGetState(USART_TypeDef *usart) {
    UART_HandleTypeDef* huart = getUartHalHandleByUSART(usart);
    return HAL_UART_GetState(huart);
}


bool uartInit(USART_TypeDef *usart, uint32_t baudrate, uint8_t NVIC_Priority, uartRxUserDataCb dataCb, uartRxUserErrorCb errorCb) {
    UART_HandleTypeDef *huart = getUartHalHandleByUSART(usart);
    if (huart == NULL) {
        return false;
    }
    uart_t *uart = getUartByHalHandle(huart);
    uart->dataCb = dataCb;
    uart->error_cb = errorCb;
    huart->Instance = usart;
    huart->Init.BaudRate = baudrate;
    huart->Init.WordLength = UART_WORDLENGTH_8B;
    huart->Init.StopBits = UART_STOPBITS_1;
    huart->Init.Parity = UART_PARITY_NONE;
    huart->Init.Mode = UART_MODE_TX_RX;
    huart->Init.OverSampling = UART_OVERSAMPLING_16;
    huart->Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
    huart->Init.ClockPrescaler = UART_PRESCALER_DIV1;
    huart->AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
    if (HAL_UART_Init(huart) != HAL_OK) {
        return false;
    }
    if (HAL_UARTEx_SetTxFifoThreshold(huart, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK) {
        return false;
    }
    if (HAL_UARTEx_SetRxFifoThreshold(huart, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK) {
        return false;
    }
    if (HAL_UARTEx_DisableFifoMode(huart) != HAL_OK) {
        return false;
    }

    if (UART_WaitOnFlagUntilTimeout(huart, UART_FLAG_IDLE, RESET, HAL_GetTick(), 2000) == HAL_OK ) {
        __HAL_UART_CLEAR_FLAG(huart, UART_FLAG_IDLE);
        UART_WaitOnFlagUntilTimeout(huart, UART_FLAG_IDLE, SET, HAL_GetTick(), 2000);
    }

    if (usart == USART1) {
        HAL_NVIC_EnableIRQ(USART1_IRQn);
        HAL_NVIC_SetPriority(USART1_IRQn, NVIC_Priority, 0);
    } else if (usart == USART2) {
        HAL_NVIC_EnableIRQ(USART2_IRQn);
        HAL_NVIC_SetPriority(USART2_IRQn, NVIC_Priority, 0);
    } else if (usart == USART3) {
        HAL_NVIC_EnableIRQ(USART3_IRQn);
        HAL_NVIC_SetPriority(USART3_IRQn, NVIC_Priority, 0);
    } else if (usart == UART4) {
        HAL_NVIC_EnableIRQ(UART4_IRQn);
        HAL_NVIC_SetPriority(UART4_IRQn, NVIC_Priority, 0);
    } else if (usart == UART5) {
        HAL_NVIC_EnableIRQ(UART5_IRQn);
        HAL_NVIC_SetPriority(UART5_IRQn, NVIC_Priority, 0);
    } else if (usart == USART6) {
        HAL_NVIC_EnableIRQ(USART6_IRQn);
        HAL_NVIC_SetPriority(USART6_IRQn, NVIC_Priority, 0);
    }

    if (uart->dma.dmaHandleRx.Instance != NULL)
        setPriorityDMA(uart->dma.dmaHandleRx.Instance, NVIC_Priority);
    if (uart->dma.dmaHandleTx.Instance != NULL)
        setPriorityDMA(uart->dma.dmaHandleTx.Instance, NVIC_Priority);

    return true;
}

bool uartSetDMAPriority(USART_TypeDef *usart, uint32_t DMA_CCR) {

    UART_HandleTypeDef *huart = getUartHalHandleByUSART(usart);
    if (huart == NULL) {
        return false;
    }
    uart_t *uart = getUartByHalHandle(huart);
    if (huart->hdmarx != NULL) {
        if (huart->hdmarx->State != HAL_UART_STATE_RESET) {
            if (HAL_DMA_DeInit(huart->hdmarx) != HAL_OK) {
                return false;
            }
        }
    }
    if (uart->dma.dmaHandleRx.InitLinkedList.LinkedListMode == DMA_LINKEDLIST_CIRCULAR) {
        uart->dma.dmaHandleRx.InitLinkedList.Priority = DMA_CCR;
        HAL_DMAEx_List_Init(&uart->dma.dmaHandleRx);
    } else {
        uart->dma.dmaHandleRx.Init.Priority = DMA_CCR;
        HAL_DMA_Init(&uart->dma.dmaHandleRx);
    }

}

void HAL_UART_MspInit(UART_HandleTypeDef *huart) {


#ifdef UART1_HW
    if (huart->Instance == USART1) {
        __HAL_RCC_USART1_CLK_ENABLE();

#ifdef UART1_HW_RX_PIN
        enableClkGPIO((GPIO_TypeDef *) UART1_HW_RX_PORT);
        initUartGPIO((GPIO_TypeDef *) UART1_HW_RX_PORT, UART1_HW_RX_PIN, UART1_HW_RX_ALTERNATE_FUNC,
                     GPIO_SPEED_FREQ_LOW);
#ifdef UART1_HW_CIRCULAR

#else

#endif
#endif

#ifdef UART1_HW_TX_PIN
        enableClkGPIO((GPIO_TypeDef *) UART1_HW_TX_PORT);
        initUartGPIO((GPIO_TypeDef *) UART1_HW_TX_PORT, UART1_HW_TX_PIN, UART1_HW_TX_ALTERNATE_FUNC,
                     GPIO_SPEED_FREQ_LOW);

#endif

#if UART1_HW_FLOW_CONTROL == (USART_CR3_RTSE | USART_CR3_CTSE)
        enableClkGPIO((GPIO_TypeDef *)UART1_HW_RTS_PORT);
        initUartGPIO((GPIO_TypeDef *)UART1_HW_RTS_PORT, UART1_HW_RTS_PIN, UART1_HW_RTS_ALTERNATE_FUNC, GPIO_SPEED_FREQ_VERY_HIGH);
        enableClkGPIO((GPIO_TypeDef *)UART1_HW_CTS_PORT);
        initUartGPIO((GPIO_TypeDef *)UART1_HW_CTS_PORT, UART1_HW_CTS_PIN, UART1_HW_CTS_ALTERNATE_FUNC, GPIO_SPEED_FREQ_VERY_HIGH);
#elif UART1_HW_FLOW_CONTROL == USART_CR3_RTSE
        enableClkGPIO((GPIO_TypeDef *)UART1_HW_CTS_PORT);
        initUartGPIO((GPIO_TypeDef *)UART1_HW_CTS_PORT, UART1_HW_CTS_PIN, UART1_HW_CTS_ALTERNATE_FUNC, GPIO_SPEED_FREQ_VERY_HIGH);
#elif UART1_HW_FLOW_CONTROL == USART_CR3_CTSE
        enableClkGPIO((GPIO_TypeDef *)UART1_HW_RTS_PORT);
        initUartGPIO((GPIO_TypeDef *)UART1_HW_RTS_PORT, UART1_HW_RTS_PIN, UART1_HW_RTS_ALTERNATE_FUNC, GPIO_SPEED_FREQ_VERY_HIGH);
#endif


    } else if (huart->Instance == USART2) {
        __HAL_RCC_USART2_CLK_ENABLE();

#ifdef UART2_HW_RX_PIN
        enableClkGPIO((GPIO_TypeDef *) UART2_HW_RX_PORT);
        initUartGPIO((GPIO_TypeDef *) UART2_HW_RX_PORT, UART2_HW_RX_PIN, UART2_HW_RX_ALTERNATE_FUNC,
                     GPIO_SPEED_FREQ_LOW);
#endif

#ifdef UART2_HW_TX_PIN
        enableClkGPIO((GPIO_TypeDef *) UART2_HW_TX_PORT);
        initUartGPIO((GPIO_TypeDef *) UART2_HW_TX_PORT, UART2_HW_TX_PIN, UART2_HW_TX_ALTERNATE_FUNC,
                     GPIO_SPEED_FREQ_LOW);
#endif

#if UART2_HW_FLOW_CONTROL == (USART_CR3_RTSE | USART_CR3_CTSE)
        enableClkGPIO((GPIO_TypeDef *) UART2_HW_RTS_PORT);
        initUartGPIO((GPIO_TypeDef *) UART2_HW_RTS_PORT, UART2_HW_RTS_PIN, UART2_HW_RTS_ALTERNATE_FUNC,
                     GPIO_SPEED_FREQ_VERY_HIGH);
        enableClkGPIO((GPIO_TypeDef *) UART2_HW_CTS_PORT);
        initUartGPIO((GPIO_TypeDef *) UART2_HW_CTS_PORT, UART2_HW_CTS_PIN, UART2_HW_CTS_ALTERNATE_FUNC,
                     GPIO_SPEED_FREQ_VERY_HIGH);
#elif UART2_HW_FLOW_CONTROL == USART_CR3_RTSE
        enableClkGPIO((GPIO_TypeDef *)UART2_HW_CTS_PORT);
        initUartGPIO((GPIO_TypeDef *)UART2_HW_CTS_PORT, UART2_HW_CTS_PIN, UART2_HW_CTS_ALTERNATE_FUNC, GPIO_SPEED_FREQ_VERY_HIGH);
#elif UART2_HW_FLOW_CONTROL == USART_CR3_CTSE
        enableClkGPIO((GPIO_TypeDef *)UART2_HW_RTS_PORT);
        initUartGPIO((GPIO_TypeDef *)UART2_HW_RTS_PORT, UART2_HW_RTS_PIN, UART2_HW_RTS_ALTERNATE_FUNC, GPIO_SPEED_FREQ_VERY_HIGH);
#endif
    } else if (huart->Instance == USART3) {
        __HAL_RCC_USART3_CLK_ENABLE();

#ifdef UART3_HW_RX_PIN
        enableClkGPIO((GPIO_TypeDef *)UART3_HW_RX_PORT);
        initUartGPIO((GPIO_TypeDef *)UART3_HW_RX_PORT, UART3_HW_RX_PIN, UART3_HW_RX_ALTERNATE_FUNC, GPIO_SPEED_FREQ_LOW);
#endif

#ifdef UART3_HW_TX_PIN
        enableClkGPIO((GPIO_TypeDef *)UART3_HW_TX_PORT);
        initUartGPIO((GPIO_TypeDef *)UART3_HW_TX_PORT, UART3_HW_TX_PIN, UART3_HW_TX_ALTERNATE_FUNC, GPIO_SPEED_FREQ_LOW);
#endif

#if UART3_HW_FLOW_CONTROL == (USART_CR3_RTSE | USART_CR3_CTSE)
        enableClkGPIO((GPIO_TypeDef *)UART3_HW_RTS_PORT);
        initUartGPIO((GPIO_TypeDef *)UART3_HW_RTS_PORT, UART3_HW_RTS_PIN, UART3_HW_RTS_ALTERNATE_FUNC, GPIO_SPEED_FREQ_VERY_HIGH);
        enableClkGPIO((GPIO_TypeDef *)UART3_HW_CTS_PORT);
        initUartGPIO((GPIO_TypeDef *)UART3_HW_CTS_PORT, UART3_HW_CTS_PIN, UART3_HW_CTS_ALTERNATE_FUNC, GPIO_SPEED_FREQ_VERY_HIGH);
#elif UART3_HW_FLOW_CONTROL == USART_CR3_RTSE
        enableClkGPIO((GPIO_TypeDef *)UART3_HW_CTS_PORT);
        initUartGPIO((GPIO_TypeDef *)UART3_HW_CTS_PORT, UART3_HW_CTS_PIN, UART3_HW_CTS_ALTERNATE_FUNC, GPIO_SPEED_FREQ_VERY_HIGH);
#elif UART3_HW_FLOW_CONTROL == USART_CR3_CTSE
        enableClkGPIO((GPIO_TypeDef *)UART3_HW_RTS_PORT);
        initUartGPIO((GPIO_TypeDef *)UART3_HW_RTS_PORT, UART3_HW_RTS_PIN, UART3_HW_RTS_ALTERNATE_FUNC, GPIO_SPEED_FREQ_VERY_HIGH);
#endif
    } else if (huart->Instance == UART4) {
        __HAL_RCC_UART4_CLK_ENABLE();

#ifdef UART4_HW_RX_PIN
        enableClkGPIO((GPIO_TypeDef *)UART4_HW_RX_PORT);
        initUartGPIO((GPIO_TypeDef *)UART4_HW_RX_PORT, UART4_HW_RX_PIN, UART4_HW_RX_ALTERNATE_FUNC, GPIO_SPEED_FREQ_LOW);
#endif

#ifdef UART4_HW_TX_PIN
        enableClkGPIO((GPIO_TypeDef *)UART4_HW_TX_PORT);
        initUartGPIO((GPIO_TypeDef *)UART4_HW_TX_PORT, UART4_HW_TX_PIN, UART4_HW_TX_ALTERNATE_FUNC, GPIO_SPEED_FREQ_LOW);
#endif

#if UART4_HW_FLOW_CONTROL == (USART_CR3_RTSE | USART_CR3_CTSE)
        enableClkGPIO((GPIO_TypeDef *)UART4_HW_RTS_PORT);
        initUartGPIO((GPIO_TypeDef *)UART4_HW_RTS_PORT, UART4_HW_RTS_PIN, UART4_HW_RTS_ALTERNATE_FUNC, GPIO_SPEED_FREQ_VERY_HIGH);
        enableClkGPIO((GPIO_TypeDef *)UART4_HW_CTS_PORT);
        initUartGPIO((GPIO_TypeDef *)UART4_HW_CTS_PORT, UART4_HW_CTS_PIN, UART4_HW_CTS_ALTERNATE_FUNC, GPIO_SPEED_FREQ_VERY_HIGH);
#elif UART4_HW_FLOW_CONTROL == USART_CR3_RTSE
        enableClkGPIO((GPIO_TypeDef *)UART4_HW_CTS_PORT);
        initUartGPIO((GPIO_TypeDef *)UART4_HW_CTS_PORT, UART4_HW_CTS_PIN, UART4_HW_CTS_ALTERNATE_FUNC, GPIO_SPEED_FREQ_VERY_HIGH);
#elif UART4_HW_FLOW_CONTROL == USART_CR3_CTSE
        enableClkGPIO((GPIO_TypeDef *)UART4_HW_RTS_PORT);
        initUartGPIO((GPIO_TypeDef *)UART4_HW_RTS_PORT, UART4_HW_RTS_PIN, UART4_HW_RTS_ALTERNATE_FUNC, GPIO_SPEED_FREQ_VERY_HIGH);
#endif
    } else if (huart->Instance == UART5) {
        __HAL_RCC_UART5_CLK_ENABLE();

#ifdef UART5_HW_RX_PIN
        enableClkGPIO((GPIO_TypeDef *) UART5_HW_RX_PORT);
        initUartGPIO((GPIO_TypeDef *) UART5_HW_RX_PORT, UART5_HW_RX_PIN, UART5_HW_RX_ALTERNATE_FUNC,
                     GPIO_SPEED_FREQ_LOW);
#endif

#ifdef UART5_HW_TX_PIN
        enableClkGPIO((GPIO_TypeDef *) UART5_HW_TX_PORT);
        enableClkGPIO((GPIO_TypeDef *) UART5_HW_TX_PORT);

        initUartGPIO((GPIO_TypeDef *) UART5_HW_TX_PORT, UART5_HW_TX_PIN, UART5_HW_TX_ALTERNATE_FUNC,
                     GPIO_SPEED_FREQ_LOW);
#endif

#if UART5_HW_FLOW_CONTROL == (USART_CR3_RTSE | USART_CR3_CTSE)
        enableClkGPIO((GPIO_TypeDef *)UART5_HW_RTS_PORT);
        initUartGPIO((GPIO_TypeDef *)UART5_HW_RTS_PORT, UART5_HW_RTS_PIN, UART5_HW_RTS_ALTERNATE_FUNC, GPIO_SPEED_FREQ_VERY_HIGH);
        enableClkGPIO((GPIO_TypeDef *)UART5_HW_CTS_PORT);
        initUartGPIO((GPIO_TypeDef *)UART5_HW_CTS_PORT, UART5_HW_CTS_PIN, UART5_HW_CTS_ALTERNATE_FUNC, GPIO_SPEED_FREQ_VERY_HIGH);
#elif UART5_HW_FLOW_CONTROL == USART_CR3_RTSE
        enableClkGPIO((GPIO_TypeDef *)UART5_HW_CTS_PORT);
        initUartGPIO((GPIO_TypeDef *)UART5_HW_CTS_PORT, UART5_HW_CTS_PIN, UART5_HW_CTS_ALTERNATE_FUNC, GPIO_SPEED_FREQ_VERY_HIGH);
#elif UART5_HW_FLOW_CONTROL == USART_CR3_CTSE
        enableClkGPIO((GPIO_TypeDef *)UART5_HW_RTS_PORT);
        initUartGPIO((GPIO_TypeDef *)UART5_HW_RTS_PORT, UART5_HW_RTS_PIN, UART5_HW_RTS_ALTERNATE_FUNC, GPIO_SPEED_FREQ_VERY_HIGH);
#endif
    }

#endif

    uart_t *uart = getUartByHalHandle(huart);
    if (uart->dma.dmaHandleRx.Instance != NULL) {
        uint32_t dmaRequest = 0;
        //@todo in next release need to detectd GPDMA1 or GPDMA2 , because in current MCU GPDMA1_REQUEST equal GPDMA2_REQUEST but in next mcu its can be differents.
        if (uart->huart.Instance == USART1)
            dmaRequest = GPDMA1_REQUEST_USART1_RX;
        else if (uart->huart.Instance == USART2)
            dmaRequest = GPDMA1_REQUEST_USART2_RX;
        else if (uart->huart.Instance == USART3)
            dmaRequest = GPDMA1_REQUEST_USART3_RX;
        else if (uart->huart.Instance == UART4)
            dmaRequest = GPDMA1_REQUEST_UART4_RX;
        else if (uart->huart.Instance == UART5)
            dmaRequest = GPDMA1_REQUEST_UART5_RX;
        else if (uart->huart.Instance == USART6)
            dmaRequest = GPDMA1_REQUEST_USART6_RX;

        if (uart->dma.dmaHandleRx.Init.Mode == DMA_LINKEDLIST_CIRCULAR) {
            initDmaCircularForUART(&uart->dma.dmaHandleRx, dmaRequest, 0);
        } else {
            initDmaForUART(&uart->dma.dmaHandleRx, dmaRequest, 0);
        }
    }
    if (uart->dma.dmaHandleTx.Instance != NULL) {
        uint32_t dmaRequest = 0;
        //@todo in next release need to detectd GPDMA1 or GPDMA2 , because in current MCU GPDMA1_REQUEST equal GPDMA2_REQUEST but in next mcu its can be differents.
        if (uart->huart.Instance == USART1)
            dmaRequest = GPDMA1_REQUEST_USART1_TX;
        else if (uart->huart.Instance == USART2)
            dmaRequest = GPDMA1_REQUEST_USART2_TX;
        else if (uart->huart.Instance == USART3)
            dmaRequest = GPDMA1_REQUEST_USART3_TX;
        else if (uart->huart.Instance == UART4)
            dmaRequest = GPDMA1_REQUEST_UART4_TX;
        else if (uart->huart.Instance == UART5)
            dmaRequest = GPDMA1_REQUEST_UART5_TX;
        else if (uart->huart.Instance == USART6)
            dmaRequest = GPDMA1_REQUEST_USART6_TX;

        initDmaForUART(&uart->dma.dmaHandleTx, dmaRequest, 0);
    }

}

void deinitUart(uart_t *uart) {
    if (uart == NULL)
        return;
}

static void enableClkGPIO(GPIO_TypeDef *port) {
    if (port == GPIOA) {
        __HAL_RCC_GPIOA_CLK_ENABLE();
    } else if (port == GPIOB) {
        __HAL_RCC_GPIOB_CLK_ENABLE();
    } else if (port == GPIOC) {
        __HAL_RCC_GPIOC_CLK_ENABLE();
    } else if (port == GPIOD) {
        __HAL_RCC_GPIOD_CLK_ENABLE();
    } else if (port == GPIOE) {
        __HAL_RCC_GPIOE_CLK_ENABLE();
    } else if (port == GPIOH) {
        __HAL_RCC_GPIOH_CLK_ENABLE();
    }
}


void initUartGPIO(GPIO_TypeDef *port, uint32_t pin, uint8_t alternateFunction, uint8_t gpioSpeed) {

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin = pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = gpioSpeed;
    GPIO_InitStruct.Alternate = alternateFunction;
    HAL_GPIO_Init(port, &GPIO_InitStruct);

}


void initDmaForUART(DMA_HandleTypeDef *dmaHandle, uint32_t DMA_REQUEST, uint32_t DMA_CCR) {
    dmaHandle->Init.Request = DMA_REQUEST;
    dmaHandle->Init.BlkHWRequest = DMA_BREQ_SINGLE_BURST;

    if (dmaUsingFor(dmaHandle->Instance) == DMA_USING_FOR_TX) {
        dmaHandle->Init.Direction = DMA_MEMORY_TO_PERIPH;
        dmaHandle->Init.SrcInc = DMA_SINC_INCREMENTED;
        dmaHandle->Init.DestInc = DMA_DINC_FIXED;
        dmaHandle->Init.SrcDataWidth = DMA_SRC_DATAWIDTH_BYTE;
        dmaHandle->Init.DestDataWidth = DMA_DEST_DATAWIDTH_BYTE;
        dmaHandle->Init.Priority = DMA_CCR;
        dmaHandle->Init.SrcBurstLength = 1;
        dmaHandle->Init.DestBurstLength = 1;
        dmaHandle->Init.TransferAllocatedPort = DMA_SRC_ALLOCATED_PORT1 | DMA_DEST_ALLOCATED_PORT0;
        dmaHandle->Init.TransferEventMode = DMA_TCEM_BLOCK_TRANSFER;
        if (HAL_DMA_Init(dmaHandle) != HAL_OK) {
            //@todo for debugging only
            while (1) {

            }
        }
        UART_HandleTypeDef *huart = getUartHalHandleByDMA(dmaHandle->Instance);
        __HAL_LINKDMA(huart, hdmatx, *dmaHandle);

        if (HAL_DMA_ConfigChannelAttributes(dmaHandle, DMA_CHANNEL_NPRIV) != HAL_OK) {
            //@todo for debugging only
            while (1) {

            }
        }
    } else if (dmaUsingFor(dmaHandle->Instance) == DMA_USING_FOR_RX) {
        dmaHandle->Init.Direction = DMA_PERIPH_TO_MEMORY;
        dmaHandle->Init.SrcInc = DMA_SINC_FIXED;
        dmaHandle->Init.DestInc = DMA_DINC_INCREMENTED;
        dmaHandle->Init.SrcDataWidth = DMA_SRC_DATAWIDTH_BYTE;
        dmaHandle->Init.DestDataWidth = DMA_DEST_DATAWIDTH_BYTE;
        dmaHandle->Init.Priority = DMA_CCR;
        dmaHandle->Init.SrcBurstLength = 1;
        dmaHandle->Init.DestBurstLength = 1;
        dmaHandle->Init.TransferAllocatedPort = DMA_SRC_ALLOCATED_PORT0 | DMA_DEST_ALLOCATED_PORT1;
        dmaHandle->Init.TransferEventMode = DMA_TCEM_BLOCK_TRANSFER;
        if (HAL_DMA_Init(dmaHandle) != HAL_OK) {
            //@todo for debugging only
            while (1) {

            }
        }
        UART_HandleTypeDef *huart = getUartHalHandleByDMA(dmaHandle->Instance);
        __HAL_LINKDMA(huart, hdmarx, *dmaHandle);

        if (HAL_DMA_ConfigChannelAttributes(dmaHandle, DMA_CHANNEL_NPRIV) != HAL_OK) {
            //@todo for debugging only
            while (1) {

            }
        }
    }
}

void initDmaCircularForUART(DMA_HandleTypeDef *dmaHandle, uint32_t DMA_REQUEST, uint32_t DMA_CCR) {
    dmaHandle->Init.Request = DMA_REQUEST;
    dmaHandle->Init.BlkHWRequest = DMA_BREQ_SINGLE_BURST;
    UART_HandleTypeDef *huart = getUartHalHandleByDMA(dmaHandle->Instance);
    uart_t *uart = getUartByHalHandle(huart);
    DMA_NodeConfTypeDef NodeConfig = {0};

    NodeConfig.NodeType = DMA_GPDMA_LINEAR_NODE;
    NodeConfig.Init.Request = DMA_REQUEST;
    NodeConfig.Init.BlkHWRequest = DMA_BREQ_SINGLE_BURST;
    NodeConfig.Init.Direction = DMA_PERIPH_TO_MEMORY;
    NodeConfig.Init.SrcInc = DMA_SINC_FIXED;
    NodeConfig.Init.DestInc = DMA_DINC_INCREMENTED;
    NodeConfig.Init.SrcDataWidth = DMA_SRC_DATAWIDTH_BYTE;
    NodeConfig.Init.DestDataWidth = DMA_DEST_DATAWIDTH_BYTE;
    NodeConfig.Init.SrcBurstLength = 1;
    NodeConfig.Init.DestBurstLength = 1;
    NodeConfig.Init.TransferAllocatedPort = DMA_SRC_ALLOCATED_PORT0 | DMA_DEST_ALLOCATED_PORT1;
    NodeConfig.Init.TransferEventMode = DMA_TCEM_BLOCK_TRANSFER;
    NodeConfig.Init.Mode = DMA_NORMAL;
    NodeConfig.TriggerConfig.TriggerPolarity = DMA_TRIG_POLARITY_MASKED;
    NodeConfig.DataHandlingConfig.DataExchange = DMA_EXCHANGE_NONE;
    NodeConfig.DataHandlingConfig.DataAlignment = DMA_DATA_RIGHTALIGN_ZEROPADDED;
    if (HAL_DMAEx_List_BuildNode(&NodeConfig, &uart->dma.nodeRx) != HAL_OK) {
        while (1) {
            //@todo ERROR handler
        }
    }

    if (HAL_DMAEx_List_InsertNode(&uart->dma.listRx, NULL, &uart->dma.nodeRx) != HAL_OK) {
        while (1) {
            //@todo ERROR handler
        }
    }

    if (HAL_DMAEx_List_SetCircularMode(&uart->dma.listRx) != HAL_OK) {
        while (1) {
            //@todo ERROR handler
        }
    }


    dmaHandle->InitLinkedList.Priority = DMA_CCR;
    dmaHandle->InitLinkedList.LinkStepMode = DMA_LSM_FULL_EXECUTION;
    dmaHandle->InitLinkedList.LinkAllocatedPort = DMA_LINK_ALLOCATED_PORT1;
    dmaHandle->InitLinkedList.TransferEventMode = DMA_TCEM_BLOCK_TRANSFER;
    dmaHandle->InitLinkedList.LinkedListMode = DMA_LINKEDLIST_CIRCULAR;
    if (HAL_DMAEx_List_Init(dmaHandle) != HAL_OK) {
        while (1) {
            //@todo ERROR handler
        }
    }

    if (HAL_DMAEx_List_LinkQ(dmaHandle, &uart->dma.listRx) != HAL_OK) {
        while (1) {
            //@todo ERROR handler
        }
    }

    __HAL_LINKDMA(huart, hdmarx, *dmaHandle);

    if (HAL_DMA_ConfigChannelAttributes(dmaHandle, DMA_CHANNEL_NPRIV) != HAL_OK) {
        while (1) {
            //@todo ERROR handler
        }
    }
}

void setPriorityDMA(DMA_Channel_TypeDef *dmaChannel, uint8_t priority) {
    if (dmaChannel == GPDMA1_Channel0) {
        HAL_NVIC_SetPriority(GPDMA1_Channel0_IRQn, priority, 0);
        HAL_NVIC_EnableIRQ(GPDMA1_Channel0_IRQn);
    } else if (dmaChannel == GPDMA1_Channel1) {
        HAL_NVIC_SetPriority(GPDMA1_Channel1_IRQn, priority, 0);
        HAL_NVIC_EnableIRQ(GPDMA1_Channel1_IRQn);
    } else if (dmaChannel == GPDMA1_Channel2) {
        HAL_NVIC_SetPriority(GPDMA1_Channel2_IRQn, priority, 0);
        HAL_NVIC_EnableIRQ(GPDMA1_Channel2_IRQn);
    } else if (dmaChannel == GPDMA1_Channel3) {
        HAL_NVIC_SetPriority(GPDMA1_Channel3_IRQn, priority, 0);
        HAL_NVIC_EnableIRQ(GPDMA1_Channel3_IRQn);
    } else if (dmaChannel == GPDMA1_Channel4) {
        HAL_NVIC_SetPriority(GPDMA1_Channel4_IRQn, priority, 0);
        HAL_NVIC_EnableIRQ(GPDMA1_Channel4_IRQn);
    } else if (dmaChannel == GPDMA1_Channel5) {
        HAL_NVIC_SetPriority(GPDMA1_Channel5_IRQn, priority, 0);
        HAL_NVIC_EnableIRQ(GPDMA1_Channel5_IRQn);
    } else if (dmaChannel == GPDMA1_Channel6) {
        HAL_NVIC_SetPriority(GPDMA1_Channel6_IRQn, priority, 0);
        HAL_NVIC_EnableIRQ(GPDMA1_Channel6_IRQn);
    } else if (dmaChannel == GPDMA1_Channel7) {
        HAL_NVIC_SetPriority(GPDMA1_Channel7_IRQn, priority, 0);
        HAL_NVIC_EnableIRQ(GPDMA1_Channel7_IRQn);
    } else if (dmaChannel == GPDMA2_Channel0) {
        HAL_NVIC_SetPriority(GPDMA2_Channel0_IRQn, priority, 0);
        HAL_NVIC_EnableIRQ(GPDMA2_Channel0_IRQn);
    } else if (dmaChannel == GPDMA2_Channel1) {
        HAL_NVIC_SetPriority(GPDMA2_Channel1_IRQn, priority, 0);
        HAL_NVIC_EnableIRQ(GPDMA2_Channel1_IRQn);
    } else if (dmaChannel == GPDMA2_Channel2) {
        HAL_NVIC_SetPriority(GPDMA2_Channel2_IRQn, priority, 0);
        HAL_NVIC_EnableIRQ(GPDMA2_Channel2_IRQn);
    } else if (dmaChannel == GPDMA2_Channel3) {
        HAL_NVIC_SetPriority(GPDMA2_Channel3_IRQn, priority, 0);
        HAL_NVIC_EnableIRQ(GPDMA2_Channel3_IRQn);
    } else if (dmaChannel == GPDMA2_Channel4) {
        HAL_NVIC_SetPriority(GPDMA2_Channel4_IRQn, priority, 0);
        HAL_NVIC_EnableIRQ(GPDMA2_Channel4_IRQn);
    } else if (dmaChannel == GPDMA2_Channel5) {
        HAL_NVIC_SetPriority(GPDMA2_Channel5_IRQn, priority, 0);
        HAL_NVIC_EnableIRQ(GPDMA2_Channel5_IRQn);
    } else if (dmaChannel == GPDMA2_Channel6) {
        HAL_NVIC_SetPriority(GPDMA2_Channel6_IRQn, priority, 0);
        HAL_NVIC_EnableIRQ(GPDMA2_Channel6_IRQn);
    } else if (dmaChannel == GPDMA2_Channel7) {
        HAL_NVIC_SetPriority(GPDMA2_Channel7_IRQn, priority, 0);
        HAL_NVIC_EnableIRQ(GPDMA2_Channel7_IRQn);
    }
}

void resetUART(uart_t *uart) {
    uart->countTC = 0;
    uint8_t* tmpPnt = uart->huart.pRxBuffPtr;
    uint16_t tmpSize = uart->huart.RxXferSize;
    uart->lastWrtPnt = uart->huart.pRxBuffPtr;
    HAL_UART_DMAStop(&uart->huart);
    uartStartReceive(uart->huart.Instance, tmpPnt, tmpSize);
}


static void handleCircularUart(uart_t *uart, uint16_t size) {
    if (uart->huart.RxEventType == HAL_UART_RXEVENT_TC) {
        uart->countTC++;
        return;
    } else if (uart->huart.RxEventType == HAL_UART_RXEVENT_IDLE) {

        if (uart->countTC > 1) {
            resetUART(uart);
            return;
        }

        uart->countTC = 0;
        uint8_t *tmpPos = uart->lastWrtPnt;
        uint32_t realSize = 0;
        bool overHead = false;

        if (uart->lastWrtPnt < (uart->huart.pRxBuffPtr + size)) {
            realSize = size - (uart->lastWrtPnt - uart->huart.pRxBuffPtr);
            uart->lastWrtPnt += realSize;
        } else {
            overHead = true;
            realSize = uart->huart.pRxBuffPtr + uart->huart.RxXferSize - uart->lastWrtPnt + size;
            uart->lastWrtPnt = uart->huart.pRxBuffPtr + size;
        }

        if (uart->lastWrtPnt == uart->huart.pRxBuffPtr + size) {
            uart->lastWrtPnt = uart->huart.pRxBuffPtr;
        }

        if (overHead == false) {
            uart->dataCb(tmpPos, realSize, NULL, 0);
        } else {
            uart->dataCb(tmpPos, uart->huart.pRxBuffPtr + size - tmpPos, uart->huart.pRxBuffPtr, size);
        }
    }
}


void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t size) {

    uart_t *uart = getUartByHalHandle(huart);
    handleCircularUart(uart, size);

}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    uart_t *uart = getUartByHalHandle(huart);
    uart->dataCb((uint8_t *) huart->pRxBuffPtr, huart->RxXferSize, NULL, 0);
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart) {


}



