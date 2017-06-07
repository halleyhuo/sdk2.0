/***

	*************************************************************************
	*																		*
	*		header file for error											*
	*																		*
	*														ERROR.H			*
	*************************************************************************
	ALL RIGHTS RESERVED, COPYRIGHT(C) FUJITSU FRONTECH LIMITED. 2002-2007

	SN			Date		Name		Revision.No.	Contents
	-------------------------------------------------------------------------
	001-ZZ01	2002/11/07	M.Kamimura	<BRZ-001>		The First Version
				2003/03/10	A.Maruyama					Real programing start
				2003/03/11	M.Banba						Add	Jam Error
				2003/03/13	M.Kibe						Add	Mecha Error
				2003/03/18	Y.Saito						Add Separator,Escrow and PreAcceptor Error
	002-ZZ02	2003/04/14	A.Kojima	<BRZ-016>		Add E_WAIT_xDAC, E_ROTATION_TDCM
										<BRZ-019>		Add E_OVER_MAX_LEVEL_xxxx, E_OFF_xxxx
	003-ZZ03	2003/04/22	A.Kojima	<BRZ-021>		Change E_OVER_MAX_LEVEL_xxxx, E_OFF_xxxx
														for new upper(A3 Mech.)
				2003/04/23	M.Banba		<BRZ-021>		Change sensor flag for new upper(A3 Mech.)
				2003/04/28	M.Banba		<BRZ-044>		change error code no.
				2003/04/30	A.Maruyama	<BRZ-058>		add error code. and change carrier error lavel.
				2003/05/06	M.Banba		<BRZ-060>		Medium residual error addition
				2003/05/07	Y.Saito		<BRZ-079>		add error code.
				2003/05/13	M.Kamimura	<BRZ-112>		add error code.(E_REMAIN_EELS/EERS/PASS)
							A.Maruyama	<BRZ-115>		add error code
														 E_RETRY_BACKWARD_PAC_BELT
														 E_RETRY_DOWN_PAC_CLAMP/E_RETRY_UP_PAC_CLAMP
	004-ZZ04	2003/05/22	M.Kamimura	<BRZ-128>		add error code.
														 E_UNJUST_COMMAND
														 E_OUTSIDE_EVENT
							M.Kibe		<BRZ-134>		add error code
														 E_RETRY_OPEN_SHT
														 E_RETRY_CLOSE_SHT
				2003/06/18	M.Kamimura	<BRZ-166>		add error code.(E_UNJUST_PARAMETER_Ax)
							Y.Saito		<BRZ-170>		add error code.(E_WATCH_ILLEGAL_SENSOR)
	005-ZZ06	2003/07/15	Y.Saito		<BRZ-191>		add error code.(E_START_VALIDATE_BV)
														add error code.(E_BV_UNJUST_RECEPTION)
														add error code.(E_UNJUST_BUF_BV)
							M.Kibe		<BRZ-224>		add error code.(E_LOCK_RELEASE_NG_CA1)
														add error code.(E_LOCK_RELEASE_NG_CA2)
														add error code.(E_LOCK_RELEASE_NG_CA3)
														add error code.(E_LOCK_RELEASE_NG_CA4)
				2003/07/18	M.Banba		<BRZ-245>		add error code.
														:E_BV_BUSY
														:E_BV_RESPONSE_TIMEOUT
														:E_BV_RESPONSE_DISCORD_SUM
														:E_BV_RESPONSE_DISCORD_LENGTH
														:E_BV_FAILURE_RESET
				2003/07/18	M.Kamimura	<BRZ-246>		add error code.
														:E_REMAIN_PATH
				2003/07/31	Y.Saito		<BRZ-290>		add error code.
														:E_RETRY_ROTARY_SEP
														:E_RETRY_ROTARY_CA1
														:E_RETRY_ROTARY_CA2
														:E_RETRY_ROTARY_CA3
														:E_RETRY_ROTARY_CA4
				2003/08/01	Y.Saito		<BRZ-289>		add error code.
														:E_BV_NOT_RECOGNIZED_OVER
				2003/08/04	M.Kamimura	<BRZ-285>		add error code.
														:E_NOTHING_PARAMETER_A1
				2003/08/08	Y.Saito		<BRZ-311>		add error code.
														:E_NOT_SUIT_NUMBER_BILL
				2003/08/20	A.Kojima	<BRZ-295>		add error code.
														:E_OVER_MAX_LEVEL_PDSS,E_OFF_PDSS
							A.Maruyama	<BRZ-321>		add error code.
														:E_RECEIPT_UNJUST_xx
														  xx : LENGTH/FORMAT/BLOCK_NUMBER/SUM
				2003/08/08	Y.Saito		<BRZ-311>		add error code.
														:E_FULL_FIT
														:E_FULL_RJT
														:E_FULL_CPT
				2003/08/25	M.Banba		<BRZ-285>		Different denominations number-of-sheets over is added.
														:E_BV_DIFFERENT_OVER
														:E_BV_DAMAGED_OVER(Un-supporting)
														:E_BV_COUNTERFEIT_OVER
				2003/08/26	M.Kamimura	<BRZ-285>		add error code.
														:E_RECEIPT_UNJUST_CLASS
				2003/08/27	M.Kibe		<BRZ-337>		Deletion error code.
														:E_UNCERTAINTY_PAC_CARRIER
														:E_RETRY_PICK_CA1
														:E_RETRY_PICK_CA2
														:E_RETRY_PICK_CA3
														:E_RETRY_PICK_CA4
	006-ZZ07	2003/09/02	M.Kibe		<BRZ-337>		Deletion error code.
														:E_SNS_SSGC_SEP
														:E_SNS_SSLC_SEP
										<BRZ-345>		add error code.
														:E_THINCK_POLC_PAC
				2003/09/10	M.Kamimura	<BRZ-362>		add error code.
														:E_BV_UNJUST_VD
				2003/09/17	M.Kamimura	<BRZ-372>		add error code.
														:E_REMAIN_PAC
														:E_OUTSIDE_REMAIN
				2003/09/20	A.Maruyama	<BRZ-386>		add error code for re-download
														:E_FLASH_ERASE
														:E_FLASH_WRITE
														:E_UNJUST_PARAMETER_H0
														:E_DOWNLOAD_SEQUENCE
	007-ZY01	2003/10/01	M.Kibe		<BRZ-394>		add error code.
														:E_THRUST_COMB_SEP
														:E_ESCAPE_COMB_SEP
										<BRZ-397>		add error code.
														:E_REMAIN_PAC_CARRIER
				2003/10/29	Y.Saito		<BRZ-437>		add error code.
														:E_BV_NONRESPONSE
	008-ZY02	2003/11/11	M.Kamimura	<BRZ-456>		add error code.
														:E_SET_RJT
										<BRZ-458>		add error code.
														:E_NOT_DECIDE_DEST
														:E_FULL_ESC
														:E_FULL_RSV
														:E_FULL_CA1
														:E_FULL_CA2
														:E_FULL_CA3
														:E_FULL_CA4
										<BRZ-460>		add error code.
														:E_SET_UPPER_UNIT
														:E_SET_LOWER_UNIT
														:E_SET_LOWER_TRANSPORT
				2003/11/17	M.Banba		<BRZ-474>		add error code.
														:E_UNJUST_PARAMETER_I2
							Y.Saito		<BRZ-475>		add error code.
														:E_BV_COMPARE_VD
				2003/11/18	M.Banba		<BRZ-474>		delete error code.
														:E_UNJUST_PARAMETER_I2
				2003/11/25	M.Kamimura	<BRZ-497>		add error code.
														:E_REMAIN_PTCS
														:E_REMAIN_PS1S
														:E_REMAIN_PS2S
														:E_REMAIN_PS3S
														:E_REMAIN_PS4S
				2003/11/27	M.Kamimura	<BRZ-506>		add error code.
														:E_SET_CA1
														:E_SET_CA2
														:E_SET_CA3
														:E_SET_CA4
							A.Kojima	<BRZ-507>		add error code.
														:E_OVER_MAX_LEVEL_LFHS,
														 E_OFF_LFHS
	009-ZY03	2003/12/01	M.Banba		<BRZ-512>		add error code.
														:E_STAY_xxxx(xxxx:sensor name)
														:E_REMAIN_PDSS
														change error code number.
														:E_REMAIN_PTCS
														:E_REMAIN_PS1S
														:E_REMAIN_PS2S
														:E_REMAIN_PS3S
														:E_REMAIN_PS4S
				2003/12/02	M.Kamimura	<BRZ-514>		add error code.
														:E_TYPE_TARGET_CA
														:E_DENOMI_TARGET_CA
														:E_NOTHING_TEMP_CA
														:E_REMAIN_TEMP_CA
				2003/12/08	M.Kamimura	<BRZ-529>		add error code.
														:E_NOTHING_MEDIA_PATH
							M.Kibe		<BRZ-532>		add error code.
														:E_SNS_SHOC_SHCC_SHT
	010-ZY04	2003/12/15	M.Kamimura	<BRZ-557>		delete error code.
														:E_NOTHING_MEDIA_PATH
														change error code.
														:E_STAY_xxx
				2003/12/16	M.Kibe		<BRZ-555>		add error code.
														:E_NON_CONNECT_PAC
														:E_TYPE_DIFFERENT_PAC
				2003/12/19	M.Kamimura	<BRZ-575>		add error code.
														:E_REMAIN_KNOT_LOWER
										<BRZ-577>		add error code.
														:E_REMAIN_LFHS
														:E_ILLEGAL_LFHS
														:E_STAY_LFHS
				2003/12/26	M.Kibe		<BRZ-555>		change error code.
														:E_NON_CONNECT_PAC->E_CONNECT_PAC
	011-ZY05	2004/01/06	M.Banba		<BRZ-607>		add error code.
														:E_ILLEGAL_UULC
														:E_ILLEGAL_ULPC
														:E_ILLEGAL_URLC
														:E_ILLEGAL_BLLC
							M.Kamimura	<BRZ-609>		add error code.
														:E_REMAIN_PRESENT_BILL
							M.Banba		<BRZ-610>		add error code.
														:E_BV_OUTSIDE_OVER
							M.Banba		<BRZ-613>		add error code.
														:E_DISAPPEARANCE_RSV
														:E_DISAPPEARANCE_ESC
				2004/01/08	A.Kojima	<BRZ-569>		add error code.
														:E_OVER_CURRENT_XXXXXX
	012-ZY06	2004/01/20	Y.Saito		<BRZ-669>		add error code.
														:E_SET_ENCRYPTION_KEY
				2004/01/22	M.Kamimura	<BRZ-671>		add error code.
														:E_UNJUST_PARAMETER_A0
							M.Kibe		<BRZ-677>		add error code.
														:E_NOT_OPEN_SHT
														:E_NOT_CLOSE_SHT
				2004/01/24	A.Kojima	<BRZ-681>		add error code.
														:E_JAM_APPEAR_BVIN,E_JAM_ARRIVE_BVIN
				2004/01/28	M.Kibe		<BRZ-677>		add error code.
														:E_TYPE_DIFFERENT_UNIT
				2004/01/29	A.Kojima	<BRZ-699>		delete & add error code
														:E_OVER_CURRENT_UFL5VSE,E_OVER_CURRENT_UFL5VES,
														 E_OVER_CURRENT_UFL0RSV5,E_OVER_CURRENT_UFL0RSV6
														 delete
														:E_OVER_CURRENT_UFL5VSE2,E_OVER_CURRENT_UFL5VES2,
														 E_OVER_CURRENT_UFL5VSE4,E_OVER_CURRENT_UFL5VES4
														 add
	013-ZW01	2003/01/31	A.Maruyama	<BRZ-702>		delete code for A-model
				2003/02/06	Y.Saito		<BRZ-709>		add error code.
														:E_BV_RESPONSE_DISCORD_COMMAND
				2003/02/09	M.Kibe		<BRZ-725>		add error code.
														:E_THRUST_STOPPER_ESC
														:E_ESCAPE_STOPPER_ESC
	014-ZW03	2004/02/19	M.Kamimura	<BRZ-755>		add error code.
														:E_RAS_PASSWORD_xxx
				2004/02/20	M.Kibe		<BRZ-758>		add error code.
														:E_ESCAPE_HOOK_PAC
				2004/02/21	M.Kibe		<BRZ-758>		add error code.
														:E_THRUST_HOOK_PAC
				2004/02/27	M.Kamimura	<BRZ-772>		add error code.
														:E_BV_UNIT_NG
														change error code.( 25xx -> 2Bxx )
														:E_BV_UNJUST_VD
										<BRZ-773>		add error code.
														:E_BV_LACK_PROGRAM
														:E_BV_COVER_OPEN
														:E_BV_MEDIA_REMAIN
				2004/02/27	Y.Saito		<BRZ-774>		add error code.
														:E_BV_RESPONSE_DISCORD_BLOCK
	015-ZW04	2004/03/10	M.Kamimura	<BRZ-811>		add error code.
														:E_STAY_BVIN
														:E_STAY_BVOUT
														:E_ILLEGAL_BVIN
														:E_ILLEGAL_BVOUT
				2004/03/16	M.Kamimura	<BRZ-837>		add error code.
														:E_HOME_POSITION_SEDM
				2004/03/22	A.Maruyama	<BRZ-861>		add error code
														:E_USB_CONNECTOR_OFF
				2004/03/24	A.Maruyama	<BRZ-861>		add error code
														:E_USB_BUS_RESET
	016-ZW06	2004/04/06	M.Kamimura	<BRZ-899>		add error code.
														:E_ILLEGAL_SHCC
	017-ZV01	2004/04/09	M.Kamimura	<BRZ-910>		add error code.
														:E_SET_BEFORE_BV
														:E_SET_UNDER_REJECT
														:E_ILLEGAL_SBLC
														:E_ILLEGAL_UGLC
										<BRZ-911>		add error code.
														:E_OVER_MAX_LEVEL_ETRS
														:E_OFF_ETRS
										<BRZ-912>		add error code.
														:E_SET_TOP_TRANSPORT
														:E_ILLEGAL_ETLC
	018-ZV03	2004/04/14	M.Kamimura	<BRZ-920>		add error code.
														:E_SET_INTERLOCK
														:E_ILLEGAL_INTERLOCK
	019-ZV05	2004/04/27	M.Kibe		<BRZ-960>		add error code.
														:E_RETRY_BACKFEED_SEP
							M.Kamimura	<BRZ-966>		add error code.
														:E_TIMEOUT_CMD_LIMIT_WATCH
														:E_TIMEOUT_CMD_LIMIT_STOP
										<BRZ-968>		add error code.
														:E_DISPENSABLE_OVER
							A.Maruyama	<BRZ-970>		add error code.
														:E_ROTATION_TDCM_FLT
				2004/04/28	Y.Saito		<BRZ-997>		Change error level, error place and read log request.
							A.Maruyama	<BRZ-971>		add error code
														:E_MEMORY_BREAK
				2004/04/30	A.Kojima	<BRZ-979>		add error code.
														:E_JAM_APPEAR_SDIS,E_JAM_ARRIVE_SDIS,
														 E_GET_TRANSPORT_DATA_xxxx
							M.Kamimura	<BRZ-984>		delete error code
														:E_REMAIN_KNOT_LOWER
														add error code.
														:E_REMAIN_KNOT_URHS
														:E_REMAIN_KNOT_LFHS
							A.Maruyama	<BRZ-985>		add error code
														:E_ILLEGAL_PSxS (x=1-4)
	020-ZV07	2004/05/04	M.Kamimura	<BRZ-994>		add error code
														:E_REMAIN_BUNCH_TRANSPORT
	021-ZV08	2004/05/11	M.Kamimura	<BRZ-1005>		add error code
														:E_HALF_NOTE_DETECTION
				2004/05/12	A.Maruyama	<BRZ-1011>		add error code
														:E_ILLEGAL_PTCS
														:E_ILLEGAL_PASS
														:E_ILLEGAL_PDSS
														:E_ILLEGAL_EERS
														:E_ILLEGAL_EELS
														:E_ILLEGAL_EECS
														:E_ILLEGAL_PTPC
														:E_ILLEGAL_PBPC
	022-ZU03	2004/05/21	M.Kamimura	<BRZ-1029>		add error code
														:E_EMPTY_SEP
				2004/05/26	M.Kibe		<BRZ-1052>		add error code
														:E_REMAIN_LONG_BILL_PAC
							A.Maruyama	<BRZ-1053>		add error code
														:E_USB_TIMEOUT_TRANSMIT
							M.Kibe		<BRZ-1078>		add error code
														:E_REMAIN_BELT_SLIP_PAC
	023-ZT02	2004/06/14	M.Kibe		<BRZ-1114>		add error code
														:E_NOT_MOVE_SEP
										<BRZ-1116>		add error code
														:E_DISAPPEARANCE_PDSS
														:E_DISAPPEARANCE_PTCS
				2004/06/15	M.Kibe		<BRZ-1124>		add error code
														:E_SNS_ECHC_ECCC_ECPC_PCEC_CARRIER_PAC
														:E_SNS_ECHC_ECCC_ECPC_CARRIER_PAC
														:E_SNS_ECHC_ECCC_PCEC_CARRIER_PAC
														:E_SNS_ECHC_ECCC_CARRIER_PAC
														:E_SNS_ECHC_ECPC_PCEC_CARRIER_PAC
														:E_SNS_ECHC_ECPC_CARRIER_PAC
														:E_SNS_ECCC_ECPC_PCEC_CARRIER_PAC
														:E_SNS_ECCC_ECPC_CARRIER_PAC
														:E_SNS_ECCC_PCEC_CARRIER_PAC
														:E_SNS_ECPC_PCEC_CARRIER_PAC
														:E_SNS_PDPC_PLPC_PRPC_TRAY_PAC
														:E_SNS_PDPC_PLPC_TRAY_PAC
														:E_SNS_PDPC_PRPC_TRAY_PAC
														:E_SNS_PLPC_PRPC_TRAY_PAC
														:E_SNS_SPUC_SPBC_PUSHER_SEP
														:E_SNS_SPUC_SPCC_PUSHER_SEP
														:E_SNS_SSUC_SSLC_STAGE_SEP
														:E_SNS_SFOC_SFIC_COMB_SEP
														:E_SNS_ERUC_ERRC_ERLC_RSV
														:E_SNS_ERUC_ERRC_RSV
														:E_SNS_ERUC_ERLC_RSV
														:E_SNS_ERRC_ERLC_RSV
														:E_SNS_EERC_EEUC_EELC_ESC
														:E_SNS_EERC_EEUC_ESC
														:E_SNS_EERC_EELC_ESC
														:E_SNS_EEUC_EELC_ESC
														:E_SNS_CF1C_CE1C_NE1C_NF1C_CA1
														:E_SNS_CF1C_CE1C_NE1C_CA1
														:E_SNS_CF1C_CE1C_NF1C_CA1
														:E_SNS_CF1C_CE1C_CA1
														:E_SNS_CF1C_NE1C_NF1C_CA1
														:E_SNS_CF1C_NE1C_CA1
														:E_SNS_CF2C_CE2C_NE2C_NF2C_CA2
														:E_SNS_CF2C_CE2C_NE2C_CA2
														:E_SNS_CF2C_CE2C_NF2C_CA2
														:E_SNS_CF2C_CE2C_CA2
														:E_SNS_CF2C_NE2C_NF2C_CA2
														:E_SNS_CF2C_NE2C_CA2
														:E_SNS_CF3C_CE3C_NE3C_NF3C_CA3
														:E_SNS_CF3C_CE3C_NE3C_CA3
														:E_SNS_CF3C_CE3C_NF3C_CA3
														:E_SNS_CF3C_CE3C_CA3
														:E_SNS_CF3C_NE3C_NF3C_CA3
														:E_SNS_CF3C_NE3C_CA3
														:E_SNS_CF4C_CE4C_NE4C_NF4C_CA4
														:E_SNS_CF4C_CE4C_NE4C_CA4
														:E_SNS_CF4C_CE4C_NF4C_CA4
														:E_SNS_CF4C_CE4C_CA4
														:E_SNS_CF4C_NE4C_NF4C_CA4
														:E_SNS_CF4C_NE4C_CA4
				2004/06/16	M.Kibe		<BRZ-1124>		add error code
														:E_SNS_CE1C_NF1C_CA1
														:E_SNS_NE1C_NF1C_CA1
														:E_SNS_NE1C_CF1C_CA1
														:E_SNS_CE2C_NF2C_CA2
														:E_SNS_NE2C_NF2C_CA2
														:E_SNS_NE2C_CF2C_CA2
														:E_SNS_CE3C_NF3C_CA3
														:E_SNS_NE3C_NF3C_CA3
														:E_SNS_NE3C_CF3C_CA3
														:E_SNS_CE4C_NF4C_CA4
														:E_SNS_NE4C_NF4C_CA4
														:E_SNS_NE4C_CF4C_CA4
														delete error code
														:E_SNS_CF1C_CE1C_NE1C_NF1C_CA1
														:E_SNS_CF1C_CE1C_NE1C_CA1
														:E_SNS_CF1C_CE1C_NF1C_CA1
														:E_SNS_CF1C_CE1C_CA1
														:E_SNS_CF1C_NE1C_NF1C_CA1
														:E_SNS_CF1C_NE1C_CA1
														:E_SNS_CF2C_CE2C_NE2C_NF2C_CA2
														:E_SNS_CF2C_CE2C_NE2C_CA2
														:E_SNS_CF2C_CE2C_NF2C_CA2
														:E_SNS_CF2C_CE2C_CA2
														:E_SNS_CF2C_NE2C_NF2C_CA2
														:E_SNS_CF2C_NE2C_CA2
														:E_SNS_CF3C_CE3C_NE3C_NF3C_CA3
														:E_SNS_CF3C_CE3C_NE3C_CA3
														:E_SNS_CF3C_CE3C_NF3C_CA3
														:E_SNS_CF3C_CE3C_CA3
														:E_SNS_CF3C_NE3C_NF3C_CA3
														:E_SNS_CF3C_NE3C_CA3
														:E_SNS_CF4C_CE4C_NE4C_NF4C_CA4
														:E_SNS_CF4C_CE4C_NE4C_CA4
														:E_SNS_CF4C_CE4C_NF4C_CA4
														:E_SNS_CF4C_CE4C_CA4
														:E_SNS_CF4C_NE4C_NF4C_CA4
														:E_SNS_CF4C_NE4C_CA4
				2004/06/16	A.Maruyama	<BRZ-1127>		add error code
														:E_BV_INVALID_PARITY_VD
	024-ZT05	2004/06/28	M.Kamimura	<BRZ-1132>		add error code
														:E_NOT_RECOGNIZED_OVER_xxx
														:E_DAMAGED_OVER_xxx
														:E_DIFFERENT_OVER_xxx
														:E_COUNTERFEIT_OVER_xxx
														:E_OUTSIDE_OVER_xxx
														:E_INSUFFICIENT_PAYMENT_xxx
	025-ZT10	2004/07/13	Y.Saito		<BRZ-1152>		add error code
														:E_BV_OVER_VD
				2004/07/15	A.Maruyama	<BRZ-1162>		segmentalize media remain error by jam-counter
														:E_REMAIN_JAM_BASE
														:E_REMAIN_xxxxx
														 (xxxxx = label of jam-counter[e.g. JAM_SSxS_SDIS])
	026-AA04	2004/08/09	A.Maruyama	<BRZ-1196>		add error code for PCB communication error
														:E_COMMUNICATION_PCB
				2004/08/10	M.Kibe		<BRZ-1199>		add error code for D-stopper retry over
														:E_RETRY_THRUST_DSTOPPER_PAC
	027-AA05	2004/09/06	Y.Saito		<BRZ-1223>		add error code for RAS start error
														:E_INSUFFICIENT_PREP_RAS
				2004/09/10	M.Kibe		<BRZ-1239>		add error code for It cannot draw and remains(PAC)
														:E_NOT_DRAW_BILL_PAC
	028-AA08	2004/09/28	M.Kibe		<BRZ-1274>		add error code
														:E_REMAIN_BELT_JAM_PAC
	029-AA09	2004/09/30	M.Kamimura	<BRZ-1277>		add error code
														:E_TYPE_TEMP_CA
				2004/10/04	M.Kibe		<BRZ-1279>		add error code
														:E_NOT_PRE_DRAW_BILL_PAC
	030-AA10	2004/10/07	M.Kibe		<BRZ-1294>		add error code
														:E_REMAIN_PAC_CARRIER_BUNCH
	031-AA17	2005/02/14	A.Kojima	<BRZ-1388>		add error code
														:E_RIGHT_POSITION_SEDM,
														 E_LEFT_POSITION_SEDM,
														 E_STEP_OUT_SEDM,
														 E_SNS_SCDC_SHDC_DESKEW_SEP
	032-AA18	2005/03/03	M.Kibe		<BRZ-1392>		add error code
														:E_RETRY_ESCAPE_DSTOPPER_PAC
														:E_MOVE_THRUST_DSTOPPER_PAC
	033-AA27	2006/01/19	M.Kamimura	<BRZ-1464>		add error code
														:E_JAM_ARRIVE_UERS_FULL,
														 E_JAM_PASS_UERS_FULL
	034-AA30	2006/04/18	A.Kojima	<BRZ-1480>		add error code
														:E_JAM_ARRIVE_UEFS_FULL,
														 E_JAM_ARRIVE_UECS_FULL,
														 E_JAM_PASS_UEFS_FULL,
														 E_JAM_PASS_UECS_FULL
	035-AA33	2006/07/03	M.Kamimura	<BRZ-1486>		add error code
														:E_SIGNATURE_OVER_SEP
	036-AA37	2006/12/11	M.Kamimura	<BRZ-1506>		add error code
														:E_DISAPPEARANCE_PAC
				2006/12/11	M.Kibe		<BRZ-1506>		add error code
														:E_DISAPPEARANCE_PDPC_PDSS
	037-AA41	2007/01/30	A.Kojima	<BRZ-1512>		add error code
														:E_JAM_APPEAR_Cx1S_FULL,E_JAM_APPEAR_Cx2S_FULL,
														 E_JAM_APPEAR_Cx3S_FULL,E_JAM_APPEAR_Cx4S_FULL,
														 E_JAM_ARRIVE_Cx1S_FULL,E_JAM_ARRIVE_Cx2S_FULL,
														 E_JAM_ARRIVE_Cx3S_FULL,E_JAM_ARRIVE_Cx4S_FULL,
														 E_JAM_PASS_Cx1S_FULL,E_JAM_PASS_Cx2S_FULL,
														 E_JAM_PASS_Cx3S_FULL,E_JAM_PASS_Cx4S_FULL,
														 E_GET_TRANSPORT_DATA_Cx1S_FULL,
														 E_GET_TRANSPORT_DATA_Cx2S_FULL,
														 E_GET_TRANSPORT_DATA_Cx3S_FULL,
														 E_GET_TRANSPORT_DATA_Cx4S_FULL,
														 E_STAY_Cx1S_FULL,E_STAY_Cx2S_FULL,
														 E_STAY_Cx3S_FULL,E_STAY_Cx4S_FULL,
														 E_ILLEGAL_Cx1S_FULL,E_ILLEGAL_Cx2S_FULL,
														 E_ILLEGAL_Cx3S_FULL,E_ILLEGAL_Cx4S_FULL
				2007/01/31	M.Kibe		<BRZ-1512>		add error code
														 E_RETRY_DOWN_CA1_FULL,E_RETRY_UP_CA1_FULL
														 E_FULL_JAM_CA1,E_REMAIN_BILL_PINCH_CA1_FULL
														 E_RETRY_DOWN_CA2_FULL,E_RETRY_UP_CA2_FULL
														 E_FULL_JAM_CA2,E_REMAIN_BILL_PINCH_CA2_FULL
														 E_RETRY_DOWN_CA3_FULL,E_RETRY_UP_CA3_FULL
														 E_FULL_JAM_CA3,E_REMAIN_BILL_PINCH_CA3_FULL
														 E_RETRY_DOWN_CA4_FULL,E_RETRY_UP_CA4_FULL
														 E_FULL_JAM_CA4,E_REMAIN_BILL_PINCH_CA4_FULL
	038-AA48	2007/05/24	A.Maruyama	<BRZ-1535>		add error code
														:E_DISAPPEARANCE_SEP
				2007/06/27	M.Kibe		<BRZ-1540>		add error code
														:E_REMAIN_PAC_NON_HOOK
COMMENT END
***/

