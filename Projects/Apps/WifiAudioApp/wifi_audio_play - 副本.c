/**
 **************************************************************************************
 * @file    wifi_audio_play.c
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

#include "chip_info.h"

#include "type.h"
#include "rtos_api.h"
#include "audio_core.h"
#include "audio_utility.h"
#include "mv_ring_buffer.h"
#include "main_app.h"
#include "app_message.h"
#include "audio_decoder.h"
#include "decoder_service.h"
#include "wifi_audio_play.h"
#include "pcm_transfer.h"
#include "dac.h"
#include "audio_path.h"
#include "app_config.h"
#include "clk.h"
#include "pcm_fifo.h"
#include "key.h"

/***************************************************************************************
 *
 * External defines
 *
 */

#define WIFI_AUDIO_PLAY_TASK_STACK_SIZE		1024
#define WIFI_AUDIO_PLAY_TASK_PRIO			3



/***************************************************************************************
 *
 * Internal defines
 *
 */

typedef enum
{
	WifiAudioPlayStateNone = 0,
	WifiAudioPlayStateReady,
	WifiAudioPlayStatePlaying,
}WifiAudioPlayState;

typedef struct _WifiAudioPlayContext
{
	xTaskHandle 		taskHandle;
	MessageHandle		msgHandle;
	WifiAudioPlayState	state;

	QueueHandle_t 		audioMutex;

	MemHandle			decoderMemHandle;
	uint8_t				*audioCoreMixBuf;
	AudioCoreHandle		audioCoreSrcHandle;
	AudioCoreHandle		audioCoreSinkHandle;
}WifiAudioPlayContext;


/***************************************************************************************
 *
 * Internal varibles
 *
 */

#define WIFI_AUDIO_NUM_MESSAGE_QUEUE		10

static WifiAudioPlayContext		wifiAudioPlayCt;
#define WIFI_AUDIO_PLAY(x)		(wifiAudioPlayCt.x)


/** wifi audio play task name*/
const char wifiAudioPlayName[] = "WifiAudioPlay";

static MessageId wifiAudioKeyMap[][5] = 
{
	{NULL, MSG_WIFI_AUDIO_PLAY_PAUSE,	MSG_WIFI_AUDIO_STOP,		NULL,					NULL				},
	{NULL, MSG_WIFI_AUDIO_PRE,			MSG_WIFI_AUDIO_VOLDOWN, 	MSG_WIFI_AUDIO_VOLDOWN,	NULL				},
	{NULL, MSG_WIFI_AUDIO_NEXT,			MSG_WIFI_AUDIO_VOLUP,		MSG_WIFI_AUDIO_VOLUP,	NULL				},
	{NULL, MSG_WIFI_AUDIO_READ_WX,		NULL,						NULL,					NULL				},
	{NULL, NULL,						MSG_WIFI_AUDIO_RECORD_WX,	NULL,					MSG_WIFI_AUDIO_SEND_WX}
};



/***************************************************************************************
 *
 * Internal functions
 *
 */

MessageId GetWifiAudioKeyMap(KeyValue value, KeyEvent event)
{
	return wifiAudioKeyMap[value][event];
}



static uint16_t WifiAudioSourceGetData(int16_t * buf, uint16_t sampleLen)
{
	return GetDecodedPcmData(buf, sampleLen, 2);
}


static BOOL WifiAudioSinkPutData(void * buf, uint16_t len)
{
	if((PcmFifoGetStatus() == 1) && (PcmFifoGetRemainSamples() > 1024))
	{
		PcmFifoPlay();
	}

	if(!CheckXrTx() || PcmFifoGetRemainSamples() >= 1856)
	{
		return FALSE;
	}

	if(GetTx())
	{
		memcpy(WIFI_AUDIO_PLAY(audioCoreMixBuf), buf, len*4);
		
		if(PcmFifoIsEmpty())
		{
			DBG("Empty\n");
		}
		PcmTxTransferData((void *)WIFI_AUDIO_PLAY(audioCoreMixBuf), (void *)WIFI_AUDIO_PLAY(audioCoreMixBuf), len);
		return TRUE;
	}

	return FALSE;
}

static void ConfigPhub4WifiAudioPlay(void)
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

static void DeconfigPhub2WifiAudioPlay(void)
{

}

