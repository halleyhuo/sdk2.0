/**
 **************************************************************************************
 * @file    media_audio_play.c
 * @brief   
 *
 * @author  kk
 * @version V1.0.0
 *
 * $Created: 2017-3-17 13:06:47$
 *
 * @Copyright (C) 2016, Shanghai Mountain View Silicon Co.,Ltd. All rights reserved.
 **************************************************************************************
 */

#include <string.h>
#include "chip_info.h"
#include "type.h"
#include "rtos_api.h"
#include "audio_core.h"
#include "audio_utility.h"
#include "mv_ring_buffer.h"
#include "main_app.h"
#include "app_message.h"

#include "media_audio_play.h"
#include "pcm_transfer.h"
#include "dac.h"
#include "audio_path.h"
#include "app_config.h"
#include "clk.h"

#include "media_service.h"
#include "gpio.h"
#include "key.h"

/***************************************************************************************
 *
 * External defines
 *
 */

#define MEDIA_AUDIO_PLAY_TASK_STACK_SIZE	1024
#define MEDIA_AUDIO_PLAY_TASK_PRIO			3



/***************************************************************************************
 *
 * Internal defines
 *
 */

#define MAUDIO_PLAY_AUDIO_CORE_SRC_BUF_SIZE	(8*1024)
#define MAUDIO_PLAY_AUDIO_CORE_OUT_BUF_SIZE	2048

bool xrtxMedia = TRUE;

typedef struct _mediaAudioPlayContext
{
	xTaskHandle 		taskHandle;
	MessageHandle		msgHandle;
	QueueHandle_t 		audioMutex;
	QueueHandle_t		pcmBufMutex;

	//MemHandle			decoderMemHandle;
	MvRingBuffer		audioCoreSrcBuf;
	uint8_t				*audioCoreMixBuf;
	AudioCoreHandle		audioCoreSrcHandle;
	AudioCoreHandle		audioCoreSinkHandle;
}MediaAudioPlayContext;



/***************************************************************************************
 *
 * Internal varibles
 *
 */

#define MEDIA_AUDIO_NUM_MESSAGE_QUEUE		10

static MediaAudioPlayContext	mediaAudioPlayCt;
#define MEDIA_AUDIO_PLAY(x)		(mediaAudioPlayCt.x)


/** media audio play task name*/
const char mediaAudioPlayName[] = "MediaAudioPlay";


static MessageId mediaAudioKeyMap[][5] = 
{
	{NULL, MSG_MEDIA_AUDIO_PLAY_PAUSE,	MSG_MEDIA_AUDIO_STOP,		NULL,						NULL				},
	{NULL, MSG_MEDIA_AUDIO_PRE,			MSG_MEDIA_AUDIO_VOLDOWN, 	MSG_MEDIA_AUDIO_VOLDOWN,	NULL				},
	{NULL, MSG_MEDIA_AUDIO_NEXT,		MSG_MEDIA_AUDIO_VOLUP,		MSG_MEDIA_AUDIO_VOLUP,		NULL				},
	{NULL, MSG_MEDIA_AUDIO_READ_WX,		NULL,						NULL,						NULL				},
	{NULL, NULL,						MSG_MEDIA_AUDIO_RECORD_WX,	NULL,						MSG_MEDIA_AUDIO_SEND_WX}
};

/***************************************************************************************
 *
 * Internal functions
 *
 */
 
MessageId GetMediaAudioKeyMap(KeyValue value, KeyEvent event)
{
	return mediaAudioKeyMap[value][event];
}

static uint16_t MediaAudioSourceGetData(int16_t * buf, uint16_t sampleLen)
{
	int16_t	dataSize;

	if(MvRingBufferVaildSize(&MEDIA_AUDIO_PLAY(audioCoreSrcBuf)) == 0)
	{
		return 0;
	}

	GetMediaPcmBufMutex();
	dataSize = MvRingBufferRead(&MEDIA_AUDIO_PLAY(audioCoreSrcBuf), (uint8_t *)buf, sampleLen*2*2);
	ReleaseMediaPcmBufMutex();

	return dataSize/4;

}

