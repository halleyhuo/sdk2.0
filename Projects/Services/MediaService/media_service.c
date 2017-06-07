/**
 **************************************************************************************
 * @file    media_service.c
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

#include "type.h"
#include "rtos_api.h"
#include "gpio.h"
#include "irqs.h"

#include "app_message.h"
#include "app_config.h"

#include "media_service.h"

#include "gpio.h"
#include "sd_spi.h"

#include "decoder_service.h"

/***************************************************************************************
 *
 * External defines
 *
 */
extern uint8_t *memp_memory;


/***************************************************************************************
 *
 * External defines
 *
 */

 
#define MEDIA_SERVICE_SIZE				1024
#define MEDIA_SERVICE_PRIO				3
	
#define MEDIA_SERVICE_TIMEOUT			10	/* 1 ms */

#define MS_NUM_MESSAGE_QUEUE			10

/***************************************************************************************
 *
 * Internal defines
 *
 */	
	
typedef struct _MediaServiceContext
{
	xTaskHandle 		taskHandle;
	MessageHandle		msgHandle;
	ServiceState		serviceState;
}MediaServiceContext;

/** MEDIA servcie name*/
const char mediaServiceName[]		= "MediaService";


/***************************************************************************************
 *
 * Internal varibles
 *
 */
static MediaServiceContext		mediaServiceCt;


#define FF_FB_STEP                  2000

AUDIO_DISK_PLAYER* gpDiskPlayer = NULL;

/***************************************************************************************
 *
 * Internal functions
 *
 */

static bool IsCardLink(void)
{
	bool TempFlag;
	GpioSpimIoConfig(0xff);

	GpioClrRegBits(CARD_DETECT_PORT_PU, CARD_DETECT_IO);
	GpioClrRegBits(CARD_DETECT_PORT_PD, CARD_DETECT_IO);
	GpioClrRegBits(CARD_DETECT_PORT_OE, CARD_DETECT_IO);
	GpioSetRegBits(CARD_DETECT_PORT_IE, CARD_DETECT_IO);
	
	if(GpioGetReg(CARD_DETECT_PORT_IN) & CARD_DETECT_IO)
	{
		TempFlag = FALSE;
	}
	else
	{
		TempFlag = TRUE;
	}
	
	if(TempFlag)
	{
		GpioSpimIoConfig(0);
	}
	return TempFlag;
}
 
static bool HardwareInit(DEV_ID DevId)
{
	DBG("hardware init start.\n");
	switch(DevId)
	{
#ifdef FUNC_CARD_EN
		case DEV_ID_SD:
			if(!IsCardLink())
			{ 
				DBG("Card is not exist.\n");
				return FALSE;
			}
			FSDeInit(DEV_ID_USB);
            FSDeInit(DEV_ID_SD);
			if(SdCardInit() != NONE_ERR)	
			{
				DBG("Card init err.\n");
				return FALSE;
			}
			if(!FSInit(DEV_ID_SD))
			{
				DBG("fs init err.\n");
				return FALSE;
			}
			return TRUE;
#endif

#ifdef FUNC_USB_EN
		case DEV_ID_USB:
			OTG_SetCurrentPort(UDISK_PORT_NUM);
			if(!IsUDiskLink())
			{
				DBG("UNLINK UDisk\n");
				return FALSE;
			}
			FSDeInit(DEV_ID_SD);
			FSDeInit(DEV_ID_USB);
			if(!OTG_HostInit() == 1)
			{
				DBG("Host Intit Disk Error\n");
				return FALSE;
			}
			if(!FSInit(DEV_ID_USB))
			{
				return FALSE;
			}
			return TRUE;
#endif
		default:
			break;
	}
	return FALSE;
}

//开始播放
//FileHandle: 文件指针
//FileType:   IO_TYPE_FILE--播放U盘/SD卡中的文件，IO_TYPE_MEMORY--播放提示音
//StartTime:  播放的开始时间 
bool DecoderTaskPlayStart(void* FileHandle, uint8_t FileType, uint32_t StartTime)
{
	MessageContext		msgSend;
	MessageHandle		msgHandle;

	DBG("DecoderTaskPlayStart()\n");
	
	/*if(GetDecoderServiceState() != DecoderStateReday)
	{
		return FALSE;
	}*/
	
	msgHandle = GetDecoderServiceMsgHandle();
	msgSend.msgId		= MSG_SERVICE_START;
	msgSend.msgParams	= MSG_PARAM_DECODER_MODE_MEDIA;
	MessageSend(msgHandle, &msgSend);

	msgHandle = GetAudioCoreMessageHandle();
	msgSend.msgId		= MSG_SERVICE_START;
	msgSend.msgParams	= NULL;
	MessageSend(msgHandle, &msgSend);
	return TRUE;
}

//停止播放
void DecoderTaskStop(void)
{	
	DBG("DecoderTaskStop()\n");
/*
//	Mixer_MuteSet(Mixer, gSys.DecMixerNum, TRUE, TRUE);
	WaitMs(300); //和mixer buf大小有关，buf越大延时时间越长
	
	DecoderCtrl.DecoderControlCmd = DECODER_TASK_CTRL_STOP;
	DecoderTaskWaitResp(DECODER_TASK_WAIT_TIMEOUT);	
*/
}

//暂停
void DecoderTaskPause(void)
{	
	DBG("DecoderTaskPause()\n");

/*	if(DecoderCtrl.DecoderTaskState != DECODER_TASK_STATE_PLAY)
	{
		return;
	}

//	Mixer_MuteSet(Mixer, gSys.DecMixerNum, TRUE, TRUE);
	
	WaitMs(20);
	DecoderCtrl.DecoderControlCmd = DECODER_TASK_CTRL_PAUSE;
	DecoderTaskWaitResp(DECODER_TASK_WAIT_TIMEOUT);
*/
}

//由暂停恢复播放
void DecoderTaskResume(void)
{	
	DBG("DecoderTaskResume()\n");
		
/*	if(DecoderCtrl.DecoderTaskState != DECODER_TASK_STATE_PAUSE)
	{
		return;
	}
	
	DecoderCtrl.DecoderControlCmd = DECODER_TASK_CTRL_RESUME;
	DecoderTaskWaitResp(DECODER_TASK_WAIT_TIMEOUT);
//	Mixer_MuteSet(Mixer, gSys.DecMixerNum, FALSE, FALSE);
*/
}


