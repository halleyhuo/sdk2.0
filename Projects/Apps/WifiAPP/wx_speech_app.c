#include "airkiss_types.h"
#include <string.h>
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

#define wx_debug(format, ...)		printf(format, ##__VA_ARGS__)
#define	CFG_SDRAM_BASE	(0x60000000)

media_record_st *pt_media_record;
media_id_record_st *pt_media_id_record;

extern char WifiStreaming;
extern QueueHandle_t CollectAudioMSG,ReadyForWeixinMSG,PlayWeixinMSG,PlaySoundRemindEndMSG;
extern QueueHandle_t KeyMSGQueue;
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
uint8_t *media_id;
uint8_t *url1;
uint8_t *url2;
uint8_t *url3;
uint8_t *url0;
uint8_t *getlistcmd;
int16_t parser_http(uint8_t *buf, uint32_t buf_len, uint32_t *phead_len, uint32_t *pdata_len);
uint32_t parser_type(uint8_t *buf, uint32_t buf_len);
int32_t parser_errcode(uint8_t *buf, uint32_t buf_len, int32_t* error);
extern uint8_t play_stage;
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
void BurnWeixinRecord(void);
//void play_sdxx(void);

int32_t file_down_load(int32_t* errcode_id)
{
    int sock = -1;
    int32_t headlen,cn=0;
    osMessage MSGEvent;
    int32_t Theadlen0,Theadlen1,Temp0,RecvSize;

    osMessageSend(KeyMSGQueue,MSG_START_WEIXIN,0xffffffff);
    xQueueReset(ReadyForWeixinMSG);
    osMessageRecv(ReadyForWeixinMSG, 0xffffffff);
    
    WifiStreamHandle = GetWifiAudioPlayDecoderBuffer();
    play_weixin_stage = PLAY_WEIIXN_CONNECT;
    AudioFormat = AMR_DECODER;

    *errcode_id = 0;
    while(1)
    {
        MSGEvent = osMessageRecv(PlayWeixinMSG,0);
        if(MSGEvent.value.v == MSG_START_PLAY_FRIEND_WEIXN)
        {
            osMessageSend(PlayWeixinMSG,MSG_START_PLAY_FRIEND_WEIXN,0);
            play_weixin_stage = PLAY_WEIIXN_NEXT;
        }
        if(MSGEvent.value.v == MSG_STOP_PLAY_FRIEND_WEIXIN)
        {
            play_weixin_stage = PLAY_WEIIXN_STOP;
        }

        if((play_stage != WAIT_URL)&&(play_stage != WAIT_FOR_WEIXIN))
        {
            play_weixin_stage = PLAY_WEIIXN_STOP;
        }

        switch(play_weixin_stage)
        {
        case PLAY_WEIIXN_CONNECT:
            if(connect_file_weixin(&sock) != 1)
            {
                wifi_audio_debug("_file_down_load: Connect weixin fail\n");
                return FILE_DOWNLOAD_ERR;
            }
            memset(wx_read_buffer,0,1024);
            sprintf((char*)wx_read_buffer,"GET /cgi-bin/media/get?access_token=%s&media_id=%s HTTP/1.1\r\nConnection: Keep-Alive\r\nAccept-Encoding:gzip, deflate\r\nAccept-Language: zh-CN,en,*\r\nUser-Agent: Mozilla/5.0\r\nHost: file.api.weixin.qq.com\r\n\r\n",access_token,media_id);
            lwip_write(sock,wx_read_buffer,sizeof(wx_read_buffer));
            memset(wx_read_buffer,0,1024);
            headlen = wifi_read(sock,wx_read_buffer,1024,3000);
            wx_debug("wx........%s\n",wx_read_buffer);
            wx_debug("wx_rx_len=%d\n",headlen);

            if(headlen <= 0)
            {
                close(sock);
                wx_debug("_file_down_load:Get head data fail\n");
                return FILE_DOWNLOAD_ERR;
            }

            Theadlen0 = parser_type(wx_read_buffer, headlen);
            if(memcmp(&wx_read_buffer[Theadlen0],"audio/amr",9) != 0)
            {
                close(sock);
                wx_debug("_file_down_load:Get This is not amr data\n");

                parser_errcode(wx_read_buffer, headlen, errcode_id);
                return FILE_DOWNLOAD_INVALID;
            }

            wx_debug("\n content type = amr...\n");
            parser_http(wx_read_buffer, headlen, &Theadlen0, &Theadlen1);
            mv_mwrite(&wx_read_buffer[Theadlen0], 1, headlen-Theadlen0, WifiStreamHandle);
            RecvSize = headlen-Theadlen0;
            play_weixin_stage = PLAY_WEIIXN_DOWN_DATA;
            break;
        case PLAY_WEIIXN_DOWN_DATA:
            if(mv_mremain(WifiStreamHandle) < 512)
            {
                vTaskDelay(10);
            }
            else
            {
                if(RecvSize < Theadlen1)
                {
                    Temp0 = wifi_read(sock,wx_read_buffer,512,3000);
                    wx_debug("wx_rx_len=%d\n",Temp0);

                    if(Temp0 > 0)
                    {
                        mv_mwrite(wx_read_buffer, 1, Temp0, WifiStreamHandle);
                        RecvSize += Temp0;
                    }
                }

                if(!WifiStreamReady && (mv_msize(WifiStreamHandle) > 256))
                {
                    WifiStreamReady = 1;
                    vTaskDelay(10);
                }

                if((RecvSize >= Theadlen1)||(Temp0 <= 0))
                {
                    close(sock);
                    sock = -1;
                    play_weixin_stage = PLAY_WEIIXN_WAIT1;
                }
            }
            break;
        case PLAY_WEIIXN_WAIT1:
            if((mv_msize(WifiStreamHandle) > 0)||( audio_decoder->error_code != -127 ))
            {
                cn++;
                if(cn > 100)
                {
                    wifi_audio_debug("break1\n");
                    play_weixin_stage = PLAY_WEIIXN_WAIT2;
                }
                vTaskDelay(100);
                wifi_audio_debug("Wait play weixin remain: %d\n",mv_msize(WifiStreamHandle));
            }
            else
            {
                play_weixin_stage = PLAY_WEIIXN_WAIT2;
            }
            break;
        case PLAY_WEIIXN_WAIT2:
            if(!PcmFifoIsEmpty())
            {
                cn++;
                if(cn > 1100)
                {
                    wifi_audio_debug("break2\n");
                    play_weixin_stage = PLAY_WEIIXN_WAIT2;
                }
                vTaskDelay(10);
                wifi_audio_debug("Wait PcmFifoIsEmpty\n");
            }
            else
            {
                play_weixin_stage = PLAY_WEIIXN_END;
            }
            break;
        case PLAY_WEIIXN_END:
            osMessageSend(KeyMSGQueue,MSG_WEIXN_DONE,0);
            if((play_stage == WAIT_URL)||(play_stage == WAIT_FOR_WEIXIN))
            {
                WifiStreamReady        = 0;
                WifiStreaming          = 0;
            }
            if(sock != -1)
            {
                close(sock);
            }
            return FILE_DOWNLOAD_OK;
            break;

        case PLAY_WEIIXN_STOP:
            osMessageSend(KeyMSGQueue,MSG_WEIXN_DONE,0);
            if((play_stage == WAIT_URL)||(play_stage == WAIT_FOR_WEIXIN))
            {
                WifiStreamReady        = 0;
                WifiStreaming          = 0;
            }
            if(sock != -1)
            {
                close(sock);
            }
            return FILE_DOWNLOAD_DROPOUT;
            break;

        case PLAY_WEIIXN_NEXT:
            osMessageSend(KeyMSGQueue,MSG_WEIXN_DONE,0);
            if((play_stage == WAIT_URL)||(play_stage == WAIT_FOR_WEIXIN))
            {
                WifiStreamReady        = 0;
                WifiStreaming          = 0;
            }
            if(sock != -1)
            {
                close(sock);
            }
            return FILE_DOWNLOAD_NEXT;
            break;

        default:
            break;
        }
    }

}

