/**
 **************************************************************************************
 * @file    battery.h
 * @brief   
 *
 * @author  bukk
 * @version V1.0.0
 *
 * $Created: 2017-2-28 13:06:47$
 *
 * @Copyright (C) 2016, Shanghai Mountain View Silicon Co.,Ltd. All rights reserved.
 **************************************************************************************
 */


#ifndef __BATTERY_H__
#define __BATTERY_H__

#include "type.h"

typedef int32_t						BatteryStatus;

#define BATTERY_STATUS_SUCCESS			0

#define BATTERY_STATUS_FAILED			-1

#define BATTERY_STATUS_ALREADY_EXIST	-2

#define BATTERY_STATUS_NOT_FOUND		-3

typedef uint8_t						BatteryType;

#define BATTERY_TYPE	1

/**
 * Battery event
 */
typedef uint8_t						BatteryEvent;

#define BATTERY_EVENT_NONE				0
/** Battery Level Update */
#define BATTERY_EVENT_UPDATE			1

/**
 * Battery value
 */
typedef uint8_t						BatteryValue;

#define INVAILD_BATTERY_VALUE			0xFF

/**
 * Battery level
 */
typedef uint8_t						BatteryLevel;

#define INVAILD_BATTERY_LEVEL			0

#define BATTERY_LEVEL_FULL				1
#define BATTERY_LEVEL_HIGH				2
#define BATTERY_LEVEL_MID				3
#define BATTERY_LEVEL_LOW				4
#define BATTERY_LEVEL_POWEROFF			5

/**
 * Parameters for key callback function
 */
typedef struct _BateryCbParam
{
	BatteryType		type;
	BatteryLevel	level;
	BatteryValue	value;
}BatteryCbParam;

/**
 * @brief
 *		Callback function for Battery. This function
 *		will be called when a key event generated.
 *
 * @param
 *		params Parameter for Battery callback function
 *
 * @return
 *		NONE
 */
typedef void (*BatteryCallbackFunc)(BatteryCbParam * params);


/**
 * @brief
 *		Battery init function
 *
 * @param
 *		void
 *
 * @return
 *		NONE
 */
typedef void (*BatteryInitFunc)(void);

/**
 * @brief
 *		Key scan function
 *
 * @param
 *		event Key event with key value
 *
 * @return
 *		Key value
 */
typedef BatteryLevel (*BatteryScanFunc)(BatteryEvent *event);

typedef BatteryValue (*BatteryGetValueFunc)(void);

typedef BatteryLevel (*BatteryGetLevelFunc)(void);

/**
 * Key context
 */
typedef struct _BatteryContext
{
	BatteryCallbackFunc		callbackFunc;
	BatteryInitFunc			initFunc;
	BatteryScanFunc			scanFunc;
	BatteryGetValueFunc		getValueFunc;
	BatteryGetLevelFunc		getLevelFunc;
}BatteryContext;

BatteryStatus BatteryInit(void);

void BatteryDeinit(void);

BatteryStatus BatteryRegister(BatteryType batteryType, BatteryContext * batteryCt);

BatteryStatus BatteryDeregister(BatteryType batteryType);

void BatteryScan(void);

BatteryValue BatteryGetValue(void);

BatteryLevel BatteryGetLevel(void);

#endif /*__BATTERY_H__*/
