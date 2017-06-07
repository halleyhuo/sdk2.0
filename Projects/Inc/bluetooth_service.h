/**
 **************************************************************************************
 * @file    bluetooth_service.h
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

#ifndef __BLUETOOTH_MANAGER_H__
#define __BLUETOOTH_MANAGER_H__

#include "type.h"

/**
 * @brief
 *		Get message receive handle of bt servcie
 * 
 * @param
 *		NONE
 *
 * @return
 *		MessageHandle
 */

MessageHandle GetBtMessageHandle(void);



/**
 * @brief
 *		Start bluetooth service.
 * @param
 * 	 NONE
 * @return  
 */
int32_t BluetoothServiceStart(void);

void BluetoothServiceStop(void);

#endif /*__BLUETOOTH_MANAGER_H__*/


