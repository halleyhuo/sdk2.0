/**
 **************************************************************************************
 * @file    wifi service.c
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

#include "type.h"
#include "rtos_api.h"
#include "gpio.h"
#include "irqs.h"
#include "app_message.h"
#include "app_config.h"
#include "timeout.h"

#include <net_mgr.h>
#include "wifi_api.h"
#include "wifi_porting.h"
#include "wifi_service.h"
#include <cli/cmds/cli_cmd_wifi.h>


/***************************************************************************************
 *
 * External defines
 *
 */
extern uint8_t *memp_memory;

TIMER GetIPWaitTimer;

/***************************************************************************************
 *
 * External defines
 *
 */

 
/** WIFI servcie name*/
const char wifiServiceName[] = "WifiService";
#define WIFI_SERVICE_SIZE				1024
#define WIFI_SERVICE_PRIO				3
	
#define WIFI_SERVICE_TIMEOUT			1	/* 1 ms */

#define WS_NUM_MESSAGE_QUEUE			10


/***************************************************************************************
 *
 * Internal defines
 *
 */
const char initSSVDeviceName[] = "InitSSVDeviceTask";
#define INIT_SSV_TASK_STACK_SIZE		1024*8
#define INIT_SSV_TASK_PRIO				3
	
const char wifiConnectServiceTaskName[] = "WifiConnectServiceTask";
#define WIFI_CONNECT_SERVICE_TASK_STACK_SIZE		1024
#define WIFI_CONNECT_SERVICE_TASK_PRIO			3
	
#define MEMP_MEMORY_LEN					200*1024
	
#define GPIO_INT_PRIO					2

const uint8_t ssid_name[] = "mv-cs-guest";
const uint8_t ssid_passwords[] = "62welcome";

typedef enum _ConnectState
{
	WIFI_IDLE = 0,	//disconnect
	WIFI_START,
	WIFI_SCAN,
	WIFI_SCAN_END,
	WIFI_JOIN,
	WIFI_JOIN_END,
	WIFI_JOIN_SPECIFY_NET,
	WIFI_JOIN_SPECIFY_NET_END,
	WIFI_SMARTLINK,
	WIFI_SMARTLINK_CONFIG_END,
	WIFI_SMARTLINK_JOIN_END,
	WIFI_CONNECT_AP,
	WIFI_GET_IP,
	WIFI_CONNECTED,
	WIFI_UPGRADE,
}ConnectState;

typedef enum _ConfigLinkMode
{
	MODE_RECONNECT = 0,
	MODE_SMARTLINK,
	MODE_SPECIFY_NET,
}ConfigLinkMode;

typedef struct _WifiConnectServiceContext
{
	ConnectState		connectState;
	ConfigLinkMode		configLinkMode;
}WifiConnectServiceContext;

typedef struct _WifiServiceContext
{
	//wifi service
	xTaskHandle 		taskHandle;
	MessageHandle		msgHandle;
	MessageHandle		parentMsgHandle;
	ServiceState		serviceState;

	//wifi ConnectService task
	xTaskHandle 		connectServiceTaskHandle;
	MessageHandle		connectServiceMsgHandle;
	ServiceState		connectServiceState;
	WifiConnectServiceContext	wifiConnectServiceContext;
}WifiServiceContext;

/***************************************************************************************
 *
 * Internal variables
 *
 */
static WifiServiceContext		wifiServiceCt;
#define WS(x)					(wifiServiceCt.x)

/***************************************************************************************
 *
 * Internal functions
 *
 */
	

static void SelectWifiInSdioMode(void)
{
	//Select wifi module use sdio mode
	GpioSetRegOneBit(GPIO_C_OE, GPIOC3);
	GpioClrRegOneBit(GPIO_C_OUT,GPIOC3);
}

/***************************************************************************************
 *
 * wifi ConnectService task
 *
 */

static MessageHandle GetWifiConnectServiceMessageHandle(void)
{
	return wifiServiceCt.connectServiceMsgHandle;
}

static ServiceState GetWifiConnectServiceState(void)
{
	return wifiServiceCt.connectServiceState;
}

static void SetWifiConnectServiceState(ServiceState state)
{
	wifiServiceCt.connectServiceState = state;
}

static void SetWifiConnectState(ConnectState state)
{
	wifiServiceCt.wifiConnectServiceContext.connectState = state;
}

static ConnectState GetWifiConnectState(void)
{
	return wifiServiceCt.wifiConnectServiceContext.connectState;
}

