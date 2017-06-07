/**
 **************************************************************************************
 * @file    bluetooth_interface.c
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
#include "gpio.h"
#include "uart.h"
#include "chip_info.h"
#include "delay.h"

#if (BT_RF_DEVICE == BTUartDeviceRTK8761)
#include "bt_rtk_driver.h"
#elif BT_RF_DEVICE == BTUartDeviceMTK662X
#include "bt_mtk_driver.h"
#endif



/***************************************************************************************
 *
 * External defines
 *
 */
#define BUART_RX_TX_FIFO_ADDR			(VMEM_ADDR + 57 * 1024)
#define BUART_RX_FIFO_SIZE				(6 * 1024)
#define BUART_TX_FIFO_SIZE				(1 * 1024)


/***************************************************************************************
 *
 * Internal defines
 *
 */

const uint8_t btDevAddr[6] = BT_ADDRESS;


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

static void BtDevicePinConfig(void)
{
	ResetBuartMoudle();

	GpioBuartRxIoConfig(BT_UART_RX_PORT);
	GpioBuartTxIoConfig(BT_UART_TX_PORT);
	GpioBuartRtsIoConfig(BT_UART_RTS_PORT);
	GpioClk32kIoConfig(BT_UART_EXT_CLK_PORT);
}

static void BtLDOEn(bool enable)
{
	uint8_t	gpioPort;

	/* LDO pin*/
	switch(BT_LDOEN_GPIO_PORT)
	{
		case 1:
			gpioPort = GPIO_A_IN;
			break;
		case 2:
			gpioPort = GPIO_B_IN;
			break;
		case 3:
			gpioPort = GPIO_C_IN;
			break;
		default:
			return;
	}

	if(enable)
	{
		GpioClrRegOneBit(gpioPort + 2, ((uint32_t)1 << BT_LDOEN_GPIO_PIN));
		GpioSetRegOneBit(gpioPort + 3, ((uint32_t)1 << BT_LDOEN_GPIO_PIN));
		GpioSetRegOneBit(gpioPort + 1, ((uint32_t)1 << BT_LDOEN_GPIO_PIN));
	}
	else
	{
		GpioClrRegOneBit(gpioPort + 2, ((uint32_t)1 << BT_LDOEN_GPIO_PIN));
		GpioSetRegOneBit(gpioPort + 3, ((uint32_t)1 << BT_LDOEN_GPIO_PIN));
		GpioClrRegOneBit(gpioPort + 1, ((uint32_t)1 << BT_LDOEN_GPIO_PIN));
	}

#if BT_RF_DEVICE == BTUartDeviceMTK662X
/* MTK RF 6622 should operate RESET pin at the same time*/

	/*RESET pin*/
	switch(BT_REST_GPIO_PORT)
	{
		case 1:
			gpioPort = GPIO_A_IN;
			break;
		case 2:
			gpioPort = GPIO_B_IN;
			break;
		case 3:
			gpioPort = GPIO_C_IN;
			break;
		default:
			return;
	}

	if(enable)
	{
		GpioClrRegOneBit(gpioPort + 2, ((uint32_t)1 << BT_REST_GPIO_PIN));
		GpioSetRegOneBit(gpioPort + 3, ((uint32_t)1 << BT_REST_GPIO_PIN));
		GpioSetRegOneBit(gpioPort + 1, ((uint32_t)1 << BT_REST_GPIO_PIN));
	}
	else
	{
		GpioClrRegOneBit(gpioPort + 2, ((uint32_t)1 << BT_REST_GPIO_PIN));
		GpioSetRegOneBit(gpioPort + 3, ((uint32_t)1 << BT_REST_GPIO_PIN));
		GpioClrRegOneBit(gpioPort + 1, ((uint32_t)1 << BT_REST_GPIO_PIN));
	}
#endif
}


/***************************************************************************************
 *
 * APIs
 *
 */
bool BtPowerOn(void)
{
	BtLDOEn(FALSE);
	WaitMs(200);
	BtLDOEn(TRUE);
	WaitMs(200);
	return TRUE;
}

bool BtUartInit(void)
{

	// 115200, 8, 0, 1

	BuartInit(115200, 8, 0, 1);

	BuartIOctl(UART_IOCTL_RXINT_SET,0);

	BuartIOctl(UART_IOCTL_TXINT_SET,0);

#if FLOW_CTRL == ENABLE
	BuartIOctl(BUART_IOCTL_RXRTS_FLOWCTL_SET, 2);
#endif

	BuartExFifoInit(BUART_RX_TX_FIFO_ADDR - PMEM_ADDR, BUART_RX_FIFO_SIZE, BUART_TX_FIFO_SIZE, 3);

	return TRUE;
}

