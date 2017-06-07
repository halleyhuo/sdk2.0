
#include "type.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "spi_flash.h"
#include "debug.h"
#include "gpio.h"
//#include "sys_app.h"
//#include "wifi_audio.h"
#include "timeout.h"
//#include "wakeup.h"
#include "file.h"
#include "smart_cfg_net.h"

//extern PLAY_RECORD *WifiaudioPlayRecord;
//extern uint8_t Volume;
//struct device_user_st *pdeviceuser;
//VOLUME_RECORD VolumeRecord;
uint8_t burn_dev_user = 0;


FILE* pPlayRecordFile;
char PlayRecordFileName[] = "PlayRecordFile.txt";

FILE* pVolumeRecordFile;
char VolumeRecordFileName[] = "VolumeRecordFile.txt";

FILE* pGetDeviceUserFile;
char GetDeviceUserFileName[] = "GetDeviceUserFileName.txt";

FILE* pMediaFile;
char MediaFileName[] = "MediaFileName.txt";

FILE* pMediaIDFile;
char MediaIDFileName[] = "MediaIDFileName.txt";

FILE* pNetRecordFile;
char NetRecordFileName[] = "NetRecordFileName.txt";

#ifdef FUNC_CARD_EN
FILE* pCardPlayRecordFile;
char CardPlayRecordFileName[] = "CardInforFileName.txt";
#endif

// º∆À„CRC
uint8_t GetCrc8CheckSum(uint8_t* ptr, uint32_t len)
{
	uint32_t crc = 0;
	uint32_t i;

	while(len--)
	{
		crc ^= *ptr++;
		for(i = 0; i < 8; i++)
		{
			if(crc & 0x01)
			{
				crc = ((crc >> 1) ^ 0x8C);
			}
			else
			{
				crc >>= 1;
			}
		}
	}
	return (uint8_t)crc;
}

int32_t InitFlashFS(void)
{
    int ret;
    SpiFlashInfoInit();
    ret = b_file_initialize();
    memset(&_iob, 0, sizeof(_iob));
    return ret;
}

void BurnNetRecord(void)
{
	pApJoiningRecord->flag = AP_RECORD_FLAG;
//	SpiFlashInfoInit();
//	FlashUnlock();

	pNetRecordFile = Fopen(NetRecordFileName, "w");
	Fwrite(pApJoiningRecord, sizeof(struct AP_RECORD), 1, pNetRecordFile);
	Fclose( pNetRecordFile );
}

void EraseLinkNetRecord(void)
{
//	SpiFlashInfoInit();
//	FlashUnlock();

	memset(pApJoiningRecord, 0xFF, sizeof(struct AP_RECORD));
	pNetRecordFile = Fopen(NetRecordFileName, "w");
	Fwrite(pApJoiningRecord, sizeof(struct AP_RECORD), 1, pNetRecordFile);
	Fclose( pNetRecordFile );
}

void ReadNetRecord(void)
{
	pNetRecordFile = Fopen(NetRecordFileName, "r");
	Fread(pApJoiningRecord, sizeof(struct AP_RECORD), 1, pNetRecordFile);
	Fclose( pNetRecordFile );
}

//void GetVolumeRecord(void)
//{
//	pVolumeRecordFile = Fopen(VolumeRecordFileName, "r");
//	Fread(&VolumeRecord, sizeof(VOLUME_RECORD), 1, pVolumeRecordFile);
//	Fclose( pVolumeRecordFile );	
//}

//void BurnVolumeRecord(void)
//{
//    VolumeRecord.flag = VOLUME_RECORD_FLAG;
//    VolumeRecord.volume = Volume;
//    SpiFlashInfoInit();
////	FlashUnlock();
//	pVolumeRecordFile = Fopen(VolumeRecordFileName, "w");
//	Fwrite(&VolumeRecord, sizeof(VOLUME_RECORD), 1, pVolumeRecordFile);
//	Fclose( pVolumeRecordFile );	
//}

//void GetPlayRecord(void)
//{
//	pPlayRecordFile = Fopen(PlayRecordFileName,"r");
//	Fread(WifiaudioPlayRecord, sizeof(PLAY_RECORD),1 ,pPlayRecordFile);
//	Fclose( pPlayRecordFile );	
//}

//void BurnPlayRecord(void)
//{
//    WifiaudioPlayRecord->flag = WIFIAUDIO_RECORD_FLAG;
//    SpiFlashInfoInit();
////	FlashUnlock();
//	pPlayRecordFile = Fopen(PlayRecordFileName,"w");
//	Fwrite(WifiaudioPlayRecord, sizeof(PLAY_RECORD), 1, pPlayRecordFile);
//	Fclose( pPlayRecordFile );
//}

