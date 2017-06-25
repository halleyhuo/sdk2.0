#include "airkiss_types.h"
#include <string.h>
#include "wx_speech_service.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "semphr.h"
#include "sockets.h"
#include <stdarg.h>
#include "audio_utility.h"
#include "audio_adc.h"
#include "audio_path.h"
#include "cache.h"
#include "debug.h"
#include "delay.h"
#include "watchdog.h"
#include "pcm_fifo.h"
#include "pcm_transfer.h"
#include "mp3enc_api.h"
#include "audio_decoder.h"
#include "gpio.h"
#include "dac.h"
#include "sys_app.h"
//#include "sound_remind.h"
//#include "wifi_audio.h"
//#include "sys_vol.h"
#include "rtos_api.h"
//#include "disk_player.h"
#include "app_config.h"
#include "wxcloud_api.h"


#define wx_debug(format, ...)		printf(format, ##__VA_ARGS__)
#define	CFG_SDRAM_BASE	(0x60000000)

//media_record_st *pt_media_record;
//media_id_record_st *pt_media_id_record;

char WifiStreamReady = 0;

extern uint32_t gSysTick;
extern MemHandle* WifiStreamHandle;
extern PLAY_RECORD *WifiaudioPlayRecord;

const uint8_t AMRHeader[6] = {0x23, 0x21, 0x41, 0x4D, 0x52, 0x0A};
const uint8_t HttpRes1[] = "HTTP/1.1 200 OK";
const uint8_t HttpRes2[] = "Content-Length: ";
const uint8_t HttpRes3[4] = {0x0D,0X0A,0x0D,0X0A};
const uint8_t token[] = "ZhPcVlNrrkIXnpjBRLP1507dkgxFmJG_gAiZV3uaD2f1Yzu6z-T6NHUbJuIJTeUoCVQWZ42Kl7tqZ8HH8uzEc1OoRxT6N9WGTSbT2x52jpvb9lKQ6NQtpwfj-aSuVSGHCRSaAFAKZA";
const uint8_t find_media[] = "media_id";

void * amr;
uint8_t wx_read_buffer[1*1024];
short buf[160];
uint8_t outbuf[500];
uint8_t *access_token;
//uint8_t *media_id;
extern uint8_t media_id[512];
uint8_t *getlistcmd;
extern int32_t AudioFormat;
uint8_t play_weixin_stage;
uint8_t collect_weixin_audio = 0;
uint8_t play_weixin_audio = 0;
#define PLAY_WEIIXN_CONNECT 	1
#define PLAY_WEIIXN_DOWN_DATA 2
#define PLAY_WEIIXN_WAIT1 		3
#define PLAY_WEIIXN_WAIT2 		4
#define PLAY_WEIIXN_END 			5
#define PLAY_WEIIXN_STOP			6
#define PLAY_WEIIXN_NEXT			7

#define FILE_DOWNLOAD_INVALID	-2	// accesstoken id invalid / media id invalid
#define FILE_DOWNLOAD_ERR		-1
#define FILE_DOWNLOAD_OK		1
#define FILE_DOWNLOAD_DROPOUT	2
#define FILE_DOWNLOAD_NEXT		3

//weixin response
#define RESP_OK						0
#define RESP_SYSTEM_BUSY			-1
#define RESP_ACCESS_TOKEN_INVALID	40001
#define RESP_MEDIA_ID_INVALID		40007
#define RESP_MEDIA_ID_MISSING		41006


uint32_t AmrAccessId = 0;
uint32_t AmrAccessId_s = 0;
//void BurnWeixinRecord(void);
//void play_sdxx(void);

extern PLAY_RECORD *WifiaudioPlayRecord;
extern VOLUME_RECORD VolumeRecord;
extern uint8_t Volume;
extern struct device_user_st *pdeviceuser;
extern uint8_t burn_dev_user;

typedef struct 
{
}PlayState;