bool file_up_load(uint8_t *Buffer,uint32_t FileSize)
{
    int sock;
    uint32_t datalength;
    uint32_t rand;
    uint32_t i,j;
    int16_t len;

    if(connect_file_weixin(&sock) != 1)
    {
        wifi_audio_debug("_file_up_load: Connect weixin fail\n");
        return 0;
    }

    datalength = FileSize;
    rand = gSysTick;
    memset(wx_read_buffer,0,1024);
    sprintf((char*)wx_read_buffer,"POST /cgi-bin/media/upload?access_token=%s&type=voice HTTP/1.1\r\nHost: file.api.weixin.qq.com\r\nContent-Length: %d\r\nContent-Type: multipart/form-data; boundary=------------------------7e21b4c3%08x\r\n\r\n--------------------------7e21b4c3%08x\r\nContent-Disposition: form-data; name=\"media\"; filename=\"E:\\WWW\\1.amr\"\r\nContent-Type: application/octet-stream\r\n\r\n",access_token,157+FileSize+48,rand,rand);
    write(sock,wx_read_buffer,strlen((char*)wx_read_buffer));
    wx_debug("httpreq:\n%s",wx_read_buffer);
    {
        uint32_t Temp0,Temp1,i;
        Temp0 = datalength/1024;
        Temp1 = datalength%1024;
        for(i=0; i<Temp0; i++)
        {
            memcpy(wx_read_buffer,Buffer+i*1024,1024);
            write(sock,wx_read_buffer,1024);
        }
        if(Temp1)
        {
            memcpy(wx_read_buffer,Buffer+Temp0*1024,Temp1);
            write(sock,wx_read_buffer,Temp1);
        }
        memset(wx_read_buffer,0,1024);
        sprintf((char*)wx_read_buffer,"--------------------------7e21b4c3%08x--\r\n\r\n\r\n\r\n",rand);
        write(sock,wx_read_buffer,strlen((char*)wx_read_buffer));
    }
    memset(wx_read_buffer,0,512);
    len = wifi_read(sock,wx_read_buffer,512,3000);
    wx_debug("_file_up_load: get media_id:%s\n\n",wx_read_buffer);
    closesocket(sock);
    if(len > 0)
    {
        for(i=0; i<strlen((char*)wx_read_buffer); i++)
        {
            if(memcmp(find_media,wx_read_buffer+i,strlen(find_media)) == 0)
            {
                wifi_audio_debug("file_up_load: media:%s\n",wx_read_buffer+i+11);
                memcpy(media_id,wx_read_buffer+i+11,strlen((char*)wx_read_buffer)-i-11);
                for(j=0; j<100; j++)
                {
                    if(media_id[j] == '"')
                    {
                        memset(media_id+j,0,512-j);
                    }
                }
                wifi_audio_debug("_file_up_load: media_id:%s\n",media_id);
                return 1;
            }
        }

        wifi_audio_debug("_file_up_load: Invalid media information\n");
        return 0;
    }
    else
    {
        wifi_audio_debug("file_up_load: Get media timeout\n");
        return 0;
    }
}

