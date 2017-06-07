/***

	*************************************************************************
	*																		*
	*		header file for I/O port address and bit defines				*
	*																		*
	*														IO_Port.h		*
	*************************************************************************
	ALL RIGHTS RESERVED, COPYRIGHT(C) FUJITSU FRONTECH LIMITED. 2003-2007

	SN			Date		Name		Revision.No.	Contents
	-------------------------------------------------------------------------
	001-ZZ01	2003/01/xx	A.Kojima	<BRZ-001>		The First Version
				2003/03/04	A.Maruyama					make consistent with specifications of MemoryMap (E08 2003.02.20)
	002-ZZ03	2003/04/22	A.Kojima	<BRZ-021>		change for new upper(A3 Mech.)
	003-ZZ06	2003/08/07	A.Kojima	<BRZ-295>		change for A4 Pre-Acceptor
	004-ZY01	2003/10/02	A.Kojima	<BRZ-406>		change for B'-model
				2003/10/21	A.Kojima	<BRZ-429>		change for B-model
	005-ZY02	2003/11/04	A.Kojima	<BRZ-446>		add SM_PD2
				2003/11/21	A.Kojima	<BRZ-476>		add for shutter motor
				2003/11/21	A.Kojima	<BRZ-477>		add for MEI
	006-ZY03	2003/12/08	A.Kojima	<BRZ-535>		change bit of WLSHT_DISP_SOL
	007-ZY04	2003/12/22	A.Kojima	<BRZ-593>		change for Memory Map(B-6)
	008-ZY06	2004/01/29	A.Kojima	<BRZ-699>		change over current bit at upper 5V
	009-ZW01	2004/01/31	A.Maruyama	<BRZ-702>		delete code for A-model
				2004/02/07	A.Kojima	<BRZ-723>		change for B2-model
	010-ZV01	2004/04/09	A.Maruyama	<BRZ-911>		add ETRS for B3-model
										<BRZ-912>		add ETLC for B3-model
	011-ZT02	2004/06/11	A.Kojima	<BRZ-1108>		add for A/D converter
	012-AA04	2004/08/05	A.Kojima	<BRZ-1189>		add PDAC sensor
				2004/08/09	A.Maruyama	<BRZ-1196>		add RLUCOM/WSCRCLR port
	013-AA42	2007/11/02	A.Maruyama	<BRZ-1554>		for Dual BRU
														-Add RLS6_DUAL
	014-AA54	2008/01/24	A.Kojima	<BRZ-1557>		add CS1E/CS2E/CS3E/CS4E sensor

COMMENT END
***/
/****************************************************************************/
/*																			*/
/*	defines																	*/
/*																			*/
/****************************************************************************/
/*--------------------------------------------------------------------------*/
/*																			*/
/*																			*/
/*	I/O, System																*/
/*																			*/
/*																			*/
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/*																			*/
/*	Upper (Write)															*/
/*																			*/
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/*	7 segments LED															*/
/*--------------------------------------------------------------------------*/
#define	PORT_D7S			( volatile USHORT * )0x00C04000
#define	PORT_D7S_U			( volatile UCHAR * )0x00C04000
#define	PORT_D7S_L			( volatile UCHAR * )0x00C04001
	#define	D7S_DP				BIT7
	#define	D7S_G				BIT6
	#define	D7S_F				BIT5
	#define	D7S_E				BIT4
	#define	D7S_D				BIT3
	#define	D7S_C				BIT2
	#define	D7S_B				BIT1
	#define	D7S_A				BIT0
/*--------------------------------------------------------------------------*/
/*	Linear solenoid															*/
/*	Rev.(ZZ06:BRZ-295)														*/
/*	 Add WULSOL_PHMG														*/
/*	Rev.(ZY01:BRZ-406)														*/
/*	 Add WULSOL_SRMG														*/
/*--------------------------------------------------------------------------*/
#define	PORT_WULSOL			( volatile UCHAR * )0x00C04002
	#define	WULSOL_SRMG			BIT3
	#define	WULSOL_PHMG			BIT2
	#define	WULSOL_PDMG			BIT1
	#define	WULSOL_PAMG			BIT0
/*--------------------------------------------------------------------------*/
/*	Rotary solenoid															*/
/*	Rev.(ZZ06:BRZ-295)														*/
/*	 Delete WURSOL_PHMG														*/
/*	Rev.(ZY01:BRZ-406)														*/
/*	 Add WURSOL_ESMG														*/
/*--------------------------------------------------------------------------*/
#define	PORT_WURSOL			( volatile UCHAR * )0x00C04003
	#define	WURSOL_ESMG			BIT5
	#define	WURSOL_UEMG			BIT4
	#define	WURSOL_UDMG			BIT3
	#define	WURSOL_UCMG			BIT2
	#define	WURSOL_EBMG			BIT1
	#define	WURSOL_UAMG			BIT0
#define	PORT_WURSOLI		( volatile UCHAR * )0x00C04004
/*--------------------------------------------------------------------------*/
/*	Transport DC motor														*/
/*--------------------------------------------------------------------------*/
#define	PORT_WUUTMM			( volatile UCHAR * )0x00C04005
	#define	TDCM_MRST			BIT7
	#define	TDCM_PDOWN			BIT5
	#define	TDCM_HSEL			BIT4
	#define	TDCM_HI  			BIT3
	#define	TDCM_BRK			BIT2
	#define	TDCM_FW				BIT1
	#define	TDCM_GO				BIT0
/*--------------------------------------------------------------------------*/
/*	Counter clear															*/
/*--------------------------------------------------------------------------*/
#define	PORT_WUCLR			( volatile UCHAR * )0x00C04006
	#define	WUCLR_SSCL			BIT0
/*--------------------------------------------------------------------------*/
/*	Sensor																	*/
/*	Rev.(ZZ06:BRZ-295)														*/
/*	 Add PORT_WUPDSS and change address of SDIS,SDOS,SSLS,SSRS,SSOS			*/
/*	Rev.(ZV01:BRZ-911)														*/
/*	 add PORT_WUETRS														*/
/*--------------------------------------------------------------------------*/
#define	PORT_WUPS1S			( volatile UCHAR * )0x00C04008
#define	PORT_WUPS2S			( volatile UCHAR * )0x00C04009
#define	PORT_WUPS3S			( volatile UCHAR * )0x00C0400A
#define	PORT_WUPS4S			( volatile UCHAR * )0x00C0400B
#define	PORT_WUPTCS			( volatile UCHAR * )0x00C0400C
#define	PORT_WUPASS			( volatile UCHAR * )0x00C0400D
#define	PORT_WUPDSS			( volatile UCHAR * )0x00C0400E
#define	PORT_WUSDIS			( volatile UCHAR * )0x00C0400F
#define	PORT_WUSDOS			( volatile UCHAR * )0x00C04010
#define	PORT_WUSSLS			( volatile UCHAR * )0x00C04011
#define	PORT_WUSSRS			( volatile UCHAR * )0x00C04012
#define	PORT_WUSSOS			( volatile UCHAR * )0x00C04013
#define	PORT_WUEECS			( volatile UCHAR * )0x00C04014
#define	PORT_WUETLS			( volatile UCHAR * )0x00C04015
#define	PORT_WUEELS			( volatile UCHAR * )0x00C04016
#define	PORT_WUEERS			( volatile UCHAR * )0x00C04017
#define	PORT_WUEDLS			( volatile UCHAR * )0x00C04018
#define	PORT_WUEDRS			( volatile UCHAR * )0x00C04019
#define	PORT_WUERLS			( volatile UCHAR * )0x00C0401A
#define	PORT_WUERRS			( volatile UCHAR * )0x00C0401B
#define	PORT_WUUGAS			( volatile UCHAR * )0x00C0401C
#define	PORT_WUURHS			( volatile UCHAR * )0x00C0401D
#define	PORT_WUUFHS			( volatile UCHAR * )0x00C0401E
#define	PORT_WUUGDS			( volatile UCHAR * )0x00C0401F
#define	PORT_WUUECS			( volatile UCHAR * )0x00C04020
#define	PORT_WUUEFS			( volatile UCHAR * )0x00C04021
#define	PORT_WUUERS			( volatile UCHAR * )0x00C04022
#define	PORT_WUETRS			( volatile UCHAR * )0x00C04023
/*--------------------------------------------------------------------------*/
/*	Stepping motor															*/
/*	Rev.(ZY02:BRZ-446)														*/
/*	 Add SM_PD2																*/
/*--------------------------------------------------------------------------*/
#define	PORT_WUPABM			( volatile UCHAR * )0x00C04030
	#define	SM_PD2				BIT6
	#define	SM_PD				BIT5

	#define	SM_NB				BIT3
	#define	SM_NA				BIT2
	#define	SM_B				BIT1
	#define	SM_A				BIT0

	#define	SM_E2				BIT3
	#define	SM_E1				BIT2
	#define	SM_P2				BIT1
	#define	SM_P1				BIT0
