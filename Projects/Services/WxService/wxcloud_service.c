/**
 **************************************************************************************
 * @file    wxcloud service.c
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

#include <string.h>
#include <stdarg.h>
#include "airkiss_types.h"
#include "airkiss_cloudapi.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "semphr.h"
#include "sockets.h"
#include "gpio.h"
#include "rtos_api.h"
#include "app_config.h"
#include "access_flash.h"
#include "app_message.h"
#include "wxcloud_service.h"
#include "wxcloud_api.h"
#include "sys_app.h"

/***************************************************************************************
 *
 * External defines
 *
 */

WxcloudParams		wxcloudParams;
WxcloudDevInfo		wxcloudDevInfor;

/** WIFI servcie name*/
const char wxcloudServiceName[] = "WxcloudService";
#define WXCLOUD_SERVICE_SIZE			1024
#define WXCLOUD_SERVICE_PRIO			3
	
#define WXCLOUD_SERVICE_TIMEOUT			1	/* 1 ms */

#define WXCS_NUM_MESSAGE_QUEUE			10


/***************************************************************************************
 *
 * Internal defines
 *
 */

const char wxcloudParentTaskName[] = "WxcloudParentTask";
#define WXCLOUD_PARENT_TASK_STACK_SIZE	1024
#define WXCLOUD_PARENT_TASK_PRIO		3
	
//微信消息 cmd tag 
const uint8_t *prev_cmd = "PREV";
const uint8_t *play_cmd = "PLAY";
const uint8_t *stop_cmd = "STOP";
const uint8_t *next_cmd = "NEXT";
const uint8_t *list_cmd = "LIST";
const uint8_t *voic_cmd = "VOIC";
const uint8_t *toke_cmd = "TOKE";
const uint8_t *up_list_cmd = "UPLI";
const uint8_t *volinc_cmd = "VOL ";
const uint8_t *voldec_cmd = "VOL-";
const uint8_t *power_cmd = "POWE";

typedef enum 
{
	WXCLOUD_IDLE = 0,
	WXCLOUD_INIT,
	WXCLOUD_DATA_PROCESS,
	WXCLOUD_REINIT,
}WxcloudState;

typedef struct _WxcloudParentContext
{
	WxcloudState		wxcloudState;
}WxcloudParentContext;

typedef struct _WxcloudServiceContext
{
	//wxcloud service
	xTaskHandle 		taskHandle;
	MessageHandle		msgHandle;
	ServiceState		serviceState;

	//wxcloud parent task
	xTaskHandle 		parentTaskHandle;
	MessageHandle		parentMsgHandle;
	ServiceState		parentState;
	WxcloudParentContext	wxcloudParentContext;
}WxcloudServiceContext;

/***************************************************************************************
 *
 * Internal variables
 *
 */
static WxcloudServiceContext		wxcloudServiceCt;
//static uint8_t wxcloudStage = WX_INIT;

extern uint8_t *access_token;
extern uint32_t AmrAccessId;
extern uint32_t AmrAccessId_s;

PLAY_LIST *WifiAudioPlayList;

uint8_t DevID[64];
uint8_t DevType[32];
uint8_t DevUser[48];

typedef struct _device_st {
    uint32_t flag;
    uint8_t  licence[256];
    uint8_t  id[64];
    uint32_t crc;
} device_st;
device_st *pdevice  = (uint8_t *)device_licence_flash_addr;

const uint8_t testinfo[] = "{\"mac\":\"247260028b3c\",\"sn\":\"4561231231231\"}";

uint8_t msg_id[17];
//uint8_t download = 0;
uint8_t song2paly_ctl=2,song3paly_ctl=2;

ak_mutex_t m_task_mutex, m_malloc_mutex,m_loop_mutex;

PLAY_RECORD *WifiaudioPlayRecord;

//处理push list数据
uint8_t listIdBuf[10];
uint8_t listSizeBuf[10];
uint8_t listSongIndexBuf[10];

uint8_t wx_send_buffer[512];

//void GetSongList(uint32_t zj_id,uint32_t song_index)
//{
//    memset(getlistcmd,0,1024);
//    sprintf(getlistcmd,"{\"msg_type\":\"notify\",\"services\":{\"operation_status\":{\"status\":1},\"air_conditioner\":{\"tempe_indoor\":26,\"tempe_outdoor\":31,\"tempe_target\":26,\"fan_speed\":50}},\"data\":\"getlist;%s;%s\"}",zj_id,song_index);
//    airkiss_cloud_sendmessage(1,(uint8_t*)getlistcmd,strlen(getlistcmd));
//}


