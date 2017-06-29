/**
 **************************************************************************************
 * @file    wifi_audio_service.c
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
#include "app_message.h"
#include "audio_utility.h"
#include "sockets.h"
#include "app_config.h"
#include "wifi_audio_api.h"
#include "sys_app.h"

/***************************************************************************************
 *
 * External defines
 *
 */

#define WIFI_AUDIO_SERVICE_TASK_STACK_SIZE		1024
#define WIFI_AUDIO_SERVICE_TASK_PRIO			3



/***************************************************************************************
 *
 * Internal defines
 *
 */

#define MAX_URL_LEN								256
#define DOWNLOAD_SIZE_EACH						1024
#define DOWNLOAD_TIMEOUT						4000

typedef enum
{
	DSNone,
	DSConnecting,
	DSConnected,
	DSDownloading,
	DSDownloadFinished
} DownloadState;

typedef struct _WifiAudioServiceContext
{
	xTaskHandle 		taskHandle;
	MessageHandle		msgHandle;
	MessageHandle		parentMsgHandle;
	ServiceState		state;

	int16_t 			sock;
	DownloadState		downloadState;
	MemHandle			bufHandle;
	uint32_t			totalLen;
	uint8_t				tempBuf[DOWNLOAD_SIZE_EACH];
	uint32_t			thresholdLen;
	BOOL				sendDataReady;
	uint32_t			position;

	char				url[MAX_URL_LEN];
	uint32_t			headerLen;
	uint32_t			contentLen;
	uint32_t			downloadedLen;
}WifiAudioServiceContext;

#define WAS_RECV_MSG_TIMEOUT					2

/***************************************************************************************
 *
 * Internal varibles
 *
 */

static WifiAudioServiceContext		wifiAudioServiceCt;
#define WAS(x)						(wifiAudioServiceCt.x)

/** wifi audio service name*/
const char wifiAudioServiceName[] = "WifiAudioService";

#define WAS_NUM_MESSAGE_QUEUE	10

extern PLAY_LIST *WifiAudioPlayList;
/***************************************************************************************
 *
 * Internal functions
 *
 */
static void WAS_Init(MessageHandle parentMsgHandle)
{
	memset(&wifiAudioServiceCt, 0, sizeof(WifiAudioServiceContext));

	wifiAudioServiceCt.parentMsgHandle = parentMsgHandle;

	wifiAudioServiceCt.bufHandle.addr = (uint8_t *) (SDRAM_BASE_ADDR + SDRAM_SIZE/2);
	wifiAudioServiceCt.bufHandle.mem_capacity = SDRAM_SIZE/2;
	wifiAudioServiceCt.bufHandle.mem_len = 0;
	wifiAudioServiceCt.bufHandle.p = 0;

	memset(wifiAudioServiceCt.bufHandle.addr, 0, SDRAM_SIZE/2);
	
	wifiAudioServiceCt.msgHandle = MessageRegister(WAS_NUM_MESSAGE_QUEUE);

	WifiAudioInit();
}

static void WAS_Deinit(void)
{

}

#if 0 // Halley for test
uint8_t testUrl[] = "http://fdfs.xmcdn.com/group8/M02/63/6D/wKgDYFXZ08yQ2D2tANIQkbsykWo940.mp3";
#endif

