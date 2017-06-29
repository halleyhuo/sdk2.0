/**
 **************************************************************************************
 * @file    wifi_audio_api.c
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
#include "wifi_audio_api.h"
#include "wxcloud_api.h"
#include "wifi_api.h"

#if 1
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
#define WA_MAX_DATA_BUFFER_SIZE		1024

#define MAX_DONMAIN_LEN				64

#define WA_MAX_RECEIVE_TIMEOUT		3000


typedef struct _WaSocketContext
{
	int32_t 		waSocket;
	uint8_t 		*waDataBuff;
	bool			waMediaStart;

	/* for receive */
	bool			headerFlag;
	uint32_t		waMediaTotalRecvLen;
	uint32_t		waMediaReceivedLen;
}WaSocketContext;


/***************************************************************************************
 *
 * Internal varibles
 *
 */

static WaSocketContext			waSocketLink;

const char endString[] = "Host: fdfs.xmcdn.com\r\nConnection: Keep-Alive\r\n\r\n";


/***************************************************************************************
 *
 * Internal functions
 *
 */

uint16_t ParseDonmainName(uint8_t * url, uint8_t * donmainName)
{
	uint8_t		*posStart, *posEnd;
	uint16_t	len;


	if(url == NULL || donmainName == NULL)
		return 0;

	/* skip "http://" */
	posStart = url + 7;

	/* find first '/' */
	posEnd = strstr(posStart, "/");

	len = posEnd - posStart;

	if(len >= MAX_DONMAIN_LEN)
		return 0;

	strncpy(donmainName, posStart, len);

	return len;
}

static WAudioStatus WifiAudioHttpHeaderParse(uint8_t * buff, uint16_t buffLen, uint8_t * itemString, uint8_t * itemContent)
{
	uint32_t		len = 0;
	uint32_t		itemStringLen;


	itemStringLen = strlen(itemString);

	while(len < buffLen)
	{
		if(memcmp(&buff[len],itemString,strlen(itemString)) == 0)
		{
			uint16_t		i;

			for(len += itemStringLen, i = 0; (buff[len] != '\r' && buff[len] != '\n'); len++, i++)
			{
				itemContent[i] = buff[len];
			}
			return WXCLOUD_STATUS_SUCCESS;
		}
		len++;
	}

	return WXCLOUD_STATUS_FAILED;	
}


static int32_t WifiAudioHttpGetBodyPos(uint8_t * buff, uint16_t buffLen)
{
	int32_t			position = 0;

	if(buff == NULL || buffLen == 0)
		return -1;

	while(position < buffLen - 3)
	{
		if(buff[position] == '\r' && buff[position+1] == '\n' && buff[position+2] == '\r' && buff[position+3] == '\n')
			break;

		position++;
	}

	if(position >= buffLen - 3)
	{
		return -1;
	}

	return position + 4;
}

AudioFormat WifiAudioFormatParse(const uint8_t *buff)
{
	uint32_t		len = 0;
	uint32_t		stringLen=0;

	stringLen = strlen(buff);

	while(len<stringLen)
	{
		if(memcmp(&buff[len],".mp3",4) == 0)
		{
			return FORMAT_MP3;
		}
		else if(memcmp(&buff[len],".m4a",4) == 0)
		{
			return FORMAT_M4A;
		}
		len++;
	}
	return FORMAT_UNKNOWN;
}

/***************************************************************************************
 *
 * APIs
 *
 */
 
WAudioStatus WifiAudioInit(void)
{
	
}

WAudioStatus WifiAudioDeinit(void)
{
	

}