//extern uint8_t DiskPlayStage;
//void play_sdxx(void)
//{
//    uint32_t Temp;
//    if(gSys.CurModuleID == MODULE_ID_WIFI_AUDIO)
//    {
//	    if(play_stage == WAIT_FOR_WEIXIN)
//	    {
//	        BurnWeixinRecord();
//	        BurnWeixinMediaId();
//	        SoundRemind(SOUND_SDXX,0);
//	    }
//	    else
//	    {
//	        Temp = MSG_PLAY_PAUSE;
//	        xQueueSend(KeyMSGQueue, &Temp, 0);
//	        vTaskDelay(1000);
//	        BurnWeixinRecord();
//	        BurnWeixinMediaId();
//	        SoundRemind(SOUND_SDXX,0);
//	        xQueueReset(PlaySoundRemindEndMSG);
//	        xQueueReceive(PlaySoundRemindEndMSG, &Temp, 2000);
//	        Temp = MSG_PLAY_PAUSE;
//	        xQueueSend(KeyMSGQueue, &Temp, 0);
//	    }
//	}
//	else if(gSys.CurModuleID == MODULE_ID_PLAYER_SD)
//	{
//		if((DiskPlayStage != DISK_STOP)||(DiskPlayStage != DISK_READY_WORK_FOR_WEIXIN)
//			||(DiskPlayStage != DISK_WAIT_FOR_WEIXIN))
//	    {
//	    	uint32_t backTemp;
//	    	backTemp = DiskPlayStage;
//	        Temp = MSG_DISK_STOP;
//	        xQueueSend(KeyMSGQueue, &Temp, 0);
//	        vTaskDelay(1000);
//	        BurnWeixinRecord();
//	        BurnWeixinMediaId();
//	        SoundRemind(SOUND_SDXX,0);
//	        xQueueReset(PlaySoundRemindEndMSG);
//	        xQueueReceive(PlaySoundRemindEndMSG, &Temp, 2000);
//	        if(backTemp != DISK_PAUSE)
//	        {
//		        Temp = MSG_PLAY_PAUSE;
//		        xQueueSend(KeyMSGQueue, &Temp, 0);
//		    }
//	    }
//	}
//}

uint16_t power_off_cmd;
uint32_t power_off_remain_time;
uint8_t media_id[512];

/***************************************************************************************
 *
 * Internal functions
 *
 */

static void SendMsg2WxcloudService(uint16_t msgId, uint16_t msgParams)
{
	MessageHandle		mainHandle;
	MessageContext		msgSend;

	mainHandle			= GetWxcloudMessageHandle();
	msgSend.msgId 		= msgId;
	msgSend.msgParams	= msgParams;
	MessageSend(mainHandle, &msgSend);
}

void GetNextPreSongURL(bool UpDown)
{
	if(UpDown)
	{
		//next song
        WifiAudioPlayList->playSongIndex++;
        if(WifiAudioPlayList->playSongIndex == WifiAudioPlayList->playListSize)
        {
            WifiAudioPlayList->playSongIndex = 0;
        }
        memset(WifiAudioPlayList->playUrl,0,512);
        memcpy(WifiAudioPlayList->playUrl,WifiAudioPlayList->playUrlNext,512);
	}
	else
	{
		//prev song
        if(WifiAudioPlayList->playSongIndex == 0)
        {
            WifiAudioPlayList->playSongIndex = WifiAudioPlayList->playListSize-1;
        }
        else
        {
            WifiAudioPlayList->playSongIndex--;
        }
        memset(WifiAudioPlayList->playUrl,0,512);
        memcpy(WifiAudioPlayList->playUrl,WifiAudioPlayList->playUrlPrev,512);
	}
	
	//if(zj_size > 3)
    {
        memset(wx_send_buffer,0,512);
        sprintf(wx_send_buffer,"{\"msg_type\":\"notify\",\"services\":{\"operation_status\":{\"status\":1},\"air_conditioner\":{\"tempe_indoor\":26,\"tempe_outdoor\":31,\"tempe_target\":26,\"fan_speed\":50}},\"data\":\"getlist#%s#%d#%s#%s#%s\"}",listIdBuf,WifiAudioPlayList->playSongIndex,DevType,DevID,DevUser);
        airkiss_cloud_sendmessage(1, (uint8_t*)wx_send_buffer,strlen(wx_send_buffer));
        //DBG("%s\n",wx_send_buffer);
    }
	
    /*if(zj_size == 1)
    {
        memset(url0,0,512);
        memcpy(url0,url2,512);
    }
    else if(zj_size == 2)
    {
        song2paly_ctl++;
        if(song2paly_ctl > 3)
        {
            song2paly_ctl = 2;
        }
        if(song2paly_ctl == 3)
        {
            memset(url0,0,512);
            memcpy(url0,url3,512);
        }
        else
        {
            memset(url0,0,512);
            memcpy(url0,url2,512);
        }
	}
	else if(zj_size == 3)
	{
	    switch(MSGEvent.value.v)
	    {
	    case MSG_SONG_NEXT:
	        song3paly_ctl++;
	        if(song3paly_ctl > 3)
	        {
	            song3paly_ctl = 1;
	        }
	        break;
	    case MSG_SONG_PRE:
	        if(song3paly_ctl < 2)
	        {
	            song3paly_ctl = 3;
	        }
	        else
	        {
	            song3paly_ctl--;
	        }
	        break;
	    default:
	        break;
	    }
	    if(song3paly_ctl == 1)
	    {
	        memset(url0,0,512);
	        memcpy(url0,url1,512);
	    }
	    else if(song3paly_ctl == 2)
	    {
	        memset(url0,0,512);
	        memcpy(url0,url2,512);
	    }
	    else if(song3paly_ctl == 3)
	    {
	        memset(url0,0,512);
	        memcpy(url0,url3,512);
	    }
	}*/

}

/*
 *
 * wxcloud params parse
 *
 */

