/**
 **************************************************************************************
 * @file    tip_sound.c
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

#include <string.h>
#include "chip_info.h"
#include "type.h"
#include "tip_sound.h"
#include "rtos_api.h"
#include "audio_utility.h"
#include "mv_ring_buffer.h"
#include "main_app.h"
#include "app_message.h"

#include "pcm_transfer.h"
#include "dac.h"
#include "audio_path.h"
#include "app_config.h"
#include "clk.h"
#include "pcm_fifo.h"
#include "spi_flash.h"

//中英文双语提示音
typedef struct _SOUND_TABLE_ITEM
{
    uint16_t Id;
    uint32_t IdChn;

} SOUND_TABLE_ITEM;

#define STR_TO_UINT(s)	((s[0] << 0) | (s[1] << 8) | (s[2] << 16) | (s[3] << 24))
static const SOUND_TABLE_ITEM SoundTable[] =
{
//   ID                                 中文ID
    {SOUND_KJ,						STR_TO_UINT("K  J")},	//1开机
    {SOUND_MYLW,					STR_TO_UINT("MYLW")},	//2没有联网，请先联网
    {SOUND_QXPW,					STR_TO_UINT("QXPW")},	//3没有找到网络，请配置网络
    {SOUND_LWCG,					STR_TO_UINT("LWCG")},	//4网络连接成功
    {SOUND_WLDK,					STR_TO_UINT("WLDK")},	//5网络已断开
    {SOUND_SSWL,					STR_TO_UINT("SSWL")},	//6正在搜索网络
    {SOUND_SZWL,					STR_TO_UINT("SZWL")},	//7请打开APP，设置当前网络
    {SOUND_SJRJ,					STR_TO_UINT("SJRJ")},	//8发现新的软件版本，请升级软件
    {SOUND_SDXX,					STR_TO_UINT("SDXX")},	//9收到新信息
    {SOUND_DBGQ,					STR_TO_UINT("DBGQ")},	//10请打开APP点播歌曲
    {SOUND_SJCG,					STR_TO_UINT("SJCG")},	//11软件升级成功
    {SOUND_KSSJ,					STR_TO_UINT("KSSJ")},	//12开始软件升级，在升级成功之前请不要断电
    {SOUND_BYSJ,					STR_TO_UINT("BYSJ")},	//13软件已是最新版本，不需要升级
    {SOUND_SCCG,					STR_TO_UINT("SCCG")},	//14收藏成功
    {SOUND_DD,						STR_TO_UINT("D  D")},	//15"滴"
    {SOUND_XX,						STR_TO_UINT("X  X")},	//16"咻"
    {SOUND_QXSC,					STR_TO_UINT("QXSC")},	//17已取消收藏
    {SOUND_QCJL,					STR_TO_UINT("QCJL")},	//18已清除联网记录
    {SOUND_XXGD,					STR_TO_UINT("XXGD")},	//19消息过短
    {SOUND_SJSB,					STR_TO_UINT("SJSB")},	//20软件升级失败
    {SOUND_XTFM,					STR_TO_UINT("XTFM")},	//21系统繁忙，请稍后再试
    {SOUND_XXGQ,					STR_TO_UINT("XXGQ")},	//22消息已过期
    {SOUND_LJSB,					STR_TO_UINT("LJSB")},	//23连接网络失败
    {SOUND_DLWX,					STR_TO_UINT("DLWX")},	//24正在登陆微信，请稍等
    {SOUND_XZXX,					STR_TO_UINT("XZXX")},	//25您有未读消息
    {SOUND_JSCD,					STR_TO_UINT("JSCD")},	//26电量过低,请及时充电
    {SOUND_ZDGJ,					STR_TO_UINT("ZDGJ")},	//27电量过低,自动关机
};

static uint8_t TipSoundFileBuf[256];

/***************************************************************************************
 *
 * External defines
 *
 */

#define TIP_SOUND_TASK_STACK_SIZE		1024
#define TIP_SOUND_TASK_PRIO				3



/***************************************************************************************
 *
 * Internal defines
 *
 */