#define	PORT_WUPATM			( volatile UCHAR * )0x00C04031
#define	PORT_WUPACM			( volatile UCHAR * )0x00C04032
#define	PORT_WUSEFM			( volatile UCHAR * )0x00C04033
#define	PORT_WUSEPM			( volatile UCHAR * )0x00C04034
#define	PORT_WUSESM			( volatile UCHAR * )0x00C04035
#define	PORT_WUSEDM			( volatile UCHAR * )0x00C04036
#define	PORT_WUESCM			( volatile UCHAR * )0x00C04037
#define	PORT_WUERSM			( volatile UCHAR * )0x00C04038
#define	PORT_WUEESM			( volatile UCHAR * )0x00C04039
/*--------------------------------------------------------------------------*/
/*																			*/
/*	Lower (Write)															*/
/*																			*/
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/*	Linear solenoid															*/
/*--------------------------------------------------------------------------*/
#define	PORT_WLLSOL			( volatile UCHAR * )0x00C04100
	#define	WLLSOL_C4MG			BIT3
	#define	WLLSOL_C3MG			BIT2
	#define	WLLSOL_C2MG			BIT1
	#define	WLLSOL_C1MG			BIT0
/*--------------------------------------------------------------------------*/
/*	Rotary solenoid															*/
/*--------------------------------------------------------------------------*/
#define	PORT_WLRSOL			( volatile UCHAR * )0x00C04102
	#define	WLRSOL_L4MG			BIT3
	#define	WLRSOL_L3MG			BIT2
	#define	WLRSOL_L2MG			BIT1
	#define	WLRSOL_L1MG			BIT0
#define	PORT_WLRSOLI		( volatile UCHAR * )0x00C04103
/*--------------------------------------------------------------------------*/
/*	Counter clear															*/
/*--------------------------------------------------------------------------*/
#define	PORT_WLCLR			( volatile UCHAR * )0x00C04104
	#define	WLCLR_C4CL			BIT3
	#define	WLCLR_C3CL			BIT2
	#define	WLCLR_C2CL			BIT1
	#define	WLCLR_C1CL			BIT0
/*--------------------------------------------------------------------------*/
/*	Enable cassettes														*/
/*	Rev.(ZY01:BRZ-429)														*/
/*	 Delete ENC1,ENC2,ENC3,ENC4 and add ENCS								*/
/*--------------------------------------------------------------------------*/
#define	PORT_WLENCS			( volatile UCHAR * )0x00C04105
	#define	WLENCS_ENCS			BIT0
/*--------------------------------------------------------------------------*/
/*	Rev.(ZY02:BRZ-476)	add													*/
/*	Shutter DC motor														*/
/*	Rev.(ZY03:BRZ-535)														*/
/*	 Change bit of WLSHT_DISP_SOL from BIT0 to BIT2							*/
/*--------------------------------------------------------------------------*/
#define	PORT_WLSHT			( volatile UCHAR * )0x00C04106
	#define	WLSHT_DISP_SOL		BIT2
/*--------------------------------------------------------------------------*/
/*	Rev.(ZY02:BRZ-477)	add													*/
/*	MEI																		*/
/*--------------------------------------------------------------------------*/
#define	PORT_WLMEI			( volatile UCHAR * )0x00C04107
	#define	WLMEI_MEI			BIT0
/*--------------------------------------------------------------------------*/
/*	Sensor																	*/
/*	Rev.(ZY01:BRZ-406)														*/
/*	 Add PORT_WLLFHS														*/
/*--------------------------------------------------------------------------*/
#define	PORT_WLLT3S			( volatile UCHAR * )0x00C04108
#define	PORT_WLLFHS			( volatile UCHAR * )0x00C04109
#define	PORT_WLCL1S			( volatile UCHAR * )0x00C04114
#define	PORT_WLCR1S			( volatile UCHAR * )0x00C04115
#define	PORT_WLCL2S			( volatile UCHAR * )0x00C04116
#define	PORT_WLCR2S			( volatile UCHAR * )0x00C04117
#define	PORT_WLCL3S			( volatile UCHAR * )0x00C04118
#define	PORT_WLCR3S			( volatile UCHAR * )0x00C04119
#define	PORT_WLCL4S			( volatile UCHAR * )0x00C0411A
#define	PORT_WLCR4S			( volatile UCHAR * )0x00C0411B
#define	PORT_WLCT1S			( volatile UCHAR * )0x00C0411C
#define	PORT_WLCT2S			( volatile UCHAR * )0x00C0411D
#define	PORT_WLCT3S			( volatile UCHAR * )0x00C0411E
#define	PORT_WLCT4S			( volatile UCHAR * )0x00C0411F
/*--------------------------------------------------------------------------*/
/*	Stepping motor															*/
/*--------------------------------------------------------------------------*/
#define	PORT_WLBS1M			( volatile UCHAR * )0x00C04130
#define	PORT_WLBF1M			( volatile UCHAR * )0x00C04131
#define	PORT_WLBS2M			( volatile UCHAR * )0x00C04132
#define	PORT_WLBF2M			( volatile UCHAR * )0x00C04133
#define	PORT_WLBS3M			( volatile UCHAR * )0x00C04134
#define	PORT_WLBF3M			( volatile UCHAR * )0x00C04135
#define	PORT_WLBS4M			( volatile UCHAR * )0x00C04136
#define	PORT_WLBF4M			( volatile UCHAR * )0x00C04137
#define	PORT_WLSHTM			( volatile UCHAR * )0x00C04139
/*--------------------------------------------------------------------------*/
/*																			*/
/*	Upper (Read)															*/
/*																			*/
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/*	Sensor																	*/
/*	Rev.(ZZ06:BRZ-295)														*/
/*	 Delete RUS0_PPRC,RUS0_PLPC and add RUS0_PBPC,RUS0_PTPC,RUS6_PDSS		*/
/*	Rev.(ZY01:BRZ-406)														*/
/*	 Delete RUS4_SWLC,SWRC													*/
/*	 Add RUS4_SFIC,RUS4_SFOC,RUS4_SHDC,RUS4_SBLC,RUS5_UGLC					*/
/*	Rev.(ZW01:BRZ-723)														*/
/*	 Add RUS1_PHPC,RUS2_PLPC,RUS2_ESPC										*/
/*	Rev.(ZV01:BRZ-911)														*/
/*	 Add RUS6_ETRS															*/
/*	Rev.(ZV01:BRZ-912)														*/
/*	 Add RUS2_ETLC															*/
/*	Rev.(AA04:BRZ-1189)														*/
/*	 add RUS3_PDAC															*/
/*--------------------------------------------------------------------------*/
#define	PORT_RUS0			( volatile UCHAR * )0x00C05000
	#define	RUS0_PCEC			BIT6
	#define	RUS0_PBPC			BIT5
	#define	RUS0_PRPC			BIT4
	#define	RUS0_PTPC			BIT3
	#define	RUS0_PDPC			BIT2
	#define	RUS0_POLC			BIT1
	#define	RUS0_PTHC			BIT0
	#define	RUS0_RSV			( BIT7 )
#define	PORT_RUS1			( volatile UCHAR * )0x00C05001
	#define	RUS1_PHPC			BIT7
	#define	RUS1_ERLC			BIT5
	#define	RUS1_ERRC			BIT4
	#define	RUS1_ERUC			BIT3
	#define	RUS1_ECPC			BIT2
	#define	RUS1_ECCC			BIT1
	#define	RUS1_ECHC			BIT0
	#define	RUS1_RSV			( BIT6 )
#define	PORT_RUS2			( volatile UCHAR * )0x00C05002
	#define	RUS2_PLPC			BIT7
	#define	RUS2_ETLC			BIT4
	#define	RUS2_ESPC			BIT3
	#define	RUS2_EERC			BIT2
	#define	RUS2_EELC			BIT1
	#define	RUS2_EEUC			BIT0
	#define	RUS2_RSV			( BIT6 | BIT5 )
#define	PORT_RUS3			( volatile UCHAR * )0x00C05003
	#define	RUS3_PDAC			BIT7
	#define	RUS3_SSEC			BIT5
	#define	RUS3_SSLC			BIT4
	#define	RUS3_SSUC			BIT3
	#define	RUS3_SPBC			BIT2
	#define	RUS3_SPPC			BIT1
	#define	RUS3_SPUC			BIT0
	#define	RUS3_RSV			( BIT6 )
