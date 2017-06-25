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
	DSDownloadHeader,
	DSDownloadContent,
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
	bool				sendDataReady;

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

/***************************************************************************************
 *
 * Internal functions
 *
 */
static void WAS_Init(MessageHandle parentMsgHandle)
{
	memset(&wifiAudioServiceCt, 0, sizeof(WifiAudioServiceContext));

	WAS(parentMsgHandle) = parentMsgHandle;

	WAS(bufHandle).addr = (uint8_t *) SDRAM_BASE_ADDR + SDRAM_SIZE/2;
	WAS(bufHandle).mem_capacity = SDRAM_SIZE/2;
	WAS(bufHandle).mem_len = 0;
	WAS(bufHandle).p = 0;
}

static void WAS_Deinit(void)
{

}

static void parser_http(uint8_t *buf, uint32_t buf_len, uint32_t *phead_len, uint32_t *pdata_len)
{
	uint32_t len = 0;
	while(len < buf_len)
	{
		if(buf[len++] == '\n')
		{
			if(memcmp(&buf[len],"Content-Length",14) == 0)
			{
				len += 16;
				sscanf(&buf[len],"%d",pdata_len);
				break;
			}
		}
	}
	
	len+=4;
	while(len < buf_len)
	{
		if(buf[len++] == '\r')
		{
			if(buf[len+1] == '\r')
			{
				len+=3;
				*phead_len = len;
				break;
			}
		}
	}
}
static int app_tcp_recv(int socket, char *buf, uint32_t size, uint32_t timeout)
{
	int ret;
	fd_set rfds;
	struct timeval tmo;
	tmo.tv_sec = timeout/1000;
	timeout = timeout%1000;
	tmo.tv_usec = timeout*1000;

	FD_ZERO(&rfds);
	FD_SET(socket, &rfds);
	ret = select(socket+1, &rfds, NULL, NULL, &tmo);
	if(ret != 0)
	{
		if(FD_ISSET(socket, &rfds))
		{
			ret = recv( socket, buf, size, 0);
			if(ret < 0)
			{
				return -1;
			}
			else
			{
				return ret;
			}
		}
	}
	return 0;
}
static int16_t wifi_read(int32_t sock,uint8_t *temp_buffer,uint16_t recv_len,uint32_t timeout)
{

	uint16_t len,nodata;
	len = 0;
	nodata = 0;
	timeout /= 100;
	while(len == 0)
	{
		len = app_tcp_recv(sock,temp_buffer,recv_len,0);
		if(len != 0)
		{
			break;
		}
		vTaskDelay(100);
		nodata++;
		if(nodata > timeout)
		{
			break;
		}
	}
	return len;
}

static void WAS_Run(void)
{
	uint32_t		len;

	switch(WAS(downloadState))
	{
		case DSNone:
			WAS(downloadState) = DSConnecting;
			break;

		case DSConnecting:
			// connect url
			break;

		case DSConnected:
			WAS(downloadState) = DSDownloadHeader;
		case DSDownloadHeader:
			{

				len = read(WAS(sock), WAS(tempBuf), DOWNLOAD_SIZE_EACH);
				mv_mwrite(WAS(tempBuf), 1, len, &WAS(bufHandle));
				WAS(totalLen) += len;

				parser_http(WAS(tempBuf), len, &WAS(headerLen), &WAS(contentLen));

				WAS(downloadState) = DSDownloadContent;
			}

		case DSDownloadContent:
			if( WAS(totalLen) >= WAS(headerLen)+ WAS(contentLen))
			{
				// download finished
				WAS(downloadState) = DSDownloadFinished;
				break;
			}

			if(mv_mremain(&WAS(bufHandle)) < 2 * DOWNLOAD_SIZE_EACH)
			{
				vTaskDelay(10);
				break;
			}

			len = wifi_read(WAS(sock), WAS(tempBuf), DOWNLOAD_SIZE_EACH, DOWNLOAD_TIMEOUT);
			WAS(totalLen) += len;

			mv_mwrite(WAS(tempBuf), 1, len, &WAS(bufHandle));

			if(WAS(totalLen) > WAS(thresholdLen) && !WAS(sendDataReady))
			{
				MessageContext		msgSend;

				msgSend.msgId = MSG_WIFI_AUDIO_SERVICE_DATA_READY;
				msgSend.msgParams = NULL;

				MessageSend(WAS(parentMsgHandle), &msgSend);

				WAS(sendDataReady) = TRUE;
			}
			break;


		case DSDownloadFinished:
			break;
	}
}

static void WAS_ProcessMsgStart(uint16_t msgParams)
{
	MessageContext		msgSend;

	WAS(state) = ServiceStateRunning;

	msgSend.msgId = MSG_SERVICE_STARTED;
	msgSend.msgParams = MSG_PARAM_WIFI_AUDIO_SERVICE;

	MessageSend(WAS(parentMsgHandle), &msgSend);
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

	while(1)
	{
		MessageRecv(WAS(msgHandle), &msgRecv, WAS_RECV_MSG_TIMEOUT);

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

		if(WAS(state) == ServiceStateRunning)
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
	return &WAS(bufHandle);
}

void WifiAudioServiceInit(void)
{
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