static void MediaAudioSinkPutData(void * buf, uint16_t len)
{
	GetMediaMutex();
	if(PcmFifoIsEmpty())
	{
		//DBG("Empty\n");
	}
	PcmTxTransferData((void *)buf, (void *)buf, len);
}

static void ConfigPhub2MediaAudioPlay(void)
{
	/* DAC initialization */
	CodecDacInit(TRUE);
	CodecDacMuteSet(TRUE, TRUE);
	CodecDacChannelSel(DAC_CH_DECD_L | DAC_CH_DECD_R);
	DacVolumeSet(0x200, 0x200);
	DacNoUseCapacityToPlay();
	DacConfig(MDAC_DATA_FROM_DEC, USB_MODE);
	/* PCMFIFO_MIX_DACOUT */
	PhubPathSel(PCMFIFO_MIX_DACOUT);
	CodecDacMuteSet(FALSE, FALSE);
}

static void DeconfigPhub2MediaAudioPlay(void)
{
	
}

static void ConfigAudioCore2MediaAudioPlay(void)
{

	AuidoCoreInit(AUDIO_CORE_MODE_MIX);

	MEDIA_AUDIO_PLAY(audioCoreSrcHandle) = AudioCoreRegisterSource(MediaAudioSourceGetData, AUDIO_CORE_SRC_TYPE_DECODER);

	MEDIA_AUDIO_PLAY(audioCoreSinkHandle) = AudioCoreRegisterSink(MediaAudioSinkPutData, AUDIO_CORE_SINK_TYPE_DAC);

}

static void DeconfigAudioCore2MediaAudioPlay(void)
{
	AudioCoreDeregisterSource(MEDIA_AUDIO_PLAY(audioCoreSrcHandle));
	AudioCoreDeregisterSink(MEDIA_AUDIO_PLAY(audioCoreSinkHandle));
}

static void ConfigMemory4MediaAudioPlay(void)
{
	/* for decoder */ 
	/* file point */
	
	/* for audio core source buffer */
	MEDIA_AUDIO_PLAY(audioCoreSrcBuf).buffer = (uint8_t *)pvPortMalloc(MAUDIO_PLAY_AUDIO_CORE_SRC_BUF_SIZE);
	MEDIA_AUDIO_PLAY(audioCoreSrcBuf).capacity = MAUDIO_PLAY_AUDIO_CORE_SRC_BUF_SIZE;
	MvRingBufferInit(&MEDIA_AUDIO_PLAY(audioCoreSrcBuf));

	/* for audio core mix buffer */
	MEDIA_AUDIO_PLAY(audioCoreMixBuf) = (uint8_t *)(VMEM_ADDR + AUDIOC_CORE_TRANSFER_OFFSET);

	PcmFifoInitialize(PCM_FIFO_OFFSET, PCM_FIFO_SIZE, 0, 0);
}

static void DeconfigMemory4MediaAudioPlay(void)
{
	
}

static void CreateMediaAudioPlayServices(void)
{
	MediaServiceCreate();

	DecoderServiceCreate();

	AudioCoreServiceCreate();

}

static void WaitMediaAudioPlayServices(void)
{
	while(1)
	{
		if(GetDecoderServiceState() == ServiceStateReady 
			&& GetMediaServiceState() == ServiceStateReady
			&& GetAudioCoreServiceState() == ServiceStateReady)
		{
			break;
		}
		else
		{
			vTaskDelay(10);
		}
	}
}

static void StartMediaAudioPlayServices(void)
{
	MessageContext		msgSend;
	MessageHandle		msgHandle;

	msgSend.msgId		= MSG_SERVICE_START;
	msgSend.msgParams	= NULL;

	msgHandle = GetMediaMessageHandle();
	MessageSend(msgHandle, &msgSend);

}

static int32_t MediaAudioPlayInit(void)
{
	memset(&mediaAudioPlayCt, 0, sizeof(MediaAudioPlayContext));
	
	MEDIA_AUDIO_PLAY(audioMutex) = xSemaphoreCreateMutex();
	MEDIA_AUDIO_PLAY(pcmBufMutex) = xSemaphoreCreateMutex();
	
	/* Read storage parameters */
//	PreferenceLoad(btAudioPlayStorName, &BT_AUDIO_PLAY(params), sizeof(BtAudioPlayParams));

	/* Config audio path*/
	ConfigPhub2MediaAudioPlay();

	/* Config memory */
	ConfigMemory4MediaAudioPlay();

	/* Create media audio services */
	CreateMediaAudioPlayServices();

	/* Config audio core source */
	ConfigAudioCore2MediaAudioPlay();
	

	return 0;
}

