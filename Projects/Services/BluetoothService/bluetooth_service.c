/**
 **************************************************************************************
 * @file    bluetooth_service.c
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

#include "uart.h"
#include "bt_stack_api.h"
#include "bt_stack_callback.h"


/***************************************************************************************
 *
 * External defines
 *
 */

#define BT_SERVICE_TASK_STACK_SIZE		1024
#define BT_SERVICE_TASK_PRIO			3

/***************************************************************************************
 *
 * Internal defines
 *
 */


#define BTS_NUM_MESSAGE_QUEUE		4

static const char btServcieName[]	= "BtServcie";

typedef struct _BtManagerContext
{
	xTaskHandle			serviceHandle;
	MessageHandle		msgHandle;
}BtManagerContext;


/***************************************************************************************
 *
 * Internal varibles
 *
 */

static BtManagerContext		btManger;
#define BTS(x)				(btManger.x)


//static BtManagerContext	*btManger;
//#define BTS(x)			(btManger->x)



/***************************************************************************************
 *
 * Internal functions
 *
 */
static void BtCommandEvent(uint32_t event, BT_STACK_CALLBACK_PARAMS * param)
{
	switch(event)
	{
		case BT_STACK_EVENT_COMMON_STACK_INITIALIZED:
			break;

		case BT_STACK_EVENT_COMMON_INQUIRY_RESULT:
			break;

		case BT_STACK_EVENT_COMMON_INQUIRY_COMPLETE:
			break;

		case BT_STACK_EVENT_COMMON_INQUIRY_CANCELED:
			break;


		case BT_STACK_EVENT_COMMON_MODE_CHANGE:
			break;

		case BT_STACK_EVENT_COMMON_GET_REMDEV_NAME:
			break;

		case BT_STACK_EVENT_COMMON_ACCESS_MODE:
			break;

		default:
		break;
	}
}

static void BtTrustListEvent(uint32_t event, BT_STACK_CALLBACK_PARAMS * param)
{
}

static void BtA2dpEvent(uint32_t event, BT_STACK_CALLBACK_PARAMS * param)
{
	switch(event)
	{
		case BT_STACK_EVENT_A2DP_CONNECTED:
			break;

		case BT_STACK_EVENT_A2DP_DISCONNECTED:
			break;

		case BT_STACK_EVENT_A2DP_STREAM_START:
			break;

		case BT_STACK_EVENT_A2DP_STREAM_SUSPEND:
			break;

		case BT_STACK_EVENT_A2DP_STREAM_DATA_IND:
			break;

		default:
			break;
	}
}

static void BtAvrcpEvent(uint32_t event, BT_STACK_CALLBACK_PARAMS * param)
{
	switch(event)
	{

		case BT_STACK_EVENT_AVRCP_CONNECTED:
			break;

		case BT_STACK_EVENT_AVRCP_DISCONNECTED:
			break;

		default:
			break;
	}
}


static void BtHfpEvent(uint32_t event, BT_STACK_CALLBACK_PARAMS * param)
{
	switch(event)
	{

		case BT_STACK_EVENT_HFP_CONNECTED:
			break;

		case BT_STACK_EVENT_HFP_DISCONNECTED:
			break;

		case BT_STACK_EVENT_HFP_SCO_CONNECTED:
			break;

		case BT_STACK_EVENT_HFP_SCO_DISCONNECTED:
			break;

		case BT_STACK_EVENT_HFP_CALL_CONNECTED:
			break;

		case BT_STACK_EVENT_HFP_CALL_DISCONNECTED:
			break;

		case BT_STACK_EVENT_HFP_CALLSETUP_NONE:
			break;

		case BT_STACK_EVENT_HFP_CALLSETUP_IN:
			break;

		case BT_STACK_EVENT_HFP_CALLSETUP_OUT:
			break;

		case BT_STACK_EVENT_HFP_CALLSETUP_ALERT:
			break;

		case BT_STACK_EVENT_HFP_RING:
			break;

		case BT_STACK_EVENT_HFP_CALLER_ID_NOTIFY:
			break;

		case BT_STACK_EVENT_HFP_CURRENT_CALLS:
			break;

		case BT_STACK_EVENT_HFP_CALL_WAIT_NOTIFY:
			break;

		case BT_STACK_EVENT_HFP_BATTERY:
			break;

		case BT_STACK_EVENT_HFP_SIGNAL:
			break;

		case BT_STACK_EVENT_HFP_ROAM:
			break;

		case BT_STACK_EVENT_HFP_VOICE_RECOGNITION:
			break;

		case BT_STACK_EVENT_HFP_SPEAKER_VOLUME:
			break;

		case BT_STACK_EVENT_HFP_IN_BAND_RING:
			break;
		case BT_STACK_EVENT_HFP_MANUFACTORY_INFO:
			break;

		case BT_STACK_EVENT_HFP_DEVICE_TYPE:
			break;

		case BT_STACK_EVENT_HFP_UNSOLICITED_DATA:
			break;

		default:
			break;
	}
}


