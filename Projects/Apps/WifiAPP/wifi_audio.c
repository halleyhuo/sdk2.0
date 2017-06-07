/**
 **************************************************************************************
 * @file    wifi_audio.c
 * @brief   Wifi audio player 
 *
 * @author  Peter
 * @version V1.0.0
 *
 * $Created: 2017-03-06 10:06:47$
 *
 * @Copyright (C) 2017, Shanghai Mountain View Silicon Co.,Ltd. All rights reserved.
 **************************************************************************************
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

unsigned char temp_buffer[1024];
unsigned char recv_buffer[1024*4];
char WifiStreamReady = 0;
MemHandle WifiStreamHandle;

extern void AudioDecoderTask(void);
extern void ClientTask(void);
extern uint32_t get_ipadress(void);
extern void SCONFIGmode_default();

uint32_t get_ipadress(void)
{
	ipinfo info;
	netmgr_ipinfo_get(WLAN_IFNAME, &info);
	return info.ipv4;
}

void WeixinCloudTask(void);

void StartWifiaudioTask(void)
{
	uint32_t addr;
	
	smart_link_netc(0);

	while(netif_status_get() == 0)
	{
		vTaskDelay(1000);
		wifi_audio_debug("Getting ip address\n");
	}
	wifi_audio_debug("Get ip success\n");
	
	addr=get_ipadress();
	wifi_audio_debug("IP=%d.%d.%d.%d\n",addr&0xFF,(addr>>8)&0xFF,(addr>>16)&0xFF,(addr>>24)&0xFF);
	
	xTaskCreate(AudioDecoderTask, "AudioDecoder", 256, NULL, 2, NULL);
	xTaskCreate(ClientTask, "Client", 256, NULL, 3, NULL );
	xTaskCreate(WeixinCloudTask, "WeixinCloud", 1024, NULL, 3, NULL );
	vTaskDelete(NULL);
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
		wifi_audio_debug("IPµØÖ·%ld.%ld.%ld.%ld\r\n",(ip&0x000000ff),(ip&0x0000ff00)>>8,(ip&0x00ff0000)>>16,(ip&0xff000000)>>24);
		sprintf(addr,"%d.%d.%d.%d",(ip&0x000000ff),(ip&0x0000ff00)>>8,(ip&0x00ff0000)>>16,(ip&0xff000000)>>24);
	
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
	
		WifiStreamHandle.addr         = SDRAM_BASE_ADDR + (SDRAM_SIZE/2);
		WifiStreamHandle.mem_capacity = SDRAM_SIZE/2;
		WifiStreamHandle.p            = 0;
		WifiStreamHandle.mem_len      = 0;

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
		mv_mwrite(temp_buffer, 1, len, &WifiStreamHandle);
		buflen +=len;
		wifi_audio_debug("%s\n",temp_buffer);
	
		parser_http(&temp_buffer[0], len, &head_len, &data_len);
	
		wifi_audio_debug("head_len%d\n",head_len);
	
		while(buflen < (head_len+data_len))
		{
			if(sever_task_recv_data_flag==1)
			{
				break;
			}
			if(mv_mremain(&WifiStreamHandle) < 20*1024)
			{
				vTaskDelay(10);
			}
			else
			{
				buflen += len = wifi_read(sock, temp_buffer, 1024, 4000);
				wifi_audio_debug("%d\n",len);
				if(len < 0)
				{
					break;
				}
				mv_mwrite(temp_buffer, 1, len, &WifiStreamHandle);
				vTaskDelay(5);
			}
			if(!WifiStreamReady && mv_msize(&WifiStreamHandle) > 2 * 1024)
			{
				//wifi_audio_debug("123123\n");
				WifiStreamReady = 1;
				vTaskDelay(10);
			}
		}
		close(sock);
	}
}

#include "clk.h"
#include "dac.h"
#include "chip_info.h"
#include "audio_path.h"
#include "pcm_fifo.h"
#include "pcm_transfer.h"

char xr_start_flag = 0;
char tx_start_flag = 0;

void AudioDecoderTask(void)
{
	/* DAC initialization */
	CodecDacInit(TRUE);
	CodecDacMuteSet(TRUE, TRUE);
	CodecDacChannelSel(DAC_CH_DECD_L | DAC_CH_DECD_R);
	DacVolumeSet(0x50, 0x50);
	DacNoUseCapacityToPlay();
	DacConfig(MDAC_DATA_FROM_DEC, USB_MODE);
	/* PCMFIFO_MIX_DACOUT */
	PhubPathSel(PCMFIFO_MIX_DACOUT);
	CodecDacMuteSet(FALSE, FALSE);
	
	while(!WifiStreamReady)
	{
		vTaskDelay(10);
	}
	
	while(1)
	{
		wifi_audio_debug("Start audio decoder initialization.\n");
	
		if(RT_SUCCESS == audio_decoder_initialize((uint8_t*)VMEM_ADDR + 11* 1024, &WifiStreamHandle, IO_TYPE_MEMORY, MP3_DECODER))
		{
			wifi_audio_debug("Audio decoder initialize successed, SampleRate@%dHz.\n", audio_decoder->song_info->sampling_rate);
	
			PcmTxInitWithDefaultPcmFifoSize((PCM_DATA_MODE)audio_decoder->song_info->pcm_data_mode);
			PcmFifoInitialize(PCM_FIFO_OFFSET, PCM_FIFO_SIZE, 0, 0);
	
			DacAdcSampleRateSet(audio_decoder->song_info->sampling_rate, USB_MODE);
	
			xr_start_flag = 0;
			tx_start_flag = 0;
	
			NVIC_EnableIRQ(DECODER_IRQn);
	
			while(RT_YES == audio_decoder_can_continue())
			{
				if(xr_start_flag)
				{
					if(is_audio_decoder_with_hardware())
					{
						vTaskDelay(10);
						continue;
					}
					else
					{
						xr_start_flag = 0;
						audio_decoder_start_pcm_transfer();
						tx_start_flag = 1;
					}
				}
	
				if(tx_start_flag)
				{
					vTaskDelay(2);
					continue;
				}
	
				if(RT_SUCCESS == audio_decoder_decode())
				{
					xr_start_flag = 1;
				}
			}
		}
		else
		{
			wifi_audio_debug("Audio decoder initialize failed.\n");
		}
	}
}

void audio_decoder_interrupt_callback(int32_t intterupt_type)
{
	if(intterupt_type == 0)//XR_DONE
	{
		xr_start_flag = 0;
		audio_decoder_start_pcm_transfer();
		tx_start_flag = 1;
	}
	
	if(intterupt_type == 1)//TX_DONE
	{
		tx_start_flag = 0;
	}
}

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