void WxcloudDeviceUser(const uint8_t *body)
{
    uint16_t i,j;
    uint16_t id_s,id_e;
    for(i=0; i<strlen((char*)body); i++)
    {
        if(body[i] == '"')
        {
            if(memcmp(body+i+1,"user",4) == 0)
            {
                id_s = i+8;
                for(j=id_s; j<id_s+48; j++)
                {
                    if(body[j] == '"')
                    {
                        break;
                    }
                }

                if(j < id_s+48)
                {
                    id_e = j;
                    memset(DevUser, 0, 48);
                    memcpy(DevUser, body+id_s, id_e-id_s);
                    DBG("DeviceUser:%s\n",DevUser);
                    /*if(burn_dev_user)
                    {
                        burn_dev_user = 0;
                        BurnDeviceUser();
                    }*/
                }
                break;
            }
        }
    }
}

static void WxcloudPushList(const uint8_t *body, uint32_t pt)
{
    uint32_t i,j;
    i=pt;
	/*
    	"data":"<LIST;
    		5;
    		2667276;
    		100;
    		0;
    		http://fdfs.xmcdn.com/group14/M09/56/0A/wKgDZFcghP3gTTfyAQZL7g6lXN0462.mp3;
    		http://fdfs.xmcdn.com/group12/M06/9B/D9/wKgDW1dtBbiRZj1NAZ532QJpiik698.mp3;
    		http://fdfs.xmcdn.com/group5/M01/8F/08/wKgDtldtBvyTqmsSALzS80dFfjA235.mp3
    		>"
    		}
    */
	i = i+7;
    for(j=0; j<10; j++)
    {
        if(body[i+j] == ';')
        {
            break;
        }
    }
    memset(listIdBuf,0,10);
    memcpy(listIdBuf,body+i,j);
    DBG("listId:%s\n",listIdBuf);
    i = i+j+1;
    for(j=0; j<10; j++)
    {
        if(body[i+j] == ';')
        {
            break;
        }
    }
    memset(listSizeBuf,0,10);
    memcpy(listSizeBuf,body+i,j);
    DBG("listSize:%s\n",listSizeBuf);
    i = i+j+1;
    for(j=0; j<10; j++)
    {
        if(body[i+j] == ';')
        {
            break;
        }
    }
    memset(listSongIndexBuf,0,10);
    memcpy(listSongIndexBuf,body+i,j);
    DBG("listSongIndex:%s\n",listSongIndexBuf);


    i = i+j+1;
    for(j=0; j<512; j++)
    {
        if(body[i+j] == ';')
        {
            break;
        }
    }
    memset(WifiAudioPlayList->playUrlPrev,0,512);
    memcpy(WifiAudioPlayList->playUrlPrev,body+i,j);
    DBG("WifiAudioPlayList->playUrlPrev:%s\n",WifiAudioPlayList->playUrlPrev);

    i = i+j+1;
    for(j=0; j<512; j++)
    {
        if(body[i+j] == ';')
        {
            break;
        }
    }
    memset(WifiAudioPlayList->playUrlCur,0,512);
    memcpy(WifiAudioPlayList->playUrlCur,body+i,j);
    DBG("WifiAudioPlayList->playUrlCur:%s\n",WifiAudioPlayList->playUrlCur);

    i = i+j+1;
    for(j=0; j<512; j++)
    {
        if(body[i+j] == '>')
        {
            break;
        }
    }
    memset(WifiAudioPlayList->playUrlNext,0,512);
    memcpy(WifiAudioPlayList->playUrlNext,body+i,j);
    DBG("WifiAudioPlayList->playUrlNext:%s\n",WifiAudioPlayList->playUrlNext);

    if(strlen(listSongIndexBuf) == 1)
    {
        WifiAudioPlayList->playSongIndex=listSongIndexBuf[0]-0x30;
    }
    else if(strlen(listSongIndexBuf) == 2)
    {
        WifiAudioPlayList->playSongIndex=(listSongIndexBuf[0]-0x30)*10 + (listSongIndexBuf[1]-0x30);
    }
    else if(strlen(listSongIndexBuf) == 3)
    {
        WifiAudioPlayList->playSongIndex=(listSongIndexBuf[0]-0x30)*100 + (listSongIndexBuf[1]-0x30)*10 + listSongIndexBuf[2]-0x30;;
    }
    DBG("song_index = %d\n",WifiAudioPlayList->playSongIndex);

    if(strlen(listSizeBuf) == 1)
    {
        WifiAudioPlayList->playListSize=listSizeBuf[0]-0x30;
    }
    else if(strlen(listSizeBuf) == 2)
    {
        WifiAudioPlayList->playListSize=(listSizeBuf[0]-0x30)*10 + (listSizeBuf[1]-0x30);
    }
    else if(strlen(listSizeBuf) == 3)
    {
        WifiAudioPlayList->playListSize=(listSizeBuf[0]-0x30)*100 + (listSizeBuf[1]-0x30)*10 + listSizeBuf[2]-0x30;;
    }
    DBG("zj_size = %d\n",WifiAudioPlayList->playListSize);

    memset(WifiAudioPlayList->playUrl,0,512);
    memcpy(WifiAudioPlayList->playUrl,WifiAudioPlayList->playUrlCur,512);
//    song2paly_ctl=2;
//    song3paly_ctl=2;
}