static void MediaAudioPlayDeinit(void)
{
	MessageContext		msgSend;
	MessageHandle		mainHandle;

	/* Deconfig audio path*/
	DeconfigPhub2MediaAudioPlay();

	/* Deconfig audio core */
	DeconfigAudioCore2MediaAudioPlay();

	/* Write storage parameters */
//	PrefrenceSave(btAudioPlayStorName, &BT_AUDIO_PLAY(params), sizeof(BtAudioPlayParams));

	/* Send message to main app */
	mainHandle = GetMainMessageHandle();

	msgSend.msgId		= MSG_SERVICE_STOPPED;
	msgSend.msgParams	= MSG_PARAM_MEDIA_AUDIO_PLAY;
	MessageSend(mainHandle, &msgSend);

}


static void MediaAudioPlaykEntrance(void * param)
{
	MessageContext		msgRecv;
	MessageContext		msgSend;
	MessageHandle		mainHandle;


	/* message handle */
	MEDIA_AUDIO_PLAY(msgHandle) = MessageRegister(MEDIA_AUDIO_NUM_MESSAGE_QUEUE);

	/* Send message to main app */
	mainHandle = GetMainMessageHandle();

	msgSend.msgId		= MSG_SERVICE_CREATED;
	msgSend.msgParams	= MSG_PARAM_MEDIA_AUDIO_PLAY;

	MessageSend(mainHandle, &msgSend);

	/* Wait servcies ready */
	WaitMediaAudioPlayServices();

	/* Start servcies */
	StartMediaAudioPlayServices();

	while(1)
	{
		MessageRecv(MEDIA_AUDIO_PLAY(msgHandle), &msgRecv, MAX_RECV_MSG_TIMEOUT);

		switch(msgRecv.msgId)
		{
			case MSG_MEDIA_AUDIO_MODE_STOP:
				MediaAudioPlayDeinit();

				/* Wait for kill*/
				vTaskSuspend(NULL);
				break;
			
			case MSG_MEDIA_AUDIO_PLAY_PAUSE:
				DBG("MSG_WIFI_AUDIO_PLAY_PAUSE\n");
				break;
			
			case MSG_MEDIA_AUDIO_STOP:
				DBG("MSG_WIFI_AUDIO_STOP\n");
				break;
			
			case MSG_MEDIA_AUDIO_NEXT:
				DBG("MSG_WIFI_AUDIO_NEXT\n");
				{
					AudioPlayerCloseSongFile();
					
					MessageContext		msgSend;
					MessageHandle		mainHandle;

					mainHandle = GetDecoderServiceMsgHandle();
					msgSend.msgId		= MSG_SERVICE_STOP;
					msgSend.msgParams	= NULL;
					MessageSend(mainHandle, &msgSend);
					//vTaskDelay(500);

					mainHandle = GetAudioCoreMessageHandle();
					MessageSend(mainHandle, &msgSend);
					vTaskDelay(1000);
					
					AudioPlayerNextSong();
					
					/* Send message to main app */
					mainHandle = GetMediaMessageHandle();
					msgSend.msgId		= MSG_SERVICE_START;
					msgSend.msgParams	= NULL;
					MessageSend(mainHandle, &msgSend);
				}
				break;
			
			case MSG_MEDIA_AUDIO_PRE:
				DBG("MSG_WIFI_AUDIO_PRE\n");
				break;
			
			case MSG_MEDIA_AUDIO_VOLUP:
				DBG("MSG_WIFI_AUDIO_VOLUP\n");
				break;
			
			case MSG_MEDIA_AUDIO_VOLDOWN:
				DBG("MSG_WIFI_AUDIO_VOLDOWN\n");
				break;
			
			case MSG_MEDIA_AUDIO_READ_WX:
				DBG("MSG_WIFI_AUDIO_READ_WX\n");
				break;
			
			case MSG_MEDIA_AUDIO_RECORD_WX:
				DBG("MSG_WIFI_AUDIO_RECORD_WX\n");
				break;
			
			case MSG_MEDIA_AUDIO_SEND_WX:
				DBG("MSG_WIFI_AUDIO_SEND_WX\n");
				break;
			
		}
	}
}


