/**
 **************************************************************************************
 * @file    wifi_manager.h
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

#ifndef __WIFI_MANAGER_H__
#define __WIFI_MANAGER_H__

#include "type.h"
#include "rtos_api.h"

int32_t WifiServiceCreate(MessageHandle parentMsgHandle);

/**
 * @brief
 *		Start wifi service.
 * @param
 * 	 NONE
 * @return  
 */
int32_t WifiServiceStart(void);

void WifiServiceStop(void);

void WifiServiceKill(void);


#endif /*__WIFI_MANAGER_H__*/

