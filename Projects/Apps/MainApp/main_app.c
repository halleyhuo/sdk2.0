/**
 **************************************************************************************
 * @file    main_app.c
 * @brief   Program Entry 
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
#include "app_mode.h"
#include "app_message.h"

//#include "bluetooth_service.h"
#include "device_service.h"
#include "decoder_service.h"
#include "audio_core_service.h"
#include "wifi_service.h"
#include "app_config.h"
#include "key.h"


/***************************************************************************************
 *
 * External defines
 *
 */

#define MAIN_APP_TASK_STACK_SIZE	1024
#define MAIN_APP_TASK_PRIO			3


/***************************************************************************************
 *
 * Internal defines
 *
 */

#define MAIN_NUM_MESSAGE_QUEUE		10

typedef struct _MainAppContext
{
	xTaskHandle			taskHandle;
	MessageHandle		msgHandle;
	AppMode				appCurrentMode;
}MainAppContext;


/***************************************************************************************
 *
 * Internal varibles
 *
 */

static MainAppContext	mainAppCt;
#define MAIN_APP(x)		(mainAppCt.x)


//static MainAppContext	*mainAppCt;
//#define MAIN_APP(x)		(mainAppCt->x)


/***************************************************************************************
 *
 * Internal functions
 *
 */
static int32_t MainAppInit(void)
{
	memset(&mainAppCt, 0, sizeof(MainAppContext));

	MAIN_APP(msgHandle) = MessageRegister(MAIN_NUM_MESSAGE_QUEUE);

	return 0;
}


static void CreateService(void)
{
//	BluetoothServiceStart();

	DeviceServiceCreate();
//	DecoderServiceCreate();
//	AudioCoreServiceCreate();

	//wifi service
	WifiServiceCreate(mainAppCt.msgHandle);
	//wxcloud service
	WxcloudServiceCreate();
}

static void ServiceCreated(uint16_t msgParams)
{
	switch(msgParams)
	{
		case MSG_PARAM_WIFI_AUDIO_PLAY:
			WifiAudioPlayStart();
			break;

		case MSG_PARAM_DEVICE_SERVICE_ID:
			DeviceServiceStart();
			break;

		case MSG_PARAM_AUDIO_CORE_SERVICE:
			break;

		case MSG_PARAM_DECODER_SERVICE:
			break;

		case MSG_PARAM_WIFI_SERVICE:
			WifiServiceStart();
			break;

		case MSG_PARAM_MEDIA_SERVICE:
			break;
			
		default:
			break;
	}
}

static void ServiceStarted(uint16_t msgParams)
{
	switch(msgParams)
	{
		case MSG_PARAM_WIFI_AUDIO_PLAY:
			break;

		case MSG_PARAM_DEVICE_SERVICE_ID:
			break;

		case MSG_PARAM_AUDIO_CORE_SERVICE:
			break;

		case MSG_PARAM_DECODER_SERVICE:
			break;

		case MSG_PARAM_WIFI_SERVICE:
			//微信云服务在wifi service running 之后再start
			WxcloudServiceStart();
			break;

		case MSG_PARAM_MEDIA_SERVICE:
			break;
			
		default:
			break;
	}
}

static MessageId KeyEventConvert(uint16_t msgParams)
{
	KeyEvent		keyEvent;
	KeyValue		keyValue;

	keyEvent = (msgParams & 0xFF00) >> 8;
	keyValue = (msgParams & 0x00FF);

	DBG("keyEvent = 0x%02x, keyValue = 0x%02x\n", keyEvent, keyValue);
	return GetWifiAudioKeyMap(keyValue, keyEvent);
}

static void MainAppTaskEntrance(void * param)
{
	MessageContext		msg;
	bool msgRet;


	CreateService();

	EnterMode(MAIN_APP(appCurrentMode));

	while(1)
	{
		msgRet = MessageRecv(MAIN_APP(msgHandle), &msg, MAX_RECV_MSG_TIMEOUT);

		if(!msgRet)
		{
			continue;
		}
		
		switch(msg.msgId)
		{
			case MSG_SERVICE_CREATED:
				ServiceCreated(msg.msgParams);
				break;

			case MSG_SERVICE_STARTED:
				ServiceStarted(msg.msgParams);
				break;

			case MSG_KEY_EVENT:
				{
					MessageId		msgId;
					MessageHandle	msgHandle;
					MessageContext	msgSend;

					msgId = KeyEventConvert(msg.msgParams);
					msgHandle = GetWifiAudioPlayMessageHandle();

					msgSend.msgId = msgId;
					msgSend.msgParams = NULL;
					MessageSend(msgHandle, &msgSend);
				}
				break;

			case MSG_WXCLOUD_EVENT:
				{
					MessageHandle	msgHandle;
					MessageContext	msgSend;

					DBG("[MAIN_APP]: MSG_WXCLOUD_EVENT.\n");

					msgSend.msgParams = NULL;
					msgSend.msgId = NULL;
					switch(msg.msgParams)
					{
						case MSG_PARAM_PRE_SONG:
							msgSend.msgId = MSG_WIFI_AUDIO_PRE;
							break;
							
						case MSG_PARAM_NEXT_SONG:
							msgSend.msgId = MSG_WIFI_AUDIO_NEXT;
							break;
							
						case MSG_PARAM_PLAY_SONG:
							msgSend.msgId = MSG_WIFI_AUDIO_PLAY_PAUSE;
							break;

						case MSG_PARAM_PUSH_LIST:
							msgSend.msgId = MSG_WIFI_AUDIO_PUSH_SONG;
							break;

					}

					if(msgSend.msgId)
					{
						msgHandle = GetWifiAudioPlayMessageHandle();
						MessageSend(msgHandle, &msgSend);
					}
				}
				break;
		}
	}
}

/***************************************************************************************
 *
 * APIs
 *
 */


/**
 * @brief
 *		Start a main program task.
 * @param
 *		NONE
 * @return	
 */
int32_t MainAppTaskStart(void)
{
	MainAppInit();

	xTaskCreate(MainAppTaskEntrance, "MainApp", MAIN_APP_TASK_STACK_SIZE, NULL, MAIN_APP_TASK_PRIO, &MAIN_APP(taskHandle));

	return 0;
}



MessageHandle GetMainMessageHandle(void)
{
	return MAIN_APP(msgHandle);
}

