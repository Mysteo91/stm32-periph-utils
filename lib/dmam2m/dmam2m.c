//
// Created by user on 19.02.2025.
//

#include "gpdma.h"

#include "dmam2m.h"

typedef enum {
    DMA_COPY_NO_INIT,
    DMA_COPY_SOLO,
    DMA_COPY_SPLIT_IT,
    DMA_COPY_WITHOUT_IT,
}dma_copy_type_enum;

typedef struct {
    DMA_HandleTypeDef dmaHalChannel;
    dma_copy_type_enum type;
    DMA_HandleTypeDef* pairOfDMA;  /// use only for DMA_SPLIT type
    bool isBusy;
    uint16_t transmitSize;
}dma_t;


dma_t dma_handle[DMA_CHANNEL_USING];

static uint8_t dmaHalAssigned = 0;


static void gpdmaHalInit(DMA_Channel_TypeDef* channel, DMA_HandleTypeDef *handle) {

    IRQn_Type NVIC_Priority ;
    if (channel >= GPDMA1_Channel0 && channel <= GPDMA1_Channel7) {
        __HAL_RCC_GPDMA1_CLK_ENABLE();
        NVIC_Priority = GPDMA1_Channel0_IRQn;
        for (uint8_t i = 0; i < 8; i ++) {
            if (channel == GPDMA1_Channel0 + 50*i) {
                NVIC_Priority = GPDMA1_Channel0_IRQn + i;
                break;
            }
        }
    }else if (channel >= GPDMA2_Channel1 && channel <= GPDMA2_Channel7) {
        __HAL_RCC_GPDMA2_CLK_ENABLE();
        NVIC_Priority = GPDMA1_Channel0_IRQn;
        for (uint8_t i = 0; i < 8; i ++) {
            if (channel == GPDMA2_Channel0 + 50*i) {
                NVIC_Priority = GPDMA1_Channel0_IRQn + i;
                break;
            }
        }
    }
    HAL_NVIC_SetPriority(NVIC_Priority, DMA_MEM2MEM_IT_PRIORITY, 0);
    HAL_NVIC_EnableIRQ(GPDMA1_Channel0_IRQn);

    handle->Instance = channel;
    handle->Init.Request = DMA_REQUEST_SW;
    handle->Init.BlkHWRequest = DMA_BREQ_SINGLE_BURST;
    handle->Init.Direction = DMA_MEMORY_TO_MEMORY;
    handle->Init.SrcInc = DMA_SINC_INCREMENTED;
    handle->Init.DestInc = DMA_DINC_INCREMENTED;
    handle->Init.SrcDataWidth = DMA_SRC_DATAWIDTH_BYTE;
    handle->Init.DestDataWidth = DMA_DEST_DATAWIDTH_BYTE;
    handle->Init.Priority = DMA_MEM2MEM_CHANNEL_PRIORITY;
    handle->Init.SrcBurstLength = 1;
    handle->Init.DestBurstLength = 1;
    handle->Init.TransferAllocatedPort = DMA_SRC_ALLOCATED_PORT0|DMA_DEST_ALLOCATED_PORT0;
    handle->Init.TransferEventMode = DMA_TCEM_BLOCK_TRANSFER;
    handle->Init.Mode = DMA_NORMAL;
    if (HAL_DMA_Init(handle) != HAL_OK)
    {
    Error_Handler();
    }
    if (HAL_DMA_ConfigChannelAttributes(handle, DMA_CHANNEL_NPRIV) != HAL_OK)
    {
    Error_Handler();
    }
}


static dma_t* getFreeDMA(void) {
    for (uint8_t i = 0; i < dmaHalAssigned; i++) {
        if (HAL_DMA_GetState(&dma_handle[i].dmaHalChannel) == HAL_DMA_STATE_READY && dma_handle[i].isBusy == false) {
            return &dma_handle[i];
        }
    }
    return NULL;
}


static dma_t* getHandleOfDma(DMA_HandleTypeDef* hdma) {
    dma_t* dma ;
    for (dma = &dma_handle[0]; dma <= &dma_handle[dmaHalAssigned - 1]; dma++) {
        if (&dma->dmaHalChannel == hdma) {
            return dma;
        }
    }
    return NULL;
}

static void setBusyDMA(dma_t* dma) {
    dma->isBusy = true;
}

static void resetDMA(dma_t* dma) {
    if (dma != NULL) {
        dma->isBusy = false;
        dma->type = DMA_COPY_NO_INIT;
        dma->transmitSize = 0;
        dma->pairOfDMA = NULL;
    }
}



