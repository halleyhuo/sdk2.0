/**
 **************************************************************************************
 * @file    device_manager.c
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
#include <string.h>
#include "type.h"
#include "bt_config.h"
#include "rtos_api.h"
#include "app_message.h"
#include "main_app.h"

#include "key.h"
#include "battery.h"
#include "device_detect.h"

#define DBG printf
/***************************************************************************************
 *
 * External defines
 *
 */

#define DEVICE_SERVICE_SIZE				1024
#define DEVICE_SERVICE_PRIO				3

#define DEVICE_SERVICE_TIMEOUT			10	/* 10 ms */

extern void AdcKeyInit(void);
extern KeyValue AdcKeyScan(KeyEvent *event);

extern void CodingKeyInit(void);
extern KeyValue CodingKeyScan(KeyEvent *event);

extern void IrKeyInit(void);
extern KeyValue IrKeyScan(KeyEvent *event);

extern void BatteryInitInter(void);
extern BatteryLevel BatteryScanInter(BatteryEvent *event);
extern uint8_t GetBatteryLevel(void);
extern uint16_t BatteryGetVoltage(void);

extern void DeviceCardInit(void);
extern DeviceValue DeviceCardDetect(DeviceEvent *event);
extern bool GetCardLinkFlag(void);

extern void DeviceMicInit(void);
extern DeviceValue DeviceMicDetect(DeviceEvent *event);
extern bool GetMicLinkFlag(void);

//static KeyEventMsg			keyEventMsg;

/***************************************************************************************
 *
 * Internal defines
 *
 */
#define DS_NUM_MESSAGE_QUEUE		4

typedef struct _DeviceServiceContext
{
	xTaskHandle			taskHandle;
	MessageHandle		msgHandle;
	ServiceState		serviceState;
	

}DeviceServiceContext;

/** Device servcie name*/
const char deviceServiceName[]		= "DeviceService";


/***************************************************************************************
 *
 * Internal varibles
 *
 */

static DeviceServiceContext			deviceServiceCt;
#define DS(x)						(deviceServiceCt.x)


//static DeviceServiceContext		*deviceServiceCt;
//#define DS(x)						(deviceServiceCt->x)

/***************************************************************************************
 *
 * Internal functions
 *
 */

static void KeysCallback(KeyCbParam * params)
{
	MessageHandle		mainHandle;
	MessageContext		msgCt;
	uint16_t			keyMsgParams;

	mainHandle = GetMainMessageHandle();

	keyMsgParams = (((uint8_t)params->event << 8) | (uint8_t)params->value);

	msgCt.msgId 	= MSG_KEY_EVENT;
	msgCt.msgParams	= keyMsgParams;
	MessageSend(mainHandle, &msgCt);
}

static void KeysInit(void)
{
	KeyContext		adcKey;
	KeyContext		codingKey;
	KeyContext		irKey;

	/* Key init */
	KeyInit();

	/* Register ADC key*/
	adcKey.callbackFunc	= KeysCallback;
	adcKey.initFunc		= AdcKeyInit;
	adcKey.scanFunc		= AdcKeyScan;
	KeyRegister(KEY_TYPE_ADC, &adcKey);

	/* Register coding key*/
	/*codingKey.callbackFunc	= KeysCallback;
	codingKey.initFunc		= CodingKeyInit;
	codingKey.scanFunc		= CodingKeyScan;
	KeyRegister(KEY_TYPE_CODING, &codingKey);
	*/
	/* Register IR key*/
	/*irKey.callbackFunc	= KeysCallback;
	irKey.initFunc		= IrKeyInit;
	irKey.scanFunc		= IrKeyScan;
	KeyRegister(KEY_TYPE_IR, &irKey);
	*/
}


static void BatteryCallBack(BatteryCbParam *params)
{
	MessageHandle		mainHandle;
	MessageContext		msgCt;
	uint16_t			batteryEventMsg;

	mainHandle = GetDeviceMessageHandle();

	batteryEventMsg = (((uint8_t)params->level << 8) | (uint8_t)params->value);
	
	msgCt.msgId 	= MSG_BATTERY_EVENT;
	msgCt.msgParams	= batteryEventMsg;
	MessageSend(mainHandle, &msgCt);
}

static void BatteryServiceInit(void)
{
	BatteryContext	batteryService;
	
	SarAdcLdoinVolInit();
	
	/* Battery init */
	BatteryInit();

	/* Register Device Card*/
	batteryService.callbackFunc	= BatteryCallBack;
	batteryService.initFunc		= BatteryInitInter;
	batteryService.scanFunc		= BatteryScanInter;
	batteryService.getValueFunc	= BatteryGetVoltage;
	batteryService.getLevelFunc	= GetBatteryLevel;
	BatteryRegister(BATTERY_TYPE, &batteryService);
}


static void DevicesCallback(DeviceCbParam * params)
{
	MessageHandle		mainHandle;
	MessageContext		msgCt;
	uint16_t			deviceEventMsg;

	mainHandle = GetDeviceMessageHandle();

	deviceEventMsg = (((uint8_t)params->event << 8) | (uint8_t)params->value);

	msgCt.msgId 	= MSG_DEVICE_EVENT;
	msgCt.msgParams	= deviceEventMsg;
	MessageSend(mainHandle, &msgCt);
}