//快进
void DecoderTaskFF(uint32_t StepTime)
{	
	DBG("DecoderTaskFF()\n");
	
/*	if(DecoderCtrl.DecoderTaskState != DECODER_TASK_STATE_PLAY)
	{
		return;
	}

//	Mixer_MuteSet(Mixer, gSys.DecMixerNum, TRUE, TRUE);
	WaitMs(20);

	DecoderCtrl.DecoderControlParam = StepTime;
	DecoderCtrl.DecoderControlCmd = DECODER_TASK_CTRL_FF;
	DecoderTaskWaitResp(DECODER_TASK_WAIT_TIMEOUT);

//	Mixer_MuteSet(Mixer, gSys.DecMixerNum, FALSE, FALSE);
*/
}

//快退
void DecoderTaskFB(uint32_t StepTime)
{	
	DBG("DecoderTaskFB()\n");
	
/*	if(DecoderCtrl.DecoderTaskState != DECODER_TASK_STATE_PLAY)
	{
		return;
	}
//	Mixer_MuteSet(Mixer, gSys.DecMixerNum, TRUE, TRUE);
	WaitMs(20);

	DecoderCtrl.DecoderControlParam = StepTime;
	DecoderCtrl.DecoderControlCmd = DECODER_TASK_CTRL_FB;
	DecoderTaskWaitResp(DECODER_TASK_WAIT_TIMEOUT);

//	Mixer_MuteSet(Mixer, gSys.DecMixerNum, FALSE, FALSE);
*/
}

//指定时间播放
void DecoderTaskSeek(uint32_t Time)
{	
	DBG("DecoderTaskSeek()\n");
	
/*	if(DecoderCtrl.DecoderTaskState != DECODER_TASK_STATE_PLAY)
	{
		return;
	}

	DecoderCtrl.DecoderControlParam = Time;
	DecoderCtrl.DecoderControlCmd = DECODER_TASK_CTRL_SEEK;
	DecoderTaskWaitResp(DECODER_TASK_WAIT_TIMEOUT);
*/
}

//判断一首歌是否播放结束
bool DecoderTaskIsSongEnd(void)
{
//	return (DecoderCtrl.DecoderTaskState == DECODER_TASK_STATE_STOP);	
	return 0;	
}


//获取当前播放时间
uint32_t DecoderTaskGetPlayTime(void)
{
// 	return DecoderCtrl.DecoderPlayTime;
 	return 0;
}

//初始化decoder，并返回当前解码类型
static DecoderType DecoderGetType(void)
{
	uint8_t* ExtFileName = gpDiskPlayer->PlayerFile.ShortName;
	
	//播放提示音
//	if(DecoderCtrl.DecoderFileType == IO_TYPE_MEMORY)
//	{
//		if(RT_SUCCESS != audio_decoder_initialize(audio_decoder, DecoderCtrl.DecoderFileHandle, IO_TYPE_MEMORY, MP3_DECODER))
//		{
//			APP_DBG("mp3（格式错误）Error type: %d\r\n", audio_decoder_get_error_code(audio_decoder));
//			audio_decoder_close(audio_decoder);
//			return UNKOWN_DECODER;
//        }
//		return MP3_DECODER;
//	}

	//播放U盘/SD卡文件
	if(((ExtFileName[8] == 'M') && (ExtFileName[9] == 'P') && (ExtFileName[10] == '2'))
	|| ((ExtFileName[8] == 'M') && (ExtFileName[9] == 'P') && (ExtFileName[10] == '3'))
	|| ((ExtFileName[8] == 'W') && (ExtFileName[9] == 'M') && (ExtFileName[10] == 'V'))
	|| ((ExtFileName[8] == 'W') && (ExtFileName[9] == 'M') && (ExtFileName[10] == 'A'))
	|| ((ExtFileName[8] == 'A') && (ExtFileName[9] == 'S') && (ExtFileName[10] == 'F')))
	{
		return WAV_DECODER;
		/*if(audio_decoder_initialize(audio_decoder, DecoderCtrl.DecoderFileHandle, IO_TYPE_FILE, WAV_DECODER) == (int32_t)RT_SUCCESS)
		{
			audio_decoder_seek(audio_decoder, 0);
			return WAV_DECODER;
		}
            
		if(audio_decoder_initialize(audio_decoder, DecoderCtrl.DecoderFileHandle, IO_TYPE_FILE, WMA_DECODER) != (int32_t)RT_SUCCESS)
		{
//			if(audio_decoder_get_error_code(audio_decoder) != -256)
//			{
//				APP_DBG("wma（格式错误）Error type: %d\n", audio_decoder_get_error_code(audio_decoder));
//				APP_DBG("decoder size = %d\n", audio_decoder->decoder_size);
//				audio_decoder_close(audio_decoder);
//				//audio_decoder = NULL;
//				return UNKOWN_DECODER;
//			}
			if(audio_decoder_initialize(audio_decoder, DecoderCtrl.DecoderFileHandle, IO_TYPE_FILE, MP3_DECODER) != (int32_t)RT_SUCCESS)
			{
				APP_DBG("mp3（格式错误）Error type: %d\n", audio_decoder_get_error_code(audio_decoder));
				audio_decoder_close(audio_decoder);
				//audio_decoder = NULL;
				return UNKOWN_DECODER;      //error found
			}
			return MP3_DECODER;
		}
		return WMA_DECODER;
		*/
	}
	
	if((ExtFileName[8] == 'W') && (ExtFileName[9] == 'A') && (ExtFileName[10] == 'V'))
	{
		APP_DBG("WAV_DECODER\n");
		return WAV_DECODER;
	}

	if((ExtFileName[8] == 'F') && (ExtFileName[9] == 'L') && (ExtFileName[10] == 'A'))
	{
		APP_DBG("FLAC_DECODER\n");
		return FLAC_DECODER;
	}

	if((ExtFileName[8] == 'S') && (ExtFileName[9] == 'B') && (ExtFileName[10] == 'C'))
	{
		return SBC_DECODER;
	}

	if(((ExtFileName[8] == 'A') && (ExtFileName[9] == 'A') && ExtFileName[10] == 'C') 
	|| ((ExtFileName[8] == 'M') && (ExtFileName[9] == 'P') && ExtFileName[10] == '4') 
	|| ((ExtFileName[8] == 'M') && (ExtFileName[9] == '4') && ExtFileName[10] == 'A'))
	{
		return AAC_DECODER;
	}
    
    if(ExtFileName[8] == 'A' && ExtFileName[9] == 'I' && ExtFileName[10] == 'F')
	{
		return AIF_DECODER;
	}
	return UNKOWN_DECODER;
}