static void WxcloudUpgradeList(const uint8_t *body, uint32_t pt)
{
    uint32_t i,j;
    i=pt;
	/*
    	"data":"<UPLI;
			5;
			3493173;
			100;
			6;
			http://fdfs.xmcdn.com/group26/M04/19/6A/w KgJWFjii3PzPPWnASc1PJ2dDPw149.mp3;
			http://fdfs.xmcdn.com/group26/ M0B/0A/93/wKgJWFjg-c6zaaRYAPoB39zyqyI113.mp3;
			http:// fdfs.xmcdn.com/group26/M01/0A/97 /wKgJWFjg-fPjuJOMAMkZGXqhKmY596.mp3
			>"
    		}
    */
    i = i+7;
    for(j=0; j<10; j++)
    {
        if(body[i+j] == ';')
        {
            break;
        }
    }
    memset(listIdBuf,0,10);
    memcpy(listIdBuf,body+i,j);
    DBG("listId:%s\n",listIdBuf);
    
    i = i+j+1;
    for(j=0; j<10; j++)
    {
        if(body[i+j] == ';')
        {
            break;
        }
    }
    memset(listSizeBuf,0,10);
    memcpy(listSizeBuf,body+i,j);
    DBG("listSize:%s\n",listSizeBuf);

    i = i+j+1;
    for(j=0; j<10; j++)
    {
        if(body[i+j] == ';')
        {
            break;
        }
    }
    memset(listSongIndexBuf,0,10);
    memcpy(listSongIndexBuf,body+i,j);
    DBG("listSongIndex:%s\n",listSongIndexBuf);

    i = i+j+1;
    for(j=0; j<512; j++)
    {
        if(body[i+j] == ';')
        {
            break;
        }
    }
    memset(WifiAudioPlayList->playUrlPrev,0,512);
    memcpy(WifiAudioPlayList->playUrlPrev,body+i,j);
    DBG("WifiAudioPlayList->playUrlPrev:%s\n",WifiAudioPlayList->playUrlPrev);

    i = i+j+1;
    for(j=0; j<512; j++)
    {
        if(body[i+j] == ';')
        {
            break;
        }
    }
    memset(WifiAudioPlayList->playUrlCur,0,512);
    memcpy(WifiAudioPlayList->playUrlCur,body+i,j);
    DBG("WifiAudioPlayList->playUrlCur:%s\n",WifiAudioPlayList->playUrlCur);

    i = i+j+1;
    for(j=0; j<512; j++)
    {
        if(body[i+j] == '>')
        {
            break;
        }
    }
    memset(WifiAudioPlayList->playUrlNext,0,512);
    memcpy(WifiAudioPlayList->playUrlNext,body+i,j);
    DBG("WifiAudioPlayList->playUrlNext:%s\n",WifiAudioPlayList->playUrlNext);
    if(strlen(listSongIndexBuf) == 1)
    {
        WifiAudioPlayList->playSongIndex=listSongIndexBuf[0]-0x30;
    }
    else if(strlen(listSongIndexBuf) == 2)
    {
        WifiAudioPlayList->playSongIndex=(listSongIndexBuf[0]-0x30)*10 + (listSongIndexBuf[1]-0x30);
    }
    else if(strlen(listSongIndexBuf) == 3)
    {
        WifiAudioPlayList->playSongIndex=(listSongIndexBuf[0]-0x30)*100 + (listSongIndexBuf[1]-0x30)*10 + listSongIndexBuf[2]-0x30;;
    }
    DBG("song_index = %d\n",WifiAudioPlayList->playSongIndex);

    if(strlen(listSizeBuf) == 1)
    {
        WifiAudioPlayList->playListSize=listSizeBuf[0]-0x30;
    }
    else if(strlen(listSizeBuf) == 2)
    {
        WifiAudioPlayList->playListSize=(listSizeBuf[0]-0x30)*10 + (listSizeBuf[1]-0x30);
    }
    else if(strlen(listSizeBuf) == 3)
    {
        WifiAudioPlayList->playListSize=(listSizeBuf[0]-0x30)*100 + (listSizeBuf[1]-0x30)*10 + listSizeBuf[2]-0x30;;
    }
    DBG("zj_size = %d\n",WifiAudioPlayList->playListSize);
    
}

