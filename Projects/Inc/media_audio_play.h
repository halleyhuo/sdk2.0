/**
 **************************************************************************************
 * @file    media_audio_play.h
 * @brief   uDisk and TF Card 
 *
 * @author  kk
 * @version V1.0.0
 *
 * $Created: 2017-3-17 13:06:47$
 *
 * @Copyright (C) 2016, Shanghai Mountain View Silicon Co.,Ltd. All rights reserved.
 **************************************************************************************
 */

#ifndef __MEDIA_AUDIO_PLAY_H__
#define __MEDIA_AUDIO_PLAY_H__

#include "type.h"
#include "audio_utility.h"
#include "mv_ring_buffer.h"

//void * GetMediaAudioPlayDecoderBuffer(void);


MvRingBuffer * GetMediaAudioPlayAudioCoreBuffer(void);


int32_t SaveMediaDecodedPcmData(int32_t * data, uint16_t dataLen, uint32_t channels);


void GetMediaMutex(void);


void ReleaseMediaMutex(void);


void GetMediaPcmBufMutex(void);


void ReleaseMediaPcmBufMutex(void);


#endif /*__MEDIA_AUDIO_PLAY_H__*/
