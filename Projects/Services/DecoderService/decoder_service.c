/**
 **************************************************************************************
 * @file    decoder_service.c
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

#include "type.h"
#include "app_message.h"
#include "rtos_api.h"
#include "audio_utility.h"
#include "audio_decoder.h"
#include "mv_ring_buffer.h"
#include "decoder_service.h"

#include "app_config.h"
#include "chip_info.h"
#include "clk.h"

/***************************************************************************************
 *
 * External defines
 *
 */
 
#define DECODER_SERVICE_SIZE				1024
#define DECODER_SERVICE_PRIO				3

#define DECODER_SERVICE_TIMEOUT				2	/* 1 ms */

/***************************************************************************************
 *
 * Internal defines
 *
 */

#define DCS_NUM_MESSAGE_QUEUE				4

#define DEFAULT_DECODED_BUFFER_SIZE			(4*1024)

typedef enum
{
	DecoderStateNone = 0,
	DecoderStateInitilized,
	DecoderStateDecoding,
	DecoderStateWaitXrDone,
	DecoderStateToSavePcmData,
	DecoderStateDeinitilizing,
	DecoderStateSavePcmData
}DecoderState;

typedef struct _DecoderServiceContext
{
	xTaskHandle 		taskHandle;
	MessageHandle		msgHandle;
	MessageHandle		parentMsgHandle;
	ServiceState		serviceState;

	/*for audio decode init*/
	MemHandle			*memHandle;
	int32_t				ioType;
	int32_t				decoderType;

	/* for decoded buffer */
	MvRingBuffer		decodedBuf;
	QueueHandle_t		decodedBufMutex;

	/* for save decoded PCM data*/
	uint32_t			pcmDataSize;
	uint32_t			savedSize;
	uint8_t				*toSavePos;

	DecoderState		decoderState;
}DecoderServiceContext;

/** Device servcie name*/
const char decoderServiceName[]		= "DecoderService";

/***************************************************************************************
 *
 * Internal varibles
 *
 */

static DecoderServiceContext 		decoderServiceCt;
#define DCS(x)						(decoderServiceCt.x)


/***************************************************************************************
 *
 * Internal functions
 *
 */

void audio_decoder_interrupt_callback(int32_t intterupt_type)
{
//	DBG("intr = %d\n", intterupt_type);
	if(intterupt_type == 0)//XR_DONE
	{
		ReleaseXr();
	}

	if(intterupt_type == 1)//TX_DONE
	{
		ReleaseTx();
	}
}

static int32_t DS_Init(MessageHandle parentMsgHandle)
{
	memset(&decoderServiceCt, 0, sizeof(DecoderServiceContext));

	decoderServiceCt.parentMsgHandle = parentMsgHandle;

	decoderServiceCt.decodedBuf.buffer = (uint8_t *)pvPortMalloc(DEFAULT_DECODED_BUFFER_SIZE);
	decoderServiceCt.decodedBuf.capacity = DEFAULT_DECODED_BUFFER_SIZE;
	MvRingBufferInit(&decoderServiceCt.decodedBuf);
	/* register message handle */
	decoderServiceCt.msgHandle = MessageRegister(DCS_NUM_MESSAGE_QUEUE);

	decoderServiceCt.decodedBufMutex = xSemaphoreCreateMutex();

	NVIC_SetPriority(DECODER_IRQn, 2);

	InitXrTx();

	return 0;
}


static void DS_Deinit(void)
{
	MessageContext		msgSend;

	/* Send message to main app */
	msgSend.msgId		= MSG_SERVICE_STOPPED;
	msgSend.msgParams	= MSG_PARAM_DECODER_SERVICE;
	MessageSend(decoderServiceCt.parentMsgHandle, &msgSend);

	vSemaphoreDelete(decoderServiceCt.decodedBufMutex);

	decoderServiceCt.serviceState = ServiceStateNone;
}


static void GetPcmBufMutex(void)
{
	xSemaphoreTake(decoderServiceCt.decodedBufMutex , 0xFFFFFFFF);
}

static void ReleasePcmBufMutex(void)
{
	portBASE_TYPE taskWoken = pdFALSE;

	if (__get_IPSR() != 0)
	{
		if (xSemaphoreGiveFromISR(decoderServiceCt.decodedBufMutex, &taskWoken) != pdTRUE)
		{
			return;
		}
		portEND_SWITCHING_ISR(taskWoken);
	}
	else
	{
		if (xSemaphoreGive(decoderServiceCt.decodedBufMutex) != pdTRUE)
		{

		}
	}

	return;
}

