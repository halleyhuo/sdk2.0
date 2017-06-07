/**
 **************************************************************************************
 * @file    bt_audio_play.c
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

#include <string.h>

#include "type.h"
#include "rtos_api.h"

#include "main_app.h"
#include "app_message.h"

#include "dac.h"
#include "audio_adc.h"
#include "audio_path.h"
#include "rst.h"
#include "pcm_transfer.h"
#include "pcm_fifo.h"
#include "chip_info.h"
#include "clk.h"

/***************************************************************************************
 *
 * External defines
 *
 */

#define BT_AUDIO_PLAY_TASK_STACK_SIZE	1024
#define BT_AUDIO_PLAY_TASK_PRIO			3

#define DECODER_PCM_FIFO_ADDR			PMEM_ADDR
#define DECODER_PCM_FIFO_SIZE			(16*1024)




/***************************************************************************************
 *
 * Internal defines
 *
 */


#define BT_AUDIO_NUM_MESSAGE_QUEUE		10

typedef struct _BtAudioPlayParams
{
	uint32_t			dacVol;
	
}BtAudioPlayParams;

typedef struct _BtAudioPlayContext
{
	xTaskHandle			taskHandle;
	MessageHandle		msgHandle;

	BtAudioPlayParams	params;

}BtAudioPlayContext;

/** bt audio play task name*/
const char btAudioPlayName[]		= "BtAudioPlay";

/** bt audio play storage name*/
const char btAudioPlayStorName[]	= "BtAudioPlay";

/***************************************************************************************
 *
 * Internal varibles
 *
 */

static BtAudioPlayContext		btAudioPlayCt;
#define BT_AUDIO_PLAY(x)		(btAudioPlayCt.x)


//static BtAudioPlayContext		*btAudioPlayCt;
//#define BT_AUDIO_PLAY(x)		(btAudioPlayCt->x)

/***************************************************************************************
 *
 * Internal functions
 *
 */
static void ConfigPhub2BtAudioPlay(void)
{
	CodecDacInit(TRUE);
	CodecAdcAnaInit();
	DacSoftMuteSet(TRUE, TRUE);
	CodecDacMuteSet(TRUE, TRUE);

	PcmFifoPause();
	PcmFifoInit((uint32_t)DECODER_PCM_FIFO_ADDR, DECODER_PCM_FIFO_SIZE);
	PcmFifoPlay();
	PcmTxSetPcmDataMode(DATA_MODE_STEREO_LR);

	PhubPathClose(ALL_PATH_CLOSE);
	RstPhubModule();
	RstMclk();

	CodecDacChannelSel(DAC_CH_DECD_L | DAC_CH_DECD_R);

	DacConfig(MDAC_DATA_FROM_DEC, NORMAL_MODE);

	PhubPathSel(PCMFIFO_MIX_DACOUT);

	(*(volatile unsigned long*)0x4001A0AC) = 0x0;	

	DacVolumeSet(BT_AUDIO_PLAY(params).dacVol, BT_AUDIO_PLAY(params).dacVol);

	CodecDacMuteSet(FALSE, FALSE);
	DacSoftMuteSet(FALSE, FALSE);
}

static void DeconfigPhub2BtAudioPlay(void)
{
	DacSoftMuteSet(TRUE, TRUE);


	PhubPathClose(ALL_PATH_CLOSE);
	(*(volatile unsigned long*)0x4001A0AC) = 0x77;	// important for low power!!! Don't delete this line 

	DacVolumeSet(0, 0);

	CodecDacDeinit(TRUE);
	CodecAdcAnaDeInit();
	DacDisable();
}

static int32_t BtAudioPlayInit(void)
{
	memset(&btAudioPlayCt, 0, sizeof(BtAudioPlayContext));

	/* Read storage parameters */
//	PreferenceLoad(btAudioPlayStorName, &BT_AUDIO_PLAY(params), sizeof(BtAudioPlayParams));

	/* Config audio path*/
	ConfigPhub2BtAudioPlay();

	return 0;
}

static void BtAudioPlayDeinit(void)
{
	MessageContext		msgSend;
	MessageHandle		mainHandle;

	/* Deconfig audio path*/
	DeconfigPhub2BtAudioPlay();

	/* Write storage parameters */
//	PrefrenceSave(btAudioPlayStorName, &BT_AUDIO_PLAY(params), sizeof(BtAudioPlayParams));

	/* Send message to main app */
	mainHandle = GetMainMessageHandle();

	msgSend.msgId		= MSG_SERVICE_STOPPED;
	msgSend.msgParams	= MSG_PARAM_BT_AUDIO_PLAY;
	MessageSend(mainHandle, &msgSend);

}

static void BtAudioPlaykEntrance(void * param)
{
	MessageContext		msgRecv;
	MessageContext		msgSend;
	MessageHandle		mainHandle;


	/* message handle */
	BT_AUDIO_PLAY(msgHandle) = MessageRegister(BT_AUDIO_NUM_MESSAGE_QUEUE);

	/* Send message to main app */
	mainHandle = GetMainMessageHandle();

	msgSend.msgId		= MSG_SERVICE_CREATED;
	msgSend.msgParams	= MSG_PARAM_BT_AUDIO_PLAY;

	MessageSend(mainHandle, &msgSend);

	while(1)
	{
		MessageRecv(BT_AUDIO_PLAY(msgHandle), &msgRecv, MAX_RECV_MSG_TIMEOUT);

		switch(msgRecv.msgId)
		{
			case MSG_BT_AUDIO_STOP:
				BtAudioPlayDeinit();

				/* Wait for kill*/
				vTaskSuspend(NULL);
				break;
		}
	}
}


/***************************************************************************************
 *
 * APIs
 *
 */


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
MessageHandle GetBtAudioPlayMessageHandle(void)
{
	return BT_AUDIO_PLAY(msgHandle);
}

/**
 * @brief
 *		Start bt audio play program task.
 * @param
 * 	 NONE
 * @return  
 */
int32_t BtAudioPlayStart(void)
{
	BtAudioPlayInit();
	xTaskCreate(BtAudioPlaykEntrance, btAudioPlayName, BT_AUDIO_PLAY_TASK_STACK_SIZE, NULL, BT_AUDIO_PLAY_TASK_PRIO, &BT_AUDIO_PLAY(taskHandle));
	return 0;
}

/**
 * @brief
 *		Exit bt audio play program task.
 * @param
 * 	 NONE
 * @return  
 */
void BtAudioPlayStop(void)
{
	vTaskDelete(BT_AUDIO_PLAY(taskHandle));
}

