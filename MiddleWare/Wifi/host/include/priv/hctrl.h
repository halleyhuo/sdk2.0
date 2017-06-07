/*
*  (C) Copyright 2014-2016 Shenzhen South Silicon Valley microelectronics co.,limited
*
*  All Rights Reserved
*/


#ifndef _HCTRL_H_
#define _HCTRL_H_

#define SSV6200_ID_AC_BK_OUT_QUEUE          8
#define SSV6200_ID_AC_BE_OUT_QUEUE          15
#define SSV6200_ID_AC_VI_OUT_QUEUE          16
#define SSV6200_ID_AC_VO_OUT_QUEUE          16
#define SSV6200_ID_MANAGER_QUEUE            8

#define SSV6200_ID_TX_THRESHOLD         30    //64 
/*Avoide MCU input queue full into deadlock (HCI output queue full, MACRX output queue full)
  Add MICRX after MCU in Rx DATA flow. (HCI:16 + MICRX:4+4) */
#define SSV6200_ID_RX_THRESHOLD         31    //64
#define SSV6200_PAGE_TX_THRESHOLD       60    //128
#define SSV6200_PAGE_RX_THRESHOLD       61    //128

#define SSV6200_TX_LOWTHRESHOLD_PAGE_TRIGGER            45
#define SSV6200_TX_LOWTHRESHOLD_ID_TRIGGER 		2

struct ssv6xxx_hci_txq_info {
	u32 tx_use_page:8;
    u32 tx_use_id:6;
    u32 txq0_size:4;
	u32 txq1_size:4;
	u32 txq2_size:5;
	u32 txq3_size:5;
};


struct ssv6xxx_hci_txq_info2 {
	u32 tx_use_page:9;
    u32 tx_use_id:8;
	u32 txq4_size:4;
    u32 rsvd:11;
};


#define TXPB_OFFSET		80
#define RXPB_OFFSET		80

#define RXINFO_SIZE		0x18

//TX_PKT_RSVD(3) * unit(16)
#define SSV6xxx_TX_PKT_RSVD_SETTING     0x3
#define SSV6xxx_TX_PKT_RSVD             SSV6xxx_TX_PKT_RSVD_SETTING*16
#define SSV6xxx_ALLOC_RSVD              TXPB_OFFSET+SSV6xxx_TX_PKT_RSVD


#define HW_MMU_PAGE_SHIFT           0x8
#define HW_MMU_PAGE_MASK            0xff

#define MMU_PAGE_SIZE


#endif /* _HCTRL_H */

