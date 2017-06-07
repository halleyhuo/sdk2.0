/**
 **************************************************************************************
 * @file    device_detect.h
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

#ifndef __DEVICE_DETECT_H__
#define __DEVICE_DETECT_H__

#define DEVICE_STATUS_SUCCESS			0
#define DEVICE_STATUS_FAILED			-1
#define DEVICE_STATUS_NOT_FOUND			-2
#define DEVICE_STATUS_ALREADY_EXIST		-3

#define DEVICE_STATUS_NOLINK			0
#define DEVICE_STATUS_LINKED			1

/**
 * Device Type
 */
typedef uint8_t						DeviceType;

/** USB */
#define DEVICE_TYPE_USB					1

/** CARD */
#define DEVICE_TYPE_CARD				2

/** MIC */
#define DEVICE_TYPE_MIC					3

/** LINEIN */
#define DEVICE_TYPE_LINEIN				4

/**
 * device event
 */
typedef uint8_t						DeviceEvent;

/** device pull in */
#define DEVICE_PULL_IN					1

/** device pull out */
#define DEVICE_PULL_OUT					2

/**
 * device value
 */
typedef uint8_t						DeviceValue;

#define INVAILD_DEVICE_VALUE			0xFF


typedef struct _DeviceCbParam
{
	DeviceType		type;
	uint8_t			event;
	uint16_t		value;
	bool			flag;
}DeviceCbParam;

typedef void (*DeviceCallbackFunc)(DeviceCbParam * params);

typedef void (*DeviceInitFunc)(void);

typedef DeviceValue (*DeviceScanFunc)(DeviceEvent *event);

typedef bool (*DeviceGetLinkFunc)(void);

typedef struct _DeviceContext
{
	DeviceCallbackFunc		callbackFunc;
	DeviceInitFunc			initFunc;
	DeviceScanFunc			scanFunc;
	DeviceGetLinkFunc		getLinkFunc;
}DeviceContext;

int32_t DeviceDetectInit(void);

int32_t DeviceDetectDeinit(void);

int32_t DeviceDetectRegister(DeviceType deviceType, DeviceContext * deviceCt);

int32_t DeviceDetectDeregister(DeviceType deviceType);

void DeviceDetect(void);

int32_t DeviceGetLinkFlag(DeviceType deviceType);


#endif /* __DEVICE_DETECT_H__ */