// 音源格式是否支持，目前仅检测采样率
static bool IsSupportSourceType(uint32_t sample_rate, uint32_t decoder_type)
{
	bool ret = FALSE;

	switch(sample_rate)
	{
		case 8000:
		case 11025:
		case 12000:
		case 16000:
		case 22050:
		case 24000:
		case 32000:
		case 44100:
		case 48000:
			ret = TRUE;
			break;

		default:
			ret = FALSE;
			break;
	}
	return ret;
}

//歌曲播放初始化
static bool DecoderPlayStart(void)
{	
	//播放初始化
	uint32_t DecoderType;
	APP_DBG("DoPlayer...\n");

/*	DecoderCtrl.TotalDecodedSamples = 0;
	DecoderCtrl.DecoderPlayTime = 0;
	
    DecoderType = DecoderGetType();
	if(DecoderType == UNKOWN_DECODER)
	{	
		return FALSE;
	}
	
	if(DecoderCtrl.DecoderFileType == IO_TYPE_FILE)
	{
		FileSeek(DecoderCtrl.DecoderFileHandle, 0, SEEK_SET);
		if(audio_decoder_initialize(audio_decoder, DecoderCtrl.DecoderFileHandle, IO_TYPE_FILE, DecoderType) != (int32_t)RT_SUCCESS)
		{
			//audio_decoder = NULL;
			APP_DBG("（格式错误）Error Id = %x\n, DecoderType = %d\n", (int32_t)audio_decoder_get_error_code(audio_decoder), DecoderType);
			return FALSE;//error found
		}

		// 判断是否是支持的音源格式
		if(!IsSupportSourceType(audio_decoder->song_info->sampling_rate, DecoderType))
		{
			return FALSE;
		}
	}
	
	APP_DBG("decoder size = %d\n", audio_decoder->decoder_size);
	DBG("Fs = %d, Chl = %d\n", audio_decoder->song_info->sampling_rate, audio_decoder->song_info->num_channels);

    //设置Mixer format
#ifndef FUNC_MIXER_SRC_EN
	AudioSampleRateSet(audio_decoder->song_info->sampling_rate);//设置采样率
	AudioCoreSetSourceFormat(&AudioCore, gSys.DecMixerNum, (audio_decoder->song_info->num_channels == 1) ? MIXER_FORMAT_MONO_1 : MIXER_FORMAT_STEREO);
	#ifdef FUNC_KEY_BEEP_SOUND_EN
	//beep音采样率重新配置
	//BeepInit(2600, audio_decoder->song_info->sampling_rate, 8000, 5, 25, 10);
	//Mixer_ConfigFormat(Mixer, Mixer->SourceNum-1, audio_decoder->song_info->sampling_rate, MIXER_FORMAT_STERO_1);//beep通道，44100采样率，立体声输入
	#endif
#else
	AudioCoreSetSourceFormat(&AudioCore, gSys.DecMixerNum, (audio_decoder->song_info->num_channels == 1) ? MIXER_FORMAT_MONO_1 : MIXER_FORMAT_STEREO);
	SampleRateConvertInit(gSys.DecMixerNum, audio_decoder->song_info->sampling_rate, 44100, audio_decoder->song_info->num_channels);
#endif
	
	if(audio_decoder->bc->io_type != IO_TYPE_MEMORY)
	{
		audio_decoder_seek(audio_decoder, DecoderCtrl.DecoderPlayTime);
	}
*/	
	return TRUE;
}

static void DecoderPlayStop(void)
{
	APP_DBG("end_of_play...\n");

//	DecoderCtrl.DecoderPlayTime = 0;
//	DecoderCtrl.DecoderPlayState = DECODER_START_DECODE;
}