static void BtMfiEvent(uint32_t event, BT_STACK_CALLBACK_PARAMS * param)
{
	switch(event)
	{
		case BT_STACK_EVENT_MFI_CONNECTED:
			break;

		case BT_STACK_EVENT_MFI_DISCONNECTED:
			break;

		case BT_STACK_EVENT_MFI_DATA_RECEIVED:
			break;

		case BT_STACK_EVENT_MFI_DATA_SENT:
			{
				
			}
			break;

		default:
			break;
	}
}


static void BtSppEvent(uint32_t event, BT_STACK_CALLBACK_PARAMS * param)
{
	switch(event)
	{
		case BT_STACK_EVENT_SPP_CONNECTED:
			break;

		case BT_STACK_EVENT_SPP_DISCONNECTED:
			break;

		case BT_STACK_EVENT_SPP_DATA_RECEIVED:
			break;

		case BT_STACK_EVENT_SPP_DATA_SENT:
			{
				
			}
			break;

		default:
			break;
	}
}


static void BtHidEvent(uint32_t event, BT_STACK_CALLBACK_PARAMS * param)
{
	switch(event)
	{
		case BT_STACK_EVENT_HID_CONNECTED:
			break;

		case BT_STACK_EVENT_HID_DISCONNECTED:
			break;

		case BT_STACK_EVENT_HID_DATA_RECEIVED:
			break;

		case BT_STACK_EVENT_HID_DATA_SENT:
			break;

		default:
			break;
	}
}


/**
 * Buart interrupt function
 */
__attribute__((section(".driver.isr")))
void BuartInterrupt(void)
{
	long			status;
	MessageContext	msgSend;

	status = BuartIOctl(UART_IOCTL_RXSTAT_GET,0);

	if(status & 0x01)	// interrupt by data arrived
	{
		BuartIOctl(UART_IOCTL_RXINT_SET,0);	// disable interrupt
		BuartIOctl(UART_IOCTL_RXINT_CLR,0);	// clear the interrupt flag

		msgSend.msgId		= MSG_SERVICE_STOPPED;
		msgSend.msgParams	= NULL;
		MessageSend(BTS(msgHandle), &msgSend);
	}
}

static uint32_t GetSupportProfiles(void)
{
	uint32_t		profiles = 0;

#if BT_HFP_SUPPORT == ENABLE
	profiles |= BT_PROFILE_SUPPORTED_HFP;
#endif

#if BT_A2DP_SUPPORT == ENABLE
	profiles |= BT_PROFILE_SUPPORTED_A2DP;
#endif

#if BT_AVRCP_SUPPORT == ENABLE
	profiles |= BT_PROFILE_SUPPORTED_AVRCP;
#endif

#if BT_SPP_SUPPORT == ENABLE
	profiles |= BT_PROFILE_SUPPORTED_SPP;
#endif

#if BT_OPP_SUPPORT == ENABLE
	profiles |= BT_PROFILE_SUPPORTED_OPP;
#endif

#if BT_HID_SUPPORT == ENABLE
	profiles |= BT_PROFILE_SUPPORTED_HID;
#endif

#if BT_MFI_SUPPORT == ENABLE
	profiles |= BT_PROFILE_SUPPORTED_MFI;
#endif

	return profiles;
}


/**
 * @brief
 *		Bluetooth stack callback
 *
 * @param
 *		event Event Id from stack call
 * @param
 *		param Parameters of stack callback, related with event
 *
 * @return
 *		NONE
 */
