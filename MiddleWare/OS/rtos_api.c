/*
 * RTOS_API.c
 *
 *  Created on: Aug 30, 2016
 *      Author: peter
 */

#include <stdint.h>
#include <stddef.h>
#include "type.h"
#include "rtos_api.h"
#include "chip_info.h"
#include "app_config.h"

/* Determine whether we are in thread mode or handler mode. */
__asm uint32_t inHandlerMode (void)
{
    PRESERVE8
    mrs r0, ipsr
    bx r14
}



bool MessageSend(MessageHandle msgHandle,  MessageContext * msgContext)
{
	portBASE_TYPE taskWoken = pdFALSE;

	if (inHandlerMode())
	{
		if (xQueueSendFromISR(msgHandle, msgContext, &taskWoken) != pdTRUE)
		{
			return FALSE;
		}
		portEND_SWITCHING_ISR(taskWoken);
	}
	else
	{
		if (xQueueSend(msgHandle, msgContext, 0) != pdTRUE)
		{
			return FALSE;
		}
	}

	return TRUE;
}

void MessageSendx(MessageHandle msgHandle,  MessageContext * msgContext)
{
	xQueueSend(msgHandle, msgContext, 0xFFFFFFFF);
}


bool MessageRecv(MessageHandle msgHandle, MessageContext * msgContext, uint32_t millisec)
{
	portBASE_TYPE	taskWoken;
	bool			ret = FALSE;

	if (msgHandle == NULL)
	{
		return FALSE;
	}

	taskWoken = pdFALSE;
	msgContext->msgId = MSG_INVAILD;

	if (inHandlerMode())
	{
		if (xQueueReceiveFromISR(msgHandle, msgContext, &taskWoken) == pdTRUE)
		{
			/* We have mail */
			ret = TRUE;
		}
		else
		{
			ret = FALSE;
		}
		portEND_SWITCHING_ISR(taskWoken);
	}
	else 
	{
		if (xQueueReceive(msgHandle, msgContext, millisec) == pdTRUE)
		{
			/* We have mail */
			ret = TRUE;
		}
		else 
		{
			ret = FALSE;
		}
	}

	return ret;
}

void InitialiseHeapArea(void)
{
	extern unsigned int Image$$RW_XMEM$$Base;
	extern unsigned int Image$$RW_XMEM$$Limit;
	extern unsigned int Image$$RW_XMEM$$Length;
	extern unsigned int Image$$RW_XMEM$$ZI$$Base;
	extern unsigned int Image$$RW_XMEM$$ZI$$Limit;
	extern unsigned int Image$$RW_XMEM$$ZI$$Length;
	extern unsigned int Image$$RW_VMEM$$Base;
	extern unsigned int Image$$RW_VMEM$$Length;

	uint32_t mallocStart;
	HeapRegion_t xHeapRegions[4];
	uint8_t i=0;

	mallocStart = (uint32_t) &Image$$RW_XMEM$$ZI$$Limit;
	mallocStart = (mallocStart + 3) & (~0x03);

	xHeapRegions[i].pucStartAddress = (uint8_t*)mallocStart;
	xHeapRegions[i].xSizeInBytes = XMEM_SIZE+DECODER_MEM_OFFSET-SDIO_SEND_RECV_BUF_SIZE-((uint32_t)&Image$$RW_XMEM$$ZI$$Limit-(uint32_t)&Image$$RW_XMEM$$Base);

	i++;
	xHeapRegions[i].pucStartAddress = (uint8_t*)SDRAM_BASE_ADDR;
	xHeapRegions[i].xSizeInBytes = SDRAM_SIZE / 2;
	
	i++;
	xHeapRegions[i].pucStartAddress = NULL;
	xHeapRegions[i].xSizeInBytes = 0;

	vPortDefineHeapRegions( xHeapRegions );
}