#define WTIP_SOUND_AUDIO_CORE_SRC_BUF_SIZE	(8*1024)
#define WTIP_SOUND_AUDIO_CORE_OUT_BUF_SIZE	2048


typedef struct _TipSoundContext
{
	xTaskHandle 		taskHandle;
	MessageHandle		msgHandle;
	QueueHandle_t 		audioMutex;
	QueueHandle_t		pcmBufMutex;

	MemHandle			decoderMemHandle;
	MvRingBuffer		audioCoreSrcBuf;
	uint8_t				*audioCoreMixBuf;
	AudioCoreHandle		audioCoreSrcHandle;
	AudioCoreHandle		audioCoreSinkHandle;

}TipSoundContext;


uint32_t 			ConstDataAddr;
uint32_t			ConstDataSize;
uint32_t 			ConstDataOffset;

bool tipsoundxrtx = TRUE;

/***************************************************************************************
 *
 * Internal varibles
 *
 */

#define TIP_SOUND_NUM_MESSAGE_QUEUE		10

static TipSoundContext		tipSoundCt;
#define TIP_SOUND(x)		(tipSoundCt.x)


/** tip sound task name*/
const char tipSoundName[] = "TipSound";

/***************************************************************************************
 *
 * Internal functions
 *
 */

/////////////////////////////////////////////////////////////////////////
uint32_t TipSoundFillStreamCallback(void *buffer, uint32_t length)
{
    int32_t RemainBytes = ConstDataSize - ConstDataOffset;
    int32_t ReadBytes   = length > RemainBytes ? RemainBytes : length;

    if(ReadBytes == 0)
    {
        return 0;	//此次不加载数据
    }

    //APP_DBG("SoundRemind Fill Stream Callback...\n");

    if(SpiFlashConstDataRead((uint8_t*)buffer,
                             ReadBytes,
                             ConstDataAddr + ConstDataOffset) < 0)
    {
        ReadBytes = 0;
        APP_DBG("read const data error!\r\n");
    }

    ConstDataOffset += ReadBytes;

    return ReadBytes;
}

// stream 缓存数据填充（decoder task每次解帧时调用）
// return -1 -- stream over; 0 -- no fill; other value -- filled bytes
int32_t TipSoundFillStream(void)
{
    int32_t FillBytes;	//本次要加载的数据长度
    int32_t LeftBytes;	//文件缓冲区中已有的数据长度

    LeftBytes = (tipSoundCt.decoderMemHandle.mem_len - tipSoundCt.decoderMemHandle.p);
    FillBytes = ConstDataSize - ConstDataOffset;
    if(FillBytes > tipSoundCt.decoderMemHandle.mem_capacity - LeftBytes)
    {
        FillBytes = tipSoundCt.decoderMemHandle.mem_capacity - LeftBytes;
    }

    if((LeftBytes > 0) && (tipSoundCt.decoderMemHandle.p == 0))
    {
        return 0;	//还有数据，并且数据没有消耗
    }

    if(FillBytes == 0)
    {

        return -1;	//播放结束
    }

    memcpy(tipSoundCt.decoderMemHandle.addr, tipSoundCt.decoderMemHandle.addr + tipSoundCt.decoderMemHandle.p, LeftBytes);
    if(SpiFlashConstDataRead((uint8_t*)(tipSoundCt.decoderMemHandle.addr + LeftBytes),
                             FillBytes,
                             ConstDataAddr + ConstDataOffset) < 0)
    {
        APP_DBG("read const data error!\n");
    }

    tipSoundCt.decoderMemHandle.p = 0;
    tipSoundCt.decoderMemHandle.mem_len = LeftBytes + FillBytes;
    ConstDataOffset += FillBytes;

    return FillBytes;
}