#define	PORT_RUS4			( volatile UCHAR * )0x00C05004
	#define	RUS4_SBLC			BIT6
	#define	RUS4_SHDC			BIT5
	#define	RUS4_SCDC			BIT4
	#define	RUS4_SFPC			BIT3
	#define	RUS4_SPCC			BIT2
	#define	RUS4_SFOC			BIT1
	#define	RUS4_SFIC			BIT0
	#define	RUS4_RSV			( BIT7 )
#define	PORT_RUS5			( volatile UCHAR * )0x00C05005
	#define	RUS5_UGLC			BIT6
	#define	RUS5_ULPC			BIT5
	#define	RUS5_URFC			BIT4
	#define	RUS5_UFFC			BIT3
	#define	RUS5_UCFC			BIT2
	#define	RUS5_URLC			BIT1
	#define	RUS5_UULC			BIT0
	#define	RUS5_RSV			( BIT7 )
#define	PORT_RUS6			( volatile UCHAR * )0x00C05006
	#define	RUS6_ETRS			BIT7
	#define	RUS6_PDSS			BIT6
	#define	RUS6_PASS			BIT5
	#define	RUS6_PTCS			BIT4
	#define	RUS6_PS4S			BIT3
	#define	RUS6_PS3S			BIT2
	#define	RUS6_PS2S			BIT1
	#define	RUS6_PS1S			BIT0
	#define	RUS6_RSV			( 0 )
#define	PORT_RUS7			( volatile UCHAR * )0x00C05007
	#define	RUS7_ETLS			BIT3
	#define	RUS7_EECS			BIT2
	#define	RUS7_EERS			BIT1
	#define	RUS7_EELS			BIT0
	#define	RUS7_RSV			( BIT7 | BIT6 | BIT5 | BIT4 )
#define	PORT_RUS8			( volatile UCHAR * )0x00C05008
	#define	RUS8_RSV			( BIT7 | BIT6 | BIT5 | BIT4 | BIT3 | BIT2 | BIT1 | BIT0 )
#define	PORT_RUS9			( volatile UCHAR * )0x00C05009
	#define	RUS9_FLD			BIT7
	#define	RUS9_FLT			BIT6
	#define	RUS9_LOCK			BIT4
	#define	RUS9_SW3			BIT2
	#define	RUS9_SW2			BIT1
	#define	RUS9_SW1			BIT0
	#define	RUS9_RSV			( BIT5 | BIT3 )
#define	PORT_RUS12			( volatile UCHAR * )0x00C0500C
	#define	RUS12_UERS			BIT6
	#define	RUS12_UEFS			BIT5
	#define	RUS12_UECS			BIT4
	#define	RUS12_UFHS			BIT3
	#define	RUS12_URHS			BIT2
	#define	RUS12_UGDS			BIT1
	#define	RUS12_UGAS			BIT0
	#define	RUS12_RSV			( BIT7 )
#define	PORT_RUS13			( volatile UCHAR * )0x00C0500D
	#define	RUS13_SDOS			BIT4
	#define	RUS13_SDIS			BIT3
	#define	RUS13_SSOS			BIT2
	#define	RUS13_SSLS			BIT1
	#define	RUS13_SSRS			BIT0
	#define	RUS13_RSV			( BIT7 | BIT6 | BIT5 )
#define	PORT_RUS14			( volatile UCHAR * )0x00C0500E
	#define	RUS14_EDRS			BIT7
	#define	RUS14_EDLS			BIT6
	#define	RUS14_ERRS			BIT5
	#define	RUS14_ERLS			BIT4
	#define	RUS14_RSV			( BIT3 | BIT2 | BIT1 | BIT0 )
/*--------------------------------------------------------------------------*/
/*	Skew counter															*/
/*--------------------------------------------------------------------------*/
#define	PORT_RUSSCS			( volatile UCHAR * )0x00C05010
	#define	SKEW_RL				BIT7
	#define	SKEW_ON				BIT6
	#define	SKEW_CNTR			( BIT5 | BIT4 | BIT3 | BIT2 | BIT1 | BIT0 )
/*--------------------------------------------------------------------------*/
/*	Over current															*/
/*	Rev.(ZY06:BRZ-699)														*/
/*	 Delete RUFL0_FL5VSE,RUFL0_FL5VES										*/
/*	 Add RUFL0_FL5VES4,RUFL0_FL5VSE4,RUFL0_FL5VES2,RUFL0_FL5VSE2			*/
/*--------------------------------------------------------------------------*/
#define	PORT_RUFL0			( volatile UCHAR * )0x00C05018
	#define	RUFL0_FL5VES4		BIT6
	#define	RUFL0_FL5VSE4		BIT5
	#define	RUFL0_FL5VRV		BIT4
	#define	RUFL0_FL5VES2		BIT3
	#define	RUFL0_FL5VUB		BIT2
	#define	RUFL0_FL5VSE2		BIT1
	#define	RUFL0_FL5VPA		BIT0
	#define	RUFL0_RSV			( BIT7 )
#define	PORT_RUFL1			( volatile UCHAR * )0x00C05019
	#define	RUFL1_FL24VRV		BIT3
	#define	RUFL1_FL24VES		BIT2
	#define	RUFL1_FL24VUB		BIT1
	#define	RUFL1_FL24VSE		BIT0
	#define	RUFL1_RSV			( BIT7 | BIT6 | BIT5 | BIT4 )
/*--------------------------------------------------------------------------*/
/*	DAC																		*/
/*--------------------------------------------------------------------------*/
#define	PORT_RUDAC			( volatile UCHAR * )0x00C0501C
	#define	RUDAC_UDAC			BIT7
/*--------------------------------------------------------------------------*/
/*																			*/
/*	Lower (Read)															*/
/*																			*/
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/*	Sensor																	*/
/*	Rev.(ZY01:BRZ-406)														*/
/*	 Add RLS5_LFHS															*/
/*	Rev.(ZY01:BRZ-429)														*/
/*	 Change address of SHOC,SHCC											*/
/*	Rev.(ZY04:BRZ-593)														*/
/*	 Add RLS4_ILOF															*/
/*	Rev.(AA52:BRZ-1554)		for Dual BRU									*/
/*	 Add RLS6_DUAL															*/
/*	Rev.(AA54:BRZ-1557)														*/
/*	 add RLS8_CS1E,RLS10_CS2E,RLS12_CS3E,RLS14_CS4E							*/
/*--------------------------------------------------------------------------*/
#define	PORT_RLS0			( volatile UCHAR * )0x00C05100
	#define	RLS0_C1SET			BIT7
	#define	RLS0_D13C			BIT3
	#define	RLS0_D12C			BIT2
	#define	RLS0_D11C			BIT1
	#define	RLS0_D10C			BIT0
	#define	RLS0_RSV			( BIT6 | BIT5 | BIT4 )
#define	PORT_RLS1			( volatile UCHAR * )0x00C05101
	#define	RLS1_C2SET			BIT7
	#define	RLS1_D23C			BIT3
	#define	RLS1_D22C			BIT2
	#define	RLS1_D21C			BIT1
	#define	RLS1_D20C			BIT0
	#define	RLS1_RSV			( BIT6 | BIT5 | BIT4 )
#define	PORT_RLS2			( volatile UCHAR * )0x00C05102
	#define	RLS2_C3SET			BIT7
	#define	RLS2_D33C			BIT3
	#define	RLS2_D32C			BIT2
	#define	RLS2_D31C			BIT1
	#define	RLS2_D30C			BIT0
	#define	RLS2_RSV			( BIT6 | BIT5 | BIT4 )
#define	PORT_RLS3			( volatile UCHAR * )0x00C05103
	#define	RLS3_C4SET			BIT7
	#define	RLS3_D43C			BIT3
	#define	RLS3_D42C			BIT2
	#define	RLS3_D41C			BIT1
	#define	RLS3_D40C			BIT0
	#define	RLS3_RSV			( BIT6 | BIT5 | BIT4 )
#define	PORT_RLS4			( volatile UCHAR * )0x00C05104
	#define	RLS4_SHOC			BIT5
	#define	RLS4_SHCC			BIT4
	#define	RLS4_ILOF			BIT1
	#define	RLS4_BLLC			BIT0
	#define	RLS4_RSV			( BIT7 | BIT6 | BIT3 | BIT2 )
#define	PORT_RLS5			( volatile UCHAR * )0x00C05105
	#define	RLS5_LFHS			BIT1
	#define	RLS5_LT3S			BIT0
	#define	RLS5_RSV			( BIT7 | BIT6 | BIT5 | BIT4 | BIT3 | BIT2 )
#define	PORT_RLS6			( volatile UCHAR * )0x00C05106
	#define	RLS6_DUAL			BIT4
	#define	RLS6_RSV			( BIT7 | BIT6 | BIT5 | BIT3 | BIT2 | BIT1 | BIT0 )