bool BtUartDeInit(void)
{

	return TRUE;
}

bool BtUartChangeBaudRate(uint32_t baudrate)
{
	//change uart baud rate
	BuartIOctl(UART_IOCTL_DISENRX_SET,0); 

	BuartIOctl(UART_IOCTL_BAUDRATE_SET,baudrate);//different bt module may have the differnent bautrate!!

	BuartIOctl(UART_IOCTL_DISENRX_SET,1);

	return TRUE;
}

uint32_t BtUartSend(uint8_t * data, uint32_t dataLen, uint32_t timeout)
{
	return BuartSend(data, dataLen);
}

uint32_t BtUartRecv(uint8_t * data, uint32_t dataLen, uint32_t timeout)
{
	uint32_t	len;
	len = BuartRecv2(data, dataLen, timeout);
	return len;
//	return BuartRecv(data, dataLen, timeout);
}

void BtUartWaitMs(uint32_t ms)
{
	WaitMs(ms);
}


bool BtDeviceInit(void)
{
	bool	ret;

	BtDevicePinConfig();

	#if BT_RF_DEVICE == BTUartDeviceRTK8761
	
	{
		RtkConfigParam			params;

		memcpy(params.bdAddr, btDevAddr, 6);
		params.uartSettings.uartBaudrate	= PARAMS_UART_BAUDRATE;

		params.pcmSettings.scoInterface		= PARAMS_SCO_INTERFACE;
		params.pcmSettings.pcmFormat		= PARAMS_PCM_FORMAT;
		params.pcmSettings.pcmWidth			= PARAMS_PCM_WIDTH;

		params.radioPower.txPower			= PARAMS_TX_POWER;
		params.radioPower.txDac				= PARAMS_TX_DAC;

		params.enableFlowCtrl				= PARAMS_FLOW_CTRL;
		params.enableExtClk					= PARAMS_EXT_CLOCK;

		ret = BTDeviceInit_RTK8761(&params);
	}
	
	#elif BT_RF_DEVICE == BTUartDeviceMTK662X
	{
		MtkConfigParam			params;

		/*uart config*/
		params.uartSettings.baudrate		= PARAMS_UART_BAUDRATE;
		params.uartSettings.dataBits		= PARAMS_UART_DATA_BITS;
		params.uartSettings.stopBits		= PARAMS_UART_STOP_BITS;
		params.uartSettings.parityChk		= PARAMS_UART_PARITY_CHECK;
		params.uartSettings.flowCtrl		= PARAMS_UART_FLOW_CONTROL;

		/*pcm config*/
		params.pcmSettings.pcmMode			= PARAMS_PCM_MODE;
		params.pcmSettings.pcmClock			= PARAMS_PCM_CLOCK;
		params.pcmSettings.pcmInClkAbi		= PARAMS_PCM_CLK_ABI;
		params.pcmSettings.pcmSyncFormat	= PARAM_PCM_SYNC_FORMAT;
		params.pcmSettings.pcmEndianFormat	= PARAMS_PCM_ENDIAN;
		params.pcmSettings.pcmSignExt		= PARAMS_PCM_ENDIAN;

		/*local features*/
		params.localFeatures.enableAutoSniff		= PARAMS_AUTO_SNIFF;
		params.localFeatures.enableEV3				= PARAMS_EV3;
		params.localFeatures.enable3EV3				= PARAMS_3EV3;
		params.localFeatures.enableSimplePairing	= PARAMS_SIMPLE_PAIRING;

		/*tx power*/
		params.txPower		= PARAMS_TX_POWER;

		/*xo trim*/
		params.trimValue	= PARAMS_XO_TRIM;

		/* device address*/
		memcpy(params.bdAddr, btDevAddr, 6);

		ret = BTDeviceInit_MTK662x(&params);
	}
	#else
		#error "Select one bluetooth RF device";
	#endif

	return ret;
}
void BtStackRunNotify(void)
{
//	OSQueueMsgSend(MSG_NEED_BT_STACK_RUN, NULL, 0, MSGPRIO_LEVEL_HI, 0);
}