static void WifiConnectServiceMsgProcess(MessageContext *msg)
{
	switch(msg->msgId)
	{
		case MSG_WIFI_CONNECT_SERVICE_START:
			if(GetWifiConnectServiceState() == ServiceStateReady) 
			{
				if(GetWifiConnectState() == WIFI_IDLE)
				{
					//wifi start connect network
					SetWifiConnectState(WIFI_START);
				}
			}
			break;

		case MSG_WIFI_CONNECT_SERVICE_STOP:
			if(GetWifiConnectServiceState() == ServiceStateRunning) 
			{
				
			}
			break;

		default:
			break;
	}
}

static void WifiConnectServiceEntrance(void)
{
	MessageContext		msgRecv;
	MessageContext		msgSend;
	MessageHandle		wifiServiceHandle;
	
	uint32_t addr;
	uint8_t i,item;
	int32_t ret = -1;
	wifi_sta_join_cfg *join_cfg = NULL;
	uint32_t ap_count;
	struct ssv6xxx_ieee80211_bss *ap_list = NULL;
	
	while(!pApJoiningRecord)
	{
		pApJoiningRecord = (struct AP_RECORD *)pvPortMalloc(sizeof(struct AP_RECORD ));
	}
	
	/* register message handle */
	wifiServiceCt.connectServiceMsgHandle = MessageRegister(WS_NUM_MESSAGE_QUEUE);

	wifiServiceCt.wifiConnectServiceContext.connectState = WIFI_IDLE;

	wifiServiceCt.connectServiceState = ServiceStateReady;
	wifiServiceHandle	= GetWifiMessageHandle();
	msgSend.msgId		= MSG_WIFI_CONNECT_SERVICE_INITED;
	msgSend.msgParams	= NULL;
	MessageSend(wifiServiceHandle, &msgSend);
	
	while(1)
	{
		MessageRecv(wifiServiceCt.connectServiceMsgHandle, &msgRecv, 0);

		if(msgRecv.msgId)
		{
			WifiConnectServiceMsgProcess(&msgRecv);
		}

		switch(wifiServiceCt.wifiConnectServiceContext.connectState)
		{
			case WIFI_IDLE:
				vTaskDelay(200);

				if(GetWifiConnectServiceState() == ServiceStateRunning)
				{
					msgSend.msgId		= MSG_WIFI_CONNECT_SERVICE_STOPPED;
					msgSend.msgParams	= NULL;
					MessageSend(wifiServiceHandle, &msgSend);
					SetWifiConnectServiceState(ServiceStateReady);
				}
				break;

			case WIFI_START:
				ReadNetRecord();
				if(wifiServiceCt.wifiConnectServiceContext.configLinkMode == MODE_SPECIFY_NET)
				{
					SetWifiConnectState(WIFI_JOIN_SPECIFY_NET);
				}
				else if((pApJoiningRecord->total_items == 0)||(pApJoiningRecord->total_items > 10)||(pApJoiningRecord->flag != AP_RECORD_FLAG)
					||(wifiServiceCt.wifiConnectServiceContext.configLinkMode == MODE_SMARTLINK)) 
				{
					if(pApJoiningRecord->flag != AP_RECORD_FLAG)
					{
						pApJoiningRecord->total_items = 0;
						pApJoiningRecord->current_item = 0;
					}
					SetWifiConnectState(WIFI_SMARTLINK);
				}
				else
				{
					join_cfg = (wifi_sta_join_cfg *)MALLOC(sizeof(wifi_sta_join_cfg));
					memset(join_cfg,0,sizeof(wifi_sta_join_cfg));
					SetWifiConnectState(WIFI_SCAN);
				}
				break;

			//wifi link mode: normal
			case WIFI_SCAN:
				set_scan_flag(0);
				Switch2STAmode();
				vTaskDelay(1000);
				ScanWifi();
	//			SoundRemind(SOUND_SSWL, 1);
				SetWifiConnectState(WIFI_SCAN_END);
				break;
				
			case WIFI_SCAN_END:
				if(get_scan_flag() == 0)
				{
					vTaskDelay(1000);
					DBG("Wait for scan\n");
				}
				else if(get_scan_flag() == 1)
				{
					DBG("Scan success\n");
					vTaskDelay(1500);//关键delay
					PrintfScanWifiResult();
					ap_count = ssv6xxx_get_aplist_info((void *)&ap_list);
					SetWifiConnectState(WIFI_JOIN);
					i = 0;
				}
				else if(get_scan_flag() == 2)
				{
					DBG("Scan fail\n");
					SetWifiConnectState(WIFI_SCAN);
				}
				break;

			case WIFI_JOIN:
				if(i >= pApJoiningRecord->total_items)
				{
					FREE((void *)ap_list);
					FREE(join_cfg);
					SetWifiConnectState(WIFI_SMARTLINK);
					break;
				}
		
				item = (i+pApJoiningRecord->current_item) % pApJoiningRecord->total_items;
				if(FindApInWifiList(item, ap_count, ap_list) == 1)
				{
					memcpy(join_cfg->ssid.ssid, (void *)&pApJoiningRecord->ssid_pwd[item].ssid[0],pApJoiningRecord->ssid_pwd[item].ssid_len);
					join_cfg->ssid.ssid_len = pApJoiningRecord->ssid_pwd[item].ssid_len;
					memcpy(join_cfg->password, (void *)&pApJoiningRecord->ssid_pwd[item].password, pApJoiningRecord->ssid_pwd[item].password_len);
					ret = netmgr_wifi_join_async(join_cfg);
					if (ret == 0)
					{
						set_connect_wifi_flag(0);
						SetWifiConnectState(WIFI_JOIN_END);
					}
				}
				i++;
		
				break;
			
			case WIFI_JOIN_END:
				if(get_connect_wifi_flag() == 0)
				{
					vTaskDelay(1000);
					DBG("Wait for connect wifi\n");
				}
				else if(get_connect_wifi_flag() == 1)
				{
					DBG("Connect wifi success\n");
		
					FREE((void *)ap_list);
					FREE(join_cfg);
					if(item != pApJoiningRecord->current_item)
					{
						pApJoiningRecord->current_item = item;
					}
					SetWifiConnectState(WIFI_CONNECT_AP);
				}
				else if(get_connect_wifi_flag() == 2)
				{
					DBG("Connect wifi fail\n");
					vTaskDelay(1000);
					SetWifiConnectState(WIFI_JOIN);
					i++;
				}
				break;

			//wifi link mode: link specify network  连接特定的网络
			case WIFI_JOIN_SPECIFY_NET:
				vTaskDelay(1000);
				ScanWifi();
				vTaskDelay(2000);
				JoinWifi(ssid_name, ssid_passwords);
				SetWifiConnectState(WIFI_JOIN_SPECIFY_NET_END);
				break;

			case WIFI_JOIN_SPECIFY_NET_END:
				if(get_connect_wifi_flag() == 0)
				{
					vTaskDelay(500);
					DBG("Wait for connect wifi\n");
				}
				else if(get_connect_wifi_flag() == 1)
				{
					DBG("Connect wifi success\n");
					SetWifiConnectState(WIFI_GET_IP);
				}
				else if(get_connect_wifi_flag() == 2)
				{
					DBG("Connect wifi fail\n");
					SetWifiConnectState(WIFI_JOIN_SPECIFY_NET);
				}
				break;
				
			//wifi link mode: smartlink
			case WIFI_SMARTLINK:
				vTaskDelay(1000);
				//SoundRemind(SOUND_SZWL, 1);
				set_connect_wifi_flag(0);
				set_sconfig_flag(0);
		
				if(pApJoiningRecord->total_items > TOTAL_WIFI)
					memset(pApJoiningRecord, 0, sizeof(struct AP_RECORD));
		
				if(Switch2SCONFIGmode() == 1)
				{
					//DBG("SCONFIG mode success\n");
					SetWifiConnectState(WIFI_SMARTLINK_CONFIG_END);
				}
				else
				{
					SetWifiConnectState(WIFI_SMARTLINK);
				}
				break;
				
			case WIFI_SMARTLINK_CONFIG_END:
				if(get_sconfig_flag() == 0)
				{
	//				SetLed5(1);
					vTaskDelay(500);
	//				SetLed5(0);
					vTaskDelay(500);
					DBG("Wait for smartlink\n");
				}
				else if(get_sconfig_flag() == 1)
				{
					DBG("Smatlink success\n");
					SetWifiConnectState(WIFI_SMARTLINK_JOIN_END);
				}
				else if(get_sconfig_flag() == 2)
				{
					DBG("Smartlink fail\n");
					SetWifiConnectState(WIFI_SMARTLINK);
				}
				break;
			
			case WIFI_SMARTLINK_JOIN_END:
				if(get_connect_wifi_flag() == 0)
				{
					vTaskDelay(500);
					DBG("Wait for connect wifi\n");
				}
				else if(get_connect_wifi_flag() == 1)
				{
					DBG("Connect wifi success\n");
					SetWifiConnectState(WIFI_CONNECT_AP);
				}
				else if(get_connect_wifi_flag() == 2)
				{
					DBG("Connect wifi fail\n");
					SetWifiConnectState(WIFI_SMARTLINK);
				}
				break;

			
			case WIFI_CONNECT_AP:
				BurnNetRecord();
				TimeOutSet(&GetIPWaitTimer,45*1000);
				SetWifiConnectState(WIFI_GET_IP);
				break;
			
			case WIFI_GET_IP:
				if(GetNetifStatus() == 0)
	            {
	                if(IsTimeOut(&GetIPWaitTimer))
	                {
	                    //SoundRemind(SOUND_LJSB,1);
	                    SetWifiConnectState(WIFI_IDLE);
	                    break;
	                }
	                vTaskDelay(200);
	                DBG("Getting ip address\n");
	            }
	            else
	            {
	                DBG("Get ip success\n");
	                addr=GetIpAdress();
	                DBG("IP=%d.%d.%d.%d\n",addr&0xFF,(addr>>8)&0xFF,(addr>>16)&0xFF,(addr>>24)&0xFF);
	                //SoundRemind(SOUND_LWCG,1);
	                SetWifiConnectState(WIFI_CONNECTED);
	            }
				break;
				
			case WIFI_CONNECTED:
				vTaskDelay(200);

				if(GetWifiConnectServiceState() == ServiceStateReady)
				{
					msgSend.msgId		= MSG_WIFI_CONNECT_SERVICE_STARTED;
					msgSend.msgParams	= NULL;
					MessageSend(wifiServiceHandle, &msgSend);
					SetWifiConnectServiceState(ServiceStateRunning);
				}
				break;
				
			case WIFI_UPGRADE:
				break;
				
		}
	}
}

