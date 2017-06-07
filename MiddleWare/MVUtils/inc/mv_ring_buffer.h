/**
 **************************************************************************************
 * @file    mv_ring_buffer.h
 * @brief   
 *
 * @author  halley
 * @version V1.0.0
 *
 * $Created: 2016-6-29 13:06:47$
 *
 * @Copyright (C) 2016, Shanghai Mountain View Silicon Co.,Ltd. All rights reserved.
 **************************************************************************************
 */





#ifndef __MV_RING_BUFFER_H__
#define __MV_RING_BUFFER_H__

#include "type.h"


typedef struct _MvRingBuffer
{
	uint8_t			*buffer;
	uint8_t			*pRead;
	uint8_t			*pWrite;
	uint32_t		capacity;
	uint32_t		vaildSize;
}MvRingBuffer;

int32_t MvRingBufferInit(MvRingBuffer * ringBuffer);

int32_t MvRingBufferWrite(MvRingBuffer * ringBuffer, uint8_t * data, uint32_t dataLen);

int32_t MvRingBufferRead(MvRingBuffer * ringBuffer, uint8_t * data, uint32_t dataLen);

uint32_t MvRingBufferFreeSize(MvRingBuffer * ringBuffer);
#define MvRingBufferFreeSize(x)		((x)->capacity - (x)->vaildSize)


uint32_t MvRingBufferVaildSize(MvRingBuffer * ringBuffer);
#define MvRingBufferVaildSize(x)	((x)->vaildSize)

uint32_t MvRingBufferCapacity(MvRingBuffer * ringBuffer);
#define MvRingBufferCapacity(x)		((x)->capacity)


#endif /*__MV_RING_BUFFER_H__*/