static void WAS_Run(void)
{
	uint32_t		len;
	WAudioStatus	WAState = WAUDIO_STATUS_SUCCESS;
	uint8_t 		*WASongBuf = wifiAudioServiceCt.tempBuf;
	MemHandle 		*WASongMem = GetWifiAudioServiceBuf();

	switch(wifiAudioServiceCt.downloadState)
	{
		case DSNone:
			wifiAudioServiceCt.position = 0;
			wifiAudioServiceCt.downloadState = DSConnecting;
			DBG("****** downloadState: [DSConnecting]\n");
			break;

		case DSConnecting:
			// connect url
#if 0 // Halley for test
			WAState = WifiAudioGetMediaStart(testUrl, 0);
#endif
			WAState = WifiAudioGetMediaStart(wifiAudioServiceCt.url, wifiAudioServiceCt.position);
			if(WAState == WAUDIO_STATUS_SUCCESS)
			{
				{
					MessageContext	msgSend;

					msgSend.msgId = MSG_WIFI_AUDIO_DOWLOAD_START;
					msgSend.msgParams = NULL;

					MessageSend(wifiAudioServiceCt.parentMsgHandle, &msgSend);
				}
				
				wifiAudioServiceCt.downloadState = DSConnected;
				DBG("****** downloadState: [DSConnected]\n");
			}
			
			break;

		case DSConnected:
			WAState = WifiAudioGetMedia(&WASongBuf, &wifiAudioServiceCt.downloadedLen, &wifiAudioServiceCt.position);
			if(WAState == WAUDIO_STATUS_SUCCESS)
			{
				wifiAudioServiceCt.downloadState = DSDownloading;
				
				if(wifiAudioServiceCt.downloadedLen)
				{
					mv_mwrite(WASongBuf, 1, wifiAudioServiceCt.downloadedLen, WASongMem);
				}

				DBG("****** downloadState: [DSDownloading]\n");
			}
			break;

		case DSDownloading:

			if(!wifiAudioServiceCt.sendDataReady)
			{
				if(mv_msize(WASongMem) > wifiAudioServiceCt.thresholdLen)
				{
					// Send DATA_READY message to parent task
					MessageContext	msgSend;

					msgSend.msgId = MSG_WIFI_AUDIO_SERVICE_DATA_READY;
					msgSend.msgParams = NULL;
					MessageSend(wifiAudioServiceCt.parentMsgHandle, &msgSend);

					// Send this message only once
					wifiAudioServiceCt.sendDataReady = TRUE;
				}
			}

			if(mv_msize(WASongMem) == 0)
			{
				// If there is none data in memory, send DATA_EMPTY to parent task
				MessageContext	msgSend;
				
				msgSend.msgId = MSG_WIFI_AUDIO_SERVICE_DATA_EMPTY;
				msgSend.msgParams = NULL;
				MessageSend(wifiAudioServiceCt.parentMsgHandle, &msgSend);

				wifiAudioServiceCt.sendDataReady = FALSE;
			}
			
			
			{
				WAState = WifiAudioGetMedia(&WASongBuf, &wifiAudioServiceCt.downloadedLen, &wifiAudioServiceCt.position);
				//DBG("download len = %d\n",wifiAudioServiceCt.downloadedLen);

				if(WAState == WAUDIO_STATUS_SUCCESS)
				{
					if(wifiAudioServiceCt.downloadedLen > 0)
					{
						mv_mwrite(WASongBuf, 1, wifiAudioServiceCt.downloadedLen, WASongMem);
					}
				}
				else if(WAState == WAUDIO_STATUS_NO_MORE_DATA)
				{
					wifiAudioServiceCt.downloadState = DSDownloadFinished;
					DBG("****** downloadState: [DSDownloadFinished]\n");
				}
				else
				{
					//err
					break;
				}

				if(wifiAudioServiceCt.downloadedLen <= 0)
				{
					//err
					break;
				}
				vTaskDelay(5);
			}
			break;

		case DSDownloadFinished:
			wifiAudioServiceCt.state = ServiceStateNone;
			wifiAudioServiceCt.downloadState = DSNone;
			DBG("****** downloadState: [End]\n");

			WifiAudioGetMediaStop();
			
			{
				MessageContext	msgSend;

				msgSend.msgId = MSG_WIFI_AUDIO_DOWLOAD_FINISHED;
				msgSend.msgParams = NULL;

				MessageSend(wifiAudioServiceCt.parentMsgHandle, &msgSend);
			}
			break;
	}
	
}

static void WAS_ProcessMsgStart(uint16_t msgParams)
{
	MessageContext		msgSend;
	MessageHandle		msgHandle;

	msgHandle = GetWifiAudioPlayMessageHandle();
	WAS(state) = ServiceStateRunning;

	msgSend.msgId = MSG_SERVICE_STARTED;
	msgSend.msgParams = MSG_PARAM_WIFI_AUDIO_SERVICE;

	MessageSend(msgHandle, &msgSend);
}