static void ConfigAudioCore2WifiAudioPlay(void)
{
	AuidoCoreInit(AUDIO_CORE_MODE_MIX);

	WIFI_AUDIO_PLAY(audioCoreSrcHandle) = AudioCoreRegisterSource(WifiAudioSourceGetData, AUDIO_CORE_SRC_TYPE_DECODER);

	if(WIFI_AUDIO_PLAY(audioCoreSrcHandle))
		AudioCoreEnableSource(WIFI_AUDIO_PLAY(audioCoreSrcHandle));

	WIFI_AUDIO_PLAY(audioCoreSinkHandle) = AudioCoreRegisterSink(WifiAudioSinkPutData, AUDIO_CORE_SINK_TYPE_DAC);
	if(WIFI_AUDIO_PLAY(audioCoreSinkHandle))
		AudioCoreEnableSink(WIFI_AUDIO_PLAY(audioCoreSinkHandle));

}

static void DeconfigAudioCore2WifiAudioPlay(void)
{
	AudioCoreDeregisterSource(WIFI_AUDIO_PLAY(audioCoreSrcHandle));
	AudioCoreDeregisterSink(WIFI_AUDIO_PLAY(audioCoreSinkHandle));
}

static void ConfigMemory4WifiAudioPlay(void)
{


}

static void DeconfigMemory4WifiAudioPlay(void)
{
	
}

static void DeocderCallback(DecoderServiceEvent event, DecoderCallbackParams * param)
{
	switch(event)
	{

		case DS_EVENT_DECODE_INITED:
			PcmTxSetPcmDataMode((PCM_DATA_MODE)param->songInfo->pcm_data_mode);
			DacAdcSampleRateSet(param->songInfo->sampling_rate, USB_MODE);
			DBG("samplerate = %d\n",param->songInfo->sampling_rate);
			NVIC_EnableIRQ(DECODER_IRQn);

			break;

		default:
			break;
	}
}

static void CreateWifiAudioPlayServices(void)
{
	WifiServiceCreate();
}

