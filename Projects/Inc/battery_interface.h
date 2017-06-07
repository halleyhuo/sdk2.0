/**
 **************************************************************************************
 * @file    battery_interface.h
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

#ifndef __BATTERY_INTERFACE_H__
#define __BATTERY_INTERFACE_H__

#include "type.h"
#include "battery.h"
#include "app_message.h"
#include "adc.h"

//电池电压等级设置门槛
#define BATTERY_VOLTAGE_FULL		4200
#define BATTERY_VOLTAGE_HIGH		3900
#define BATTERY_VOLTAGE_MID			3500
#define BATTERY_VOLTAGE_LOW			3300

#define BATTERY_SAMPLE_COUNT		10			//获取用来平均的采样次数

uint8_t GetBatteryLevel(void);
uint16_t BatteryGetVoltage(void);

#endif /*__BATTERY_INTERFACE_H__*/