//歌曲解析信息显示
void DisplaySongInfoLog(void)
{
    SongInfo* PlayingSongInfo = audio_decoder_get_song_info();
    uint16_t FileCnt = gpDiskPlayer->PlayerFolder.RecFileCnt;

    APP_DBG("PlayCtrl:DisplaySongInfoLog\n");
    if(PlayingSongInfo == NULL)
    {
        return;
    }

    FileCnt = gpDiskPlayer->PlayerFolder.IncFileCnt;

    APP_DBG("---------Folder Info--------\n");
    APP_DBG("Folder Opened:%d\n", gpDiskPlayer->PlayerFolder.FolderNum);
    APP_DBG("Folder Name:%s\n", gpDiskPlayer->PlayerFolder.ShortName);

    APP_DBG("Folder Sum:%d\n", gpDiskPlayer->PlayerFolder.RecFolderCnt);
    APP_DBG("Folder Includes Files:%d\n", FileCnt);
    APP_DBG("----------------------------\n");

#ifdef FUNC_LRC_EN
    APP_DBG("LRC:%d\n", gpDiskPlayer->IsLrcRunning);
#else
    APP_DBG("LRC:0\n");
#endif
    APP_DBG("----------TAG Info----------\n");

    APP_DBG("CharSet:");
    switch(PlayingSongInfo->char_set)
    {
        case CHAR_SET_ISO_8859_1:
            APP_DBG("CHAR_SET_ISO_8859_1\n");
            break;
        case CHAR_SET_UTF_16:
            APP_DBG("CHAR_SET_UTF_16\n");
            break;
        case CHAR_SET_UTF_8:
            APP_DBG("CHAR_SET_UTF_8\n");
            break;
        default:
            APP_DBG("CHAR_SET_UNKOWN\n");
            break;
    }
    
#ifdef FUNC_STRING_CONVERT_EN
    if(PlayingSongInfo->char_set == CHAR_SET_UTF_8)
    {
        StringConvert(PlayingSongInfo->title,	  MAX_TAG_LEN, PlayingSongInfo->title,	   MAX_TAG_LEN, UTF8_TO_GBK);
        StringConvert(PlayingSongInfo->artist,	  MAX_TAG_LEN, PlayingSongInfo->artist,    MAX_TAG_LEN, UTF8_TO_GBK);
        StringConvert(PlayingSongInfo->album,	  MAX_TAG_LEN, PlayingSongInfo->album,	   MAX_TAG_LEN, UTF8_TO_GBK);
        StringConvert(PlayingSongInfo->comment,   MAX_TAG_LEN, PlayingSongInfo->comment,   MAX_TAG_LEN, UTF8_TO_GBK);
        StringConvert(PlayingSongInfo->genre_str, MAX_TAG_LEN, PlayingSongInfo->genre_str, MAX_TAG_LEN, UTF8_TO_GBK);
    }
    else if(PlayingSongInfo->char_set == CHAR_SET_UTF_16)
    {
        StringConvert(PlayingSongInfo->title,	  MAX_TAG_LEN, PlayingSongInfo->title,	   MAX_TAG_LEN, UNICODE_TO_GBK);
        StringConvert(PlayingSongInfo->artist,	  MAX_TAG_LEN, PlayingSongInfo->artist,    MAX_TAG_LEN, UNICODE_TO_GBK);
        StringConvert(PlayingSongInfo->album,	  MAX_TAG_LEN, PlayingSongInfo->album,	   MAX_TAG_LEN, UNICODE_TO_GBK);
        StringConvert(PlayingSongInfo->comment,   MAX_TAG_LEN, PlayingSongInfo->comment,   MAX_TAG_LEN, UNICODE_TO_GBK);
        StringConvert(PlayingSongInfo->genre_str, MAX_TAG_LEN, PlayingSongInfo->genre_str, MAX_TAG_LEN, UNICODE_TO_GBK);
    }
    else if((PlayingSongInfo->char_set & 0xF0000000) == CHAR_SET_DIVERSE)
    {
        uint32_t type = PlayingSongInfo->char_set & 0xF;
        if(type > 1)  
        {
            StringConvert(PlayingSongInfo->title,	  MAX_TAG_LEN, PlayingSongInfo->title,	   MAX_TAG_LEN, (type - 2) * 2); 
        }
        type = (audio_decoder->song_info->char_set >> 4)  & 0xF;
        if(type > 1)  
        {
            StringConvert(PlayingSongInfo->artist,	  MAX_TAG_LEN, PlayingSongInfo->artist,    MAX_TAG_LEN, (type - 2) * 2);
        }
        type = (audio_decoder->song_info->char_set >> 8)  & 0xF;
        if(type > 1)  
        {
            StringConvert(PlayingSongInfo->album,	  MAX_TAG_LEN, PlayingSongInfo->album,	   MAX_TAG_LEN, (type - 2) * 2);
        }
        type = (audio_decoder->song_info->char_set >> 12) & 0xF;
        if(type > 1)  
        {
            StringConvert(PlayingSongInfo->comment,   MAX_TAG_LEN, PlayingSongInfo->comment,   MAX_TAG_LEN, (type - 2) * 2);
        }
        type = (audio_decoder->song_info->char_set >> 16) & 0xF;
        if(type > 1)  
        {
            StringConvert(PlayingSongInfo->genre_str, MAX_TAG_LEN, PlayingSongInfo->genre_str, MAX_TAG_LEN, (type - 2) * 2);
        }
    }
#endif
    
    APP_DBG("title: %s\n", PlayingSongInfo->title);
    APP_DBG("artist: %s\n", PlayingSongInfo->artist);
    APP_DBG("Album: %s\n", PlayingSongInfo->album);
    APP_DBG("comment: %s\n", PlayingSongInfo->comment);
    APP_DBG("genre: %d %s\n", PlayingSongInfo->genre, PlayingSongInfo->genre_str);
    APP_DBG("year: %s\n", PlayingSongInfo->year);
    
    APP_DBG("\n");
    APP_DBG("----------------------------\n");
    APP_DBG("**********Song Info*********\n");
    APP_DBG("SongType:");
    switch(PlayingSongInfo->stream_type)
    {
        case STREAM_TYPE_MP2:
            APP_DBG("MP2");
            break;
        case STREAM_TYPE_MP3:
            APP_DBG("MP3");
            break;
        case STREAM_TYPE_WMA:
            APP_DBG("WMA");
            break;
        case STREAM_TYPE_SBC:
            APP_DBG("SBC");
            break;
        case STREAM_TYPE_PCM:
            APP_DBG("PCM");
            break;
        case STREAM_TYPE_ADPCM:
            APP_DBG("ADPCM");
            break;
        case STREAM_TYPE_FLAC:
            APP_DBG("FLAC");
            break;
        case STREAM_TYPE_AAC:
            APP_DBG("AAC");
            break;
        default:
            APP_DBG("UNKNOWN");
            break;
    }
    APP_DBG("\n");
    APP_DBG("Chl Num:%d\n", PlayingSongInfo->num_channels);
    APP_DBG("SampleRate:%d\n", PlayingSongInfo->sampling_rate);
    APP_DBG("BitRate:%d\n", PlayingSongInfo->bitrate);
    APP_DBG("File Size:%d\n", PlayingSongInfo->file_size);
    APP_DBG("TotalPlayTime:%dms\n", PlayingSongInfo->duration);
    APP_DBG("CurPlayTime:%dms\n", gpDiskPlayer->CurPlayTime);
    APP_DBG("IsVBR:%d\n", PlayingSongInfo->vbr_flag);
    APP_DBG("MpegVer:");
    switch(audio_decoder_get_mpeg_version())
    {
        case MPEG_VER2d5:
            APP_DBG("MPEG_2_5");
            break;
        case MPEG_VER1:
            APP_DBG("MPEG_1");
            break;
        case MPEG_VER2:
            APP_DBG("MPEG_2");
            break;
        default:
            APP_DBG("MPEG_UNKNOWN");
            break;
    }
    APP_DBG("\n");
    APP_DBG("Id3Ver:%d\n", audio_decoder_get_id3_version());

    APP_DBG("**************************\n");   
}

//打开播放文件
bool AudioPlayerOpenSongFile(void)
{
    if(!FileOpenByNum(&gpDiskPlayer->PlayerFile, NULL, gpDiskPlayer->CurFileIndex))
    {
        DBG(("FileOpenByNum() error!\n"));
        return FALSE;
    }
    
    gpDiskPlayer->CurFolderIndex = GetValidFolderNum(gpDiskPlayer->PlayerFile.FsContext, gpDiskPlayer->PlayerFile.FolderNum);
    if(!FolderOpenByValidNum(&gpDiskPlayer->PlayerFolder, NULL, gpDiskPlayer->CurFolderIndex))
    {
        APP_DBG("Folder open fail!\n");
        return FALSE;
    }
    DBG("%s\n", gpDiskPlayer->PlayerFile.ShortName);
    
    //DisplaySongInfoLog();
    return TRUE;
}

//关闭播放文件
void AudioPlayerCloseSongFile(void)
{
    FileClose(&gpDiskPlayer->PlayerFile);
}

