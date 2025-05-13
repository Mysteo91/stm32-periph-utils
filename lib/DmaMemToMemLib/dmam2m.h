//
// Created by user on 19.02.2025.
//

#ifndef DMAM2M_H
#define DMAM2M_H

#include <stdbool.h>

#include "stm32h5xx.h"


#define DMA_CHANNEL_USING 4
#define DMA_MEM2MEM_IT_PRIORITY 0
#define DMA_MEM2MEM_CHANNEL_PRIORITY DMA_LOW_PRIORITY_LOW_WEIGHT

typedef enum {
    DMAM2M_Result_OK,
    DMAM2M_Result_ERROR,
    DMAM2M_Result_BUSY
}DMAM2MResult_enum;

void DMA_CopyCompleteCallback(uint8_t *address, uint16_t size);
DMAM2MResult_enum copyWithDMASplit(uint8_t *data, uint16_t size, uint8_t *data2, uint16_t size2, uint8_t *dstBuf);
DMAM2MResult_enum copyWithDMA(uint8_t *data, uint16_t size, uint8_t *dstBuf);
bool dmaM2MInit(DMA_Channel_TypeDef **dmaChannels, uint8_t howManyChannelsUse);

#endif //DMAM2M_H
