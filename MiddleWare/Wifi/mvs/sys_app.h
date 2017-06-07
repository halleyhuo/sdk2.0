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
	uint32_t flag;
	uint8_t v;
	uint32_t playstage;
	//最新播放位置
	uint32_t playposition;
	uint8_t u1[512];
	uint8_t u2[512];
	uint8_t u3[512];
	uint8_t zj_id_s[10];
	uint8_t zj_size_s[10];
	uint16_t song_index;
	//收藏歌曲信息
	uint32_t flag_collect;
	uint8_t u1_collect[512];
	uint8_t u2_collect[512];
	uint8_t u3_collect[512];
	uint8_t zj_id_s_collect[10];
	uint8_t zj_size_s_collect[10];
	uint16_t song_index_collect;
} PLAY_RECORD;

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

#define MEDIA_RECORD_NUM 	200
#define MEDIA_ITEM_LEN		100
#define MEDIA_OLD_NUM		20

struct  media_id_st {
    uint8_t media_id[MEDIA_ITEM_LEN];
};

typedef struct _media_id_record_st {
	struct  media_id_st item[MEDIA_RECORD_NUM];
}media_id_record_st;

typedef struct _media_record_st {
    uint32_t total_number;//消息总数
    uint32_t current_item;//当前消息位置
    uint32_t old_item;//已读信息位置
	uint32_t newest_item;//最后1条新消息位置
	uint32_t newest_number;//新消息数目
	uint32_t valid_number;//有效消息数目 max=MEDIA_OLD_NUM
	uint32_t flag;
}media_record_st;

extern media_record_st *pt_media_record;
extern media_id_record_st *pt_media_id_record;
extern uint8_t zj_id_s[10];
extern uint8_t zj_size_s[10];
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

#define MEDIA_RECORD_FLAG				0x56784321
#define AP_RECORD_FLAG					0x87651234
#define VOLUME_RECORD_FLAG				0x67891234
#define WIFIAUDIO_RECORD_FLAG			0x78901234
#define DEVICEUSER_FLAG					0x54321023
#define WIFIAUDIO_RECORD_COLLECT_FLAG 	0x78901234
#define DEVICE_LICENSE_FLAG				0x78901234
#define DISK_PLAYER_FLAG				0x67891234

#endif /* SYS_APP_H_ */