//打开下一首歌曲并播放
bool AudioPlayerNextSong(void)
{
    APP_DBG("PlayCtrl:AudioPlayerNextSong\n");
	gpDiskPlayer->CurPlayMode = PLAY_MODE_REPEAT_ALL;
    switch(gpDiskPlayer->CurPlayMode)
    {
        case PLAY_MODE_RANDOM_ALL:
            //gPlayContrl->CurFileIndex = (uint16_t)GetRandomNum(((uint16_t)osKernelSysTick()), gPlayContrl->TotalFileNumInDisk);
            break;
        case PLAY_MODE_RANDOM_FOLDER:
            //gPlayContrl->CurFileIndex = (uint16_t)GetRandomNum(((uint16_t)osKernelSysTick()), gPlayContrl->FolderHandle.IncFileCnt);
            break;
        case PLAY_MODE_REPEAT_FOLDER:
            gpDiskPlayer->CurFileIndex++;
            if(gpDiskPlayer->CurFileIndex - gpDiskPlayer->PlayerFolder.StartFileNum > gpDiskPlayer->PlayerFolder.IncFileCnt)
            {
                gpDiskPlayer->CurFileIndex = gpDiskPlayer->PlayerFolder.StartFileNum + 1;
            }
            break;
        case PLAY_MODE_REPEAT_ALL:
        case PLAY_MODE_PREVIEW_PLAY:
            gpDiskPlayer->CurFileIndex++;
//#ifndef FUNC_PLAY_RECORD_FOLDER_EN
//				if(gPlayContrl->CurFileIndex >= gPlayContrl->RecFileStartId 
//				&& gPlayContrl->CurFileIndex <= gPlayContrl->RecFileEndId)
//				{
//					gPlayContrl->CurFileIndex = gPlayContrl->RecFileEndId + 1;
//				}
//#endif
            if(gpDiskPlayer->CurFileIndex > gpDiskPlayer->TotalFileSumInDisk)
            {
                gpDiskPlayer->CurFileIndex = 1;
            }
            break;
            
        case PLAY_MODE_REPEAT_ONE:
        default:
            break;
    }
    if(!AudioPlayerOpenSongFile())
    {
        //return FALSE;//发送下一首歌的MSG
    }
    SetPlayState(PLAYER_STATE_PLAYING);
    DecoderTaskPlayStart(&gpDiskPlayer->PlayerFile, IO_TYPE_FILE, 0);
    DisplaySongInfoLog();
	return TRUE;
}

bool AudioPlayerPreSong(void)
{				
	APP_DBG("PlayCtrl:AudioPlayerPreSong\n");

    switch(gpDiskPlayer->CurPlayMode)
    {
        case PLAY_MODE_RANDOM_ALL:
            //gPlayContrl->CurFileIndex = (uint16_t)GetRandomNum(((uint16_t)osKernelSysTick()), gPlayContrl->TotalFileNumInDisk);
            break;
        case PLAY_MODE_RANDOM_FOLDER:
            // 根据时钟或某个时刻变化的值生成随机数
            //gPlayContrl->CurFileIndex = (uint16_t)GetRandomNum(((uint16_t)osKernelSysTick()), gPlayContrl->FolderHandle.IncFileCnt);
            break;
        case PLAY_MODE_REPEAT_FOLDER:                        
            gpDiskPlayer->CurFileIndex--;
            if(gpDiskPlayer->CurFileIndex - gpDiskPlayer->PlayerFolder.StartFileNum < 1)
            {
                gpDiskPlayer->CurFileIndex = gpDiskPlayer->PlayerFolder.StartFileNum + gpDiskPlayer->PlayerFolder.IncFileCnt;
            }
            break;
        case PLAY_MODE_REPEAT_ALL:
        case PLAY_MODE_PREVIEW_PLAY:
            gpDiskPlayer->CurFileIndex--;
            if(gpDiskPlayer->CurFileIndex < 1)
            {
                gpDiskPlayer->CurFileIndex = gpDiskPlayer->TotalFileSumInDisk;
            }			
            break;
        case PLAY_MODE_REPEAT_ONE:
        default:
            break;
    }	
    if(!AudioPlayerOpenSongFile())
    {
        return FALSE;
    }
    SetPlayState(PLAYER_STATE_PLAYING);
    DecoderTaskPlayStart(&gpDiskPlayer->PlayerFile, IO_TYPE_FILE, 0);
    DisplaySongInfoLog();
	return TRUE;
}

//播放下一个文件夹歌曲
bool AudioPlayerNextFolder(void)
{
	APP_DBG("PlayCtrl:AudioPlayerNextFolder\n");    
	gpDiskPlayer->CurFolderIndex++;
	if(gpDiskPlayer->CurFolderIndex > gpDiskPlayer->ValidFolderSumInDisk)
	{
		gpDiskPlayer->CurFolderIndex = 1;
	}
	
	if(!FolderOpenByValidNum(&gpDiskPlayer->PlayerFolder, NULL, gpDiskPlayer->CurFolderIndex))
	{
		APP_DBG("Folder open fail!\n");
		//return FALSE;
        //发送一条MSG Next folder?
	}

    switch(gpDiskPlayer->CurPlayMode)
    {
        case PLAY_MODE_RANDOM_ALL:
            //gPlayContrl->CurFileIndex = (uint16_t)GetRandomNum(((uint16_t)osKernelSysTick()), gPlayContrl->TotalFileNumInDisk);//在当前Index + gPlayContrl->FolderHandle.IncFileCnt
            break;
        case PLAY_MODE_RANDOM_FOLDER:
            // 根据时钟或某个时刻变化的值生成随机数
            //gPlayContrl->CurFileIndex = (uint16_t)GetRandomNum(((uint16_t)osKernelSysTick()), gPlayContrl->FolderHandle.IncFileCnt);
            break;
        case PLAY_MODE_REPEAT_FOLDER:
        case PLAY_MODE_REPEAT_ALL:
        case PLAY_MODE_PREVIEW_PLAY:
            gpDiskPlayer->CurFileIndex =  gpDiskPlayer->PlayerFolder.StartFileNum + 1;
            APP_DBG("gPlayContrl->CurFileIndex:%d\n", gpDiskPlayer->CurFileIndex);        
            break;
        case PLAY_MODE_REPEAT_ONE:
        default:
            break;
    }	
    
	APP_DBG("Play Folder:%s\n", gpDiskPlayer->PlayerFolder.ShortName);
	if(!AudioPlayerOpenSongFile())
	{
		//return FALSE;
        //发送MSG next song
	}
    
    SetPlayState(PLAYER_STATE_PLAYING);
    DecoderTaskPlayStart(&gpDiskPlayer->PlayerFile, IO_TYPE_FILE, 0);
    DisplaySongInfoLog();
    return TRUE;
}