extern uint8_t DevID[64];
#define WX_MEDIA_ID_LEN		64
void get_wx_unread_list(void)
{
    int sock,RecvDataLen;
    uint8_t *recv_buf,read_done;
    int16_t i,len, mediaid_e, mediaid_s;
    uint8_t *wxtemp;
    uint8_t wx_sum;
    uint16_t wx_item[20];
    uint16_t pt_list;

    if(ConnectURL("www.yuanyiwei.top", &sock) == 1)
    {
        wxtemp = pvPortMalloc(2048);

        memset(wx_read_buffer,0,1024);
        sprintf((char*)wx_read_buffer,"GET /device_get_mediaid.php?device_id=%s HTTP/1.1\r\nHost: www.yuanyiwei.top\r\nConnection: keep-alive\r\n\r\n",DevID);
        lwip_write(sock,wx_read_buffer,sizeof(wx_read_buffer));

        memset(wxtemp,0,2048);
        read_done=1;
        RecvDataLen = 0;
        while(read_done)
        {
            len = wifi_read(sock,&wxtemp[RecvDataLen],1024,3000);

            if(len > 0)
            {
                RecvDataLen += len;
            }
            else
            {
                break;
            }

            for(i=RecvDataLen; i>0; i--)
            {
                if(wxtemp[i] == ')')
                {
                    read_done = 0;
                    break;
                }
            }
        }
        printf(wxtemp);
        wx_debug("wx_rx_len=%d\n",RecvDataLen);

        if(RecvDataLen<=0)
        {
            close(sock);
            vPortFree(wxtemp);
            return;
        }

        mediaid_e=0;
        mediaid_s=0;

        i=0;
        while(i<RecvDataLen)
        {
            if(wxtemp[i++] == '(')
            {
                if(memcmp(&wxtemp[i],"mediaid", 7) == 0)
                {
                    mediaid_s=i+7;
                    break;
                }
            }
        }
        if(mediaid_s == 0)
        {
            close(sock);
            vPortFree(wxtemp);
            return;
        }

        for(i=mediaid_s; i<RecvDataLen; i++)
        {
            if(wxtemp[i] == ')')
            {
                mediaid_e=i;
                break;
            }
        }
        //wx_debug("media id start = %d\n",mediaid_s);
        //wx_debug("media id end = %d\n",mediaid_e);

        if(mediaid_e <= (mediaid_s+1))
        {
            close(sock);
            vPortFree(wxtemp);
            return;
        }

        wx_sum = 0;
        i=mediaid_s;
        memset(wxtemp,0,20);
        while(i<mediaid_e)
        {
            if(wxtemp[i++] == ';')
            {
                wx_item[wx_sum] = i;
                wx_sum++;
            }
        }
        wx_debug("unread media number = [%d]\n",wx_sum);

        if(wx_sum<=0)
        {
            close(sock);
            vPortFree(wxtemp);
            return;
        }

        SoundRemind(SOUND_XZXX, 1);
        xQueueReset(PlaySoundRemindEndMSG);

        for(i=wx_sum; i>0; i--)
        {
            pt_list = wx_item[i-1];
            //wx_debug("pt_list = %d\n",pt_list);
            memset(media_id,0,512);
            memcpy(media_id,&wxtemp[pt_list],64);
            AmrAccessId = 1;
            //AmrAccessId_s = 1;

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
            //printf("media_id：%s\n",media_id);
        }
        osMessageRecv(PlaySoundRemindEndMSG,2000);

        close(sock);
        vPortFree(wxtemp);

        BurnWeixinRecord();
        BurnWeixinMediaId();
    }
}
extern uint8_t ConnectWXFlag;
uint8_t back2PlayStage = 0xff;
extern uint8_t DiskPlayStage;
void PlayWeixinAudioTask(void)
{
    osMessage MSGEvent;
    int32_t download_ret=0;
    uint32_t err_id=0;

    GetMediaIdRecord();
    if(pt_media_record->flag != MEDIA_RECORD_FLAG)//0x87651234)
    {
        pt_media_record->flag = MEDIA_RECORD_FLAG;
        pt_media_record->current_item = 0;
        pt_media_record->total_number = 0;
        pt_media_record->newest_item = 0;
        pt_media_record->newest_number = 0;
        pt_media_record->valid_number = 0;
        wifi_audio_debug("pt_media_record is null...\n");
    }
    else
    {
        if((pt_media_record->total_number > MEDIA_RECORD_NUM)||(pt_media_record->newest_number > pt_media_record->total_number))
        {
            pt_media_record->current_item = 0;
            pt_media_record->total_number = 0;
            pt_media_record->newest_item = 0;
            pt_media_record->newest_number = 0;
            pt_media_record->valid_number = 0;
        }
        else
        {
            if(pt_media_record->newest_number == 0)
            {
                pt_media_record->current_item = pt_media_record->newest_item;
            }

            if(pt_media_record->valid_number > MEDIA_OLD_NUM)
            {
                pt_media_record->valid_number = MEDIA_OLD_NUM;

                if((pt_media_record->total_number < MEDIA_OLD_NUM)&&(pt_media_record->valid_number > pt_media_record->total_number))
                {
                    pt_media_record->valid_number = pt_media_record->total_number;
                }
            }
        }
    }
    pt_media_record->old_item = 0;
    xQueueReset(PlayWeixinMSG);
    while(1)
    {

        MSGEvent = osMessageRecv(PlayWeixinMSG,0);
        if(ConnectWXFlag == 0)
        {
            MSGEvent.value.v = MSG_NONE;
        }
        if(MSGEvent.value.v == MSG_START_PLAY_FRIEND_WEIXN)
        {
            //CodecDacMuteSet(FALSE, FALSE);
            if(AmrAccessId == 1)
            {
                AmrAccessId = 0;
            }

            if(pt_media_record->total_number == 0)
            {
                continue;
            }

            if((pt_media_record->total_number)&&(pt_media_record->newest_number==0)&&(pt_media_record->valid_number==0))
            {
                continue;
            }

            play_weixin_audio=1;

            memset(media_id,0,512);
            memcpy(media_id,&(pt_media_id_record->item[pt_media_record->current_item].media_id[0]),MEDIA_ITEM_LEN);

            download_ret = 0;
            err_id = 0;
            download_ret = file_down_load(&err_id);

            if((download_ret < FILE_DOWNLOAD_OK)||(download_ret > FILE_DOWNLOAD_NEXT))
            {
                //下面开始处理微信返回错误码的相关信息
                if(download_ret == FILE_DOWNLOAD_INVALID)
                {
                    wifi_audio_debug("error code id = [%d].\n", err_id);
                    if(err_id == RESP_SYSTEM_BUSY)
                    {
                        wifi_audio_debug("system is busy...\n");

                        //SoundRemind(SOUND_XTFM,1);
                        //xQueueReset(PlaySoundRemindEndMSG);
                        //osMessageRecv(PlaySoundRemindEndMSG,3000);
                    }
                    else if(err_id == RESP_ACCESS_TOKEN_INVALID)
                    {
                        vTaskDelay(100);
                        wifi_audio_debug("access token invalid.\n");
                        //GetAccessToken();

                        vTaskDelay(100);
                        download_ret = file_down_load(&err_id);
                    }
                    else if(err_id == RESP_MEDIA_ID_INVALID)
                    {
                        wifi_audio_debug("media id invalid.\n");

                        //SoundRemind(SOUND_XXGQ,1);
                        //xQueueReset(PlaySoundRemindEndMSG);
                        //osMessageRecv(PlaySoundRemindEndMSG,2000);
                    }
                    else if(err_id == RESP_MEDIA_ID_MISSING)
                    {
                        wifi_audio_debug("media id missing.\n");
                        vTaskDelay(200);
                        download_ret = file_down_load(&err_id);
                    }
                    else
                    {
                        wifi_audio_debug("other error...\n");
                    }
                }
            }

            //if download the amr file success, refresh the pt_media_record list
            if((download_ret == FILE_DOWNLOAD_OK)||(download_ret == FILE_DOWNLOAD_NEXT)||
                    ((download_ret == FILE_DOWNLOAD_INVALID)&&((err_id == RESP_MEDIA_ID_INVALID)||(err_id == RESP_MEDIA_ID_MISSING))))
            {
                vTaskDelay(200);
                if(AmrAccessId == 0)
                {
                    if(pt_media_record->newest_number)
                    {
                        pt_media_record->newest_number--;

                        if(pt_media_record->newest_number == 0)
                        {
                            if(pt_media_record->total_number>1)
                            {
                                pt_media_record->old_item = 1;
                                pt_media_record->current_item = (pt_media_record->newest_item-1);
                            }
                            else
                            {
                                pt_media_record->current_item = 0;
                                pt_media_record->old_item = 0;
                            }
                        }
                        else
                        {
                            pt_media_record->current_item++;
                            if(pt_media_record->current_item >= MEDIA_RECORD_NUM)
                            {
                                pt_media_record->current_item = 0;
                            }
                        }
                        //在未读消息时,消息失效后,valid_number和newest_number关联
                        if(download_ret == FILE_DOWNLOAD_INVALID)
                        {
                            pt_media_record->valid_number = pt_media_record->newest_number;
                        }
                    }
                    else
                    {
                        //在处理已读消息时,消息失效后,valid_number和old_item关联
                        if(download_ret == FILE_DOWNLOAD_INVALID)
                        {
                            pt_media_record->valid_number = pt_media_record->old_item-1;
                        }

                        pt_media_record->old_item+=1;
                        if(pt_media_record->old_item <= (pt_media_record->total_number-1))
                        {
                            if(pt_media_record->old_item >= pt_media_record->valid_number)
                            {
                                pt_media_record->old_item=0;
                                pt_media_record->current_item = pt_media_record->newest_item;
                            }
                            else
                            {
                                if(pt_media_record->current_item)
                                {
                                    pt_media_record->current_item -= 1;
                                }
                                else
                                {
                                    pt_media_record->current_item = pt_media_record->total_number-1;
                                }
                            }
                        }
                        else
                        {
                            pt_media_record->old_item=0;
                            pt_media_record->current_item = pt_media_record->newest_item;
                        }
                    }

                    BurnWeixinRecord();

                    //还有未读语音,则继续播放
                    if((pt_media_record->newest_number)&&((download_ret == FILE_DOWNLOAD_OK)
                                                          ||(err_id == RESP_MEDIA_ID_INVALID)))
                    {
                        osMessageSend(PlayWeixinMSG,MSG_START_PLAY_FRIEND_WEIXN,0);
                    }
                    else if(download_ret == FILE_DOWNLOAD_OK)
                    {
                    	/*if(gSys.CurModuleID == MODULE_ID_WIFI_AUDIO)
                    	{
                    		//正常播放已读消息或者所有的未读消息后,自动返回到之前的播放状态
	                    	if((play_stage == WAIT_FOR_WEIXIN))
	                    	{
	                    		if((back2PlayStage != WAIT_URL)&&(back2PlayStage != WAIT_FOR_WEIXIN)&&(back2PlayStage != STAGE_BACKUP_IDLE))
	                    		{
		                    		uint32_t Temp;
		                    		Temp = MSG_PLAY_PAUSE;
			        				xQueueSend(KeyMSGQueue, &Temp, 0);
			        			}
	                    	}

	                    	back2PlayStage = STAGE_BACKUP_IDLE;
	                    }
	                    else if(gSys.CurModuleID == MODULE_ID_PLAYER_SD)
	                    {
                    		//正常播放已读消息或者所有的未读消息后,自动返回到之前的播放状态
	                    	if((DiskPlayStage == DISK_WAIT_FOR_WEIXIN))
	                    	{
			            		if((back2PlayStage != DISK_STOP)&&(back2PlayStage != DISK_READY_WORK_FOR_WEIXIN)
			            			&&(back2PlayStage != STAGE_BACKUP_IDLE)&&(back2PlayStage != DISK_WAIT_FOR_WEIXIN)
			            			&&(back2PlayStage != DISK_PAUSE))
	                    		{
		                    		uint32_t Temp;
		                    		Temp = MSG_PLAY_PAUSE;
			        				xQueueSend(KeyMSGQueue, &Temp, 0);
			        			}
	                    	}
	                    	
	                    	back2PlayStage = STAGE_BACKUP_IDLE;
	                    }
	                    else
	                    {
	                    	back2PlayStage = STAGE_BACKUP_IDLE;
	                    }*/
                    }
                }
            }
            else if(download_ret == FILE_DOWNLOAD_DROPOUT)
            {
                wifi_audio_debug("_file_down_load: drop out!!!\n");
            }
            else
            {
                wifi_audio_debug("_file_down_load: err!!!\n");
            }

            play_weixin_audio=0;
            //goto_lowpower_f();
        }
        else
        {
            if(AmrAccessId_s == 1)
            {
                if(collect_weixin_audio == 0)
                {
                    //play_sdxx();
                }
                AmrAccessId_s = 0;
            }

            if(AmrAccessId == 1)
            {
                /*SetLed3(1);
                vTaskDelay(500);
                SetLed3(0);
                vTaskDelay(500);
                */
            }
            else
            {
                vTaskDelay(200);
            }
        }
    }
}
extern PLAY_RECORD *WifiaudioPlayRecord;
extern VOLUME_RECORD VolumeRecord;
extern uint8_t Volume;
extern uint8_t *DevType;
extern uint8_t *DevUser;
extern struct device_user_st *pdeviceuser;
extern uint8_t burn_dev_user;
/*void GetPlayRecord(void);
void GetVolumeRecord(void);
void GetMediaIdRecord(void);
*/
/*void RestoreVolume(void)
{
    GetVolumeRecord();
    if(VolumeRecord.flag != VOLUME_RECORD_FLAG)
    {
        Volume = VOLUME_INIT;
    }
    else
    {
        if(VolumeRecord.volume > MAX_VOLUME)
        {
            Volume = VOLUME_INIT;
        }
        else
        {
            Volume = VolumeRecord.volume;
        }
    }
    SetVolume(Volume);
}
*/
extern uint8_t ConnectWXFlag;
void SendWeixinAudioTask()
{
    uint8_t *pInFile;
    uint8_t *pOutFile;
    uint32_t n;
    uint32_t FileSize;
    uint32_t i;
    uint32_t TempTick;
    uint32_t  gCycleCnt1,gCycleCnt2;
    uint32_t TempTick1;
    osMessage MSGEvent;
    uint16_t flag;

    while(ConnectWXFlag == 0)
    {
        vTaskDelay(200);
    }

    xQueueReset(CollectAudioMSG);

    while(1)
    {
        MSGEvent = osMessageRecv(CollectAudioMSG, 100);
        if(ConnectWXFlag == 0)
        {
            MSGEvent.value.v = MSG_NONE;
        }
        if((MSGEvent.value.v == MSG_START_GET_FAMILY_AUDIO)||(MSGEvent.value.v == MSG_START_GET_FRIEND_AUDIO))
        {

            if(MSGEvent.value.v == MSG_START_GET_FAMILY_AUDIO)
            {
                flag = 1;
            }
            else
            {
                flag = 2;
            }
            osMessageSend(PlayWeixinMSG,MSG_STOP_PLAY_FRIEND_WEIXIN,0);

            osMessageSend(KeyMSGQueue,MSG_START_WEIXIN,0xffffffff);
            xQueueReset(ReadyForWeixinMSG);
            osMessageRecv(ReadyForWeixinMSG ,0xffffffff);
            collect_weixin_audio = 1;
            SoundRemind(SOUND_DD,1);
            xQueueReset(PlaySoundRemindEndMSG);
            osMessageRecv(PlaySoundRemindEndMSG,1000);
            SetLed4(1);

            AdcVolumeSet(0xFB0, 0xFB0);
            PhubPathSel(ADCIN_TO_PMEM);
            CodecAdcChannelSel(ADC_CH_NONE);
            CodecAdcChannelSel(ADC_CH_MIC_L | ADC_CH_MIC_R);

            CodecDacMuteSet(TRUE, TRUE);
            DacAdcSampleRateSet(8000, 0);
            CodecDacMuteSet(FALSE, FALSE);
            uint32_t Count = 0;

            pOutFile = (uint8_t*)(CFG_SDRAM_BASE+1024*1024);
            memcpy(pOutFile,AMRHeader,6);
            pOutFile =pOutFile + 6;
            TempTick = gSysTick;
            FileSize = 6;
            AdcPmemWriteEn();
            while(1)
            {
                if(AdcPmemPcmRemainLenGet() >= 160)//10ms
                {
                    AdcPcmDataRead(buf,160,1);
                    //TempTick1 = gSysTick;
                    //gCycleCnt1 = *(unsigned long*)0xE0001004;
                    n = Encoder_Interface_Encode(amr, /*MR795*/5, buf, outbuf, 0);
                    //gCycleCnt2 = *(unsigned long*)0xE0001004;
                    //printf("mmmmmmm%d\n",gCycleCnt2-gCycleCnt1);
                    memcpy(pOutFile,outbuf,n);
                    pOutFile = pOutFile + n;
                    FileSize = FileSize + n;
                }
                else
                {
                    vTaskDelay(5);
                }

                MSGEvent = osMessageRecv(CollectAudioMSG,0);

                if(flag == 1)
                {
                    if(MSGEvent.value.v == MSG_STOP_GET_FAMILY_AUDIO)
                    {
                        break;
                    }
                }
                else if(flag == 2)
                {
                    if(MSGEvent.value.v == MSG_STOP_GET_FRIEND_AUDIO)
                    {
                        break;
                    }
                }

                if((gSysTick - TempTick) > 55000)//最大时间为60s
                {
                    break;
                }
            }
            SetLed4(0);
            AdcPmemWriteDis();
            xQueueReset(CollectAudioMSG);

            while(AdcPmemPcmRemainLenGet() >= 160)//10ms
            {
                AdcPcmDataRead(buf,160,1);
                n = Encoder_Interface_Encode(amr, /*MR795*/5, buf, outbuf, 0);
                memcpy(pOutFile,outbuf,n);
                pOutFile = pOutFile + n;
                FileSize = FileSize + n;
            }

            PhubPathSel(PCMFIFO_MIX_DACOUT);
            if((gSysTick - TempTick) < 800)
            {
                SoundRemind(SOUND_XXGD,1);
                xQueueReset(PlaySoundRemindEndMSG);
                osMessageRecv(PlaySoundRemindEndMSG,1000);
            }
            else
            {
                SoundRemind(SOUND_XX,1);
                xQueueReset(PlaySoundRemindEndMSG);
                osMessageRecv(PlaySoundRemindEndMSG,1000);
                if(file_up_load((uint8_t*)(CFG_SDRAM_BASE+1024*1024),FileSize) == 1)
                {
                    memset(wx_read_buffer,0,1024);
                    sprintf((char*)wx_read_buffer,"{\"msg_type\":\"notify\",\"services\":{\"operation_status\":{\"status\":1},\"air_conditioner\":{\"tempe_indoor\":26,\"tempe_outdoor\":31,\"tempe_target\":26,\"fan_speed\":50}},\"data\":\"sendamr#%s#%d\"}",media_id,flag);
                    airkiss_cloud_sendmessage(1, (uint8_t*)wx_read_buffer,strlen(wx_read_buffer));
                }
                else
                {
                    wifi_audio_debug("_file_up_load: Send weixin message fail\n");
                }
            }
            collect_weixin_audio = 0;
            osMessageSend(KeyMSGQueue,MSG_WEIXN_DONE,0);

            if(gSys.CurModuleID == MODULE_ID_WIFI_AUDIO)
        	{
        		//正常播放已读消息或者所有的未读消息后,自动返回到之前的播放状态
            	if((play_stage == WAIT_FOR_WEIXIN))
            	{
            		if((back2PlayStage != WAIT_URL)&&(back2PlayStage != WAIT_FOR_WEIXIN)&&(back2PlayStage != STAGE_BACKUP_IDLE))
            		{
                		uint32_t Temp;
                		Temp = MSG_PLAY_PAUSE;
        				xQueueSend(KeyMSGQueue, &Temp, 0);
        			}
            	}

            	back2PlayStage = STAGE_BACKUP_IDLE;
            }
            else if(gSys.CurModuleID == MODULE_ID_PLAYER_SD)
            {
        		//正常播放已读消息或者所有的未读消息后,自动返回到之前的播放状态
            	if((DiskPlayStage == DISK_WAIT_FOR_WEIXIN))
            	{
            		if((back2PlayStage != DISK_STOP)&&(back2PlayStage != DISK_READY_WORK_FOR_WEIXIN)
            			&&(back2PlayStage != STAGE_BACKUP_IDLE)&&(back2PlayStage != DISK_WAIT_FOR_WEIXIN)
            			&&(back2PlayStage != DISK_PAUSE))
            		{
                		uint32_t Temp;
                		Temp = MSG_PLAY_PAUSE;
        				xQueueSend(KeyMSGQueue, &Temp, 0);
        			}
            	}

            	back2PlayStage = STAGE_BACKUP_IDLE;
            }
        }
    }
}