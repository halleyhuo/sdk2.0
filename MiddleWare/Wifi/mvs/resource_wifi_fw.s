	AREA  WIFIFW, CODE, READONLY, ALIGN=8

	EXPORT RES_WIFI_FW_START

RES_WIFI_FW_START
	INCBIN  ..\..\MiddleWare\Wifi\host\firmware\ssv6200-uart.bin
RES_WIFI_END
	EXPORT RES_WIFI_END

	END