static void WxcloudSpeechList(uint8_t *body, uint32_t pt)
{
    uint32_t i,j;
    uint32_t token_s,token_e,id_s,id_e;
    i=pt;
	/* 
	"data":"<VOIC;
		3;
		f927Bic3j2Eq8zndgZDHn7 FcGshJ5MOSIiLo_M4sxmkp4vUZSjlcsn ezH-slV4G-ztOfXoPsVWmJ0B5LC-8fzS Ye9spFfqCrV0QUnmwD240GPRdADAXGI;
		 0Y-q60yVD3bM-0MqO1KmrDYfdY5cAnDm NCwglMCqpgnyKsMerhA9v_FVW0DBdxEc ;
		64>
		"
	*/
    for(i=0; i<strlen((char*)body); i++)
    {
        if(body[i] == '<')
        {
            token_s = i;
            break;
        }
    }
    token_s = token_s + 8;//<VOICE;2;
    for(i=token_s; i<strlen((char*)body); i++)
    {
        if(body[i] == ';')
        {
            token_e = i;
            break;
        }
    }
    DBG(">>%d   %d\n",token_s,token_e);
    memset(access_token,0,512);
    memcpy(access_token,body+token_s,token_e - token_s);
    DBG("access_token：%s\n",access_token);

    id_s = token_e;
    for(i=id_s+1; i<strlen((char*)body); i++)
    {
        if(body[i] == ';')
        {
            id_e = i;
            break;
        }
    }

    memset(media_id,0,512);
    memcpy(media_id,body+id_s+1,id_e - (id_s)-1);
//        xQueueReset(PlayWeixinMSG);
    AmrAccessId = 1;
    AmrAccessId_s = 1;
	/*
    if(pt_media_record->total_number < MEDIA_RECORD_NUM)
    {
        pt_media_record->total_number += 1;
    }
    if(pt_media_record->newest_number < MEDIA_RECORD_NUM)
    {
        pt_media_record->newest_number++;
    }

    pt_media_record->newest_item += 1;
    if(pt_media_record->total_number == 1)
    {
        pt_media_record->newest_item = 0;
    }
    if(pt_media_record->newest_item >= MEDIA_RECORD_NUM)
    {
        pt_media_record->newest_item = 0;
    }
    if(pt_media_record->newest_number >= MEDIA_RECORD_NUM)
    {
        pt_media_record->current_item = pt_media_record->newest_item+1;
        if(pt_media_record->current_item >= MEDIA_RECORD_NUM)
        {
            pt_media_record->current_item = 0;
        }
    }
    else if(pt_media_record->newest_number == 1)
    {
        pt_media_record->current_item = pt_media_record->newest_item;
    }

    pt_media_record->valid_number++;
    if(pt_media_record->valid_number>=MEDIA_OLD_NUM)
    {
        pt_media_record->valid_number=MEDIA_OLD_NUM;
    }

    memset(&(pt_media_id_record->item[pt_media_record->newest_item].media_id[0]),0,MEDIA_ITEM_LEN);
    memcpy(&(pt_media_id_record->item[pt_media_record->newest_item].media_id[0]),media_id,MEDIA_ITEM_LEN);
	*/
    DBG("media_id：%s\n",media_id);
    //BurnWeixinRecord();
    //BurnWeixinMediaId();
}

static void WxcloudPoweroffCmd(const uint8_t *body, uint32_t pt)
{
	uint32_t i,j;
    uint32_t token_s,token_e,id_s,id_e;    
    uint8_t tmp[10];

	/*"data":"<POWE;
		2; //mode
		10; //timeout
		3>"
	*/
	i=pt;
	
	for(j=i; j<i+30; j++)
    {
        if(body[j] == '>')
        {
            break;
        }
    }

    if(j == i+30)
    {
        wifi_audio_debug("关机参数错误\n");
        return ;
    }

    while(i < j)
    {
        if(body[i++] == ';')
        {
            break;
        }
    }

    while(i < j)
    {
        if(body[i++] == ';')
        {
            break;
        }
    }
    token_s = i;

    while(i < j)
    {
        if(body[i++] == ';')
        {
            break;
        }
    }

    token_e = i-1;

    id_s = i;
    id_e = j;

    if(token_e-token_s > 4)
    {
        wifi_audio_debug("关机参数错误\n");
        return ;
    }

    memset(tmp, 0, 10);
    memcpy(tmp,body+token_s,token_e-token_s);

    power_off_remain_time = 0;

    for(i=0; i<strlen(tmp); i++)
    {
        power_off_remain_time *= 10;
        power_off_remain_time += tmp[i]-48;
    }

    wifi_audio_debug("power_off_remain_time=%d\n",power_off_remain_time);
    memset(tmp, 0, 10);

    memcpy(tmp, body+id_s, id_e-id_s);

    power_off_cmd = 0;

    for(i=0; i<strlen(tmp); i++)
    {
        power_off_cmd *= 10;
        power_off_cmd += tmp[i]-48;
    }

    wifi_audio_debug("power_off_cmd=%d\n",power_off_cmd);
	
}

static void WxcloudAccessToken(const uint8_t *body, uint32_t pt)
{
    uint32_t i;
    uint32_t token_s,token_e;
    i=pt;
    for(i=0; i<strlen((char*)body); i++)
    {
        if(body[i] == '<')
        {
            token_s = i;
            break;
        }
    }
    for(i=token_s; i<strlen((char*)body); i++)
    {
        if(body[i] == '>')
        {
            token_e = i;
            break;
        }
    }
    memset(access_token,0,512);
    memcpy(access_token,body+token_s+8,token_e - (token_s+8));
    DBG("access_token：%s\n",access_token);
}

/*
 *
 * wxcloud callback
 *
 */