#define	PORT_RLS7			( volatile UCHAR * )0x00C05107
	#define	RLS7_CR4S			BIT7
	#define	RLS7_CL4S			BIT6
	#define	RLS7_CR3S			BIT5
	#define	RLS7_CL3S			BIT4
	#define	RLS7_CR2S			BIT3
	#define	RLS7_CL2S			BIT2
	#define	RLS7_CR1S			BIT1
	#define	RLS7_CL1S			BIT0
	#define	RLS7_RSV			( 0 )
#define	PORT_RLS8			( volatile UCHAR * )0x00C05108
	#define	RLS8_CE1C			BIT7
	#define	RLS8_CS1E			BIT5
	#define	RLS8_C1NR			BIT4
	#define	RLS8_CT1S			BIT3
	#define	RLS8_NE1C			BIT2
	#define	RLS8_NF1C			BIT1
	#define	RLS8_CF1C			BIT0
	#define	RLS8_RSV			( BIT6 )
#define	PORT_RLS9			( volatile UCHAR * )0x00C05109
	#define	RLS9_CV1C			BIT7
	#define	RLS9_CC1C			BIT4
	#define	RLS9_CO1C			BIT3
	#define	RLS9_CD1C			BIT2
	#define	RLS9_CS1C			BIT1
	#define	RLS9_CP1C			BIT0
	#define	RLS9_RSV			( BIT6 | BIT5 )
#define	PORT_RLS10			( volatile UCHAR * )0x00C0510A
	#define	RLS10_CE2C			BIT7
	#define	RLS10_CS2E			BIT5
	#define	RLS10_C2NR			BIT4
	#define	RLS10_CT2S			BIT3
	#define	RLS10_NE2C			BIT2
	#define	RLS10_NF2C			BIT1
	#define	RLS10_CF2C			BIT0
	#define	RLS10_RSV			( BIT6 )
#define	PORT_RLS11			( volatile UCHAR * )0x00C0510B
	#define	RLS11_CV2C			BIT7
	#define	RLS11_CC2C			BIT4
	#define	RLS11_CO2C			BIT3
	#define	RLS11_CD2C			BIT2
	#define	RLS11_CS2C			BIT1
	#define	RLS11_CP2C			BIT0
	#define	RLS11_RSV			( BIT6 | BIT5 )
#define	PORT_RLS12			( volatile UCHAR * )0x00C0510C
	#define	RLS12_CE3C			BIT7
	#define	RLS12_CS3E			BIT5
	#define	RLS12_C3NR			BIT4
	#define	RLS12_CT3S			BIT3
	#define	RLS12_NE3C			BIT2
	#define	RLS12_NF3C			BIT1
	#define	RLS12_CF3C			BIT0
	#define	RLS12_RSV			( BIT6 )
#define	PORT_RLS13			( volatile UCHAR * )0x00C0510D
	#define	RLS13_CV3C			BIT7
	#define	RLS13_CC3C			BIT4
	#define	RLS13_CO3C			BIT3
	#define	RLS13_CD3C			BIT2
	#define	RLS13_CS3C			BIT1
	#define	RLS13_CP3C			BIT0
	#define	RLS13_RSV			( BIT6 | BIT5 )
#define	PORT_RLS14			( volatile UCHAR * )0x00C0510E
	#define	RLS14_CE4C			BIT7
	#define	RLS14_CS4E			BIT5
	#define	RLS14_C4NR			BIT4
	#define	RLS14_CT4S			BIT3
	#define	RLS14_NE4C			BIT2
	#define	RLS14_NF4C			BIT1
	#define	RLS14_CF4C			BIT0
	#define	RLS14_RSV			( BIT6 )
#define	PORT_RLS15			( volatile UCHAR * )0x00C0510F
	#define	RLS15_CV4C			BIT7
	#define	RLS15_CC4C			BIT4
	#define	RLS15_CO4C			BIT3
	#define	RLS15_CD4C			BIT2
	#define	RLS15_CS4C			BIT1
	#define	RLS15_CP4C			BIT0
	#define	RLS15_RSV			( BIT6 | BIT5 )
/*--------------------------------------------------------------------------*/
/*	Skew counter															*/
/*	Rev.(ZY01:BRZ-429)														*/
/*	 Change all address														*/
/*--------------------------------------------------------------------------*/
#define	PORT_RLC1CS			( volatile UCHAR * )0x00C05120
#define	PORT_RLC2CS			( volatile UCHAR * )0x00C05121
#define	PORT_RLC3CS			( volatile UCHAR * )0x00C05122
#define	PORT_RLC4CS			( volatile UCHAR * )0x00C05123
/*--------------------------------------------------------------------------*/
/*	Over current															*/
/*	Rev.(ZY01:BRZ-429)														*/
/*	 Change bit of FL5VLT,FL24VEX,FL24VCS,FL24VLT							*/
/*	 Delete FL5VLB,FLSHDM,FL24VRV,FL24VLB									*/
/*	 Add FL5VSH,FL5VCS5,FL24VLB2,FL24VLB1									*/
/*--------------------------------------------------------------------------*/
#define	PORT_RLFL0			( volatile UCHAR * )0x00C05118
	#define	RLFL0_FL5VCS4		BIT7
	#define	RLFL0_FL5VCS3		BIT6
	#define	RLFL0_FL5VCS2		BIT5
	#define	RLFL0_FL5VCS1		BIT4
	#define	RLFL0_FL5VRV		BIT3
	#define	RLFL0_FL5VEX		BIT2
	#define	RLFL0_FL5VSH		BIT1
	#define	RLFL0_FL5VLT		BIT0
	#define	RLFL0_RSV			( 0 )
#define	PORT_RLFL1			( volatile UCHAR * )0x00C05119
	#define	RLFL1_FL5VCS5		BIT7
	#define	RLFL1_FL24VSH		BIT5
	#define	RLFL1_FL24VEX		BIT4
	#define	RLFL1_FL24VCS		BIT3
	#define	RLFL1_FL24VLT		BIT2
	#define	RLFL1_FL24VLB2		BIT1
	#define	RLFL1_FL24VLB1		BIT0
	#define	RLFL1_RSV			( BIT6 )
/*--------------------------------------------------------------------------*/
/*	Rev.(AA04:BRZ-1196)														*/
/*	 Add RLUCOM port														*/
/*--------------------------------------------------------------------------*/
#define	PORT_RLUCOM			( volatile UCHAR * )0x00C0511A
	#define	RLUCOM_RSTD			BIT7

/*--------------------------------------------------------------------------*/
/*	DAC																		*/
/*--------------------------------------------------------------------------*/
#define	PORT_RLDAC			( volatile UCHAR * )0x00C0511C
	#define	RLDAC_LDAC			BIT7
/*--------------------------------------------------------------------------*/
/*																			*/
/*	System (Read)															*/
/*																			*/
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/*	Rev.(ZY01:BRZ-429)														*/
/*	 Delete BTNALM,RSRST_BTSSLM,5VNOFF,UILC,BILC,SHT						*/
/*	 Add ILOFF,RJSEL,PAC2,PAC1,PAC0,LOW2,LOW1,LOW0,BNBR						*/
/*	 Change bit of UP2,UP1,UP0,UBSEL,C3C4E									*/
/*	Rev.(ZY04:BRZ-593)														*/
/*	 Delete RSINT_TIMER,RSINT_ILOFF											*/
/*	 Add RSINT_PARITY														*/
/*--------------------------------------------------------------------------*/
#define	PORT_RSIOEN			( volatile UCHAR * )0x00C06000
	#define	RSIOEN_PMG_TO_E		BIT2
	#define	RSIOEN_HMG_TO_E		BIT1
	#define	RSIOEN_EN24V		BIT0
#define	PORT_RSRST			( volatile UCHAR * )0x00C06001
	#define	RSRST_IO_RST_E		BIT0
#define	PORT_RSINT			( volatile UCHAR * )0x00C06002
	#define	RSINT_PARITY		BIT6
	#define	RSINT_LAN			BIT4
	#define	RSINT_USB			BIT3
	#define	RSINT_PNOFF			BIT2
	#define	RSINT_OCINT			BIT0
#define	PORT_RSUSB			( volatile UCHAR * )0x00C06003
	#define	RSUSB_LANRST		BIT4
	#define	RSUSB_USBVBUS		BIT2
	#define	RSUSB_USBON			BIT1
	#define	RSUSB_USBRST		BIT0
#define	PORT_RSUP			( volatile UCHAR * )0x00C06004
	#define	RSUP_UP2			BIT7
	#define	RSUP_UP1			BIT6
	#define	RSUP_UP0			BIT5
	#define	RSUP_RJSEL			BIT4
	#define	RSUP_UBSEL			BIT3
	#define	RSUP_PAC2			BIT2
	#define	RSUP_PAC1			BIT1
	#define	RSUP_PAC0			BIT0
