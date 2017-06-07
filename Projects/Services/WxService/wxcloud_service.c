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
//#include "sys_app.h"
//#include "sound_remind.h"
//#include "wifi_audio.h"
//#include "board_common.h"
#include "rtos_api.h"
//#include "disk_player.h"
#include "app_config.h"
#include "access_flash.h"

#include "app_message.h"

#define wifi_audio_debug printf

//extern volatile unsigned long gSysTick;
//extern uint8_t *getlistcmd;
//extern const uint8_t getmessage[];
//extern uint8_t *access_token;
//extern uint8_t *media_id;
//extern uint32_t AmrAccessId;
//extern uint32_t AmrAccessId_s;
//extern uint8_t *url1;
//extern uint8_t *url2;
//extern uint8_t *url3;
//extern uint8_t *url0;
//extern QueueHandle_t KeyMSGQueue,NextPreSongReqMSG,GetNextPreSongMSG,PlayWeixinMSG,PlaySoundRemindEndMSG;
//extern uint8_t burn_dev_user;

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

//const uint8_t DevType[] = "gh_6f0e9cf4f5a0";
//const uint8_t DevUser[] = "oaox0wus34h-6IBezgp_-4Pwou3U";
uint8_t DevType[32];
//uint8_t DevUser[32];


uint8_t devlicence[256];
uint8_t DevID[64];

typedef struct _device_st {
    uint32_t flag;
    uint8_t  licence[256];
    uint8_t  id[64];
    uint32_t crc;
} device_st;
device_st *pdevice  = (uint8_t *)device_licence_flash_addr;

const uint8_t testinfo[] = "{\"mac\":\"247260028b3c\",\"sn\":\"4561231231231\"}";

uint8_t wx_send_buffer[512];
uint8_t msg_id[17];
uint8_t download = 0;
uint16_t zj_id;
uint16_t zj_size;
uint16_t song_index;
uint8_t zj_id_s[10];
uint8_t zj_size_s[10];
uint8_t song_index_s[10];
uint8_t song2paly_ctl=2,song3paly_ctl=2;

ak_mutex_t m_task_mutex, m_malloc_mutex,m_loop_mutex;

void recv_respcb(uint32_t hashcode, uint32_t errcode, uint32_t funcid, const uint8_t* body, uint32_t bodylen)
{
    printf("444444444444444444\n");
    printf("%s",body);
}

//void GetSongList(uint32_t zj_id,uint32_t song_index)
//{
//    memset(getlistcmd,0,1024);
//    sprintf(getlistcmd,"{\"msg_type\":\"notify\",\"services\":{\"operation_status\":{\"status\":1},\"air_conditioner\":{\"tempe_indoor\":26,\"tempe_outdoor\":31,\"tempe_target\":26,\"fan_speed\":50}},\"data\":\"getlist;%s;%s\"}",zj_id,song_index);
//    airkiss_cloud_sendmessage(1,(uint8_t*)getlistcmd,strlen(getlistcmd));
//}


extern uint8_t recv_app_cmd_flag;
extern uint8_t play_stage;
extern uint8_t DiskPlayStage;
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

//void get_device_user_from_wx(uint8_t* body)
//{
//    uint16_t i,j;
//    uint16_t id_s,id_e;
//    for(i=0; i<strlen((char*)body); i++)
//    {
//        if(body[i] == '"')
//        {
//            if(memcmp(body+i+1,"user",4) == 0)
//            {
//                id_s = i+8;
//                for(j=id_s; j<id_s+48; j++)
//                {
//                    if(body[j] == '"')
//                    {
//                        break;
//                    }
//                }

//                if(j < id_s+48)
//                {
//                    id_e = j;
//                    memset(DevUser, 0, 48);
//                    memcpy(DevUser, body+id_s, id_e-id_s);
//                    wifi_audio_debug("DeviceUser:%s\n",DevUser);
//                    if(burn_dev_user)
//                    {
//                        burn_dev_user = 0;
//                        BurnDeviceUser();
//                    }
//                }
//                break;
//            }
//        }
//    }
//}

