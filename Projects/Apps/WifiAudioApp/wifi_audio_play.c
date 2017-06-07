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

#include "audio_core_service.h"
#include "decoder_service.h"

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

typedef struct _WifiAudioPlayContext
{
	xTaskHandle 		taskHandle;
	MessageHandle		msgHandle;
	MessageHandle		parentMsgHandle;
	
	ServiceState		state;

	ServiceState		wifiAudioServiceState;
	ServiceState		decoderServiceState;
	ServiceState		audioCoreServiceState;

	MessageHandle		wifiAudioServiceMsgHandle;
	MessageHandle		decoderServiceMsgHandle;
	MessageHandle		audioCoreServiceMsgHandle;

	QueueHandle_t 		audioMutex;

	MvRingBuffer		*deocdedBuf;

	MemHandle			*decoderMemHandle;
	int32_t				decoderIoType;
	int32_t				decoderType;
	SongInfo			*songInfo;
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
	return 1;
}


static BOOL WifiAudioSinkPutData(void * buf, uint16_t len)
{


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
	WifiAudioServiceCreate();
}

static void WaitWifiAudioPlayServices(void)
{
	while(1)
	{
		if(GetDecoderServiceState() == ServiceStateReady 
			&& GetWifiAudioServiceState() == ServiceStateReady
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


static void WifiAudioPlayModeStart(void)
{

}

static void WifiAudioPlayModeStop(void)
{
	vSemaphoreDelete(WIFI_AUDIO_PLAY(audioMutex));
}

static void WifiAudioPlayServicesCreate(void)
{
	// Create audio core service
	AudioCoreServiceCreate(WIFI_AUDIO_PLAY(msgHandle));

	// Create decoder service
	DecoderServiceCreate(WIFI_AUDIO_PLAY(msgHandle));

	// Create wifi audio servcie
//	WifiAudioServiceCreate(WIFI_AUDIO_PLAY(msgHandle));
}

static void MsgProcessServiceCreated(uint16_t msgParams)
{
	MessageContext		msgSend;

	if(msgParams == MSG_PARAM_WIFI_AUDIO_SERVICE)
	{
		WIFI_AUDIO_PLAY(wifiAudioServiceState) = ServiceStateReady;
		WIFI_AUDIO_PLAY(wifiAudioServiceMsgHandle) = GetWifiAudioServiceMsgHandle();
		WIFI_AUDIO_PLAY(decoderMemHandle) = GetWifiAudioServiceBuf();
	}
	else if(msgParams == MSG_PARAM_DECODER_SERVICE)
	{
		WIFI_AUDIO_PLAY(decoderServiceState) = ServiceStateReady;
		WIFI_AUDIO_PLAY(decoderServiceMsgHandle) = GetDecoderServiceMsgHandle();
		WIFI_AUDIO_PLAY(deocdedBuf) = GetDecoderServiceBuf();
	}
	else if(msgParams == MSG_PARAM_AUDIO_CORE_SERVICE)
	{
		WIFI_AUDIO_PLAY(audioCoreServiceState) = ServiceStateReady;
		WIFI_AUDIO_PLAY(audioCoreServiceMsgHandle) = GetAudioCoreServiceMsgHandle();
		AudioCoreModeSet(AUDIO_CORE_MODE_MIX);
	}


	if( WIFI_AUDIO_PLAY(audioCoreServiceState) == ServiceStateReady
		&& WIFI_AUDIO_PLAY(decoderServiceState) == ServiceStateReady )
	{
		if(WIFI_AUDIO_PLAY(wifiAudioServiceState) == ServiceStateReady)
		{
			WIFI_AUDIO_PLAY(state) = ServiceStateReady;

			/* 
			 * All of services is created
			 * Send CREATED message to parent
			 */
			msgSend.msgId		= MSG_SERVICE_CREATED;
			msgSend.msgParams	= MSG_PARAM_WIFI_AUDIO_PLAY;
			MessageSend(WIFI_AUDIO_PLAY(parentMsgHandle), &msgSend);
		}
		else if(WIFI_AUDIO_PLAY(wifiAudioServiceState) == ServiceStatePaused)
		{
			AudioCoreServiceStart();
			DecoderServiceStart();
			WifiAudioServiceResume();
		}
	}
}

static void MsgProcessServiceStarted(uint16_t msgParams)
{
	MessageContext		msgSend;
	
	if(msgParams == MSG_PARAM_WIFI_AUDIO_SERVICE)
	{
		WIFI_AUDIO_PLAY(wifiAudioServiceState) = ServiceStateRunning;
	}
	else if(msgParams == MSG_PARAM_DECODER_SERVICE)
	{
		WIFI_AUDIO_PLAY(decoderServiceState) = ServiceStateRunning;
	}
	else if(msgParams == MSG_PARAM_AUDIO_CORE_SERVICE)
	{
		WIFI_AUDIO_PLAY(audioCoreServiceState) = ServiceStateRunning;
	}

	if( WIFI_AUDIO_PLAY(audioCoreServiceState) == ServiceStateRunning
		&& WIFI_AUDIO_PLAY(decoderServiceState) == ServiceStateRunning
		&& WIFI_AUDIO_PLAY(wifiAudioServiceState) == ServiceStateRunning)
	{
		WIFI_AUDIO_PLAY(state) = ServiceStateRunning;
		
		/* 
		 * All of services is started
		 * Send STARTED message to parent
		 */
		msgSend.msgId		= MSG_SERVICE_STARTED;
		msgSend.msgParams	= MSG_PARAM_WIFI_AUDIO_PLAY;

		MessageSend(WIFI_AUDIO_PLAY(parentMsgHandle), &msgSend);
	}
}

static void MsgProcessServicePaused(uint16_t msgParams)
{
	MessageContext		msgSend;

	if(msgParams == MSG_PARAM_WIFI_AUDIO_SERVICE)
	{
		WIFI_AUDIO_PLAY(wifiAudioServiceState) = ServiceStatePaused;
	}

	if( WIFI_AUDIO_PLAY(audioCoreServiceState) == ServiceStateStopped
		&& WIFI_AUDIO_PLAY(decoderServiceState) == ServiceStateStopped
		&& WIFI_AUDIO_PLAY(wifiAudioServiceState) == ServiceStatePaused )
	{
		WIFI_AUDIO_PLAY(state) = ServiceStatePaused;

		msgSend.msgId		= MSG_SERVICE_PAUSED;
		msgSend.msgParams	= MSG_PARAM_WIFI_AUDIO_PLAY;

		MessageSend(WIFI_AUDIO_PLAY(parentMsgHandle), &msgSend);
	}
}

static void MsgProcessServiceStopped(uint16_t msgParams)
{
	MessageContext		msgSend;

	if(msgParams == MSG_PARAM_WIFI_AUDIO_SERVICE)
	{
		WIFI_AUDIO_PLAY(wifiAudioServiceState) = ServiceStateStopped;
		WifiAudioServiceKill();
	}
	else if(msgParams == MSG_PARAM_DECODER_SERVICE)
	{
		WIFI_AUDIO_PLAY(decoderServiceState) = ServiceStateStopped;
		DecoderServiceKill();
	}
	else if(msgParams == MSG_PARAM_AUDIO_CORE_SERVICE)
	{
		WIFI_AUDIO_PLAY(audioCoreServiceState) = ServiceStateStopped;
		AudioCoreServiceKill();
	}

	if( WIFI_AUDIO_PLAY(audioCoreServiceState) == ServiceStateStopped
		&& WIFI_AUDIO_PLAY(decoderServiceState) == ServiceStateStopped )
	{
		if(WIFI_AUDIO_PLAY(wifiAudioServiceState) == ServiceStateStopped)
		{
			WIFI_AUDIO_PLAY(state) = ServiceStateStopped;
			/* 
			 * All of services is stopped
			 * Send STOPPED message to parent
			 */
			msgSend.msgId		= MSG_SERVICE_STOPPED;
			msgSend.msgParams	= MSG_PARAM_WIFI_AUDIO_PLAY;

			MessageSend(WIFI_AUDIO_PLAY(parentMsgHandle), &msgSend);
		}
		else if(WIFI_AUDIO_PLAY(wifiAudioServiceState) == ServiceStatePaused)
		{
			WIFI_AUDIO_PLAY(state) = ServiceStatePaused;
			
			msgSend.msgId		= MSG_SERVICE_PAUSED;
			msgSend.msgParams	= MSG_PARAM_WIFI_AUDIO_PLAY;

			MessageSend(WIFI_AUDIO_PLAY(parentMsgHandle), &msgSend);
		}
	}
}

static void MsgProcessServiceStart(uint16_t msgParams)
{

	ServiceState		state;

	state = WIFI_AUDIO_PLAY(state);

	switch(state)
	{
		case ServiceStateReady:
			{
				// Init & start releated services
				WIFI_AUDIO_PLAY(state) = ServiceStateStarting;
				WifiAudioServiceInit();
				WifiAudioServiceStart();
			}
			break;
		default:
			break;
	}
}

static void MsgProcessServicePause(uint16_t msgParams)
{

	ServiceState		state;

	state = WIFI_AUDIO_PLAY(state);

	switch(state)
	{
		case ServiceStateRunning:
			{
				WIFI_AUDIO_PLAY(state) = ServiceStatePausing;
				WifiAudioServicePause();
				AudioCoreServiceStop();
				DecoderServiceStop();
			}
			break;

		default:
			break;
	}
}

static void MsgProcessServiceResume(uint16_t msgParams)
{

	ServiceState		state;

	state = WIFI_AUDIO_PLAY(state);
	switch(state)
		{
			case ServiceStatePaused:
				{
					WIFI_AUDIO_PLAY(state) = ServiceStateResuming;

					// Resume wifi audio service
					WifiAudioServiceResume();
					// Create audio core service
					AudioCoreServiceCreate(WIFI_AUDIO_PLAY(msgHandle));
					// Create decoder service
					DecoderServiceCreate(WIFI_AUDIO_PLAY(msgHandle));
					
				}
				break;
	
			default:
				break;
		}
}

static void MsgProcessServiceStop(uint16_t msgParams)
{
	WIFI_AUDIO_PLAY(state) = ServiceStateStopping;

	if(WIFI_AUDIO_PLAY(audioCoreServiceState) != ServiceStateStopped)
	{
		AudioCoreServiceStop();
	}

	if(WIFI_AUDIO_PLAY(decoderServiceState) != ServiceStateStopped)
	{
		DecoderServiceStop();
	}

	if(WIFI_AUDIO_PLAY(wifiAudioServiceState) != ServiceStateStopped)
	{
		WifiAudioServiceStop();
	}
}

static void MsgProcessWifiDataReady(void)
{
	int32_t					ret;
	AudioCorePcmParams		acPcmParams;
	SongInfo				*songInfo;


	WIFI_AUDIO_PLAY(decoderIoType) = IO_TYPE_MEMORY;
	WIFI_AUDIO_PLAY(decoderType) = MP3_DECODER;

	// Initialize decoder
	ret = DecoderInit(&WIFI_AUDIO_PLAY(decoderMemHandle), 
						WIFI_AUDIO_PLAY(decoderIoType), 
						WIFI_AUDIO_PLAY(decoderType),
						&WIFI_AUDIO_PLAY(songInfo));

	if(ret != RT_SUCCESS)
	{
		DBG("Decoder Init Error\n");
		return;
	}

	// Config audio core source
	songInfo = WIFI_AUDIO_PLAY(songInfo);
	if(songInfo == NULL)
		return;

	acPcmParams.channelNums		= songInfo->num_channels;
	acPcmParams.pcmDataMode		= songInfo->pcm_data_mode;
	acPcmParams.samplingRate	= songInfo->sampling_rate;
	acPcmParams.bitRate			= songInfo->bitrate;
	AC_MixSourcePcmParamsConfig(0, &acPcmParams);

	AC_MixSourceEnable(0);

	// start decoder & audio core service
	DecoderServiceStart();
	AudioCoreServiceStart();
}

static void WifitAudioPlaykEntrance(void * param)
{
	MessageContext		msgRecv;
	MessageContext		msgSend;


	// Create services
	WifiAudioPlayServicesCreate();

	while(1)
	{
		MessageRecv(WIFI_AUDIO_PLAY(msgHandle), &msgRecv, MAX_RECV_MSG_TIMEOUT);

		switch(msgRecv.msgId)
		{
			case MSG_SERVICE_CREATED:
				{
					MsgProcessServiceCreated(msgRecv.msgParams);
				}
				break;

			case MSG_SERVICE_STARTED:
				{
					MsgProcessServiceStarted(msgRecv.msgParams);
				}
				break;

			case MSG_SERVICE_PAUSED:
				{
					MsgProcessServicePaused(msgRecv.msgParams);
				}
				break;

			case MSG_SERVICE_STOPPED:
				{
					MsgProcessServiceStopped(msgRecv.msgParams);
				}
				break;

			case MSG_SERVICE_START:
				{
					MsgProcessServiceStart(msgRecv.msgParams);
				}
				break;

			case MSG_SERVICE_PAUSE:
				{
					MsgProcessServicePause(msgRecv.msgParams);
				}
				break;

			case MSG_SERVICE_RESUME:
				{
					MsgProcessServiceResume(msgRecv.msgParams);
				}
				break;

			case MSG_SERVICE_STOP:
				{
					MsgProcessServiceStop(msgRecv.msgParams);
				}
				break;

			case MSG_WIFI_AUDIO_SERVICE_DATA_READY:
				{
					MsgProcessWifiDataReady();
				}
				break;

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


static int32_t WAP_Init(MessageHandle parentMsgHandle)
{
	memset(&wifiAudioPlayCt, 0, sizeof(WifiAudioPlayContext));

	/* message handle */
	WIFI_AUDIO_PLAY(msgHandle) = MessageRegister(WIFI_AUDIO_NUM_MESSAGE_QUEUE);

	/* Parent message handle */
	WIFI_AUDIO_PLAY(parentMsgHandle) = parentMsgHandle;

	WIFI_AUDIO_PLAY(wifiAudioServiceState) = ServiceStateNone;
	WIFI_AUDIO_PLAY(decoderServiceState) = ServiceStateNone;
	WIFI_AUDIO_PLAY(audioCoreServiceState) = ServiceStateNone;

	WIFI_AUDIO_PLAY(decoderIoType) = IO_TYPE_MEMORY;
	WIFI_AUDIO_PLAY(decoderType) = MP3_DECODER;


	WIFI_AUDIO_PLAY(audioMutex) = xSemaphoreCreateMutex();

	ConfigPhub4WifiAudioPlay();

	PcmFifoInitialize(PCM_FIFO_OFFSET, PCM_FIFO_SIZE, 0, 0);
	PcmFifoPause();

	return 0;
}

static void WAP_Deinit(void)
{
	MessageContext		msgSend;
	MessageHandle		mainHandle;

	/* Deconfig audio path*/
	DeconfigPhub2WifiAudioPlay();


	/* Write storage parameters */
//	PrefrenceSave(btAudioPlayStorName, &BT_AUDIO_PLAY(params), sizeof(BtAudioPlayParams));

	/* Send message to main app */
	mainHandle = GetMainMessageHandle();

	msgSend.msgId		= MSG_SERVICE_STOPPED;
	msgSend.msgParams	= MSG_PARAM_WIFI_AUDIO_PLAY;
	MessageSend(mainHandle, &msgSend);

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

int32_t WifiAudioPlayCreate(MessageHandle parentMsgHandle)
{
	WAP_Init(parentMsgHandle);
	xTaskCreate(WifitAudioPlaykEntrance, 
				wifiAudioPlayName,
				WIFI_AUDIO_PLAY_TASK_STACK_SIZE,
				NULL, WIFI_AUDIO_PLAY_TASK_PRIO,
				&WIFI_AUDIO_PLAY(taskHandle));
}

int32_t WifiAudioPlayKill(void)
{
	WAP_Deinit();
	vTaskDelete(WIFI_AUDIO_PLAY(taskHandle));
}

int32_t WifiAudioPlayStart(void)
{
	MessageContext		msgSend;

	msgSend.msgId		= MSG_SERVICE_START;
	msgSend.msgParams	= NULL;
	MessageSend(WIFI_AUDIO_PLAY(msgHandle), &msgSend);

	return 0;
}

int32_t WifiAudioPlayPause(void)
{
	MessageContext		msgSend;

	msgSend.msgId		= MSG_SERVICE_PAUSE;
	msgSend.msgParams	= NULL;
	MessageSend(WIFI_AUDIO_PLAY(msgHandle), &msgSend);

	return 0;
}

int32_t WifiAudioPlayResume(void)
{
	MessageContext		msgSend;

	msgSend.msgId		= MSG_SERVICE_RESUME;
	msgSend.msgParams	= NULL;
	MessageSend(WIFI_AUDIO_PLAY(msgHandle), &msgSend);

	return 0;
}

int32_t WifiAudioPlayStop(void)
{
	MessageContext		msgSend;

	msgSend.msgId		= MSG_SERVICE_STOP;
	msgSend.msgParams	= NULL;
	MessageSend(WIFI_AUDIO_PLAY(msgHandle), &msgSend);

	return 0;
}


