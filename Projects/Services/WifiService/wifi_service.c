/**
 **************************************************************************************
 * @file    wifi_manager.c
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

/***************************************************************************************
 *
 * External defines
 *
 */
extern uint8_t *memp_memory;


/***************************************************************************************
 *
 * External defines
 *
 */

 
#define WIFI_SERVICE_SIZE				1024
#define WIFI_SERVICE_PRIO				3
	
#define WIFI_SERVICE_TIMEOUT				1	/* 1 ms */

#define WS_NUM_MESSAGE_QUEUE			10

void ClientTask(void);

/***************************************************************************************
 *
 * Internal defines
 *
 */
#define INIT_SSV_TASK_STACK_SIZE		1024*8
#define INIT_SSV_TASK_PRIO				3
	
#define START_AUDIO_TASK_STACK_SIZE		1024
#define START_AUDIO_TASK_PRIO			3
	
#define MEMP_MEMORY_LEN					200*1024
	
#define GPIO_INT_PRIO					2
	
typedef struct _WifiServiceContext
{
	xTaskHandle 		taskHandle;
	MessageHandle		msgHandle;
	ServiceState		serviceState;
}WifiServiceContext;

/** WIFI servcie name*/
const char wifiServiceName[]		= "WifiService";


/***************************************************************************************
 *
 * Internal varibles
 *
 */
static WifiServiceContext		wifiServiceCt;

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


static void WifiDeviceInit(void)
{
	uint32_t addr;
	vTaskDelay(1000);
	cmd_wifi_scan();
	vTaskDelay(2000);
	cmd_wifi_join();

	/* 用于airkiss或smartlink连接wifi */
//	SCONFIGmode_default();

	while(netif_status_get() == 0)
	{
		vTaskDelay(1000);
	}
	
	addr=get_ipadress();
}


static void WifiServiceEntrance(void * param)
{
	MessageContext		msgRecv;
	MessageContext		msgSend;
	MessageHandle		mainHandle;


	/* register message handle */
	wifiServiceCt.msgHandle = MessageRegister(WS_NUM_MESSAGE_QUEUE);

	wifiServiceCt.serviceState = ServiceStateReady;

	/* Send message to main app */
	mainHandle = GetMainMessageHandle();
	msgSend.msgId		= MSG_SERVICE_CREATED;
	msgSend.msgParams	= MSG_PARAM_WIFI_SERVICE;
	MessageSend(mainHandle, &msgSend);

	while(1)
	{
		MessageRecv(wifiServiceCt.msgHandle, &msgRecv, WIFI_SERVICE_TIMEOUT);
		switch(msgRecv.msgId)
		{
			case MSG_SERVICE_START:
				if(wifiServiceCt.serviceState == ServiceStateReady)
				{
					wifiServiceCt.serviceState = ServiceStateRunning;
					msgSend.msgId		= MSG_SERVICE_STARTED;
					msgSend.msgParams	= MSG_PARAM_WIFI_SERVICE;
					MessageSend(mainHandle, &msgSend);
					DBG("Wifi service start\n");
					xTaskCreate(ClientTask, "Client", 256, NULL, 3, NULL );
				}
				break;
			case MSG_SERVICE_STOP:
				if(wifiServiceCt.serviceState == ServiceStateRunning)
				{
					wifiServiceCt.serviceState = ServiceStateReady;
					msgSend.msgId		= MSG_SERVICE_STOPPED;
					msgSend.msgParams	= MSG_PARAM_WIFI_SERVICE;
					MessageSend(mainHandle, &msgSend);
				}

				break;
			default:
				break;
		}
	}
}

static void InitSSVDeviceTask (void)
{
	memp_memory = pvPortMalloc(MEMP_MEMORY_LEN);
	
	NVIC_SetPriority(GPIO_IRQn, GPIO_INT_PRIO);
	
	SelectWifiInSdioMode();
	
	ssv6xxx_dev_init(0,NULL);

	WifiDeviceInit();

	xTaskCreate(WifiServiceEntrance, wifiServiceName, WIFI_SERVICE_SIZE, NULL, WIFI_SERVICE_PRIO, &wifiServiceCt.taskHandle);
	vTaskDelete(NULL);
	while(1);
	
}


/***************************************************************************************
 *
 * APIs
 *
 */


MessageHandle GetWifiAudioServiceMsgHandle(void)
{
	return wifiServiceCt.msgHandle;
}

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

	xTaskCreate((TaskFunction_t)InitSSVDeviceTask,
				"InitSSVDeviceTask",
				INIT_SSV_TASK_STACK_SIZE,
				NULL,
				INIT_SSV_TASK_PRIO,
				NULL );
	return 0;
}


