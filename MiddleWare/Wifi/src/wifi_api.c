/**
 **************************************************************************************
 * @file    wifi_api.c
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
#include "sockets.h"
#include <net_mgr.h>


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

#define HTTP_PORT						80

#define TEMP_MALLOC_SIZE				2048

#define GET_IP_RESOLVE_TIMEOUT			3000

/***************************************************************************************
 *
 * Internal varibles
 *
 */

const char dnsPodGet[] = "Accept: image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, */*\r\nUser-Agent: Mozilla/4.0 (compatible; MSIE 5.5; Windows 98)\r\nHost: www.dnspod.cn\r\nConnection: Keep-Alive\r\nCache-Control: no-cache\r\n\r\n";


/***************************************************************************************
 *
 * Internal functions
 *
 */
 
static WifiStatus ResolveIPFromDNSPOD(uint8_t *url, IP_ADDR *ipAddr)
{
	int						ip,sock,nodata;
	int16_t					len,i,j;
	struct ip_addr			dnsAddr;
	struct sockaddr_in		address;
	uint8_t					*temp = NULL;



	temp = pvPortMalloc(TEMP_MALLOC_SIZE);
	if(temp == NULL)
	{
		return WIFI_STATUS_FAILED;
	}

	if(netconn_gethostbyname("www.dnspod.cn",&dnsAddr) != 0)
	{
		dnsAddr.addr = 0x6738B1A3;
	}

	ip = dnsAddr.addr;

	memset(temp,0,IP_ADDRESS_LENGTH);

	sprintf(temp,"%d.%d.%d.%d",(ip&0x000000ff),(ip&0x0000ff00)>>8,(ip&0x00ff0000)>>16,(ip&0xff000000)>>24);

	/* create a TCP socket */
	if ((sock = SocketOpen(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		vPortFree(temp);
		return WIFI_STATUS_FAILED;
	}

	/* bind to port 80 at any interface */
	memset(&address, 0, sizeof(struct sockaddr_in));
	address.sin_family = AF_INET;
	address.sin_port = htons(HTTP_PORT);
	address.sin_addr.s_addr = inet_addr(temp);


	if(SocketConnect(sock,(struct sockaddr *)&address, sizeof (address)) < 0)
	{
		close(sock);
		vPortFree(temp);
		return WIFI_STATUS_FAILED;
	}

	memset(temp, 0, TEMP_MALLOC_SIZE);
	sprintf(temp,"GET /Httpdns/Query?dn=%s HTTP/1.1\r\n%s", url, dnsPodGet);
	WifiSend(sock, temp, strlen(temp),0);
	memset(temp,0,TEMP_MALLOC_SIZE);

	len = WifiRecv(sock, temp, TEMP_MALLOC_SIZE, GET_IP_RESOLVE_TIMEOUT);
	close(sock);

	if(len <= 0)
	{
		vPortFree(temp);
		return WIFI_STATUS_FAILED;
	}

	printf("%s\n", temp);
	for(i = len-10; i > 10; i--)
	{
		if((temp[i-3]=='"')&&(temp[i-2]=='i')&&(temp[i-1]=='p')&&(temp[i]=='"'))
		{
			i += 3;
			j = i;
			while(temp[j] != '"')
			{
				j++;
			}
			memcpy(ipAddr->ipAddrStr, &temp[i], j-i);
			vPortFree(temp);
			return WIFI_STATUS_SUCCESS;
		}
	}

	vPortFree(temp);

	return WIFI_STATUS_FAILED;
}

/***************************************************************************************
 *
 * APIs
 *
 */




/**
* @brief
* 	 Connect to a URL
*
* @param
* 	 url	 URL
* 	 sock	 Socket for this link
*
* @return
* 	 WIFI_STATUS_SUCCESS or WIFI_STATUS_FAILED
*/
WifiStatus WifiConnectURL(uint8_t *url, int32_t *sock, int32_t port)
{
	IP_ADDR		ipAddress;

	memset(&ipAddress.ipAddrStr[0], 0, sizeof(IP_ADDR));
	if(ResolveIP(url, &ipAddress.ipAddrStr[0]) == WIFI_STATUS_SUCCESS)
	{
		return WifiConnectIP(&ipAddress.ipAddrStr[0], sock, port);
	}

	return WIFI_STATUS_FAILED;

}



/**
* @brief
* 	 Connect to a IP address
*
* @param
*		ipAddr 	 IP address in char type. "192.168.1.1"
*		wifiSock	 Socket for this link
*		port
*
* @return
* 	 WIFI_STATUS_SUCCESS or WIFI_STATUS_FAILED
*/
WifiStatus WifiConnectIP(IP_ADDR* ipAddr, int32_t *wifiSock, int32_t port)
{
	int sock;
	struct sockaddr_in address;

	/* create a TCP socket */
	if ((sock = SocketOpen(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		return WIFI_STATUS_FAILED;
	}

	/* bind to port 80 at any interface */
	memset(&address,0,sizeof(struct sockaddr_in));
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	address.sin_addr.s_addr = inet_addr(ipAddr->ipAddrStr);

	if(SocketConnect(sock,(struct sockaddr *)&address, sizeof (address)) < 0)
	{
		close(sock);
		return WIFI_STATUS_FAILED;
	}

	*wifiSock = sock;

	return WIFI_STATUS_SUCCESS;
}


/**
* @brief
* 	 Receive data from wifi link
*
* @param
* 	 socket 	 Socket created by connect function
* 	 buf		 Receive buffer
* 	 size		 Size of receive buffer
* 	 timeout	 Timeout for receive
*
* @return
* 	 The length of received data, or WIFI_STATUS_CONNECTION_ERROR 
* 	 for connection error. When receive  WIFI_STATUS_CONNECT_ERROR
* 	 the connection should be reconnect again.
*/
int32_t WifiRecv(int32_t socket, char *buf, uint32_t size, uint32_t timeout)
{
	int					ret;
	fd_set				rfds;
	struct timeval		timeoutSt;


	timeoutSt.tv_sec = timeout/1000;
	timeout = timeout%1000;
	timeoutSt.tv_usec = timeout*1000;

	FD_ZERO(&rfds);
	FD_SET(socket, &rfds);
	ret = select(socket+1, &rfds, NULL, NULL, &timeoutSt);
	if(ret != 0)
	{
		if(FD_ISSET(socket, &rfds))
		{
			ret = SocketRecv( socket, buf, size, 0);
			if(ret < 0)
			{
				return WIFI_STATUS_CONNECTION_ERROR;
			}
			else
			{
				return ret;
			}
		}
	}
	return 0;
}


/**
* @brief
* 	 Send data
*
* @param
* 	 socket 	 Socket created by connect function
* 	 buf		 Receive buffer
* 	 size		 Size of receive buffer
* 	 timeout	 Timeout for receive
*
* @return
* 	 The length of sent data or WIFI_STATUS_CONNECTION_ERROR
*/
int32_t WifiSend(int32_t socket, char *buf, uint32_t size, uint32_t timeout)
{
	return SocketWrite(socket, buf, size);
}


/**
* @brief
* 	 Resolve an URL to IP address
*
* @param
* 	 url	 
* 	 result  IP address resolved from URL.
*
* @return
* 	 WIFI_STATUS_SUCCESS or WIFI_STATUS_FAILED.
*/
WifiStatus  ResolveIP(uint8_t *url, IP_ADDR *ipAddr)
{
    struct ip_addr		dnsAddr;
    int					ip;

    if(netconn_gethostbyname(url, &dnsAddr) == 0)
    {
        ip = dnsAddr.addr;
        sprintf(ipAddr->ipAddrStr, "%d.%d.%d.%d", (ip&0x000000ff),(ip&0x0000ff00)>>8,(ip&0x00ff0000)>>16,(ip&0xff000000)>>24);
        return WIFI_STATUS_SUCCESS;
    }

    return ResolveIPFromDNSPOD(url, ipAddr);
}