typedef struct 
{
}SpeechPlayContext;

typedef struct 
{
}RecordState;

typedef struct 
{
}SpeechRecordContext;

typedef struct _WxSpeechServiceContext
{
	xTaskHandle 		taskHandle;
	MessageHandle		msgHandle;
	ServiceState		serviceState;

	//wx speech play
	xTaskHandle 		playTaskHandle;
	MessageHandle		playMsgHandle;
	PlayState			playState;
	SpeechPlayContext	sppechPlayContext;
	MemHandle			SpeechMemHandle;

	//wx speech record
	xTaskHandle 		recordTaskHandle;
	MessageHandle		recordMsgHandle;
	RecordState			recordState;
	SpeechRecordContext	sppechRecordContext;
}WxSpeechServiceContext;


extern uint8_t DevID[64];

WxSpeechContext wxSpeechContext;

WX_SPEECH_RECORD *pWxSpeechRecord = NULL;
WX_SPEECH_ID_RECORD *pWxSpeechIdRecord = NULL;

static WxSpeechServiceContext		wxSpeechServiceCt;
#define WXSS(x)						(wxSpeechServiceCt.x);

extern WxcloudDevInfo		wxcloudDevInfor;

#define WXSS_NUM_MESSAGE_QUEUE		10

/*
 * API: wx speech record infor 
 */
static void GetWxSpeechInforInit(void)
{
	while(!pWxSpeechRecord)
	{
		pWxSpeechRecord = pvPortMalloc(sizeof(WX_SPEECH_RECORD));
	}
	while(!pWxSpeechIdRecord)
	{
		pWxSpeechIdRecord = pvPortMalloc(sizeof(WX_SPEECH_ID_RECORD));
	}
	memset(&pWxSpeechRecord, 0, sizeof(WX_SPEECH_RECORD));
	memset(&pWxSpeechIdRecord, 0, sizeof(WX_SPEECH_ID_RECORD));
	
    ReadWxSpeechRecord();
    ReadWxSpeechIdRecord();
    if(pWxSpeechRecord->flag != MEDIA_RECORD_FLAG)
    {
        pWxSpeechRecord->flag = MEDIA_RECORD_FLAG;
        pWxSpeechRecord->current_item = 0;
        pWxSpeechRecord->total_number = 0;
        pWxSpeechRecord->newest_item = 0;
        pWxSpeechRecord->newest_number = 0;
        pWxSpeechRecord->valid_number = 0;
        wifi_audio_debug("pWxSpeechRecord is null...\n");
    }
    else
    {
        if((pWxSpeechRecord->total_number > SPEECH_LIST_TOTAL_NUM)||(pWxSpeechRecord->newest_number > pWxSpeechRecord->total_number))
        {
            pWxSpeechRecord->current_item = 0;
            pWxSpeechRecord->total_number = 0;
            pWxSpeechRecord->newest_item = 0;
            pWxSpeechRecord->newest_number = 0;
            pWxSpeechRecord->valid_number = 0;
        }
        else
        {
            if(pWxSpeechRecord->newest_number == 0)
            {
                pWxSpeechRecord->current_item = pWxSpeechRecord->newest_item;
            }

            if(pWxSpeechRecord->valid_number > SPEECH_LIST_OLD_NUM)
            {
                pWxSpeechRecord->valid_number = SPEECH_LIST_OLD_NUM;

                if((pWxSpeechRecord->total_number < SPEECH_LIST_OLD_NUM)&&(pWxSpeechRecord->valid_number > pWxSpeechRecord->total_number))
                {
                    pWxSpeechRecord->valid_number = pWxSpeechRecord->total_number;
                }
            }
        }
    }
    pWxSpeechRecord->old_item = 0;
}