static void WifiConnectServiceTaskCreate(void)
{
	xTaskCreate(WifiConnectServiceEntrance,
				wifiConnectServiceTaskName,
				WIFI_CONNECT_SERVICE_TASK_STACK_SIZE,
				NULL,
				WIFI_CONNECT_SERVICE_TASK_PRIO,
				&wifiServiceCt.connectServiceTaskHandle);
}

/***************************************************************************************
 *
 * wifi service
 *
 */
//init ssv device
static void WifiService_Init(MessageHandle parentMsgHandle)
{
	//给wifi协议栈分配内存
	memp_memory = pvPortMalloc(MEMP_MEMORY_LEN);
	
	NVIC_SetPriority(GPIO_IRQn, GPIO_INT_PRIO);
	
	SelectWifiInSdioMode();
	
	ssv6xxx_dev_init(0,NULL);

	memset(&wifiServiceCt, 0, sizeof(wifiServiceCt));

	/* register message handle */
	wifiServiceCt.msgHandle = MessageRegister(WS_NUM_MESSAGE_QUEUE);
	wifiServiceCt.parentMsgHandle = parentMsgHandle;
}

static void SetWifiServiceState(ServiceState state)
{
	wifiServiceCt.serviceState = state;
}

static void WifiServiceEntrance(void * param)
{
	MessageContext		msgRecv;
	MessageContext		msgSend;

	//wifi ConnectService tast create
	WifiConnectServiceTaskCreate();

	while(1)
	{
		MessageRecv(wifiServiceCt.msgHandle, &msgRecv, MAX_RECV_MSG_TIMEOUT);

		switch(msgRecv.msgId)
		{		
			//main task msg
			case MSG_SERVICE_START:
				if(wifiServiceCt.serviceState == ServiceStateReady)
				{
					if(GetWifiConnectServiceState() == ServiceStateRunning)
					{
						wifiServiceCt.serviceState = ServiceStateRunning;
						msgSend.msgId		= MSG_SERVICE_STARTED;
						msgSend.msgParams	= MSG_PARAM_WIFI_SERVICE;
						MessageSend(wifiServiceCt.parentMsgHandle, &msgSend);
						DBG("Wifi service start\n");
					}
					else
					{
						msgSend.msgId		= MSG_WIFI_CONNECT_SERVICE_START;
						msgSend.msgParams	= NULL;
						MessageSend(wifiServiceCt.parentMsgHandle, &msgSend);
						DBG("Wifi ConnectService task start\n");
					}
				}
				break;
			case MSG_SERVICE_STOP:
				if(wifiServiceCt.serviceState == ServiceStateRunning)
				{
					if(GetWifiConnectServiceState() == ServiceStateRunning)
					{
						msgSend.msgId		= MSG_WIFI_CONNECT_SERVICE_STOP;
						msgSend.msgParams	= NULL;
						MessageSend(wifiServiceCt.parentMsgHandle, &msgSend);
						DBG("Wifi ConnectService task stop\n");
					}
					else
					{
						wifiServiceCt.serviceState = ServiceStateReady;
						msgSend.msgId		= MSG_SERVICE_STOPPED;
						msgSend.msgParams	= MSG_PARAM_WIFI_SERVICE;
						MessageSend(wifiServiceCt.parentMsgHandle, &msgSend);
						DBG("Wifi service stopped\n");
					}
				}
				break;

			//ConnectService task msg
			case MSG_WIFI_CONNECT_SERVICE_INITED:
				if(GetWifiConnectServiceState() == ServiceStateReady)
				{
					wifiServiceCt.serviceState = ServiceStateReady;
					msgSend.msgId		= MSG_SERVICE_CREATED;
					msgSend.msgParams	= MSG_PARAM_WIFI_SERVICE;
					MessageSend(wifiServiceCt.parentMsgHandle, &msgSend);
					DBG("wifi service inited \n");
				}
				break;

			case MSG_WIFI_CONNECT_SERVICE_STARTED:
				if((GetWifiConnectServiceState() == ServiceStateRunning) && 
					(wifiServiceCt.serviceState == ServiceStateReady))
				{
					wifiServiceCt.serviceState = ServiceStateRunning;
					msgSend.msgId		= MSG_SERVICE_STARTED;
					msgSend.msgParams	= MSG_PARAM_WIFI_SERVICE;
					MessageSend(wifiServiceCt.parentMsgHandle, &msgSend);
					DBG("wifi service started \n");
				}
				break;
				
			case MSG_WIFI_CONNECT_SERVICE_STOPPED:
				if((GetWifiConnectServiceState() == ServiceStateReady) && 
					(wifiServiceCt.serviceState == ServiceStateRunning))
				{
					wifiServiceCt.serviceState = ServiceStateReady;

					msgSend.msgId		= MSG_SERVICE_STOPPED;
					msgSend.msgParams	= MSG_PARAM_WIFI_SERVICE;
					MessageSend(wifiServiceCt.parentMsgHandle, &msgSend);
					DBG("wifi service stopped \n");
				}
				break;
			
			default:
				break;
		}
	}
}

