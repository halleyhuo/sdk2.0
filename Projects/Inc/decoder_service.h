/**
 **************************************************************************************
 * @file    decoder_service.h
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



#ifndef __DECODER_SERVICE_H__
#define __DECODER_SERVICE_H__

#include "type.h"
#include "rtos_api.h"
#include "audio_decoder.h"

typedef enum
{
	DS_EVENT_SERVICE_INITED,
	DS_EVENT_SERVICE_STARTED,
	DS_EVENT_DECODE_INITED,
	DS_EVENT_DECODE_DECODED,
} DecoderServiceEvent;

typedef struct _DecoderCallbackParams
{
	BOOL		status;
	SongInfo	*songInfo;
}DecoderCallbackParams;

typedef void (* DcsCallback)(DecoderServiceEvent event, DecoderCallbackParams * param);

int32_t DecoderServiceCreate(MessageHandle parentMsgHandle);

/**
 * @brief
 *		Start decoder service.
 * @param
 * 	 NONE
 * @return  
 */
void DecoderServiceStart(void);

/**
 * @brief
 *		Stop device service.
 * @param
 * 	 NONE
 * @return  
 */
void DecoderServiceStop(void);

void DecoderServiceKill(void);


/**
 * @brief
 *		Get message handle
 * @param
 * 	 NONE
 * @return  
 */
MessageHandle GetDecoderServiceMsgHandle(void);


int16_t GetDecodedPcmData(int16_t * pcmData, uint16_t sampleLen, uint32_t channels);

/***************************************************************************************
 *
 * The following APIs only for O18B XrTx module
 *
 */

void InitXrTx(void);

BOOL CheckXr(void);

BOOL CheckTx(void);

BOOL CheckXrTx(void);

BOOL GetXr(void);

BOOL GetTx(void);

void ReleaseXr(void);

void ReleaseTx(void);

#endif /*__DECODER_SERVICE_H__*/