static uint16_t TipSoundSourceGetData(int16_t * buf, uint16_t sampleLen)
{
	int16_t	dataSize;

	if(MvRingBufferVaildSize(&TIP_SOUND(audioCoreSrcBuf)) == 0)
	{
		return 0;
	}

	GetTipSoundPcmBufMutex();
	dataSize = MvRingBufferRead(&TIP_SOUND(audioCoreSrcBuf), (uint8_t *)buf, sampleLen*2*2);
	ReleaseTipSoundPcmBufMutex();

	return dataSize/4;

}

static void TipSoundSinkPutData(void * buf, uint16_t len)
{
	GetTipSoundMutex();
	if(PcmFifoIsEmpty())
	{
		DBG("Empty\n");
	}
	PcmTxTransferData((void *)buf, (void *)buf, len);
}

static void ConfigPhub2TipSound(void)
{
	/* DAC initialization */
	CodecDacInit(TRUE);
	CodecDacMuteSet(TRUE, TRUE);
	CodecDacChannelSel(DAC_CH_DECD_L | DAC_CH_DECD_R);
	DacVolumeSet(0x200, 0x200);
	DacNoUseCapacityToPlay();
	DacConfig(MDAC_DATA_FROM_DEC, USB_MODE);
	/* PCMFIFO_MIX_DACOUT */
	PhubPathSel(PCMFIFO_MIX_DACOUT);
	CodecDacMuteSet(FALSE, FALSE);
}

static void DeconfigPhub2TipSound(void)
{

}

static void ConfigAudioCore2TipSound(void)
{

	AuidoCoreInit(AUDIO_CORE_MODE_MIX);

	TIP_SOUND(audioCoreSrcHandle)   = AudioCoreRegisterSource(TipSoundSourceGetData, AUDIO_CORE_SRC_TYPE_DECODER);

	TIP_SOUND(audioCoreSinkHandle)  = AudioCoreRegisterSink(TipSoundSinkPutData, AUDIO_CORE_SINK_TYPE_DAC);
}

static void DeconfigAudioCore2TipSound(void)
{
	AudioCoreDeregisterSource(TIP_SOUND(audioCoreSrcHandle));
	AudioCoreDeregisterSink(TIP_SOUND(audioCoreSinkHandle));
}

static void ConfigMemory4TipSound(void)
{
	/* for decoder */ 
	TIP_SOUND(decoderMemHandle).addr = TipSoundFileBuf;
	TIP_SOUND(decoderMemHandle).mem_capacity = sizeof(TipSoundFileBuf);
	TIP_SOUND(decoderMemHandle).mem_len = 0;
	TIP_SOUND(decoderMemHandle).p = 0;

	/* for audio core source buffer */
	TIP_SOUND(audioCoreSrcBuf).buffer = (uint8_t *)pvPortMalloc(WTIP_SOUND_AUDIO_CORE_SRC_BUF_SIZE);
	TIP_SOUND(audioCoreSrcBuf).capacity = WTIP_SOUND_AUDIO_CORE_SRC_BUF_SIZE;
	MvRingBufferInit(&TIP_SOUND(audioCoreSrcBuf));

	/* for audio core mix buffer */
	TIP_SOUND(audioCoreMixBuf) = (uint8_t *)(VMEM_ADDR + AUDIOC_CORE_TRANSFER_OFFSET);

	PcmFifoInitialize(PCM_FIFO_OFFSET, PCM_FIFO_SIZE, 0, 0);
}

static void DeconfigMemory4TipSound(void)
{
	
}

static void CreateTipSoundServices(void)
{
	DecoderServiceCreate();

	AudioCoreServiceCreate();

}

static void WaitTipSoundServices(void)
{
	while(1)
	{
		if(GetDecoderServiceState() == ServiceStateReady 
			//&& GetWifiServiceState() == ServiceStateReady
			&& GetAudioCoreServiceState() == ServiceStateReady
			)
		{
			break;
		}
		else
		{
			vTaskDelay(10);
		}
	}
}

