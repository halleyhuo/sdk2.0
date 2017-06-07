/**
 **************************************************************************************
 * @file    audio_core_manager.c
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

#ifndef __AUDIO_CORE_MANAGER_H__
#define __AUDIO_CORE_MANAGER_H__

#include "type.h"
#include "rtos_api.h"

/**
 * Audio core mode
 */
typedef uint8_t			AudioCoreMode;

#define AUDIO_CORE_MODE_NONE			0

#define AUDIO_CORE_MODE_MIX				1

#define AUDIO_CORE_MODE_AEC				2

/**
 * Audio core handle
 */
typedef uint32_t		AudioCoreIndex;


/**
 * @brief
 *		Funciton define : Get data from source
 *
 * @param
 *		buf - The buffer which receives data
 * @param
 *		len - The length of data to be get
 *
 * @return
 *		The actual length of received data
 */
typedef uint16_t (*AudioCoreGetData)(int16_t * buf, uint16_t len);


/**
 * @brief
 *		Funciton define : Put data to sink
 *
 * @param
 *		buf - The data in this buffer has been processed by audio core
 *			and the data in this buffer should be put to sink
 * @param
 *		len - The length of data to put
 *
 * @return
 *		NONE
 */
typedef BOOL (*AudioCorePutData)(void * buf, uint16_t len);


typedef struct _AudioCorePcmParams
{
	uint16_t		channelNums;
	uint16_t		pcmDataMode;
	uint32_t		samplingRate;
	uint32_t		bitRate;
}AudioCorePcmParams;


typedef struct _AudioCoreSource
{
	BOOL				enable;
	AudioCoreGetData	funcGetData;
	AudioCorePcmParams	pcmParams;
}AudioCoreSource;

typedef struct _AudioCoreSink
{
	BOOL				enable;
	AudioCorePutData	funcPutData;
	AudioCorePcmParams	pcmParams;
}AudioCoreSink;


int32_t AudioCoreServiceCreate(MessageHandle parentMsgHandle);

bool AudioCoreModeSet(AudioCoreMode mode);


/**
 * @brief
 *		Start audio core service.
 * @param
 * 	 NONE
 * @return  
 */
int32_t AudioCoreServiceStart(void);


/**
 * @brief
 *		Exit audio core service.
 * @param
 * 	 NONE
 * @return  
 */
void AudioCoreServiceStop(void);

int32_t AudioCoreServiceKill(void);


#endif