#define	PORT_RSLOW			( volatile UCHAR * )0x00C06005
	#define	RSLOW_LOW2			BIT7
	#define	RSLOW_LOW1			BIT6
	#define	RSLOW_LOW0			BIT5
	#define	RSLOW_C3C4E			BIT1
	#define	RSLOW_BNBR			BIT0
#define	PORT_RSCS			( volatile UCHAR * )0x00C06006
	#define	RSCS_C4NR			BIT3
	#define	RSCS_C3NR			BIT2
	#define	RSCS_C2NR			BIT1
	#define	RSCS_C1NR			BIT0
#define	PORT_RSSR			( volatile UCHAR * )0x00C06008
	#define	RSSR_WDT_TO			BIT7
/*--------------------------------------------------------------------------*/
/*																			*/
/*	System (Write)															*/
/*																			*/
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/*	Rev.(ZY01:BRZ-429)														*/
/*	 Delete BATDS															*/
/*	 Add PRT_CLR,F_PRT														*/
/*	Rev.(ZY04:BRZ-593)														*/
/*	 Change WSINTEN port													*/
/*	Rev.(AA04:BRZ-1196)														*/
/*	 Add WSCRCLR port														*/
/*--------------------------------------------------------------------------*/
#define	PORT_WSIOEN			( volatile UCHAR * )0x00C06100
	#define	WSIOEN_DV_RST		BIT3
	#define	WSIOEN_PMG_TO_E		BIT2
	#define	WSIOEN_HMG_TO_E		BIT1
	#define	WSIOEN_EN24V		BIT0
#define	PORT_WSRST			( volatile UCHAR * )0x00C06101
	#define	WSRST_IO_RST_E		BIT0
#define	PORT_WSINTEN		( volatile UCHAR * )0x00C06102
	#define	WSINTEN_PARITY_E	BIT4
	#define	WSINTEN_LANINT_E	BIT3
	#define	WSINTEN_USBINT_E	BIT2
	#define	WSINTEN_PNOFF_E		BIT1
	#define	WSINTEN_OCINT_E		BIT0
#define	PORT_WSUSB			( volatile UCHAR * )0x00C06103
	#define	WSUSB_LANRST		BIT4
	#define	WSUSB_USBON			BIT1
	#define	WSUSB_USBRST		BIT0
#define	PORT_WSCR0			( volatile UCHAR * )0x00C06108
	#define	WSCR0_WDT_EN		BIT7
	#define	WSCR0_OC_CLR		BIT6
	#define	WSCR0_PRT_CLR		BIT0
#define	PORT_WSCR1			( volatile UCHAR * )0x00C06109
	#define	WSCR1_WDT_CLR		BIT7
	#define	WSCR1_F_PRT			BIT0
#define	PORT_WSCRCLR		( volatile UCHAR * )0x00C0610A
	#define	WSCRCLR_RDCLR		BIT1
/*--------------------------------------------------------------------------*/
/*																			*/
/*																			*/
/*	On-chip peripheral I/O													*/
/*																			*/
/*																			*/
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/*	SCI																		*/
/*--------------------------------------------------------------------------*/
	/*----------------------------------------------------------------------*/
	/*	channel 0															*/
	/*----------------------------------------------------------------------*/
#define	PORT_SCI_SMR0		( volatile UCHAR  * )0xFFFF81A0
#define	PORT_SCI_BRR0		( volatile UCHAR  * )0xFFFF81A1
#define	PORT_SCI_SCR0		( volatile UCHAR  * )0xFFFF81A2
#define	PORT_SCI_TDR0		( volatile UCHAR  * )0xFFFF81A3
#define	PORT_SCI_SSR0		( volatile UCHAR  * )0xFFFF81A4
#define	PORT_SCI_RDR0		( volatile UCHAR  * )0xFFFF81A5
#define	PORT_SCI_SDCR0		( volatile UCHAR  * )0xFFFF81A6
	/*----------------------------------------------------------------------*/
	/*	channel 1															*/
	/*----------------------------------------------------------------------*/
#define	PORT_SCI_SMR1		( volatile UCHAR  * )0xFFFF81B0
#define	PORT_SCI_BRR1		( volatile UCHAR  * )0xFFFF81B1
#define	PORT_SCI_SCR1		( volatile UCHAR  * )0xFFFF81B2
#define	PORT_SCI_TDR1		( volatile UCHAR  * )0xFFFF81B3
#define	PORT_SCI_SSR1		( volatile UCHAR  * )0xFFFF81B4
#define	PORT_SCI_RDR1		( volatile UCHAR  * )0xFFFF81B5
#define	PORT_SCI_SDCR1		( volatile UCHAR  * )0xFFFF81B6
	/*----------------------------------------------------------------------*/
	/*	channel 2															*/
	/*----------------------------------------------------------------------*/
#define	PORT_SCI_SMR2		( volatile UCHAR  * )0xFFFF81C0
#define	PORT_SCI_BRR2		( volatile UCHAR  * )0xFFFF81C1
#define	PORT_SCI_SCR2		( volatile UCHAR  * )0xFFFF81C2
#define	PORT_SCI_TDR2		( volatile UCHAR  * )0xFFFF81C3
#define	PORT_SCI_SSR2		( volatile UCHAR  * )0xFFFF81C4
#define	PORT_SCI_RDR2		( volatile UCHAR  * )0xFFFF81C5
#define	PORT_SCI_SDCR2		( volatile UCHAR  * )0xFFFF81C6
	/*----------------------------------------------------------------------*/
	/*	channel 3															*/
	/*----------------------------------------------------------------------*/
#define	PORT_SCI_SMR3		( volatile UCHAR  * )0xFFFF81D0
#define	PORT_SCI_BRR3		( volatile UCHAR  * )0xFFFF81D1
#define	PORT_SCI_SCR3		( volatile UCHAR  * )0xFFFF81D2
#define	PORT_SCI_TDR3		( volatile UCHAR  * )0xFFFF81D3
#define	PORT_SCI_SSR3		( volatile UCHAR  * )0xFFFF81D4
#define	PORT_SCI_RDR3		( volatile UCHAR  * )0xFFFF81D5
#define	PORT_SCI_SDCR3		( volatile UCHAR  * )0xFFFF81D6
	/*----------------------------------------------------------------------*/
	/*	SMR register bit													*/
	/*----------------------------------------------------------------------*/
	#define	SMR_CA				BIT7
	#define	SMR_CHR				BIT6
	#define	SMR_PE				BIT5
	#define	SMR_OE				BIT4
	#define	SMR_STOP			BIT3
	#define	SMR_MP				BIT2
	#define	SMR_CKS1			BIT1
	#define	SMR_CKS0			BIT0
	/*----------------------------------------------------------------------*/
	/*	SCR register bit													*/
	/*----------------------------------------------------------------------*/
	#define	SCR_TIE				BIT7
	#define	SCR_RIE				BIT6
	#define	SCR_TE				BIT5
	#define	SCR_RE				BIT4
	#define	SCR_MPIE			BIT3
	#define	SCR_TEIE			BIT2
	#define	SCR_CKE1			BIT1
	#define	SCR_CKE0			BIT0
	/*----------------------------------------------------------------------*/
	/*	SSR register bit													*/
	/*----------------------------------------------------------------------*/
	#define	SSR_TDRE			BIT7
	#define	SSR_RDRF			BIT6
	#define	SSR_ORER			BIT5
	#define	SSR_FER				BIT4
	#define	SSR_PER				BIT3
	#define	SSR_TEND			BIT2
	#define	SSR_MPB				BIT1
	#define	SSR_MPBT			BIT0
	/*----------------------------------------------------------------------*/
	/*	SDCR register bit													*/
	/*----------------------------------------------------------------------*/
	#define	SDCR_DIR			BIT3
	#define	SDCR_RSV			( BIT7 | BIT6 | BIT5 | BIT4 | BIT1 )
/*--------------------------------------------------------------------------*/
/*	MTU																		*/
/*--------------------------------------------------------------------------*/
	/*----------------------------------------------------------------------*/
	/*	channel 3,4															*/
	/*----------------------------------------------------------------------*/