//播放上一个文件夹歌曲
bool AudioPlayerPreFolder(void)
{
	APP_DBG("PlayCtrl:AudioPlayerPreFolder\n");
	gpDiskPlayer->CurFolderIndex--;
	if(gpDiskPlayer->CurFolderIndex < 1)
	{
		gpDiskPlayer->CurFolderIndex = gpDiskPlayer->ValidFolderSumInDisk;
	}
	
	if(!FolderOpenByValidNum(&gpDiskPlayer->PlayerFolder, NULL, gpDiskPlayer->CurFolderIndex))
	{
		APP_DBG("Folder open fail!\n");
		//return FALSE;
        //发送 pre folder
	}

    switch(gpDiskPlayer->CurPlayMode)
    {
        case PLAY_MODE_RANDOM_ALL:
            //gPlayContrl->CurFileIndex = (uint16_t)GetRandomNum(((uint16_t)osKernelSysTick()), gPlayContrl->TotalFileNumInDisk);//在当前Index + gPlayContrl->FolderHandle.IncFileCnt
            break;
        case PLAY_MODE_RANDOM_FOLDER:
            // 根据时钟或某个时刻变化的值生成随机数
            //gPlayContrl->CurFileIndex = (uint16_t)GetRandomNum(((uint16_t)osKernelSysTick()), gPlayContrl->FolderHandle.IncFileCnt);
            break;
        case PLAY_MODE_REPEAT_FOLDER:
        case PLAY_MODE_REPEAT_ALL:
        case PLAY_MODE_PREVIEW_PLAY:
            gpDiskPlayer->CurFileIndex =  gpDiskPlayer->PlayerFolder.StartFileNum + 1;
            APP_DBG("gPlayContrl->CurFileIndex:%d\n", gpDiskPlayer->CurFileIndex);        
            break;
        case PLAY_MODE_REPEAT_ONE:
        default:
            break;
    }	
    
	APP_DBG("Play Folder:%s\n", gpDiskPlayer->PlayerFolder.ShortName);
	if(!AudioPlayerOpenSongFile())
	{
		//return FALSE;
        //发送 next song
	}
    
    SetPlayState(PLAYER_STATE_PLAYING);
    DecoderTaskPlayStart(&gpDiskPlayer->PlayerFile, IO_TYPE_FILE, 0); 
    DisplaySongInfoLog();
    return TRUE;
}

//播放&暂停
void AudioPlayerPlayPause(void)
{
    if(GetPlayState() == PLAYER_STATE_PLAYING)
    {
        DecoderTaskPause();
        SetPlayState(PLAYER_STATE_PAUSE);
	}
	else if(GetPlayState() == PLAYER_STATE_IDLE)
	{
	    if(!AudioPlayerOpenSongFile())
        {
            //MSG next song
        }
	    SetPlayState(PLAYER_STATE_PLAYING);
        DecoderTaskPlayStart(&gpDiskPlayer->PlayerFile, IO_TYPE_FILE, 0);
	}
	else
	{
	    DecoderTaskResume();
	    SetPlayState(PLAYER_STATE_PLAYING);
	}
}

//停止播放
void AudioPlayerStop(void)
{
	APP_DBG("PlayCtrl:AudioPlayerStop\n");	
//	gPlayContrl->FFAndFBCnt = 0;
//	gPlayContrl->CurSongTitlePtr = NULL;
//	gPlayContrl->RepeatAB.RepeatFlag = REPEAT_CLOSED;
//	gPlayContrl->IsPlayerBeStop = TRUE;   

    DecoderTaskStop();
    //AudioPlayerCloseSongFile();

	// 播放时间清零
	gpDiskPlayer->CurPlayTime = 0;
	SetPlayState(PLAYER_STATE_IDLE);
}

bool AudioPlayerInitialize(int32_t FileIndex, uint32_t FolderIndex)
{
    bool IsFileOpenSuccese = FALSE;
    DEV_ID NewDevId;
    //1、设备初始化
    //2、文件系统初始化
    //3、查找到文件进行decoder初始化

    //NewDevId = (gSys.CurModuleID == MODULE_ID_PLAYER_USB ? DEV_ID_USB : DEV_ID_SD);
    //if(!HardwareInit(NewDevId))//配置选择U盘或sd卡 默认为SD卡
    if(!HardwareInit(DEV_ID_SD))//配置选择U盘或sd卡 默认为SD卡
    {
        APP_DBG("Hardware initialize error\n");
        return FALSE;
    }
    APP_DBG("Hardware initialize success.\n");
    
    //默认使用全盘播放第一个文件
    gpDiskPlayer->CurFolderIndex = 1; // 根目录
    gpDiskPlayer->CurFileIndex = 1;

    // 打开播放文件夹，默认全盘播放
    if(!FolderOpenByNum(&gpDiskPlayer->PlayerFolder, NULL, gpDiskPlayer->CurFolderIndex) 
    || gpDiskPlayer->PlayerFolder.RecFileCnt == 0)
    {
        APP_DBG("Folder open fail, Or no song founded\n");
        return FALSE;
    }
    
    gpDiskPlayer->TotalFileSumInDisk = gpDiskPlayer->PlayerFolder.RecFileCnt;
    gpDiskPlayer->ValidFolderSumInDisk = gpDiskPlayer->PlayerFolder.FsContext->gFsInfo.ValidFolderSum;

//    //if(gPlayContrl->PlayFolderFlag == FALSE)
//    {
//        FOLDER   FolderHandle;
//        FAT_FILE FileHandle;
//        memset(&FolderHandle, 0, sizeof(FolderHandle));
//        if(FolderOpenByName(&FolderHandle, &gPlayContrl->FolderHandle, "record")
//        && FileOpenByNum(&FileHandle, &FolderHandle, 1))
//        {
////            gPlayContrl->RecFileStartId = FileHandle.FileNumInDisk;
////            gPlayContrl->RecFileEndId   = gPlayContrl->RecFileStartId + FolderHandle.RecFileCnt;
////            gPlayContrl->RecFolderId    = FolderHandle.FolderNum;
//            FileClose(&FileHandle);
//        }
////        if(FolderHandle.RecFileCnt == gPlayContrl->FolderHandle.RecFileCnt)
////        {
////            APP_DBG("only record folder!\n");
////            return FALSE;
////        }
//    }
            
    //if(!FileOpenByNum(&gPlayContrl.PlayerFile, NULL, gPlayContrl.FileNum))
//    if(!FileOpenByNum(&gPlayContrl->PlayerFile, NULL, 1))
//	{
//		DBG(("FileOpenByNum() error!\n"));
//		return FALSE;
//	}

    // 文件夹播放，使用相对路径
    IsFileOpenSuccese = FileOpenByNum(&gpDiskPlayer->PlayerFile, NULL, (uint16_t)(gpDiskPlayer->CurFileIndex + gpDiskPlayer->PlayerFolder.StartFileNum));
    if(IsFileOpenSuccese == TRUE)
    {
        gpDiskPlayer->CurFolderIndex = GetValidFolderNum(gpDiskPlayer->PlayerFile.FsContext, gpDiskPlayer->PlayerFile.FolderNum);
        gpDiskPlayer->CurFileIndex   = gpDiskPlayer->PlayerFile.FileNumInFolder;
        //FileClose(&gPlayContrl->PlayerFile);
    }

    if(!FolderOpenByValidNum(&gpDiskPlayer->PlayerFolder, NULL, gpDiskPlayer->CurFolderIndex))
    {
        APP_DBG("Folder open fail!\n");
        return FALSE;
    }
    
    APP_DBG("%s\n", gpDiskPlayer->PlayerFile.ShortName);
    SetPlayState(PLAYER_STATE_PLAYING);
	DecoderTaskPlayStart(&gpDiskPlayer->PlayerFile, IO_TYPE_FILE, 0);
    DisplaySongInfoLog();
    return TRUE;
}

