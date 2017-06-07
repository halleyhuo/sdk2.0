/**
 **************************************************************************************
 * @file    device_manager.h
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

#ifndef __DEVICE_MANAGER_H__
#define __DEVICE_MANAGER_H__

#include "type.h"


int32_t DeviceServiceCreate(void);

/**
 * @brief
 *		Start wifi service.
 * @param
 * 	 NONE
 * @return  
 */
int32_t DeviceServiceStart(void);

/**
 * @brief
 *		Stop device service.
 * @param
 * 	 NONE
 * @return  
 */
void DeviceServiceStop(void);

void DeviceServiceKill(void);

/**
 * @brief
 *		Get message handle
 * @param
 * 	 NONE
 * @return  
 */
MessageHandle GetDeviceMessageHandle(void);

#endif /*__DEVICE_MANAGER_H__*/


