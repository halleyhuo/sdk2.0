/*
*  (C) Copyright 2014-2016 Shenzhen South Silicon Valley microelectronics co.,limited
*
*  All Rights Reserved
*/


/*
 * This file contains definitions and data structures specific
 * to South Silicon Valley Cabrio 802.11 NIC. It contains the
 * Device Information structure struct cabrio_private..
 */
#ifndef _CABRIO_DEV_H_
#define _CABRIO_DEV_H_


/* Hardware Offload Engine ID */
#define M_ENG_CPU                       0x00
#define M_ENG_HWHCI                     0x01
//#define M_ENG_FRAG                    0x02
#define M_ENG_EMPTY                     0x02
#define M_ENG_ENCRYPT                   0x03
#define M_ENG_MACRX                     0x04
#define M_ENG_MIC                       0x05
#define M_ENG_TX_EDCA0                  0x06
#define M_ENG_TX_EDCA1                  0x07
#define M_ENG_TX_EDCA2                  0x08
#define M_ENG_TX_EDCA3                  0x09
#define M_ENG_TX_MNG                    0x0A
#define M_ENG_ENCRYPT_SEC               0x0B
#define M_ENG_MIC_SEC                   0x0C
#define M_ENG_RESERVED_1                0x0D
#define M_ENG_RESERVED_2                0x0E
#define M_ENG_TRASH_CAN                 0x0F
#define M_ENG_MAX                      (M_ENG_TRASH_CAN+1)


/* Software Engine ID: */
#define M_CPU_HWENG                     0x00
#define M_CPU_TXL34CS                   0x01
#define M_CPU_RXL34CS                   0x02
#define M_CPU_DEFRAG                    0x03
#define M_CPU_EDCATX                    0x04
#define M_CPU_RXDATA                    0x05
#define M_CPU_RXMGMT                    0x06
#define M_CPU_RXCTRL                    0x07
#define M_CPU_FRAG                      0x08

#define LBYTESWAP(a)  ((((a) & 0x00ff00ff) << 8) | \
    (((a) & 0xff00ff00) >> 8))

#define LONGSWAP(a)   ((LBYTESWAP(a) << 16) | (LBYTESWAP(a) >> 16))

#define MAC_DECITBL1_SIZE               16
#define MAC_DECITBL2_SIZE               9

#define MAC_REG_WRITE(_r, _v)                  \
        ssv6xxx_drv_write_reg(_r,_v)
#define MAC_REG_READ(_r, _v)                   \
        _v = ssv6xxx_drv_read_reg(_r)
#define MAC_LOAD_FW(_s, _l)                            \
        ssv6xxx_drv_load_fw(_s,_l)


#define MAC_DECITBL1_SIZE               16
#define MAC_DECITBL2_SIZE               9

//extern u16 sta_deci_tbl[];

/* Access Categories / ACI to AC coding */
enum {
    WMM_AC_BE = 0 /* Best Effort */,
    WMM_AC_BK = 1 /* Background */,
    WMM_AC_VI = 2 /* Video */,
    WMM_AC_VO = 3 /* Voice */,
    WMM_NUM_AC
};


#define SSV_EVENT_SIZE  (768)		// Probe response might be large.
#define SSV_EVENT_COUNT (12)

struct ssv6xxx_iqk_cfg {
    u32 cfg_xtal:8;
    u32 cfg_pa:8;
    u32 cfg_pabias_ctrl:8;
    u32 cfg_pacascode_ctrl:8;
    u32 cfg_tssi_trgt:8;
    u32 cfg_tssi_div:8;
    u32 cfg_def_tx_scale_11b:8;
    u32 cfg_def_tx_scale_11b_p0d5:8;
    u32 cfg_def_tx_scale_11g:8;
    u32 cfg_def_tx_scale_11g_p0d5:8;
    u32 cmd_sel;
    union {
        u32 fx_sel;
        u32 argv;
    }un;
    u32 phy_tbl_size;
    u32 rf_tbl_size;
};
#define PHY_SETTING_SIZE sizeof(phy_setting)

/*
    If change defallt value .please recompiler firmware image.
*/
#define MAX_PHY_SETTING_TABLE_SIZE    1920
#define MAX_RF_SETTING_TABLE_SIZE    512

typedef enum {
    SSV6XXX_IQK_CFG_XTAL_26M = 0,
    SSV6XXX_IQK_CFG_XTAL_40M,
    SSV6XXX_IQK_CFG_XTAL_24M,
    SSV6XXX_IQK_CFG_XTAL_MAX,
} ssv6xxx_iqk_cfg_xtal;

typedef enum {
    SSV6XXX_IQK_CFG_PA_DEF = 0,
    SSV6XXX_IQK_CFG_PA_LI_MPB,
    SSV6XXX_IQK_CFG_PA_LI_EVB,
    SSV6XXX_IQK_CFG_PA_HP,
} ssv6xxx_iqk_cfg_pa;

typedef enum {
    SSV6XXX_IQK_CMD_INIT_CALI = 0,
    SSV6XXX_IQK_CMD_RTBL_LOAD,
    SSV6XXX_IQK_CMD_RTBL_LOAD_DEF,
    SSV6XXX_IQK_CMD_RTBL_RESET,
    SSV6XXX_IQK_CMD_RTBL_SET,
    SSV6XXX_IQK_CMD_RTBL_EXPORT,
    SSV6XXX_IQK_CMD_TK_EVM,
    SSV6XXX_IQK_CMD_TK_TONE,
    SSV6XXX_IQK_CMD_TK_CHCH,
    SSV6XXX_IQK_CMD_TK_RXCNT,
} ssv6xxx_iqk_cmd_sel;

#define SSV6XXX_IQK_TEMPERATURE 0x00000004
#define SSV6XXX_IQK_RXDC        0x00000008
#define SSV6XXX_IQK_RXRC        0x00000010
#define SSV6XXX_IQK_TXDC        0x00000020
#define SSV6XXX_IQK_TXIQ        0x00000040
#define SSV6XXX_IQK_RXIQ        0x00000080
#define SSV6XXX_IQK_TSSI        0x00000100
#define SSV6XXX_IQK_PAPD        0x00000200

#define CHIP_ID_SSV6051Q_OLD 0x70000000
#define CHIP_ID_SSV6051Z 0x71000000
#define CHIP_ID_SSV6052Q 0x72000000
#define CHIP_ID_SSV6051Q 0x73000000
#define CHIP_ID_SSV6060P 0x74000000
#define CHIP_ID_SSV6051P 0x75000000
#define CHIP_ID_SSV6030P 0x76000000

#endif