void WifiServiceStart(void)
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
	vTaskDelete(wifiServiceCt.taskHandle);
}






























/***************************************************************************************
 *
 * from wifi_audio.c
 *
 */
#include "sockets.h"
#include <os_wrapper.h>
#include <log.h>
#include <host_apis.h>
#include <cli/cmds/cli_cmd_wifi.h>
#include <httpserver_raw/httpd.h>
#include <SmartConfig/SmartConfig.h>
#include <net_mgr.h>
#include "audio_utility.h"
#include "audio_decoder.h"
#include "app_config.h"


#define wifi_audio_debug(format, ...)		printf(format, ##__VA_ARGS__)
static int buflen;

//const char s_1[] = "GET /group4/M00/11/32/wKgDs1MnylzSREmkABssQfEbOng678.mp3 HTTP/1.1\r\n";
const char s_1[] = "GET /group8/M02/63/6D/wKgDYFXZ08yQ2D2tANIQkbsykWo940.mp3 HTTP/1.1\r\n";

const char s_2[] = "Accept-Language: zh-cn\r\n";
//const char s_2[] = "User-Agent: MVNET-HTTP/1.0\r\n\r\n";
const char s_3[] = "User-Agent: Mozilla/4.0 (compatible; MSIE 5.01; Windows NT 5.0)\r\n";
const char s_4[] = "RANGE: bytes=0-\r\n";
const char s_5[] = "UA-CPU: AMD64\r\n";
const char s_6[] = "Accept-Encoding: gzip, deflate\r\n";
const char s_7[] = "Host: fdfs.xmcdn.com\r\n";
const char s_8[] = "Connection: Keep-Alive\r\n\r\n";


//http://audio.xmcdn.com/group16/M02/46/74/wKgDbFWnc96i7cw8AFjdSVxOqow739.m4a

/*

const char s_1[] = "GET /sine.mp3 HTTP/1.1\r\n";
const char s_2[] = "Accept-Language: zh-CN,zh;q=0.8\r\n";
const char s_3[] = "User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/53.0.2785.104 Safari/537.36 Core/1.53.2372.400 QQBrowser/9.5.10548.400\r\n";
const char s_4[] = "RANGE: bytes=0-\r\n";
const char s_5[] = "UA-CPU: AMD64\r\n";
const char s_6[] = "Accept-Encoding: gzip, deflate, sdch\r\n";
const char s_7[] = "Host: 192.168.1.210\r\n";
const char s_8[] = "Connection: Keep-Alive\r\n\r\n";
*/


unsigned char temp_buffer[1024];
unsigned char recv_buffer[1024*4];
char WifiStreamReady = 0;
MemHandle * WifiStreamHandle;

extern void AudioDecoderTask(void);
extern uint32_t get_ipadress(void);
extern void SCONFIGmode_default();


uint32_t get_ipadress(void)
{
	ipinfo info;
	netmgr_ipinfo_get(WLAN_IFNAME, &info);
	return info.ipv4;
}

uint8_t sever_task_buffer[256],sever_task_recv_data_flag=0;

void parser_http(uint8_t *buf, uint32_t buf_len, uint32_t *phead_len, uint32_t *pdata_len)
{
	uint32_t len = 0;
	while(len < buf_len)
	{
		if(buf[len++] == '\n')
		{
			if(memcmp(&buf[len],"Content-Length",14) == 0)
			{
				len += 16;
				sscanf(&buf[len],"%d",pdata_len);
				wifi_audio_debug("datalen=%d\n",*pdata_len);
				break;
			}
		}
	}
	
	len+=4;
	while(len < buf_len)
	{
		if(buf[len++] == '\r')
		{
			if(buf[len+1] == '\r')
			{
				len+=3;
				*phead_len = len;
				wifi_audio_debug("headlen=%d\n",len);
				break;
			}
		}
	}
}

int app_tcp_recv(int socket, char *buf, uint32_t size, uint32_t timeout)
{
	int ret;
	fd_set rfds;
	struct timeval tmo;
	tmo.tv_sec = timeout/1000;
	timeout = timeout%1000;
	tmo.tv_usec = timeout*1000;
	
	FD_ZERO(&rfds);
	FD_SET(socket, &rfds);
	ret = select(socket+1, &rfds, NULL, NULL, &tmo);
	if(ret != 0)
	{
		if(FD_ISSET(socket, &rfds))
		{
			ret = recv( socket, buf, size, 0);
			if(ret < 0)
			{
				return -1;
			}
			else
			{
				return ret;
			}
		}
	}
	return 0;
}

