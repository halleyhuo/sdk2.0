/**
 **************************************************************************************
 * @file    media_service.h
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

#ifndef __MEDIA_SERVICE_H__
#define __MEDIA_SERVICE_H__

#include "type.h"

#include "fsinfo.h"
#include "fat_file.h"
#include "folder.h"
#include "audio_decoder.h"

typedef enum _PLAYER_STATE
{
    PLAYER_STATE_IDLE = 0,    // 空闲
    PLAYER_STATE_PLAYING,     // 播放
    PLAYER_STATE_PAUSE,       // 暂停
    PLAYER_STATE_FF,          // 快进中
    PLAYER_STATE_FB,          // 快退中
} PLAYER_STATE;


typedef enum _AUDIO_PLAYER_PLAY_MODE_
{
    PLAY_MODE_REPEAT_ALL,     // 全盘顺序循环播放
    PLAY_MODE_REPEAT_FOLDER,  // 文件夹顺序循环播放
    PLAY_MODE_REPEAT_ONE,     // 单曲循环播放
    PLAY_MODE_RANDOM_ALL,     // 全盘随机播放
	PLAY_MODE_RANDOM_FOLDER,  // 文件夹随机播放
    PLAY_MODE_PREVIEW_PLAY,   // 预览播放（在文件浏览中，选中歌曲，可预览播放几秒钟）
    PLAY_MODE_SUM,
} AUDIO_PLAYER_MODE;

///////////////////////////////////////////////////////
// 复读模式的数据结构，后续系统设置有单独的复读模式设置(复读时长，循环次数)
#define REPEAT_CLOSED  0 // 复读关闭
#define REPEAT_A_SETED 1 // 已设置复读起点
#define REPEAT_OPENED  2 // 复读中

typedef struct _REPEAT_AB_
{
	uint32_t StartTime; // 起始时间(MS)，播放时，选择复读模式后，设置起点
	uint32_t Times;      // 复读时间长度(MS)，如果不通过设置结束时间的方式操作，最终的复读时间以此为准，可预设值
	uint8_t LoopCount;  // 循环次数，可预先设置(EPROM)，默认3次
	uint8_t RepeatFlag; // 当前是否复读模式(0 - 复读关闭, 1 - 已设置起点, 2 - 已设置终点，并开始复读)
} REPEAT_AB;

///////////////////////////////////////////////////////
typedef struct _AUDIO_PLAYER_CONTROL_
{
	uint8_t		CurPlayState;		// 播放器状态 (uint8_t)
    uint8_t		CurPlayMode;		// 当前播放循环模式
    
    uint32_t	CurPlayTime;		// 播放时间, ms
	uint32_t	LastPlayTime;		// 保存上次UI刷新时的播放时间值，用于刷新优化

	FAT_FILE	PlayerFile;         // 当前播放文件
	SongInfo*	CurSongInfo;		// 当前歌曲信息
	uint8_t*	CurSongTitlePtr;	// 当前歌曲标题、艺术家等信息
	uint16_t	CurFileIndex;		// 当前文件号，则代表全盘ID，
	uint16_t	TotalFileSumInDisk;	// 全盘中的文件总数
	
    FOLDER		PlayerFolder;		// 当前文件夹句柄（默认是磁盘根目录）
	uint16_t	CurFolderIndex;		// 当前文件夹全盘ID号（播放文件夹根目录或子目录），用于文件夹播放模式
    uint16_t	ValidFolderSumInDisk;//全盘中有效的文件夹总数，过滤空文件夹(不包含歌曲文件的文件夹)


#ifdef FUNC_LRC_EN
	uint8_t		LrcFlag;			// 歌词显示标志(EPROM设置项)
	uint8_t		IsLrcRunning;
	LRC_ROW		LrcRow;
#endif

//	SW_TIMER	DelayDoTimer;		// 延迟处理Timer【适用于连续切换歌曲、快进、快退等按键的延迟累加处理】
    
    REPEAT_AB	RepeatAB;			// 复读模式设置信息

//#ifdef PLAYER_SPECTRUM 				// 频谱显示
//	uint8_t		SpecTrumFlag;		// 频谱打开标识
//	SPECTRUM_INFO SpecTrumInfo;
//#endif

//	uint16_t	error_times;		// 某些错误连续发生的次数，用户恢复播放
//	uint8_t		IsBPMached;			// 是否FS已匹配了断点信息，主要用于防止保存无效的断点信息(播放模式初始化失败后，需要改标志判断是否保存断点信息)

//	uint16_t	InputNumber;		// 红外数字选取
//	SW_TIMER	NumKeyTimer;

//#ifdef FUNC_REC_PLAYBACK_EN
//	uint8_t		RecBackPlayFlag;
//#endif

//#ifndef FUNC_PLAY_RECORD_FOLDER_EN
//	uint16_t	RecFileStartId;
//	uint16_t	RecFileEndId;
//	uint16_t	RecFolderId;
//#endif

//#ifdef FUNC_BROWSER_EN
//	bool	BrowseFlag;
//#endif
} AUDIO_DISK_PLAYER;

extern AUDIO_DISK_PLAYER* gpDiskPlayer;


bool AudioPlayerInitialize(int32_t FileIndex, uint32_t FolderIndex);


/**
 * @brief
 *		Create Media service.
 * @param
 * 
 * @return  
 */
int32_t MediaServiceCreate(void);

/**
 * @brief
 *		Start Media service.
 * @param
 * 
 * @return  
 */
void MediaServiceStart(void);

/**
 * @brief
 *		Stop Media service.
 * @param
 * 
 * @return  
 */
void MediaServiceStop(void);

/**
 * @brief
 *		Kill Media service.
 * @param
 * 
 * @return  
 */
void MediaServiceKill(void);

MessageHandle GetMediaMessageHandle(void);

void * GetPtMediaFile(void);

#endif /*__MEDIA_SERVICE_H__*/