static void StartTipSoundServices(void)
{
	MessageContext		msgSend;
	MessageHandle		msgHandle;

	msgSend.msgId		= MSG_SERVICE_START;
	msgSend.msgParams	= NULL;

	msgHandle = GetTipSoundMessageHandle();
	MessageSend(msgHandle, &msgSend);

	msgHandle = GetDecoderServiceMsgHandle();
	msgSend.msgParams = MSG_PARAM_DECODER_MODE_TIPSOUND;
	MessageSend(msgHandle, &msgSend);

	msgHandle = GetAudioCoreMessageHandle();
	MessageSend(msgHandle, &msgSend);
}

static int32_t TipSoundInit(void)
{
	memset(&tipSoundCt, 0, sizeof(TipSoundContext));
	
	TIP_SOUND(audioMutex) = xSemaphoreCreateMutex();
	TIP_SOUND(pcmBufMutex) = xSemaphoreCreateMutex();
	
	/* Read storage parameters */
//	PreferenceLoad(btAudioPlayStorName, &BT_AUDIO_PLAY(params), sizeof(BtAudioPlayParams));

	/* Config audio path*/
	ConfigPhub2TipSound();

	/* Config memory */
	ConfigMemory4TipSound();


	/* Create wifi audio services */
	CreateTipSoundServices();

	/* Config audio core source */
	ConfigAudioCore2TipSound();
	

	return 0;
}

static void TipSoundDeinit(void)
{
	MessageContext		msgSend;
	MessageHandle		mainHandle;

	/* Deconfig audio path*/
	DeconfigPhub2TipSound();

	/* Deconfig audio core */
	DeconfigAudioCore2TipSound();

	/* Write storage parameters */
//	PrefrenceSave(btAudioPlayStorName, &BT_AUDIO_PLAY(params), sizeof(BtAudioPlayParams));

	/* Send message to main app */
	mainHandle = GetMainMessageHandle();

	msgSend.msgId		= MSG_SERVICE_STOPPED;
	msgSend.msgParams	= MSG_PARAM_TIP_SOUND;
	MessageSend(mainHandle, &msgSend);

}


static void TipSoundkEntrance(void * param)
{
	MessageContext		msgRecv;
	MessageContext		msgSend;
	MessageHandle		mainHandle;


	/* message handle */
	TIP_SOUND(msgHandle) = MessageRegister(TIP_SOUND_NUM_MESSAGE_QUEUE);

	/* Send message to main app */
	mainHandle = GetMainMessageHandle();

	msgSend.msgId		= MSG_SERVICE_CREATED;
	msgSend.msgParams	= MSG_PARAM_TIP_SOUND;

	MessageSend(mainHandle, &msgSend);

	/* Wait servcies ready */
	WaitTipSoundServices();
	SpiFlashInfoInit();

	vTaskDelay(500);
	{
		uint16_t i;
		uint16_t SoundId;
		uint32_t ConstDataId;
		int32_t err;

		SoundId = SOUND_SJRJ;//SOUND_KJ;//
		
	    //通过SoundId查找对应的ConstDataId
	    for(i = 0; i < sizeof(SoundTable)/sizeof(SOUND_TABLE_ITEM); i++)
	    {
	        if(SoundTable[i].Id == SoundId)
	        {
	            ConstDataId = SoundTable[i].IdChn;
	            break;	//找到
	        }
	    }
	    if(i >= sizeof(SoundTable)/sizeof(SOUND_TABLE_ITEM))
	    {
	        APP_DBG("Can not get the SoundId : %d\n", SoundId);
	        //SoundRemindControl.IsRunning = 0;
	        return;		//未找到
	    }
	    APP_DBG("the SoundId is available. \n");

	    ConstDataSize = 0;
	    ConstDataAddr = 0;
	    ConstDataOffset = 0;

		err = SpiFlashConstGetInfo(ConstDataId, &ConstDataSize, &ConstDataAddr);
	    if(err < 0)
	    {
	        APP_DBG("[err] = %d!\n", err);
	        APP_DBG("Get const data info error!\n");
	        //SoundRemindControl.IsRunning = 0;
	        return;
	    }
	    //APP_DBG("Get const data info from spi flash = OK!\n");
	    TipSoundFillStream();
	}
	
	/* Start servcies */
	StartTipSoundServices();

	while(1)
	{
		//MessageRecv(TIP_SOUND(msgHandle), &msgRecv, MAX_RECV_MSG_TIMEOUT);
		MessageRecv(TIP_SOUND(msgHandle), &msgRecv, 2);

		switch(msgRecv.msgId)
		{
			case MSG_TIP_SOUND_MODE_STOP:
				TipSoundDeinit();

				/* Wait for kill*/
				vTaskSuspend(NULL);
				break;
			
			
		}

		//TipSoundFillStream();
	}
}


