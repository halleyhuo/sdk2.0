/**
 **************************************************************************************
 * @file    wifi_audio_api.h
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


#ifndef __WIFI_AUDIO_API_H__
#define __WIFI_AUDIO_API_H__

#include "type.h"

typedef int32_t				WAudioStatus;


#define WAUDIO_STATUS_SUCCESS			0

#define WAUDIO_STATUS_FAILED			-1

#define WAUDIO_STATUS_PARAMS_ERR		-2

#define WAUDIO_STATUS_NO_MORE_DATA		-3

#define WAUDIO_STATUS_NOT_FOUND			-4

typedef enum
{
	FORMAT_UNKNOWN = 0,
	FORMAT_MP3,
	FORMAT_M4A,
}AudioFormat;

AudioFormat WifiAudioFormatParse(const uint8_t *buff);

WAudioStatus WifiAudioInit(void);

WAudioStatus WifiAudioDeinit(void);

WAudioStatus WifiAudioGetMediaStart(uint8_t * url, int32_t position);

WAudioStatus WifiAudioGetMedia(uint8_t **audioData, int32_t *dataLen, int32_t *position);

WAudioStatus WifiAudioGetMediaStop(void);


#endif /*__WIFI_AUDIO_API_H__*/

