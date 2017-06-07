/*
*  (C) Copyright 2014-2016 Shenzhen South Silicon Valley microelectronics co.,limited
*
*  All Rights Reserved
*/


#ifndef _DEV_H_
#define _DEV_H_
#include <host_apis.h>
#include "cmd_def.h"
#include <rtos.h>

//#ifdef ARRAY_SIZE
#undef ARRAY_SIZE
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
//#endif




typedef u32 tx_result;
#define TX_CONTINUE	((tx_result) 0u)
#define TX_DROP		((tx_result) 1u)
#define TX_QUEUED	((tx_result) 2u)


//Off->Init->Running->Pause->Off


enum TXHDR_ENCAP {
	TXREQ_ENCAP_ADDR4               =0,
	TXREQ_ENCAP_QOS                 ,
	TXREQ_ENCAP_HT                  ,
};


#define IS_TXREQ_WITH_ADDR4(x)          ((x)->txhdr_mask & (1<<TXREQ_ENCAP_ADDR4) )
#define IS_TXREQ_WITH_QOS(x)            ((x)->txhdr_mask & (1<<TXREQ_ENCAP_QOS)   )
#define IS_TXREQ_WITH_HT(x)             ((x)->txhdr_mask & (1<<TXREQ_ENCAP_HT)    )

#define SET_TXREQ_WITH_ADDR4(x, _tf)    (x)->txhdr_mask = (((x)->txhdr_mask & ~(1<<TXREQ_ENCAP_ADDR4))	| ((_tf)<<TXREQ_ENCAP_ADDR4) )
#define SET_TXREQ_WITH_QOS(x, _tf)      (x)->txhdr_mask = (((x)->txhdr_mask & ~(1<<TXREQ_ENCAP_QOS))	| ((_tf)<<TXREQ_ENCAP_QOS)   )
#define SET_TXREQ_WITH_HT(x, _tf)       (x)->txhdr_mask = (((x)->txhdr_mask & ~(1<<TXREQ_ENCAP_HT))		| ((_tf)<<TXREQ_ENCAP_HT)    )



typedef enum txreq_type_en {
	TX_TYPE_M0 = 0,
	TX_TYPE_M1,
	TX_TYPE_M2,
} txreq_type;


#define HOST_RECOVERY_CB_NUM  1
#define HOST_DATA_CB_NUM  2
#define HOST_EVT_CB_NUM  4
#define PRMOISCUOUS_CB_NUM  1

typedef enum {
	SSV6XXX_CB_ADD		,
	SSV6XXX_CB_REMOVE	,
	SSV6XXX_CB_MOD		,
} ssv6xxx_cb_action;


typedef struct DeviceInfo{

    OsMutex g_dev_info_mutex;
    OsMutex g_dev_bcn_mutex;
	ssv6xxx_hw_mode hw_mode;
	txreq_type tx_type;
	u32 txhdr_mask;
    u8 self_mac[ETH_ALEN];
	ETHER_ADDR addr4;
	u16 qos_ctrl;
	u32 ht_ctrl;

    //Set key base on VIF.
    u32 hw_buf_ptr;
    u32 hw_sec_key;
    u32 hw_pinfo;
    u8 beacon_usage:2;        //DRV_BCN_BCN0 bit 0,DRV_BCN_BCN1 bit 1
    u8 enable_beacon:1;
    u8 beacon_upd_need:1;
    u8 rsvd:4;
    struct ApInfo *APInfo; // AP mode used
    struct APStaInfo *StaConInfo; // AP mode used
    struct cfg_join_request *joincfg; // Station mode used
    struct cfg_join_request *joincfg_backup; // Station mode used
    #if(ENABLE_DYNAMIC_RX_SENSITIVE==1)
    u16 cci_current_level; //Station mode used
    u16 cci_current_gate; //Station mode used
    #endif
    enum conn_status    status;                 //Auth,Assoc,Eapol
    struct ssv6xxx_ieee80211_bss *ap_list; //station ap info list used (useing "g_dev_info_mutex" to protect it)
    u32 channel_edcca_count[MAX_CHANNEL_NUM];
    u32 channel_packet_count[MAX_CHANNEL_NUM];
//-----------------------------
//Data path handler
//-----------------------------
	data_handler data_cb[HOST_DATA_CB_NUM];

//-----------------------------
//Event path handler
//-----------------------------
	evt_handler evt_cb[HOST_EVT_CB_NUM];
//-----------------------------
// promiscuous call back function
//-----------------------------
    promiscuous_data_handler promiscuous_cb[PRMOISCUOUS_CB_NUM];

//-----------------------------
// promiscuous call back function
//-----------------------------
    recovery_handler recovery_cb[HOST_RECOVERY_CB_NUM];


//reload fw count
    s32 reload_fw_cnt;

//timer interrupt count
    u32 fw_timer_interrupt;

//tx loopback semaphore
    OsSemaphore tx_loopback;

//tx loopback result
    struct cfg_tx_loopback_info tx_loopback_info;

}DeviceInfo_st;

extern DeviceInfo_st *gDeviceInfo;
//Rate control setting
struct Host_cfg{
    u32 rate_msk:16;
    u32 target_pf:16;
    u32 arith_sft:8;
    u32 resent:1;
    u32 b_mode_highpower:1;
    u32 rc_direct_down:1;
    u32 RSVD0:21;
    u32 default_up_pf;
    u32 default_down_pf;
    u32 bcn_interval:8;
    u32 trx_hdr_len:16;
    u32 RSVD1:8;
    u32 pool_size;
    u32 recv_buf_size;
};

#endif /* _HOST_GLOBAL_ */

