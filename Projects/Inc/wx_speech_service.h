/**
 **************************************************************************************
 * @file    wx_speech_service.h
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

#ifndef __WX_SPEECH_SERVICE_H__
#define __WX_SPEECH_SERVICE_H__

#include "type.h"
#include "app_message.h"
#include "freertos.h"
#include "rtos_api.h"

//wx speech file download err
#define FILE_DOWNLOAD_INVALID	-2	// accesstoken id invalid / media id invalid
#define FILE_DOWNLOAD_ERR		-1
#define FILE_DOWNLOAD_OK		0
#define FILE_DOWNLOAD_DROPOUT	1
#define FILE_DOWNLOAD_NEXT		2

//wx cloud response
#define RESP_OK						0
#define RESP_SYSTEM_BUSY			-1
#define RESP_ACCESS_TOKEN_INVALID	40001
#define RESP_MEDIA_ID_INVALID		40007
#define RESP_MEDIA_ID_MISSING		41006

//get wx speech infor status
#define WX_SPEECH_GET_SUCCESS		0
#define WX_SPEECH_GET_FAIL			-1
#define WX_SPEECH_GET_DATA_ERR		-2

//wx record led 
#define LEDOFF			0
#define LEDON			1

typedef enum
{
	WxSpeechPlayMode = 0,
	WxSpeechRecordMode,
}WxSpeechMode;

typedef enum
{
	WxSpeechPlay_Idle = 0,
	WxSpeechPlay_Start,
	WxSpeechPlay_Runing,
	WxSpeechPlay_WaitForEnd,
	WxSpeechPlay_End,
	WxSpeechPlay_Next,
	WxSpeechPlay_Prev,
	WxSpeechPlay_Stop,
}WxSpeechPlayStage;

typedef enum
{
	WxSpeechRecord_Idle = 0,
	WxSpeechRecord_Start,
	WxSpeechRecord_CollectAndEncoder,
	WxSpeechRecord_End,
	WxSpeechRecord_Send2Family,
	WxSpeechRecord_Send2Friend,
	WxSpeechRecord_Stop,
}WxSpeechRecordStage;

typedef enum
{
	WxSpeechSend2Family = 0,
	WxSpeechSend2Friend,
}WxSpeechSendMode;

typedef enum
{
	WxSpeechEnd = 0,
	WxSpeechNext,
	WxSpeechDropout,
}WxSpeechControl;

typedef struct _WxSpeechContext
{
	WxSpeechMode		wxSpeechMode;

	//play params
	WxSpeechPlayStage	wxSpeechPlayStage;
	bool				newWxSpeech;
	uint8_t				wxSpeechLedFlash;
	WxSpeechControl		wxSpeechControl;		//end?next?dropout?
	bool				wxSpeechStart;

	//record params
	WxSpeechRecordStage wxSpeechRecordStage;
	WxSpeechSendMode	wxSpeechSendMode;

	
}WxSpeechContext;
/*
typedef struct _WxSpeechServiceContext
{
	xTaskHandle 		taskHandle;
	MessageHandle		msgHandle;
	ServiceState		serviceState;

	//wx speech play
	xTaskHandle 		playTaskHandle;
	MessageHandle		playMsgHandle;
	MemHandle			SpeechMemHandle;

	//wx speech record
	xTaskHandle 		recordTaskHandle;
	MessageHandle		recordMsgHandle;
}WxSpeechServiceContext;
*/

MessageHandle GetWxSpeechServiceMessageHandle(void);

ServiceState GetWxSpeechServiceState(void);

int32_t WxSpeechServiceCreate(void);

void WxSpeechServiceStart(void);

void WxSpeechServiceStop(void);

void WxSpeechServiceKill(void);

#endif /*__WX_SPEECH_SERVICE_H__*/

