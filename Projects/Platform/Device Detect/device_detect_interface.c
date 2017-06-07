/**
 **************************************************************************************
 * @file    device_detect_interface.c
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

#include "type.h"
#include "device_detect_interface.h"
#include "rtos_api.h"

#define DBG printf

static bool isCardLink = FALSE;
static __INLINE void CardDetectDelay(void)
{
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
}
void DeviceCardInit(void)
{
	//card io config
	GpioSpimIoConfig(RESTORE_TO_GENERAL_IO);

    //CS - A1
	GpioSetRegOneBit(SD_SPI_CS_OUT, SD_SPI_CS_IO);
	GpioSetRegOneBit(SD_SPI_CS_OE, SD_SPI_CS_IO);
	GpioClrRegOneBit(SD_SPI_CS_IE, SD_SPI_CS_IO);
	GpioClrRegOneBit(SD_SPI_CS_PU, SD_SPI_CS_IO);
	GpioClrRegOneBit(SD_SPI_CS_PD, SD_SPI_CS_IO);

	//CMD - A2
	GpioClrRegOneBit(SD_SPI_CMD_PU, SD_SPI_CMD_IO);
	GpioClrRegOneBit(SD_SPI_CMD_PD, SD_SPI_CMD_IO);
	
	//CLK - A3
	GpioClrRegOneBit(SD_SPI_CLK_PU, SD_SPI_CLK_IO);
	GpioClrRegOneBit(SD_SPI_CLK_PD, SD_SPI_CLK_IO);
	
	//DAT - A4
	GpioClrRegOneBit(SD_SPI_DAT_PU, SD_SPI_DAT_IO);
	GpioClrRegOneBit(SD_SPI_DAT_PD, SD_SPI_DAT_IO);

	//DETECT IO
	GpioClrRegBits(CARD_DETECT_PORT_PU, CARD_DETECT_IO);
	GpioClrRegBits(CARD_DETECT_PORT_PD, CARD_DETECT_IO);
	GpioClrRegBits(CARD_DETECT_PORT_OE, CARD_DETECT_IO);

	GpioSetRegBits(CARD_DETECT_PORT_IE, CARD_DETECT_IO);

	CardDetectDelay(); //Disable和设置为IE 后，可能需要时延

	if(GpioGetReg(CARD_DETECT_PORT_IN) & CARD_DETECT_IO)
	{
		isCardLink = FALSE;
	}
	else
	{
		isCardLink = TRUE;
	}
	
	if(isCardLink)
	{
		GpioSpimIoConfig(SD_PORT_NUM);
	}
}

DeviceValue DeviceCardDetect(DeviceEvent *event)
{
	bool cardStatus;
	//LockSdClk();
	GpioSpimIoConfig(RESTORE_TO_GENERAL_IO);

	GpioClrRegBits(CARD_DETECT_PORT_PU, CARD_DETECT_IO);
	GpioClrRegBits(CARD_DETECT_PORT_PD, CARD_DETECT_IO);
	GpioClrRegBits(CARD_DETECT_PORT_OE, CARD_DETECT_IO);

	GpioSetRegBits(CARD_DETECT_PORT_IE, CARD_DETECT_IO);

	CardDetectDelay(); //Disable和设置为IE 后，可能需要时延

	if(GpioGetReg(CARD_DETECT_PORT_IN) & CARD_DETECT_IO)
	{
		cardStatus = FALSE;
	}
	else
	{
		cardStatus = TRUE;
	}
	
	if(cardStatus)
	{
		GpioSpimIoConfig(SD_PORT_NUM);
	}
	//UnLockSdClk();

	//
	if((!isCardLink)&&(cardStatus))
	{
		isCardLink = TRUE;
		*event = DEVICE_PULL_IN;
		return DEVICE_TYPE_CARD;
	}
	else if((isCardLink)&&(!cardStatus))
	{
		isCardLink = FALSE;
		*event = DEVICE_PULL_OUT;
		return DEVICE_TYPE_CARD;
	}
	return INVAILD_DEVICE_VALUE;
}

bool GetCardLinkFlag(void)
{
	return isCardLink;
}


static bool isMicLink = FALSE;
void DeviceMicInit(void)
{
	//设为输入，打开上拉
	GpioClrRegOneBit(MICIN_DETECT_PORT_OE, MICIN_DETECT_BIT);
	GpioClrRegOneBit(MICIN_DETECT_PORT_PU, MICIN_DETECT_BIT);
	GpioClrRegOneBit(MICIN_DETECT_PORT_PD, MICIN_DETECT_BIT);
	GpioSetRegBits(MICIN_DETECT_PORT_IE, MICIN_DETECT_BIT);

	if(GpioGetReg(MICIN_DETECT_PORT_IN) & MICIN_DETECT_BIT)
	{
		isMicLink = 0;
	}
	else
	{
		isMicLink = 1;
	}
}

DeviceValue DeviceMicDetect(DeviceEvent *event)
{
	static uint8_t micLinkState = 0;
	
	if(GpioGetReg(MICIN_DETECT_PORT_IN) & MICIN_DETECT_BIT)
	{
		micLinkState = 0;						//断开状态不做消抖处理
	}
	else
	{
		if(micLinkState < MICIN_JETTER_TIMES)	//连接状态做消抖处理
		{
			micLinkState++;
		}
	}
	
	if((!isMicLink)&&(micLinkState>=MICIN_JETTER_TIMES))
	{
		isMicLink = TRUE;
		*event = DEVICE_PULL_IN;
		return DEVICE_TYPE_MIC;
	}
	else if((isMicLink)&&(!micLinkState))
	{
		isMicLink = FALSE;
		*event = DEVICE_PULL_OUT;
		return DEVICE_TYPE_MIC;
	}
	return INVAILD_DEVICE_VALUE;
}

bool GetMicLinkFlag(void)
{
	return isMicLink;
}