#define	PORT_MTU_TCR3		( volatile UCHAR  * )0xFFFF8200
#define	PORT_MTU_TCR4		( volatile UCHAR  * )0xFFFF8201
#define	PORT_MTU_TMDR3		( volatile UCHAR  * )0xFFFF8202
#define	PORT_MTU_TMDR4		( volatile UCHAR  * )0xFFFF8203
#define	PORT_MTU_TIORH3		( volatile UCHAR  * )0xFFFF8204
#define	PORT_MTU_TIORL3		( volatile UCHAR  * )0xFFFF8205
#define	PORT_MTU_TIORH4		( volatile UCHAR  * )0xFFFF8206
#define	PORT_MTU_TIORL4		( volatile UCHAR  * )0xFFFF8207
#define	PORT_MTU_TIER3		( volatile UCHAR  * )0xFFFF8208
#define	PORT_MTU_TIER4		( volatile UCHAR  * )0xFFFF8209
#define	PORT_MTU_TOER		( volatile UCHAR  * )0xFFFF820A
#define	PORT_MTU_TOCR		( volatile UCHAR  * )0xFFFF820B
#define	PORT_MTU_TGCR		( volatile UCHAR  * )0xFFFF820D
#define	PORT_MTU_TCNT3		( volatile USHORT * )0xFFFF8210
#define	PORT_MTU_TCNT4		( volatile USHORT * )0xFFFF8212
#define	PORT_MTU_TCDR		( volatile USHORT * )0xFFFF8214
#define	PORT_MTU_TDDR		( volatile USHORT * )0xFFFF8216
#define	PORT_MTU_TGRA3		( volatile USHORT * )0xFFFF8218
#define	PORT_MTU_TGRB3		( volatile USHORT * )0xFFFF821A
#define	PORT_MTU_TGRA4		( volatile USHORT * )0xFFFF821C
#define	PORT_MTU_TGRB4		( volatile USHORT * )0xFFFF821E
#define	PORT_MTU_TCNTS		( volatile USHORT * )0xFFFF8220
#define	PORT_MTU_TCBR		( volatile USHORT * )0xFFFF8222
#define	PORT_MTU_TGRC3		( volatile USHORT * )0xFFFF8224
#define	PORT_MTU_TGRD3		( volatile USHORT * )0xFFFF8226
#define	PORT_MTU_TGRC4		( volatile USHORT * )0xFFFF8228
#define	PORT_MTU_TGRD4		( volatile USHORT * )0xFFFF822A
#define	PORT_MTU_TSR3		( volatile UCHAR  * )0xFFFF822C
#define	PORT_MTU_TSR4		( volatile UCHAR  * )0xFFFF822D
	/*----------------------------------------------------------------------*/
	/*	common																*/
	/*----------------------------------------------------------------------*/
#define	PORT_MTU_TSTR		( volatile UCHAR  * )0xFFFF8240
#define	PORT_MTU_TSYR		( volatile UCHAR  * )0xFFFF8241
	/*----------------------------------------------------------------------*/
	/*	channel 0															*/
	/*----------------------------------------------------------------------*/
#define	PORT_MTU_TCR0		( volatile UCHAR  * )0xFFFF8260
#define	PORT_MTU_TMDR0		( volatile UCHAR  * )0xFFFF8261
#define	PORT_MTU_TIORH0		( volatile UCHAR  * )0xFFFF8262
#define	PORT_MTU_TIORL0		( volatile UCHAR  * )0xFFFF8263
#define	PORT_MTU_TIER0		( volatile UCHAR  * )0xFFFF8264
#define	PORT_MTU_TSR0		( volatile UCHAR  * )0xFFFF8265
#define	PORT_MTU_TCNT0		( volatile USHORT * )0xFFFF8266
#define	PORT_MTU_TGRA0		( volatile USHORT * )0xFFFF8268
#define	PORT_MTU_TGRB0		( volatile USHORT * )0xFFFF826A
#define	PORT_MTU_TGRC0		( volatile USHORT * )0xFFFF826C
#define	PORT_MTU_TGRD0		( volatile USHORT * )0xFFFF826E
	/*----------------------------------------------------------------------*/
	/*	channel 1															*/
	/*----------------------------------------------------------------------*/
#define	PORT_MTU_TCR1		( volatile UCHAR  * )0xFFFF8280
#define	PORT_MTU_TMDR1		( volatile UCHAR  * )0xFFFF8281
#define	PORT_MTU_TIOR1		( volatile UCHAR  * )0xFFFF8282
#define	PORT_MTU_TIER1		( volatile UCHAR  * )0xFFFF8284
#define	PORT_MTU_TSR1		( volatile UCHAR  * )0xFFFF8285
#define	PORT_MTU_TCNT1		( volatile USHORT * )0xFFFF8286
#define	PORT_MTU_TGRA1		( volatile USHORT * )0xFFFF8288
#define	PORT_MTU_TGRB1		( volatile USHORT * )0xFFFF828A
	/*----------------------------------------------------------------------*/
	/*	channel 2															*/
	/*----------------------------------------------------------------------*/
#define	PORT_MTU_TCR2		( volatile UCHAR  * )0xFFFF82A0
#define	PORT_MTU_TMDR2		( volatile UCHAR  * )0xFFFF82A1
#define	PORT_MTU_TIOR2		( volatile UCHAR  * )0xFFFF82A2
#define	PORT_MTU_TIER2		( volatile UCHAR  * )0xFFFF82A4
#define	PORT_MTU_TSR2		( volatile UCHAR  * )0xFFFF82A5
#define	PORT_MTU_TCNT2		( volatile USHORT * )0xFFFF82A6
#define	PORT_MTU_TGRA2		( volatile USHORT * )0xFFFF82A8
#define	PORT_MTU_TGRB2		( volatile USHORT * )0xFFFF82AA
	/*----------------------------------------------------------------------*/
	/*	TSTR register bit													*/
	/*----------------------------------------------------------------------*/
	#define	TSTR_CST4			BIT7
	#define	TSTR_CST3			BIT6
	#define	TSTR_CST2			BIT2
	#define	TSTR_CST1			BIT1
	#define	TSTR_CST0			BIT0
	/*----------------------------------------------------------------------*/
	/*	TSYR register bit													*/
	/*----------------------------------------------------------------------*/
	#define	TSYR_SYNC4			BIT7
	#define	TSYR_SYNC3			BIT6
	#define	TSYR_SYNC2			BIT2
	#define	TSYR_SYNC1			BIT1
	#define	TSYR_SYNC0			BIT0
	/*----------------------------------------------------------------------*/
	/*	TCR register bit													*/
	/*----------------------------------------------------------------------*/
	#define	TCR_CCLR2			BIT7
	#define	TCR_CCLR1			BIT6
	#define	TCR_CCLR0			BIT5
	#define	TCR_CKEG1			BIT4
	#define	TCR_CKEG0			BIT3
	#define	TCR_TPSC2			BIT2
	#define	TCR_TPSC1			BIT1
	#define	TCR_TPSC0			BIT0
	/*----------------------------------------------------------------------*/
	/*	TMDR register bit													*/
	/*----------------------------------------------------------------------*/
	#define	TMDR_BFB			BIT5
	#define	TMDR_BFA			BIT4
	#define	TMDR_MD3			BIT3
	#define	TMDR_MD2			BIT2
	#define	TMDR_MD1			BIT1
	#define	TMDR_MD0			BIT0
	#define	TMDR_RSV			( BIT7 | BIT6 )
	/*----------------------------------------------------------------------*/
	/*	TIORH register bit													*/
	/*----------------------------------------------------------------------*/
	#define	TIORH_IOB3			BIT7
	#define	TIORH_IOB2			BIT6
	#define	TIORH_IOB1			BIT5
	#define	TIORH_IOB0			BIT4
	#define	TIORH_IOA3			BIT3
	#define	TIORH_IOA2			BIT2
	#define	TIORH_IOA1			BIT1
	#define	TIORH_IOA0			BIT0
	/*----------------------------------------------------------------------*/
	/*	TIORL register bit													*/
	/*----------------------------------------------------------------------*/
	#define	TIORL_IOD3			BIT7
	#define	TIORL_IOD2			BIT6
	#define	TIORL_IOD1			BIT5
	#define	TIORL_IOD0			BIT4
	#define	TIORL_IOC3			BIT3
	#define	TIORL_IOC2			BIT2
	#define	TIORL_IOC1			BIT1
	#define	TIORL_IOC0			BIT0
	/*----------------------------------------------------------------------*/
	/*	TIOR register bit													*/
	/*----------------------------------------------------------------------*/
	#define	TIOR_IOB3			BIT7
	#define	TIOR_IOB2			BIT6
	#define	TIOR_IOB1			BIT5
	#define	TIOR_IOB0			BIT4
	#define	TIOR_IOA3			BIT3
	#define	TIOR_IOA2			BIT2
	#define	TIOR_IOA1			BIT1
	#define	TIOR_IOA0			BIT0
	/*----------------------------------------------------------------------*/
	/*	TIER register bit													*/
	/*----------------------------------------------------------------------*/
	#define	TIER_TTGE			BIT7
	#define	TIER_TCIEU			BIT5
	#define	TIER_TCIEV			BIT4
	#define	TIER_TGIED			BIT3
	#define	TIER_TGIEC			BIT2
	#define	TIER_TGIEB			BIT1
	#define	TIER_TGIEA			BIT0
	#define	TIER_RSV			( BIT6 )
	/*----------------------------------------------------------------------*/
	/*	TSR register bit													*/
	/*----------------------------------------------------------------------*/
	#define	TSR_TCFD			BIT7
	#define	TSR_TCFU			BIT5
	#define	TSR_TCFV			BIT4
	#define	TSR_TGFD			BIT3
	#define	TSR_TGFC			BIT2
	#define	TSR_TGFB			BIT1
	#define	TSR_TGFA			BIT0
	#define	TSR_RSV				( BIT6 )
	/*----------------------------------------------------------------------*/
	/*	TOER register bit													*/
	/*----------------------------------------------------------------------*/
	#define	TOER_OE4D			BIT5
	#define	TOER_OE4C			BIT4
	#define	TOER_OE3D			BIT3
	#define	TOER_OE4B			BIT2
	#define	TOER_OE4A			BIT1
	#define	TOER_OE3B			BIT0
	#define	TOER_RSV			( BIT7 | BIT6 )
	/*----------------------------------------------------------------------*/
	/*	TOCR register bit													*/
	/*----------------------------------------------------------------------*/
	#define	TOCR_PSYE			BIT6
	#define	TOCR_OLSN			BIT1
	#define	TOCR_OLSP			BIT0
	/*----------------------------------------------------------------------*/
	/*	TGCR register bit													*/
	/*----------------------------------------------------------------------*/
	#define	TGCR_BDC			BIT6
	#define	TGCR_N				BIT5
	#define	TGCR_P				BIT4
	#define	TGCR_FB				BIT3
	#define	TGCR_WF				BIT2
	#define	TGCR_VF				BIT1
	#define	TGCR_UF				BIT0
	#define	TGCR_RSV			( BIT7 )
