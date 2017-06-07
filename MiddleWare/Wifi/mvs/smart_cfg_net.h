#ifndef		__SMART_CFG_NET_H__
#define		__SMART_CFG_NET_H__

#ifdef __cplusplus
extern "C" {
#endif//__cplusplus
#include "type.h"

#define TOTAL_WIFI 		10
#define SSID_LEN 		32
#define PASSWORD_LEN 	16
#define AP_RECORD_FLAG	0x87651234

struct  AP_SSID_PWD {
    uint8_t ssid[SSID_LEN];
    uint8_t ssid_len;
    uint8_t password[PASSWORD_LEN];
    uint8_t password_len;
};

struct AP_RECORD {
    uint32_t total_items;
    uint32_t current_item;
    uint32_t flag;
    struct  AP_SSID_PWD ssid_pwd[TOTAL_WIFI];
};

extern struct AP_RECORD *pApJoiningRecord;

#ifdef __cplusplus
}
#endif//__cplusplus

#endif	//__SMART_CFG_NET_H__