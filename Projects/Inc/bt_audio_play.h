/**
 **************************************************************************************
 * @file    bt_audio_play.h
 * @brief   Bluetooth audio player 
 *
 * @author  halley
 * @version V1.0.0
 *
 * $Created: 2016-6-29 13:06:47$
 *
 * @Copyright (C) 2016, Shanghai Mountain View Silicon Co.,Ltd. All rights reserved.
 **************************************************************************************
 */


#ifndef __BT_AUDIO_PLAY_H__
#define __BT_AUDIO_PLAY_H__

#include "type.h"



/**
 * @brief
 *		Get message receive handle of bt audio play app
 * 
 * @param
 *		NONE
 *
 * @return
 *		MessageHandle
 */

MessageHandle GetBtAudioPlayMessageHandle(void);


/**
 * @brief
 *		Start bt audio play program task.
 * @param
 *		NONE
 * @return	
 */
int32_t BtAudioPlayStart(void);

void BtAudioPlayStop(void);


#endif /*__BT_AUDIO_PLAY_H__*/