/*--------------------------------------------------------------------------*/
/*	INTC																	*/
/*--------------------------------------------------------------------------*/
#define	PORT_INTC_IPRA		( volatile USHORT * )0xFFFF8348
#define	PORT_INTC_IPRB		( volatile USHORT * )0xFFFF834A
#define	PORT_INTC_IPRC		( volatile USHORT * )0xFFFF834C
#define	PORT_INTC_IPRD		( volatile USHORT * )0xFFFF834E
#define	PORT_INTC_IPRE		( volatile USHORT * )0xFFFF8350
#define	PORT_INTC_IPRF		( volatile USHORT * )0xFFFF8352
#define	PORT_INTC_IPRG		( volatile USHORT * )0xFFFF8354
#define	PORT_INTC_IPRH		( volatile USHORT * )0xFFFF8356
#define	PORT_INTC_ICR1		( volatile USHORT * )0xFFFF8358
#define	PORT_INTC_ISR		( volatile USHORT * )0xFFFF835A
#define	PORT_INTC_IPRI		( volatile USHORT * )0xFFFF835C
#define	PORT_INTC_IPRJ		( volatile USHORT * )0xFFFF835E
#define	PORT_INTC_ICR2		( volatile USHORT * )0xFFFF8366
/*--------------------------------------------------------------------------*/
/*	I/O																		*/
/*--------------------------------------------------------------------------*/
#define	PORT_IO_PADRH		( volatile USHORT * )0xFFFF8380
#define	PORT_IO_PADRL		( volatile USHORT * )0xFFFF8382
#define	PORT_IO_PBDR		( volatile USHORT * )0xFFFF8390
#define	PORT_IO_PCDR		( volatile USHORT * )0xFFFF8392
#define	PORT_IO_PDDRH		( volatile USHORT * )0xFFFF83A0
#define	PORT_IO_PDDRL		( volatile USHORT * )0xFFFF83A2
#define	PORT_IO_PEDRL		( volatile USHORT * )0xFFFF83B0
#define	PORT_IO_PFDR		( volatile UCHAR  * )0xFFFF83B3
/*--------------------------------------------------------------------------*/
/*	PFC																		*/
/*--------------------------------------------------------------------------*/
#define	PORT_PFC_PAIORH		( volatile USHORT * )0xFFFF8384
#define	PORT_PFC_PAIORL		( volatile USHORT * )0xFFFF8386
#define	PORT_PFC_PACRH		( volatile USHORT * )0xFFFF8388
#define	PORT_PFC_PACRL1		( volatile USHORT * )0xFFFF838C
#define	PORT_PFC_PACRL2		( volatile USHORT * )0xFFFF838E
#define	PORT_PFC_PBIOR		( volatile USHORT * )0xFFFF8394
#define	PORT_PFC_PCIOR		( volatile USHORT * )0xFFFF8396
#define	PORT_PFC_PBCR1		( volatile USHORT * )0xFFFF8398
#define	PORT_PFC_PBCR2		( volatile USHORT * )0xFFFF839A
#define	PORT_PFC_PCCR		( volatile USHORT * )0xFFFF839C
#define	PORT_PFC_PDIORH		( volatile USHORT * )0xFFFF83A4
#define	PORT_PFC_PDIORL		( volatile USHORT * )0xFFFF83A6
#define	PORT_PFC_PDCRH1		( volatile USHORT * )0xFFFF83A8
#define	PORT_PFC_PDCRH2		( volatile USHORT * )0xFFFF83AA
#define	PORT_PFC_PDCRL1		( volatile USHORT * )0xFFFF83AC
#define	PORT_PFC_PDCRL2		( volatile USHORT * )0xFFFF83AE
#define	PORT_PFC_PEIORL		( volatile USHORT * )0xFFFF83B4
#define	PORT_PFC_PECRL1		( volatile USHORT * )0xFFFF83B8
#define	PORT_PFC_PECRL2		( volatile USHORT * )0xFFFF83BA
/*--------------------------------------------------------------------------*/
/*	POE																		*/
/*--------------------------------------------------------------------------*/
#define	PORT_POE_ICSR1		( volatile USHORT * )0xFFFF83C0
#define	PORT_POE_OCSR		( volatile USHORT * )0xFFFF83C2
/*--------------------------------------------------------------------------*/
/*	CMT																		*/
/*--------------------------------------------------------------------------*/
#define	PORT_CMT_CMSTR		( volatile USHORT * )0xFFFF83D0
#define	PORT_CMT_CMCSR0		( volatile USHORT * )0xFFFF83D2
#define	PORT_CMT_CMCNT0		( volatile USHORT * )0xFFFF83D4
#define	PORT_CMT_CMCOR0		( volatile USHORT * )0xFFFF83D6
#define	PORT_CMT_CMCSR1		( volatile USHORT * )0xFFFF83D8
#define	PORT_CMT_CMCNT1		( volatile USHORT * )0xFFFF83DA
#define	PORT_CMT_CMCOR1		( volatile USHORT * )0xFFFF83DC
	/*----------------------------------------------------------------------*/
	/*	CMSTR register bit													*/
	/*----------------------------------------------------------------------*/
	#define	CMSTR_STR1			BIT1
	#define	CMSTR_STR0			BIT0
	/*----------------------------------------------------------------------*/
	/*	CMCSR register bit													*/
	/*----------------------------------------------------------------------*/
	#define	CMCSR_CMF			BIT7
	#define	CMCSR_CMIE			BIT6
	#define	CMCSR_CKS1			BIT1
	#define	CMCSR_CKS0			BIT0
/*--------------------------------------------------------------------------*/
/*	A/D																		*/
/*--------------------------------------------------------------------------*/
#define	PORT_AD_ADDR0		( volatile USHORT * )0xFFFF8420
#define	PORT_AD_ADDR1		( volatile USHORT * )0xFFFF8422
#define	PORT_AD_ADDR2		( volatile USHORT * )0xFFFF8424
#define	PORT_AD_ADDR3		( volatile USHORT * )0xFFFF8426
#define	PORT_AD_ADDR4		( volatile USHORT * )0xFFFF8428
#define	PORT_AD_ADDR5		( volatile USHORT * )0xFFFF842A
#define	PORT_AD_ADDR6		( volatile USHORT * )0xFFFF842C
#define	PORT_AD_ADDR7		( volatile USHORT * )0xFFFF842E
#define	PORT_AD_ADCSR0		( volatile UCHAR  * )0xFFFF8480
#define	PORT_AD_ADCSR1		( volatile UCHAR  * )0xFFFF8481
#define	PORT_AD_ADCR0		( volatile UCHAR  * )0xFFFF8488
#define	PORT_AD_ADCR1		( volatile UCHAR  * )0xFFFF8489
	/*----------------------------------------------------------------------*/
	/*	Rev.(ZT02:BRZ-1108)		add											*/
	/*	ADCSR register bit													*/
	/*----------------------------------------------------------------------*/
	#define	ADCSR_ADF			BIT7
	#define	ADCSR_ADIE			BIT6
	#define	ADCSR_ADM			BIT4
	#define	ADCSR_CH1			BIT1
	#define	ADCSR_CH0			BIT0
	#define	ADCSR_RSV			( BIT3 )
	/*----------------------------------------------------------------------*/
	/*	Rev.(ZT02:BRZ-1108)		add											*/
	/*	ADCR register bit													*/
	/*----------------------------------------------------------------------*/
	#define	ADCR_TRGE			BIT7
	#define	ADCR_CKS1			BIT6
	#define	ADCR_CKS0			BIT5
	#define	ADCR_ADST			BIT4
	#define	ADCR_ADCS			BIT3
	#define	ADCR_RSV			( BIT2 | BIT1 | BIT0)