static void WAS_ProcessMsgPause(uint16_t msgParams)
{

}

static void WAS_ProcessMsgResume(uint16_t msgParams)
{

}

static void WAS_ProcessMsgStop(uint16_t msgParams)
{

}


static void WifiAudioServiceEntrance(void * param)
{
	MessageContext		msgRecv;
	MessageContext		msgSend;

	/* Send message to parent */
	msgSend.msgId		= MSG_SERVICE_CREATED;
	msgSend.msgParams	= MSG_PARAM_WIFI_AUDIO_SERVICE;
	MessageSend(wifiAudioServiceCt.parentMsgHandle, &msgSend);

	while(1)
	{
		MessageRecv(wifiAudioServiceCt.msgHandle, &msgRecv, WAS_RECV_MSG_TIMEOUT);

		switch(msgRecv.msgId)
		{
			case MSG_SERVICE_CREATED:
				break;

			case MSG_SERVICE_STARTED:
				break;

			case MSG_SERVICE_PAUSED:
				break;

			case MSG_SERVICE_STOPPED:
				break;

			case MSG_SERVICE_START:
				{
					WAS_ProcessMsgStart(msgRecv.msgParams);
				}
				break;

			case MSG_SERVICE_PAUSE:
				{
					WAS_ProcessMsgPause(msgRecv.msgParams);
				}
				break;

			case MSG_SERVICE_RESUME:
				{
					WAS_ProcessMsgResume(msgRecv.msgParams);
				}
				break;

			case MSG_SERVICE_STOP:
				{
					WAS_ProcessMsgStop(msgRecv.msgParams);
				}
				break;
		}

		if(wifiAudioServiceCt.state == ServiceStateRunning)
		{
			WAS_Run();
		}
	}
}






/***************************************************************************************
 *
 * APIs
 *
 */
MessageHandle GetWifiAudioServiceMsgHandle(void)
{
	return WAS(msgHandle);
}

ServiceState GetWifiAudioServiceState(void)
{
	return WAS(state);
}

void WifiAudioServiceConnect(const char * url, uint16_t urlLen)
{
	strncpy(WAS(url), url, urlLen);
}

MemHandle * GetWifiAudioServiceBuf(void)
{
	return &wifiAudioServiceCt.bufHandle;
}

int32_t WifiAudioServiceCreate(MessageHandle parentMsgHandle)
{
	WAS_Init(parentMsgHandle);
	xTaskCreate(WifiAudioServiceEntrance, 
				wifiAudioServiceName,
				WIFI_AUDIO_SERVICE_TASK_STACK_SIZE,
				NULL,
				WIFI_AUDIO_SERVICE_TASK_PRIO,
				&WAS(taskHandle));
}

void WifiAudioServiceInit(uint32_t thresholdLen)
{
	wifiAudioServiceCt.thresholdLen = thresholdLen;
}

int32_t WifiAudioServiceKill(void)
{
	WAS_Deinit();
	vTaskDelete(WAS(taskHandle));
}

int32_t WifiAudioServiceStart(void)
{
	MessageContext		msgSend;

	msgSend.msgId		= MSG_SERVICE_START;
	msgSend.msgParams	= NULL;
	MessageSend(WAS(msgHandle), &msgSend);

	return 0;
}

int32_t WifiAudioServicePause(void)
{
	MessageContext		msgSend;

	msgSend.msgId		= MSG_SERVICE_PAUSE;
	msgSend.msgParams	= NULL;
	MessageSend(WAS(msgHandle), &msgSend);

	return 0;
}

int32_t WifiAudioServiceResume(void)
{
	MessageContext		msgSend;

	msgSend.msgId		= MSG_SERVICE_RESUME;
	msgSend.msgParams	= NULL;
	MessageSend(WAS(msgHandle), &msgSend);

	return 0;
}

int32_t WifiAudioServiceStop(void)
{
	MessageContext		msgSend;

	msgSend.msgId		= MSG_SERVICE_STOP;
	msgSend.msgParams	= NULL;
	MessageSend(WAS(msgHandle), &msgSend);

	return 0;
}