//更新微信语音消息列表
//有新消息
static void WxSpeechUnplayedListPtUpdate(void)
{
	if(pWxSpeechRecord->newest_number)
    {
        pWxSpeechRecord->newest_number--;

        if(pWxSpeechRecord->newest_number == 0)
        {
            if(pWxSpeechRecord->total_number>1)
            {
                pWxSpeechRecord->old_item = 1;
                pWxSpeechRecord->current_item = (pWxSpeechRecord->newest_item-1);
            }
            else
            {
                pWxSpeechRecord->current_item = 0;
                pWxSpeechRecord->old_item = 0;
            }
        }
        else
        {
            pWxSpeechRecord->current_item++;
            if(pWxSpeechRecord->current_item >= SPEECH_LIST_TOTAL_NUM)
            {
                pWxSpeechRecord->current_item = 0;
            }
        }
        
        //在未读消息时,消息失效后,valid_number和newest_number关联
        /*if(download_ret == FILE_DOWNLOAD_INVALID)
        {
            pWxSpeechRecord->valid_number = pWxSpeechRecord->newest_number;
        }*/
    }
}

//无新消息
static void WxSpeechPlayedListPtUpdate(void)
{
	//在处理已读消息时,消息失效后,valid_number和old_item关联
    /*if(download_ret == FILE_DOWNLOAD_INVALID)
    {
        pWxSpeechRecord->valid_number = pWxSpeechRecord->old_item-1;
    }*/

    pWxSpeechRecord->old_item+=1;
    if(pWxSpeechRecord->old_item <= (pWxSpeechRecord->total_number-1))
    {
        if(pWxSpeechRecord->old_item >= pWxSpeechRecord->valid_number)
        {
            pWxSpeechRecord->old_item=0;
            pWxSpeechRecord->current_item = pWxSpeechRecord->newest_item;
        }
        else
        {
            if(pWxSpeechRecord->current_item)
            {
                pWxSpeechRecord->current_item -= 1;
            }
            else
            {
                pWxSpeechRecord->current_item = pWxSpeechRecord->total_number-1;
            }
        }
    }
    else
    {
        pWxSpeechRecord->old_item=0;
        pWxSpeechRecord->current_item = pWxSpeechRecord->newest_item;
    }
}

static void WxSpeechListPtUpdate(void)
{
	if(wxSpeechContext.newWxSpeech)
	{
		WxSpeechUnplayedListPtUpdate();
	}
	else
	{
		WxSpeechPlayedListPtUpdate();
	}
}

