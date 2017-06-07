/**
 **************************************************************************************
 * @file    battery_interface.c
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


#include "type.h"
#include "battery_interface.h"
#include "rtos_api.h"

#define DBG		printf


static uint32_t batterySampleSum = 0;		//采样值总和
static uint32_t batterySampleAverage = 0;	//采样值平均数
static uint16_t batterySampleCnt = 0;		//采样次数
static uint8_t batteryLevel = 0;			//电池电量级别

uint8_t GetBatteryLevel(void)
{
	return batteryLevel;
}

uint16_t BatteryGetVoltage(void)
{
	return SarAdcGetLdoinVoltage();
}

void BatteryInitInter(void)
{
	batterySampleCnt = BATTERY_SAMPLE_COUNT;

	//to obtain battery voltage for the first time
	while(batterySampleCnt)
	{
		batterySampleCnt--;
		batterySampleSum += SarAdcGetLdoinVoltage();
		vTaskDelay(5);
	}
	BatteryScanInter();
}

BatteryLevel BatteryScanInter(BatteryEvent *event)
{
	bool batteryLevelUpdate = 0;

	*event = BATTERY_EVENT_NONE;
	
	if(batterySampleCnt > 0)
	{
		batterySampleSum += SarAdcGetLdoinVoltage();
		batterySampleCnt--;
	}

	//采样足够次数,求平均值
	if(batterySampleCnt == 0)
	{
		batterySampleAverage = batterySampleSum / BATTERY_SAMPLE_COUNT;

		batterySampleCnt = BATTERY_SAMPLE_COUNT;
		batterySampleSum = 0;
		
		batteryLevelUpdate = 0;
		if(batterySampleAverage >= BATTERY_VOLTAGE_FULL)
		{
			if(batteryLevel != BATTERY_LEVEL_FULL)
			{
				batteryLevel = BATTERY_LEVEL_FULL;
				batteryLevelUpdate= 1;
			}
		}
		else if(batterySampleAverage >= BATTERY_VOLTAGE_HIGH)
		{
			if(batteryLevel != BATTERY_LEVEL_HIGH)
			{
				batteryLevel = BATTERY_LEVEL_HIGH;
				batteryLevelUpdate= 1;
			}
		}
		else if(batterySampleAverage >= BATTERY_VOLTAGE_MID)
		{
			if(batteryLevel != BATTERY_LEVEL_MID)
			{
				batteryLevel = BATTERY_LEVEL_MID;
				batteryLevelUpdate= 1;
			}
		}
		else if(batterySampleAverage >= BATTERY_VOLTAGE_LOW)
		{
			if(batteryLevel != BATTERY_LEVEL_LOW)
			{
				batteryLevel = BATTERY_LEVEL_LOW;
				batteryLevelUpdate= 1;
			}
		}
		else
		{
			if(batteryLevel != BATTERY_LEVEL_POWEROFF)
			{
				batteryLevel = BATTERY_LEVEL_POWEROFF;
				batteryLevelUpdate= 1;
			}
		}

		if(batteryLevelUpdate)
		{
			BatteryCbParam	batteryParams;
			
			batteryLevelUpdate = 0;

			DBG("[BATTERY]: level = [%d]\n",batteryLevel);
			*event = BATTERY_EVENT_UPDATE;
			return batteryLevel;
		}
	}

	return INVAILD_BATTERY_LEVEL;
}


