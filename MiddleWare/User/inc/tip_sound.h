/**
 **************************************************************************************
 * @file    tip_sound.h
 * @brief   
 *
 * @author  kk
 * @version V1.0.0
 *
 * $Created: 2017-3-17 13:06:47$
 *
 * @Copyright (C) 2016, Shanghai Mountain View Silicon Co.,Ltd. All rights reserved.
 **************************************************************************************
 */

#ifndef __TIP_SOUND_H__
#define __TIP_SOUND_H__

#ifdef __cplusplus
extern "C" {
#endif//__cplusplus

#include "type.h"
#include "audio_utility.h"
#include "mv_ring_buffer.h"


typedef enum _SOUND_ID
{
 	SOUND_KJ = 0,						//1开机	
 	SOUND_MYLW,							//2没有联网，请先联网
 	SOUND_QXPW,							//3没有找到网络，请配置网络
 	SOUND_LWCG,							//4网络连接成功
 	SOUND_WLDK,							//5网络已断开
 	SOUND_SSWL,							//6正在搜索网络
 	SOUND_SZWL,							//7请打开APP，设置当前网络
	SOUND_SJRJ,							//8发现新的软件版本，请升级软件
	SOUND_SDXX,							//9收到新信息
	SOUND_DBGQ,							//10请打开APP点播歌曲
	SOUND_SJCG,							//11软件升级成功
    SOUND_KSSJ,							//12开始软件升级，在升级成功之前请不要断电
    SOUND_BYSJ,							//13软件已是最新版本，不需要升级
    SOUND_SCCG,							//14收藏成功
    SOUND_DD,							//15"滴"
    SOUND_XX,							//16"咻"
    SOUND_QXSC,							//17已取消收藏
    SOUND_QCJL,							//18已清除联网记录
    SOUND_XXGD,							//19消息过短
    SOUND_SJSB,							//20软件升级失败
    SOUND_XTFM,							//21系统繁忙，请稍后再试
    SOUND_XXGQ,							//22消息已过期
    SOUND_LJSB,							//23连接网络失败
    SOUND_DLWX,							//24正在登陆微信，请稍等
    SOUND_XZXX,							//25您有未读消息
    SOUND_JSCD,							//26电量过低,请及时充电
    SOUND_ZDGJ,							//27电量过低,自动关机
} SOUND_ID;

uint32_t TipSoundFillStreamCallback(void *buffer, uint32_t length);

MemHandle * GetTipSoundDecoderBuffer(void);


MvRingBuffer * GetTipSoundAudioCoreBuffer(void);


int32_t SaveTipSoundDecodedPcmData(int32_t * data, uint16_t dataLen, uint32_t channels);


void GetTipSoundMutex(void);


void ReleaseTipSoundMutex(void);


void GetTipSoundPcmBufMutex(void);


void ReleaseTipSoundPcmBufMutex(void);


#ifdef __cplusplus
}
#endif//__cplusplus

#endif /* __TIP_SOUND_H__ */

