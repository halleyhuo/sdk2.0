/*
 * access_flash.h
 *
 *  Created on: Mar 24, 2017
 *      Author: peter
 */

#ifndef ACCESS_FLASH_H_
#define ACCESS_FLASH_H_

//device licence 
#define device_licence_flash_addr (0xF8000+1024*1024)

#define DEVICEUSER_FLAG			0x54321023
#define DEVICE_LICENSE_FLAG		0x78901234

//Net infor record
void BurnNetRecord(void);
void EraseLinkNetRecord(void);
void ReadNetRecord(void);

//wifi play infor record
void ReadPlayRecord(void);
void BurnPlayRecord(void);

//wx speech record
void BurnWxSpeechRecord(void);
void ReadWxSpeechRecord(void);
void BurnWxSpeechIdRecord(void);
void ReadWxSpeechIdRecord(void);


#endif /* ACCESS_FLASH_H_ */
