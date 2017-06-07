/**
 **************************************************************************************
 * @file    battery.c
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
#include "battery.h"
#include "mv_list.h"
#include "freertos.h"
#include "app_message.h"

/***************************************************************************************
 *
 * External defines
 *
 */



/***************************************************************************************
 *
 * Internal defines
 *
 */

typedef struct _BatteryNode
{
	uint8_t				type;
	BatteryContext		battery;
}BatteryNode;

static MVList	batteryList;

/***************************************************************************************
 *
 * APIs
 *
 */

/**
 * @brief
 *		Key initialization function
 *
 * @param
 *		callback Callback function for receiving key event
 *
 * @return
 *		0 for initializing successful, otherwise failed
 */
BatteryStatus BatteryInit(void)
{
	MVListInit(&batteryList);
	return BATTERY_STATUS_SUCCESS;
}

/**
 * @brief
 *		Key deinit function
 *
 * @param
 *		NONE
 *
 * @return
 *		NONE
 */
void BatteryDeinit(void)
{
	MVListNode	*tempNode;
	BatteryNode	*batteryNode;

	/* Clear the key list */
	while(!MVIsListEmpty(&batteryList))
	{
		tempNode = MVGetHeadNode(&batteryList);

		batteryNode = (BatteryNode *)MVGetNodeContext(tempNode);
		vPortFree(batteryNode);

		MVRemoveNode(&batteryList, tempNode);
	}
}

/**
 * @brief
 *		Register a callback function for a type of key
 *
 * @param
 *		keyType	Key type
 * @param
 *		callback Callback function for receiving key event
 *
 * @return
 *		0 for registering successful, otherwise failed
 */
BatteryStatus BatteryRegister(BatteryType batteryType, BatteryContext * batteryCt)
{
	BatteryNode 	*batteryNode = NULL;
	MVListNode		*tempNode;

	/* Parameters check */
	if(batteryCt == NULL)
		return BATTERY_STATUS_FAILED;

	/*
	 * Make a new key node
	 */
	batteryNode = (BatteryNode*)pvPortMalloc(sizeof(BatteryNode));

	if(batteryNode == NULL)
	{
		return BATTERY_STATUS_FAILED;
	}

	batteryNode->type					= batteryType;
	batteryNode->battery.callbackFunc	= batteryCt->callbackFunc;
	batteryNode->battery.initFunc		= batteryCt->initFunc;
	batteryNode->battery.scanFunc		= batteryCt->scanFunc;

	MVInsertNodeToTail(&batteryList, batteryNode);

	/* Init the key */
	batteryCt->initFunc();

	return BATTERY_STATUS_SUCCESS;
}

/**
 * @brief
 *		Deregister a key type
 *
 * @param
 *		keyType	Key type
 *
 * @return
 *		0 for registering successful, otherwise failed
 */
BatteryStatus BatteryDeregister(BatteryType batteryType)
{
	BatteryNode		*batteryNode;
	MVListNode		*tempNode;

	tempNode = MVGetHeadNode(&batteryList);

	if(!tempNode)
		return BATTERY_STATUS_NOT_FOUND;

	batteryNode = (BatteryNode *)MVGetNodeContext(tempNode);
	
	vPortFree(batteryNode);

	MVRemoveNode(&batteryList, tempNode);

	return BATTERY_STATUS_SUCCESS;
}


/**
 * @brief
 *		Key scan function
 *
 * @param
 *		NONE
 *
 * @return
 *		NONE
 */
void BatteryScan(void)
{
	MVListNode		*tempNode;
	BatteryNode 	*batteryNode;
	BatteryValue	value;
	BatteryLevel	level;
	BatteryEvent	event;

	if(MVIsListEmpty(&batteryList))
		return;

	tempNode = MVGetHeadNode(&batteryList);

	batteryNode = (BatteryNode *)MVGetNodeContext(tempNode);

	level = batteryNode->battery.scanFunc(&event);

	if(level != INVAILD_BATTERY_LEVEL)
	{
		BatteryCbParam		batteryParams;

		batteryParams.level	= event;
		batteryParams.type	= batteryNode->type;
		batteryParams.value = value;

		batteryNode->battery.callbackFunc(&batteryParams);
	}
}

BatteryValue BatteryGetValue(void)
{
	MVListNode		*tempNode;
	BatteryNode 	*batteryNode;
	BatteryValue	value;
	
	if(MVIsListEmpty(&batteryList))
		return;

	tempNode = MVGetHeadNode(&batteryList);

	batteryNode = (BatteryNode *)MVGetNodeContext(tempNode);

	value = batteryNode->battery.getValueFunc();
	return value;
}

BatteryLevel BatteryGetLevel(void)
{
	MVListNode		*tempNode;
	BatteryNode 	*batteryNode;
	BatteryLevel	level;
	
	if(MVIsListEmpty(&batteryList))
		return;

	tempNode = MVGetHeadNode(&batteryList);

	batteryNode = (BatteryNode *)MVGetNodeContext(tempNode);

	level = batteryNode->battery.getLevelFunc();
	return level;
}