/*--------------------------------------------------------------------------*/
/*	UBC																		*/
/*--------------------------------------------------------------------------*/
#define	PORT_UBC_UBARH		( volatile USHORT * )0xFFFF8600
#define	PORT_UBC_UBARL		( volatile USHORT * )0xFFFF8602
#define	PORT_UBC_UBAMRH		( volatile USHORT * )0xFFFF8604
#define	PORT_UBC_UBAMRL		( volatile USHORT * )0xFFFF8606
#define	PORT_UBC_UBBR		( volatile USHORT * )0xFFFF8608
#define	PORT_UBC_UBCR		( volatile USHORT * )0xFFFF860A
/*--------------------------------------------------------------------------*/
/*	WDT																		*/
/*--------------------------------------------------------------------------*/
#define	PORT_WDT_TCSR_W		( volatile USHORT * )0xFFFF8610
#define	PORT_WDT_TCSR_R		( volatile UCHAR  * )0xFFFF8610
#define	PORT_WDT_TCNT_W		( volatile USHORT * )0xFFFF8610
#define	PORT_WDT_TCNT_R		( volatile UCHAR  * )0xFFFF8611
#define	PORT_WDT_RSTCSR_W	( volatile USHORT * )0xFFFF8612
#define	PORT_WDT_RSTCSR_R	( volatile UCHAR  * )0xFFFF8613
/*--------------------------------------------------------------------------*/
/*	MST																		*/
/*--------------------------------------------------------------------------*/
#define	PORT_MST_SBYCR		( volatile UCHAR  * )0xFFFF8614
#define	PORT_MST_SYSCR		( volatile UCHAR  * )0xFFFF8618
#define	PORT_MST_MSTCR1		( volatile USHORT * )0xFFFF861C
#define	PORT_MST_MSTCR2		( volatile USHORT * )0xFFFF861E
	/*----------------------------------------------------------------------*/
	/*	SBYCR register bit													*/
	/*----------------------------------------------------------------------*/
	#define	SBYCR_SSBY			BIT7				/* Software Standby		*/
	#define	SBYCR_HIZ			BIT6				/* Port High-Impedance	*/
	#define	SBYCR_IRQEH			BIT1				/* IRQ7-4 Enable		*/
	#define	SBYCR_IRQEL			BIT0				/* IRQ3-0 Enable		*/
	#define	SBYCR_RSV			(BIT4|BIT3|BIT2)	/* (reserved)			*/
	/*----------------------------------------------------------------------*/
	/*	SYSCR register bit													*/
	/*----------------------------------------------------------------------*/
	#define	SYSCR_AUDSRST		BIT1				/* AUD Software-Reset	*/
	#define	SYSCR_RAME			BIT0				/* On-Bord SRAM Enable	*/
	#define	SYSCR_RSV			(BIT7|BIT6)			/* (reserved)			*/
	/*----------------------------------------------------------------------*/
	/*	MSTCR1 register bit													*/
	/*----------------------------------------------------------------------*/
	#define	MSTCR1_MSTP27		BIT11					/* On-Bord SRAM			*/
	#define	MSTCR1_MSTP26		BIT10					/* On-Bord Flash ROM	*/
	#define	MSTCR1_MSTP25		BIT9					/* DTC					*/
	#define	MSTCR1_MSTP24		BIT8					/* DMAC					*/
	#define	MSTCR1_MSTP21		BIT5					/* IIC					*/
	#define	MSTCR1_MSTP19		BIT3					/* SCI-3				*/
	#define	MSTCR1_MSTP18		BIT2					/* SCI-2				*/
	#define	MSTCR1_MSTP17		BIT1					/* SCI-1				*/
	#define	MSTCR1_MSTP16		BIT0					/* SCI-0				*/
	#define	MSTCR1_RSV			(BIT15|BIT14|BIT13|BIT12|BIT4)	/* (reserved)	*/
	/*----------------------------------------------------------------------*/
	/*	MSTCR2 register bit													*/
	/*----------------------------------------------------------------------*/
	#define	MSTCR2_MSTP13		BIT13						/* MTU			*/
	#define	MSTCR2_MSTP12		BIT12						/* CMT			*/
	#define	MSTCR2_MSTP5		BIT5						/* A/D-1		*/
	#define	MSTCR2_MSTP4		BIT4						/* A/D-2		*/
	#define	MSTCR2_MSTP3		BIT3						/* AUD			*/
	#define	MSTCR2_MSTP2		BIT2						/* H-UDI		*/
	#define	MSTCR2_MSTP0		BIT0						/* UBC			*/
	#define	MSTCR2_RSV			(BIT15|BIT14|BIT7|BIT6)		/* (reserved)	*/
/*--------------------------------------------------------------------------*/
/*	BSC																		*/
/*--------------------------------------------------------------------------*/
#define	PORT_BSC_BCR1		( volatile USHORT * )0xFFFF8620
#define	PORT_BSC_BCR2		( volatile USHORT * )0xFFFF8622
#define	PORT_BSC_WCR1		( volatile USHORT * )0xFFFF8624
#define	PORT_BSC_WCR2		( volatile USHORT * )0xFFFF8626
/*--------------------------------------------------------------------------*/
/*	DMAC																	*/
/*--------------------------------------------------------------------------*/
#define	PORT_DMA_DMAOR		( volatile USHORT * )0xFFFF86B0
#define	PORT_DMA_SAR0		( volatile ULONG  * )0xFFFF86C0
#define	PORT_DMA_DAR0		( volatile ULONG  * )0xFFFF86C4
#define	PORT_DMA_DMATCR0	( volatile ULONG  * )0xFFFF86C8
#define	PORT_DMA_CHCR0		( volatile ULONG  * )0xFFFF86CC
#define	PORT_DMA_SAR1		( volatile ULONG  * )0xFFFF86D0
#define	PORT_DMA_DAR1		( volatile ULONG  * )0xFFFF86D4
#define	PORT_DMA_DMATCR1	( volatile ULONG  * )0xFFFF86D8
#define	PORT_DMA_CHCR1		( volatile ULONG  * )0xFFFF86DC
#define	PORT_DMA_SAR2		( volatile ULONG  * )0xFFFF86E0
#define	PORT_DMA_DAR2		( volatile ULONG  * )0xFFFF86E4
#define	PORT_DMA_DMATCR2	( volatile ULONG  * )0xFFFF86E8
#define	PORT_DMA_CHCR2		( volatile ULONG  * )0xFFFF86EC
#define	PORT_DMA_SAR3		( volatile ULONG  * )0xFFFF86F0
#define	PORT_DMA_DAR3		( volatile ULONG  * )0xFFFF86F4
#define	PORT_DMA_DMATCR3	( volatile ULONG  * )0xFFFF86F8
#define	PORT_DMA_CHCR3		( volatile ULONG  * )0xFFFF86FC
/*--------------------------------------------------------------------------*/
/*	DTC																		*/
/*--------------------------------------------------------------------------*/
#define	PORT_DTC_DTEA		( volatile UCHAR  * )0xFFFF8700
#define	PORT_DTC_DTEB		( volatile UCHAR  * )0xFFFF8701
#define	PORT_DTC_DTEC		( volatile UCHAR  * )0xFFFF8702
#define	PORT_DTC_DTED		( volatile UCHAR  * )0xFFFF8703
#define	PORT_DTC_DTCSR		( volatile USHORT * )0xFFFF8706
#define	PORT_DTC_DTBR		( volatile USHORT * )0xFFFF8708
#define	PORT_DTC_DTEE		( volatile UCHAR  * )0xFFFF8710
#define	PORT_DTC_DTEG		( volatile UCHAR  * )0xFFFF8712
/*--------------------------------------------------------------------------*/
/*	A/D																		*/
/*--------------------------------------------------------------------------*/
#define	PORT_AD_ADTSR		( volatile UCHAR  * )0xFFFF87F4