//void AudioPlayerDeinitialize(void)
//{
//    osPortFree(gpDiskPlayer);
//    gpDiskPlayer = NULL;
//}

void AudioPlayerPreviewPlay(void)
{
//    if(GetPlayState() == PLAYER_STATE_PLAYING)
//    {
//        // 检查预览模式是否预览超时
//        if(PLAY_MODE_PREVIEW_PLAY == gpDiskPlayer->CurPlayMode && gpDiskPlayer->CurPlayTime >= 8000)
//        {
//            MsgSend(MSG_NEXT_SONG);
//        } 
//    }
}

//更新歌曲播放时间
void AudioPlayerTimeUpdate(void)
{
    if((GetPlayState() == PLAYER_STATE_PLAYING)
    || (GetPlayState() == PLAYER_STATE_FF)
    || (GetPlayState() == PLAYER_STATE_FB))
	{
//		gpDiskPlayer->CurPlayTime = DecoderTaskGetPlayTime();//更新播放时间
        if((gpDiskPlayer->CurPlayTime / 1000 - gpDiskPlayer->LastPlayTime / 1000 >= 1))
		{
/*			if(gSys.CurModuleID == MODULE_ID_PLAYER_USB)
            {
                APP_DBG("USB ");
            }
            else if(gSys.CurModuleID == MODULE_ID_PLAYER_SD)
            {
                APP_DBG("SD ");
            }*/
            if((gpDiskPlayer->CurPlayMode == PLAY_MODE_RANDOM_FOLDER)
            || (gpDiskPlayer->CurPlayMode == PLAY_MODE_REPEAT_FOLDER))
            {
                APP_DBG("F(%d, %d/%d) ", 
                    gpDiskPlayer->CurFolderIndex, 
                    gpDiskPlayer->CurFileIndex - gpDiskPlayer->PlayerFolder.StartFileNum, 
                    gpDiskPlayer->PlayerFolder.IncFileCnt);
            }
            else
            {
                APP_DBG("D(%d, %d/%d) ", 
                    gpDiskPlayer->CurFolderIndex, 
                    gpDiskPlayer->CurFileIndex, 
                    gpDiskPlayer->PlayerFile.FsContext->gFsInfo.FileSum);
            }
            
            APP_DBG("%-.8s.%-.3s %02d:%02d ", 
                    &gpDiskPlayer->PlayerFile.ShortName[0],
                    &gpDiskPlayer->PlayerFile.ShortName[8],
                    (gpDiskPlayer->CurPlayTime / 1000) / 60,
                    (gpDiskPlayer->CurPlayTime / 1000) % 60);
            
            switch(gpDiskPlayer->CurPlayMode)
            {
                case PLAY_MODE_REPEAT_ONE:
                    APP_DBG("ONE ");
                    break;
                case PLAY_MODE_REPEAT_ALL:
                    APP_DBG("ALL ");
                    break;
                case PLAY_MODE_REPEAT_FOLDER:
                    APP_DBG("RP_FOLDER ");
                    break;
                case PLAY_MODE_RANDOM_FOLDER:
                    APP_DBG("RDM_FOLDER ");
                    break;
                case PLAY_MODE_RANDOM_ALL:
                    APP_DBG("RDM_ALL ");
                    break;
                case PLAY_MODE_PREVIEW_PLAY:
                    APP_DBG("PREVIRW ");
                    break;
                default:
                    break;
            }

            APP_DBG("\n");
            gpDiskPlayer->LastPlayTime = gpDiskPlayer->CurPlayTime;
		}
	}
}

void AudioPlayerRepeatAB(void)
{
    if(GetPlayState() == PLAYER_STATE_PLAYING)
	{
		if(gpDiskPlayer->RepeatAB.RepeatFlag == REPEAT_OPENED 
        && gpDiskPlayer->CurPlayTime >= (gpDiskPlayer->RepeatAB.StartTime + gpDiskPlayer->RepeatAB.Times))
		{
			if(gpDiskPlayer->RepeatAB.LoopCount == 0)
			{
				APP_DBG("Repeat Mode Over\n");
				gpDiskPlayer->RepeatAB.RepeatFlag = REPEAT_CLOSED;
			}
			else
			{
				DecoderTaskFB(gpDiskPlayer->RepeatAB.Times);
				gpDiskPlayer->RepeatAB.LoopCount--;
				APP_DBG("Repeat Mode Loop %d\n", gpDiskPlayer->RepeatAB.LoopCount);
			}
        } 
    }
}

#ifdef FUNC_LRC_EN
void AudioPlayerDispLrc(void)
{
    if((GetPlayState() == PLAYER_STATE_PLAYING)
    && (gPlayContrl->IsLrcRunning))
    {
        PlayerParseLrc();
    }
}
#endif // FUNC_LRC_EN

void AudioPlayerFastForward(void)
{
	APP_DBG("PlayCtrl:AudioPlayerFastForward\n");
//#ifdef FUNC_FFFB_END_WITHOUT_AUTO_SWITCH
//	IsFFFBEndAutoSwitch = FALSE;//快进快退到文件头/尾是否自动切歌
//#endif
	
	if(GetPlayState() < PLAYER_STATE_PLAYING)	// 停止状态下，禁止快进、快退
	{
		return;
	}
    DecoderTaskFF(FF_FB_STEP);	
    SetPlayState(PLAYER_STATE_FF);
}