static void WxcloudNotifyCB(uint32_t funcid, const uint8_t* body, uint32_t bodylen)
{
    uint32_t i,j;
    uint32_t token_s,token_e,id_s,id_e;
    uint32_t cheackcode;
    uint8_t tmp[10];
    
    DBG("333333333333333333\n");
    DBG("%s",body);

    for(i=10; i<27; i++)
    {
        if(body[i] == ',')
        {
            break;
        }
    }
    
    memset(msg_id,0,17);
    memcpy(msg_id,body+10,i-10);

    DBG("msg_id:%s\n\n\n",msg_id);
    memset(media_id,0,512);
    sprintf(media_id,"{\"asy_error_code\":0,\"asy_error_msg\":\"ok\",\"msg_id\":%s,\"msg_type\":\"set\",\"services\":{\"operation_status\":{\"status\":1111}}}",msg_id);
    airkiss_cloud_sendmessage(1,(uint8_t*)media_id,strlen(media_id));

    for(i=0; i<strlen((char*)body); i++)
    {
        if(body[i] == '<')
        {
            break;
        }
    }
    i=i+1;
    if(memcmp(body+i,prev_cmd,4) == 0)
    {
        DBG("上一曲\n");
		SendMsg2WxcloudService(MSG_WXCLOUD_CALLBACK, MSG_PARAM_PRE_SONG);
    }
    else if(memcmp(body+i,play_cmd,4) == 0)
    {
        DBG("播放\n");
		SendMsg2WxcloudService(MSG_WXCLOUD_CALLBACK, MSG_PARAM_PLAY_SONG);
    }
    else if(memcmp(body+i,stop_cmd,4) == 0)
    {
        DBG("停止\n");
    }
    else if(memcmp(body+i,next_cmd,4) == 0)
    {
        DBG("下一曲\n");
        SendMsg2WxcloudService(MSG_WXCLOUD_CALLBACK, MSG_PARAM_NEXT_SONG);
    }
    else if(memcmp(body+i,volinc_cmd,4) == 0)
    {
        DBG("音量+\n");
        SendMsg2WxcloudService(MSG_WXCLOUD_CALLBACK, MSG_PARAM_VOL_INC);
    }
    else if(memcmp(body+i,voldec_cmd,4) == 0)
    {
        DBG("音量-\n");
        SendMsg2WxcloudService(MSG_WXCLOUD_CALLBACK, MSG_PARAM_VOL_DEC);
    }
    else if(memcmp(body+i,list_cmd,4) == 0)
    {
        DBG("推送列表\n");
	    WxcloudPushList(body, i);
		SendMsg2WxcloudService(MSG_WXCLOUD_CALLBACK, MSG_PARAM_PUSH_LIST);
    }
    else if(memcmp(body+i,up_list_cmd,4) == 0)
    {
        DBG("更新列表\n");
		WxcloudUpgradeList(body,i);
		SendMsg2WxcloudService(MSG_WXCLOUD_CALLBACK, MSG_PARAM_UPGRADE_LIST);
    }
    else if(memcmp(body+i,voic_cmd,4) == 0)
    {
        DBG("微信语音\n");
        WxcloudSpeechList(body,i);
		SendMsg2WxcloudService(MSG_WXCLOUD_CALLBACK, MSG_PARAM_WXSPEECH);
    }
    else if(memcmp(body+i,toke_cmd,4) == 0)
    {
        DBG("access token\n");
        WxcloudAccessToken(body, i);
		SendMsg2WxcloudService(MSG_WXCLOUD_CALLBACK, MSG_PARAM_ACCESSTOKEN);
    }
    else if(memcmp(body+i,power_cmd,4) == 0)
    {
        wifi_audio_debug("关机\n");
        WxcloudPoweroffCmd(body, i);
		SendMsg2WxcloudService(MSG_WXCLOUD_CALLBACK, MSG_PARAM_POWEROFF);
	}
	else
	{
		DBG("未知命令\n");
	}

    WxcloudDeviceUser(body);
}

static void WxcloudSubdevNotifyCB(const uint8_t* subdevid, uint32_t funcid, const uint8_t* body, uint32_t bodylen)
{
    DBG("222222222222222222\n");
    DBG("%s",body);
}

static void WxcloudRespCB(uint32_t hashcode, uint32_t errcode, uint32_t funcid, const uint8_t* body, uint32_t bodylen)
{
    DBG("444444444444444444\n");
    DBG("%s",body);
}

static void WxcloudEventCB(EventValue event_value)
{
	int ret;
	DBG("111111111111111\n");
	DBG("%d\n",event_value);
	
	if(event_value == 1)
	{
//		SetConnectWXFlag();
//		SetLed3(0);
//		SetLed5(1);

#if 0 // Halley for test
		MessageHandle	msgHandle;
		MessageContext	msgSend;
		
		msgSend.msgId = MSG_WIFI_AUDIO_PUSH_SONG;
		msgHandle = GetWifiAudioPlayMessageHandle();
		MessageSend(msgHandle, &msgSend);
#endif
	}
	else if(event_value == 2)
	{
//		SetLed5(0);
//		SetLed3(1);
//		ClrConnectWXFlag();
	}
}

/***************************************************************************************
 *
 * wxcloud parent task
 *
 */

static MessageHandle GetWxcloudParentMessageHandle(void)
{
	return wxcloudServiceCt.parentMsgHandle;
}

static ServiceState GetWxcloudParentState(void)
{
	return wxcloudServiceCt.parentState;
}

static void SetWxcloudParentState(ServiceState state)
{
	wxcloudServiceCt.parentState = state;
}

static void SetWxcloudState(WxcloudState state)
{
	wxcloudServiceCt.wxcloudParentContext.wxcloudState = state;
}

static WxcloudState GetWxcloudState(void)
{
	return wxcloudServiceCt.wxcloudParentContext.wxcloudState;
}

static void WxcloudParentMsgProcess(MessageContext *msg)
{
	switch(msg->msgId)
	{
		case MSG_WXCLOUD_PARENT_INIT:
			break;
			
		case MSG_WXCLOUD_PARENT_START:
			if(GetWxcloudParentState() == ServiceStateReady) 
			{
				if(GetWxcloudState() == WXCLOUD_IDLE)
				{
					//wxcloud start login
					SetWxcloudState(WXCLOUD_INIT);
				}
			}
			break;
			
		case MSG_WXCLOUD_PARENT_STOP:
			break;
			
		default:
			break;
	}
}

