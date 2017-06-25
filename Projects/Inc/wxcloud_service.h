/**
 **************************************************************************************
 * @file    wxcloud_service.h
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

#ifndef __WXCLOUD_SERVICE_H__
#define __WXCLOUD_SERVICE_H__

#include "type.h"
#include "freeRTOS.h"
#include "rtos_api.h"
#include "app_message.h"
#include "sys_app.h"

extern PLAY_RECORD *WifiaudioPlayRecord;




void GetNextPreSongURL(bool UpDown);

MessageHandle GetWxcloudMessageHandle(void);

ServiceState GetWxcloudServiceState(void);

int32_t WxcloudServiceCreate(void);

void WxcloudServiceStart(void);

void WxcloudServiceStop(void);

void WxcloudServiceKill(void);




#endif /*__WXCLOUD_SERVICE_H__*/