int32_t GetWxSpeechUnreadData()
{
	uint8_t		*wxTemp;
	uint8_t		wxId[20];
	uint8_t		wxNum = 0;
	uint8_t		temp;
	uint16_t	stringLen;
	uint16_t	posLen;
	uint16_t	stringStart, stringEnd;
	uint16_t	*posStart;
	uint8_t		speechItem[64];
	
	WxcloudStatus	wxCloudStatus;

	wxTemp = pvPortMalloc(2048);
	wxCloudStatus = WxCloudGetSpeechUnreadList(&wxTemp, &stringLen, &wxcloudDevInfor.devId);

	if(wxCloudStatus != WXCLOUD_STATUS_SUCCESS)
	{
		vPortFree(wxTemp);
		return WX_SPEECH_GET_FAIL;
	}

	//Err: len < 64 
	if(stringLen < SPEECH_ID_ITEM_LEN)
	{
		vPortFree(wxTemp);
		return WX_SPEECH_GET_DATA_ERR;
	}

	posStart = strstr(wxTemp, "mediaid;");
	if(posStart = NULL)
	{
		vPortFree(wxTemp);
		return WX_SPEECH_GET_DATA_ERR;
	}

	stringStart = *posStart + 8;
	stringEnd = stringLen;
	wxNum = 0;
	//计算总共有多少条未读消息
    while(stringStart<stringEnd)
    {
        if(wxTemp[stringStart++] == ';')
        {
            wxId[wxNum] = stringStart;
            wxNum++;
        }
    }
    DBG("wx speech unread list number = [%d]\n",wxNum);
	
    if(wxNum<=0)
    {
		vPortFree(wxTemp);
		return WX_SPEECH_GET_DATA_ERR;
    }

	//刷新 speech list信息,并将数据保存到list
    for(temp=wxNum; temp>0; temp--)
    {
    	stringStart = wxId[temp-1];
    	memset(speechItem, 0, SPEECH_ID_ITEM_LEN);
    	memcpy(speechItem, &wxTemp[stringStart], SPEECH_ID_ITEM_LEN);
    	
        if(pWxSpeechRecord->total_number < SPEECH_LIST_TOTAL_NUM)
        {
            pWxSpeechRecord->total_number += 1;
        }
        if(pWxSpeechRecord->newest_number < SPEECH_LIST_TOTAL_NUM)
        {
            pWxSpeechRecord->newest_number++;
        }

        pWxSpeechRecord->newest_item += 1;
        if(pWxSpeechRecord->total_number == 1)
        {
            pWxSpeechRecord->newest_item = 0;
        }
        if(pWxSpeechRecord->newest_item >= SPEECH_LIST_TOTAL_NUM)
        {
            pWxSpeechRecord->newest_item = 0;
        }
        if(pWxSpeechRecord->newest_number >= SPEECH_LIST_TOTAL_NUM)
        {
            pWxSpeechRecord->current_item = pWxSpeechRecord->newest_item+1;
            if(pWxSpeechRecord->current_item >= SPEECH_LIST_TOTAL_NUM)
            {
                pWxSpeechRecord->current_item = 0;
            }
        }
        else if(pWxSpeechRecord->newest_number == 1)
        {
            pWxSpeechRecord->current_item = pWxSpeechRecord->newest_item;
        }

        pWxSpeechRecord->valid_number++;
        if(pWxSpeechRecord->valid_number>=SPEECH_LIST_OLD_NUM)
        {
            pWxSpeechRecord->valid_number=SPEECH_LIST_OLD_NUM;
        }

        memset(&(pWxSpeechIdRecord->item[pWxSpeechRecord->newest_item].speech_id[0]),0,SPEECH_ID_ITEM_LEN);
        memcpy(&(pWxSpeechIdRecord->item[pWxSpeechRecord->newest_item].speech_id[0]),media_id,SPEECH_ID_ITEM_LEN);

		wxSpeechContext.newWxSpeech = 1;
    }

    BurnWxSpeechRecord();
    BurnWxSpeechIdRecord();

	vPortFree(wxTemp);
	return WX_SPEECH_GET_SUCCESS;
}

/*
 * Wx Speech Play
 */
MessageHandle GetWxSpeechPlayMessageHandle(void)
{
	return wxSpeechServiceCt.playMsgHandle;
}

void SendTickMsg2PlayTask(void)
{
	MessageContext		msgSend;
	MessageHandle		mainHandle;
	
	mainHandle = GetWxSpeechPlayMessageHandle();
	msgSend.msgId		= MSG_WX_SPEECH_TICK;
	msgSend.msgParams	= NULL;
	MessageSend(mainHandle, &msgSend);
}

static void ConfigMemory4SpeechPlay(void)
{
	/* for decoder */ 
	wxSpeechServiceCt.SpeechMemHandle.addr = (uint8_t *) SDRAM_BASE_ADDR + SDRAM_SIZE/2;
	wxSpeechServiceCt.SpeechMemHandle.mem_capacity = SDRAM_SIZE/2;
	wxSpeechServiceCt.SpeechMemHandle.mem_len = 0;
	wxSpeechServiceCt.SpeechMemHandle.p = 0;

	/* for audio core mix buffer */
	//WIFI_AUDIO_PLAY(audioCoreMixBuf) = (uint8_t *)(VMEM_ADDR + AUDIOC_CORE_TRANSFER_OFFSET);

	PcmFifoInitialize(PCM_FIFO_OFFSET, PCM_FIFO_SIZE, 0, 0);
	PcmFifoPause();
}

