/*
 * sys_app.h
 *
 *  Created on: Aug 30, 2016
 *      Author: peter
 */

#ifndef SYS_APP_H_
#define SYS_APP_H_
#include "type.h"

typedef struct _PLAY_RECORD {
	//最新播放位置
	uint32_t playFlag;
	uint32_t playStage;
	uint32_t playPosition;
	uint8_t urlPrev[512];
	uint8_t urlCur[512];
	uint8_t urlNext[512];
	uint8_t listId[10];
	uint8_t listSize[10];
	uint16_t listSongIndex;
	
	//收藏歌曲信息
	uint32_t collectFlag;
	uint8_t collectUrlPrev[512];
	uint8_t collectUrlCur[512];
	uint8_t collectUrlNext[512];
	uint8_t collectListId[10];
	uint8_t collectListSize[10];
	uint16_t collectListSongIndex;
} PLAY_RECORD;

//URL list
typedef struct _PLAY_LIST{
	uint8_t		playUrlPrev[512];
	uint8_t		playUrlCur[512];
	uint8_t		playUrlNext[512];
	uint8_t		playUrl[512];
	uint16_t	playListId;
	uint16_t	playListSize;
	uint16_t	playSongIndex;
}PLAY_LIST;

struct device_user_st 
{
	uint32_t flag;
	uint8_t devuser[48];
	uint32_t crc;
};

#define DEVICE_USER_ADDR 0x1FC000

typedef struct _VOLUME_RECORD {
	uint32_t flag;
    uint8_t volume;
} VOLUME_RECORD;


/*
 * media player infor
 */
#define PLAYER_DISK_BP_CNT 3

typedef struct _BP_PLAY_DISK_INFO_
{
	uint32_t FileAddr; 		// 文件扇区号
	uint16_t PlayTime; 		// 播放时间
	uint8_t  CRC8;     		// 文件名校验码
	uint8_t  FolderEnFlag; 	//文件夹使能标志
} BP_PLAY_DISK_INFO;

typedef struct _CARD_PLAY_RECORD {
	uint32_t flag;
	// 播放盘信息
	BP_PLAY_DISK_INFO PlayDiskInfo[PLAYER_DISK_BP_CNT];
} CARD_PLAY_RECORD;


/*
 * wx speech infor
 */
#define SPEECH_LIST_TOTAL_NUM 	200	//最大列表长度
#define SPEECH_LIST_OLD_NUM		20	//循环播放数目
#define SPEECH_ID_ITEM_LEN		64	//每个media id长度

struct  speech_id_st {
    uint8_t speech_id[SPEECH_ID_ITEM_LEN];
};

typedef struct _WX_SPEECH_ID_RECORD {
	struct  speech_id_st item[SPEECH_LIST_TOTAL_NUM];
}WX_SPEECH_ID_RECORD;

typedef struct _WX_SPEECH_RECORD {
    uint32_t total_number;//消息总数
    uint32_t current_item;//当前消息位置
    uint32_t old_item;//已读信息位置
	uint32_t newest_item;//最后1条新消息位置
	uint32_t newest_number;//新消息数目
	uint32_t valid_number;//有效消息数目 max=MEDIA_OLD_NUM
	uint32_t flag;
}WX_SPEECH_RECORD;



//extern media_record_st *pt_media_record;
//extern media_id_record_st *pt_media_id_record;
extern uint8_t zj_id_s[10];
//extern uint8_t zj_size_s[10];
//extern SYS_INFO gSys;

uint32_t GetNextModeId(uint32_t CurModeId);
void ExitCurrentMode(uint32_t Mode);
void SwitchToNextAppMode(uint32_t Mode);
uint32_t SelectDefaultAppMode(void);
int32_t AdcKeyInit(void);
uint16_t AdcKeyScan(void);
extern int16_t SmartlinkStatus;
void DetectPowerOff(void);
void erase_linknet_record(void);
extern uint8_t connect_weixin_done;
extern uint8_t enable_wifi_lowpower;

enum
{
	UPGRADE_NULL = 0,		//无升级版本
	UPGRADE_OPTION,			//可选升级版本
	UPGRADE_FORCE,			//强制升级版本
	UPGRADE_VERSION			//升级软件
};

void goto_lowpower(void);
uint8_t get_wifi_power_state(void);

#define TOTAL_WIFI 10
#define SSID_LEN 40
#define PASSWORD_LEN 40


struct  AP_SSID_PWD {
    uint8_t ssid[SSID_LEN];
    uint8_t ssid_len;
    uint8_t password[PASSWORD_LEN];
    uint8_t password_len;
};

struct AP_RECORD {
    uint32_t total_items;
    uint32_t current_item;
    uint32_t flag;
    struct  AP_SSID_PWD ssid_pwd[TOTAL_WIFI];
};

//flag param
#define MEDIA_RECORD_FLAG				0x56784321
#define AP_RECORD_FLAG					0x87651234
#define VOLUME_RECORD_FLAG				0x67891234
#define WIFIAUDIO_RECORD_FLAG			0x78901234
#define DEVICEUSER_FLAG					0x54321023
#define WIFIAUDIO_RECORD_COLLECT_FLAG 	0x78901234
#define DEVICE_LICENSE_FLAG				0x78901234
#define DISK_PLAYER_FLAG				0x67891234

#endif /* SYS_APP_H_ */