void AudioPlayerFastBackward(void)
{
	APP_DBG("PlayCtrl:AudioPlayerFastBackward\n");

//#ifdef FUNC_FFFB_END_WITHOUT_AUTO_SWITCH
//	IsFFFBEndAutoSwitch = FALSE;//快进快退到文件头/尾是否自动切歌
//#endif
	
	if(GetPlayState() < PLAYER_STATE_PLAYING)	// 停止状态下，禁止快进、快退
	{
		return;
	}
    DecoderTaskFB(FF_FB_STEP);
    SetPlayState(PLAYER_STATE_FB);
}


void AudioPlayerFFFBEnd(void)
{
	APP_DBG("PlayCtrl:AudioPlayerFFFBEnd\n");
//#ifdef FUNC_FFFB_END_WITHOUT_AUTO_SWITCH
//	IsFFFBEndAutoSwitch = TRUE;//快进快退到文件头/尾是否自动切歌
//#endif

    DecoderTaskResume();
	SetPlayState(PLAYER_STATE_PLAYING);
//#ifdef FUNC_LRC_EN
//	gPlayContrl->LrcRow.StartTime = 0;
//	gPlayContrl->LrcRow.Duration = 0;
//#endif
}

void SetPlayState(uint8_t state)
{
	if(gpDiskPlayer != NULL)
	{
		if(gpDiskPlayer->CurPlayState != state)
		{
			APP_DBG("PlayCtrl:SetPlayState %d\n", state);
			gpDiskPlayer->CurPlayState = state;
		}
	}
}

uint8_t GetPlayState(void)
{
	if(gpDiskPlayer != NULL)
	{
		return gpDiskPlayer->CurPlayState;
	}
	else
	{
		return PLAYER_STATE_IDLE;
	}
}





static void MediaPlayerInit(void)
{
	if(gpDiskPlayer == NULL)
	{
		gpDiskPlayer = pvPortMalloc(sizeof(AUDIO_DISK_PLAYER));
	}
	
	memset(gpDiskPlayer, 0, sizeof(AUDIO_DISK_PLAYER));
}

static void MediaPlayerDeinit(void)
{
	if(gpDiskPlayer != NULL)
	{
		vPortFree(gpDiskPlayer);
		gpDiskPlayer = NULL;
	}
}


static void MediaServiceEntrance(void * param)
{
	MessageContext		msgRecv;
	MessageContext		msgSend;
	MessageHandle		mainHandle;

	/* register message handle */
	mediaServiceCt.msgHandle = MessageRegister(MS_NUM_MESSAGE_QUEUE);

	mediaServiceCt.serviceState = ServiceStateReady;

	/* Send message to main app */
	mainHandle = GetMainMessageHandle();
	msgSend.msgId		= MSG_SERVICE_CREATED;
	msgSend.msgParams	= MSG_PARAM_MEDIA_SERVICE;
	MessageSend(mainHandle, &msgSend);

	while(1)
	{
		MessageRecv(mediaServiceCt.msgHandle, &msgRecv, MEDIA_SERVICE_TIMEOUT);
		switch(msgRecv.msgId)
		{
			case MSG_SERVICE_START:
				if(mediaServiceCt.serviceState == ServiceStateReady)
				{
					mediaServiceCt.serviceState = ServiceStateRunning;
					msgSend.msgId		= MSG_SERVICE_STARTED;
					msgSend.msgParams	= MSG_PARAM_MEDIA_SERVICE;
					MessageSend(mainHandle, &msgSend);
					DBG("Media service start\n");

					/* media audio play start */
					AudioPlayerInitialize(1,1);
				}
				break;
			case MSG_SERVICE_STOP:
				if(mediaServiceCt.serviceState == ServiceStateRunning)
				{
					mediaServiceCt.serviceState = ServiceStateReady;
					msgSend.msgId		= MSG_SERVICE_STOPPED;
					msgSend.msgParams	= MSG_PARAM_MEDIA_SERVICE;
					MessageSend(mainHandle, &msgSend);
				}
				break;

			case MSG_DECODER_EVENT:
				{
					switch(msgRecv.msgParams)
					{
						case MSG_PARAM_DECODER_ERR:
							{
								AudioPlayerCloseSongFile();
								
								MessageContext		msgSend;
								MessageHandle		mainHandle;

								mainHandle = GetDecoderServiceMsgHandle();
								msgSend.msgId		= MSG_SERVICE_STOP;
								msgSend.msgParams	= NULL;
								MessageSend(mainHandle, &msgSend);
								//vTaskDelay(500);

								mainHandle = GetAudioCoreMessageHandle();
								MessageSend(mainHandle, &msgSend);
								vTaskDelay(1000);
								
								AudioPlayerNextSong();
								
								/* Send message to main app */
								mainHandle = GetMediaMessageHandle();
								msgSend.msgId		= MSG_SERVICE_START;
								msgSend.msgParams	= NULL;
								MessageSend(mainHandle, &msgSend);
							}
							break;

						default:
							break;
					}
				}
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
	
	
MessageHandle GetMediaMessageHandle(void)
{
	return mediaServiceCt.msgHandle;
}

ServiceState GetMediaServiceState(void)
{
	return mediaServiceCt.serviceState;
}



/**
 * @brief
 *		Create media service.
 * @param
 * 	 
 * @return  
 */
int32_t MediaServiceCreate(void)
{
	MediaPlayerInit();
	xTaskCreate(MediaServiceEntrance, mediaServiceName, MEDIA_SERVICE_SIZE, NULL, MEDIA_SERVICE_PRIO, &mediaServiceCt.taskHandle);
	return 0;
}

/**
 * @brief
 *		Start media service.
 * @param
 * 	 
 * @return  
 */
void MediaServiceStart(void)
{
	MessageContext		msgSend;

	msgSend.msgId		= MSG_SERVICE_START;
	msgSend.msgParams	= NULL;
	MessageSend(mediaServiceCt.msgHandle, &msgSend);
}

/**
 * @brief
 *		Stop media service.
 * @param
 * 	 
 * @return  
 */
void MediaServiceStop(void)
{
	MessageContext		msgSend;

	msgSend.msgId		= MSG_SERVICE_STOP;
	msgSend.msgParams	= NULL;
	MessageSend(mediaServiceCt.msgHandle, &msgSend);
}


/**
 * @brief
 *		kill media service
 * @param
 * 
 * @return  
 */
void MediaServiceKill(void)
{
	MediaPlayerDeinit();
	
	vTaskDelete(mediaServiceCt.taskHandle);
}


void* GetPtMediaFile(void)
{
	return (void *)&gpDiskPlayer->PlayerFile;
}

DecoderType GetMediaDecoderType(void)
{
	return DecoderGetType();
}