void SetWxSpeechPlayStage(WxSpeechPlayStage stage)
{
	wxSpeechContext.wxSpeechPlayStage = stage;
}

void WxSpeechPlayTask(void)
{
	MessageContext		msgRecv;
	uint8_t				mediaId[64];
	uint8_t 			*wxSpeechReadBuf = NULL;
	int32_t				wxSpeechFileLen=0;
	int32_t				errParam=0;
	WxcloudStatus		wxcloudStatus;
	uint32_t 			wxSpeechPlayTimeOut;

	GetWxSpeechInforInit();

	ConfigMemory4SpeechPlay();
	
	wxSpeechPlayTimeOut = 0xffffffff;//max
	
	/* register message handle */
	wxSpeechServiceCt.playMsgHandle = MessageRegister(WXSS_NUM_MESSAGE_QUEUE);

	while(1)
	{
		MessageRecv(wxSpeechServiceCt.playMsgHandle, &msgRecv, wxSpeechPlayTimeOut);
		switch(wxSpeechContext.wxSpeechPlayStage)
		{
			case WxSpeechPlay_Idle:
				//led flash
				if(wxSpeechContext.newWxSpeech)
				{
					wxSpeechContext.wxSpeechLedFlash++;
					if(wxSpeechContext.wxSpeechLedFlash & 0x01)
					{
						//led on
					}
					else
					{
						//led off
					}
					wxSpeechPlayTimeOut = 500;
				}
				else
				{
					//suspend
					wxSpeechPlayTimeOut = 0xffffffff;
				}
				break;

			case WxSpeechPlay_Start:
				memcpy(mediaId,&(pWxSpeechIdRecord->item[pWxSpeechRecord->current_item].speech_id[0]),SPEECH_ID_ITEM_LEN);

				wxcloudStatus = WxcloudGetMediaStart(mediaId);
				if(wxcloudStatus == WXCLOUD_STATUS_SUCCESS)
				{
					wxSpeechFileLen=0;
					errParam=0;
					wxcloudStatus = WxcloudGetMedia(&wxSpeechReadBuf, &wxSpeechFileLen, &errParam);
					if(wxcloudStatus == WXCLOUD_STATUS_SUCCESS)
					{
						wxSpeechContext.wxSpeechStart = 1;
						SetWxSpeechPlayStage(WxSpeechPlay_Runing);
					}
					else
					{
						//err:
						if(errParam != 0)
						{
						}
						else
						{
						}
					}
				}
				else if(wxcloudStatus == WXCLOUD_STATUS_NO_MORE_DATA)
				{
					SetWxSpeechPlayStage(WxSpeechPlay_End);
				}
				else
				{
					WxcloudGetMediaStop();
				}
				break;

			case WxSpeechPlay_Runing:
				if(mv_msize(&wxSpeechServiceCt.SpeechMemHandle) < 1024*20)
				{
					wxSpeechPlayTimeOut = 100;
				}
				else
				{
					if(wxSpeechContext.wxSpeechStart)
					{
						wxSpeechContext.wxSpeechStart = 0;
						//decoder and audiocore start
						
					}
					
	                wxcloudStatus = WxcloudGetMedia(&wxSpeechReadBuf, &wxSpeechFileLen, &errParam);
					if(wxcloudStatus == WXCLOUD_STATUS_SUCCESS)
					{
						
					}
	                else if(wxcloudStatus == WXCLOUD_STATUS_NO_MORE_DATA)
	                {
						SetWxSpeechPlayStage(WxSpeechPlay_WaitForEnd);
					}
					else if(wxcloudStatus == WXCLOUD_STATUS_FAILED)
					{
						SetWxSpeechPlayStage(WxSpeechPlay_End);
						//restart?
					}
				}
				break;

			case WxSpeechPlay_WaitForEnd:
				{
					//wait for decoder and audiocore end?
					
				}
				SetWxSpeechPlayStage(WxSpeechPlay_End);
				break;

			case WxSpeechPlay_End:
				WxcloudGetMediaStop();

				WxSpeechListPtUpdate();
				if(wxSpeechContext.newWxSpeech)
				{
					SetWxSpeechPlayStage(WxSpeechPlay_Start);
				}
				break;

			case WxSpeechPlay_Next:
				WxcloudGetMediaStop();

				WxSpeechListPtUpdate();
				SetWxSpeechPlayStage(WxSpeechPlay_Start);
				break;

			case WxSpeechPlay_Prev:
				break;

			case WxSpeechPlay_Stop:
				WxcloudGetMediaStop();
				
				SetWxSpeechPlayStage(WxSpeechPlay_Idle);
				break;
		}
	}
}