void dmaCopyCompleteCb ( DMA_HandleTypeDef * _hdma) {
    dma_t* dma = getHandleOfDma(_hdma);
    dma_t* dmaWithoutIt = NULL;
    uint32_t addressFromDMAWith_IT = 0;
    uint32_t addressFromDMAWithout_IT = 0;
    uint8_t* address;
    if (dma == NULL) {
        Error_Handler();
    }
    if (dma->type == DMA_COPY_SPLIT_IT) {
        dmaWithoutIt = getHandleOfDma(dma->pairOfDMA);
        if (dmaWithoutIt == NULL) {
            Error_Handler();
        }
        addressFromDMAWithout_IT =  dma->dmaHalChannel.Instance->CDAR;
        addressFromDMAWith_IT =  dmaWithoutIt->dmaHalChannel.Instance->CDAR;
        if (addressFromDMAWithout_IT < addressFromDMAWith_IT)
            address = (uint8_t*) (addressFromDMAWithout_IT);
        else
            address = (uint8_t*) (addressFromDMAWith_IT);
        uint16_t size = dmaWithoutIt->transmitSize + dma->transmitSize;
        DMA_CopyCompleteCallback(address, size);
    }
    else if (dma->type == DMA_COPY_SOLO) {
        uint16_t size = dma->transmitSize;
        address = (uint8_t*) _hdma->Instance->CDAR;
        DMA_CopyCompleteCallback(address, size);
    }
    else {
        DMA_CopyCompleteCallback(NULL, 0);
    }
    if (dmaWithoutIt != NULL)
        resetDMA(dmaWithoutIt);
    resetDMA(dma);
}


DMAM2MResult_enum copyWithDMA(uint8_t *data, uint16_t size, uint8_t *dstBuf) {
    dma_t* dma1 = getFreeDMA();
    if (dma1 == NULL) {
        return HAL_BUSY;
    }
    setBusyDMA(dma1);
    dma1->type = DMA_COPY_SOLO;
    dma1->transmitSize = size;
    HAL_StatusTypeDef ret = HAL_DMA_Start_IT(&dma1->dmaHalChannel, (uint32_t)data, (uint32_t)dstBuf, size);
    if (ret != HAL_OK) {

        resetDMA(dma1);
        return ret;
    }
}


bool dmaM2MInit(DMA_Channel_TypeDef **dmaChannels, uint8_t howManyChannelsUse) {
    dmaHalAssigned = howManyChannelsUse;
    if (howManyChannelsUse > DMA_CHANNEL_USING)
        return false;

    for (uint8_t i = 0; i < howManyChannelsUse; i++)
    {
        //&dma_handle[i].dmaHalChannel = *dmaChannels++;
        gpdmaHalInit(*dmaChannels, &dma_handle[i].dmaHalChannel);
        HAL_DMA_RegisterCallback(&dma_handle[i].dmaHalChannel, HAL_DMA_XFER_CPLT_CB_ID, dmaCopyCompleteCb);
    }
    return true;
}

DMAM2MResult_enum copyWithDMASplit(uint8_t *data, uint16_t size, uint8_t *data2, uint16_t size2, uint8_t *dstBuf) {
    dma_t* dma1 = getFreeDMA();
    if (dma1 == NULL) {
        return DMAM2M_Result_BUSY;
    }
    setBusyDMA(dma1);
    dma_t* dma2 = getFreeDMA();
    if (dma2 == NULL) {
        resetDMA(dma1);
        return DMAM2M_Result_BUSY;
    }
    setBusyDMA(dma2);
    dma_t* dmaWithIT;
    dma_t* dmaWithoutIT;
    uint16_t sizeWithIT;
    uint16_t sizeWithoutIT;
    uint8_t* dataWithIT;
    uint8_t* dataWithoutIT;
    uint8_t* dstWithIT;
    uint8_t* dstWithoutIT;
    HAL_StatusTypeDef ret;
    if (size >= size2) {
        dataWithIT = data;
        dataWithoutIT = data2;
        dmaWithIT = dma1;
        dmaWithoutIT = dma2;
        sizeWithIT = size;
        sizeWithoutIT = size2;
        dstWithIT = dstBuf;
        dstWithoutIT = dstBuf + sizeWithIT;
    }
    else {
        dataWithIT = data2;
        dataWithoutIT = data;
        dmaWithIT = dma2;
        dmaWithoutIT = dma1;
        sizeWithoutIT = size;
        sizeWithIT = size2;
        dstWithIT = dstBuf + sizeWithoutIT;
        dstWithoutIT = dstBuf;
    }
    dmaWithIT->type = DMA_COPY_SPLIT_IT;
    dmaWithIT->pairOfDMA = &dmaWithoutIT->dmaHalChannel;
    dmaWithoutIT->type = DMA_COPY_WITHOUT_IT;
    dma1->isBusy = true;
    dma1->transmitSize = size;
    dma2->transmitSize = size2;
    ret = HAL_DMA_Start_IT(&dmaWithIT->dmaHalChannel, (uint32_t)dataWithIT, (uint32_t)dstWithIT, sizeWithIT);
    if (ret != HAL_OK) {
        resetDMA(dma1);
        resetDMA(dma2);
        return DMAM2M_Result_ERROR;
    }
    dma2->isBusy = true;
    ret = HAL_DMA_Start(&dmaWithoutIT->dmaHalChannel, (uint32_t)dataWithoutIT, (uint32_t)dstWithoutIT, sizeWithoutIT);
    if (ret != HAL_OK) {
        resetDMA(dma1);
        resetDMA(dma2);
        return DMAM2M_Result_ERROR;
    }
    return DMAM2M_Result_OK;
}


__weak void DMA_CopyCompleteCallback(uint8_t *address, uint16_t size) {
    __NOP();
}