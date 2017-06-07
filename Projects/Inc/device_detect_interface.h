/**
 **************************************************************************************
 * @file    device_detect_interface.h
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

#ifndef __DEVICE_DETECT_INTERFACE_H__
#define __DEVICE_DETECT_INTERFACE_H__

#include "type.h"
#include "device_detect.h"
#include "app_message.h"
#include "gpio.h"

//CARD(SPI CONFIG)
#define SD_SPI_CS_IE			GPIO_A_IE
#define SD_SPI_CS_OE			GPIO_A_OE
#define SD_SPI_CS_PU			GPIO_A_PU
#define SD_SPI_CS_PD			GPIO_A_PD
#define SD_SPI_CS_OUT			GPIO_A_OUT
#define SD_SPI_CS_IO			GPIOA1

#define SD_SPI_CMD_IE			GPIO_A_IE
#define SD_SPI_CMD_OE			GPIO_A_OE
#define SD_SPI_CMD_PU			GPIO_A_PU
#define SD_SPI_CMD_PD			GPIO_A_PD
#define SD_SPI_CMD_OUT			GPIO_A_OUT
#define SD_SPI_CMD_IO			GPIOA2

#define SD_SPI_CLK_IE			GPIO_A_IE
#define SD_SPI_CLK_OE			GPIO_A_OE
#define SD_SPI_CLK_PU			GPIO_A_PU
#define SD_SPI_CLK_PD			GPIO_A_PD
#define SD_SPI_CLK_OUT			GPIO_A_OUT
#define SD_SPI_CLK_IO			GPIOA3

#define SD_SPI_DAT_IE			GPIO_A_IE
#define SD_SPI_DAT_OE			GPIO_A_OE
#define SD_SPI_DAT_PU			GPIO_A_PU
#define SD_SPI_DAT_PD			GPIO_A_PD
#define SD_SPI_DAT_OUT			GPIO_A_OUT
#define SD_SPI_DAT_IO			GPIOA4

#define CARD_DETECT_PORT_IE		GPIO_A_IE
#define CARD_DETECT_PORT_OE		GPIO_A_OE
#define CARD_DETECT_PORT_PU		GPIO_A_PU
#define CARD_DETECT_PORT_PD		GPIO_A_PD
#define CARD_DETECT_PORT_OUT	GPIO_A_OUT
#define CARD_DETECT_PORT_IN		GPIO_A_IN
#define CARD_DETECT_IO			GPIOA3

#define SD_PORT_NUM				0


#define	MICIN_DETECT_PORT_IN		GPIO_A_IN
#define	MICIN_DETECT_PORT_IE		GPIO_A_IE
#define	MICIN_DETECT_PORT_OE		GPIO_A_OE
#define	MICIN_DETECT_PORT_PU		GPIO_A_PU
#define	MICIN_DETECT_PORT_PD		GPIO_A_PD
#define MICIN_DETECT_BIT			GPIOA1

#define MICIN_JETTER_TIMES			10	//连接检测消抖时间：10次，100ms


//DEVICE - CARD
void DeviceCardInit(void);
DeviceValue DeviceCardDetect(DeviceEvent *event);
bool GetCardLinkFlag(void);

//DEVICE - MIC
void DeviceMicInit(void);
DeviceValue DeviceMicDetect(DeviceEvent *event);
bool GetMicLinkFlag(void);

#endif /* __DEVICE_DETECT_INTERFACE_H__ */