int16_t wifi_read(int32_t sock,uint8_t *temp_buffer,uint16_t recv_len,uint32_t timeout)
{

	uint16_t len,nodata;
	len = 0;
	nodata = 0;
	timeout /= 100;
	while(len == 0)
	{
		len = app_tcp_recv(sock,temp_buffer,recv_len,0);
		if(len != 0)
		{
			break;
		}
		vTaskDelay(100);
//		wifi_audio_debug("wifi_read: Wait data %d\n",nodata);
		nodata++;
		if(nodata > timeout)
		{
			break;
		}
	}
	return len;
}

uint8_t addr[64];

void ClientTask(void)
{
	int sock, ip, len;
	uint32_t data_len, head_len;
	struct sockaddr_in address, remotehost;
	struct ip_addr DNS_Addr;
	
	while(1)
	{
	
		if(netconn_gethostbyname("fdfs.xmcdn.com", &DNS_Addr) != 0)
		{
			wifi_audio_debug("Get fdfs.xmcdn.com ip address fail\n");
			continue;
		}
		
		ip = DNS_Addr.addr;
		memset(addr,0,50);
		wifi_audio_debug("IP地址%ld.%ld.%ld.%ld\r\n",(ip&0x000000ff),(ip&0x0000ff00)>>8,(ip&0x00ff0000)>>16,(ip&0xff000000)>>24);
		sprintf(addr,"%d.%d.%d.%d",(ip&0x000000ff),(ip&0x0000ff00)>>8,(ip&0x00ff0000)>>16,(ip&0xff000000)>>24);
//		sprintf(addr,"%d.%d.%d.%d",192,168,1,210);
	
		/* create a TCP socket */
		if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		{
			wifi_audio_debug("Client: Create socket fail\n");
			continue;
		}
	
		/* bind to port 80 at any interface */
		memset(&address,0,sizeof(struct sockaddr_in));
		address.sin_family = AF_INET;
		address.sin_port = htons(80);
		//address.sin_addr.s_addr = inet_addr("112.253.38.95");
		address.sin_addr.s_addr = inet_addr(addr);
	
		if(connect(sock,(struct sockaddr *)&address, sizeof (address))<0)
		{
			wifi_audio_debug("Connect fdfs.xmcdn.com fail\n");
			continue;
		}
		wifi_audio_debug("Connect fdfs.xmcdn.com success\n");
		WifiStreamHandle = GetWifiAudioPlayDecoderBuffer();
		write(sock, s_1, sizeof(s_1)-1);
		write(sock, s_2, sizeof(s_2)-1);
		write(sock, s_3, sizeof(s_3)-1);
		// write(sock, s_4, sizeof(s_4)-1);
		write(sock, s_5, sizeof(s_5)-1);
		write(sock, s_6, sizeof(s_6)-1);
		write(sock, s_7, sizeof(s_7)-1);
		write(sock, s_8, sizeof(s_8)-1);
	
		buflen = 0;
		len = read(sock,&temp_buffer[0],1024);
		
		buflen +=len;
		wifi_audio_debug("%d\n",len);
	
		parser_http(&temp_buffer[0], len, &head_len, &data_len);

		mv_mwrite(&temp_buffer[head_len], 1, len - head_len, WifiStreamHandle);
	
		wifi_audio_debug("head_len%d\n",head_len);
	
		while(buflen < (head_len+data_len))
		{

			if(mv_mremain(WifiStreamHandle) < 20*1024)
			{
				vTaskDelay(10);
			}
			else
			{
				buflen += len = wifi_read(sock, temp_buffer, 1024, 4000);
				//wifi_audio_debug("%d\n",len);
				if(len < 0)
				{
					break;
				}
				mv_mwrite(temp_buffer, 1, len, WifiStreamHandle);
				vTaskDelay(5);
			}
/*
			if(!WifiStreamReady && mv_msize(&WifiStreamHandle) > 2 * 1024)
			{
				//wifi_audio_debug("123123\n");
				WifiStreamReady = 1;
				vTaskDelay(10);
			}
*/
		}
		close(sock);
		while(1)
			vTaskDelay(10);
	}
}

/*

void FileClose()
{
	printf("FileClose\n");
}
void FileEOF()
{
	printf("FileEOF\n");
}
void FileRead()
{
	printf("FileRead\n");
}
void FileSeek()
{
	printf("FileSeek\n");
}
void FileSof()
{
	printf("FileSof\n");
}
void FileTell()
{
	printf("FileTell\n");
}
void FileWrite()
{
	printf("FileWrite\n");
}
*/