static int16_t SaveDecodedPcmData(uint8_t * pcmData, uint16_t pcmDataLen)
{
	int32_t			writeDataLen;

	if(pcmData == NULL || pcmDataLen == 0)
		return -1;

	GetPcmBufMutex();
	writeDataLen = MvRingBufferWrite(&decoderServiceCt.decodedBuf, (uint8_t *)pcmData, pcmDataLen);
	ReleasePcmBufMutex();
	if(writeDataLen <= 0)
		return -1;

	return writeDataLen;
}


static void DecoderProcess(void)
{
	switch(decoderServiceCt.decoderState)
	{
		case DecoderStateInitilized:
			decoderServiceCt.decoderState	= DecoderStateDecoding;
			break;

		case DecoderStateDecoding:
			if(GetXr())
			{
				if(RT_SUCCESS == audio_decoder_decode())
				{
					if(is_audio_decoder_with_hardware())
					{
						decoderServiceCt.decoderState = DecoderStateWaitXrDone;
					}
					else
					{
						ReleaseXr();
						decoderServiceCt.decoderState = DecoderStateToSavePcmData;
					}
				}
				else
				{
					DBG("Deocder error %d\n", audio_decoder_get_error_code());
					ReleaseXr();
				}
			}
			break;

		case DecoderStateWaitXrDone:
			if(audio_decoder_check_xr_done() == RT_YES)
			{
				audio_decoder_clear_xr_done();
				decoderServiceCt.decoderState = DecoderStateToSavePcmData;
			}
			break;

		case DecoderStateToSavePcmData:
			{
				DecoderCallbackParams		params;
				
				params.status = TRUE;
				params.songInfo = audio_decoder->song_info;

				{
					decoderServiceCt.pcmDataSize	= (audio_decoder->song_info->pcm_data_length)*(audio_decoder->song_info->num_channels)*2;
					decoderServiceCt.savedSize		= 0;
					decoderServiceCt.toSavePos		= (uint8_t *)audio_decoder->song_info->pcm0_addr;

					decoderServiceCt.decoderState = DecoderStateSavePcmData;
				}
			}
		case DecoderStateSavePcmData:
			{
				int32_t		savedSize;

				savedSize = SaveDecodedPcmData(decoderServiceCt.toSavePos,decoderServiceCt.pcmDataSize - decoderServiceCt.savedSize);

				if(savedSize > 0)
				{
					decoderServiceCt.savedSize += savedSize;
					decoderServiceCt.toSavePos += savedSize;
					if(decoderServiceCt.savedSize == decoderServiceCt.pcmDataSize)
					{
						decoderServiceCt.decoderState = DecoderStateDecoding;
					}
				}
				else
				{
					
				}
			}
			break;

		case DecoderStateDeinitilizing:
			decoderServiceCt.decoderState = DecoderStateNone;
			break;

		default:
			break;
	}
}

static void DecoderServiceEntrance(void * param)
{
	MessageContext		msgRecv;
	MessageContext		msgSend;


	decoderServiceCt.serviceState = ServiceStateReady;

	/* Send message to parent*/
	msgSend.msgId		= MSG_SERVICE_CREATED;
	msgSend.msgParams	= MSG_PARAM_DECODER_SERVICE;
	MessageSend(decoderServiceCt.parentMsgHandle, &msgSend);


	while(1)
	{
		MessageRecv(decoderServiceCt.msgHandle, &msgRecv, DECODER_SERVICE_TIMEOUT);
		switch(msgRecv.msgId)
		{
			case MSG_SERVICE_START:
				if(decoderServiceCt.serviceState == ServiceStateReady)
				{
					msgSend.msgId		= MSG_SERVICE_STARTED;
					msgSend.msgParams	= MSG_PARAM_DECODER_SERVICE;
					MessageSend(decoderServiceCt.parentMsgHandle, &msgSend);
					decoderServiceCt.serviceState = ServiceStateRunning;
				}
				break;

			case MSG_SERVICE_STOP:
				if(decoderServiceCt.serviceState == ServiceStateRunning)
				{
					decoderServiceCt.serviceState = ServiceStateReady;
				}

				break;
			default:
				break;
		}

		if(decoderServiceCt.serviceState == ServiceStateRunning)
			DecoderProcess();

	}
}


/***************************************************************************************
 *
 * APIs
 *
 */