int32_t WxSpeechPlayTaskCreate(void)
{
	xTaskCreate(WxSpeechPlayTask, "WxSpeechPlay", 512, NULL, 3, &wxSpeechServiceCt.playTaskHandle );
	return 0;
}

void WxSpeechPlayTaskKill(void)
{
	vTaskDelete(&wxSpeechServiceCt.playTaskHandle);
}


/*
 * Wx Speech Record 
 */

void RecordLedDisplay(uint8_t disp)
{
	switch(disp)
	{
		case LEDON:
			break;

		case LEDOFF:
			break;
			
	}
}

void ConfigPuth4SpeechRecord(void)
{
    AdcVolumeSet(0xFB0, 0xFB0);
    PhubPathSel(ADCIN_TO_PMEM);
    CodecAdcChannelSel(ADC_CH_NONE);
    CodecAdcChannelSel(ADC_CH_MIC_L | ADC_CH_MIC_R);

    CodecDacMuteSet(TRUE, TRUE);
    DacAdcSampleRateSet(8000, 0);
    CodecDacMuteSet(FALSE, FALSE);
}

void SetWxSpeechRecordStage(WxSpeechRecordStage stage)
{
	wxSpeechContext.wxSpeechRecordStage = stage;
}

MessageHandle GetWxSpeechRecordMessageHandle(void)
{
	return wxSpeechServiceCt.recordMsgHandle;
}

void SendTickMsg2RecordTask(void)
{
	MessageContext		msgSend;
	MessageHandle		mainHandle;
	
	mainHandle = GetWxSpeechRecordMessageHandle();
	msgSend.msgId		= MSG_WX_SPEECH_TICK;
	msgSend.msgParams	= NULL;
	MessageSend(mainHandle, &msgSend);
}