/****************************************************************************/
/*																			*/
/*	variables																*/
/*																			*/
/****************************************************************************/
extern	const	ERR_TBL		ertErrorTable[];
extern	const	UCHAR		bErrorTableEnd;

/*--------------------------------------------------------------------------*/
/*	Error code																*/
/*	‹K–ñ:																	*/
/*	E_AAAA_BBBB_CCCC														*/
/*	AAAA:TIMEOUT,JAM,‚È‚ÇƒGƒ‰[‚ÌŒ´ˆö‚½‚¾‚µNG‚Æ‚©‚¶‚á‚È‚­‚È‚é‚×‚­‹ï‘Ì“I‚É	*/
/*	BBBB:OPEN,UP,‚È‚Ç“®ìŒn													*/
/*	CCCC:SHUTTER,UGAS‚È‚ÇêŠŒn												*/
/*--------------------------------------------------------------------------*/
typedef	enum	{
	/*----------------------------------------------------------------------*/
	/*	for Clear or Cancel													*/
	/*----------------------------------------------------------------------*/
	E_NONE						= 0x0000,	/*	Nothing							*/
	
	/*----------------------------------------------------------------------*/
	/*	relate with System Error								(0xxx)		*/
	/*----------------------------------------------------------------------*/
		/*------------------------------------------------------------------*/
		/*	firm-ware inoperative								(0Cxx)		*/
		/*	Rev(ZZ04:BRZ-128)	add error code (E_OUTSIDE_EVENT)			*/
		/*	Rev(ZZ07:BRZ-372)	add error code (E_OUTSIDE_REMAIN)			*/
		/*	Rev(ZZ07:BRZ-386)	add error code (E_FLASH_ERASE/E_FLASH_WRITE)*/
		/*	Rev(ZY02:BRZ-458)	add error code (E_NOT_DECIDE_DEST)			*/
		/*	Rev(ZV05:BRZ-966)	add error code (E_TIMEOUT_CMD_LIMIT_xxx)	*/
		/*	Rev(ZV05:BRZ-971)	add error code (E_MEMORY_BREAK)				*/
		/*------------------------------------------------------------------*/
	E_RETURN_TASK_SYS			= 0x0C00,	/*	return from system-management-task	*/
	E_UNJUST_ARGUMENT			= 0x0C01,	/*	unjust agument for the function		*/
	E_OUTSIDE_EVENT				= 0x0C02,	/*	Event generating besides assumption	*/
	E_NOT_DECIDE_DEST			= 0x0C03,	/*	not decide destination				*/
	
	E_ALLOCATE_TCB				= 0x0C10,	/*	not allocate memory for TCB	*/
	E_ALLOCATE_PKT_TASK			= 0x0C11,	/*	not allocate memory for packet of task	*/
	E_ALLOCATE_PKT_TRANSFER		= 0x0C12,	/*	not allocate memory for packet of transfer process	*/
	E_INITIALIZE_TIMER			= 0x0C13,	/*	not initialize for timer-control		*/
	
	E_SET_TIMER					= 0x0C20,	/*	timer-set impossible		*/
	E_SET_PACKET				= 0x0C21,	/*	setpkt impossible			*/

	E_OUTSIDE_REMAIN			= 0x0C30,	/*	Operation is impossible.(by remain)	*/
	
	E_FLASH_ERASE				= 0x0C40,	/*	FLASH-rom erase impossible	*/
	E_FLASH_WRITE				= 0x0C41,	/*	FLASH-rom write impossible	*/

	E_MEMORY_BREAK				= 0x0C50,	/*	Memory break				*/

	E_TIMEOUT_CMD_LIMIT_WATCH	= 0x0C60,	/*	Command limit timeout (1st)	*/
	E_TIMEOUT_CMD_LIMIT_STOP	= 0x0C61,	/*	Command limit timeout (2nd)	*/
	/*----------------------------------------------------------------------*/
	/*	relate with Host Interface Error						(1xxx)		*/
	/*----------------------------------------------------------------------*/
		/*------------------------------------------------------------------*/
		/*	The command non-given a definition					(15xx)		*/
		/*	Rev(ZZ04:BRZ-128)	add error code (E_UNJUST_COMMAND)			*/
		/*------------------------------------------------------------------*/
	E_UNJUST_COMMAND			= 0x1500,	/*	Command an error non-given a definition	*/
		/*------------------------------------------------------------------*/
		/*	The abnormalities in wording of a telegram			(16xx)		*/
		/*	Rev(ZZ04:BRZ-166)	add error code (E_UNJUST_PARAMETER_Ax)		*/
		/*	Rev(ZZ06:BRZ-321)	add error code (1601-1604)					*/
		/*	Rev(ZZ06:BRZ-285)	add error code (1600)						*/
		/*	Rev(ZZ07:BRZ-386)	add error code (E_UNJUST_PARAMETER_H0)		*/
		/*									   (E_DOWNLOAD_SEQUENCE)		*/
		/*	Rev(ZY06:BRZ-671)	add error code (E_UNJUST_PARAMETER_A0)		*/
		/*------------------------------------------------------------------*/
	E_RECEIPT_UNJUST_CLASS			= 0x1600,	/*							*/
	E_RECEIPT_UNJUST_LENGTH			= 0x1601,	/*							*/
	E_RECEIPT_UNJUST_FORMAT			= 0x1602,	/*							*/
	E_RECEIPT_UNJUST_BLOCK_NUMBER	= 0x1603,	/*							*/
	E_RECEIPT_UNJUST_SUM			= 0x1604,	/*							*/
	
	E_UNJUST_PARAMETER_A1		= 0x1620,	/*	Abnormalities in a parameter A1		*/
	E_UNJUST_PARAMETER_A2		= 0x1621,	/*	Abnormalities in a parameter A2		*/
	E_UNJUST_PARAMETER_A5		= 0x1622,	/*	Abnormalities in a parameter A5		*/
	E_UNJUST_PARAMETER_A6		= 0x1623,	/*	Abnormalities in a parameter A6		*/
	E_UNJUST_PARAMETER_A7		= 0x1624,	/*	Abnormalities in a parameter A7		*/
	E_UNJUST_PARAMETER_A8		= 0x1625,	/*	Abnormalities in a parameter A8		*/
	E_UNJUST_PARAMETER_A9		= 0x1626,	/*	Abnormalities in a parameter A9		*/
	E_UNJUST_PARAMETER_AZ		= 0x1627,	/*	Abnormalities in a parameter AZ		*/
	E_UNJUST_PARAMETER_H0		= 0x1628,	/*	Abnormalities in a parameter H0		*/
	E_UNJUST_PARAMETER_A0		= 0x1629,	/*	Abnormalities in a parameter A0		*/
	
	E_DOWNLOAD_SEQUENCE			= 0x1640,	/*	abnormalities in download sequence	*/
		/*------------------------------------------------------------------*/
		/*	With no fixed parameter								(17xx)		*/
		/*	Rev.(ZZ06:BRZ-285)	add error code (E_UNSETTLED_PARAMETER_A1)	*/
		/*------------------------------------------------------------------*/
	E_NOTHING_PARAMETER_A1		= 0x1700,	/*	parameter A1 un-setting up.			*/
		/*------------------------------------------------------------------*/
		/*	RAS error											(1Cxx)		*/
		/*	Rev.(ZW03:BRZ-755)	add error code (E_RAS_PASSWORD_xxx)			*/
		/*------------------------------------------------------------------*/
	E_RAS_PASSWORD_PAYMENT		= 0x1C00,	/*	Payment password un-setting up.		*/
	E_RAS_PASSWORD_CALCULATION	= 0x1C01,	/*	Calculation password un-setting up.	*/
		/*------------------------------------------------------------------*/
		/*	involved with USB									(1Exx)		*/
		/*	Rev.(ZW04:BRZ-861)	add error code	(E_USB_CONNECTOR_OFF)		*/
		/*										(E_USB_BUS_RESET)			*/
		/*	Rev.(ZU03:BRZ-1053)	add error code	(E_USB_TIMEOUT_TRANSMIT)	*/
		/*------------------------------------------------------------------*/
	E_USB_CONNECTOR_OFF			= 0x1E00,	/*	USB connector off			*/
	E_USB_BUS_RESET				= 0x1E01,	/*	USB BUS reset				*/
	E_USB_TIMEOUT_TRANSMIT		= 0x1E02,	/*	USB transmitting timeout	*/
	/*----------------------------------------------------------------------*/
	/*	relate with BV Error									(2xxx)		*/
	/*----------------------------------------------------------------------*/
		/*------------------------------------------------------------------*/
		/*														(20xx)		*/
		/*	Rev(ZZ06:BRZ-245)	add error code 								*/
		/*	Rev(ZW01:BRZ-709)	add error code 								*/
		/*	Rev.(ZW03:BRZ-774)	add error code (E_BV_RESPONSE_DISCORD_BLOCK)*/
		/*	Rev.(ZW03:BRZ-773)	add error code (E_BV_LACK_PROGRAM)			*/
		/*------------------------------------------------------------------*/
	E_BV_BUSY					= 0x2001,
	E_BV_RESPONSE_TIMEOUT		= 0x2004,
	E_BV_RESPONSE_DISCORD_SUM	= 0x2005,
	E_BV_RESPONSE_DISCORD_LENGTH= 0x2006,
	E_BV_FAILURE_RESET			= 0x2007,
	E_BV_RESPONSE_DISCORD_COMMAND= 0x2008,
	E_BV_RESPONSE_DISCORD_BLOCK	= 0x2009,
	E_BV_LACK_PROGRAM			= 0x2020,
		/*------------------------------------------------------------------*/
		/*														(21xx)		*/
		/*	Rev(ZY01:BRZ-437)	add error code 								*/
		/*------------------------------------------------------------------*/
	E_BV_NONRESPONSE			= 0x2100,
		/*------------------------------------------------------------------*/
		/*														(23xx)		*/
		/*	Rev(ZT10:BRZ-1152)	add error code 								*/
		/*------------------------------------------------------------------*/
	E_BV_OVER_VD				= 0x2300,
		/*------------------------------------------------------------------*/
		/*														(25xx)		*/
		/*	Rev.(ZW03:BRZ-772)	add error code (E_BV_UNIT_NG)				*/
		/*------------------------------------------------------------------*/
	E_BV_UNIT_NG				= 0x2500,
		/*------------------------------------------------------------------*/
		/*														(26xx)		*/
		/*	Rev(ZY02:BRZ-475)	add error code (E_BV_COMPARE_VD)			*/
		/*------------------------------------------------------------------*/
	E_BV_COMPARE_VD				= 0x2600,
		/*------------------------------------------------------------------*/
		/*														(27xx)		*/
		/*	Rev(ZZ06:BRZ-191)	add error code 								*/
		/*------------------------------------------------------------------*/
	E_BV_ERROR_RECEPTION		= 0x2700,
		/*------------------------------------------------------------------*/
		/*														(27xx)		*/
		/*	Rev(ZZ06:BRZ-191)	add error code 								*/
		/*------------------------------------------------------------------*/
	E_BV_INVALID_RECEPTION		= 0x2800,
		/*------------------------------------------------------------------*/
		/*														(29xx)		*/
		/*	Rev(ZZ06:BRZ-191)	add error code 								*/
		/*------------------------------------------------------------------*/
	E_START_VALIDATE_BV			= 0x2900,
		/*------------------------------------------------------------------*/
		/*														(2Bxx)		*/
		/*	Rev.(ZZ07:BRZ-362)	add error code (E_BV_UNJUST_VD)				*/
		/*	Rev.(ZW03:BRZ-772)	change error code ( 25xx -> 2Bxx )			*/
		/*	Rev.(ZW03:BRZ-773)	add error code								*/
		/*	Rev.(ZT02:BRZ-1127)	add error code (E_BV_INVALID_PARITY_VD)		*/
		/*------------------------------------------------------------------*/
	E_BV_UNJUST_VD				= 0x2B00,
	E_BV_INVALID_PARITY_VD		= 0x2B01,
	E_BV_COVER_OPEN				= 0x2B10,
	E_BV_MEDIA_REMAIN			= 0x2B20,
		/*------------------------------------------------------------------*/
		/*														(2Fxx)		*/
		/*	Rev(ZZ06:BRZ-289)	add error code 								*/
		/*	Rev(ZZ06:BRZ-285)				 								*/
		/*	Different denominations number-of-sheets over is added. 		*/
		/*	Rev(ZY05:BRZ-610)				 								*/
		/*	Outside bill number-of-sheets exaggerated correspondence for payment*/
		/*------------------------------------------------------------------*/
	E_BV_NOT_RECOGNIZED_OVER	= 0x2F00,
	E_BV_DAMAGED_OVER			= 0x2F01,
	E_BV_DIFFERENT_OVER			= 0x2F02,
	E_BV_COUNTERFEIT_OVER		= 0x2F03,
	E_BV_OUTSIDE_OVER			= 0x2F04,
	/*----------------------------------------------------------------------*/
	/*	relate with Command Error								(3xxx)		*/
	/*----------------------------------------------------------------------*/
		/*------------------------------------------------------------------*/
		/*														(30xx)		*/
		/*	Rev.(AA05:BRZ-1223)	add error code	 							*/
		/*------------------------------------------------------------------*/
	E_RANGE_VALUE_RAS			= 0x3000,
	E_INSUFFICIENT_PREP_RAS		= 0x3001,
		/*------------------------------------------------------------------*/
		/*														(31xx)		*/
		/*	Rev.(ZV05:BRZ-968)	add error code	(E_DISPENSABLE_OVER) 		*/
		/*------------------------------------------------------------------*/
	E_NOT_PAYMENT_CASSETTE		= 0x3100,
	E_INSUFFICIENT_PAYMENT		= 0x3101,
	E_DISPENSABLE_OVER			= 0x3102,
		/*------------------------------------------------------------------*/
		/*	Type / Denomination									(32xx)		*/
		/*	Rev.(ZY03:BRZ-514)	add error code	 							*/
		/*	Rev.(AA09:BRZ-1277)	add error code	(E_TYPE_TEMP_CA) 			*/
		/*------------------------------------------------------------------*/
	E_TYPE_TARGET_CA			= 0x3200,
	E_TYPE_TEMP_CA				= 0x3201,
	E_DENOMI_TARGET_CA			= 0x3210,
		/*------------------------------------------------------------------*/
		/*	Nothing purpose										(33xx)		*/
		/*	Rev.(ZY03:BRZ-514)	add error code	 							*/
		/*	Rev.(ZY03:BRZ-529)	add error code	 (E_NOTHING_MEDIA_PATH)		*/
		/*	Rev.(ZY04:BRZ-557)	Delete error code(E_NOTHING_MEDIA_PATH)		*/
		/*	Rev.(ZU03:BRZ-1029)	add error code	 (E_EMPTY_SEP)				*/
		/*------------------------------------------------------------------*/
	E_NOTHING_TEMP_CA			= 0x3300,
	E_EMPTY_SEP					= 0x3310,
		/*------------------------------------------------------------------*/
		/*	Media remain										(34xx)		*/
		/*	Rev.(ZY03:BRZ-514)	add error code	 							*/
		/*	Rev.(ZY04:BRZ-575)	add error code	 							*/
		/*	Rev.(ZY05:BRZ-609)	add error code	(E_REMAIN_PRESENT_BILL) 	*/
		/*	Rev.(ZV05:BRZ-984)	delete error code	(E_REMAIN_KNOT_LOWER) 	*/
		/*						add error code	(E_REMAIN_KNOT_URHS/LFHS)	*/
		/*------------------------------------------------------------------*/
	E_REMAIN_TEMP_CA			= 0x3400,
	E_REMAIN_PRESENT_BILL		= 0x3411,
	E_REMAIN_KNOT_URHS			= 0x3412,
	E_REMAIN_KNOT_LFHS			= 0x3413,
		/*------------------------------------------------------------------*/
		/*														(35xx)		*/
		/*	Rev.(ZW04:BRZ-837)	add error code	(E_HOME_POSITION_SEDM)		*/
		/*	Rev.(AA17:BRZ-1388)	add error code								*/
		/*	 (E_RIGHT_POSITION_SEDM,E_LEFT_POSITION_SEDM,E_STEP_OUT_SEDM	*/
		/*	  E_SNS_SCDC_SHDC_DESKEW_SEP)									*/
		/*------------------------------------------------------------------*/
	E_HOME_POSITION_SEDM		= 0x3500,
	E_RIGHT_POSITION_SEDM		= 0x3501,
	E_LEFT_POSITION_SEDM		= 0x3502,
	E_STEP_OUT_SEDM				= 0x3503,
	E_SNS_SCDC_SHDC_DESKEW_SEP	= 0x3510,
		/*------------------------------------------------------------------*/
		/*														(3Cxx)		*/
		/*	Rev.(ZZ06:BRZ-311)	add error code 								*/
		/*	Rev.(ZV08:BRZ-1005)	add error code	(E_HALF_NOTE_DETECTION) 	*/
		/*------------------------------------------------------------------*/
	E_NOT_SUIT_NUMBER_BILL		= 0x3C00,
	E_HALF_NOTE_DETECTION		= 0x3C01,
	/*----------------------------------------------------------------------*/
	/*	relate with Unit Set & Full								(4xxx)		*/
	/*----------------------------------------------------------------------*/
		/*------------------------------------------------------------------*/
		/*	Set													(40xx)		*/
		/*	Rev.(ZY02:BRZ-456)	add error code 	(E_SET_RJT)					*/
		/*	Rev.(ZY02:BRZ-460)	add error code 	(E_SET_UPPER/LOWER)			*/
		/*	Rev.(ZY02:BRZ-506)	add error code 	(E_SET_CA1->CA4)			*/
		/*	Rev.(ZV01:BRZ-910)	add error code 	(BEFORE_BV,UNDER_REJECT)	*/
		/*	Rev.(ZV01:BRZ-912)	add error code 	(E_SET_TOP_TRANSPORT)		*/
		/*	Rev.(ZV02:BRZ-920)	add error code 	(E_SET_INTERLOCK)			*/
		/*------------------------------------------------------------------*/
	E_SET_UPPER_UNIT			= 0x4001,
	E_SET_LOWER_UNIT			= 0x4002,
	E_SET_LOWER_TRANSPORT		= 0x4003,
	E_SET_RJT					= 0x4004,
	E_SET_CA1					= 0x4005,
	E_SET_CA2					= 0x4006,
	E_SET_CA3					= 0x4007,
	E_SET_CA4					= 0x4008,
	E_SET_BEFORE_BV				= 0x4009,
	E_SET_UNDER_REJECT			= 0x400A,
	E_SET_TOP_TRANSPORT			= 0x400B,
	E_SET_INTERLOCK				= 0x400F,
		/*------------------------------------------------------------------*/
		/*	Full												(43xx)		*/
		/*	Rev.(ZY02:BRZ-458)	add error code 	(E_FULL_ESC -> E_FULL_CA4)	*/
		/*------------------------------------------------------------------*/
	E_FULL_FIT					= 0x4300,
	E_FULL_RJT					= 0x4301,
	E_FULL_CPT					= 0x4302,
	E_FULL_ESC					= 0x4303,
	E_FULL_RSV					= 0x4304,
	E_FULL_CA1					= 0x4305,
	E_FULL_CA2					= 0x4306,
	E_FULL_CA3					= 0x4307,
	E_FULL_CA4					= 0x4308,
		/*------------------------------------------------------------------*/
		/*	The abnormalities in a type							(45xx)		*/
		/*	Rev.(ZY06:BRZ-677)	add error code 								*/
		/*------------------------------------------------------------------*/
	E_TYPE_DIFFERENT_UNIT		= 0x4501,
	/*----------------------------------------------------------------------*/
	/*	(reserve)		 										(5xxx)		*/
	/*----------------------------------------------------------------------*/
	
	/*----------------------------------------------------------------------*/
	/*	relate with place of Pre-acceptor,Separator,Shutter		(6xxx)		*/
	/*	Rev.(ZZ03:BRZ-044)		change error code no						*/
	/*----------------------------------------------------------------------*/
		/*------------------------------------------------------------------*/
		/*	poor mechanism operation							(61xx)		*/
		/*------------------------------------------------------------------*/
			/*--------------------------------------------------------------*/
			/*	PAC carrier										(610x)		*/
			/*	Rev.(ZZ03:BRZ-058)											*/
			/*	 change lavel												*/
			/*	  E_RETRY_FORWARD_PAC_CARRIER/E_RETRY_BACKWARD_PAC_CARRIER	*/
			/*	Rev(ZZ06:BRZ-337)	Deletion error code 					*/
			/*	  E_UNCERTAINTY_PAC_CARRIER									*/
			/*	Rev(ZY01:BRZ-397)	add error code 							*/
			/*	  E_REMAIN_PAC_CARRIER										*/
			/*	Rev(AA10:BRZ-1294)	add error code 							*/
			/*	  E_REMAIN_PAC_CARRIER_BUNCH								*/
			/*--------------------------------------------------------------*/
	E_RETRY_FORWARD_PAC_CARRIER		= 0x6100,
	E_RETRY_BACKWARD_PAC_CARRIER	= 0x6101,
	E_REMAIN_PAC_CARRIER			= 0x6102,
	E_REMAIN_PAC_CARRIER_BUNCH		= 0x6103,
			/*--------------------------------------------------------------*/
			/*	PAC tray										(612x)		*/
			/*	Rev.(ZZ03:BRZ-058)											*/
			/*	 add error code												*/
			/*	  E_RETRY_FORWARD_PAC_TRAY/E_RETRY_BACKWARD_PAC_TRAY		*/
			/*--------------------------------------------------------------*/
	E_RETRY_FORWARD_PAC_TRAY	= 0x6120,
	E_RETRY_BACKWARD_PAC_TRAY	= 0x6121,
	E_UNCERTAINTY_PAC_TRAY		= 0x612F,
			/*--------------------------------------------------------------*/
			/*	PAC belt										(613x)		*/
			/*	Rev.(ZZ03:BRZ-079)											*/
			/*	 add error code												*/
			/*	  E_RETRY_FORWARD_PAC_BELT									*/
			/*	Rev.(ZZ03:BRZ-115)	add error code							*/
			/*	  E_RETRY_BACKWARD_PAC_BELT									*/
			/*--------------------------------------------------------------*/
	E_RETRY_FORWARD_PAC_BELT	= 0x6130,
	E_RETRY_BACKWARD_PAC_BELT	= 0x6131,
			/*--------------------------------------------------------------*/
			/*	PAC clamp										(614x)		*/
			/*	Rev.(ZZ03:BRZ-115)	add error code							*/
			/*	  E_RETRY_DOWN_PAC_CLAMP/E_RETRY_UP_PAC_CLAMP				*/
			/*--------------------------------------------------------------*/
	E_RETRY_DOWN_PAC_CLAMP		= 0x6140,
	E_RETRY_UP_PAC_CLAMP		= 0x6141,
			/*--------------------------------------------------------------*/
			/*	PAC type										(615x)		*/
			/*	Rev.(ZY04:BRZ-555)	add error code							*/
			/*	  E_NON_CONNECT_PAC/E_TYPE_DIFFERENT_PAC					*/
			/*	Rev.(ZY04:BRZ-555)	change error code						*/
			/*	  E_NON_CONNECT_PAC->E_CONNECT_PAC							*/
			/*--------------------------------------------------------------*/
	E_CONNECT_PAC				= 0x6150,
	E_TYPE_DIFFERENT_PAC		= 0x6151,
			/*--------------------------------------------------------------*/
			/*	SEP pusher										(618x)		*/
			/*--------------------------------------------------------------*/
	E_RETRY_DOWN_PUSHER_SEP		= 0x6180,
	E_RETRY_UP_PUSHER_SEP		= 0x6181,
			/*--------------------------------------------------------------*/
			/*	SEP stage										(619x)		*/
			/*--------------------------------------------------------------*/
	E_RETRY_DOWN_STAGE_SEP		= 0x6190,
	E_RETRY_UP_STAGE_SEP		= 0x6191,
			/*--------------------------------------------------------------*/
			/*	Rev.(ZZ04:BRZ-134)	add error code							*/
			/*	Shutter											(61Ax)		*/
			/*--------------------------------------------------------------*/
	E_RETRY_OPEN_SHT			= 0x61A0,
	E_RETRY_CLOSE_SHT			= 0x61A1,
			/*--------------------------------------------------------------*/
			/*	Rev.(ZY06:BRZ-677)	add error code							*/
			/*	Shutter											(61Bx)		*/
			/*--------------------------------------------------------------*/
	E_NOT_OPEN_SHT				= 0x61B0,
	E_NOT_CLOSE_SHT				= 0x61B1,
		/*------------------------------------------------------------------*/
		/*	the abnormalities in a sensor						(62xx)		*/
		/*------------------------------------------------------------------*/
			/*--------------------------------------------------------------*/
			/*	PAC carrier										(621x)		*/
			/*	Rev.(ZT02:BRZ-1124)											*/
			/*--------------------------------------------------------------*/
	E_SNS_ECHC_ECCC_ECPC_PCEC_CARRIER_PAC	= 0x6210,
	E_SNS_ECHC_ECCC_ECPC_CARRIER_PAC		= 0x6211,
	E_SNS_ECHC_ECCC_PCEC_CARRIER_PAC		= 0x6212,
	E_SNS_ECHC_ECCC_CARRIER_PAC				= 0x6213,
	E_SNS_ECHC_ECPC_PCEC_CARRIER_PAC		= 0x6214,
	E_SNS_ECHC_ECPC_CARRIER_PAC				= 0x6215,
	E_SNS_ECCC_ECPC_PCEC_CARRIER_PAC		= 0x6216,
	E_SNS_ECCC_ECPC_CARRIER_PAC				= 0x6217,
	E_SNS_ECCC_PCEC_CARRIER_PAC				= 0x6218,
	E_SNS_ECPC_PCEC_CARRIER_PAC				= 0x6219,
			/*--------------------------------------------------------------*/
			/*	PAC tray										(622x)		*/
			/*	Rev.(ZT02:BRZ-1124)											*/
			/*--------------------------------------------------------------*/
	E_SNS_PDPC_PLPC_PRPC_TRAY_PAC			= 0x6220,
	E_SNS_PDPC_PLPC_TRAY_PAC				= 0x6221,
	E_SNS_PDPC_PRPC_TRAY_PAC				= 0x6222,
	E_SNS_PLPC_PRPC_TRAY_PAC				= 0x6223,
			/*--------------------------------------------------------------*/
			/*	SEP pusher										(628x)		*/
			/*	Rev.(ZZ07:BRZ-337)											*/
			/*	Deletion error code:E_SNS_SSGC_SEP							*/
			/*	Rev.(ZT02:BRZ-1124)											*/
			/*	add error code												*/
			/*--------------------------------------------------------------*/
	E_SNS_SPUC_SEP				= 0x6280,
	E_SNS_SPUC_SPBC_PUSHER_SEP	= 0x6281,
	E_SNS_SPUC_SPCC_PUSHER_SEP	= 0x6282,
			/*--------------------------------------------------------------*/
			/*	SEP stage										(629x)		*/
			/*	Rev.(ZZ07:BRZ-337)											*/
			/*	Deletion error code:E_SNS_SSLC_SEP							*/
			/*	Rev.(ZT02:BRZ-1124)											*/
			/*	add error code												*/
			/*--------------------------------------------------------------*/
	E_SNS_SSUC_SSLC_STAGE_SEP	= 0x6290,
			/*--------------------------------------------------------------*/
			/*	SEP comb										(62Ax)		*/
			/*	Rev.(ZY01:BRZ-394)											*/
			/*	add error code:E_THRUST_COMB_SEP,E_ESCAPE_COMB_SEP			*/
			/*	Rev.(ZT02:BRZ-1124)											*/
			/*	add error code												*/
			/*--------------------------------------------------------------*/
	E_THRUST_COMB_SEP			= 0x62A0,
	E_ESCAPE_COMB_SEP			= 0x62A1,
	E_SNS_SFOC_SFIC_COMB_SEP	= 0x62A2,
			/*--------------------------------------------------------------*/
			/*	SHT												(62Bx)		*/
			/*	Rev.(ZY03:BRZ-532)											*/
			/*	add error code:E_SNS_SHOC_SHCC								*/
			/*--------------------------------------------------------------*/
	E_SNS_SHOC_SHCC_SHT			= 0x62B0,
		/*------------------------------------------------------------------*/
		/*	the abnormalities in medium thickness				(64xx)		*/
		/*	Rev.(ZZ07:BRZ-345)		add										*/
		/*------------------------------------------------------------------*/
	E_THICK_POLC_PAC			= 0x6400,
		/*------------------------------------------------------------------*/
		/*	Remain Media										(66xx)		*/
		/*	Rev.(ZZ03:BRZ-060)	add error code.(E_REMAIN_SEP)				*/
		/*	Rev.(ZZ07:BRZ-372)	add	error code.(E_REMAIN_PAC)				*/
		/*	Rev.(ZU03:BRZ-1052)	add	error code.(E_REMAIN_LONG_BILL_PAC)		*/
		/*	Rev.(ZU03:BRZ-1078)	add	error code.(E_REMAIN_BELT_SLIP_PAC)		*/
		/*	Rev.(AA08:BRZ-1274)	add	error code.(E_REMAIN_BELT_JAM_PAC)		*/
		/*	Rev.(AA48:BRZ-1540)	add	error code.(E_REMAIN_PAC_NON_HOOK)		*/
		/*------------------------------------------------------------------*/
	E_REMAIN_PAC				= 0x6600,
	E_REMAIN_SEP				= 0x6601,
	E_REMAIN_LONG_BILL_PAC		= 0x6602,
	E_REMAIN_BELT_SLIP_PAC		= 0x6603,
	E_REMAIN_BELT_JAM_PAC		= 0x6604,
	E_REMAIN_PAC_NON_HOOK		= 0x6605,
		/*------------------------------------------------------------------*/
		/*	Hook escape error									(67xx)		*/
		/*	Rev.(ZW03:BRZ-758)												*/
		/*	add error code:E_ESCAPE_HOOK_PAC								*/
		/*	add error code:E_THRUST_HOOK_PAC								*/
		/*	Rev.(AA04:BRZ-1199)												*/
		/*	add error code:E_RETRY_THRUST_DSTOPPER_PAC						*/
		/*	Rev.(AA18:BRZ-1392)												*/
		/*	add error code:E_RETRY_ESCAPE_DSTOPPER_PAC						*/
		/*	add error code:E_MOVE_THRUST_DSTOPPER_PAC						*/
		/*------------------------------------------------------------------*/
	E_ESCAPE_HOOK_PAC			= 0x6700,
	E_THRUST_HOOK_PAC			= 0x6701,
	E_RETRY_THRUST_DSTOPPER_PAC	= 0x6702,
	E_RETRY_ESCAPE_DSTOPPER_PAC	= 0x6703,
	E_MOVE_THRUST_DSTOPPER_PAC	= 0x6704,
		/*------------------------------------------------------------------*/
		/*	Backfeed error										(68xx)		*/
		/*	Rev.(ZV05:BRZ-960)												*/
		/*	add error code:E_RETRY_BACKFEED_SEP								*/
		/*------------------------------------------------------------------*/
	E_RETRY_BACKFEED_SEP		= 0x6800,
		/*------------------------------------------------------------------*/
		/*	move error											(69xx)		*/
		/*	Rev.(ZT02:BRZ-1114)												*/
		/*	add error code:E_NOT_MOVE_SEP									*/
		/*------------------------------------------------------------------*/
	E_NOT_MOVE_SEP				= 0x6900,
		/*------------------------------------------------------------------*/
		/*	Money Trouble													*/
		/*	Rev.(ZT02:BRZ-1116) add this error	(6Cxx)						*/
		/*	add error code:E_NOT_MOVE_SEP									*/
		/*	Rev.(AA37:BRZ-1506) add error code.	(6C11)						*/
		/*	Rev.(AA37:BRZ-1506) add error code.	(6C02)						*/
		/*	Rev.(AA48:BRZ-1535) add error code.	(6C21)						*/
		/*------------------------------------------------------------------*/
	E_DISAPPEARANCE_PDSS		= 0x6C00,
	E_DISAPPEARANCE_PTCS		= 0x6C01,
	E_DISAPPEARANCE_PDPC_PDSS	= 0x6C02,
	E_DISAPPEARANCE_PAC			= 0x6C11,
	E_DISAPPEARANCE_SEP			= 0x6C21,
		/*------------------------------------------------------------------*/
		/*	a delivery is poor									(6Fxx)		*/
		/*------------------------------------------------------------------*/
			/*--------------------------------------------------------------*/
			/*	PAC												(6F7x)		*/
			/*	Rev.(AA05:BRZ-1239)	add error code.	( 6F70 )				*/
			/*	Rev.(AA09:BRZ-1271)	add error code.	( 6F71 )				*/
			/*--------------------------------------------------------------*/
	E_NOT_DRAW_BILL_PAC			= 0x6F70,
	E_NOT_PRE_DRAW_BILL_PAC		= 0x6F71,
			/*--------------------------------------------------------------*/
			/*	SEP												(6F8x)		*/
			/*	Rev.(ZT05:BRZ-1132)	add error code.	( 6F83 -> 6F87 )		*/
			/*	Rev.(AA33:BRZ-1486)	add error code.	( 6F88 )				*/
			/*--------------------------------------------------------------*/
	E_RETRY_DRAW_SEP			= 0x6F80,
	E_FAIL_EMPTY_SEP			= 0x6F81,
	E_RETRY_ROTARY_SEP			= 0x6F82,
	E_NOT_RECOGNIZED_OVER_SEP	= 0x6F83,
	E_DAMAGED_OVER_SEP			= 0x6F84,
	E_DIFFERENT_OVER_SEP		= 0x6F85,
	E_COUNTERFEIT_OVER_SEP		= 0x6F86,
	E_OUTSIDE_OVER_SEP			= 0x6F87,
	E_SIGNATURE_OVER_SEP		= 0x6F88,
	/*----------------------------------------------------------------------*/
	/*	relate with place of Escrow,Reservoir					(7xxx)		*/
	/*	Rev.(ZZ03:BRZ-044)		change error code no						*/
	/*----------------------------------------------------------------------*/
		/*------------------------------------------------------------------*/
		/*	poor mechanism operation							(71xx)		*/
		/*------------------------------------------------------------------*/
			/*--------------------------------------------------------------*/
			/*	RSV												(710x)		*/
			/*--------------------------------------------------------------*/
	E_RETRY_DOWN_RSV			= 0x7100,
	E_RETRY_UP_RSV				= 0x7101,
			/*--------------------------------------------------------------*/
			/*	ESC												(718x)		*/
			/*--------------------------------------------------------------*/
	E_RETRY_DOWN_ESC			= 0x7180,
	E_RETRY_UP_ESC				= 0x7181,
		/*------------------------------------------------------------------*/
		/*	the abnormalities in a sensor						(72xx)		*/
		/*------------------------------------------------------------------*/
			/*--------------------------------------------------------------*/
			/*	RSV												(720x)		*/
			/*	Rev.(ZT02:BRZ-1124)											*/
			/*	add error code												*/
			/*--------------------------------------------------------------*/
	E_SNS_ERUC_RSV				= 0x7200,
	E_SNS_ERRC_RSV				= 0x7201,
	E_SNS_ERUC_ERRC_ERLC_RSV	= 0x7202,
	E_SNS_ERUC_ERRC_RSV			= 0x7203,
	E_SNS_ERUC_ERLC_RSV			= 0x7204,
	E_SNS_ERRC_ERLC_RSV			= 0x7205,
			/*--------------------------------------------------------------*/
			/*	ESC												(728x)		*/
			/*	Rev.(ZT02:BRZ-1124)											*/
			/*	add error code												*/
			/*--------------------------------------------------------------*/
	E_SNS_EEUC_ESC				= 0x7280,
	E_SNS_EERC_EEUC_EELC_ESC	= 0x7281,
	E_SNS_EERC_EEUC_ESC			= 0x7282,
	E_SNS_EERC_EELC_ESC			= 0x7283,
	E_SNS_EEUC_EELC_ESC			= 0x7284,
			/*--------------------------------------------------------------*/
			/*	ESC	stopper										(72Ax)		*/
			/*	Rev.(ZW01:BRZ-725)	add error code							*/
			/*	  E_THRUST_STOPPER_ESC,	E_ESCAPE_STOPPER_ESC				*/
			/*--------------------------------------------------------------*/
	E_THRUST_STOPPER_ESC		= 0x72A0,
	E_ESCAPE_STOPPER_ESC		= 0x72A1,
		/*------------------------------------------------------------------*/
		/*	Remain Media	Rev.(ZZ03:BRZ-060) add this error	(76xx)		*/
		/*------------------------------------------------------------------*/
			/*--------------------------------------------------------------*/
			/*	RSV												(760x)		*/
			/*--------------------------------------------------------------*/
	E_REMAIN_RSV				= 0x7601,
			/*--------------------------------------------------------------*/
			/*	ESC												(768x)		*/
			/*--------------------------------------------------------------*/
	E_REMAIN_ESC				= 0x7681,
		/*------------------------------------------------------------------*/
		/*	money trouble error									(7Cxx)		*/
		/*------------------------------------------------------------------*/
			/*--------------------------------------------------------------*/
			/*	RSV												(7C0x)		*/
			/*	Rev(ZY05:BRZ-613)	add E_DISAPPEARANCE_RSV					*/
			/*--------------------------------------------------------------*/
	E_DISAPPEARANCE_RSV			= 0x7C01,
			/*--------------------------------------------------------------*/
			/*	ESC												(7C8x)		*/
			/*	Rev(ZY05:BRZ-613)	add E_DISAPPEARANCE_ESC					*/
			/*--------------------------------------------------------------*/
	E_DISAPPEARANCE_ESC			= 0x7C81,
		/*------------------------------------------------------------------*/
		/*	a delivery is poor									(7Fxx)		*/
		/*	Rev.(ZV05:BRZ-xxx)	Delete 7F00 & 7F81 error	 				*/
		/*------------------------------------------------------------------*/
	/*----------------------------------------------------------------------*/
	/*	relate with place of Cassette-1							(8xxx)		*/
	/*----------------------------------------------------------------------*/
		/*------------------------------------------------------------------*/
		/*	poor mechanism operation							(81xx)		*/
		/*	Rev(ZZ06:BRZ-337)	Deletion error code 						*/
		/*	  E_RETRY_PICK_CA1												*/
		/*	Rev(AA41:BRZ-1512)	add error code		 						*/
		/*	  E_RETRY_DOWN_CA1_FULL,E_RETRY_UP_CA1_FULL						*/
		/*------------------------------------------------------------------*/
	E_RETRY_DOWN_CA1			= 0x8100,			/* cassette 1 downward operation retry over		*/
	E_RETRY_UP_CA1				= 0x8101,			/* cassette 1 rise operation retry over			*/
	E_RETRY_IMPELLER_CA1		= 0x8120,			/* impeller retry over							*/
	E_RETRY_DOWN_CA1_FULL		= 0x8180,			/* cassette 1 downward operation retry over		*/
	E_RETRY_UP_CA1_FULL			= 0x8181,			/* cassette 1 rise operation retry over			*/
		/*------------------------------------------------------------------*/
		/*	the abnormalities in a sensor						(82xx)		*/
		/*	Rev.(ZT02:BRZ-1124)												*/
		/*	add error code													*/
		/*------------------------------------------------------------------*/
	E_SNS_CF1C_CP1C_CA1				= 0x8200,		/* lower-end-sensor-detects with a crease check	*/
	E_SNS_CE1C_NF1C_CA1				= 0x8201,
	E_SNS_NE1C_NF1C_CA1				= 0x8202,
	E_SNS_NE1C_CF1C_CA1				= 0x8203,
		/*------------------------------------------------------------------*/
		/*	Rev.(ZZ06:BRZ-224)	add error code								*/
		/*	feed roller lock release NG							(83xx)		*/
		/*------------------------------------------------------------------*/
	E_LOCK_RELEASE_NG_CA1		= 0x8300,
		/*------------------------------------------------------------------*/
		/*	Rev.(AA41:BRZ-1512)	add error code								*/
		/*	Compulsory Storing Jam								(84xx)		*/
		/*------------------------------------------------------------------*/
	E_FULL_JAM_CA1				= 0x8400,
		/*------------------------------------------------------------------*/
 		/*	money trouble check	error							(8Cxx)		*/
 		/*------------------------------------------------------------------*/
		/*------------------------------------------------------------------*/
		/*	medium error										(8Exx)		*/
		/*	Rev(AA41:BRZ-1512)	add error code		 						*/
		/*	  E_REMAIN_BILL_PINCH_CA1_FULL									*/
		/*------------------------------------------------------------------*/
	E_REMAIN_BILL_PINCH_CA1			= 0x8E00,		/* a bite lump bill remains						*/
	E_REMAIN_BREAK_BILL_CA1			= 0x8E01,		/* crease bill remains							*/
	E_REMAIN_BILL_PINCH_CA1_FULL	= 0x8E80,		/* a bite lump bill remains						*/
		/*------------------------------------------------------------------*/
		/*	A delivery is poor									(8Fxx)		*/
		/*	Rev.(ZT05:BRZ-1132)	add error code.	( 8F03 -> 8F07, 8F10 )		*/
		/*------------------------------------------------------------------*/
	E_RETRY_DRAW_CA1			= 0x8F00,
	E_FAIL_EMPTY_CA1			= 0x8F01,
	E_RETRY_ROTARY_CA1			= 0x8F02,
	E_NOT_RECOGNIZED_OVER_CA1	= 0x8F03,
	E_DAMAGED_OVER_CA1			= 0x8F04,
	E_DIFFERENT_OVER_CA1		= 0x8F05,
	E_COUNTERFEIT_OVER_CA1		= 0x8F06,
	E_OUTSIDE_OVER_CA1			= 0x8F07,
	E_INSUFFICIENT_PAYMENT_CA1	= 0x8F10,
	/*----------------------------------------------------------------------*/
	/*	relate with place of Cassette-2							(9xxx)		*/
	/*----------------------------------------------------------------------*/
		/*------------------------------------------------------------------*/
		/*	poor mechanism operation							(91xx)		*/
		/*	Rev(ZZ06:BRZ-337)	Deletion error code 						*/
		/*	  E_RETRY_PICK_CA2												*/
		/*	Rev(AA41:BRZ-1512)	add error code		 						*/
		/*	  E_RETRY_DOWN_CA2_FULL,E_RETRY_UP_CA2_FULL						*/
		/*------------------------------------------------------------------*/
	E_RETRY_DOWN_CA2			= 0x9100,			/* cassette 2 downward operation retry over		*/
	E_RETRY_UP_CA2				= 0x9101,			/* cassette 2 rise operation retry over			*/
	E_RETRY_IMPELLER_CA2		= 0x9120,			/* impeller retry over							*/
	E_RETRY_DOWN_CA2_FULL		= 0x9180,			/* cassette 2 downward operation retry over		*/
	E_RETRY_UP_CA2_FULL			= 0x9181,			/* cassette 2 rise operation retry over			*/
		/*------------------------------------------------------------------*/
		/*	the abnormalities in a sensor						(92xx)		*/
		/*	Rev.(ZT02:BRZ-1124)												*/
		/*	add error code													*/
		/*------------------------------------------------------------------*/
	E_SNS_CF2C_CP2C_CA2			= 0x9200,			/* lower-end-sensor-detects with a crease check	*/
	E_SNS_CE2C_NF2C_CA2			= 0x9201,
	E_SNS_NE2C_NF2C_CA2			= 0x9202,
	E_SNS_NE2C_CF2C_CA2			= 0x9203,
		/*------------------------------------------------------------------*/
		/*	Rev.(ZZ06:BRZ-224)	add error code								*/
		/*	feed roller lock release NG							(93xx)		*/
		/*------------------------------------------------------------------*/
	E_LOCK_RELEASE_NG_CA2		= 0x9300,
		/*------------------------------------------------------------------*/
		/*	Rev.(AA41:BRZ-1512)	add error code								*/
		/*	Compulsory Storing Jam								(94xx)		*/
		/*------------------------------------------------------------------*/
	E_FULL_JAM_CA2				= 0x9400,
		/*------------------------------------------------------------------*/
 		/*	money trouble check	error							(9Cxx)		*/
 		/*------------------------------------------------------------------*/
		/*------------------------------------------------------------------*/
		/*	medium error										(9Exx)		*/
		/*	Rev(AA41:BRZ-1512)	add error code		 						*/
		/*	  E_REMAIN_BILL_PINCH_CA2_FULL									*/
		/*------------------------------------------------------------------*/
	E_REMAIN_BILL_PINCH_CA2			= 0x9E00,			/* a bite lump bill remains						*/
	E_REMAIN_BREAK_BILL_CA2			= 0x9E01,			/* crease bill remains							*/
	E_REMAIN_BILL_PINCH_CA2_FULL	= 0x9E80,			/* a bite lump bill remains						*/
		/*------------------------------------------------------------------*/
		/*	A delivery is poor									(9Fxx)		*/
		/*	Rev.(ZT05:BRZ-1132)	add error code.	( 9F03 -> 9F07, 9F10 )		*/
		/*------------------------------------------------------------------*/
	E_RETRY_DRAW_CA2			= 0x9F00,
	E_FAIL_EMPTY_CA2			= 0x9F01,
	E_RETRY_ROTARY_CA2			= 0x9F02,
	E_NOT_RECOGNIZED_OVER_CA2	= 0x9F03,
	E_DAMAGED_OVER_CA2			= 0x9F04,
	E_DIFFERENT_OVER_CA2		= 0x9F05,
	E_COUNTERFEIT_OVER_CA2		= 0x9F06,
	E_OUTSIDE_OVER_CA2			= 0x9F07,
	E_INSUFFICIENT_PAYMENT_CA2	= 0x9F10,
	/*----------------------------------------------------------------------*/
	/*	relate with place of Cassette-3							(Axxx)		*/
	/*----------------------------------------------------------------------*/
		/*------------------------------------------------------------------*/
		/*	poor mechanism operation							(A1xx)		*/
		/*	Rev(ZZ06:BRZ-337)	Deletion error code 						*/
		/*	  E_RETRY_PICK_CA3												*/
		/*	Rev(AA41:BRZ-1512)	add error code		 						*/
		/*	  E_RETRY_DOWN_CA3_FULL,E_RETRY_UP_CA3_FULL						*/
		/*------------------------------------------------------------------*/
	E_RETRY_DOWN_CA3			= 0xA100,			/* cassette 3 downward operation retry over		*/
	E_RETRY_UP_CA3				= 0xA101,			/* cassette 3 rise operation retry over			*/
	E_RETRY_IMPELLER_CA3		= 0xA120,			/* impeller retry over							*/
	E_RETRY_DOWN_CA3_FULL		= 0xA180,			/* cassette 3 downward operation retry over		*/
	E_RETRY_UP_CA3_FULL			= 0xA181,			/* cassette 3 rise operation retry over			*/
		/*------------------------------------------------------------------*/
		/*	the abnormalities in a sensor						(A2xx)		*/
		/*	Rev.(ZT02:BRZ-1124)												*/
		/*	add error code													*/
		/*------------------------------------------------------------------*/
	E_SNS_CF3C_CP3C_CA3			= 0xA200,			/* lower-end-sensor-detects with a crease check	*/
	E_SNS_CE3C_NF3C_CA3			= 0xA201,
	E_SNS_NE3C_NF3C_CA3			= 0xA202,
	E_SNS_NE3C_CF3C_CA3			= 0xA203,
		/*------------------------------------------------------------------*/
		/*	Rev.(ZZ06:BRZ-224)	add error code								*/
		/*	feed roller lock release NG							(A3xx)		*/
		/*------------------------------------------------------------------*/
	E_LOCK_RELEASE_NG_CA3		= 0xA300,
		/*------------------------------------------------------------------*/
		/*	Rev.(AA41:BRZ-1512)	add error code								*/
		/*	Compulsory Storing Jam								(A4xx)		*/
		/*------------------------------------------------------------------*/
	E_FULL_JAM_CA3				= 0xA400,
		/*------------------------------------------------------------------*/
 		/*	money trouble check	error							(ACxx)		*/
 		/*------------------------------------------------------------------*/
		/*------------------------------------------------------------------*/
		/*	medium error										(AExx)		*/
		/*	Rev(AA41:BRZ-1512)	add error code		 						*/
		/*	  E_REMAIN_BILL_PINCH_CA3_FULL									*/
		/*------------------------------------------------------------------*/
	E_REMAIN_BILL_PINCH_CA3			= 0xAE00,			/* a bite lump bill remains						*/
	E_REMAIN_BREAK_BILL_CA3			= 0xAE01,			/* crease bill remains							*/
	E_REMAIN_BILL_PINCH_CA3_FULL	= 0xAE80,			/* a bite lump bill remains						*/
		/*------------------------------------------------------------------*/
		/*	A delivery is poor									(AFxx)		*/
		/*	Rev.(ZT05:BRZ-1132)	add error code.	( AF03 -> AF07, AF10 )		*/
		/*------------------------------------------------------------------*/
	E_RETRY_DRAW_CA3			= 0xAF00,
	E_FAIL_EMPTY_CA3			= 0xAF01,
	E_RETRY_ROTARY_CA3			= 0xAF02,
	E_NOT_RECOGNIZED_OVER_CA3	= 0xAF03,
	E_DAMAGED_OVER_CA3			= 0xAF04,
	E_DIFFERENT_OVER_CA3		= 0xAF05,
	E_COUNTERFEIT_OVER_CA3		= 0xAF06,
	E_OUTSIDE_OVER_CA3			= 0xAF07,
	E_INSUFFICIENT_PAYMENT_CA3	= 0xAF10,
	/*----------------------------------------------------------------------*/
	/*	relate with place of Cassette-4							(Bxxx)		*/
	/*----------------------------------------------------------------------*/
		/*------------------------------------------------------------------*/
		/*	poor mechanism operation							(B1xx)		*/
		/*	Rev(ZZ06:BRZ-337)	Deletion error code 						*/
		/*	  E_RETRY_PICK_CA4												*/
		/*	Rev(AA41:BRZ-1512)	add error code		 						*/
		/*	  E_RETRY_DOWN_CA4_FULL,E_RETRY_UP_CA4_FULL						*/
		/*------------------------------------------------------------------*/
	E_RETRY_DOWN_CA4			= 0xB100,			/* cassette 4 downward operation retry over		*/
	E_RETRY_UP_CA4				= 0xB101,			/* cassette 4 rise operation retry over			*/
	E_RETRY_IMPELLER_CA4		= 0xB120,			/* impeller retry over							*/
	E_RETRY_DOWN_CA4_FULL		= 0xB180,			/* cassette 4 downward operation retry over		*/
	E_RETRY_UP_CA4_FULL			= 0xB181,			/* cassette 4 rise operation retry over			*/
		/*------------------------------------------------------------------*/
		/*	the abnormalities in a sensor						(B2xx)		*/
		/*	Rev.(ZT02:BRZ-1124)												*/
		/*	add error code													*/
		/*------------------------------------------------------------------*/
	E_SNS_CF4C_CP4C_CA4			= 0xB200,			/* lower-end-sensor-detects with a crease check	*/
	E_SNS_CE4C_NF4C_CA4			= 0xB201,
	E_SNS_NE4C_NF4C_CA4			= 0xB202,
	E_SNS_NE4C_CF4C_CA4			= 0xB203,
		/*------------------------------------------------------------------*/
		/*	Rev.(ZZ06:BRZ-224)	add error code								*/
		/*	feed roller lock release NG							(B3xx)		*/
		/*------------------------------------------------------------------*/
	E_LOCK_RELEASE_NG_CA4		= 0xB300,
		/*------------------------------------------------------------------*/
		/*	Rev.(AA41:BRZ-1512)	add error code								*/
		/*	Compulsory Storing Jam								(B4xx)		*/
		/*------------------------------------------------------------------*/
	E_FULL_JAM_CA4				= 0xB400,
		/*------------------------------------------------------------------*/
 		/*	money trouble check	error							(BCxx)		*/
 		/*------------------------------------------------------------------*/
		/*------------------------------------------------------------------*/
		/*	medium error										(BExx)		*/
		/*	Rev(AA41:BRZ-1512)	add error code		 						*/
		/*	  E_REMAIN_BILL_PINCH_CA4_FULL									*/
		/*------------------------------------------------------------------*/
	E_REMAIN_BILL_PINCH_CA4			= 0xBE00,			/* a bite lump bill remains						*/
	E_REMAIN_BREAK_BILL_CA4			= 0xBE01,			/* crease bill remains							*/
	E_REMAIN_BILL_PINCH_CA4_FULL	= 0xBE80,			/* a bite lump bill remains						*/
		/*------------------------------------------------------------------*/
		/*	A delivery is poor									(BFxx)		*/
		/*	Rev.(ZT05:BRZ-1132)	add error code.	( BF03 -> BF07, BF10 )		*/
		/*------------------------------------------------------------------*/
	E_RETRY_DRAW_CA4			= 0xBF00,
	E_FAIL_EMPTY_CA4			= 0xBF01,
	E_RETRY_ROTARY_CA4			= 0xBF02,
	E_NOT_RECOGNIZED_OVER_CA4	= 0xBF03,
	E_DAMAGED_OVER_CA4			= 0xBF04,
	E_DIFFERENT_OVER_CA4		= 0xBF05,
	E_COUNTERFEIT_OVER_CA4		= 0xBF06,
	E_OUTSIDE_OVER_CA4			= 0xBF07,
	E_INSUFFICIENT_PAYMENT_CA4	= 0xBF10,
	/*----------------------------------------------------------------------*/
	/*	relate with DES	 										(Cxxx)		*/
	/*	Rev.(ZY06:BRZ-669)													*/
	/*----------------------------------------------------------------------*/
	E_SET_ENCRYPTION_KEY		= 0xC001,
	/*----------------------------------------------------------------------*/
	/*	(reserve)		 										(Dxxx)		*/
	/*----------------------------------------------------------------------*/
	
	/*----------------------------------------------------------------------*/
	/*	relate with Jam Error									(Exxx)		*/
	/*----------------------------------------------------------------------*/
		/*------------------------------------------------------------------*/
		/*	VD Jam															*/
		/*------------------------------------------------------------------*/
	E_JAM_FAILURE_VD					= 0xE001,
		/*------------------------------------------------------------------*/
		/*	Appear Jam														*/
		/*	Rev.(ZZ03:BRZ-021)	for A3 Mecha	(UTGS->UGAS)(UTFS->UGDS)	*/
		/*	Rev.(ZY06:BRZ-681)	add for BVIN								*/
		/*	Rev.(ZV05:BRZ-979)	add for SDIS								*/
		/*	Rev.(AA41:BRZ-1512)	add Cx1S-Cx4S with full (compulsory storing)*/
		/*------------------------------------------------------------------*/
	E_JAM_APPEAR_Cx1S					= 0xE101,
	E_JAM_APPEAR_Cx2S					= 0xE102,
	E_JAM_APPEAR_Cx3S					= 0xE103,
	E_JAM_APPEAR_Cx4S					= 0xE104,
	E_JAM_APPEAR_UGAS					= 0xE105,
	E_JAM_APPEAR_ERxS					= 0xE106,
	E_JAM_APPEAR_EDxS					= 0xE107,
	E_JAM_APPEAR_UGDS					= 0xE108,
	E_JAM_APPEAR_UEFS					= 0xE109,
	E_JAM_APPEAR_UERS					= 0xE10A,
	E_JAM_APPEAR_UECS					= 0xE10B,
	E_JAM_APPEAR_URHS					= 0xE10C,
	E_JAM_APPEAR_UFHS					= 0xE10D,
	E_JAM_APPEAR_LT3S					= 0xE10E,
	E_JAM_APPEAR_SSxS					= 0xE10F,
	E_JAM_APPEAR_BVIN					= 0xE110,
	E_JAM_APPEAR_SDIS					= 0xE111,
	E_JAM_APPEAR_Cx1S_FULL				= 0xE112,
	E_JAM_APPEAR_Cx2S_FULL				= 0xE113,
	E_JAM_APPEAR_Cx3S_FULL				= 0xE114,
	E_JAM_APPEAR_Cx4S_FULL				= 0xE115,
		/*------------------------------------------------------------------*/
		/*	Arrive Jam														*/
		/*	Rev.(ZZ03:BRZ-021)	for A3 Mecha	(UTGS->UGAS)(UTFS->UGDS)	*/
		/*	Rev.(ZY06:BRZ-681)	add for BVIN								*/
		/*	Rev.(ZV05:BRZ-979)	add for SDIS								*/
		/*	Rev.(AA27:BRZ-1464)	add for UERS with full						*/
		/*	Rev.(AA30:BRZ-1480)	add for UEFS with full, UECS with full		*/
		/*	Rev.(AA41:BRZ-1512)	add Cx1S-Cx4S with full (compulsory storing)*/
		/*------------------------------------------------------------------*/
	E_JAM_ARRIVE_Cx1S					= 0xE201,
	E_JAM_ARRIVE_Cx2S					= 0xE202,
	E_JAM_ARRIVE_Cx3S					= 0xE203,
	E_JAM_ARRIVE_Cx4S					= 0xE204,
	E_JAM_ARRIVE_UGAS					= 0xE205,
	E_JAM_ARRIVE_ERxS					= 0xE206,
	E_JAM_ARRIVE_EDxS					= 0xE207,
	E_JAM_ARRIVE_UGDS					= 0xE208,
	E_JAM_ARRIVE_UEFS					= 0xE209,
	E_JAM_ARRIVE_UERS					= 0xE20A,
	E_JAM_ARRIVE_UECS					= 0xE20B,
	E_JAM_ARRIVE_URHS					= 0xE20C,
	E_JAM_ARRIVE_UFHS					= 0xE20D,
	E_JAM_ARRIVE_LT3S					= 0xE20E,
	E_JAM_ARRIVE_BVIN					= 0xE20F,
	E_JAM_ARRIVE_SDIS					= 0xE210,
	E_JAM_ARRIVE_UERS_FULL				= 0xE211,
	E_JAM_ARRIVE_UEFS_FULL				= 0xE212,
	E_JAM_ARRIVE_UECS_FULL				= 0xE213,
	E_JAM_ARRIVE_Cx1S_FULL				= 0xE214,
	E_JAM_ARRIVE_Cx2S_FULL				= 0xE215,
	E_JAM_ARRIVE_Cx3S_FULL				= 0xE216,
	E_JAM_ARRIVE_Cx4S_FULL				= 0xE217,
		/*------------------------------------------------------------------*/
		/*	Pass Jam														*/
		/*	Rev.(AA27:BRZ-1464)	add for UERS with full						*/
		/*	Rev.(AA30:BRZ-1480)	add for UEFS with full, UECS with full		*/
		/*	Rev.(AA41:BRZ-1512)	add Cx1S-Cx4S with full (compulsory storing)*/
		/*------------------------------------------------------------------*/
	E_JAM_PASS_Cx1S						= 0xE301,
	E_JAM_PASS_Cx2S						= 0xE302,
	E_JAM_PASS_Cx3S						= 0xE303,
	E_JAM_PASS_Cx4S						= 0xE304,
	E_JAM_PASS_ERxS						= 0xE305,
	E_JAM_PASS_EDxS						= 0xE306,
	E_JAM_PASS_UEFS						= 0xE307,
	E_JAM_PASS_UERS						= 0xE308,
	E_JAM_PASS_UECS						= 0xE309,
	E_JAM_PASS_SSxS						= 0xE30A,
	E_JAM_PASS_UERS_FULL				= 0xE30B,
	E_JAM_PASS_UEFS_FULL				= 0xE30C,
	E_JAM_PASS_UECS_FULL				= 0xE30D,
	E_JAM_PASS_Cx1S_FULL				= 0xE30E,
	E_JAM_PASS_Cx2S_FULL				= 0xE30F,
	E_JAM_PASS_Cx3S_FULL				= 0xE310,
	E_JAM_PASS_Cx4S_FULL				= 0xE311,
		/*------------------------------------------------------------------*/
		/*	Rev.(ZV05:BRZ-979)		add										*/
		/*	Get transport data error										*/
		/*	Rev.(AA41:BRZ-1512)	add Cx1S-Cx4S with full (compulsory storing)*/
		/*------------------------------------------------------------------*/
	E_GET_TRANSPORT_DATA_Cx1S			= 0xE401,
	E_GET_TRANSPORT_DATA_Cx2S			= 0xE402,
	E_GET_TRANSPORT_DATA_Cx3S			= 0xE403,
	E_GET_TRANSPORT_DATA_Cx4S			= 0xE404,
	E_GET_TRANSPORT_DATA_UGAS			= 0xE405,
	E_GET_TRANSPORT_DATA_ERxS			= 0xE406,
	E_GET_TRANSPORT_DATA_EDxS			= 0xE407,
	E_GET_TRANSPORT_DATA_UGDS			= 0xE408,
	E_GET_TRANSPORT_DATA_UEFS			= 0xE409,
	E_GET_TRANSPORT_DATA_UERS			= 0xE40A,
	E_GET_TRANSPORT_DATA_UECS			= 0xE40B,
	E_GET_TRANSPORT_DATA_URHS			= 0xE40C,
	E_GET_TRANSPORT_DATA_UFHS			= 0xE40D,
	E_GET_TRANSPORT_DATA_LT3S			= 0xE40E,
	E_GET_TRANSPORT_DATA_BVIN			= 0xE40F,
	E_GET_TRANSPORT_DATA_SDIS			= 0xE410,
	E_GET_TRANSPORT_DATA_Cx1S_FULL		= 0xE411,
	E_GET_TRANSPORT_DATA_Cx2S_FULL		= 0xE412,
	E_GET_TRANSPORT_DATA_Cx3S_FULL		= 0xE413,
	E_GET_TRANSPORT_DATA_Cx4S_FULL		= 0xE414,
	E_GET_TRANSPORT_DATA_TRAILING_EDGE	= 0xE480,
	/*----------------------------------------------------------------------*/
	/*	relate with Sensor Level Error etc.						(Fxxx)		*/
	/*----------------------------------------------------------------------*/
		/*------------------------------------------------------------------*/
		/*	PCB communication error								(F1xx)		*/
		/*------------------------------------------------------------------*/
	E_COMMUNICATION_PCB					= 0xF100,
		/*------------------------------------------------------------------*/
		/*	DAC Wait Error										(F21x)		*/
		/*------------------------------------------------------------------*/
	E_WAIT_DAC							= 0xF210,	/* label for setting error code	*/
	E_WAIT_UDAC							= 0xF210,	/* Upper PCB					*/
	E_WAIT_LDAC							= 0xF211,	/* Lower PCB					*/
		/*------------------------------------------------------------------*/
		/*	Transport DC Motor Rotation Error					(F30x)		*/
		/*	Rev.(ZV05:BRZ-970)												*/
		/*	 add E_ROTATION_TDCM_FLT										*/
		/*------------------------------------------------------------------*/
	E_ROTATION_TDCM						= 0xF300,
	E_ROTATION_TDCM_FLT					= 0xF301,
		/*------------------------------------------------------------------*/
		/*	Rev.(ZY05:BRZ-569)		add										*/
		/*	Over Current										(F4xx)		*/
		/*	Rev.(ZY06:BRZ-699)												*/
		/*	 Delete E_OVER_CURRENT_UFL5VSE,E_OVER_CURRENT_UFL5VES,			*/
		/*	        E_OVER_CURRENT_UFL0RSV5,E_OVER_CURRENT_UFL0RSV6			*/
		/*	 Add E_OVER_CURRENT_UFL5VSE2,E_OVER_CURRENT_UFL5VES2,			*/
		/*	     E_OVER_CURRENT_UFL5VSE4,E_OVER_CURRENT_UFL5VES4			*/
		/*------------------------------------------------------------------*/
	E_OVER_CURRENT_UFL5VPA				= 0xF400,
	E_OVER_CURRENT_UFL5VSE2				= 0xF401,
	E_OVER_CURRENT_UFL5VUB				= 0xF402,
	E_OVER_CURRENT_UFL5VES2				= 0xF403,
	E_OVER_CURRENT_UFL5VRV				= 0xF404,
	E_OVER_CURRENT_UFL5VSE4				= 0xF405,
	E_OVER_CURRENT_UFL5VES4				= 0xF406,
	E_OVER_CURRENT_UFL0RSV7				= 0xF407,
	E_OVER_CURRENT_UFL24VSE				= 0xF408,
	E_OVER_CURRENT_UFL24VUB				= 0xF409,
	E_OVER_CURRENT_UFL24VES				= 0xF40A,
	E_OVER_CURRENT_UFL24VRV				= 0xF40B,
	E_OVER_CURRENT_UFL1RSV4				= 0xF40C,
	E_OVER_CURRENT_UFL1RSV5				= 0xF40D,
	E_OVER_CURRENT_UFL1RSV6				= 0xF40E,
	E_OVER_CURRENT_UFL1RSV7				= 0xF40F,
	E_OVER_CURRENT_LFL5VLT				= 0xF410,
	E_OVER_CURRENT_LFL5VSH				= 0xF411,
	E_OVER_CURRENT_LFL5VEX				= 0xF412,
	E_OVER_CURRENT_LFL5VRV				= 0xF413,
	E_OVER_CURRENT_LFL5VCS1				= 0xF414,
	E_OVER_CURRENT_LFL5VCS2				= 0xF415,
	E_OVER_CURRENT_LFL5VCS3				= 0xF416,
	E_OVER_CURRENT_LFL5VCS4				= 0xF417,
	E_OVER_CURRENT_LFL24VLB1			= 0xF418,
	E_OVER_CURRENT_LFL24VLB2			= 0xF419,
	E_OVER_CURRENT_LFL24VLT				= 0xF41A,
	E_OVER_CURRENT_LFL24VCS				= 0xF41B,
	E_OVER_CURRENT_LFL24VEX				= 0xF41C,
	E_OVER_CURRENT_LFL24VSH				= 0xF41D,
	E_OVER_CURRENT_LFL1RSV6				= 0xF41E,
	E_OVER_CURRENT_LFL5VCS5				= 0xF41F,
	E_OVER_CURRENT_UNKNOWN				= 0xF4FF,
		/*------------------------------------------------------------------*/
		/*	Remain Media by jam-counter							(F5xx)		*/
		/*	Rev.(ZT10:BRZ-1162)	add errors of these group (F500-F52B)		*/
		/*------------------------------------------------------------------*/
	E_REMAIN_JAM_BASE					= 0xF500,
	
	E_REMAIN_JAM_SSxS_SDIS				= 0xF500,
    E_REMAIN_JAM_BVIN_UGAS				= 0xF501,
    E_REMAIN_JAM_UGAS_EDxS				= 0xF502,
    E_REMAIN_JAM_UGAS_ERxS				= 0xF503,
    E_REMAIN_JAM_UGAS_UGDS				= 0xF504,
    E_REMAIN_JAM_UGAS_URHS				= 0xF505,
    E_REMAIN_JAM_UGDS_UECS				= 0xF506,
    E_REMAIN_JAM_UGDS_UERS				= 0xF507,
    E_REMAIN_JAM_UGDS_UEFS				= 0xF508,
    E_REMAIN_JAM_URHS_Cx1S				= 0xF509,
    E_REMAIN_JAM_URHS_Cx2S				= 0xF50A,
    E_REMAIN_JAM_URHS_LT3S				= 0xF50B,
    E_REMAIN_JAM_LT3S_Cx3S				= 0xF50C,
    E_REMAIN_JAM_LT3S_Cx4S				= 0xF50D,
    E_REMAIN_JAM_LT3S_UFHS				= 0xF50E,
    E_REMAIN_JAM_UFHS_BVIN				= 0xF50F,
    E_REMAIN_JAM_Cx1S_UFHS				= 0xF510,
    E_REMAIN_JAM_Cx2S_UFHS				= 0xF511,
    E_REMAIN_JAM_Cx3S_UFHS				= 0xF512,
    E_REMAIN_JAM_Cx4S_UFHS				= 0xF513,
    E_REMAIN_JAM_SSxS					= 0xF514,
    E_REMAIN_JAM_UGAS					= 0xF515,
    E_REMAIN_JAM_UGDS					= 0xF516,
    E_REMAIN_JAM_EDxS					= 0xF517,
    E_REMAIN_JAM_ERxS					= 0xF518,
    E_REMAIN_JAM_UECS					= 0xF519,
    E_REMAIN_JAM_UERS					= 0xF51A,
    E_REMAIN_JAM_UEFS					= 0xF51B,
    E_REMAIN_JAM_URHS					= 0xF51C,
    E_REMAIN_JAM_UFHS					= 0xF51D,
    E_REMAIN_JAM_LFHS					= 0xF51E,
    E_REMAIN_JAM_LT3S					= 0xF51F,
    E_REMAIN_JAM_Cx1S					= 0xF520,
    E_REMAIN_JAM_Cx2S					= 0xF521,
    E_REMAIN_JAM_Cx3S					= 0xF522,
    E_REMAIN_JAM_Cx4S					= 0xF523,
    E_REMAIN_JAM_Cx1S_Cx2S				= 0xF524,
    E_REMAIN_JAM_Cx3S_Cx4S				= 0xF525,
    E_REMAIN_JAM_Cx1S_LT3S				= 0xF526,
    E_REMAIN_JAM_Cx2S_LT3S				= 0xF527,
    E_REMAIN_JAM_BVIN					= 0xF528,
    E_REMAIN_JAM_BVOUT					= 0xF529,
    E_REMAIN_JAM_SDIS_BVIN				= 0xF52A,
    E_REMAIN_JAM_SDIS					= 0xF52B,

		/*------------------------------------------------------------------*/
		/*	Remain Media										(F6xx)		*/
		/*	Rev.(ZZ03:BRZ-021)	for A3 Mecha	(UTGS->UGAS)(UTFS->UGDS)	*/
		/*	Rev.(ZZ03:BRZ-112)	add error code	(EELS,EERS,PASS)			*/
		/*	Rev.(ZZ06:BRZ-246)	add error code	(E_REMAIN_PATH)				*/
		/*	Rev.(ZY02:BRZ-497)	add error code	(E_REMAIN_PTCS/PSxS)		*/
		/*	Rev.(ZY04:BRZ-575)	add error code	(E_REMAIN_LFHS)				*/
		/*	Rev.(ZV07:BRZ-994)	add error code	(E_REMAIN_BUNCH_TRANSPORT)	*/
		/*	Rev.(ZT10:BRZ-1162)	delete error code	(E_REMAIN_PATH)			*/
		/*------------------------------------------------------------------*/
	E_REMAIN_SSxS						= 0xF601,
	E_REMAIN_SDIS						= 0xF602,
	E_REMAIN_SDOS						= 0xF603,
	E_REMAIN_UFHS						= 0xF604,
	E_REMAIN_URHS						= 0xF605,
	E_REMAIN_UGAS						= 0xF606,
	E_REMAIN_EDxS						= 0xF607,
	E_REMAIN_ERxS						= 0xF608,
	E_REMAIN_UGDS						= 0xF609,
	E_REMAIN_UEFS						= 0xF60A,
	E_REMAIN_UERS						= 0xF60B,
	E_REMAIN_UECS						= 0xF60C,
	E_REMAIN_Cx1S						= 0xF60D,
	E_REMAIN_Cx2S						= 0xF60E,
	E_REMAIN_Cx3S						= 0xF60F,
	E_REMAIN_Cx4S						= 0xF610,
	E_REMAIN_LT3S						= 0xF611,
	E_REMAIN_LFHS						= 0xF612,
	E_REMAIN_EELS						= 0xF620,
	E_REMAIN_EERS						= 0xF621,
	E_REMAIN_PASS						= 0xF622,
	E_REMAIN_PDSS						= 0xF623,	/* Rev.(ZY03:BRZ-512)	*/
	E_REMAIN_PTCS						= 0xF624,	/* Rev.(ZY03:BRZ-512)	*/
	E_REMAIN_PS1S						= 0xF625,	/* Rev.(ZY03:BRZ-512)	*/
	E_REMAIN_PS2S						= 0xF626,	/* Rev.(ZY03:BRZ-512)	*/
	E_REMAIN_PS3S						= 0xF627,	/* Rev.(ZY03:BRZ-512)	*/
	E_REMAIN_PS4S						= 0xF628,	/* Rev.(ZY03:BRZ-512)	*/
	E_REMAIN_BUNCH_TRANSPORT			= 0xF629,	/* Rev.(ZV07:BRZ-994)	*/
		/*------------------------------------------------------------------*/
		/*	Stay Media											(F63x)		*/
		/*	Rev.(ZY03:BRZ-512)	add error code	(E_STAY_XXXX)				*/
		/*	Rev.(ZY04:BRZ-557)	change error code.							*/
		/*	Rev.(ZY04:BRZ-577)	add error code.	(E_STAY_LFHS)				*/
		/*	Rev.(ZW04:BRZ-811)	add error code.	(E_STAY_BVIN,BVOUT)			*/
		/*	Rev.(AA41:BRZ-1512)	add Cx1S-Cx4S with full (compulsory storing)*/
		/*------------------------------------------------------------------*/
	E_STAY_SSxS							= 0xF631,
	E_STAY_SDIS							= 0xF632,
	E_STAY_SDOS							= 0xF633,
	E_STAY_UFHS							= 0xF634,
	E_STAY_URHS							= 0xF635,
	E_STAY_UGAS							= 0xF636,
	E_STAY_EDxS							= 0xF637,
	E_STAY_ERxS							= 0xF638,
	E_STAY_UGDS							= 0xF639,
	E_STAY_UEFS							= 0xF63A,
	E_STAY_UERS							= 0xF63B,
	E_STAY_UECS							= 0xF63C,
	E_STAY_Cx1S							= 0xF63D,
	E_STAY_Cx2S							= 0xF63E,
	E_STAY_Cx3S							= 0xF63F,
	E_STAY_Cx4S							= 0xF640,
	E_STAY_LT3S							= 0xF641,
	E_STAY_EELS							= 0xF642,
	E_STAY_EERS							= 0xF643,
	E_STAY_PASS							= 0xF644,
	E_STAY_PDSS							= 0xF645,
	E_STAY_PTCS							= 0xF646,
	E_STAY_PS1S							= 0xF647,
	E_STAY_PS2S							= 0xF648,
	E_STAY_PS3S							= 0xF649,
	E_STAY_PS4S							= 0xF64A,
	E_STAY_LFHS							= 0xF64B,
	E_STAY_BVIN							= 0xF64C,
	E_STAY_BVOUT						= 0xF64D,
	E_STAY_Cx1S_FULL					= 0xF64E,
	E_STAY_Cx2S_FULL					= 0xF64F,
	E_STAY_Cx3S_FULL					= 0xF650,
	E_STAY_Cx4S_FULL					= 0xF651,
		/*------------------------------------------------------------------*/
		/*	Illegal Sensor Error							(F7xx)			*/
		/*	Rev.(ZZ04:BRZ-170)												*/
		/*	Rev.(ZY04:BRZ-577)	add error code.	(E_ILLEGAL_LFHS)			*/
		/*	Rev.(ZY05:BRZ-607)	add error code.	(E_ILLEGAL_xxxC)			*/
		/*	Rev.(ZW04:BRZ-811)	add error code.	(E_ILLEGAL_BVxx)			*/
		/*	Rev.(ZW06:BRZ-899)	add error code.	(E_ILLEGAL_SHCC)			*/
		/*	Rev.(ZV01:BRZ-910)	add error code.	(E_ILLEGAL_SBLC,UGLC)		*/
		/*	Rev.(ZV01:BRZ-912)	add error code.	(E_ILLEGAL_ETLC)			*/
		/*	Rev.(ZV02:BRZ-920)	add error code.	(E_ILLEGAL_INTERLOCK)		*/
		/*	Rev.(ZV05:BRZ-985)	add error code.	(E_ILLEGAL_PSxS) (x=1-4)	*/
		/*	Rev.(ZV05:BRZ-985)	add error code.	(E_ILLEGAL_PSxS) (x=1-4)	*/
		/*	Rev.(ZV08:BRZ-1011)	add error code.								*/
		/*				(E_ILLEGAL_PTCS/PASS/PDSS/EERS/EELS/EECS/PTPC/PBPC)	*/
		/*	Rev.(AA41:BRZ-1512)	add Cx1S-Cx4S with full (compulsory storing)*/
		/*------------------------------------------------------------------*/
	E_ILLEGAL_SSxS						= 0xF700,
	E_ILLEGAL_UGAS						= 0xF701,
	E_ILLEGAL_UGDS						= 0xF702,
	E_ILLEGAL_EDxS						= 0xF703,
	E_ILLEGAL_ERxS						= 0xF704,
	E_ILLEGAL_UECS						= 0xF705,
	E_ILLEGAL_UERS						= 0xF706,
	E_ILLEGAL_UEFS						= 0xF707,
	E_ILLEGAL_URHS						= 0xF708,
	E_ILLEGAL_UFHS						= 0xF709,
	E_ILLEGAL_LT3S						= 0xF70A,
	E_ILLEGAL_Cx1S						= 0xF70B,
	E_ILLEGAL_Cx2S						= 0xF70C,
	E_ILLEGAL_Cx3S						= 0xF70D,
	E_ILLEGAL_Cx4S						= 0xF70E,
	E_ILLEGAL_LFHS						= 0xF70F,
	E_ILLEGAL_UULC						= 0xF710,
	E_ILLEGAL_ULPC						= 0xF711,
	E_ILLEGAL_URLC						= 0xF712,
	E_ILLEGAL_BLLC						= 0xF713,
	E_ILLEGAL_BVIN						= 0xF714,
	E_ILLEGAL_BVOUT						= 0xF715,
	E_ILLEGAL_SHCC						= 0xF716,
	E_ILLEGAL_SBLC						= 0xF717,
	E_ILLEGAL_UGLC						= 0xF718,
	E_ILLEGAL_ETLC						= 0xF719,
	E_ILLEGAL_INTERLOCK					= 0xF71A,
	E_ILLEGAL_PS1S						= 0xF71B,
	E_ILLEGAL_PS2S						= 0xF71C,
	E_ILLEGAL_PS3S						= 0xF71D,
	E_ILLEGAL_PS4S						= 0xF71E,
	E_ILLEGAL_PTCS						= 0xF71F,
	E_ILLEGAL_PASS						= 0xF720,
	E_ILLEGAL_PDSS						= 0xF721,
	E_ILLEGAL_EERS						= 0xF722,
	E_ILLEGAL_EELS						= 0xF723,
	E_ILLEGAL_EECS						= 0xF724,
	E_ILLEGAL_PTPC						= 0xF725,
	E_ILLEGAL_PBPC						= 0xF726,
	E_ILLEGAL_Cx1S_FULL					= 0xF727,
	E_ILLEGAL_Cx2S_FULL					= 0xF728,
	E_ILLEGAL_Cx3S_FULL					= 0xF729,
	E_ILLEGAL_Cx4S_FULL					= 0xF72A,
		/*------------------------------------------------------------------*/
		/*	Sensor Max Level Over Error						(FF0x - FF2x)	*/
		/*	Rev.(ZZ06:BRZ-295)												*/
		/*	 Add PDSS														*/
		/*	Rev.(ZY02:BRZ-507)												*/
		/*	 Add LFHS														*/
		/*	Rev.(ZV01:BRZ-911)												*/
		/*	 Add ETRS														*/
		/*------------------------------------------------------------------*/
	E_OVER_MAX_LEVEL_SENSOR				= 0xFF00,	/* label for setting error code	*/
	E_OVER_MAX_LEVEL_PS1S				= 0xFF00,
	E_OVER_MAX_LEVEL_PS2S				= 0xFF01,
	E_OVER_MAX_LEVEL_PS3S				= 0xFF02,
	E_OVER_MAX_LEVEL_PS4S				= 0xFF03,
	E_OVER_MAX_LEVEL_PTCS				= 0xFF04,
	E_OVER_MAX_LEVEL_PASS				= 0xFF05,
	E_OVER_MAX_LEVEL_PDSS				= 0xFF06,
	E_OVER_MAX_LEVEL_SDIS				= 0xFF07,
	E_OVER_MAX_LEVEL_SDOS				= 0xFF08,
	E_OVER_MAX_LEVEL_SSLS				= 0xFF09,
	E_OVER_MAX_LEVEL_SSRS				= 0xFF0A,
	E_OVER_MAX_LEVEL_SSOS				= 0xFF0B,
	E_OVER_MAX_LEVEL_EECS				= 0xFF0C,
	E_OVER_MAX_LEVEL_ETLS				= 0xFF0D,
	E_OVER_MAX_LEVEL_EELS				= 0xFF0E,
	E_OVER_MAX_LEVEL_EERS				= 0xFF0F,
	E_OVER_MAX_LEVEL_EDLS				= 0xFF10,
	E_OVER_MAX_LEVEL_EDRS				= 0xFF11,
	E_OVER_MAX_LEVEL_ERLS				= 0xFF12,
	E_OVER_MAX_LEVEL_ERRS				= 0xFF13,
	E_OVER_MAX_LEVEL_UGAS				= 0xFF14,
	E_OVER_MAX_LEVEL_URHS				= 0xFF15,
	E_OVER_MAX_LEVEL_UFHS				= 0xFF16,
	E_OVER_MAX_LEVEL_UGDS				= 0xFF17,
	E_OVER_MAX_LEVEL_UECS				= 0xFF18,
	E_OVER_MAX_LEVEL_UEFS				= 0xFF19,
	E_OVER_MAX_LEVEL_UERS				= 0xFF1A,
	E_OVER_MAX_LEVEL_LT3S				= 0xFF1B,
	E_OVER_MAX_LEVEL_LFHS				= 0xFF1C,
	E_OVER_MAX_LEVEL_CL1S				= 0xFF1D,
	E_OVER_MAX_LEVEL_CR1S				= 0xFF1E,
	E_OVER_MAX_LEVEL_CL2S				= 0xFF1F,
	E_OVER_MAX_LEVEL_CR2S				= 0xFF20,
	E_OVER_MAX_LEVEL_CL3S				= 0xFF21,
	E_OVER_MAX_LEVEL_CR3S				= 0xFF22,
	E_OVER_MAX_LEVEL_CL4S				= 0xFF23,
	E_OVER_MAX_LEVEL_CR4S				= 0xFF24,
	E_OVER_MAX_LEVEL_CT1S				= 0xFF25,
	E_OVER_MAX_LEVEL_CT2S				= 0xFF26,
	E_OVER_MAX_LEVEL_CT3S				= 0xFF27,
	E_OVER_MAX_LEVEL_CT4S				= 0xFF28,
	E_OVER_MAX_LEVEL_ETRS				= 0xFF29,
		/*------------------------------------------------------------------*/
		/*	Sensor Off Check Error							(FF5x - FF7x)	*/
		/*	Rev.(ZZ06:BRZ-295)												*/
		/*	 Add PDSS														*/
		/*	Rev.(ZY02:BRZ-507)												*/
		/*	 Add LFHS														*/
		/*	Rev.(ZV01:BRZ-911)												*/
		/*	 Add ETRS														*/
		/*------------------------------------------------------------------*/
	E_OFF_SENSOR						= 0xFF50,	/* label for setting error code	*/
	E_OFF_PS1S							= 0xFF50,
	E_OFF_PS2S							= 0xFF51,
	E_OFF_PS3S							= 0xFF52,
	E_OFF_PS4S							= 0xFF53,
	E_OFF_PTCS							= 0xFF54,
	E_OFF_PASS							= 0xFF55,
	E_OFF_PDSS							= 0xFF56,
	E_OFF_SDIS							= 0xFF57,
	E_OFF_SDOS							= 0xFF58,
	E_OFF_SSLS							= 0xFF59,
	E_OFF_SSRS							= 0xFF5A,
	E_OFF_SSOS							= 0xFF5B,
	E_OFF_EECS							= 0xFF5C,
	E_OFF_ETLS							= 0xFF5D,
	E_OFF_EELS							= 0xFF5E,
	E_OFF_EERS							= 0xFF5F,
	E_OFF_EDLS							= 0xFF60,
	E_OFF_EDRS							= 0xFF61,
	E_OFF_ERLS							= 0xFF62,
	E_OFF_ERRS							= 0xFF63,
	E_OFF_UGAS							= 0xFF64,
	E_OFF_URHS							= 0xFF65,
	E_OFF_UFHS							= 0xFF66,
	E_OFF_UGDS							= 0xFF67,
	E_OFF_UECS							= 0xFF68,
	E_OFF_UEFS							= 0xFF69,
	E_OFF_UERS							= 0xFF6A,
	E_OFF_LT3S							= 0xFF6B,
	E_OFF_LFHS							= 0xFF6C,
	E_OFF_CL1S							= 0xFF6D,
	E_OFF_CR1S							= 0xFF6E,
	E_OFF_CL2S							= 0xFF6F,
	E_OFF_CR2S							= 0xFF70,
	E_OFF_CL3S							= 0xFF71,
	E_OFF_CR3S							= 0xFF72,
	E_OFF_CL4S							= 0xFF73,
	E_OFF_CR4S							= 0xFF74,
	E_OFF_CT1S							= 0xFF75,
	E_OFF_CT2S							= 0xFF76,
	E_OFF_CT3S							= 0xFF77,
	E_OFF_CT4S							= 0xFF78,
	E_OFF_ETRS							= 0xFF79,
	/*----------------------------------------------------------------------*/
	/*	Table End															*/
	/*----------------------------------------------------------------------*/
	E_TABLE_END				= 0xFFFF	/*	End of Error Table				*/
};	/*	ERROR_CODE	*/