/**
 * @brief
 *		Get message handle
 * @param
 * 	 NONE
 * @return  
 */
MessageHandle GetDecoderServiceMsgHandle(void)
{
	return decoderServiceCt.msgHandle;
}

ServiceState GetDecoderServiceState(void)
{
	return decoderServiceCt.serviceState;
}

MvRingBuffer * GetDecoderServiceBuf(void)
{
	return &decoderServiceCt.decodedBuf;
}

/**
 * @brief
 *		
 * @param
 * 	 NONE
 * @return  
 */
int32_t DecoderServiceCreate(MessageHandle parentMsgHandle)
{
	int32_t		ret;

	DS_Init(parentMsgHandle);
	xTaskCreate(DecoderServiceEntrance, decoderServiceName, DECODER_SERVICE_SIZE, NULL, DECODER_SERVICE_PRIO, &decoderServiceCt.taskHandle);
	return ret;
}


void DecoderServiceStart(void)
{
	MessageContext		msgSend;

	msgSend.msgId		= MSG_SERVICE_START;
	msgSend.msgParams	= NULL;
	MessageSend(decoderServiceCt.msgHandle, &msgSend);
}

/**
 * @brief
 *		Exit audio core service.
 * @param
 * 	 NONE
 * @return  
 */
void DecoderServiceStop(void)
{
	MessageContext		msgSend;

	msgSend.msgId		= MSG_SERVICE_STOP;
	msgSend.msgParams	= NULL;
	MessageSend(decoderServiceCt.msgHandle, &msgSend);
}


/**
 * @brief
 *		
 * @param
 * 	 NONE
 * @return  
 */
void DecoderServiceKill(void)
{
	DS_Deinit();
	vTaskDelete(decoderServiceCt.taskHandle);
}

int16_t GetDecodedPcmData(int16_t * pcmData, uint16_t sampleLen, uint32_t channels)
{
	int16_t	dataSize;
	uint32_t	remainSize;
	uint32_t	getSize;

	getSize = sampleLen*channels*2;
	if(getSize > MvRingBufferVaildSize(&decoderServiceCt.decodedBuf))
	{
		getSize = (MvRingBufferVaildSize(&decoderServiceCt.decodedBuf)/(channels*2))*(channels*2);
	}

	GetPcmBufMutex();
	dataSize = MvRingBufferRead(&decoderServiceCt.decodedBuf, (uint8_t *)pcmData, getSize);
	ReleasePcmBufMutex();

	return dataSize/4;
}


int32_t DecoderInit(MemHandle * memHandle, int32_t ioType, int32_t decoderType, SongInfo ** songInfo)
{
	int32_t			ret;
	ret = audio_decoder_initialize((uint8_t *)(VMEM_ADDR + DECODER_MEM_OFFSET), memHandle, ioType, decoderType);

	if(ret == RT_SUCCESS)
	{
		*songInfo = audio_decoder->song_info;
		PcmTxSetPcmDataMode((PCM_DATA_MODE)audio_decoder->song_info->pcm_data_mode);
		DacAdcSampleRateSet(audio_decoder->song_info->sampling_rate, USB_MODE);
		NVIC_EnableIRQ(DECODER_IRQn);
		decoderServiceCt.decoderState = DecoderStateInitilized;
	}
	else
	{
		int32_t		errCode;
		errCode = audio_decoder_get_error_code();
		DBG("AudioDecoder init err code = %d\n", errCode);
		*songInfo = NULL;
	}

	return ret;
}

void DecoderDeinit(void)
{
	decoderServiceCt.decoderState = DecoderStateDeinitilizing;
}

/***************************************************************************************
 *
 * The following APIs only for O18B XrTx module
 *
 */

static BOOL xrDone = TRUE;
static BOOL txDone = TRUE;

void InitXrTx(void)
{
	xrDone = TRUE;
	txDone = TRUE;
}

BOOL CheckXr(void)
{
	return xrDone;
}

BOOL CheckTx(void)
{
	return txDone;
}

BOOL CheckXrTx(void)
{
	return (xrDone && txDone);
}

BOOL GetXr(void)
{
	if(xrDone && txDone)
	{
		xrDone = FALSE;
		return TRUE;
	}

	return FALSE;
}

BOOL GetTx(void)
{
	if(xrDone && txDone)
	{
		txDone = FALSE;
		return TRUE;
	}
	return FALSE;
}

void ReleaseXr(void)
{
	xrDone = TRUE;
}

void ReleaseTx(void)
{
	txDone = TRUE;
}


