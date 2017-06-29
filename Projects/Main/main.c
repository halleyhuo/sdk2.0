/**
 **************************************************************************************
 * @file    main.c
 * @brief   Program Entry 
 *
 * @author  halley
 * @version V1.0.0
 *
 * $Created: 2016-6-29 13:06:47$
 *
 * @Copyright (C) 2016, Shanghai Mountain View Silicon Co.,Ltd. All rights reserved.
 **************************************************************************************
 */

#include <stdio.h>
#include "type.h"
#include "clk.h"
#include "wakeup.h"
#include "spi_flash.h"
#include "cache.h"
#include "uart.h"
#include "gpio.h"
#include "watchdog.h"
#include "delay.h"
#include "rtos_api.h"
#include "app_config.h"
#include "sdram.h"

static void InitZiArea(void)
{
	
	extern uint32_t Image$$RW_XMEM$$ZI$$Base;
	extern uint32_t Image$$RW_XMEM$$ZI$$Limit;
	
	uint8_t* ziStart = (uint8_t*)&Image$$RW_XMEM$$ZI$$Base;
	uint8_t* ziEnd = (uint8_t*)&Image$$RW_XMEM$$ZI$$Limit;
	
	GpioSdramIoConfig(0);
	SdramInit();
	
	memset((void*)SDRAM_BASE_ADDR, 0, SDRAM_SIZE/2);
	
	memset(ziStart, 0, (ziEnd-ziStart));
	
}

static int32_t MiniSystemInit(void)
{
	
	ClkModuleEn(ALL_MODULE_CLK_SWITCH);	
	ClkModuleGateEn(ALL_MODULE_CLK_GATE_SWITCH);        //open all clk gating

//	ClkModuleDis(SDRAM_CLK_EN|SPIM_CLK_EN|SPIS_CLK_EN|LCDC_CLK_EN|DMAC_CLK_EN|SD_CLK_EN|USB_CLK_EN);

	CacheInit();
	
	SysGetWakeUpFlag(); //get wake up flag, DO NOT remove this!!

//	SysPowerKeyInit(POWERKEY_MODE_SLIDE_SWITCH, 500);//500ms

	SpiFlashInfoInit();		//Flash RD/WR/ER/LOCK initialization
	
	ClkPorRcToDpll(0); 		//clock src is 32768hz OSC
	
	//GD flash，选择SYS CLK或DPLL80Mhz，可以开启HPM，其他型号建议关闭HPM
	SpiFlashClkSet(FLASHCLK_SYSCLK_SEL, TRUE);
	
//	Osc32kExtCapCalibrate();//32KHz external oscillator calibration
	
	InitZiArea();
	
	return 0;
}

static int32_t OsInit(void)
{
	
	InitialiseHeapArea();
	
}

static int32_t StorageInit(void)
{

}

static void PrintDeviceInit(void)
{
	GpioFuartTxIoConfig(0);
	GpioFuartRxIoConfig(0xff);// GPIOA1 for SPI-CS
	FuartInit(115200, 8, 0, 1);
}

static void WatchDogDeviceInit(void)
{
	DelayMs(200);
	WdgDis();
}

static int32_t PeripheralInit(void)
{

	WatchDogDeviceInit();

	PrintDeviceInit();

//	BtDeviceInit();

//	WifiInit();

//	KeyInit();
}

static int32_t OtherInit(void)
{
	if(InitFlashFS() != 0)
	{
		DBG("Init flashFs fail\n");
	}
	


}


static int32_t AppSystemInit(void)
{
	MiniSystemInit();

	OsInit();

	StorageInit();

	PeripheralInit();

	OtherInit();
}

int32_t main(void)
{
	AppSystemInit();
	
	APP_DBG("****************************************************************\n");
	APP_DBG("System Clock     :%d MHz(%d)\n", ClkGetCurrentSysClkFreq() / 1000000, ClkGetCurrentSysClkFreq());
//	APP_DBG("Flash Clock      :%d MHz(%d)\n", ClkGetFshcClkFreq() / 1000000, ClkGetFshcClkFreq());
//	APP_DBG("BOOT Version     :%d.%d.%d%c\n", GetBootVersion(), GetPatchVersion() / 10, GetPatchVersion() % 10,GetBootVersionEx());
//	APP_DBG("SDK  Version     :%d.%d.%d\n", (GetSdkVer() >> 8) & 0xFF, (GetSdkVer() >> 16) & 0xFF, GetSdkVer() >> 24);
//	APP_DBG("Free Memory      :%d(%d KB)\n", OSMMMIoCtl(MMM_IOCTL_GETSZ_INALL, 0), OSMMMIoCtl(MMM_IOCTL_GETSZ_INALL, 0) / 1024);
//	APP_DBG("Code Size        :%d(%d KB)\n", GetCodeSize(), GetCodeSize() / 1024);
//	APP_DBG("Code Encrypted   :%s\n", GetCodeEncryptedInfo());
//	APP_DBG("Wakeup Source    :%s(0x%08X)\n", GetWakeupSrcName(gWakeUpFlag), gWakeUpFlag);
//	APP_DBG("BT Lib Ver       :%s\n", GetLibVersionBt());
//	APP_DBG("AudioDecoder Ver :%s\n", GetLibVersionAudioDecoder());
//	APP_DBG("Driver Ver       :%s\n", GetLibVersionDriver());
//	APP_DBG("FreeRTOS Ver     :%s\n", GetLibVersionFreertos());
//	APP_DBG("FS Ver           :%s\n", GetLibVersionFs());
	APP_DBG("****************************************************************\n");

	MainAppTaskStart();
	
	vTaskStartScheduler();

	while(1);
}