void WxSpeechRecordTask(void)
{
	MessageContext	msgRecv;
    uint8_t		*pOutFile;
	uint32_t	FileSize;
    uint32_t	TempTick;
    uint32_t	n;
	uint32_t	wxSpeechRecordTimeOut;
	uint8_t		wxMediaId[64];
	WxcloudStatus	wxcloudStatus;
	
	wxSpeechRecordTimeOut = 0xffffffff;//max
	
	/* register message handle */
	wxSpeechServiceCt.recordMsgHandle = MessageRegister(WXSS_NUM_MESSAGE_QUEUE);
	while(1)
	{
		MessageRecv(wxSpeechServiceCt.recordMsgHandle, &msgRecv, wxSpeechRecordTimeOut);

		switch(wxSpeechContext.wxSpeechRecordStage)
		{
			case WxSpeechRecord_Idle:
				break;

			case WxSpeechRecord_Start:
				RecordLedDisplay(LEDON);
				
	            ConfigPuth4SpeechRecord();
	            
	            pOutFile = (uint8_t*)(CFG_SDRAM_BASE+1024*1024);
	            memcpy(pOutFile,AMRHeader,6);
	            pOutFile =pOutFile + 6;
	            TempTick = gSysTick;
	            FileSize = 6;

	            AdcPmemWriteEn();

	            wxSpeechRecordTimeOut = 0;
	            SetWxSpeechRecordStage(WxSpeechRecord_CollectAndEncoder);
				break;

			case WxSpeechRecord_CollectAndEncoder:
				if(AdcPmemPcmRemainLenGet() >= 160)//10ms
                {
                    AdcPcmDataRead(buf,160,1);
                    //n = Encoder_Interface_Encode(amr, /*MR795*/5, buf, outbuf, 0);
                    memcpy(pOutFile,outbuf,n);
                    pOutFile = pOutFile + n;
                    FileSize = FileSize + n;
                }
                else
                {
                    wxSpeechRecordTimeOut = 5;
                }
                
                if((gSysTick - TempTick) > 55000)//最大时间为60s
                {
	            	SetWxSpeechRecordStage(WxSpeechRecord_End);
                }
				break;

			case WxSpeechRecord_End:
				AdcPmemWriteDis();
				RecordLedDisplay(LEDOFF);
				
	            while(AdcPmemPcmRemainLenGet() >= 160)//10ms
	            {
	                AdcPcmDataRead(buf,160,1);
	                //n = Encoder_Interface_Encode(amr, /*MR795*/5, buf, outbuf, 0);
	                memcpy(pOutFile,outbuf,n);
	                pOutFile = pOutFile + n;
	                FileSize = FileSize + n;
	            }
	            
				PhubPathSel(PCMFIFO_MIX_DACOUT);

				wxcloudStatus = WxcloudSendMedia(pOutFile, FileSize, wxMediaId);
				if(wxcloudStatus == WXCLOUD_STATUS_SUCCESS)
				{
					uint8_t flag=0;

					if(wxSpeechContext.wxSpeechSendMode == WxSpeechSend2Family)
					{
						flag = 1;
					}
					else if(wxSpeechContext.wxSpeechSendMode == WxSpeechSend2Friend)
					{
						flag = 2;
					}
					
					WxCloudSendMediaMsg(wxMediaId, flag);

					//over
					wxSpeechRecordTimeOut = 0xffffffff;
					SetWxSpeechRecordStage(WxSpeechRecord_Idle);
				}
				break;
		}
	}
}

int32_t WxSpeechRecordTaskCreate(void)
{
	xTaskCreate(WxSpeechRecordTask, "WxSpeechRecord", 512*5, NULL, 4, &wxSpeechServiceCt.recordTaskHandle );
	return 0;
}

void WxSpeechRecordTaskKill(void)
{
	vTaskDelete(&wxSpeechServiceCt.recordTaskHandle);
}



/*
 * Wx Speech Service 
 */