static void DevicesInit(void)
{
	DeviceContext	deviceCard;
	DeviceContext	deviceMic;

	/* Device init */
	DeviceDetectInit();

	/* Register Device Card*/
	deviceCard.callbackFunc	= DevicesCallback;
	deviceCard.initFunc		= DeviceCardInit;
	deviceCard.scanFunc		= DeviceCardDetect;
	deviceCard.getLinkFunc	= GetCardLinkFlag;
	DeviceDetectRegister(DEVICE_TYPE_CARD, &deviceCard);

	/* Register Device Mic*/
	deviceMic.callbackFunc	= DevicesCallback;
	deviceMic.initFunc		= DeviceMicInit;
	deviceMic.scanFunc		= DeviceMicDetect;
	deviceCard.getLinkFunc	= GetMicLinkFlag;
	DeviceDetectRegister(DEVICE_TYPE_MIC, &deviceMic);
}


/**
 * @brief
 *		Device servcie init
 *
 * @param
 *		NONE
 *
 * @return
 *		0 for success
 */
static int32_t DeviceServiceInit(void)
{
	memset(&deviceServiceCt, 0, sizeof(DeviceServiceContext));

	DS(serviceState) = ServiceStateNone;

	/* Init keys*/
	KeysInit();

	/* Init battery */
//	BatteryServiceInit();

	/* Init device */
//	DevicesInit();
	
	return 0;
}


static void DeviceServiceDeinit(void)
{
	MessageContext		msgSend;
	MessageHandle		mainHandle;

	/* Key deinit*/
	KeyDeinit();

	/* Battery deinit */
	BatteryDeinit();

	/* Device detect deinit */
	DeviceDetectDeinit();

	DS(serviceState) = ServiceStateNone;

	/* Send message to main app */
	mainHandle = GetMainMessageHandle();
	msgSend.msgId		= MSG_SERVICE_STOPPED;
	msgSend.msgParams	= NULL;
	MessageSend(mainHandle, &msgSend);
}

static void DeviceServiceEntrance(void * param)
{
	MessageContext		msgRecv;
	MessageContext		msgSend;
	MessageHandle		mainHandle;

	/* register message handle */
	DS(msgHandle) = MessageRegister(DS_NUM_MESSAGE_QUEUE);

	DS(serviceState) = ServiceStateReady;
	
	/* Send message to main app */
	mainHandle = GetMainMessageHandle();
	msgSend.msgId		= MSG_SERVICE_CREATED;
	msgSend.msgParams	= MSG_PARAM_DEVICE_SERVICE_ID;
	MessageSend(mainHandle, &msgSend);

	while(1)
	{
		MessageRecv(DS(msgHandle), &msgRecv, DEVICE_SERVICE_TIMEOUT);
		switch(msgRecv.msgId)
		{
			case MSG_SERVICE_START:
				if(DS(serviceState) == ServiceStateReady)
				{
					DS(serviceState) = ServiceStateRunning;

					msgSend.msgId		= MSG_SERVICE_STARTED;
					msgSend.msgParams	= MSG_PARAM_DEVICE_SERVICE_ID;					
					MessageSend(mainHandle, &msgSend);
				}
				break;

			case MSG_SERVICE_STOP:
				DeviceServiceDeinit();

				/*Wait for kill*/
				vTaskSuspend(NULL);
				break;
			default:
				break;
		}

		if(DS(serviceState) == ServiceStateRunning)
		{
			/* Key scan*/
			KeyScan();

			/* Battery Scan */
//			BatteryScan();

			/* Device Detect */
//			DeviceDetect();
		}
	}
}


/***************************************************************************************
 *
 * APIs
 *
 */


/**
 * @brief
 *		Get message receive handle of audio core manager
 * 
 * @param
 *		NONE
 *
 * @return
 *		MessageHandle
 */
MessageHandle GetDeviceMessageHandle(void)
{
	return DS(msgHandle);
}

/**
 * @brief
 *		Start device service.
 *
 * @param
 * 	 NONE
 *
 * @return
 */
int32_t DeviceServiceCreate(void)
{
	DeviceServiceInit();
	xTaskCreate(DeviceServiceEntrance, deviceServiceName, DEVICE_SERVICE_SIZE, NULL, DEVICE_SERVICE_PRIO, &DS(taskHandle));
	return 0;
}


/**
 * @brief
 *		Start wifi service.
 * @param
 * 	 NONE
 * @return  
 */
int32_t DeviceServiceStart(void)
{
	MessageContext		msgSend;

	msgSend.msgId		= MSG_SERVICE_START;
	msgSend.msgParams	= NULL;
	MessageSend(DS(msgHandle), &msgSend);

	return 0;
}

/**
 * @brief
 *		Stop device service.
 * @param
 * 	 NONE
 * @return  
 */
void DeviceServiceStop(void)
{
	return 0;
}

/**
 * @brief
 *		Stop device service.
 *
 * @param
 * 	 NONE
 *
 * @return  
 */
void DeviceServiceKill(void)
{
	vTaskDelete(DS(taskHandle));
}


