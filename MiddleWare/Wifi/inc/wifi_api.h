/**
 **************************************************************************************
 * @file    wifi_api.h
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



#ifndef __WIFI_API_H__
#define __WIFI_API_H__

#include "type.h"
#include "sockets.h"


#define IP_ADDRESS_LENGTH				16


typedef struct _IP_ADDR
{
	uint8_t		ipAddrStr[IP_ADDRESS_LENGTH];
}IP_ADDR;


typedef enum
{
	SocketLinkStateClosed = 0,
	SocketLinkStateOpened
}SocketLinkState;

typedef struct _SocketLink
{
	SocketLinkState		state;
	int32_t				socket;
	uint8_t				*dataBuff;
	uint16_t			dataBuffLen;
}SocketLink;


typedef int32_t			WifiStatus;

#define WIFI_STATUS_SUCCESS					0

#define WIFI_STATUS_FAILED					-1

#define WIFI_STATUS_CONNECT_FAILED			-2

#define WIFI_STATUS_CONNECTION_ERROR		-3

/**
 * @brief
 *		Connect to a URL
 *
 * @param
 *		url		URL
 *		sock	Socket for this link
 *
 * @return
 *		WIFI_STATUS_SUCCESS or WIFI_STATUS_FAILED
 */
WifiStatus WifiConnectURL(uint8_t *url, int32_t *sock, int32_t port);



/**
 * @brief
 *		Connect to a IP address
 *
 * @param
 *		ipAddr		IP address in char type. "192.168.1.1"
 *		sock		Socket for this link
 *
 * @return
 *		WIFI_STATUS_SUCCESS or WIFI_STATUS_FAILED
 */
WifiStatus WifiConnectIP(IP_ADDR *ipAddr, int32_t *sock, int32_t port);


/**
 * @brief
 *		Receive data from wifi link
 *
 * @param
 *		socket		Socket created by connect function
 *		buf			Receive buffer
 *		size		Size of receive buffer
 *		timeout		Timeout for receive
 *
 * @return
 *		The length of received data, or WIFI_STATUS_CONNECTION_ERROR 
 *		for connection error. When receive  WIFI_STATUS_CONNECT_ERROR
 *		the connection should be reconnect again.
 */
int32_t WifiRecv(int32_t socket, char *buf, uint32_t size, uint32_t timeout);


/**
 * @brief
 *		Send data
 *
 * @param
 *		socket		Socket created by connect function
 *		buf			Receive buffer
 *		size		Size of receive buffer
 *		timeout		Timeout for receive
 *
 * @return
 *		The length of sent data or WIFI_STATUS_CONNECTION_ERROR
 */
int32_t WifiSend(int32_t socket, char *buf, uint32_t size, uint32_t timeout);


/**
 * @brief
 *		Resolve an URL to IP address
 *
 * @param
 *		url		
 *		result	IP address resolved from URL.
 *
 * @return
 *		WIFI_STATUS_SUCCESS or WIFI_STATUS_FAILED.
 */
WifiStatus  ResolveIP(uint8_t *url, IP_ADDR *result);


/**
 * @brief
 *		Convert a IP address with char format to uint32_t format
 *
 * @param
 *		ipAddr	IP address with char format
 *
 * @return
 *		IP address with uint32_t format
 */
uint32_t ConvertInetAddrToAddr(uint8_t * ipAddr);
#define ConvertInetAddrToAddr(x)		inet_addr(x)


#if LWIP_COMPAT_SOCKETS
#define SocketAccept(a,b,c)			accept(a,b,c)
#define SocketBind(a,b,c)			bind(a,b,c)
#define SocketShutdown(a,b)			shutdown(a,b)
#define SocketClose(s)				closesocket(s)
#define SocketConnect(a,b,c)		connect(a,b,c)
#define SocketGetSockName(a,b,c)	getsockname(a,b,c)
#define SocketGetPeerName(a,b,c)	getpeername(a,b,c)
#define SocketSetsockOpt(a,b,c,d,e)	setsockopt(a,b,c,d,e)
#define SocketGetSockOpt(a,b,c,d,e)	getsockopt(a,b,c,d,e)
#define SocketListen(a,b)			listen(a,b)
#define SocketRecv(a,b,c,d)			recv(a,b,c,d)
#define SocketRecvFrom(a,b,c,d,e,f)	recvfrom(a,b,c,d,e,f)
#define SocketSend(a,b,c,d)			send(a,b,c,d)
#define SocketSendTo(a,b,c,d,e,f)	sendto(a,b,c,d,e,f)
#define SocketOpen(a,b,c)			socket(a,b,c)
#define SocketSelect(a,b,c,d,e)		select(a,b,c,d,e)
#define SocketIOCtl(a,b,c)			ioctlsocket(a,b,c)

#define SocketFCntl(a, b, c)		fcntl(a,b,c)
#define SocketRead(a, b, c) 		read(a,b,c)
#define SocketWrite(a, b, c)		write(a,b,c)

#endif

#endif /*__WIFI_API_H__*/