extern uint8_t collect_weixin_audio;
uint16_t power_off_cmd;
uint32_t power_off_remain_time;
uint8_t media_id[512];
void recv_notifycb(uint32_t funcid, const uint8_t* body, uint32_t bodylen)
{
	MessageHandle		mainHandle;
	MessageContext		msgCt;
    uint32_t i,j;
    uint32_t token_s,token_e,id_s,id_e;
    uint32_t cheackcode;
    uint8_t tmp[10];
    printf("333333333333333333\n");
    printf("%s",body);

    for(i=10; i<27; i++)
    {
        if(body[i] == ',')
        {
            break;
        }
    }
    memset(msg_id,0,17);

    memcpy(msg_id,body+10,i-10);

    printf("msg_id:%s\n\n\n",msg_id);
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
//        if(collect_weixin_audio == 0)
//        {
//            osMessageSend(KeyMSGQueue,MSG_SONG_PRE,0);
//        }
        printf("上一曲\n");//0
        //getlist
        
		mainHandle = GetMainMessageHandle();
		msgCt.msgId 	= MSG_WEIXIN_EVENT;
		msgCt.msgParams	= MSG_PARAM_PRE_SONG;
		MessageSend(mainHandle, &msgCt);
    }
    else if(memcmp(body+i,play_cmd,4) == 0)
    {
//        if(collect_weixin_audio == 0)
//        {
//            osMessageSend(KeyMSGQueue,MSG_PLAY_PAUSE,0);
//        }
        printf("播放\n");//0
        
		mainHandle = GetMainMessageHandle();
		msgCt.msgId 	= MSG_WEIXIN_EVENT;
		msgCt.msgParams	= MSG_PARAM_PLAY_SONG;
		MessageSend(mainHandle, &msgCt);

    }
    else if(memcmp(body+i,stop_cmd,4) == 0)
    {

    }
    else if(memcmp(body+i,next_cmd,4) == 0)
    {
//        if(collect_weixin_audio == 0)
//        {
//            osMessageSend(KeyMSGQueue,MSG_SONG_NEXT,0);
//        }
        printf("下一曲\n");//0
        
		mainHandle = GetMainMessageHandle();
		msgCt.msgId 	= MSG_WEIXIN_EVENT;
		msgCt.msgParams	= MSG_PARAM_NEXT_SONG;
		MessageSend(mainHandle, &msgCt);
    }
    else if(memcmp(body+i,volinc_cmd,4) == 0)
    {
//        osMessageSend(KeyMSGQueue,MSG_VOL_UP,0);
        printf("音量+\n");//0
        
		mainHandle = GetMainMessageHandle();
		msgCt.msgId 	= MSG_WEIXIN_EVENT;
		msgCt.msgParams	= MSG_PARAM_VOL_INC;
		MessageSend(mainHandle, &msgCt);
    }
    else if(memcmp(body+i,voldec_cmd,4) == 0)
    {
//        osMessageSend(KeyMSGQueue,MSG_VOL_DW,0);
        printf("音量-\n");//0
        
		mainHandle = GetMainMessageHandle();
		msgCt.msgId 	= MSG_WEIXIN_EVENT;
		msgCt.msgParams	= MSG_PARAM_VOL_DEC;
		MessageSend(mainHandle, &msgCt);
    }
    else if(memcmp(body+i,list_cmd,4) == 0)
    {
        printf("推送列表\n");///5
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
//        i = i+7;
//        for(j=0; j<10; j++)
//        {
//            if(body[i+j] == ';')
//            {
//                break;
//            }
//        }
//        memset(zj_id_s,0,10);
//        memcpy(zj_id_s,body+i,j);
//        printf("zj_id_s:%s\n",zj_id_s);
//        i = i+j+1;
//        for(j=0; j<10; j++)
//        {
//            if(body[i+j] == ';')
//            {
//                break;
//            }
//        }
//        memset(zj_size_s,0,10);
//        memcpy(zj_size_s,body+i,j);
//        printf("zj_size_s:%s\n",zj_size_s);

//        i = i+j+1;
//        for(j=0; j<10; j++)
//        {
//            if(body[i+j] == ';')
//            {
//                break;
//            }
//        }
//        memset(song_index_s,0,10);
//        memcpy(song_index_s,body+i,j);
//        printf("song_index_s:%s\n",song_index_s);


//        i = i+j+1;
//        for(j=0; j<512; j++)
//        {
//            if(body[i+j] == ';')
//            {
//                break;
//            }
//        }
//        memset(url1,0,512);
//        memcpy(url1,body+i,j);
//        printf("url1:%s\n",url1);

//        i = i+j+1;
//        for(j=0; j<512; j++)
//        {
//            if(body[i+j] == ';')
//            {
//                break;
//            }
//        }
//        memset(url2,0,512);
//        memcpy(url2,body+i,j);
//        printf("url2:%s\n",url2);

//        i = i+j+1;
//        for(j=0; j<512; j++)
//        {
//            if(body[i+j] == '>')
//            {
//                break;
//            }
//        }
//        memset(url3,0,512);
//        memcpy(url3,body+i,j);
//        printf("url3:%s\n",url3);

//        if(strlen(song_index_s) == 1)
//        {
//            song_index=song_index_s[0]-0x30;
//        }
//        else if(strlen(song_index_s) == 2)
//        {
//            song_index=(song_index_s[0]-0x30)*10 + (song_index_s[1]-0x30);
//        }
//        else if(strlen(song_index_s) == 3)
//        {
//            song_index=(song_index_s[0]-0x30)*100 + (song_index_s[1]-0x30)*10 + song_index_s[2]-0x30;;
//        }
//        printf("song_index = %d\n",song_index);

//        if(strlen(zj_size_s) == 1)
//        {
//            zj_size=zj_size_s[0]-0x30;
//        }
//        else if(strlen(zj_size_s) == 2)
//        {
//            zj_size=(zj_size_s[0]-0x30)*10 + (zj_size_s[1]-0x30);
//        }
//        else if(strlen(zj_size_s) == 3)
//        {
//            zj_size=(zj_size_s[0]-0x30)*100 + (zj_size_s[1]-0x30)*10 + zj_size_s[2]-0x30;;
//        }
//        printf("zj_size = %d\n",zj_size);

//        sprintf(zj_size_s,"%s\r\n",zj_size_s);
//        sscanf(zj_size_s,"%d",zj_size);
//        printf("zj_size = %d\n",zj_size);

//        memset(url0,0,512);
//        memcpy(url0,url2,512);
//        if(collect_weixin_audio == 0)
//        {
//            osMessageSend(KeyMSGQueue,MSG_PLAY_URL,0);
//        }

        song2paly_ctl=2;
        song3paly_ctl=2;
    }
    else if(memcmp(body+i,up_list_cmd,4) == 0)
    {
        printf("更新列表\n");///5

//        i = i+7;
//        for(j=0; j<10; j++)
//        {
//            if(body[i+j] == ';')
//            {
//                break;
//            }
//        }
//        memset(zj_id_s,0,10);
//        memcpy(zj_id_s,body+i,j);
//        printf("zj_id_s:%s\n",zj_id_s);
//        i = i+j+1;
//        for(j=0; j<10; j++)
//        {
//            if(body[i+j] == ';')
//            {
//                break;
//            }
//        }
//        memset(zj_size_s,0,10);
//        memcpy(zj_size_s,body+i,j);
//        printf("zj_size_s:%s\n",zj_size_s);

//        i = i+j+1;
//        for(j=0; j<10; j++)
//        {
//            if(body[i+j] == ';')
//            {
//                break;
//            }
//        }
//        memset(song_index_s,0,10);
//        memcpy(song_index_s,body+i,j);
//        printf("song_index_s:%s\n",song_index_s);

//        i = i+j+1;
//        for(j=0; j<512; j++)
//        {
//            if(body[i+j] == ';')
//            {
//                break;
//            }
//        }
//        memset(url1,0,512);
//        memcpy(url1,body+i,j);
//        printf("url1:%s\n",url1);

//        i = i+j+1;
//        for(j=0; j<512; j++)
//        {
//            if(body[i+j] == ';')
//            {
//                break;
//            }
//        }
//        memset(url2,0,512);
//        memcpy(url2,body+i,j);
//        printf("url2:%s\n",url2);

//        i = i+j+1;
//        for(j=0; j<512; j++)
//        {
//            if(body[i+j] == '>')
//            {
//                break;
//            }
//        }
//        memset(url3,0,512);
//        memcpy(url3,body+i,j);
//        printf("url3:%s\n",url3);

//        if(strlen(song_index_s) == 1)
//        {
//            song_index=song_index_s[0]-0x30;
//        }
//        else if(strlen(song_index_s) == 2)
//        {
//            song_index=(song_index_s[0]-0x30)*10 + (song_index_s[1]-0x30);
//        }
//        else if(strlen(song_index_s) == 3)
//        {
//            song_index=(song_index_s[0]-0x30)*100 + (song_index_s[1]-0x30)*10 + song_index_s[2]-0x30;;
//        }
//        printf("song_index = %d\n",song_index);

//        if(strlen(zj_size_s) == 1)
//        {
//            zj_size=zj_size_s[0]-0x30;
//        }
//        else if(strlen(zj_size_s) == 2)
//        {
//            zj_size=(zj_size_s[0]-0x30)*10 + (zj_size_s[1]-0x30);
//        }
//        else if(strlen(zj_size_s) == 3)
//        {
//            zj_size=(zj_size_s[0]-0x30)*100 + (zj_size_s[1]-0x30)*10 + zj_size_s[2]-0x30;;
//        }
//        printf("zj_size = %d\n",zj_size);
//        sprintf(zj_size_s,"%s\r\n",zj_size_s);
//        sscanf(zj_size_s,"%d",zj_size);
//        printf("zj_size = %d\n",zj_size);
//        osMessageSend(GetNextPreSongMSG,0,0);
    }
    else if(memcmp(body+i,voic_cmd,4) == 0)
    {
        printf("微信语音\n");//2 token  id
//        for(i=0; i<strlen((char*)body); i++)
//        {
//            if(body[i] == '<')
//            {
//                token_s = i;
//                break;
//            }
//        }
//        token_s = token_s + 8;//<VOICE;2;
//        for(i=token_s; i<strlen((char*)body); i++)
//        {
//            if(body[i] == ';')
//            {
//                token_e = i;
//                break;
//            }
//        }
//        printf(">>%d   %d\n",token_s,token_e);
//        memset(access_token,0,512);
//        memcpy(access_token,body+token_s,token_e - token_s);
//        printf("access_token：%s\n",access_token);

//        id_s = token_e;
//        for(i=id_s+1; i<strlen((char*)body); i++)
//        {
//            if(body[i] == ';')
//            {
//                id_e = i;
//                break;
//            }
//        }

//        memset(media_id,0,512);
//        memcpy(media_id,body+id_s+1,id_e - (id_s)-1);
//        xQueueReset(PlayWeixinMSG);
//        AmrAccessId = 1;
//        AmrAccessId_s = 1;

//        if(pt_media_record->total_number < MEDIA_RECORD_NUM)
//        {
//            pt_media_record->total_number += 1;
//        }
//        if(pt_media_record->newest_number < MEDIA_RECORD_NUM)
//        {
//            pt_media_record->newest_number++;
//        }

//        pt_media_record->newest_item += 1;
//        if(pt_media_record->total_number == 1)
//        {
//            pt_media_record->newest_item = 0;
//        }
//        if(pt_media_record->newest_item >= MEDIA_RECORD_NUM)
//        {
//            pt_media_record->newest_item = 0;
//        }
//        if(pt_media_record->newest_number >= MEDIA_RECORD_NUM)
//        {
//            pt_media_record->current_item = pt_media_record->newest_item+1;
//            if(pt_media_record->current_item >= MEDIA_RECORD_NUM)
//            {
//                pt_media_record->current_item = 0;
//            }
//        }
//        else if(pt_media_record->newest_number == 1)
//        {
//            pt_media_record->current_item = pt_media_record->newest_item;
//        }

//        pt_media_record->valid_number++;
//        if(pt_media_record->valid_number>=MEDIA_OLD_NUM)
//        {
//            pt_media_record->valid_number=MEDIA_OLD_NUM;
//        }

//        memset(&(pt_media_id_record->item[pt_media_record->newest_item].media_id[0]),0,MEDIA_ITEM_LEN);
//        memcpy(&(pt_media_id_record->item[pt_media_record->newest_item].media_id[0]),media_id,MEDIA_ITEM_LEN);
//        printf("media_id：%s\n",media_id);
        //BurnWeixinRecord();
        //BurnWeixinMediaId();
    }
    else if(memcmp(body+i,toke_cmd,4) == 0)
    {
        printf("access token\n");//1 token
//        for(i=0; i<strlen((char*)body); i++)
//        {
//            if(body[i] == '<')
//            {
//                token_s = i;
//                break;
//            }
//        }
//        for(i=token_s; i<strlen((char*)body); i++)
//        {
//            if(body[i] == '>')
//            {
//                token_e = i;
//                break;
//            }
//        }
//        memset(access_token,0,512);
//        memcpy(access_token,body+token_s+8,token_e - (token_s+8));
//        printf("access_token：%s\n",access_token);
    }
    else if(memcmp(body+i,power_cmd,4) == 0)
    {
        wifi_audio_debug("关机\n");
//        for(j=i; j<i+30; j++)
//        {
//            if(body[j] == '>')
//            {
//                break;
//            }
//        }

//        if(j == i+30)
//        {
//            wifi_audio_debug("关机参数错误\n");
//            return ;
//        }

//        while(i < j)
//        {
//            if(body[i++] == ';')
//            {
//                break;
//            }
//        }

//        while(i < j)
//        {
//            if(body[i++] == ';')
//            {
//                break;
//            }
//        }
//        token_s = i;

//        while(i < j)
//        {
//            if(body[i++] == ';')
//            {
//                break;
//            }
//        }

//        token_e = i-1;

//        id_s = i;
//        id_e = j;

//        if(token_e-token_s > 4)
//        {
//            wifi_audio_debug("关机参数错误\n");
//            return ;
//        }

//        memset(tmp, 0, 10);

//        memcpy(tmp,body+token_s,token_e-token_s);

//        power_off_remain_time = 0;

//        for(i=0; i<strlen(tmp); i++)
//        {
//            power_off_remain_time *= 10;
//            power_off_remain_time += tmp[i]-48;
//        }

//        wifi_audio_debug("power_off_remain_time=%d\n",power_off_remain_time);

//        memset(tmp, 0, 10);

//        memcpy(tmp, body+id_s, id_e-id_s);

//        power_off_cmd = 0;

//        for(i=0; i<strlen(tmp); i++)
//        {
//            power_off_cmd *= 10;
//            power_off_cmd += tmp[i]-48;
//        }

//        wifi_audio_debug("power_off_cmd=%d\n",power_off_cmd);

	}
	else
	{
		printf("未知命令\n");
	}