static void WxSpeechServiceEntrance(void)
{
	MessageContext		msgRecv;
	MessageContext		msgSend;
	MessageHandle		mainHandle;
	
	/* register message handle */
	wxSpeechServiceCt.msgHandle = MessageRegister(WXSS_NUM_MESSAGE_QUEUE);

	wxSpeechServiceCt.serviceState = ServiceStateReady;

	/* Send message to main app */
	mainHandle = GetMainMessageHandle();
	msgSend.msgId		= MSG_SERVICE_CREATED;
	msgSend.msgParams	= MSG_PARAM_WX_SPEECH_SERVICE;
	MessageSend(mainHandle, &msgSend);

	while(1)
	{
		MessageRecv(wxSpeechServiceCt.msgHandle, &msgRecv, MAX_RECV_MSG_TIMEOUT);

		switch(msgRecv.msgId)
		{
			//service states
			case MSG_SERVICE_START:
				if(wxSpeechServiceCt.serviceState == ServiceStateReady)
				{
					wxSpeechServiceCt.serviceState = ServiceStateRunning;
					msgSend.msgId		= MSG_SERVICE_STARTED;
					msgSend.msgParams	= MSG_PARAM_WX_SPEECH_SERVICE;
					MessageSend(mainHandle, &msgSend);
					DBG("Wxcloud service start\n");
				}
				break;
				
			case MSG_SERVICE_STOP:
				if(wxSpeechServiceCt.serviceState == ServiceStateRunning)
				{
					wxSpeechServiceCt.serviceState = ServiceStateReady;
					msgSend.msgId		= MSG_SERVICE_STOPPED;
					msgSend.msgParams	= MSG_PARAM_WX_SPEECH_SERVICE;
					MessageSend(mainHandle, &msgSend);
				}
				break;

			case MSG_WX_SPEECH_GET_UNREAD_LIST:
				GetWxSpeechUnreadData();
				break;

			/*
			 * SPEECH PLAY MSG
			 */
			case MSG_WX_SPEECH_PLAY_READY:
				break;
				
			case MSG_WX_SPEECH_PLAY_START:
				if(wxSpeechServiceCt.serviceState == ServiceStateReady)
				{
					mainHandle = GetWxSpeechServiceMessageHandle();
					msgSend.msgId		= MSG_SERVICE_START;
					msgSend.msgParams	= MSG_PARAM_NULL;
					MessageSend(mainHandle, &msgSend);
				}
				break;
			case MSG_WX_SPEECH_PLAY_NEXT:
				wxSpeechContext.wxSpeechControl = WxSpeechNext;
				
				break;
			case MSG_WX_SPEECH_PLAY_STOP:
				break;
			
			/*
			 * SPEECH RECORD MSG
			 */
			case MSG_WX_SPEECH_RECORD_FAMILY_START:
				wxSpeechContext.wxSpeechSendMode = WxSpeechSend2Family;
				SetWxSpeechRecordStage(WxSpeechRecord_Start);
				
				SendTickMsg2RecordTask();
				break;
			case MSG_WX_SPEECH_RECORD_FAMILY_END:
				SetWxSpeechRecordStage(WxSpeechRecord_End);
				
				SendTickMsg2RecordTask();
				break;
				
			case MSG_WX_SPEECH_RECORD_FRIEND_START:
				wxSpeechContext.wxSpeechSendMode = WxSpeechSend2Friend;
				SetWxSpeechRecordStage(WxSpeechRecord_Start);
				
				SendTickMsg2RecordTask();
				break;
			case MSG_WX_SPEECH_RECORD_FRIEND_END:
				SetWxSpeechRecordStage(WxSpeechRecord_End);
				
				SendTickMsg2RecordTask();
				break;
				
			default:
				break;
		}
	}
}


/***************************************************************************************
 *
 * APIs
 *
 */

MessageHandle GetWxSpeechServiceMessageHandle(void)
{
	return wxSpeechServiceCt.msgHandle;
}

ServiceState GetWxSpeechServiceState(void)
{
	return wxSpeechServiceCt.serviceState;
}


int32_t WxSpeechServiceCreate(void)
{
	xTaskCreate(WxSpeechServiceEntrance, "WxSpeechService", 1024, NULL, 3, &wxSpeechServiceCt.taskHandle );
	return 0;
}


void WxSpeechServiceStart(void)
{
	MessageContext		msgSend;

	msgSend.msgId		= MSG_SERVICE_START;
	msgSend.msgParams	= NULL;
	MessageSend(wxSpeechServiceCt.msgHandle, &msgSend);
}

/**
 * @brief
 *		
 * @param
 * 	 NONE
 * @return  
 */
void WxSpeechServiceStop(void)
{
	MessageContext		msgSend;

	msgSend.msgId		= MSG_SERVICE_STOP;
	msgSend.msgParams	= NULL;
	MessageSend(wxSpeechServiceCt.msgHandle, &msgSend);
}


/**
 * @brief
 *		
 * @param
 * 	 NONE
 * @return  
 */
void WxSpeechServiceKill(void)
{
	vTaskDelete(wxSpeechServiceCt.taskHandle);
}