static void WxcloudParentEntrance(void)
{
	MessageContext		msgRecv;
	MessageContext		msgSend;
	MessageHandle		mainHandle;
	
	int ret;
	uint32_t temp=0;
	airkiss_callbacks_t cbs;
	uint8_t *pdevice_id;
	uint8_t *pdevice_type;
	
	/* register message handle */
	wxcloudServiceCt.parentMsgHandle = MessageRegister(WXCS_NUM_MESSAGE_QUEUE);

	wxcloudServiceCt.wxcloudParentContext.wxcloudState = WXCLOUD_IDLE;

	wxcloudServiceCt.parentState = ServiceStateReady;
	
	SendMsg2WxcloudService(MSG_WXCLOUD_PARENT_INITED, NULL);

	while(1)
	{
		MessageRecv(wxcloudServiceCt.parentMsgHandle, &msgRecv, 0);

		if(msgRecv.msgId)
		{
			WxcloudParentMsgProcess(&msgRecv);
		}

		switch(wxcloudServiceCt.wxcloudParentContext.wxcloudState)
		{
			case WXCLOUD_IDLE:
				vTaskDelay(200);
				break;

			case WXCLOUD_INIT:
				if(pdevice->flag != DEVICE_LICENSE_FLAG)
				{
					vTaskDelay(500);
					DBG("No device license, please burn device license first\n");
					break;
				}
				DBG("wxcloud state : [init]\n");
				
				memset(DevID,0,64);

				wxcloudParams.devLicense = &pdevice->licence[0];
				wxcloudParams.devLicenseLen = strlen(pdevice->licence);
				wxcloudParams.taskMutex = &m_task_mutex;
				wxcloudParams.mallocMutex = &m_malloc_mutex;
				wxcloudParams.loopMutex = &m_loop_mutex;
				wxcloudParams.wxBuffer = (uint8_t *)WEIXIN_BUF_ADDR;
				wxcloudParams.wxBufferLen = WEIXIN_BUF_SIZE;
				wxcloudParams.property = &testinfo[0];
				wxcloudParams.propertyLen = 51;

				wxcloudParams.cbs.m_eventcb = WxcloudEventCB;
				wxcloudParams.cbs.m_notifycb = WxcloudNotifyCB;
				wxcloudParams.cbs.m_respcb = WxcloudRespCB;
				wxcloudParams.cbs.m_subdevnotifycb = WxcloudSubdevNotifyCB;
				
				WxcloudRegister(&wxcloudParams, &wxcloudDevInfor);

				memcpy(DevID, wxcloudDevInfor.devId, strlen(wxcloudDevInfor.devId));
				memset(DevType, 0, 32);
				memcpy(DevType, wxcloudDevInfor.devType, strlen(wxcloudDevInfor.devType));
				
				SetWxcloudState(WXCLOUD_DATA_PROCESS);
				SetWxcloudParentState(ServiceStateRunning);
				SendMsg2WxcloudService(MSG_WXCLOUD_PARENT_STARTED, NULL);
				break;

			case WXCLOUD_DATA_PROCESS:
				ret = WxcloudRun();
				vTaskDelay(ret);
				break;

			case WXCLOUD_REINIT:
				WxcloudDeregister();
				SetWxcloudParentState(ServiceStateReady);
				SetWxcloudState(WXCLOUD_IDLE);
				SendMsg2WxcloudService(MSG_WXCLOUD_PARENT_STOPPED, NULL);
				break;

			default:
				break;
		}
	}
}

static void WxcloudParentTaskCreate(void)
{
	xTaskCreate(WxcloudParentEntrance, 
				wxcloudParentTaskName, 
				WXCLOUD_PARENT_TASK_STACK_SIZE, 
				NULL, 
				WXCLOUD_PARENT_TASK_PRIO, 
				&wxcloudServiceCt.parentTaskHandle);
}

/***************************************************************************************
 *
 * wxcloud service
 *
 */

static void WxcloudServiceInit(void)
{
	//内存分配
    access_token      = pvPortMalloc(1024);
    
	WifiaudioPlayRecord = (PLAY_RECORD *)pvPortMalloc(sizeof(PLAY_RECORD));
	WifiAudioPlayList	= (PLAY_LIST *)pvPortMalloc(sizeof(PLAY_LIST));

	memset(&wxcloudServiceCt, 0, sizeof(wxcloudServiceCt));
}

static void SetWxcloudServiceState(ServiceState state)
{
	wxcloudServiceCt.serviceState = state;
}

