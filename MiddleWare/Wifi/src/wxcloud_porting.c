/**
 **************************************************************************************
 * @file    wxcloud_porting.c
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
#include "wifi_api.h"






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


/***************************************************************************************
 *
 * Internal varibles
 *
 */




/***************************************************************************************
 *
 * Internal functions
 *
 */


static void WxcloudResponseCb(uint32_t hashCode, uint32_t errCode, uint32_t funcId, const uint8_t* body, uint32_t bodyLen)
{

}
static void WxcloudEventCb(EventValue eventValue)
{

}


static void WxcloudNotifyCb(uint32_t funcId, const uint8_t* body, uint32_t bodyLen)
{
	
}

static void WxcloudSubDevNotifyCb(const uint8_t* subDevId, uint32_t funcId, const uint8_t* body, uint32_t bodyLen)
{
	
}




/***************************************************************************************
 *
 * APIs
 *
 */



int airkiss_printfImp(const char *fmt, ...)
{
	va_list		args;
	int 		ret_val;


	va_start(args, fmt);
	ret_val = vprintf(fmt, args);
	va_end(args);

	return ret_val;;
}

int airkiss_mutex_create(ak_mutex_t *mutex_ptr)
{
	mutex_ptr->xSemaphore = xSemaphoreCreateMutex();
	if ( mutex_ptr->xSemaphore == NULL )
		return 1;
	else
		return 0;
}

int airkiss_mutex_lock(ak_mutex_t *mutex_ptr)
{
	xSemaphoreTake(mutex_ptr->xSemaphore, 0xffffffff);

	return 0;
}

int airkiss_mutex_unlock(ak_mutex_t *mutex_ptr)
{
	xSemaphoreGive( mutex_ptr->xSemaphore );

	return 0;
}

int airkiss_mutex_delete(ak_mutex_t *mutex_ptr)
{
	vSemaphoreDelete( mutex_ptr->xSemaphore );

	return 0;
}

int airkiss_dns_gethost(char* url, uint32_t* ipAddr)
{
	struct ip_addr		dnsAddr;
	uint8_t				tempIpAddr[IP_ADDRESS_LENGTH];

	if(netconn_gethostbyname(url, &dnsAddr) == 0)
	{
		*ipAddr	=  ((dnsAddr.addr>>24)&0xFF)<<0;
		*ipAddr += ((dnsAddr.addr>>16)&0xFF)<<8;
		*ipAddr += ((dnsAddr.addr>>8)&0xFF)<<16;
		*ipAddr += ((dnsAddr.addr>>0)&0xFF)<<24;

		return 0;
	}
	else
	{
		memset(tempIpAddr,0,IP_ADDRESS_LENGTH);
		if(ResolveIP(url, tempIpAddr) == 1)
		{
			*ipAddr = ConvertInetAddrToAddr(tempIpAddr);
			return 0;
		}
		else
		{
			return -1;
		}
	}
}

int airkiss_dns_checkstate(uint32_t* ipAddr)
{
	return -1;
}

ak_socket airkiss_tcp_socket_create()
{
	ak_socket		sock;

	if ((sock = SocketOpen(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		return -1;
	}

	return sock;
}

int airkiss_tcp_connect(ak_socket sock, char* ipaddr, uint16_t port)
{
	struct sockaddr_in		address;


	memset(&address,0,sizeof(struct sockaddr_in));
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	address.sin_addr.s_addr = inet_addr(ipaddr);

	if(SocketConnect(sock,(struct sockaddr *)&address, sizeof (address))<0)
	{
		return -1;
	}

	return 0;
}

int airkiss_tcp_checkstate(ak_socket sock)
{
	return -1;
}

int airkiss_tcp_send(ak_socket socket, char*buf, uint32_t len)
{
	int ret;

	ret = SocketWrite(socket, buf,len);

	return ret;
}

void airkiss_tcp_disconnect(ak_socket socket)
{
	SocketClose(socket);
}

int airkiss_tcp_recv(ak_socket socket, char *buf, uint32_t size, uint32_t timeout)
{
	return (int)WifiRecv(socket, buf, size, timeout);
}

uint32_t airkiss_gettime_ms()
{
	return gSysTick;
}