static void WaitWifiAudioPlayServices(void)
{
	while(1)
	{
		if(GetDecoderServiceState() == ServiceStateReady 
			&& GetWifiServiceState() == ServiceStateReady
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

static void StartWifiAudioPlayServices(void)
{
	MessageContext		msgSend;
	MessageHandle		msgHandle;

	msgSend.msgId		= MSG_SERVICE_START;
	msgSend.msgParams	= NULL;

	msgHandle = GetWifiMessageHandle();
	MessageSend(msgHandle, &msgSend);

//	msgHandle = GetDecoderMessageHandle();
//	msgSend.msgParams = MSG_PARAM_DECODER_MODE_WIFI;
//	MessageSend(msgHandle, &msgSend);

//	DecoderServiceStart();

	msgHandle = GetAudioCoreMessageHandle();
	MessageSend(msgHandle, &msgSend);
}

static void WifiAudioPlayModeStart(void)
{
	WIFI_AUDIO_PLAY(audioMutex) = xSemaphoreCreateMutex();

	ConfigPhub4WifiAudioPlay();

	PcmFifoInitialize(PCM_FIFO_OFFSET, PCM_FIFO_SIZE, 0, 0);
	PcmFifoPause();

}

static void WifiAudioPlayModeStop(void)
{
	vSemaphoreDelete(WIFI_AUDIO_PLAY(audioMutex));
}

static int32_t WifiAudioPlayInit(void)
{
	memset(&wifiAudioPlayCt, 0, sizeof(WifiAudioPlayContext));

	/* message handle */
	WIFI_AUDIO_PLAY(msgHandle) = MessageRegister(WIFI_AUDIO_NUM_MESSAGE_QUEUE);

	/* for decoder */ 
	WIFI_AUDIO_PLAY(decoderMemHandle).addr = (uint8_t *) SDRAM_BASE_ADDR + SDRAM_SIZE/2;
	WIFI_AUDIO_PLAY(decoderMemHandle).mem_capacity = SDRAM_SIZE/2;
	WIFI_AUDIO_PLAY(decoderMemHandle).mem_len = 0;
	WIFI_AUDIO_PLAY(decoderMemHandle).p = 0;

	/* for audio core mix buffer */
	WIFI_AUDIO_PLAY(audioCoreMixBuf) = (uint8_t *)(VMEM_ADDR + AUDIOC_CORE_TRANSFER_OFFSET);

	return 0;
}

static void WifiAudioPlayDeinit(void)
{
	MessageContext		msgSend;
	MessageHandle		mainHandle;

	/* Deconfig audio path*/
	DeconfigPhub2WifiAudioPlay();

	/* Deconfig audio core */
	DeconfigAudioCore2WifiAudioPlay();

	/* Write storage parameters */
//	PrefrenceSave(btAudioPlayStorName, &BT_AUDIO_PLAY(params), sizeof(BtAudioPlayParams));

	/* Send message to main app */
	mainHandle = GetMainMessageHandle();

	msgSend.msgId		= MSG_SERVICE_DEINITED;
	msgSend.msgParams	= MSG_PARAM_WIFI_AUDIO_PLAY;
	MessageSend(mainHandle, &msgSend);

}


static void WifitAudioPlaykEntrance(void * param)
{
	MessageContext		msgRecv;
	MessageContext		msgSend;
	MessageHandle		mainHandle;


	WifiAudioPlayServiceCreate();

	/* Send message to main app */
	mainHandle = GetMainMessageHandle();

	msgSend.msgId		= MSG_SERVICE_INITED;
	msgSend.msgParams	= MSG_PARAM_WIFI_AUDIO_PLAY;

	MessageSend(mainHandle, &msgSend);

	while(1)
	{
		MessageRecv(WIFI_AUDIO_PLAY(msgHandle), &msgRecv, MAX_RECV_MSG_TIMEOUT);

		switch(msgRecv.msgId)
		{
			case MSG_APP_MODE_START:
				WifiAudioPlayModeStart();
				break;
			case MSG_APP_MODE_STOP:
				WifiAudioPlayModeStop();
				break;

			case MSG_WIFI_AUDIO_PLAY_PAUSE:
				DBG("MSG_WIFI_AUDIO_PLAY_PAUSE\n");
				break;
			
			case MSG_WIFI_AUDIO_STOP:
				DBG("MSG_WIFI_AUDIO_STOP\n");
				break;
			
			case MSG_WIFI_AUDIO_NEXT:
				DBG("MSG_WIFI_AUDIO_NEXT\n");
				break;
			
			case MSG_WIFI_AUDIO_PRE:
				DBG("MSG_WIFI_AUDIO_PRE\n");
				break;
			
			case MSG_WIFI_AUDIO_VOLUP:
				DBG("MSG_WIFI_AUDIO_VOLUP\n");
				break;
			
			case MSG_WIFI_AUDIO_VOLDOWN:
				DBG("MSG_WIFI_AUDIO_VOLDOWN\n");
				break;
			
			case MSG_WIFI_AUDIO_READ_WX:
				DBG("MSG_WIFI_AUDIO_READ_WX\n");
				break;
			
			case MSG_WIFI_AUDIO_RECORD_WX:
				DBG("MSG_WIFI_AUDIO_RECORD_WX\n");
				break;
			
			case MSG_WIFI_AUDIO_SEND_WX:
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
MessageHandle GetWifiAudioPlayMessageHandle(void)
{
	return WIFI_AUDIO_PLAY(msgHandle);
}

int32_t WifiAudioPlayEntry(void)
{
	WifiAudioPlayInit();
	xTaskCreate(WifitAudioPlaykEntrance, wifiAudioPlayName, WIFI_AUDIO_PLAY_TASK_STACK_SIZE, NULL, WIFI_AUDIO_PLAY_TASK_PRIO, &WIFI_AUDIO_PLAY(taskHandle));
	
}

int32_t WifiAudioPlayExit(void)
{
	WifiAudioPlayDeinit();
	vTaskDelete(WIFI_AUDIO_PLAY(taskHandle));
}

/**
 * @brief
 *		Start bt audio play program task.
 * @param
 * 	 NONE
 * @return  
 */
int32_t WifiAudioPlayStart(void)
{
	MessageContext		msgSend;

	msgSend.msgId		= MSG_APP_MODE_START;
	msgSend.msgParams	= NULL;
	MessageSend(WIFI_AUDIO_PLAY(msgHandle), &msgSend);

	return 0;
}

/**
 * @brief
 *		Exit bt audio play program task.
 * @param
 * 	 NONE
 * @return  
 */
void WifiAudioPlayStop(void)
{
	MessageContext		msgSend;

	msgSend.msgId		= MSG_APP_MODE_STOP;
	msgSend.msgParams	= NULL;
	MessageSend(WIFI_AUDIO_PLAY(msgHandle), &msgSend);
}

MemHandle * GetWifiAudioPlayDecoderBuffer(void)
{
	return &WIFI_AUDIO_PLAY(decoderMemHandle);
}