static void WxcloudServiceEntrance(void)
{
	MessageContext		msgRecv;
	MessageContext		msgSend;
	MessageHandle		mainHandle;
	
	//wxcloud parent tast create
	WxcloudParentTaskCreate();

	/* register message handle */
	wxcloudServiceCt.msgHandle = MessageRegister(WXCS_NUM_MESSAGE_QUEUE);

	while(1)
	{
		MessageRecv(wxcloudServiceCt.msgHandle, &msgRecv, MAX_RECV_MSG_TIMEOUT);

		switch(msgRecv.msgId)
		{
			//main task msg
			case MSG_SERVICE_START:
				if(GetWxcloudServiceState()== ServiceStateReady)
				{
					if(GetWxcloudParentState() == ServiceStateRunning)
					{
						SetWxcloudServiceState(ServiceStateRunning);

						//send to main
						mainHandle 			= GetMainMessageHandle();
						msgSend.msgId		= MSG_SERVICE_STARTED;
						msgSend.msgParams	= MSG_PARAM_WXCLOUD_SERVICE;
						MessageSend(mainHandle, &msgSend);
						DBG("Wxcloud service started\n");
					}
					else
					{
						mainHandle			= GetWxcloudParentMessageHandle();
						msgSend.msgId		= MSG_WXCLOUD_PARENT_START;
						msgSend.msgParams	= NULL;
						MessageSend(mainHandle, &msgSend);
						DBG("Wxcloud parent task start\n");
					}
				}
				break;
				
			case MSG_SERVICE_STOP:
				if(GetWxcloudServiceState() == ServiceStateRunning)
				{
					if(GetWxcloudParentState() == ServiceStateRunning)
					{
						mainHandle 			= GetWxcloudParentMessageHandle();
						msgSend.msgId		= MSG_WXCLOUD_PARENT_STOP;
						msgSend.msgParams	= NULL;
						MessageSend(mainHandle, &msgSend);
						DBG("Wxcloud parent task stop\n");
					}
					else
					{
						SetWxcloudServiceState(ServiceStateReady);

						mainHandle			= GetMainMessageHandle();
						msgSend.msgId		= MSG_SERVICE_STOPPED;
						msgSend.msgParams	= MSG_PARAM_WXCLOUD_SERVICE;
						MessageSend(mainHandle, &msgSend);
						DBG("Wxcloud service stop\n");
					}
				}
				break;
			
			//wxcloud parent task msg
			case MSG_WXCLOUD_PARENT_INITED:
				if(GetWxcloudParentState() == ServiceStateReady)
				{
					SetWxcloudServiceState(ServiceStateReady);
					
					mainHandle 			= GetMainMessageHandle();
					msgSend.msgId		= MSG_SERVICE_CREATED;
					msgSend.msgParams	= MSG_PARAM_WXCLOUD_SERVICE;
					MessageSend(mainHandle, &msgSend);
				}
				break;
			
			case MSG_WXCLOUD_PARENT_STARTED:
				if((GetWxcloudParentState() == ServiceStateRunning) && 
					(GetWxcloudServiceState() == ServiceStateReady))
				{
					SetWxcloudServiceState(ServiceStateRunning);
					
					mainHandle 			= GetMainMessageHandle();
					msgSend.msgId		= MSG_SERVICE_STARTED;
					msgSend.msgParams	= MSG_PARAM_WXCLOUD_SERVICE;
					MessageSend(mainHandle, &msgSend);
					DBG("====== wxcloud service started ======\n");
				}
				break;
				
			case MSG_WXCLOUD_PARENT_STOPPED:
				if((GetWxcloudParentState() == ServiceStateReady) && 
					(GetWxcloudServiceState() == ServiceStateRunning))
				{
					SetWxcloudServiceState(ServiceStateReady);

					mainHandle 			= GetMainMessageHandle();
					msgSend.msgId		= MSG_SERVICE_STOPPED;
					msgSend.msgParams	= MSG_PARAM_WXCLOUD_SERVICE;
					MessageSend(mainHandle, &msgSend);
					DBG("====== wifi service stopped ======\n");
				}
				break;

			case MSG_WXCLOUD_CALLBACK:
				{
					mainHandle 			= GetMainMessageHandle();
					msgSend.msgId		= MSG_WXCLOUD_EVENT;
					msgSend.msgParams	= msgRecv.msgParams;
					MessageSend(mainHandle, &msgSend);
				}
				break;
				
			default:
				break;
		}
	}
}


/***************************************************************************************
 *
 * wxcloud service APIs
 *
 */

uint8_t *GetWifiPlayUrl(void)
{
	return &WifiAudioPlayList->playUrl[0];
}

MessageHandle GetWxcloudMessageHandle(void)
{
	return wxcloudServiceCt.msgHandle;
}

ServiceState GetWxcloudServiceState(void)
{
	return wxcloudServiceCt.serviceState;
}

int32_t WxcloudServiceCreate(void)
{
	WxcloudServiceInit();
	xTaskCreate(WxcloudServiceEntrance, 
				wxcloudServiceName, 
				WXCLOUD_SERVICE_SIZE, 
				NULL, 
				WXCLOUD_SERVICE_PRIO, 
				&wxcloudServiceCt.taskHandle);
	return 0;
}


void WxcloudServiceStart(void)
{
	MessageContext		msgSend;

	msgSend.msgId		= MSG_SERVICE_START;
	msgSend.msgParams	= NULL;
	MessageSend(wxcloudServiceCt.msgHandle, &msgSend);
}

/**
 * @brief
 *		
 * @param
 * 	 NONE
 * @return  
 */
void WxcloudServiceStop(void)
{
	MessageContext		msgSend;

	msgSend.msgId		= MSG_SERVICE_STOP;
	msgSend.msgParams	= NULL;
	MessageSend(wxcloudServiceCt.msgHandle, &msgSend);
}


/**
 * @brief
 *		
 * @param
 * 	 NONE
 * @return  
 */
void WxcloudServiceKill(void)
{
	if(wxcloudServiceCt.parentTaskHandle)
		vTaskDelete(wxcloudServiceCt.parentTaskHandle);
		
	if(wxcloudServiceCt.taskHandle)
		vTaskDelete(wxcloudServiceCt.taskHandle);
}