WAudioStatus WifiAudioGetMediaStart(uint8_t * url, int32_t position)
{
	uint8_t			donmainName[MAX_DONMAIN_LEN];
	uint16_t		donmainNameLen;
	uint16_t		posContent;
	WAudioStatus	waudioStatus = WAUDIO_STATUS_FAILED;
	WifiStatus		wifiStatus;

	waSocketLink.waMediaStart = TRUE;

	waSocketLink.waDataBuff = (uint8_t *)pvPortMalloc(WA_MAX_DATA_BUFFER_SIZE);
	if(waSocketLink.waDataBuff == NULL)
	{
		return WAUDIO_STATUS_FAILED;
	}
	memset(waSocketLink.waDataBuff, 0, WA_MAX_DATA_BUFFER_SIZE);
	
	donmainNameLen = ParseDonmainName(url, donmainName);
	posContent = 7 /*Skip "http://"*/ + donmainNameLen;

	wifiStatus = WifiConnectURL(donmainName, &waSocketLink.waSocket, 80);
	if(wifiStatus != WIFI_STATUS_SUCCESS)
	{
		goto END;
	}

	/* Send http request */
	sprintf(waSocketLink.waDataBuff, "GET %s HTTP/1.1\r\n", url + posContent);
	wifiStatus = WifiSend(waSocketLink.waSocket, waSocketLink.waDataBuff, strlen(waSocketLink.waDataBuff), 0);
	if(wifiStatus < WIFI_STATUS_SUCCESS)
	{
		goto END;
	}

	/* Send range */
	memset(waSocketLink.waDataBuff, 0, WA_MAX_DATA_BUFFER_SIZE);
	
	sprintf(waSocketLink.waDataBuff, "RANGE: bytes=%d-\r\n", position);

	wifiStatus = WifiSend(waSocketLink.waSocket, waSocketLink.waDataBuff, strlen(waSocketLink.waDataBuff), 0);
	if(wifiStatus < WIFI_STATUS_SUCCESS)
	{
		goto END;
	}

	/* Send ending string */
	wifiStatus = WifiSend(waSocketLink.waSocket, endString, strlen(endString), 0 );
	if(wifiStatus < WIFI_STATUS_SUCCESS)
	{
		goto END;
	}
	
	waSocketLink.headerFlag = FALSE;

	waudioStatus = WAUDIO_STATUS_SUCCESS;
	return waudioStatus;
	
END:
	if(waSocketLink.waDataBuff)
		vPortFree(waSocketLink.waDataBuff);

	return waudioStatus;
}

WAudioStatus WifiAudioGetMedia(uint8_t **audioData, int32_t *dataLen, int32_t *position)
{
	WAudioStatus	waudioStatus = WAUDIO_STATUS_FAILED;
	int32_t			headLen;
	uint8_t			mediaLength[20] = {0};
	int32_t			bodyPos;


	if(audioData == NULL || *audioData == NULL || dataLen == NULL || position == NULL)
		return WAUDIO_STATUS_PARAMS_ERR;

	if(waSocketLink.headerFlag == FALSE) /* to receive http header */
	{
		memset(waSocketLink.waDataBuff, 0, WA_MAX_DATA_BUFFER_SIZE);
		headLen = WifiRecv(waSocketLink.waSocket, waSocketLink.waDataBuff, WA_MAX_DATA_BUFFER_SIZE, WA_MAX_RECEIVE_TIMEOUT);
		if(headLen < 0)
			return WAUDIO_STATUS_FAILED;

		//DBG("%s\n", waSocketLink.waDataBuff);
		waudioStatus = WifiAudioHttpHeaderParse(waSocketLink.waDataBuff, headLen, "Content-Length: ", mediaLength);
		if(waudioStatus == WAUDIO_STATUS_SUCCESS)
		{
			sscanf(mediaLength, "%d", &waSocketLink.waMediaTotalRecvLen);
		}
		else
		{
			return WAUDIO_STATUS_FAILED;
		}

		bodyPos = WifiAudioHttpGetBodyPos(waSocketLink.waDataBuff, headLen);
		if(bodyPos <= 0)
		{
			return WAUDIO_STATUS_FAILED;
		}

		*audioData = &waSocketLink.waDataBuff[bodyPos];
		*dataLen = headLen - bodyPos;
		*position = headLen - bodyPos;
		waSocketLink.waMediaReceivedLen = headLen - bodyPos;
		waSocketLink.headerFlag = TRUE;

		return WAUDIO_STATUS_SUCCESS;
	}
	else /* http header has been received*/
	{
		if(waSocketLink.waMediaReceivedLen < waSocketLink.waMediaTotalRecvLen)
		{
			int32_t			recvLen;

			recvLen = WifiRecv(waSocketLink.waSocket, waSocketLink.waDataBuff, WA_MAX_DATA_BUFFER_SIZE, WA_MAX_RECEIVE_TIMEOUT);

			if(recvLen <= 0)
				return WAUDIO_STATUS_NO_MORE_DATA;

			*audioData = waSocketLink.waDataBuff;
			*dataLen = recvLen;
			waSocketLink.waMediaReceivedLen += recvLen;
			*position = waSocketLink.waMediaReceivedLen;
			return WAUDIO_STATUS_SUCCESS;
		}
		else
		{
			return WAUDIO_STATUS_NO_MORE_DATA;
		}
	}
}

WAudioStatus WifiAudioGetMediaStop(void)
{
	if(waSocketLink.waMediaStart)
	{
		waSocketLink.waMediaStart = FALSE;
		SocketClose(waSocketLink.waSocket);
	}

	if(waSocketLink.waDataBuff)
		vPortFree(waSocketLink.waDataBuff);

	return WAUDIO_STATUS_SUCCESS;
}

#endif
