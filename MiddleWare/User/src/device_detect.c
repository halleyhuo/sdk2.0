/**
 **************************************************************************************
 * @file    device_detect.c
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
#include "device_detect.h"
#include "mv_list.h"

typedef struct _DeviceNode
{
	MVListNode			node;
	DeviceType			type;
	DeviceContext		device;
}DeviceNode;

static MVList	deviceList;


/**
 * @brief
 *		find the device node from the list
 *
 * @param
 *		device type
 *
 * @return
 *		list
 */
static MVListNode * FindDeviceNodeWithType(DeviceType deviceType)
{
	DeviceNode 		*deviceNode = NULL;
	MVListNode		*tempNode;
	
	if(MVIsListEmpty(&deviceList))
		return NULL;

	tempNode = MVGetHeadNode(&deviceList);
	
	while(tempNode)
	{
		deviceNode = (DeviceNode*)MVGetNodeContext(tempNode);

		if(deviceNode->type == deviceType)
			break;

		tempNode = MVGetNextNode(tempNode);
	}

	return tempNode;
}

/**
 * @brief
 *		device detect init
 *
 * @param
 *		none
 *
 * @return
 *		0 for init successful, otherwise failed
 */
int32_t DeviceDetectInit(void)
{
	MVListInit(&deviceList);
	return DEVICE_STATUS_SUCCESS;
}

/**
 * @brief
 *		device detect deinit
 *
 * @param
 *		none
 *
 * @return
 *		0 for deinit successful, otherwise failed
 */
int32_t DeviceDetectDeinit(void)
{
	MVListNode	*tempNode;
	DeviceNode	*deviceNode;

	/* Clear the key list */
	while(!MVIsListEmpty(&deviceList))
	{
		tempNode = MVGetHeadNode(&deviceList);

		deviceNode = (DeviceNode *)MVGetNodeContext(tempNode);
		
		vPortFree(deviceNode);

		MVRemoveNode(&deviceList, tempNode);
	}
}

/**
 * @brief
 *		Register a callback function for a type of device detect
 *
 * @param
 *		debiceType	Device type
 * @param
 *		callback Callback function for receiving device detect event
 *
 * @return
 *		0 for registering successful, otherwise failed
 */
int32_t DeviceDetectRegister(DeviceType deviceType, DeviceContext * deviceCt)
{
	DeviceNode  *deviceNode = NULL;
	MVListNode  *tempNode;

	/* Parameters check */
	if(deviceCt == NULL)
		return DEVICE_STATUS_FAILED;

	/*
	 * Check the key type whether it has been registered
	 */
	tempNode = FindDeviceNodeWithType(deviceType);
	if(tempNode)
		return DEVICE_STATUS_ALREADY_EXIST;

	/*
	 * Make a new device node
	 */
	deviceNode = (DeviceNode*)pvPortMalloc(sizeof(DeviceNode));

	if(deviceNode == NULL)
	{
		return DEVICE_STATUS_FAILED;
	}

	deviceNode->type				= deviceType;
	deviceNode->device.callbackFunc	= deviceCt->callbackFunc;
	deviceNode->device.initFunc		= deviceCt->initFunc;
	deviceNode->device.scanFunc		= deviceCt->scanFunc;

	MVInsertNodeToTail(&deviceList, &deviceNode->node);

	/* Init the device */
	deviceCt->initFunc();

	return DEVICE_STATUS_SUCCESS;
}

/**
 * @brief
 *		Deregister a device type
 *
 * @param
 *		deviceType	Device type
 *
 * @return
 *		0 for registering successful, otherwise failed
 */
int32_t DeviceDetectDeregister(DeviceType deviceType)
{
	DeviceNode		*deviceNode;
	MVListNode		*tempNode;

	tempNode = FindDeviceNodeWithType(deviceType);

	if(!tempNode)
		return DEVICE_STATUS_NOT_FOUND;

	deviceNode = (DeviceNode *)MVGetNodeContext(tempNode);
	
	vPortFree(deviceNode);

	MVRemoveNode(&deviceList, tempNode);

	return DEVICE_STATUS_SUCCESS;
}

/**
 * @brief
 *		Device detect function
 *
 * @param
 *		NONE
 *
 * @return
 *		NONE
 */
void DeviceDetect(void)
{
	MVListNode		*tempNode;

	if(MVIsListEmpty(&deviceList))
		return;

	tempNode = MVGetHeadNode(&deviceList);

	while(tempNode)
	{
		DeviceNode 	*deviceNode;
		uint16_t	value;
		uint8_t		event;

		deviceNode = (DeviceNode *)MVGetNodeContext(tempNode);

		value = deviceNode->device.scanFunc(&event);

		if(value != INVAILD_DEVICE_VALUE)
		{
			DeviceCbParam	deviceParams;

			deviceParams.event	= event;
			deviceParams.type	= deviceNode->type;
			deviceParams.value	= value;

			deviceNode->device.callbackFunc(&deviceParams);
		}

		tempNode = MVGetNextNode(tempNode);
	}
}

/**
 * @brief
 *		get Device link state
 *
 * @param
 *		deviceType Device Type
 *
 * @return
 *		Device Link state
 */
int32_t DeviceGetLinkFlag(DeviceType deviceType)
{
	DeviceNode		*deviceNode;
	MVListNode		*tempNode;

	tempNode = FindDeviceNodeWithType(deviceType);

	if(!tempNode)
		return DEVICE_STATUS_NOT_FOUND;

	deviceNode = (DeviceNode *)MVGetNodeContext(tempNode);

	if(deviceNode->device.getLinkFunc()) 
	{
		return DEVICE_STATUS_LINKED;
	}
	else
	{
		return DEVICE_STATUS_NOLINK;
	}
}

