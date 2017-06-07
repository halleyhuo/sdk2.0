/**
 **************************************************************************************
 * @file    wifi_audio_play.h
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

#ifndef __WIFI_AUDIO_PLAY_H__
#define __WIFI_AUDIO_PLAY_H__

#include "type.h"
#include "audio_utility.h"
#include "mv_ring_buffer.h"

MemHandle * GetWifiAudioPlayDecoderBuffer(void);



int32_t SaveDecodedPcmData(int32_t * data, uint16_t dataLen, uint32_t channels);

#endif /*__WIFI_AUDIO_PLAY_H__*/