//    get_device_user_from_wx(body);
}

void recv_subdevnotifycb(const uint8_t* subdevid, uint32_t funcid, const uint8_t* body, uint32_t bodylen)
{
    printf("222222222222222222\n");
    printf("%s",body);
}

//uint8_t ConnectWXFlag = 0;

//inline void SetConnectWXFlag(void)
//{
//    ConnectWXFlag = 1;
//}

//inline void ClrConnectWXFlag(void)
//{
//    ConnectWXFlag = 0;
//}

void recv_eventcb(EventValue event_value)
{
	int ret;
	printf("111111111111111\n");
	printf("%d\n",event_value);
	
	if(event_value == 1)
	{
//		SetConnectWXFlag();
//		SetLed3(0);
//		SetLed5(1);
	}
	else if(event_value == 2)
	{
//		SetLed5(0);
//		SetLed3(1);
//		ClrConnectWXFlag();
	}
}

//void GetNextPreSongURLTask(void)
//{
//    osMessage MSGEvent;
//    while(1)
//    {
//        MSGEvent = osMessageRecv(NextPreSongReqMSG,0xffffffff);
//        switch(MSGEvent.value.v)
//        {
//        case MSG_SONG_NEXT:
//            song_index++;
//            if(song_index == zj_size)
//            {
//                song_index = 0;
//            }
//            memset(url0,0,512);
//            memcpy(url0,url3,512);
//            break;
//        case MSG_SONG_PRE:
//            if(song_index == 0)
//            {
//                song_index = zj_size-1;
//            }
//            else
//            {
//                song_index--;
//            }
//            memset(url0,0,512);
//            memcpy(url0,url1,512);
//            break;
//        default:
//            break;
//        }