/***************************************************************************************
 *
 * APIs
 *
 */
MessageHandle GetTipSoundMessageHandle(void)
{
	return TIP_SOUND(msgHandle);
}

/**
 * @brief
 *		Start bt audio play program task.
 * @param
 * 	 NONE
 * @return  
 */
int32_t TipSoundStart(void)
{
	DBG("tip sound...\n");
	TipSoundInit();
	xTaskCreate(TipSoundkEntrance, tipSoundName, TIP_SOUND_TASK_STACK_SIZE, NULL, TIP_SOUND_TASK_PRIO, &TIP_SOUND(taskHandle));
	return 0;
}

/**
 * @brief
 *		Exit bt audio play program task.
 * @param
 * 	 NONE
 * @return  
 */
void TipSoundStop(void)
{
	vTaskDelete(TIP_SOUND(taskHandle));
}

MemHandle * GetTipSoundDecoderBuffer(void)
{
	return &TIP_SOUND(decoderMemHandle);
}

MvRingBuffer * GetTipSoundAudioCoreBuffer(void)
{
	return &TIP_SOUND(audioCoreSrcBuf);
}

int32_t SaveTipSoundDecodedPcmData(int32_t * pcmData, uint16_t sampleLen, uint32_t channels)
{
	uint32_t		dataLen;

	if(pcmData == NULL || sampleLen == 0)
		return -1;

	dataLen = sampleLen * channels * 2;
	
	if(MvRingBufferFreeSize(&TIP_SOUND(audioCoreSrcBuf)) < dataLen)
		return -2;

	GetTipSoundPcmBufMutex();
	dataLen = MvRingBufferWrite(&TIP_SOUND(audioCoreSrcBuf), (uint8_t *)pcmData, dataLen);
	ReleaseTipSoundPcmBufMutex();
	if(dataLen <= 0)
		return -3;

	
	return ((dataLen / channels ) / 2);

}

void GetTipSoundMutex(void)
{
//	xSemaphoreTake( WIFI_AUDIO_PLAY(audioMutex) , 0xFFFFFFFF);
	while(!tipsoundxrtx)
	{
		vTaskDelay(1);
	}
	tipsoundxrtx = FALSE;
}


void ReleaseTipSoundMutex(void)
{
/*
	portBASE_TYPE taskWoken = pdFALSE;

	if (__get_IPSR() != 0)
	{
		if (xSemaphoreGiveFromISR(WIFI_AUDIO_PLAY(audioMutex), &taskWoken) != pdTRUE)
		{
			
			return;
		}
		portEND_SWITCHING_ISR(taskWoken);
	}
	else
	{
		if (xSemaphoreGive(WIFI_AUDIO_PLAY(audioMutex)) != pdTRUE)
		{

		}
	}
*/
	
	tipsoundxrtx = TRUE;
	return;
}


void GetTipSoundPcmBufMutex(void)
{
	xSemaphoreTake( TIP_SOUND(pcmBufMutex) , 0xFFFFFFFF);
}

void ReleaseTipSoundPcmBufMutex(void)
{
	portBASE_TYPE taskWoken = pdFALSE;

	if (__get_IPSR() != 0)
	{
		if (xSemaphoreGiveFromISR(TIP_SOUND(pcmBufMutex), &taskWoken) != pdTRUE)
		{
			return;
		}
		portEND_SWITCHING_ISR(taskWoken);
	}
	else
	{
		if (xSemaphoreGive(TIP_SOUND(pcmBufMutex)) != pdTRUE)
		{

		}
	}

	return;

}







