/**
 **************************************************************************************
 * @file    wxcloud_api.h
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


#ifndef __WXCLOUD_API_H__
#define __WXCLOUD_API_H__

#include "type.h"
#include "airkiss_types.h"
#include "airkiss_cloudapi.h"


#define DEV_LINCENSE_LEN	256

#define DEV_ID_LEN			64

#define DEV_TYPE_LEN		32




typedef int32_t				WxcloudStatus;


#define WXCLOUD_STATUS_SUCCESS			0

#define WXCLOUD_STATUS_FAILED			-1

#define WXCLOUD_STATUS_PARAMS_ERR		-2

#define WXCLOUD_STATUS_NO_MORE_DATA		-3

#define WXCLOUD_STATUS_NOT_FOUND		-4


typedef struct _WxcloudParams
{
	uint8_t					*devLicense;
	uint16_t				devLicenseLen;
	uint8_t					*wxBuffer;
	uint16_t				wxBufferLen;
	ak_mutex_t				*taskMutex;
	ak_mutex_t				*mallocMutex;
	ak_mutex_t				*loopMutex;
	uint8_t					*property;
	uint16_t				propertyLen;
	airkiss_callbacks_t		cbs;
} WxcloudParams;


typedef struct _WxcloudDevInfo
{
	uint8_t			devId[DEV_ID_LEN];
	uint8_t			devType[DEV_TYPE_LEN];	
}WxcloudDevInfo;

WxcloudStatus WxcloudInit(void);

WxcloudStatus WxcloudDeinit(void);

WxcloudStatus WxcloudRegister(WxcloudParams *params, WxcloudDevInfo *wxcloudDevInfo);

WxcloudStatus WxcloudDeregister(void);

void WxcloudRun(void);

WxcloudStatus WxcloudGetAccessToken(uint8_t * accessToken);



#endif /*__WXCLOUD_API_H__*/