//void ErasePlayRecord(void)
//{
//    SpiFlashInfoInit();
////	FlashUnlock();
//	memset(WifiaudioPlayRecord, 0xFF, sizeof(PLAY_RECORD));
//	pPlayRecordFile = Fopen(PlayRecordFileName, "w");
//	Fwrite(WifiaudioPlayRecord, sizeof(PLAY_RECORD), 1, pPlayRecordFile);
//	Fclose( pPlayRecordFile );
//}

//void GetDeviceUser(void)
//{
//	pGetDeviceUserFile = Fopen(GetDeviceUserFileName, "r");
//	Fread(pdeviceuser, sizeof(struct device_user_st), 1, pGetDeviceUserFile);
//	Fclose( pGetDeviceUserFile );
//}

//void BurnDeviceUser(void)
//{
//	struct device_user_st device_user;
//	
//	pGetDeviceUserFile = Fopen(GetDeviceUserFileName, "r");
//	Fread(&device_user, sizeof(struct device_user_st), 1, pGetDeviceUserFile);
//	Fclose( pGetDeviceUserFile );
//	
//	pdeviceuser->flag = DEVICEUSER_FLAG;
//	pdeviceuser->crc = CRC16((uint8_t *)pdeviceuser, sizeof(struct device_user_st)-4,0);
//	
//	if(device_user.crc != pdeviceuser->crc)
//	{
//		SpiFlashInfoInit();
////		FlashUnlock();
//		pGetDeviceUserFile = Fopen(GetDeviceUserFileName,"w");
//		Fwrite(pdeviceuser, sizeof(struct device_user_st), 1 ,pGetDeviceUserFile);
//		Fclose( pGetDeviceUserFile );
//	}
//}

//void GetMediaIdRecord(void)
//{
//	pMediaFile = Fopen(MediaFileName , "r");
//	Fread(pt_media_record, sizeof(media_record_st), 1, pMediaFile);
//	Fclose( pMediaFile );

//	pMediaIDFile = Fopen(MediaIDFileName , "r");
//	Fread(pt_media_id_record, sizeof(media_id_record_st), 1, pMediaIDFile);
//	Fclose( pMediaIDFile );
//}

//void BurnWeixinRecord(void)
//{
//    SpiFlashInfoInit();
////	FlashUnlock();
//	
//	pMediaFile = Fopen(MediaFileName , "w");
//	Fwrite(pt_media_record, sizeof(media_record_st), 1, pMediaFile);
//	Fclose( pMediaFile );
//}

////addr:0x1E9000 size:20K
//#define SIZE_WX_MEDIAID	0x5000 //5*4095=20K
//void BurnWeixinMediaId(void)
//{
//    SpiFlashInfoInit();
////	FlashUnlock();
//	
//	pMediaIDFile = Fopen(MediaIDFileName , "w");
//	Fwrite(pt_media_id_record, sizeof(media_id_record_st), 1, pMediaIDFile);
//	Fclose( pMediaIDFile );
//}

//void EraseWeixinRecord(void)
//{
//	memset(pt_media_record, 0xFF, sizeof(media_record_st));
//    SpiFlashInfoInit();
////	FlashUnlock();
//	
//	pMediaFile = Fopen(MediaFileName , "w");
//	Fwrite(pt_media_record, sizeof(media_record_st), 1, pMediaFile);
//	Fclose( pMediaFile );
//}

//#ifdef FUNC_CARD_EN
//extern CARD_PLAY_RECORD CardPlayRecord;
//void* GetPtCardInfor(void)
//{
//	void *pInfor=NULL;
//	pInfor = (void*)&(CardPlayRecord);
//	return pInfor;
//}

//void GetCardPlayRecord(void)
//{
//    pCardPlayRecordFile = Fopen(CardPlayRecordFileName, "r");
//    Fread(&CardPlayRecord, sizeof(CARD_PLAY_RECORD), 1, pCardPlayRecordFile);
//    Fclose( pCardPlayRecordFile );
//}

//void BurnCardPlayRecord(void)
//{
//    CardPlayRecord.flag = DISK_PLAYER_FLAG;
//    SpiFlashInfoInit();
//    pCardPlayRecordFile = Fopen(CardPlayRecordFileName, "w");
//    Fwrite(&CardPlayRecord, sizeof(CARD_PLAY_RECORD), 1, pCardPlayRecordFile);
//    Fclose( pCardPlayRecordFile );
//}
//#endif