/***************************************************************************************
 *
 * APIs
 *
 */
MessageHandle GetMediaAudioPlayMessageHandle(void)
{
	return MEDIA_AUDIO_PLAY(msgHandle);
}

/**
 * @brief
 *		Start media audio play program task.
 * @param
 * 	 NONE
 * @return  
 */
int32_t MediaAudioPlayStart(void)
{
	MediaAudioPlayInit();
	xTaskCreate(MediaAudioPlaykEntrance, mediaAudioPlayName, MEDIA_AUDIO_PLAY_TASK_STACK_SIZE, NULL, MEDIA_AUDIO_PLAY_TASK_PRIO, &MEDIA_AUDIO_PLAY(taskHandle));
	return 0;
}

/**
 * @brief
 *		Exit media audio play program task.
 * @param
 * 	 NONE
 * @return  
 */
void MediaAudioPlayStop(void)
{
	vTaskDelete(MEDIA_AUDIO_PLAY(taskHandle));
}
/*
void * GetMediaAudioPlayDecoderBuffer(void)
{
	return &MEDIA_AUDIO_PLAY(decoderMemHandle);
}
*/
MvRingBuffer * GetMediaAudioPlayAudioCoreBuffer(void)
{
	return &MEDIA_AUDIO_PLAY(audioCoreSrcBuf);
}

int32_t SaveMediaDecodedPcmData(int32_t * pcmData, uint16_t sampleLen, uint32_t channels)
{
	uint32_t		dataLen;

	if(pcmData == NULL || sampleLen == 0)
		return -1;


	dataLen = sampleLen * channels * 2;
	if(MvRingBufferFreeSize(&MEDIA_AUDIO_PLAY(audioCoreSrcBuf)) < dataLen)
		return -2;

	GetMediaPcmBufMutex();
	dataLen = MvRingBufferWrite(&MEDIA_AUDIO_PLAY(audioCoreSrcBuf), (uint8_t *)pcmData, dataLen);
	ReleaseMediaPcmBufMutex();

	if(dataLen <= 0)
		return -3;
	
	return ((dataLen / channels ) / 2);

}

void GetMediaMutex(void)
{
	//xSemaphoreTake( MEDIA_AUDIO_PLAY(audioMutex) , 0xFFFFFFFF);
	while(!xrtxMedia)
	{
		vTaskDelay(1);
	}
	xrtxMedia = FALSE;
}


void ReleaseMediaMutex(void)
{
	/*portBASE_TYPE taskWoken = pdFALSE;

	if (__get_IPSR() != 0)
	{
		if (xSemaphoreGiveFromISR(MEDIA_AUDIO_PLAY(audioMutex), &taskWoken) != pdTRUE)
		{
			return;
		}
		portEND_SWITCHING_ISR(taskWoken);
	}
	else
	{
		if (xSemaphoreGive(MEDIA_AUDIO_PLAY(audioMutex)) != pdTRUE)
		{

		}
	}

	return;
	*/
	xrtxMedia = TRUE;
}


void GetMediaPcmBufMutex(void)
{
	xSemaphoreTake( MEDIA_AUDIO_PLAY(pcmBufMutex) , 0xFFFFFFFF);
}

void ReleaseMediaPcmBufMutex(void)
{
	portBASE_TYPE taskWoken = pdFALSE;

	if (__get_IPSR() != 0)
	{
		if (xSemaphoreGiveFromISR(MEDIA_AUDIO_PLAY(pcmBufMutex), &taskWoken) != pdTRUE)
		{
			return;
		}
		portEND_SWITCHING_ISR(taskWoken);
	}
	else
	{
		if (xSemaphoreGive(MEDIA_AUDIO_PLAY(pcmBufMutex)) != pdTRUE)
		{

		}
	}
	
	return;

}