static void BtStackCallback(uint32_t event, BT_STACK_CALLBACK_PARAMS * param)
{
	if(event > BT_STACK_EVENT_COMMON_EVENT_START && event < BT_STACK_EVENT_COMMON_EVENT_END)
	{
		BtCommandEvent(event, param);
	}
	else if(event > BT_STACK_EVENT_TRUST_LIST_EVENT_START && event < BT_STACK_EVENT_TRUST_LIST_EVENT_END)
	{
		BtTrustListEvent(event, param);
	}
	else if(event > BT_STACK_EVENT_A2DP_EVENT_START && event < BT_STACK_EVENT_A2DP_EVENT_END)
	{
		BtA2dpEvent(event, param);
	}
	else if(event > BT_STACK_EVENT_AVRCP_EVENT_START && event < BT_STACK_EVENT_AVRCP_EVENT_END)
	{
		BtAvrcpEvent(event, param);
	}
	else if(event > BT_STACK_EVENT_HFP_EVENT_START && event < BT_STACK_EVENT_HFP_EVENT_END)
	{
		BtHfpEvent(event, param);
	}
	else if(event > BT_STACK_EVENT_MFI_EVENT_START && event < BT_STACK_EVENT_MFI_EVENT_END)
	{
		BtMfiEvent(event, param);
	}
	else if(event > BT_STACK_EVENT_SPP_EVENT_START && event < BT_STACK_EVENT_SPP_EVENT_END)
	{
		BtSppEvent(event, param);
	}
	else if(event > BT_STACK_EVENT_HID_EVENT_START && event < BT_STACK_EVENT_HID_EVENT_END)
	{
		BtHidEvent(event, param);
	}
	else
	{
		// unknown event
	}
}

/**
 * @brief
 *		Bluetooth manager init
 *
 * @param
 *		NONE
 *
 * @return
 *		0 for success
 */
static int32_t BtManagerInit(void)
{
	BtStackParams		stackParams;

	memset(&btManger, 0, sizeof(BtManagerContext));

	/*
	 * Initialize bluetooth stack
	 */

	/* Set support profiles */
	stackParams.supportProfiles = GetSupportProfiles();

	/* Set local device name */
	strcpy(stackParams.localDevName, BT_NAME);

	/* Set callback function */
	stackParams.callback = BtStackCallback;

	/* HFP features */
	stackParams.hfpFeatures.wbsSupport = BT_HFP_SUPPORT_WBS;
	stackParams.hfpFeatures.hfpAudioDataFormat = BT_HFP_AUDIO_DATA;

	/* A2DP features */
	stackParams.a2dpFeatures.a2dpAudioDataFormat = BT_A2DP_AUDIO_DATA;

	/* AVRCP features */
	stackParams.avrcpFeatures.supportAdvanced = BT_AVRCP_ADVANCED;
	stackParams.avrcpFeatures.supportTgSide = BT_AVRCP_TG_SIDE;

	BTStackRunInit(&stackParams);

	return 0;
}


static void BtManagerDeinit(void)
{
	MessageContext		msgSend;
	MessageHandle		mainHandle;

	BTStackRunUninit();

	/* Send message to main app */
	mainHandle = GetMainMessageHandle();
	msgSend.msgId		= MSG_SERVICE_STOPPED;
	msgSend.msgParams	= MSG_PARAM_BLUETOOTH_SERVICE;
	MessageSend(mainHandle, &msgSend);
}



static void BtServiceEntrance(void * param)
{
	MessageContext		msgRecv;
	MessageContext		msgSend;
	MessageHandle		mainHandle;



	/* register message handle */
	BTS(msgHandle) = MessageRegister(BTS_NUM_MESSAGE_QUEUE);

	/* Send message to main app */
	mainHandle = GetMainMessageHandle();
	msgSend.msgId		= MSG_SERVICE_CREATED;
	msgSend.msgParams	= (void *)MSG_PARAM_BLUETOOTH_SERVICE;
	MessageSend(mainHandle, &msgSend);

	while(1)
	{
		if(HasBtDataToProccess() || BuartIOctl(BUART_IOCTL_RXFIFO_DATLEN_GET, 0) != 0)
		{
			BTStackRun();
		}
		else
		{
			BuartIOctl(UART_IOCTL_RXINT_SET,1);
			MessageRecv(BTS(msgHandle), &msgRecv, MAX_RECV_MSG_TIMEOUT);
			switch(msgRecv.msgId)
			{
				case MSG_BT_SERVICE_DATA_ARRIVE:
					BTStackRun();
					break;

				case MSG_BT_SERVICE_STOP:
					BtManagerDeinit();
			
					/*Wait for kill*/
					vTaskSuspend(NULL);
					break;
			}
		}
	}
}


/***************************************************************************************
 *
 * APIs
 *
 */


MessageHandle GetBtMessageHandle(void)
{
	return BTS(msgHandle);
}

/**
 * @brief
 *		Start bluetooth service.
 * @param
 * 	 NONE
 * @return  
 */
int32_t BluetoothServiceStart(void)
{
	BtManagerInit();

	xTaskCreate(BtServiceEntrance, btServcieName, BT_SERVICE_TASK_STACK_SIZE, NULL, BT_SERVICE_TASK_PRIO, &BTS(serviceHandle));

	return 0;
}


void BluetoothServiceStop(void)
{
	vTaskDelete(BTS(serviceHandle));
}

