/**
 **************************************************************************************
 * @file    message.c
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


#ifndef __APP_MESSAGE_H__
#define __APP_MESSAGE_H__

#include "type.h"



/*************************************************************************************
 *
 * Message defines
 *
 */

typedef enum 
{
	MSG_SERVICE_CLASS				= 0x1000,
	MSG_SERVICE_CREATED,
	MSG_SERVICE_START,
	MSG_SERVICE_RESUME,
	MSG_SERVICE_STARTED,
	MSG_SERVICE_PAUSE,
	MSG_SERVICE_PAUSED,
	MSG_SERVICE_STOP,
	MSG_SERVICE_STOPPED,

	MSG_APP_MODE_START,
	MSG_APP_MODE_STOP,
	MSG_KEY_EVENT,
	MSG_BATTERY_EVENT,
	MSG_DEVICE_EVENT,
	MSG_DECODER_EVENT,
	MSG_WEIXIN_EVENT,

	MSG_WIFI_AUDIO_SERVICE_DATA_READY,

	MSG_BT_SERVICE_CLASS			= 0x1100,
	MSG_BT_SERVICE_STOP,
	MSG_BT_SERVICE_DATA_ARRIVE,				/*!< Buart data arrived, sent by buart interrup*/

	/** AVRCP releated message */
	MSG_BT_SERVICE_AVRCP_PLAY,
	MSG_BT_SERVICE_AVRCP_PAUSE,
	MSG_BT_SERVICE_AVRCP_NEXT,
	MSG_BT_SERVICE_AVRCP_PRE,

	/** HFP releated message*/
	MSG_BT_SERVICE_HFP_ACCEPT,
	MSG_BT_SERVICE_HFP_REJECT,
	MSG_BT_SERVICE_HFP_HUNGUP,
	MSG_BT_SERVICE_HFP_SCO_TRANS,

	MSG_AUDIO_CORE_SERVICE_CLASS	= 0x1200,
	MSG_AUDIO_CORE_SERVICE_START,
	MSG_AUDIO_CORE_SERVICE_STARTED,
	MSG_AUDIO_CORE_SERVICE_STOP,
	MSG_AUDIO_CORE_SERVICE_STOPED,

	MSG_DEVICE_SERVICE_CLASS		= 0x1300,
	MSG_DEVICE_SERVICE_START,
	MSG_DEVICE_SERVICE_STOP,


	MSG_BT_AUDIO_CLASS				= 0x2000,
	MSG_BT_AUDIO_STOP,

	MSG_WIFI_AUDIO_CLASS			= 0x3000,
	MSG_WIFI_AUDIO_MODE_STOP,
	MSG_WIFI_AUDIO_PLAY_PAUSE,
	MSG_WIFI_AUDIO_STOP,
	MSG_WIFI_AUDIO_NEXT,
	MSG_WIFI_AUDIO_PRE,
	MSG_WIFI_AUDIO_VOLUP,
	MSG_WIFI_AUDIO_VOLDOWN,
	MSG_WIFI_AUDIO_READ_WX,
	MSG_WIFI_AUDIO_RECORD_WX,
	MSG_WIFI_AUDIO_SEND_WX,

	MSG_MEDIA_AUDIO_CLASS			= 0x4000,
	MSG_MEDIA_AUDIO_MODE_STOP,
	MSG_MEDIA_AUDIO_PLAY_PAUSE,
	MSG_MEDIA_AUDIO_STOP,
	MSG_MEDIA_AUDIO_NEXT,
	MSG_MEDIA_AUDIO_PRE,
	MSG_MEDIA_AUDIO_VOLUP,
	MSG_MEDIA_AUDIO_VOLDOWN,
	MSG_MEDIA_AUDIO_READ_WX,
	MSG_MEDIA_AUDIO_RECORD_WX,
	MSG_MEDIA_AUDIO_SEND_WX,

	MSG_TIP_SOUND_CLASS				= 0x5000,
	MSG_TIP_SOUND_MODE_STOP,

} MessageId;


#define MAX_RECV_MSG_TIMEOUT		0xFFFFFFFF
typedef enum
{
	MSG_PARAM_BT_AUDIO_PLAY,
	MSG_PARAM_WIFI_AUDIO_PLAY,
	MSG_PARAM_MEDIA_AUDIO_PLAY,
	MSG_PARAM_BLUETOOTH_SERVICE,
	MSG_PARAM_DEVICE_SERVICE_ID,
	MSG_PARAM_AUDIO_CORE_SERVICE,
	MSG_PARAM_WIFI_AUDIO_SERVICE,
	MSG_PARAM_DECODER_SERVICE,
	MSG_PARAM_WIFI_SERVICE,
	MSG_PARAM_MEDIA_SERVICE,
	MSG_PARAM_TIP_SOUND,
	
	MSG_PARAM_DECODER_MODE_WIFI,
	MSG_PARAM_DECODER_MODE_BT,
	MSG_PARAM_DECODER_MODE_TIPSOUND,
	MSG_PARAM_DECODER_MODE_MEDIA,

	MSG_PARAM_DECODER_ERR,

	//wifi porting
	MSG_PARAM_NEXT_SONG,
	MSG_PARAM_PRE_SONG,
	MSG_PARAM_PLAY_SONG,
	MSG_PARAM_VOL_INC,
	MSG_PARAM_VOL_DEC,
} MessageParams;




/*************************************************************************************
 *
 * Module Message defines
 *
 *************************************************************************************/

typedef enum
{
	ServiceStateNone	= 0,
	ServiceStateCreating,
	ServiceStateReady, // ServiceStateCreated
	ServiceStateStarting,
	ServiceStateRunning, // ServiceStateStarted
	ServiceStatePausing,
	ServiceStatePaused,
	ServiceStateResuming,
	ServiceStateStopping,
	ServiceStateStopped,
}ServiceState;

#endif /*__APP_MESSAGE_H__*/

