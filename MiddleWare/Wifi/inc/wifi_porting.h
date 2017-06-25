/**
 **************************************************************************************
 * @file    wifi_porting.h
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


#ifndef __WIFI_PORTING_H__
#define __WIFI_PORTING_H__

#include "type.h"
#include "sys_app.h"

struct  ap_ssid_pwd {
	uint8_t ap_ssid[40];
    uint8_t ap_ssid_len;
    uint8_t ap_password[40];
    uint8_t ap_password_len;
};

struct ap_record {
	uint8_t total_items;
    uint8_t current_item;
    struct  ap_ssid_pwd ssid_pwd[10];
};

extern struct AP_RECORD *pApJoiningRecord;

void Switch2STAmode(void);

int16_t Switch2SCONFIGmode(void);

void PrintfScanWifiResult(void);

void ScanWifi(void);

void LeaveWifi(void);

void JoinWifi(const uint8_t *ssidName, const uint8_t *ssidPassword);

int16_t GetNetifStatus(void);

uint32_t GetIpAdress(void);

uint8_t FindApInWifiList(uint8_t n, uint32_t ap_count, struct ssv6xxx_ieee80211_bss *ap_list);


#endif /*__WIFI_PORTING_H__*/