//        if(zj_size == 1)
//        {
//            memset(url0,0,512);
//            memcpy(url0,url2,512);
//        }
//        else if(zj_size == 2)
//        {
//            song2paly_ctl++;
//            if(song2paly_ctl > 3)
//            {
//                song2paly_ctl = 2;
//            }

//            if(song2paly_ctl == 3)
//            {
//                memset(url0,0,512);
//                memcpy(url0,url3,512);
//            }
//            else
//            {
//                memset(url0,0,512);
//                memcpy(url0,url2,512);
//            }
//        }
//        else if(zj_size == 3)
//        {
//            switch(MSGEvent.value.v)
//            {
//            case MSG_SONG_NEXT:
//                song3paly_ctl++;
//                if(song3paly_ctl > 3)
//                {
//                    song3paly_ctl = 1;
//                }
//                break;
//            case MSG_SONG_PRE:
//                if(song3paly_ctl < 2)
//                {
//                    song3paly_ctl = 3;
//                }
//                else
//                {
//                    song3paly_ctl--;
//                }
//                break;
//            default:
//                break;
//            }

//            if(song3paly_ctl == 1)
//            {
//                memset(url0,0,512);
//                memcpy(url0,url1,512);

//            }
//            else if(song3paly_ctl == 2)
//            {
//                memset(url0,0,512);
//                memcpy(url0,url2,512);