/***************************************************************************************
 *
 * APIs
 *
 */
	

MessageHandle GetWifiMessageHandle(void)
{
	return wifiServiceCt.msgHandle;
}

ServiceState GetWifiServiceState(void)
{
	return wifiServiceCt.serviceState;
}

int32_t WifiServiceCreate(MessageHandle parentMsgHandle)
{
	WifiService_Init(parentMsgHandle);
	xTaskCreate(WifiServiceEntrance, 
				wifiServiceName, 
				WIFI_SERVICE_SIZE, 
				NULL, 
				WIFI_SERVICE_PRIO, 
				&wifiServiceCt.taskHandle);
	return 0;
}


int32_t WifiServiceStart(void)
{
	MessageContext		msgSend;

	msgSend.msgId		= MSG_SERVICE_START;
	msgSend.msgParams	= NULL;
	MessageSend(wifiServiceCt.msgHandle, &msgSend);
}

/**
 * @brief
 *		Exit audio core service.
 * @param
 * 	 NONE
 * @return  
 */
void WifiServiceStop(void)
{
	MessageContext		msgSend;

	msgSend.msgId		= MSG_SERVICE_STOP;
	msgSend.msgParams	= NULL;
	MessageSend(wifiServiceCt.msgHandle, &msgSend);
}


/**
 * @brief
 *		
 * @param
 * 	 NONE
 * @return  
 */
void WifiServiceKill(void)
{
	if(wifiServiceCt.connectServiceTaskHandle)
		vTaskDelete(wifiServiceCt.connectServiceTaskHandle);
		
	if(wifiServiceCt.taskHandle)
		vTaskDelete(wifiServiceCt.taskHandle);
}

