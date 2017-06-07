/**
 **************************************************************************************
 * @file    mv_ring_buffer.c
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

#include <string.h>

#include "type.h"
#include "rtos_api.h"
#include "mv_ring_buffer.h"

int32_t MvRingBufferInit(MvRingBuffer * ringBuffer)
{
	if(ringBuffer == NULL)
		return -1;

	memset(ringBuffer->buffer, 0, ringBuffer->capacity);
	ringBuffer->pRead		= ringBuffer->buffer;
	ringBuffer->pWrite		= ringBuffer->buffer;
	ringBuffer->vaildSize	= 0;
	return 0;
}

void MvRingBufferDeinit(MvRingBuffer * ringBuffer)
{

}

int32_t MvRingBufferWrite(MvRingBuffer * ringBuffer, uint8_t * data, uint32_t dataLen)
{
	uint32_t		writeSize;

	if(ringBuffer == NULL || data == NULL || dataLen == 0)
		return -1;

	writeSize = MvRingBufferFreeSize(ringBuffer) > dataLen ? dataLen : MvRingBufferFreeSize(ringBuffer);


	if(ringBuffer->pWrite + writeSize <= ringBuffer->buffer + ringBuffer->capacity)
	{
		memcpy(ringBuffer->pWrite, data, writeSize);
		ringBuffer->pWrite += writeSize;
		ringBuffer->vaildSize += writeSize;
	}
	else
	{
		int32_t		tempSize;

		tempSize = ringBuffer->buffer + ringBuffer->capacity - ringBuffer->pWrite;
		if(tempSize > 0)
			memcpy(ringBuffer->pWrite, data, tempSize);

		memcpy(ringBuffer->buffer, data + tempSize, writeSize - tempSize);
		ringBuffer->pWrite = ringBuffer->buffer + writeSize - tempSize;
		ringBuffer->vaildSize += writeSize;
	}


	return writeSize;
	
}

int32_t MvRingBufferRead(MvRingBuffer * ringBuffer, uint8_t * data, uint32_t dataLen)
{
	uint32_t		readSize;


	if(ringBuffer == NULL || data == NULL || dataLen == 0)
		return -1;

	readSize = ringBuffer->vaildSize > dataLen ? dataLen : ringBuffer->vaildSize;

	if(readSize == 0)
		return 0;


	if(ringBuffer->pRead + readSize <= ringBuffer->buffer + ringBuffer->capacity)
	{
		memcpy(data, ringBuffer->pRead, readSize);
		ringBuffer->pRead += readSize;
		ringBuffer->vaildSize -= readSize;
	}
	else
	{
		int32_t		tempSize;

		tempSize = ringBuffer->buffer + ringBuffer->capacity - ringBuffer->pRead;
		if(tempSize > 0)
			memcpy(data, ringBuffer->pRead,tempSize);

		memcpy(data + tempSize, ringBuffer->buffer, readSize - tempSize);
		ringBuffer->pRead = ringBuffer->buffer + readSize - tempSize;
		ringBuffer->vaildSize -= readSize;
	}

	return readSize;
}