//            }
//            else if(song3paly_ctl == 3)
//            {
//                memset(url0,0,512);
//                memcpy(url0,url3,512);
//            }
//        }

//        osMessageSend(KeyMSGQueue,MSG_PLAY_URL,0);
//        if(zj_size > 3)
//        {
//            memset(wx_send_buffer,0,512);
//            sprintf(wx_send_buffer,"{\"msg_type\":\"notify\",\"services\":{\"operation_status\":{\"status\":1},\"air_conditioner\":{\"tempe_indoor\":26,\"tempe_outdoor\":31,\"tempe_target\":26,\"fan_speed\":50}},\"data\":\"getlist#%s#%d#%s#%s#%s\"}",zj_id_s,song_index,DevType,DevID,DevUser);
//            airkiss_cloud_sendmessage(1, (uint8_t*)wx_send_buffer,strlen(wx_send_buffer));
//            printf("%s\n",wx_send_buffer);
//            osMessageRecv(GetNextPreSongMSG,3000);
//        }
//    }
//}

#define  WX_IDLE			1
#define  WX_INIT			2
#define  WX_DATA_PROCESS	3
#define  WX_REINIT			4

uint8_t get_deviceid_flag=0;
void WeixinCloudTask(void)
{
	int ret;
	uint32_t temp=0;
	airkiss_callbacks_t cbs;
	uint8_t *pdevice_id;
	uint8_t *pdevice_type;
	uint8_t wxStage = WX_INIT;
	
	while(1)
	{
//		if((WifiStatus == 0)&&(wxStage != WX_IDLE))
//		{
//			wxStage = WX_REINIT;
//		}

	switch(wxStage)
	{
	case WX_IDLE:
		vTaskDelay(100);
//		if(WifiStatus)
//		{
//			wxStage = WX_INIT;
//		}
		break;

	case WX_INIT:
		if(pdevice->flag != DEVICE_LICENSE_FLAG)
		{
	
			vTaskDelay(500);
			printf("No device license, please burn device license first\n");
			break;
		}
		else
		{
			memcpy(devlicence,&pdevice->licence[0],256);
			memset(DevID,0,64);
		}

//		GetAccessToken();            
		ret=airkiss_cloud_init(devlicence,strlen(devlicence),&m_task_mutex, &m_malloc_mutex, &m_loop_mutex, (char*)WEIXIN_BUF_ADDR, WEIXIN_BUF_SIZE, testinfo, 51);
		if(ret != 0)
		{
			vTaskDelay(500);
			wifi_audio_debug("Init weixincloud fail\n");
			break;
		}
		wifi_audio_debug("Init weixincloud success\n");
		pdevice_id = airkiss_get_deviceid();
		memcpy(DevID, pdevice_id, strlen(pdevice_id));
		pdevice_type = pdevice_id-33;
		memset(DevType, 0, 32);
		memcpy(DevType, pdevice_type, strlen(pdevice_type));
		wifi_audio_debug("DeviceType:%s\n",DevType);
		get_deviceid_flag=1;
		cbs.m_eventcb = recv_eventcb;
		cbs.m_notifycb = recv_notifycb;
		cbs.m_respcb = recv_respcb;
		cbs.m_subdevnotifycb = recv_subdevnotifycb;
		airkiss_regist_callbacks(&cbs);
		wxStage = WX_DATA_PROCESS;
		break;

	case WX_DATA_PROCESS:
		ret = airkiss_cloud_loop();
		vTaskDelay(ret);
//		temp += ret;
//		if(temp > 60000)
//		{
//			temp = 0;
//	
//			wakeup_wifi_s();
//			GetAccessToken();
//		}
//	if(temp == ret)
//	{
//		SendDebugInfo2Sever();
//	}
		break;
	
	case WX_REINIT:
		airkiss_cloud_release();
		wxStage = WX_IDLE;
		break;
	default :
		break;
	}
	}
}