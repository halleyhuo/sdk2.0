/***

	*************************************************************************
	*																		*
	*		header file for types and defines								*
	*																		*
	*														TYPEDEF.H		*
	*************************************************************************
	ALL RIGHTS RESERVED, COPYRIGHT(C) FUJITSU FRONTECH LIMITED. 2002-2008

	SN			Date		Name		Revision.No.	Contents
	-------------------------------------------------------------------------
	001-ZZ01	2002/10/28	M.Banba		<BRZ-001>		The First Version
				2002/11/28	M.Kibe		
				2003/01/14	M.Kibe
				2003/01/21	M.Banba						add PKT_BILL structure
				2003/02/10	M.Kibe						P_NO_END is added to a PLACE_NO type
				2003/02/13	M.Kibe						INFINITE_EVENT is moved from l_mecha.h
														RAPID_STOP is moved from l_mecha.h
				2003/02/14	M.Kibe						add MECHA_UPR_PRE_ADJUST_FEEDING
				2003/02/20	A.Maruyama					change value of TICK (2->1)
				2003/02/24  M.Banba						add TASK_CMD_DEBUG
				2003/02/28	M.Banba						add Note discrimination information
				2003/03/03  M.Kibe						upper position change of MECHA_RESPONSE
				2003/03/07  M.Banba						add PRINT_CMD_MOVE / PRINT_TRANS
				2003/03/10	A.Maruyama					add typedef&struct for error information
				2003/03/11	M.Banba						add RAS_KEY
				2003/03/12	A.Maruyama					add PRINT_MECHA
				2003/03/13	Y.Saito						add RAS_INPUT_MODE
				2003/03/14	M.Kibe						add	MECHA_CA_ALL
				2003/03/18	M.Banba						add IEF_COMPLETE_STOP
				2003/03/25	M.Kibe						add MECHA_CA_FEW_DOWN
				2003/03/26	M.Banba						add CASSETTE_TYPE
	002-ZZ02	2003/03/28	M.Banba						add IEF_ADJUST_ESC
				2003/03/28	Y.Saito						add MECHA_UPR_DECOMPRESS
				2003/04/01	M.Kibe		<BRZ-008>		add MECHA_ADJUST_STACK
				2003/04/02	M.Banba						add STATE_PROCESS
				2003/04/07	M.Kamimura	<BRZ-005>		change MOVE_REQUEST type member
														delete JOB_NONE_COMPLETE
														add MECHA_RJT_BIN
							M.Kibe		<BRZ-007>		add P_UPPER
										<BRZ-007>		MECHA_POSITION is moved to TYPEDEF.H from MECHA.H
				2003/04/09	M.Kamimura	<BRZ-005>		change PKT_BILL type member
														add define for PKT_BILL type member
				2003/04/15	A.Kojima	<BRZ-018>		add speed MOREHIGH
										<BRZ-019>		change sensor level defines
				2003/04/16	M.Kamimura	<BRZ-005>		change Name (NOTE_TRUTH_LOSS->NOTE_TRUTH_DAMAGED)
														add NOTE_TRUTH_JUDGMENT
														change INT_END_LEVEL0 of value
				2003/04/16	A.Kojima	<BRZ-019>		add LSNS_END
	003-ZZ03	2003/04/17	M.Banba		<BRZ-024>		For insertion extraction watch task
				2003/04/22	Y.Saito						add MECHA_UPR_PREPARE_END
							A.Kojima	<BRZ-021>		change driver defines for new upper(A3 Mech.)
				2003/04/23	M.Banba		<BRZ-021>		Change sensor flag for new upper(A3 Mech.)
				2003/04/25	M.Kamimura	<BRZ-034>		Reexamination of a define definition
							M.Kibe		<BRZ-030>		add FORCE MODE
							M.Banba		<BRZ-036>		add to MECHA_ORDER
														-Order for PreAcceptor & Separator
				2003/04/28	M.Banba		<BRZ-043>		add to MECHA_POSITION
														-position for PreAcceptor & Separator
				2003/04/30	M.Kibe		<BRZ-049>		add to MECHA_POSITION
														add MECHA_POSI_RELEASE_ESC
														add MECHA_POSI_RELEASE_RSV
														It changes into MECHA_POSI_RELEASE from MECHA_POSI_DISCHAGE
														It changes into MECHA_POSI_TOP from MECHA_POSI_UPPER
														add	MECHA_POSI_BOTTOM
														add MECHA_POSI_SEP_PUSHER_BEFORE_JOIN
							M.Kamimura	<BRZ-053>		change label name(EXTRACT->PRESENT)
				2003/05/01	M.Banba		<BRZ-059>		change MECHA_ORDER
														:MECHA_UPR_REPAY_BILL_COMPULSORILY->MECHA_UPR_REPAY_BILL_ALWAYS
				2003/05/06	M.Banba		<BRZ-064>		compulsion return is abolished(MECHA_UPR_REPAY_BILL_ALWAYS)
														adds the compulsion taking(MECHA_UPR_MOVE_BILL_ALWAYS)
										<BRZ-065>		add MECHA_ORDER
														:MECHA_SUB_PAC_PREPARE_MOVE
														:MECHA_SUB_PAC_MOVE
														:MECHA_UPR_COLLECT_BILL
										<BRZ-074>		add MECHA_ORDER
														:MECHA_UPR_PAY_BILL
										<BRZ-075>		add MECHA_ORDER
														:MECHA_UPR_EJECT_BILL
							Y.Saito		<BRZ-073>		add to MECHA_POSITION
														:MECHA_POSI_INSERT
							A.Maruyama	<BRZ-076>		add MECHA_POSITION
														:MECHA_POSI_DISCHARGE
														:MECHA_POSI_PAC_CHECK_LENGTH
														:MECHA_POSI_PAC_PREPARE_MOVE
														:MECHA_POSI_PAC_MOVE
														:MECHA_POSI_PAC_BEFORE_JOIN
														:MECHA_POSI_PAC_PREPARE_JOIN
														:MECHA_POSI_PAC_JOIN
														:MECHA_POSI_PAC_PRE_DISCHARGE
														:MECHA_POSI_PAC_TRAY_PDPC_PLPC
														:MECHA_POSI_PAC_TRAY_PLPC_PRPC
														:MECHA_POSI_PAC_CARRIER_ECHC_ECCC
														:MECHA_POSI_PAC_CARRIER_ECCC_ECPC
														:MECHA_POSI_PAC_CARRIER_ECPC_SEP
				2003/05/07	M.Kibe		<BRZ-081>		Label name change
														:MECHA_SUB_CA_STAGE_UP_PRESS
														:MECHA_SUB_CA_STAGE_UP_TOP
														:MECHA_SUB_CA_STAGE_UP_FEW
														:MECHA_SUB_CA_STAGE_DOWN_STACK
														:MECHA_SUB_CA_STAGE_DOWN_LEVEL
				2003/05/12	M.Kamimura	<BRZ-100>		add definition of minimum timer value
														:C_TIME_HURRY
										<BRZ-108>		add IO_REQUEST type
														:IO_REQUEST
	004-ZZ04	2003/05/19	M.Banba		<BRZ-133>		add define
														:MAX_SIZE_BUFFER_LINE
							M.Kamimura	<BRZ-133>		add structure
														:COMMUNICATION_HEADER
														:MESSAGE_HEADER
														:DATA_HEADER
				2003/05/20	M.Kibe		<BRZ-030>		FORCE_EMPTY is added to a MECHA_DEBUG_MODE type
							M.Kamimura	<BRZ-128>		add label of TASK_MSG
														:TASK_CMD_HALT_RECEPTION
														:TASK_LINE_SEND_END
				2003/05/21	M.Kamimura	<BRZ-129>		add enum (Command code)
										<BRZ-141>		change typdef enum -> enum
				2003/05/22	M.Banba		<BRZ-142>		add TASK_DRAS
				2003/05/23	M.Kibe		<BRZ-030>		MECHA_DEBUG_MODE value change
														add MECHA_DEBUG_CLR
				2003/05/26	M.Kamimura	<BRZ-143>		add label of TASK_MSG
														:TASK_RESP_REQUEST_LAST
														:TASK_RESP_REQUEST_BETWEEN
														:TASK_RESP_END_LAST
														;TASK_RESP_END_BETWEEN
														add CMD_INFORMATION type
														:CMD_INFORMATION
							M.Kibe		<BRZ-143>		add enum(RESP_xxx)
				2003/05/27	Y.Saito		<BRZ-144>		Change of a label name
														:xx_UPR_xx -> xx_UPPER_xx
				2003/05/28	A.Maruyama	<BRZ-146>		add enum for machine type
				2003/06/05	M.Kibe		<BRZ-149>		add FX_DATA type
														add	F0_DATA type
														add	G0_DATA	type
														add	Gx_DATA	type
														add	IX_DATA	type
														add	enum
				2003/06/12	M.Kamimura	<BRZ-159>		add PKT_BILL type member (vd_log)
														:PKT_BILL
										<BRZ-160>		add FRAME_FORM type
														:FRAME_FORM
				2003/06/17	M.Kamimura	<BRZ-133>		change label name(FUNCTON->FUNCTION)
														:HEADER_FUNCTION_H
														:HEADER_FUNCTION_L
							A.Maruyama	<BRZ-167>		add definitions for kind of program's version
														:PRG_VER_BOOT
														:PRG_VER_MAIN
														:PRG_VER_SUB
														:PRG_VER_BV
														:PRG_VER_BV_SUB
														:PRG_VER_CONTROL_DATA
														:PRG_VER_RESERVE
														:PRG_VER_MAX
				2003/06/18	M.Kamimura	<BRZ-160>		change max size
														:MAX_SIZE_FRAME(1496->1500)
														:MAX_SIZE_MESSAGE_DATA(1474->1478)
										<BRZ-169>		add STATE_PROCESS member
														:PROCESS_CLEAR
														:PROCESS_MOVE
														:PROCESS_SNS_ADJUST
														:PROCESS_ILLEGAL_WATCH
				2003/06/24	M.Kamimura	<BRZ-178>		add command code.(EK,CP,LG,PC,RS)
														:CMD_EK
														:CMD_CP
														:CMD_LG
														:CMD_PC
														:CMD_RS
							M.Banba		<BRZ-179>		add TASK_MSG
														:TASK_RESP_REQUEST_PROGRESS
				2003/06/25	M.Kamimura	<BRZ-184>		add response order
														:RESP_NONE
				2003/06/27	M.Kamimura	<BRZ-186>		add INT_END_LEVEL2_ERR
														:add INT_END_LEVEL2_ERR
	005-ZZ05	2003/06/30	M.Banba		<BRZ-189>		add or delete TASK_MSG
														:TASK_BV_RESPONSE(delete)
				2003/07/01	M.Banba		<BRZ-190>		The label addition for six cassettes
							M.Kamimura	<BRZ-192>		add kind of bill definitions
														:KIND_BILL_xxx
				2003/07/04	M.Kamimura	<BRZ-193>		add operation mode definitions
														:OPERATION_MODE
														add Note Generation definitions
														:NOTE_GENERATION_OLD4 -> JUDGMENT
														add Note Publication definitions
														:NOTE_PUBLICATION_JUDGMENT
														add denomination of cassette definitions
														:DENOMINATION_CA_xxx
														:KIND_CA_xxx
										<BRZ-195>		add jam place label(No.35->38)
														:JAM_Cx1S_Cx2S
														:JAM_Cx3S_Cx4S
														:JAM_Cx1S_LT3S
														:JAM_Cx2S_LT3S
				2003/07/07	M.Kamimura	<BRZ-206>		change label name.(TASK_MSG)
														:TASK_RESP_REQUEST_PROGRESS
														:TASK_RESP_REQUEST_INTERVAL
														:TASK_RESP_END_PROGRESS
				2003/07/11	M.Kamimura	<BRZ-192>		add kind of bill definitions
														:KIND_BILL_UNJUST
	006-ZZ06	2003/07/15	M.Kibe		<BRZ-228>		add CASSETTE_DEMAND_CODE
										<BRZ-223>		add MECHA_ORDER
														:MECHA_CA_BILL_STAY_CLEAR
										<BRZ-229>		add MECHA_ORDER
														:MECHA_CA_CHECK_IMPELLER
										<BRZ-220>		add MECHA_ORDER
														:MECHA_CA_PHASE_ADJUST_FEEDING
							A.Kojima	<BRZ-237>		add a task message
														:TASK_LAN_TIME_OUT_SEND
				2003/07/16	M.Banba		<BRZ-240>		add a task message
														:TASK_BV_RECEPTION_RESET
														:TASK_BV_RECEPTION_RESET_ERROR
				2003/07/17	M.Kamimura	<BRZ-220>		add label of INT_END_FACTOR.
														:IEF_ROTARY_RETRY
										<BRZ-242>		change value of INT_END_LEVELx.
														:INT_END_LEVELx
				2003/07/17	M.Kibe		<BRZ-228>		add CASSETTE_DEMAND_CODE
				2003/07/18	M.Kamimura	<BRZ-244>		change PKT_BILL type member name. (vd_log->vd_all)
														:PKT_BILL
				2003/07/18	Y.Saito		<BRZ-249>		add BV Validatation Mode
				2003/07/22	M.Kibe		<BRZ-261>		add MECHA_POSI_AFTER_FEED
				2003/07/24	M.Kibe		<BRZ-273>		MECHA_CA_BILL_STAY_CLEAR / MECHA_CA_CHECK_IMPELLER deletion
				2003/07/28	M.Banba		<BRZ-279>		add label
														:JAM_BVIN,JAM_BVOUT
										<BRZ-283>		change struct data in COMMUNICATION_HEADER
														:reserve -> continuity
							M.Kibe		<BRZ-273>		MECHA_CA_PHASE_ADJUST_FEEDING deletion
										<BRZ-287>		type / label change
				2003/08/01	Y.Saito		<BRZ-291>		add a task message
														:TASK_MOVE_ERROR
				2003/08/08	M.Kamimura	<BRZ-285>		add extension bool type.
														:EXT_BOOL
														add completion setup status type.
														:DATA_STATE_SETUP
														add damaged of bill definition.
														:KIND_BILL_DAMAGED
														add label of INT_END_FACTOR.
														:IEF_VALIDATE_AGAIN
														add label of JOB_END_FACTOR.
														:JOB_BAD_BILL_FEED
										<BRZ-310>		add definition of send factor.
														:SEND_FACTOR_xxx
				2003/08/20	A.Kojima	<BRZ-295>		change kind of solenoid and add a sensor
														:PHMG,LPDSS
							M.Kibe		<BRZ-306>		Sensor Name change and an addition
														:S_PPRC -> S_PBPC
														:S_PLPC -> S_PTPC
														:S_PDSS
										<BRZ-307>		Deletion order
														:MECHA_SUB_SEP_ADJUST_CLAMP
														:MECHA_SUB_SEP_PRESS_OFF
										<BRZ-308>		Position change and deletion
														:MECHA_POSI_PAC_TRAY_PDPC_PLPC->MECHA_POSI_PAC_TRAY_PDPC_PRPC
														:MECHA_POSI_PAC_TRAY_PLPC_PRPC
							M.Kibe		<BRZ-308>		Position addition
														:MECHA_POSI_PAC_TRAY_SAVE_POSITION
														:MECHA_POSI_PAC_CLAMP_DEPRESS_FEW
							A.Kojima	<BRZ-312>		add THRUST and ESCAPE for PAMG,PDMG,PHMG
														:THRUST,ESCAPE
							M.Kibe		<BRZ-308>		Position change/addition
														:MECHA_POSI_PAC_TRAY_PDPC_CHECKLENGTH
														:MECHA_POSI_PAC_TRAY_CHECKLENGTH_PRPC
							M.Kibe		<BRZ-301>		addition MECHA_ORDER
				2003/08/21	M.Banba		<BRZ-324>		add process
														:PROCESS_LINE_RECEPTION
				2003/08/21	M.Kibe		<BRZ-329>		add order
														:MECHA_SUB_MOVE_INITAIAL_POSITION
				2003/08/25	M.Banba		<BRZ-285>		Different denominations number-of-sheets over is added.
														:IEF_DIFFERENT_OVER
														change label
														:IEF_BAD_BILL_OVER -> IEF_NOT_RECOGNIZED_OVER
							M.Kamimura	<BRZ-321>		add label of TASK_MSG.
														:TASK_LINE_RECEPTION_ERROR
	007-ZZ07	2003/09/01	M.Banba		<BRZ-340>		add label of TASK_MSG.
														:TASK_STOP_REQUEST
				2003/09/02	M.Banba		<BRZ-341>		Job task addition correspondence
							M.Kibe		<BRZ-344>		add upper part medium remains place
										<BRZ-349>		add sensor level set place
				2003/09/02	M.Banba		<BRZ-350>		add EXT_MECHA_PLACE
				2003/09/04	M.Banba		<BRZ-351>		add TASK_IO_REQUEST_SC
				2003/09/05	M.Banba		<BRZ-341>		add Job-task request label
				2003/09/08	M.Kibe		<BRZ-352>		add order
														:MECHA_SUB_PAC_TRAY_MOVE_SAVE_POSITION
														:MECHA_SUB_PAC_BEFORE_PAY_BILL
				2003/09/08	M.Kibe		<BRZ-355>		add order
														:MECHA_UPPER_REPAY_BILL_ALWAYS
				2003/09/12	M.Banba		<BRZ-368>		The order for PAC taking-in operation of a restoration system is added.
														:MECHA_UPPER_TAKE_BILL
														:MECHA_SUB_PAC_ADJUST_MOVE
				2003/09/19	M.Kibe		<BRZ-383>		position addition
														:MECHA_POSI_PAC_BEFORE_EJECT
				2003/09/20	A.Maruyama	<BRZ-386>		add kind of download-status and file-name
	008-ZY01	2003/10/02	A.Kojima	<BRZ-408>		change for B'-model
				2003/10/02	M.Kibe		<BRZ-397>		add order
														:MECHA_SUB_PAC_CARRIER_POSITION_0_CHECK
														add position
														:MECHA_POSI_PAC_CARRIER_ZERO_CHECK
							M.Banba		<BRZ-409>		add JOB_REQUEST
														:JOB_REQUEST_INSERT
														:JOB_REQUEST_PRESENT
														:JOB_REQUEST_FEED
				2003/10/06	M.Banba		<BRZ-409>		add TASK_MSG
														:TASK_JOB_REQUEST_CLEAR_JAM
														:TASK_JOB_REQUEST_CHECK_TRANSPORT
														:TASK_JOB_REQUEST_CONFIRM_MECHA
														:TASK_JOB_REQUEST_CLOSE_SHT
														:TASK_JOB_REQUEST_INSERT
														:TASK_JOB_REQUEST_PRESENT
														:TASK_JOB_REQUEST_FEED
							M.Kamimura	<BRZ-413>		add label of I/O condition.
														:IO_CHANGE_MEDIA
							M.Kibe		<BRZ-394>		add order
														:MECHA_SUB_SEP_BEFORE_BACKFEED
														:MECHA_SUB_SEP_ESCAPE_COMB
				2003/10/07	M.Kamimura	<BRZ-409>		add MOVE_END_FACTOR label.
														:MOVE_TDCM_ERR
														:MOVE_BV_ERR
				2003/10/09	M.Banba		<BRZ-419>		add TASK_MSG
														:TASK_WATCH_MACHINE_TYPE
				2003/10/14	Y.Saito		<BRZ-421>		add TASK_RFNC
														add TASK_MSG
														:TASK_RAS_RECEPTION
				2003/10/15	M.Kibe		<BRZ-422>		add order
														:MECHA_SUB_PAC_CHECK_LENGTH_EJECT
				2003/10/20	M.Kamimura	<BRZ-426>		add JOB_END_FACTOR label.
														:JOB_ABORT_END
														add max number of sensor.
														:MAX_SNS_NUMBER
				2003/10/21	M.Banba		<BRZ-432>		Renewal correspondence of unit set information
				2003/10/28	M.Kamimura	<BRZ-433>		add RESP_REQUEST type.
														:RESP_ORDER_MAX
				2003/10/29	M.Banba		<BRZ-440>		change type of PKT_DATA member.
 														:RESP_REQUEST
	009-ZY02	2003/11/08	M.Kibe		<BRZ-451>		add position
														:MECHA_POSI_PAC_INITIAL
										<BRZ-452>		add label
														:P_NO_TOP
				2003/11/08	A.Kojima	<BRZ-439>		add print select bit for LAN
														:PRINT_LAN_PACKET,PRINT_LAN_BV
				2003/11/11	M.Kamimura	<BRZ-459>		add JOB_END_FACTOR label.
														:MOVE_DEST_ERR
				2003/11/14	M.Kamimura	<BRZ-461>		add label of cassette type.(Generation)
														:GENERATION_xxx
														add mask of bill definition.
														:KIND_BILL_MASK
	010-ZY03	2003/12/01	M.Banba		<BRZ-511>		add processing
														:PROCESS_CLEAR_FINAL
				2003/12/02	M.Kibe		<BRZ-515>		add order
														:MECHA_UPPER_TRANSPORT_CLEAR
										<BRZ-516>		add order
														:MECHA_CHECK_EMPTY
							M.Kamimura	<BRZ-517>		add command code.
														:CMD_BC
				2003/12/08	M.Kamimura	<BRZ-529>		Renewal definition of treatment number.
														:BV_TREATMENT_xxx
				2003/12/08	M.Kibe		<BRZ-532>		add position
														:MECHA_POSI_SHT_OPEN
														:MECHA_POSI_SHT_CLOSE
	011-ZY04	2003/12/12	Y.Saito		<BRZ-531>		Add response to setting CP for RAS.
														:RAS_HARD_DENOMI_xxx
				2003/12/16	M.Kibe		<BRZ-555>		Add define/enum
							A.Maruyama	<BRZ-563>		add definition of reject bin type
				2003/12/17	M.Kamimura	<BRZ-566>		Add label of TASK_MSG.
														:TASK_RESP_REQUEST_DIVISION
														:TASK_RESP_END_DIVISION
				2003/12/18	M.Kamimura	<BRZ-567>		Add / delete command code.(D-Level draft 7)
														:CMD_xx
														Add response request order.
														:RESP_T0
				2003/12/19	M.Kamimura	<BRZ-572>		Add definition of insertion / presenting.
														:IO_INVALID_OPERATION
										<BRZ-577>		Add jam counter of LFHS.
														:JAM_LFHS
				2003/12/22	M.Kibe		<BRZ-573>		Add order
														:MECHA_SUB_PAC_CLAMP_OFF_DSTOPPER_ON
										<BRZ-574>		Add order
														:MECHA_SUB_PAC_TRAY_ESCAPE_SAVE_POSITION
										<BRZ-584>		Add order
														:MECHA_UPPER_PREPARE_PATH_CLEAR
														Add demand code
														:MECHA_DEMAND_BACK_FEED_SEP
				2003/12/24	M.Kamimura	<BRZ-566>		Add member of division response.
														:RESP_REQUEST
				2003/12/26	M.Kamimura	<BRZ-598>		Change value of cassette denomination.
														:KIND_BILL_xxx
	012-ZY05	2004/01/06	M.Banba		<BRZ-603>		add processing
														:PROCESS_CLEAR_HIGH
										<BRZ-610>		Outside bill number-of-sheets exaggerated correspondence for payment
				2004/01/07	M.Kamimura	<BRZ-614>		Add label of update G0 information.
														:PROCESS_SIGNATURE_UPDATE
				2004/01/08	A.Kojima	<BRZ-569>		Add over current location port name
														:OCLP_XXXXX
							M.Kamimura	<BRZ-623>		Add state processing of record denomination.
														:PROCESS_RECORD_DENOMINATION
										<BRZ-626>		Add definition of command code.
														:CMD_LI,CMD_CL
				2004/01/10	M.Kibe		<BRZ-636>		add order
														:MECHA_UPPER_REPAY_BILL_CHECK
	013-ZY06	2004/01/20	M.Banba		<BRZ-668>		add response order
														:RESP_J0～JF,RESP_L0～LH
				2004/01/21	Y.Saito		<BRZ-672>		Renewal definition of treatment number.
														:BV_TREATMENT_CL
				2004/01/23	M.Banba		<BRZ-675>		add TASK_MSG
														:TASK_IO_REQUEST_SO
														add PROCESS
														:PROCESS_SO
				2004/01/24	A.Kojima	<BRZ-681>		change jam counter for using BVIN in transport processing
														:JAM_BVIN_UGAS,JAM_SSxS_BVIN,JAM_UFHS_BVIN
				2004/01/26	M.Kibe		<BRZ-676>		add mecha order
														:MECHA_UPPER_AUTO_PRESENT
										<BRZ-677>		add mecha order
														:MECHA_SUB_CA_TRANSPORT_LEVEL_SET
							M.Banba		<BRZ-690>		add DBG_LOG_***
														add type BUFFER_INFO
							Y.Saito		<BRZ-692>		Change definition of command code.
														:CMD_LI
				2004/01/27	M.Banba		<BRZ-693>		It is reshaking about a number.
														:BV_INFORMATION
				2004/01/28	M.Kamimura	<BRZ-698>		Change label.
														:PROCESS_COMPARE_DENOMINATION
	014-ZW01	2003/01/31	A.Maruyama	<BRZ-702>		delete code for A-model
				2003/02/03	M.Kibe		<BRZ-706>		add order
														:MECHA_UPPER_PRE_DRAW_BILL
														add position
														:MECHA_POSI_PAC_PRE_CHECK_LENGTH
							A.Maruyama	<BRZ-710>		add definition of statistics information
				2004/02/04	Y.Saito		<BRZ-713>		add PROCESS(under picture collection mode)
														:PROCESS_COLLECT_MODE
										<BRZ-711>		add TASK_MSG
														:TASK_BV_TIMEUP_COMMAND
							M.Kibe		<BRZ-706>		add order
														:MECHA_SUB_PAC_PRE_CHECK_LENGTH_EJECT
										<BRZ-707>		add position
														:MECHA_POSI_PRESS
				2004/02/07	M.Kamimura	<BRZ-707>		add definition of press control.
														:PRESS_xxx
							A.Kojima	<BRZ-723>		add sensor of B2-model and forgotten B1-model
														:S_PHPC,S_PLPC,S_ESPC,S_SHOC,S_SHCC,S_ILOF
				2004/02/14	A.Maruyama	<BRZ-739>		add PRG_CTRL_DATA and renumber
														:kind of program name
	015-ZW03	2003/02/23	M.Kibe		<BRZ-759>		add MECHA_ORDER(Cassette near end correspondence)
														:MECHA_CA_AFTER_STACK
				2004/02/24	M.Kamimura	<BRZ-765>		Change size.
														:BUFFER_INFO
				2004/02/26	M.Kibe		<BRZ-759>		add MECHA_DEMAND_CODE
														:MECHA_DEMAND_DOWN_NEAR_END_STAGE
				2004/02/27	M.Kibe		<BRZ-775>		add position
														:MECHA_POSI_SEP_STAGE_TOP_OFF
				2004/02/27	M.Kibe		<BRZ-778>		add MECHA_ORDER
														:MECHA_SUB_SEP_JOIN_FEED
				2004/02/27	M.Kibe		<BRZ-782>		add MECHA_ORDER
														:MECHA_SUB_PAC_TRAY_MOVE_RELEASE_POSITION
				2004/03/01	M.Kamimura	<BRZ-773>		add member of EXT_MECHA_PLACE.
														:EXT_MECHA_BV
	016-ZW04	2003/03/04	M.Kibe		<BRZ-795>		add MECHA_ORDER(Cassette near end correspondence)
														:MECHA_SUB_PAC_CHECK_CLAMP
				2004/03/08	M.Kamimura	<BRZ-802>		add state processing of path check.
														delete state processing of path check.
														:PROCESS_CHECK_PATH
										<BRZ-806>		add label of MECHA_PLACE.
														:MECHA_BV
				2004/03/08	M.Kibe		<BRZ-805>		add enum
														:MECHA_BILL_POSITION
														change	MECHA_INFO(resarve->bill_dir)
				2004/03/16	M.Kibe		<BRZ-832>		add MECHA_DEMAND_CODE
														:MECHA_DEMAND_COMPULSIVE_PRE_DRAW_BILL
							M.Kamimura	<BRZ-831>		add state processing of log deterrence.
														:PROCESS_LOG_DETERRENCE
							M.Kibe		<BRZ-834>		add MECHA_ORDER
														:MECHA_DEPRESS
														add MECHA_DEMAND_CODE
														:MECHA_DEMAND_DOWN_DEPRESS_STAGE
							Y.Saito		<BRZ-835>		Add details of J0 data.
														:STT_J0_SNS_xxxx
							M.Kibe		<BRZ-828>		add enum(ENCODER_STATUS)
														:ENCODER_TRAY_xxxx
														:ENCODER_BELT_xxxx
				2004/03/17	M.Kamimura	<BRZ-841>		Add member of read log data request.
														:ERR_R_xxx
														:ERR_TBL
							M.Kibe		<BRZ-842>		add MECHA_ORDER
														:MECHA_SUB_PAC_CARRIER_POSITION_PRE_RELEASE
														:MECHA_SUB_ESC_DOWN_RELEASE
				2004/03/18	M.Kibe		<BRZ-843>		add MECHA_ORDER
														:MECHA_SUB_PAC_CARRIER_MOVE
							A.Maruyama	<BRZ-841>		add member of log data kind
														:DBG_LOG_KIND_ANALYSIS
							M.Kibe		<BRZ-834>		add MECHA_ORDER
														:MECHA_POSI_DEPRESS
				2004/03/20	M.Kibe		<BRZ-828>		change enum
				2004/03/22	M.Kibe		<BRZ-858>		add position
														:MECHA_POSI_PAC_TRAY_PRE_CHECK_LENGTH
				2004/03/25	M.Kibe		<BRZ-871>		add position
														:MECHA_POSI_PAC_TRAY_PDPC_PRECHECKLENGTH
														:MECHA_POSI_PAC_TRAY_PRECHECKLENGTH_CHECKLENGTH
				2004/03/27	M.Kamimura	<BRZ-877>		add member of MECHA_ORDER.
														:MECHA_MORE_PRESS
				2004/03/28	A.Maruyama	<BRZ-880>		add define of group for TASK_STOP_REQUEST
	017-ZW06	2004/04/05	M.Kamimura	<BRZ-895>		add member of extra mecha place type.
														:EXT_MECHA_BEFORE_BV
														:EXT_MECHA_UNDER_REJECT
				2004/04/05	M.Kamimura	<BRZ-899>		add state processing of shutter move.
														:PROCESS_SHT_MOVE
				2004/04/06	M.Kibe		<BRZ-905>		add order
														:MECHA_SUB_SEP_TAKE_IN
	018-ZV01	2004/04/09	M.Kamimura	<BRZ-911>		add sensor of B3-model.
														:S_ETLS,S_ETRS,LETRS
										<BRZ-912>		add member of extra mecha place type.
														:EXT_MECHA_TOP_TRANSPORT
														:S_ETLC
										<BRZ-919>		add label of INT_END_FACTOR.
														:IEF_TROUBLE_NOTE
	019-ZV03	2004/04/14	A.Maruyama	<BRZ-920>		add member of extra mecha place type.
														:EXT_MECHA_INTERLOCK
										<BRZ-922>		add member of ERR_TBL & ERROR_INFORMATION
							Y.Saito						Movement definition.( l_resp.h -> typedef.h )
														:END_INFO_END_xxxx
	020-ZV04	2004/04/20	M.Kamimura	<BRZ-942>		change label of process.( RECORD_DENOMINATION -> ACCEPT )
														:PROCESS_ACCEPT
	021-ZV05	2004/04/26	M.Kamimura	<BRZ-961>		add label of add discharge.
														:IO_ADD_DISCHARGE
				2004/04/26	M.Kibe		<BRZ-962>		add order
														:MECHA_UPPER_MORE_DISCHARGE
				2004/04/27	A.Maruyama	<BRZ-970>		add place in error location
														( ERR_P_UPPER_PCB / ERR_P_LOWER_PCB )
							M.Kamimura	<BRZ-969>		add state process.
														:PROCESS_RESTORATION_MOVE
				2004/04/28	Y.Saito		<BRZ-986>		add BV_ORDER.
														:BV_CLEAR_FEATURE_IMAGE
				2004/04/30	A.Kojima	<BRZ-979>		add packet for bill trailing
														:PKT_BILL_TRAILING add
														change and add label of jam counter
														:JAM_SSxS_BVIN -> JAM_SSxS_SDIS
														:JAM_SDIS_BVIN, JAM_SDIS add
							M.Kamimura	<BRZ-982>		add member of EXT_MECHA_PLACE.
														:EXT_MECHA_CA_ALL
										<BRZ-985>		add member of RESP_REQUEST.
														:RESP_REQUEST
	022-ZV07	2004/05/03	M.Kibe		<BRZ-978>		add order
														:MECHA_SUB_SEP_PUSHER_FEW_DOWN
														add position
														:MECHA_POSI_TOP_FEW_DOWN
							M.Kamimura	<BRZ-989>		Bit of Int end factor is unified.( Adjust / Compress )
														:INT_END_FACTOR
	023-ZV08	2004/05/11	M.Kamimura	<BRZ-1005>		add label of INT_END_FACTOR.
														:IEF_HALF_NOTE
							M.Kibe		<BRZ-1004>		add order
														:MECHA_SUB_PAC_DSTOPPER_ESCAPE
	024-ZU03	2004/05/20	Y.Saito		<BRZ-1029>		add process of STATE_PROCESS.
														:PROCESS_RAS_COLLECT_DATA
							M.Kamimura	<BRZ-1029>		add mecha order.
														:MECHA_UPPER_TAKE_IN
				2004/05/22	M.Kibe		<BRZ-1038>		add mecha order
														:MECHA_UPPER_CHECK_REMAIN_PAC
				2004/05/24	Y.Saito		<BRZ-1042>		add BV_ORDER.
														:BV_CHANGE_CONNECTION_MODE
				2004/05/25	M.Kamimura	<BRZ-1050>		add label of INT_END_FACTOR.
														:IEF_CURRENT_STOP
				2004/05/31	M.Kamimura	<BRZ-1079>		add label of J4 information.(Not recognized note kind)
														:STT_J4_COUNTER_xxx
	025-ZU08	2004/06/07	M.Kamimura	<BRZ-1092>		add label of information J4.(Invalid insertion)
														:STT_J4_FACTOR_INVALID_INSERTION
														:STT_J4_FACTOR_xxx
										<BRZ-1093>		add label of information J4.(CL)
														:STT_J4_TRANSACTION_COLLECT
				2004/06/09	A.Maruyama	<BRZ-1100>		add label of BUNCH in MECHA_PLACE for mechanical error location
														:MECHA_PLACE
	026-ZT02	2004/06/11	A.Kojima	<BRZ-1108>		add label for A/D converter
														:ADC_CHx
				2004/06/12	A.Maruyama	<BRZ-1110>		add mecha order
														:TASK_MECHA_WAIT_ALMIGHTY
				2004/06/14	M.Kamimura	<BRZ-1111>		add label of damaged cassette.
														:DENOMINATION_CA_DAMAGED
				2004/06/15	A.Kojima	<BRZ-1120>		add full stop in INT_END_LEVEL2_ERR
														:INT_END_LEVEL2_ERR
	027-ZT06	2004/06/24	M.Kibe		<BRZ-1130>		add order
														:MECHA_SUB_CA_STAGE_DOWN_STACK_2ND
														:MECHA_SUB_CA_STAGE_DOWN_STACK_3RD
				2004/06/29	M.Kibe		<BRZ-1133>		add order
														:MECHA_SUB_PAC_BILL_TAKE_IN
														:MECHA_SUB_SEP_TAKE_IN_DOWN
				2004/06/30	A.Kojima	<BRZ-1140>		add error location
														:ERR_P_OC_PAC,ERR_P_OC_SEP,ERR_P_OC_ESC
														 ERR_P_OC_UPPER_BASE,ERR_P_OC_LOWER_TRANSPORT,
														 ERR_P_OC_LOWER_BASE add
	028-ZT09	2004/07/08	M.Kamimura	<BRZ-1145>		add label of send factor.
														:SEND_FACTOR_MEDIA_EXIST
														:SEND_FACTOR_MEDIA_NOT_EXIST
	029-ZT12	2004/07/21	M.Kamimura	<BRZ-1176>		add state process.
														:PROCESS_UNUSUAL_MASK
	030-AA02	2004/07/26	A.Kojima	<BRZ-1180>		add state process.
														:PROCESS_LOG_SAVE_FILE
	031-AA03	2004/07/30	M.Kibe		<BRZ-1185>		add state process.
														:MECHA_SUB_PAC_CLAMP_PRESS_DISCHAGE
	032-AA04	2004/08/05	A.Kojima	<BRZ-1189>		add PDAC sensor
														:S_PDAC add
				2004/08/10	M.Kibe		<BRZ-1191>		add label of TASK_MSG
														:TASK_MECHA_ABORT_DISABLE
				2004/08/12	M.Kibe		<BRZ-1191>		change label of TASK_MSG
														:(TASK_MECHA_ABORT_DISABLE->TASK_MECHA_REQUEST_ABORT_MOVE)
				2004/08/13	Y.Saito		<BRZ-1207>		add label of TASK_MSG
														:TASK_BV_RECEPTION_VD_ERROR
				2004/08/16	M.Kibe		<BRZ-1183>		add label of EXT_MECHA_PLACE
														:EXT_MECHA_CAx_FEED
	033-AA05	2004/08/26	M.Kibe		<BRZ-1224>		add MECHA_ORDER(PDAC correspondence
														:MECHA_UPPER_RELEASE_EJECT
							M.Kamimura	<BRZ-1224>		add kind of J4 factor.(Fail to move to Separator)
														:STT_J4_FACTOR_FAIL_MOVE
				2004/09/02	M.Kamimura	<BRZ-1229>		add definite timer of medium detection.
														:C_TIME_CHECK_MEDIA
	034-AA06	2004/09/14	M.Kamimura	<BRZ-1246>		add label of INT_END_FACTOR.
														:IEF_FOREIGN_OBJECT
				2004/09/15	M.Kibe		<BRZ-1250>		add MECHA_ORDER
														:MECHA_SUB_PAC_JOIN_BUNCH
	035-AA07	2004/09/21	M.Kibe		<BRZ-1259>		add MECHA_ORDER
														:MECHA_SUB_PAC_PSXS_ON_DRAW_BILL
	036-AA08	2004/09/24	M.Kibe		<BRZ-1263>		add MECHA_ORDER
														:MECHA_SUB_ESC_STOPPER_CHECK
	037-AA09	2004/09/29	M.Kamimura	<BRZ-1275>		change member.(Sensor information -> Encryption)
														:RESP_REQUEST
				2004/10/01	M.Banba		<BRZ-1278>		add Cassette Model
				2004/10/04	M.Kibe		<BRZ-1280>		add MECHA_ORDER
														:MECHA_UPPER_PRE_DRAW_BILL_SC
														:MECHA_UPPER_DRAW_BILL_SC
	038-AA10	2004/10/07	M.Kibe		<BRZ-1290>		add MECHA_ORDER
														:MECHA_UPPER_ESCAPE
							M.Kamimura	<BRZ-1290>		add command code.
														:CMD_ES
				2004/10/12	A.Kojima	<BRZ-1303>		add debug message for pick test
														:PRINT_PICK add
	039-AA11	2004/10/14	M.Kibe		<BRZ-1308>		RAS-4x correspondence(add MECHA_ORDER)
														:MECHA_UPPER_INSERT_SEP
														:MECHA_UPPER_ESCAPE_CLAMP
														:MECHA_UPPER_PRESS_CLAMP
														:MECHA_UPPER_PRE_RELEASE_CARRIER
														:MECHA_UPPER_RELEASE_ESC
				2004/10/15	M.Kibe		<BRZ-1308>		RAS-4x correspondence(change MECHA_ORDER)
														:MECHA_UPPER_INSERT_SEP->MECHA_UPPER_PREPARE_FEED_SEP
				2004/10/18	M.Kamimura	<BRZ-1308>		Add MECHA_ORDER.(For RAS-4x)
														:MECHA_UPPER_STACK_ESC
	040-AA12	2004/10/22	M.Banba		<BRZ-1321>		Statistics information (J5) item addition
														add SKEW_NAME
														:SKEW_BVIN
				2004/10/25	M.Kibe		<BRZ-1330>		Pusher downward poor prevention correspondence
														Add MECHA_ORDER
														:MECHA_SUB_PAC_BELT_BACKWARD
	041-AA13	2004/11/01	M.Banba		<BRZ-1339>		Add MECHA_ORDER
														:MECHA_UPPER_BEFORE_SO
	042-AA14	2004/11/18	A.Kojima	<BRZ-1356>		Add SKEW_NAME_END_CTRL
														:SKEW_NAME_END_CTRL
	043-AA16	2004/12/01	M.Kibe		<BRZ-1365>		Add MECHA_ORDER
														:MECHA_UPPER_BEFORE_MR
				2004/12/16	M.Kibe		<BRZ-1365>		Deletion MECHA_ORDER
														:MECHA_UPPER_BEFORE_MR
				2004/12/22	M.Banba		<BRZ-1376>		The number of times of phase detection is added.(L3,LC-LF)
														:STT_xx_FEED_PHASE
	044-AA18	2005/03/03	A.Kojima	<BRZ-1393>		add PLACE_NO
														:P_NOTHING
				2005/03/07	M.Kamimura	<BRZ-1395>		The end factor of BV abnormal device is added.
														:IEF_BV_UNIT_NG
							A.Maruyama	<BRZ-1397>		Add information of 'read log request'
														:ERROR_INFORMATION
	045-AA19	2005/03/18	M.Kibe		<BRZ-1405>		Add MECHA_ORDER
														:MECHA_UPPER_LAST_DISCHARGE
										<BRZ-1406>		Add MECHA_ORDER
														:MECHA_UPPER_PREPARE_IDLE
				2005/03/22	M.Kamimura	<BRZ-1405>		Add control of additional pushing out.
														:IO_REQUEST
				2005/03/31	A.Kojima	<BRZ-1419>		add debug message for skew data of note
														:PRINT_SKEW add
	046-AA21	2005/06/09	M.Kamimura	<BRZ-1431>		add command code.
														:CMD_LN
				2005/06/14	A.Kojima	<BRZ-1430>		add skew sensor name
														:SKEW_SSxS_R
	047-AA22	2005/08/29	M.Kamimura	<BRZ-1451>		add label of L8 information.
														:STT_RJT_xxx
	048-AA23	2005/10/03	M.Kibe		<BRZ-1453>		Add MECHA_ORDER
														:MECHA_SUB_CA_STAGE_UP_PRESS_SET
	049-AA24	2005/10/07	M.Kibe		<BRZ-1457>		Add MECHA_ORDER
														:MECHA_SUB_PAC_TRAY_ESCAPE_DERIVARY_POSITION
	050-AA25	2006/01/11	A.Kojima	<BRZ-1461>		add member of PKT_BILL_TRAILING
														:PKT_BILL_TRAILING
	051-AA36	2006/10/23	M.Kibe		<BRZ-1497>		Add MECHA_ORDER
														:MECHA_RECOVERY_ADJUST_FEEDING
	052-AA40	2007/01/16	M.Kibe		<BRZ-1511>		Making to option for Reservoir stage diving crowding.
														- add	DATA_RSV_CTRL_SETUP	
	053-AA41	2007/01/24	M.Kibe		<BRZ-1512>		for cassette storage capacity improvement FW.
														- add enum(cassette status)
				2007/01/31	M.Kibe		<BRZ-1512>		for cassette storage capacity improvement FW.
														- add enum(cassette status)
														:CASSETTE_STATUS_FULL_JAM
	054-AA43	2007/02/27	A.Kojima	<BRZ-1520>		support for cheque
														:CMD_CI,BV_READ_CHEQUE_IMAGE add
	055-AA44	2007/03/23	M.Kibe		<BRZ-1522>		for D-stopper thrust NG
														Add MECHA_ORDER
														:MECHA_SUB_PAC_MOVE_3rd
														:MECHA_SUB_PAC_CLAMP_OFF_DSTOPPER_ON_3rd
														:MECHA_SUB_PAC_DSTOPPER_THRUST_CHECK
														:MECHA_SUB_PAC_DSTOPPER_THRUST_CHECK_3rd
														:MECHA_SUB_PAC_JOIN_BUNCH_3rd
														:MECHA_SUB_PAC_BILL_TAKE_IN_3rd
														:MECHA_SUB_SEP_STAGE_FEW_DOWN
				2007/04/09	A.Maruyama	<BRZ-1527>		Add MECHA_ORDER for detached processing
														:MECHA_ADJUST_FEEDING_DETACHED
														:MECHA_CA_AFTER_STACK_DETACHED
	056-AA46	2007/05/15	M.Kibe		<BRZ-1533>		The note is prevented from dashing out from the cassette. 
														Add MECHA_ORDER
														:MECHA_CA_BILL_REMOVAL
	057-AA48	2007/05/24	A.Maruyama	<BRZ-1535>		support for pre-deposit
														:CMD_PD,CMD_BE add
														:STT_J4_TRANSACTION_BACK_ESCROW
				2007/06/07	A.Kojima	<BRZ-1530>		improve the data transfer speed
														-change for D-Level frame size change
														:DATA_LINE_NML_FRAME,DATA_LINE_BIG_FRAME,
														 MAX_SIZE_FRAME_SEND,MAX_SIZE_MESSAGE_DATA_SEND add
														:FRAME_FORM_SEND add
				2007/06/11	M.Kibe		<BRZ-1531>		for 2000pps
														Add MECHA_ORDER
														:MECHA_SUB_PAC_TRAY_MOVE_SAVE_POSITION_HIGHSPEED
														:MECHA_SUB_PAC_TRAY_MOVE_RELEASE_POSITION_HIGHSPEED
				2007/06/12	M.Kibe		<BRZ-1531>		for 2000pps
														:MECHA_SUB_PAC_CARRIER_HOME_CLAMP_OFF
				2007/06/22	M.Kibe		<BRZ-1540>		for transportation that doesn't use Hook
														:MECHA_UPPER_DRAW_BILL_NON_HOOK
														:MECHA_SUB_PAC_MOVE_NON_HOOK
				2007/06/22	M.Kibe		<BRZ-1540>		for transportation that doesn't use Hook
														:MECHA_SUB_PAC_REMAIN_CHECK_BELT_BACKWARD
														add label of L2 information.
														:STT_PAC_PDSS_NOT_BLOCK
														:STT_PAC_PDSS_NOT_CLEAR
														:STT_PAC_PDSS_BLOCK_AFTER_CLAMP
														:STT_PAC_RETRY_BELT_TRANSPORT
				2007/07/11	M.Kibe		<BRZ-1540>		for transportation that doesn't use Hook
														:MECHA_SUB_PAC_DRAW_BILL_NON_HOOK
														:MECHA_SUB_PAC_MOVE_NON_HOOK_3rd
	058-AA49	2007/07/19	A.Maruyama	<BRZ-1543>		Shutter close when the error ended was supported
														add MECHA_ORDER
														:MECHA_SHT_CLOSE_COMPULSORY
	059-AA54	2008/01/25	A.Maruyama	<BRZ-1557>		add define for extended cassette
														:CASSETTE_EXTENDED/CASSETTE_NOT_EXTENDED

COMMENT END
***/
/****************************************************************************/
/*																			*/
/*	defines																	*/
/*																			*/
/****************************************************************************/
/*--------------------------------------------------------------------------*/
/*																			*/
/*	Unsigned Define															*/
/*																			*/
/*--------------------------------------------------------------------------*/
typedef	unsigned char		uchar;
typedef	unsigned short int 	ushort;
typedef unsigned long int 	ulong;
typedef	unsigned int		uint;

typedef	uchar	UCHAR;
typedef	ushort 	USHORT;
typedef ulong 	ULONG;
typedef	uint	UINT;
/*--------------------------------------------------------------------------*/
/*																			*/
/*	Constant Define															*/
/*																			*/
/*--------------------------------------------------------------------------*/
#define		TRUE	(1)
#define		FALSE	(0)
typedef		ULONG	BOOL;

#define		OFF		0
#define		ON		1
typedef		UCHAR	ONOFF;

#define 	NULL   (0)
#define 	EMPTY  (int)0
#define 	NOWAIT (int)0
#define 	WAIT   (int)1

#define		TICK				1			/* Timer Cycle					*/
#define		C_TIME_HURRY		1			/* Minimum value				*/
#define		C_TIME_CHECK_MEDIA	30			/* Timer of medium detection	*/
#define		CNTR_CLR			0			/* Counter Initialize Data		*/
#define		PTR_CLR				0			/* Pointer Initialize Data		*/

#define		BIT0	(0x01)
#define		BIT1	(0x02)
#define		BIT2	(0x04)
#define		BIT3	(0x08)
#define		BIT4	(0x10)
#define		BIT5	(0x20)
#define		BIT6	(0x40)
#define		BIT7	(0x80)

#define		BIT8	(0x0100)
#define		BIT9	(0x0200)
#define		BIT10	(0x0400)
#define		BIT11	(0x0800)
#define		BIT12	(0x1000)
#define		BIT13	(0x2000)
#define		BIT14	(0x4000)
#define		BIT15	(0x8000)

#define		BIT16	(0x010000)
#define		BIT17	(0x020000)
#define		BIT18	(0x040000)
#define		BIT19	(0x080000)
#define		BIT20	(0x100000)
#define		BIT21	(0x200000)
#define		BIT22	(0x400000)
#define		BIT23	(0x800000)

#define		BIT24	(0x01000000)
#define		BIT25	(0x02000000)
#define		BIT26	(0x04000000)
#define		BIT27	(0x08000000)
#define		BIT28	(0x10000000)
#define		BIT29	(0x20000000)
#define		BIT30	(0x40000000)
#define		BIT31	(0x80000000)
/*--------------------------------------------------------------------------*/
/*	Bit information on note discrimination result 							*/
/*--------------------------------------------------------------------------*/
	/*----------------------------------------------------------------------*/
	/*	Note Generation								 						*/
	/*	Rev.(ZZ05:BRZ-193)	add NOTE_GENERATION_OLD4 -> JUDGMENT			*/
	/*----------------------------------------------------------------------*/
#define		NOTE_GENERATION_NEW			0
#define		NOTE_GENERATION_OLD1		BIT4
#define		NOTE_GENERATION_OLD2		BIT5
#define		NOTE_GENERATION_OLD3		( BIT4 | BIT5 )
#define		NOTE_GENERATION_OLD4		BIT6
#define		NOTE_GENERATION_OLD5		( BIT4 | BIT6 )
#define		NOTE_GENERATION_OLD6		( BIT5 | BIT6 )
#define		NOTE_GENERATION_OLD7		( BIT4 | BIT5 | BIT6 )
#define		NOTE_GENERATION_JUDGMENT	( BIT4 | BIT5 | BIT6 )
	/*----------------------------------------------------------------------*/
	/*	Money kind presence													*/
	/*----------------------------------------------------------------------*/
#define		NOTE_KIND_MANAGEMENT 		BIT3
#define		NOTE_KIND_UNCERTAINTY 		BIT2
	/*----------------------------------------------------------------------*/
	/*	Note Direction														*/
	/*----------------------------------------------------------------------*/
#define		NOTE_DIRECTION_A		 	0
#define		NOTE_DIRECTION_B		 	BIT0
#define		NOTE_DIRECTION_C		 	BIT1
#define		NOTE_DIRECTION_D		 	( BIT0 | BIT1 )
	/*----------------------------------------------------------------------*/
	/*	Note Truth															*/
	/*	Rev.(ZZ02:BRZ-005)	change Name ( LOSS -> DAMAGED )					*/
	/*						add NOTE_TRUTH_JUDGMENT							*/
	/*----------------------------------------------------------------------*/
#define		NOTE_TRUTH_GENUINE		 	0
#define		NOTE_TRUTH_SUSPECT		 	BIT4
#define		NOTE_TRUTH_COUNTERFEIT		BIT5
#define		NOTE_TRUTH_DAMAGED 			BIT7
#define		NOTE_TRUTH_JUDGMENT			( BIT4 | BIT5 | BIT6 | BIT7 )
	/*----------------------------------------------------------------------*/
	/*	Note Number															*/
	/*----------------------------------------------------------------------*/
#define		NOTE_NUMBERLESS				BIT3
	/*----------------------------------------------------------------------*/
	/*	Note Publication													*/
	/*	Rev.(ZZ05:BRZ-193)	add NOTE_PUBLICATION_JUDGMENT					*/
	/*----------------------------------------------------------------------*/
#define		NOTE_PUBLICATION_JUDGMENT 	( BIT0 | BIT1 | BIT2 )
	/*----------------------------------------------------------------------*/
	/*	Face value															*/
	/*----------------------------------------------------------------------*/
#define		NOTE_VALUE_1				1
#define		NOTE_VALUE_2				2
#define		NOTE_VALUE_3				5
#define		NOTE_VALUE_4				10
#define		NOTE_VALUE_5				20
#define		NOTE_VALUE_6				50
#define		NOTE_VALUE_7				100
#define		NOTE_VALUE_8				200
#define		NOTE_VALUE_9				500
#define		NOTE_VALUE_10				1000
#define		NOTE_VALUE_11				2000
#define		NOTE_VALUE_12				5000
#define		NOTE_VALUE_13				10000
#define		NOTE_VALUE_14				20000
#define		NOTE_VALUE_15				50000
#define		NOTE_VALUE_16				100000
#define		NOTE_VALUE_17				200000
#define		NOTE_VALUE_18				500000
#define		NOTE_VALUE_19				1000000
#define		NOTE_VALUE_20				2000000
#define		NOTE_VALUE_21				5000000
#define		NOTE_VALUE_22				10000000
	/*----------------------------------------------------------------------*/
	/*	Denomination kind of cassette										*/
	/*	Rev.(ZZ05:BRZ-193)	It moves from l_cmd.h.(delete DENOMINATION_MIX)	*/
	/*	Rev.(ZT02:BRZ-1111)	Add definition of damaged cassette.				*/
	/*----------------------------------------------------------------------*/
enum
{
	DENOMINATION_CA_NOT_USE		= 0,
	DENOMINATION_CA_SUSPECTED	= 1,
	DENOMINATION_CA_TEMPORARY	= 2,
	DENOMINATION_CA_DAMAGED		= 3
};
	/*----------------------------------------------------------------------*/
	/*	Cassette denomination type	(Generation)							*/
	/*	Rev.(ZY02:BRZ-461)	add definition of cassette type.				*/
	/*----------------------------------------------------------------------*/
enum
{
	CA_DENOMI_NONE				= 0,
	CA_DENOMI_SINGLE			= 1,
	CA_DENOMI_GENERATE			= 2,
	CA_DENOMI_MIX				= 3
};
	/*----------------------------------------------------------------------*/
	/*	Cassette hard denomination				 							*/
	/*	Rev.(ZY04:BRZ-531)	add definition of cassette hard.				*/
	/*----------------------------------------------------------------------*/
enum
{
	RAS_HARD_DENOMI_NONE		= 0x00,	/*	Not use							*/
	RAS_HARD_DENOMI_5			= 0x01,	/*	5 Euro							*/
	RAS_HARD_DENOMI_10			= 0x02,	/*	10 Euro							*/
	RAS_HARD_DENOMI_20			= 0x03,	/*	20 Euro							*/
	RAS_HARD_DENOMI_50			= 0x04,	/*	50 Euro							*/
	RAS_HARD_DENOMI_100			= 0x05,	/*	100 Euro						*/
	RAS_HARD_DENOMI_200			= 0x06,	/*	200 Euro						*/
	RAS_HARD_DENOMI_500			= 0x07,	/*	500 Euro						*/
	RAS_HARD_DENOMI_SUSPECT		= 0x0D,	/*	Suspect							*/
	RAS_HARD_DENOMI_TEMPORARY	= 0x0E,	/*	Temporary						*/
	RAS_HARD_DENOMI_MIX			= 0x0F	/*	Denomination mix				*/
};
	/*----------------------------------------------------------------------*/
	/*	Command Code														*/
	/*	Rev.(ZZ04:BRZ-129)	It moves from l_cmd.h.							*/
	/*	Rev.(ZZ04:BRZ-178)	add command code.(EK,CP,LG,PC,RS)				*/
	/*	Rev.(ZY03:BRZ-517)	add command code.(BC)							*/
	/*	Rev.(ZY04:BRZ-567)	add / delete command code.(D-Level draft 7)		*/
	/*	Rev.(ZY05:BRZ-626)	add command code.(LI,CL)						*/
	/*	Rev.(ZY06:BRZ-692)	change command code.(LI)						*/
	/*	Rev.(AA10:BRZ-1290)	add command code.(ES)							*/
	/*	Rev.(AA21:BRZ-1431)	add command code.(LN)							*/
	/*	Rev.(AA43:BRZ-1520)	add command code.(CI)							*/
	/*	Rev.(AA48:BRZ-1535)	add command code.(PD,BE)						*/
	/*----------------------------------------------------------------------*/
enum
{
	CMD_RT = 0x5254,
	CMD_HT = 0x4854,
	CMD_ST = 0x5354,
	CMD_LD = 0x4C44,
	CMD_LE = 0x4C45,
	CMD_EK = 0x454B,
	CMD_FP = 0x4650,
	CMD_CP = 0x4350,
	CMD_ID = 0x4944,
	CMD_LN = 0x4C4E,
	CMD_CR = 0x4352,
	CMD_SI = 0x5349,
	CMD_IC = 0x4943,
	CMD_LI = 0x4C49,
	CMD_SB = 0x5342,
	CMD_VR = 0x5652,
	CMD_SG = 0x5347,
	CMD_SN = 0x534E,
	CMD_PI = 0x5049,
	CMD_CI = 0x4349,
	CMD_LG = 0x4C47,
	CMD_SY = 0x5359,
	CMD_IV = 0x4956,
	CMD_DP = 0x4450,
	CMD_BK = 0x424B,
	CMD_WC = 0x5743,
	CMD_PP = 0x5050,
	CMD_TO = 0x544F,
	CMD_SO = 0x534F,
	CMD_SC = 0x5343,
	CMD_UC = 0x5543,
	CMD_BC = 0x4243,
	CMD_CL = 0x434C,
	CMD_SK = 0x534B,
	CMD_RJ = 0x524A,
	CMD_PC = 0x5043,
	CMD_MR = 0x4D52,
	CMD_MJ = 0x4D4A,
	CMD_JA = 0x4A41,
	CMD_AP = 0x4150,
	CMD_RS = 0x5253,
	CMD_DB = 0x4442,
	CMD_ES = 0x4553,
	CMD_PD = 0x5044,
	CMD_BE = 0x4245
};
	/*----------------------------------------------------------------------*/
	/*	Jam Place															*/
	/*	Rev.(ZZ03:BRZ-021)	for A3 Mecha	(UTGS->UGAS)(UTFS->UGDS)		*/
	/*	Rev.(ZZ05:BRZ-195)	add label		(No.35->38)						*/
	/*	Rev.(ZZ05:BRZ-279)	add label		(JAM_BVIN,JAM_BVOUT)			*/
	/*	Rev.(ZY04:BRZ-577)	add label		(JAM_LFHS)						*/
	/*	Rev.(ZY06:BRZ-681)													*/
	/*	 change JAM_BVIN_BVOUT to JAM_BVIN_UGAS								*/
	/*	 change JAM_SSxS_UGAS to JAM_SSxS_BVIN								*/
	/*	 change JAM_UFHS_UGAS to JAM_UFHS_BVIN								*/
	/*	Rev.(ZV05:BRZ-979)													*/
	/*	 change JAM_SSxS_BVIN to JAM_SSxS_SDIS								*/
	/*	 add JAM_SDIS_BVIN, JAM_SDIS										*/
	/*----------------------------------------------------------------------*/
enum
{
	JAM_TOP				= 0,
	JAM_SSxS_SDIS		= 0,
	JAM_BVIN_UGAS		= 1,
	JAM_UGAS_EDxS		= 2,
	JAM_UGAS_ERxS		= 3,
	JAM_UGAS_UGDS		= 4,
	JAM_UGAS_URHS		= 5,
	JAM_UGDS_UECS		= 6,
	JAM_UGDS_UERS		= 7,
	JAM_UGDS_UEFS		= 8,
	JAM_URHS_Cx1S		= 9,
	JAM_URHS_Cx2S		= 10,
	JAM_URHS_LT3S		= 11,
	JAM_LT3S_Cx3S		= 12,
	JAM_LT3S_Cx4S		= 13,
	JAM_LT3S_UFHS		= 14,
	JAM_UFHS_BVIN		= 15,
	JAM_Cx1S_UFHS		= 16,
	JAM_Cx2S_UFHS		= 17,
	JAM_Cx3S_UFHS		= 18,
	JAM_Cx4S_UFHS		= 19,
	JAM_SSxS			= 20,
	JAM_UGAS			= 21,
	JAM_UGDS			= 22,
	JAM_EDxS			= 23,
	JAM_ERxS			= 24,
	JAM_UECS			= 25,
	JAM_UERS			= 26,
	JAM_UEFS			= 27,
	JAM_URHS			= 28,
	JAM_UFHS			= 29,
	JAM_LFHS			= 30,
	JAM_LT3S			= 31,
	JAM_Cx1S			= 32,
	JAM_Cx2S			= 33,
	JAM_Cx3S			= 34,
	JAM_Cx4S			= 35,
	JAM_Cx1S_Cx2S		= 36,
	JAM_Cx3S_Cx4S		= 37,
	JAM_Cx1S_LT3S		= 38,
	JAM_Cx2S_LT3S		= 39,
	JAM_BVIN			= 40,
	JAM_BVOUT			= 41,
	JAM_SDIS_BVIN		= 42,
	JAM_SDIS			= 43,
	JAM_END				= 44
};

	/*----------------------------------------------------------------------*/
	/*	kind of program's version											*/
	/*	Rev.(ZZ04:BRZ-167)	add these definitions							*/
	/*----------------------------------------------------------------------*/
enum{
	PRG_VER_BOOT			= 0,
	PRG_VER_MAIN			= 1,
	PRG_VER_SUB				= 2,
	PRG_VER_BV				= 3,
	PRG_VER_BV_SUB			= 4,
	PRG_VER_CONTROL_DATA	= 5,
	PRG_VER_RESERVE			= 6,
	PRG_VER_MAX				= 7
};
/*--------------------------------------------------------------------------*/
/*																			*/
/*	Actuator & Sensor Driver Define											*/
/*																			*/
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/*	Common																	*/
/*--------------------------------------------------------------------------*/
	/*----------------------------------------------------------------------*/
	/*	Direction															*/
	/*	Rev.(ZZ06:BRZ-312)													*/
	/*	 add THRUST and ESCAPE												*/
	/*----------------------------------------------------------------------*/
enum
{								/* Valid actuator							*/
	FEED		= 0,			/* BF1M,BF2M,BF3M,BF4M,SEFM,				*/
	BACK		= 1,			/* Transport DC motor						*/

	UP			= 0,			/* EESM,ERSM,SEPM,SESM,PACM,BS1M,BS2M,		*/
	DOWN		= 1,			/* BS3M,BS4M								*/

	RIGHT		= 0,			/* SEDM										*/
	LEFT		= 1,			/* 											*/

	FORWARD		= 0,			/* ESCM,PABM,PATM							*/
	BACKWARD	= 1,			/* 											*/

	THRUST		= 0,			/* PAMG,PDMG,PHMG,SRMG,ESMG					*/
	ESCAPE		= 1,			/* 											*/

	CLOSE		= 0,			/* SHTM,C1MG,C2MG,C3MG,C4MG,UAMG,EBMG,UCMG,	*/
	OPEN		= 1,			/* UDMG,UEMG,L1MG,L2MG,L3MG,L4MG			*/

	DIR_END		= 2,

	DIR_NONE	= 3				/* Stop state ( When get direction )		*/
};
	/*----------------------------------------------------------------------*/
	/*	Speed																*/
	/*----------------------------------------------------------------------*/
enum
{
	LOW,
	MIDDLE,
	HIGH,
	MOREHIGH,
	SPEED_END,
	SPEED_NONE							/* Stop state ( When get speed )	*/
};
	/*----------------------------------------------------------------------*/
	/*	Stop Method ( Excitation method when the motor stopped )			*/
	/*----------------------------------------------------------------------*/
enum
{
	FREE,							/* Free stop							*/
	LOCK,							/* Lock stop							*/
	SLOCK,							/* Strong lock stop						*/
	STOP_END,
	ROTATING						/* Rotating ( When get phase status )	*/
};
/*--------------------------------------------------------------------------*/
/*	Stepping Motor															*/
/*--------------------------------------------------------------------------*/
	/*----------------------------------------------------------------------*/
	/*	Name																*/
	/*----------------------------------------------------------------------*/
enum
{
	SM_NAME_TOP	= 0,
	PABM		= 0,
	PATM		= 1,
	PACM		= 2,
	SEPM		= 3,
	SESM		= 4,
	SEDM		= 5,
	ESCM		= 6,
	ERSM		= 7,
	EESM		= 8,
	BS1M		= 9,
	BS2M		= 10,
	BS3M		= 11,
	BS4M		= 12,
	SHTM		= 13,
	SEFM		= 14,
	BF1M		= 15,
	BF2M		= 16,
	BF3M		= 17,
	BF4M		= 18,
	SM_NUM		= 19,					/* Number of stepping motor			*/
	ALLM		= 19,					/* All stepping motor ( stop only )	*/
	SM_NAME_END = 20
};
	/*----------------------------------------------------------------------*/
	/*	Number of Steps														*/
	/*----------------------------------------------------------------------*/
#define	INFINITY	0								/* Rotates to infinity.	*/
	/*----------------------------------------------------------------------*/
	/*	Excitaion Method													*/
	/*----------------------------------------------------------------------*/
#define	EXCIT_BIT_12	BIT1
#define	EXCIT_BIT_PD	BIT0
enum
{
	EXCIT2,						/* 2 phase excitation						*/
	EXCIT2PD,					/* 2 phase excitation ( power down )		*/
	EXCIT12,					/* 1 - 2 phase excitation					*/
	EXCIT12PD,					/* 1 - 2 phase excitation ( power down )	*/
	EXCIT_END
};
	/*----------------------------------------------------------------------*/
	/*	Status																*/
	/*----------------------------------------------------------------------*/
enum
{
	SM_STS_STOP,
	SM_STS_START_LOCK,
	SM_STS_SLEW_UP,
	SM_STS_REGULAR,
	SM_STS_SLEW_DOWN,
	SM_STS_END_LOCK,
	SM_STS_END
};
/*--------------------------------------------------------------------------*/
/*	Transport DC Motor														*/
/*--------------------------------------------------------------------------*/
	/*----------------------------------------------------------------------*/
	/*	Stop Mode															*/
	/*----------------------------------------------------------------------*/
enum
{
	TDCM_STOP_NORMAL,
	TDCM_STOP_FORCE,
	TDCM_STOP_IRQ,
	TDCM_STOP_END
};
	/*----------------------------------------------------------------------*/
	/*	Status																*/
	/*----------------------------------------------------------------------*/
enum
{
	TDCM_STS_STOP,
	TDCM_STS_ROTATING,
	TDCM_STS_END
};
/*--------------------------------------------------------------------------*/
/*	Linear Solenoid															*/
/*--------------------------------------------------------------------------*/
	/*----------------------------------------------------------------------*/
	/*	Name																*/
	/*	Rev.(ZZ06:BRZ-295)													*/
	/*	 Add PHMG															*/
	/*	Rev.(ZY01:BRZ-406)													*/
	/*	 Add SRMG															*/
	/*----------------------------------------------------------------------*/
enum
{
	LSOL_NAME_TOP	= 0,
	PAMG			= 0,
	PDMG			= 1,
	PHMG			= 2,
	C1MG			= 3,
	C2MG			= 4,
	C3MG			= 5,
	C4MG			= 6,
	SRMG			= 7,
	LSOL_NUM		= 8,		/* Number of linear solenoid 				*/
	LSOL_ALL		= 8,		/* All linear solenoid ( on / off only )	*/
	LSOL_NAME_END	= 9
};
/*--------------------------------------------------------------------------*/
/*	Rotary Solenoid															*/
/*--------------------------------------------------------------------------*/
	/*----------------------------------------------------------------------*/
	/*	Name																*/
	/*	Rev.(ZZ06:BRZ-295)													*/
	/*	 Delete PHMG														*/
	/*	Rev.(ZY01:BRZ-406)													*/
	/*	 Add SRMG,ESMG														*/
	/*----------------------------------------------------------------------*/
enum
{
	RSOL_NAME_TOP	= 0,
	UAMG			= 0,
	EBMG			= 1,
	UCMG			= 2,
	UDMG			= 3,
	UEMG			= 4,
	L1MG			= 5,
	L2MG			= 6,
	L3MG			= 7,
	L4MG			= 8,
	ESMG			= 9,
	RSOL_NUM		= 10,					/* Number of rotary solenoid	*/
	RSOL_NAME_END	= 10
};
/*--------------------------------------------------------------------------*/
/*	Media Indicator															*/
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/*	Sensor ( Level write )													*/
/*--------------------------------------------------------------------------*/
	/*----------------------------------------------------------------------*/
	/*	Name																*/
	/*	Rev.(ZZ06:BRZ-295)													*/
	/*	 Add PDSS															*/
	/*	Rev.(ZY01:BRZ-406)													*/
	/*	 Add LFHS															*/
	/*	Rev.(ZV01:BRZ-911)													*/
	/*	 Add ETRS															*/
	/*----------------------------------------------------------------------*/
enum
{
	LSNS_NAME_TOP	= 0,
	LPS1S			= 0,
	LPS2S			= 1,
	LPS3S			= 2,
	LPS4S			= 3,
	LPTCS			= 4,
	LPASS			= 5,
	LPDSS			= 6,
	LSDIS			= 7,
	LSDOS			= 8,
	LSSLS			= 9,
	LSSRS			= 10,
	LSSOS			= 11,
	LEECS			= 12,
	LETLS			= 13,
	LEELS			= 14,
	LEERS			= 15,
	LEDLS			= 16,
	LEDRS			= 17,
	LERLS			= 18,
	LERRS			= 19,
	LUGAS			= 20,
	LURHS			= 21,
	LUFHS			= 22,
	LUGDS			= 23,
	LUECS			= 24,
	LUEFS			= 25,
	LUERS			= 26,
	LLT3S			= 27,
	LLFHS			= 28,
	LCL1S			= 29,
	LCR1S			= 30,
	LCL2S			= 31,
	LCR2S			= 32,
	LCL3S			= 33,
	LCR3S			= 34,
	LCL4S			= 35,
	LCR4S			= 36,
	LCT1S			= 37,
	LCT2S			= 38,
	LCT3S			= 39,
	LCT4S			= 40,
	LETRS			= 41,
	LSNS_NUM		= 42,								/* Number of sensor	*/
	LSNS_END		= LSNS_NUM,			/* End point for using when specify	*/
	LSNS_NAME_END	= 42
};
	/*----------------------------------------------------------------------*/
	/*	Sensor Level														*/
	/*----------------------------------------------------------------------*/
enum
{
	SNS_LEVEL_TOP	= 0x00,
	SNS_LEVEL0		= 0x00,
	SNS_LEVEL1		= 0x01,
	SNS_LEVEL2		= 0x02,
	SNS_LEVEL3		= 0x03,
	SNS_LEVEL4		= 0x04,
	SNS_LEVEL5		= 0x05,
	SNS_LEVEL6		= 0x06,
	SNS_LEVEL7		= 0x07,
	SNS_LEVEL8		= 0x08,
	SNS_LEVEL9		= 0x09,
	SNS_LEVEL10		= 0x0A,
	SNS_LEVEL11		= 0x0B,
	SNS_LEVEL12		= 0x0C,
	SNS_LEVEL13		= 0x0D,
	SNS_LEVEL14		= 0x0E,
	SNS_LEVEL15		= 0x0F,
	SNS_LEVEL16		= 0x10,
	SNS_LEVEL17		= 0x11,
	SNS_LEVEL18		= 0x12,
	SNS_LEVEL19		= 0x13,
	SNS_LEVEL20		= 0x14,
	SNS_LEVEL21		= 0x15,
	SNS_LEVEL22		= 0x16,
	SNS_LEVEL23		= 0x17,
	SNS_LEVEL24		= 0x18,
	SNS_LEVEL25		= 0x19,
	SNS_LEVEL26		= 0x1A,
	SNS_LEVEL27		= 0x1B,
	SNS_LEVEL28		= 0x1C,
	SNS_LEVEL29		= 0x1D,
	SNS_LEVEL30		= 0x1E,
	SNS_LEVEL31		= 0x1F,
	SNS_LEVEL_MAX	= SNS_LEVEL31,
	SNS_LEVEL_END	= 0x20,
	SNS_LEVEL_NONE	= 0xFF									/* Not write	*/
};
/*--------------------------------------------------------------------------*/
/*	Sensor ( Read )															*/
/*--------------------------------------------------------------------------*/
	/*----------------------------------------------------------------------*/
	/*	Sensor Port Name													*/
	/*----------------------------------------------------------------------*/
enum
{
	SP_NAME_TOP	= 0x00FF,
	SP_RUS0		= 0x00FF,
	SP_RUS1		= 0x01FF,
	SP_RUS2		= 0x02FF,
	SP_RUS3		= 0x03FF,
	SP_RUS4		= 0x04FF,
	SP_RUS5		= 0x05FF,
	SP_RUS6		= 0x06FF,
	SP_RUS7		= 0x07FF,
	SP_RUS9		= 0x09FF,
	SP_RLS4		= 0x0AFF,
	SP_RLS6		= 0x0BFF,
	SP_RLS0		= 0x0CFF,
	SP_RLS1		= 0x0DFF,
	SP_RLS2		= 0x0EFF,
	SP_RLS3		= 0x0FFF,
	SP_RLS8		= 0x10FF,
	SP_RLS9		= 0x11FF,
	SP_RLS10	= 0x12FF,
	SP_RLS11	= 0x13FF,
	SP_RLS12	= 0x14FF,
	SP_RLS13	= 0x15FF,
	SP_RLS14	= 0x16FF,
	SP_RLS15	= 0x17FF,
	SP_RUS12	= 0x18FF,
	SP_RUS13	= 0x19FF,
	SP_RUS14	= 0x1AFF,
	SP_RLS5		= 0x1CFF,
	SP_RLS7		= 0x1DFF,
	SP_NAME_END	= 0x1EFF
};
	/*----------------------------------------------------------------------*/
	/*	Sensor Name															*/
	/*----------------------------------------------------------------------*/
enum
{
		/*------------------------------------------------------------------*/
		/*	(0) RUS0														*/
		/*	Rev.(ZZ06:BRZ-306)												*/
		/*	change (S_PPRC -> S_PBPC , S_PLPC -> S_PTPC)					*/
		/*------------------------------------------------------------------*/
	S_PCEC	= 0x0040,
	S_PBPC	= 0x0020,
	S_PRPC	= 0x0010,
	S_PTPC	= 0x0008,
	S_PDPC	= 0x0004,
	S_POLC	= 0x0002,
	S_PTHC	= 0x0001,
		/*------------------------------------------------------------------*/
		/*	(1) RUS1														*/
		/*	Rev.(ZW01:BRZ-723)												*/
		/*	 Add PHPC														*/
		/*------------------------------------------------------------------*/
	S_PHPC	= 0x0180,
	S_ERLC	= 0x0120,
	S_ERRC	= 0x0110,
	S_ERUC	= 0x0108,
	S_ECPC	= 0x0104,
	S_ECCC	= 0x0102,
	S_ECHC	= 0x0101,
		/*------------------------------------------------------------------*/
		/*	(2) RUS2														*/
		/*	Rev.(ZW01:BRZ-723)												*/
		/*	 Add PLPC,ESPC													*/
		/*	Rev.(ZV01:BRZ-912)												*/
		/*	 Add ETLC.														*/
		/*------------------------------------------------------------------*/
	S_PLPC	= 0x0280,
	S_ETLC	= 0x0210,
	S_ESPC	= 0x0208,
	S_EERC	= 0x0204,
	S_EELC	= 0x0202,
	S_EEUC	= 0x0201,
		/*------------------------------------------------------------------*/
		/*	(3) RUS3														*/
		/*	Rev.(AA04:BRZ-1189)												*/
		/*	 add PDAC														*/
		/*------------------------------------------------------------------*/
	S_PDAC	= 0x0380,
	S_SSEC	= 0x0320,
	S_SSLC	= 0x0310,
	S_SSUC	= 0x0308,
	S_SPBC	= 0x0304,
	S_SPPC	= 0x0302,
	S_SPUC	= 0x0301,
		/*------------------------------------------------------------------*/
		/*	(4) RUS4														*/
		/*	Rev.(ZY01:BRZ-406)												*/
		/*	 Delete SWLC,SWRC and add SFIC,SFOC,SHDC,SBLC					*/
		/*------------------------------------------------------------------*/
	S_SBLC	= 0x0440,
	S_SHDC	= 0x0420,
	S_SCDC	= 0x0410,
	S_SFPC	= 0x0408,
	S_SPCC	= 0x0404,
	S_SFOC	= 0x0402,
	S_SFIC	= 0x0401,
		/*------------------------------------------------------------------*/
		/*	(5) RUS5														*/
		/*	Rev.(ZY01:BRZ-406)												*/
		/*	 Add UGLC														*/
		/*------------------------------------------------------------------*/
	S_UGLC	= 0x0540,
	S_ULPC	= 0x0520,
	S_URFC	= 0x0510,
	S_UFFC	= 0x0508,
	S_UCFC	= 0x0504,
	S_URLC	= 0x0502,
	S_UULC	= 0x0501,
		/*------------------------------------------------------------------*/
		/*	(6) RUS6														*/
		/*	Rev.(ZZ06:BRZ-306)												*/
		/*	Addition (S_PDSS)												*/
		/*	Rev.(ZV01:BRZ-911)												*/
		/*	 Add ETRS.														*/
		/*------------------------------------------------------------------*/
	S_ETRS	= 0x0680,
	S_PDSS	= 0x0640,
	S_PASS	= 0x0620,
	S_PTCS	= 0x0610,
	S_PS4S	= 0x0608,
	S_PS3S	= 0x0604,
	S_PS2S	= 0x0602,
	S_PS1S	= 0x0601,
		/*------------------------------------------------------------------*/
		/*	(7) RUS7														*/
		/*	Rev.(ZV01:BRZ-911)												*/
		/*------------------------------------------------------------------*/
	S_ETLS	= 0x0708,
	S_EECS	= 0x0704,
	S_EERS	= 0x0702,
	S_EELS	= 0x0701,
		/*------------------------------------------------------------------*/
		/*	(8)																*/
		/*------------------------------------------------------------------*/
		/*------------------------------------------------------------------*/
		/*	(9) RUS9														*/
		/*------------------------------------------------------------------*/
	S_FLD	= 0x0980,
	S_FLT	= 0x0940,
	S_LOCK	= 0x0910,
	S_SW3	= 0x0904,
	S_SW2	= 0x0902,
	S_SW1	= 0x0901,
		/*------------------------------------------------------------------*/
		/*	(10) RLS4														*/
		/*	Rev.(ZW01:BRZ-723)												*/
		/*	 Add SHCC,SHOC,ILOF												*/
		/*------------------------------------------------------------------*/
	S_SHOC	= 0x0A20,
	S_SHCC	= 0x0A10,
	S_ILOF	= 0x0A02,
	S_BLLC	= 0x0A01,
		/*------------------------------------------------------------------*/
		/*	(11) RLS6														*/
		/*	Rev.(ZY01:BRZ-429)												*/
		/*	 Delete SHCC,SHOC												*/
		/*------------------------------------------------------------------*/
		/*------------------------------------------------------------------*/
		/*	(12) RLS0														*/
		/*------------------------------------------------------------------*/
	S_C1SET	= 0x0C80,
	S_D13C	= 0x0C08,
	S_D12C	= 0x0C04,
	S_D11C	= 0x0C02,
	S_D10C	= 0x0C01,
		/*------------------------------------------------------------------*/
		/*	(13) RLS1														*/
		/*------------------------------------------------------------------*/
	S_C2SET	= 0x0D80,
	S_D23C	= 0x0D08,
	S_D22C	= 0x0D04,
	S_D21C	= 0x0D02,
	S_D20C	= 0x0D01,
		/*------------------------------------------------------------------*/
		/*	(14) RLS2														*/
		/*------------------------------------------------------------------*/
	S_C3SET	= 0x0E80,
	S_D33C	= 0x0E08,
	S_D32C	= 0x0E04,
	S_D31C	= 0x0E02,
	S_D30C	= 0x0E01,
		/*------------------------------------------------------------------*/
		/*	(15) RLS3														*/
		/*------------------------------------------------------------------*/
	S_C4SET	= 0x0F80,
	S_D43C	= 0x0F08,
	S_D42C	= 0x0F04,
	S_D41C	= 0x0F02,
	S_D40C	= 0x0F01,
		/*------------------------------------------------------------------*/
		/*	(16) RLS8														*/
		/*------------------------------------------------------------------*/
	S_CE1C	= 0x1080,
	S_C1NR	= 0x1010,
	S_CT1S	= 0x1008,
	S_NE1C	= 0x1004,
	S_NF1C	= 0x1002,
	S_CF1C	= 0x1001,
		/*------------------------------------------------------------------*/
		/*	(17) RLS9														*/
		/*------------------------------------------------------------------*/
	S_CV1C	= 0x1180,
	S_CC1C	= 0x1110,
	S_CO1C	= 0x1108,
	S_CD1C	= 0x1104,
	S_CS1C	= 0x1102,
	S_CP1C	= 0x1101,
		/*------------------------------------------------------------------*/
		/*	(18) RLS10														*/
		/*------------------------------------------------------------------*/
	S_CE2C	= 0x1280,
	S_C2NR	= 0x1210,
	S_CT2S	= 0x1208,
	S_NE2C	= 0x1204,
	S_NF2C	= 0x1202,
	S_CF2C	= 0x1201,
		/*------------------------------------------------------------------*/
		/*	(19) RLS11														*/
		/*------------------------------------------------------------------*/
	S_CV2C	= 0x1380,
	S_CC2C	= 0x1310,
	S_CO2C	= 0x1308,
	S_CD2C	= 0x1304,
	S_CS2C	= 0x1302,
	S_CP2C	= 0x1301,
		/*------------------------------------------------------------------*/
		/*	(20) RLS12														*/
		/*------------------------------------------------------------------*/
	S_CE3C	= 0x1480,
	S_C3NR	= 0x1410,
	S_CT3S	= 0x1408,
	S_NE3C	= 0x1404,
	S_NF3C	= 0x1402,
	S_CF3C	= 0x1401,
		/*------------------------------------------------------------------*/
		/*	(21) RLS13														*/
		/*------------------------------------------------------------------*/
	S_CV3C	= 0x1580,
	S_CC3C	= 0x1510,
	S_CO3C	= 0x1508,
	S_CD3C	= 0x1504,
	S_CS3C	= 0x1502,
	S_CP3C	= 0x1501,
		/*------------------------------------------------------------------*/
		/*	(22) RLS14														*/
		/*------------------------------------------------------------------*/
	S_CE4C	= 0x1680,
	S_C4NR	= 0x1610,
	S_CT4S	= 0x1608,
	S_NE4C	= 0x1604,
	S_NF4C	= 0x1602,
	S_CF4C	= 0x1601,
		/*------------------------------------------------------------------*/
		/*	(23) RLS15														*/
		/*------------------------------------------------------------------*/
	S_CV4C	= 0x1780,
	S_CC4C	= 0x1710,
	S_CO4C	= 0x1708,
	S_CD4C	= 0x1704,
	S_CS4C	= 0x1702,
	S_CP4C	= 0x1701,
		/*------------------------------------------------------------------*/
		/*	(24) RUS12														*/
		/*------------------------------------------------------------------*/
	S_UERS	= 0x1840,
	S_UEFS	= 0x1820,
	S_UECS	= 0x1810,
	S_UFHS	= 0x1808,
	S_URHS	= 0x1804,
	S_UGDS	= 0x1802,
	S_UGAS	= 0x1801,
		/*------------------------------------------------------------------*/
		/*	(25) RUS13														*/
		/*------------------------------------------------------------------*/
	S_SDOS	= 0x1910,
	S_SDIS	= 0x1908,
	S_SSOS	= 0x1904,
	S_SSLS	= 0x1902,
	S_SSRS	= 0x1901,
		/*------------------------------------------------------------------*/
		/*	(26) RUS14														*/
		/*------------------------------------------------------------------*/
	S_EDRS	= 0x1A80,
	S_EDLS	= 0x1A40,
	S_ERRS	= 0x1A20,
	S_ERLS	= 0x1A10,
		/*------------------------------------------------------------------*/
		/*	(27)															*/
		/*------------------------------------------------------------------*/
		/*------------------------------------------------------------------*/
		/*	(28) RLS5														*/
		/*	Rev.(ZY01:BRZ-406)												*/
		/*	 Add LFHS														*/
		/*------------------------------------------------------------------*/
	S_LFHS	= 0x1C02,
	S_LT3S	= 0x1C01,
		/*------------------------------------------------------------------*/
		/*	(29) RLS7														*/
		/*------------------------------------------------------------------*/
	S_CR4S	= 0x1D80,
	S_CL4S	= 0x1D40,
	S_CR3S	= 0x1D20,
	S_CL3S	= 0x1D10,
	S_CR2S	= 0x1D08,
	S_CL2S	= 0x1D04,
	S_CR1S	= 0x1D02,
	S_CL1S	= 0x1D01
		/*------------------------------------------------------------------*/
		/*	(30)															*/
		/*------------------------------------------------------------------*/
		/*------------------------------------------------------------------*/
		/*	(31)															*/
		/*------------------------------------------------------------------*/
};
	/*----------------------------------------------------------------------*/
	/*	Pair Sensor Name													*/
	/*----------------------------------------------------------------------*/
enum
{
	S_SSxS = ( S_SSOS | S_SSLS | S_SSRS ),
	S_EDxS = ( S_EDRS | S_EDLS ),
	S_ERxS = ( S_ERRS | S_ERLS ),
	S_Cx4S = ( S_CR4S | S_CL4S ),
	S_Cx3S = ( S_CR3S | S_CL3S ),
	S_Cx2S = ( S_CR2S | S_CL2S ),
	S_Cx1S = ( S_CR1S | S_CL1S )
};
	/*----------------------------------------------------------------------*/
	/*	Pair Sensor on / off												*/
	/*----------------------------------------------------------------------*/
enum
{
	PAIR_SNS_OFF_OFF,
	PAIR_SNS_ON_ON,
	PAIR_SNS_ON_OFF
};
	/*----------------------------------------------------------------------*/
	/*	Skew Sensor Name													*/
	/*	Rev.(AA12:BRZ-1321) add SKEW_BVIN									*/
	/*	Rev.(AA14:BRZ-1356)													*/
	/*	 add SKEW_NAME_END_CTRL												*/
	/*	Rev.(AA21:BRZ-1430)													*/
	/*	 add SKEW_SSxS_R													*/
	/*----------------------------------------------------------------------*/
enum
{
	SKEW_NAME_TOP		= 0,
	SKEW_SSxS			= 0,
	SKEW_Cx1S			= 1,
	SKEW_Cx2S			= 2,
	SKEW_Cx3S			= 3,
	SKEW_Cx4S			= 4,
	SKEW_NAME_END_CTRL	= 5,
	SKEW_BVIN			= 5,
	SKEW_SSxS_R			= 6,
	SKEW_NAME_END		= 7
};
	/*----------------------------------------------------------------------*/
	/*	Max number of Sensor												*/
	/*	Rev.(ZY01:BRZ-426)	Add definition of Max number of sensor.			*/
	/*----------------------------------------------------------------------*/
#define	MAX_SNS_NUMBER	0x200
/*--------------------------------------------------------------------------*/
/*	Rev.(ZY05:BRZ-569)		add												*/
/*	Over Current															*/
/*--------------------------------------------------------------------------*/
	/*----------------------------------------------------------------------*/
	/*	Over Current Location Port Name										*/
	/*----------------------------------------------------------------------*/
enum
{
	OCLP_NAME_TOP	= 0,
	OCLP_RUFL0		= 0,
	OCLP_RUFL1		= 1,
	OCLP_RLFL0		= 2,
	OCLP_RLFL1		= 3,
	OCLP_NAME_END	= 4
};
/*--------------------------------------------------------------------------*/
/*	7 segments LED															*/
/*--------------------------------------------------------------------------*/
	/*----------------------------------------------------------------------*/
	/*	Code																*/
	/*----------------------------------------------------------------------*/
#define	LED7_B	0xEC												/* b	*/
#define	LED7_C	0x39												/* c	*/
#define	LED7_D	0x5E												/* d	*/
#define	LED7_I	0x19												/* i	*/
#define	LED7_J	0x0D												/* j	*/
#define	LED7_K	0x7A												/* k	*/
#define	LED7_N	0x54												/* n	*/
#define	LED7_O	0x5D												/* o	*/
#define	LED7_P	0x73												/* p	*/
#define	LED7_R	0x70												/* r	*/
#define	LED7_S	0x6D												/* s	*/
#define	LED7_T	0x78												/* t	*/
#define	LED7_V	0x1C												/* v	*/
#define	LED7_W	0x7E												/* w	*/
/*--------------------------------------------------------------------------*/
/*	Rev.(ZT02:BRZ-1108)		add												*/
/*	A/D converter															*/
/*--------------------------------------------------------------------------*/
	/*----------------------------------------------------------------------*/
	/*	Channel No.															*/
	/*----------------------------------------------------------------------*/
enum
{
	ADC_CH0,
	ADC_CH1,
	ADC_CH2,
	ADC_CH3,
	ADC_CH4,
	ADC_CH5,
	ADC_CH6,
	ADC_CH7,
	ADC_CH_END
};
/*--------------------------------------------------------------------------*/
/*																			*/
/*	Pointer Define															*/
/*																			*/
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/*	TimeUp Function Pointer													*/
/*--------------------------------------------------------------------------*/
typedef	int		(*QueueData)(void);
/*--------------------------------------------------------------------------*/
/*																			*/
/*	Event Define															*/
/*																			*/
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/*	infinite event															*/
/*--------------------------------------------------------------------------*/
#define		INFINITE_EVENT			(int)0
/*--------------------------------------------------------------------------*/
/*																			*/
/*	Steps Define															*/
/*																			*/
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/*	it stops immediately													*/
/*--------------------------------------------------------------------------*/
#define		RAPID_STOP				0
/*--------------------------------------------------------------------------*/
/*																			*/
/*	Debug Defines															*/
/*																			*/
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/*	print select bit defines												*/
/*	Rev.(ZY02:BRZ-439)														*/
/*	 Add PRINT_LAN_PACKET,PRINT_LAN_BV										*/
/*	Rev.(AA10:BRZ-1303)														*/
/*	 add PRINT_PICK															*/
/*	Rev.(AA19:BRZ-1419)														*/
/*	 add PRINT_SKEW															*/
/*--------------------------------------------------------------------------*/
#define	PRINT_NOTHING		0
#define	PRINT_SENSOR_EDGE	BIT0
#define	PRINT_SENSOR_WRITE	BIT1
#define	PRINT_CMD_MOVE		BIT2
#define	PRINT_MOVE			BIT3
#define	PRINT_DRAS			BIT4
#define	PRINT_TRANS			BIT5
#define	PRINT_MECHA			BIT6
#define	PRINT_WATCH			BIT7
#define	PRINT_LAN_PACKET	BIT8
#define	PRINT_LAN_BV		BIT9
#define	PRINT_BV_API		BIT10
#define	PRINT_PICK			BIT11
#define	PRINT_SKEW			BIT12
#define	PRINT_ALL			0xFFFFFFFF
/*--------------------------------------------------------------------------*/
/*	Stepping Motor															*/
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/*	Transport DC Motor														*/
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/*	Linear Solenoid															*/
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/*	Rotary Solenoid															*/
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/*	Media Indicator															*/
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/*	Sensor ( Level write )													*/
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/*	Sensor ( Read )															*/
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/*	insertion presenting watch												*/
/*--------------------------------------------------------------------------*/
	/*----------------------------------------------------------------------*/
	/*	Interrupt															*/
	/*	Rev.(ZY01:BRZ-413)	add label.(IO_CHANGE_MEDIA)						*/
	/*	Rev.(ZY04:BRZ-572)	add label.(IO_INVALID_OPERATION)				*/
	/*	Rev.(ZV05:BRZ-961)	add label.(IO_ADD_DISCHARGE)					*/
	/*	Rev.(ZV05:BRZ-962)	add label.(IO_MORE_DISCHARGE)					*/
	/*----------------------------------------------------------------------*/
enum
{
	IO_CLEAR_CONDITION		= 0,
	IO_COMPLETE_CONDITION	= 1,
	IO_CHANGE_MEDIA			= 2,
	IO_INVALID_OPERATION	= 3,
	IO_ADD_DISCHARGE		= 4,
	IO_MORE_DISCHARGE		= 5
};
enum
{
	IO_SC_DRAW_NORMAL		= 0,
	IO_SC_DRAW_FORCE		= 1
};
/*--------------------------------------------------------------------------*/
/*	Bill Kind																*/
/*	Rev.(ZZ05:BRZ-192)	add kind of bill definitions						*/
/*	Rev.(ZZ05:BRZ-193)	add denomination of cassette definitions			*/
/*	Rev.(ZZ06:BRZ-285)	add damaged of bill definition						*/
/*	Rev.(ZY02:BRZ-461)	add mask of bill definition							*/
/*	Rev.(ZY04:BRZ-598)	change value of cassette denomination.				*/
/*--------------------------------------------------------------------------*/
enum
{
	KIND_BILL_TOP			= 0x00,
	KIND_BILL_GENUINE_MAX	= 0x80,
	KIND_BILL_DAMAGED		= 0x80,
	KIND_BILL_NOT_RECOGNIZE	= 0x81,
	KIND_BILL_SUSPECT		= 0x82,
	KIND_BILL_COUNTERFEIT	= 0x83,

	KIND_BILL_NOT_USE		= 0x84,
	KIND_BILL_TEMPORARY		= 0x85,
/*
	KIND_CA_NOT_USE			= 0x80,
	KIND_CA_SUSPECT			= 0x81,
	KIND_CA_TEMPORARY		= 0x82,
*/
	KIND_BILL_END			= 0x84,
	KIND_BILL_CA_END		= 0x86,
	KIND_BILL_MASK			= 0xFE,
	KIND_BILL_UNJUST		= 0xFF
};
/*--------------------------------------------------------------------------*/
/*	RAS KEY																	*/
/*--------------------------------------------------------------------------*/
enum
{
	RAS_KEY_NULL			= 0x00,
	RAS_KEY_S1				= 0x01,
	RAS_KEY_S2				= 0x02,
	RAS_KEY_ST				= 0x04,
	RAS_KEY_S1_S2			= (RAS_KEY_S1|RAS_KEY_S2),
	RAS_KEY_S1_ST			= (RAS_KEY_S1|RAS_KEY_ST),
	RAS_KEY_S2_ST			= (RAS_KEY_S2|RAS_KEY_ST),
	RAS_KEY_S1_S2_ST		= (RAS_KEY_S1|RAS_KEY_S2|RAS_KEY_ST)
};
/*--------------------------------------------------------------------------*/
/*	FULL EMPTY																*/
/*--------------------------------------------------------------------------*/
enum
{
	MEDIA_EMPTY		= 0x00,
	MEDIA_NEAR_EMPTY= 0x01,
	MEDIA_NORMAL	= 0x02,
	MEDIA_NEAR_FULL	= 0x03,
	MEDIA_FULL		= 0x04
};
	/*----------------------------------------------------------------------*/
	/*	<ZZ06:BRZ-249>														*/
	/*	BV Validatation Mode												*/
	/*----------------------------------------------------------------------*/
enum{
	BV_VALIDATE_MODE1			= (UCHAR)0x00,
	BV_VALIDATE_MODE2  			= (UCHAR)0x10,
	BV_VALIDATE_MODE3			= (UCHAR)0x20,
	BV_VALIDATE_MODE4			= (UCHAR)0x30,
	BV_VALIDATE_MODE5			= (UCHAR)0x40,
	BV_VALIDATE_MODE6			= (UCHAR)0x50,
	BV_VALIDATE_MODE7			= (UCHAR)0x60,
	BV_VALIDATE_MODE8  			= (UCHAR)0x70
};
	/*----------------------------------------------------------------------*/
	/*	<ZZ06:BRZ-248>														*/
	/*	TreatmentNumber														*/
	/*	Rev.(ZY03:BRZ-529)	Renewal definition of treatment number.			*/
	/*	Rev.(ZY06:BRZ-672)	Add BV_TREATMENT_CL.							*/
	/*----------------------------------------------------------------------*/
enum{	BV_TREATMENT_SV 	= (UCHAR)BIT7,

	BV_TREATMENT_MJ	= (UCHAR)0x00,
	BV_TREATMENT_IV	= (UCHAR)0x02,
	BV_TREATMENT_DP = (UCHAR)0x03,
	BV_TREATMENT_WC	= (UCHAR)0x04,
	BV_TREATMENT_CL	= (UCHAR)0x0b,
	BV_TREATMENT_RJ	= (UCHAR)0x0c,
	BV_TREATMENT_PC	= (UCHAR)0x0d,
	BV_TREATMENT_UC	= (UCHAR)0x0e,
	BV_TREATMENT_JA	= (UCHAR)0x0f
};
/*--------------------------------------------------------------------------*/
/*	BV_INFORMATION															*/
/*	Rev.(ZY06:BRZ-693)	It is reshaking about a number.						*/
/*--------------------------------------------------------------------------*/
enum
{
	BV_ALARM_INFORMATION				= 0x01,
	BV_REVISION_INFORMATION				= 0x02,
	BV_UNIT_INFORMATION					= 0x03,
	BV_STATISTICAL_INFORMATION			= 0x04,
	BV_MESSAGE_INFORMATION				= 0x05,
	BV_VALIDATE_INFORMATION_ALL			= 0x06,
	BV_VALIDATE_INFORMATION_SAME_ALL	= 0x07,
	BV_VALIDATE_INFORMATION_LAST		= 0x08,
	BV_RECOGNITION_INFORMATION			= 0x09
};
/*--------------------------------------------------------------------------*/
/*	response order															*/
/*	Rev.(ZZ04:BRZ-143)														*/
/*	Rev.(ZZ04:BRZ-184)	add RESP_NONE (Only header part)					*/
/*	Rev.(ZY01:BRZ-433)	add RESP_ORDER_MAX.									*/
/*	Rev.(ZY04:BRZ-567)	add RESP_T0.										*/
/*	Rev.(ZY06:BRZ-668)	add RESP_J0～JF,L0～LH								*/
/*--------------------------------------------------------------------------*/
enum{
	RESP_FX = 0x01,
	RESP_F0 = 0x02,
	RESP_G0	= 0x03,			/* G0,G1,G3,G4,G5,G6,G9,GA,GB	*/
	RESP_IX = 0x04,
	RESP_I3 = 0x05,
	RESP_Jx = 0x06,			/* J0-J9,JA-JY					*/
	RESP_Lx = 0x07,			/* L0-L9						*/
	RESP_Mx = 0x08,			/* M1-M9						*/
	RESP_Rx = 0x09,			/* R0-RC						*/
	RESP_R1 = 0x0A,
	RESP_R7 = 0x0B,
	RESP_Ox = 0x0C,			/* OF,O1-O9						*/
	RESP_T0 = 0x0D,			/* T0							*/
	RESP_J0 = 0x0E,			/* J0							*/
	RESP_J1 = 0x0F,			/* J1							*/
	RESP_J4 = 0x10,			/* J4							*/
	RESP_J5 = 0x11,			/* J5							*/
	RESP_J7 = 0x12,			/* J7							*/
	RESP_J8 = 0x13,			/* J8							*/
	RESP_JA = 0x14,			/* JA							*/
	RESP_JB = 0x15,			/* JB							*/
	RESP_JC = 0x16,			/* JC							*/
	RESP_JD = 0x17,			/* JD							*/
	RESP_JE = 0x18,			/* JE							*/
	RESP_JF = 0x19,			/* JF							*/
	RESP_L0 = 0x1A,			/* L0							*/
	RESP_L1 = 0x1B,			/* L1							*/
	RESP_L2 = 0x1C,			/* L2							*/
	RESP_L3 = 0x1D,			/* L3							*/
	RESP_L4 = 0x1E,			/* L4							*/
	RESP_L5 = 0x1F,			/* L5							*/
	RESP_L6 = 0x20,			/* L6							*/
	RESP_L7 = 0x21,			/* L7							*/
	RESP_L8 = 0x22,			/* L8							*/
	RESP_L9 = 0x23,			/* L9							*/
	RESP_LA = 0x24,			/* LA							*/
	RESP_LB = 0x25,			/* LB							*/
	RESP_LC = 0x26,			/* LC							*/
	RESP_LD = 0x27,			/* LD							*/
	RESP_LE = 0x28,			/* LE							*/
	RESP_LF = 0x29,			/* LF							*/
	RESP_LG = 0x2A,			/* LG							*/
	RESP_LH = 0x2B,			/* LH							*/
	RESP_ORDER_MAX = 0x2C,
	RESP_NONE= 0xFF
};
	/*----------------------------------------------------------------------*/
	/*	SEND FACTOR															*/
	/*	Rev.(ZZ06:BRZ-310)	add definition of send factor.					*/
	/*	Rev.(ZT09:BRZ-1145)	add send factor. (Media exist/not exist)		*/
	/*----------------------------------------------------------------------*/
enum
{
	SEND_FACTOR_NORMAL			= 0x00,
	SEND_FACTOR_MEDIA			= 0x01,
	SEND_FACTOR_INSERT_NG		= 0x02,
	SEND_FACTOR_SHT_OPEN		= 0x03,
	SEND_FACTOR_SHT_CLOSE		= 0x04,
	SEND_FACTOR_PRESENT_NG		= 0x05,
	SEND_FACTOR_IO_TIMEUP		= 0x06,
	SEND_FACTOR_TO_PREPARE		= 0x07,
	SEND_FACTOR_MEDIA_EXIST		= 0x08,
	SEND_FACTOR_MEDIA_NOT_EXIST	= 0x09
};
/*--------------------------------------------------------------------------*/
/*																			*/
/*	Type Informations														*/
/*																			*/
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/*	Machine Type															*/
/*	Rev.(ZZ04:BRZ-146)	add this enum										*/
/*--------------------------------------------------------------------------*/
enum
{
	/*----------------------------------------------------------------------*/
	/*	Item																*/
	/*----------------------------------------------------------------------*/
	MACHINE_TYPE_FUNC		= 0xF0,		/* 	unit function					*/
	MACHINE_TYPE_NUMBER		= 0x0F,		/* 	cassette size(number)			*/
	MACHINE_TYPE_BRU		= 0x10,		/*	BRU								*/
	MACHINE_TYPE_BNA		= 0x20,		/*	BNA								*/
	MACHINE_TYPE_SHORT		= 0x02,		/*	short type (2 cassettes)		*/
	MACHINE_TYPE_LONG		= 0x04,		/*	long type  (4 cassettes)		*/
	/*----------------------------------------------------------------------*/
	/*	Type																*/
	/*----------------------------------------------------------------------*/
	MACHINE_TYPE_BNA_SHORT	= MACHINE_TYPE_BNA | MACHINE_TYPE_SHORT,
	MACHINE_TYPE_BNA_LONG	= MACHINE_TYPE_BNA | MACHINE_TYPE_LONG,
	MACHINE_TYPE_BRU_LONG	= MACHINE_TYPE_BRU | MACHINE_TYPE_LONG
};

/*--------------------------------------------------------------------------*/
/*	Cassette Type															*/
/*	Rev.(ZY01:BRZ-432)														*/
/*--------------------------------------------------------------------------*/
enum
{
	CASSETTE_NONE	= 0x00,							/* Cassette nothing		*/
	CASSETTE_RCY	= BIT0,							/* Recycle cassette		*/
	CASSETTE_DEP	= BIT1,							/* Deposit cassette		*/
	CASSETTE_UNK	= BIT2,							/* unknouwn cassette	*/
	CASSETTE_ALL	= (CASSETTE_RCY|CASSETTE_DEP|CASSETTE_UNK),	/* All  	*/
	CASSETTE_USE	= BIT3							/* Use cassette			*/
};
/*--------------------------------------------------------------------------*/
/*	Extended Cassette														*/
/*	Rev.(AA54:BRZ-1557)														*/
/*--------------------------------------------------------------------------*/
enum
{
	CASSETTE_NOT_EXTENDED	= 0x00,				/* Not extended cassette	*/
	CASSETTE_EXTENDED		= 0x04				/* Extended cassette		*/
};
/*--------------------------------------------------------------------------*/
/*	Cassette Model															*/
/*	Rev.(AA09:BRZ-1278)														*/
/*--------------------------------------------------------------------------*/
enum
{
	CASSETTE_MODEL_NONE	= 0x00,						/* Cassette nothing		*/
	CASSETTE_MODEL_B	= 0x01,						/* Model B				*/
	CASSETTE_MODEL_C	= 0x02						/* Model C				*/
};
/*--------------------------------------------------------------------------*/
/*	Rev.(ZY04:BRZ-555)														*/
/*	define addition															*/
/*--------------------------------------------------------------------------*/
#define		MASK_PAC		(RSUP_PAC0 | RSUP_PAC1 | RSUP_PAC2)

#define		PAC_SHORT		(RSUP_PAC1 | RSUP_PAC2)
#define		PAC_MIDDLE		(RSUP_PAC0 | RSUP_PAC2)
#define		PAC_LONG		(RSUP_PAC0 | RSUP_PAC1)
#define		PAC_MORE_LONG	(RSUP_PAC2)
#define		PAC_NON_CONNECT	(RSUP_PAC0 | RSUP_PAC1 | RSUP_PAC2)

/*--------------------------------------------------------------------------*/
/*	Rev.(ZY04:BRZ-555)														*/
/*	enum addition(Preacceptor type)											*/
/*--------------------------------------------------------------------------*/
enum
{
	PAC_TYPE_140			= 0x00,
	PAC_TYPE_178 			= 0x01,
	PAC_TYPE_240			= 0x02,
	PAC_TYPE_354			= 0x03,
	PAC_TYPE_DIFFERENT		= 0xFE,
	PAC_TYPE_NONE_CONNECT	= 0xFF
};

/*--------------------------------------------------------------------------*/
/*	reject bin type															*/
/*	Rev.(ZY04:BRZ-563)	add this definition									*/
/*--------------------------------------------------------------------------*/
enum
{
	REJECT_TYPE_REMOVAL	= 0,			/*	removal(3 area)					*/
	REJECT_TYPE_FIXED	= 1				/*	fixed(2 area)					*/
};

/*--------------------------------------------------------------------------*/
/*	Rev.(ZZ07:BRZ-341)														*/
/*	Job Request 															*/
/*	Rev.(ZY01:BRZ-409)														*/
/*	add INSERT,PRESENT,FEED													*/
/*--------------------------------------------------------------------------*/
enum
{
	JOB_REQUEST_CLEAR_JAM		= 0x01,			/* 							*/
	JOB_REQUEST_CHECK_TRANSPORT	= 0x02,			/* 							*/
	JOB_REQUEST_CONFIRM_MECHA	= 0x03,			/* 							*/
	JOB_REQUEST_CLOSE_SHT		= 0x04,			/* 							*/
	JOB_REQUEST_INSERT			= 0x05,			/* 							*/
	JOB_REQUEST_PRESENT			= 0x06,			/* 							*/
	JOB_REQUEST_FEED			= 0x07			/* 							*/
};
/*--------------------------------------------------------------------------*/
/*	Rev.(ZY06:BRZ-690)														*/
/*	Rev.(ZW04:BRZ-841)	add DBG_LOG_KIND_ANALYSIS							*/
/*--------------------------------------------------------------------------*/
enum
{
	DBG_LOG_KIND_TOP		= 0x00,
	DBG_LOG_KIND_PACKET		= 0x00,
	DBG_LOG_KIND_SENSOR		= 0x01,
	DBG_LOG_KIND_MOTOR		= 0x02,
	DBG_LOG_KIND_SOLENOID	= 0x03,
	DBG_LOG_KIND_SKEW		= 0x04,
	DBG_LOG_KIND_TIMEUP		= 0x05,
	DBG_LOG_KIND_VD			= 0x06,
	DBG_LOG_KIND_USB		= 0x07,
	DBG_LOG_KIND_COMMAND	= 0x08,
	DBG_LOG_KIND_LAN		= 0x09,
	DBG_LOG_KIND_OTHERS		= 0x0A,
	DBG_LOG_KIND_ANALYSIS	= 0x0B,
	DBG_LOG_KIND_END		= 0x0C
};
/*--------------------------------------------------------------------------*/
/*	Read log data request													*/
/*	Rev.(ZW04:BRZ-841)														*/
/*--------------------------------------------------------------------------*/
enum
{
	ERR_R_NONE				= 0x00,		/*	Nothiing request				*/
	ERR_R_LOG				= 0x01		/*	Read log data request			*/
};
/****************************************************************************/
/*																			*/
/*	typedefs																*/
/*																			*/
/****************************************************************************/
/*--------------------------------------------------------------------------*/
/*																			*/
/*	Place Define															*/
/*																			*/
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/*	MECHA_PLACE																*/
/*	Rev.(ZZ05:BRZ-190)	The label addition for six cassettes				*/
/*	Rev.(ZW04:BRZ-806)	Add label of BV.									*/
/*	Rev.(ZU08:BRZ-1100)	Add label of BUNCH for mechanical error location	*/
/*--------------------------------------------------------------------------*/
enum
{
	MECHA_CA1	= BIT0,
	MECHA_CA2	= BIT1,
	MECHA_CA3	= BIT2,
	MECHA_CA4	= BIT3,
	MECHA_CA5	= BIT4,
	MECHA_CA6	= BIT5,
	MECHA_PAC	= BIT6,
	MECHA_ESC	= BIT7,
	MECHA_RSV	= BIT8,
	MECHA_SEP	= BIT9,
	MECHA_SHT	= BIT10,
	MECHA_FIT	= BIT11,
	MECHA_RJT	= BIT12,
	MECHA_CPT	= BIT13,
	MECHA_BV	= BIT14,
	MECHA_CA_ALL	= ( MECHA_CA1 | MECHA_CA2 | MECHA_CA3 | MECHA_CA4 | MECHA_CA5 | MECHA_CA6 ),
	MECHA_UPPER		= ( MECHA_PAC | MECHA_ESC | MECHA_RSV | MECHA_SEP ),
	MECHA_RJT_BIN	= ( MECHA_FIT | MECHA_RJT | MECHA_CPT ),
	MECHA_BUNCH	= BIT15,
	MECHA_NOTHING	= 0
};
typedef	USHORT	MECHA_PLACE;
/*--------------------------------------------------------------------------*/
/*	PLACE_NO																*/
/*	Rev.(ZZ02:BRZ-007)														*/
/*	Rev.(ZZ05:BRZ-190)	The label addition for six cassettes				*/
/*	Rev.(ZY02:BRZ-452)	The label addition P_NO_TOP							*/
/*	Rev.(AA18:BRZ-1393)	The label addition P_NOTHING						*/
/*--------------------------------------------------------------------------*/
enum
{
	P_NO_TOP= 0x00,
	P_CA1	= 0x00,
	P_CA2	= 0x01,
	P_CA3	= 0x02,
	P_CA4	= 0x03,
	P_CA5	= 0x04,
	P_CA6	= 0x05,
	P_CA_END= 0x06,
	P_PAC	= 0x06,
	P_ESC	= 0x07,
	P_RSV	= 0x08,
	P_SEP	= 0x09,
	P_SHT	= 0x0A,
	P_FIT	= 0x0B,
	P_RJT	= 0x0C,
	P_CPT	= 0x0D,
	P_NO_END	= 0x0E,
	P_UPPER	= 0x0E,
	P_NOTHING	= 0xFF
};
typedef	UCHAR	PLACE_NO;
/*--------------------------------------------------------------------------*/
/*	EXT_MECHA_PLACE															*/
/*	Rev.(ZZ07:BRZ-350)	add EXT_MECHA_PLACE									*/
/*	Rev.(ZY01:BRZ-432)														*/
/*	add EXT_MECHA_UPPER,EXT_MECHA_REJECT_BIN								*/
/*		EXT_MECHA_LOWER,EXT_MECHA_LOWER_TRANSPORT							*/
/*	Rev.(ZW03:BRZ-773)	add EXT_MECHA_BV									*/
/*	Rev.(ZW06:BRZ-895)	add EXT_MECHA_BEFORE_BV,EXT_MECHA_UNDER_REJECT.		*/
/*	Rev.(ZV01:BRZ-912)	add EXT_MECHA_TOP_TRANSPORT.						*/
/*	Rev.(ZV02:BRZ-920)	add EXT_MECHA_INTERLOCK.							*/
/*	Rev.(ZV05:BRZ-982)	add EXT_MECHA_CA_ALL.								*/
/*	Rev.(AA04:BRZ-1183)	add EXT_MECHA_CAx_FEED.								*/
/*--------------------------------------------------------------------------*/
enum
{
	EXT_MECHA_CA1			= BIT0,
	EXT_MECHA_CA2			= BIT1,
	EXT_MECHA_CA3			= BIT2,
	EXT_MECHA_CA4			= BIT3,
	EXT_MECHA_CA5			= BIT4,
	EXT_MECHA_CA6			= BIT5,
	EXT_MECHA_PAC_INSERT	= BIT6,
	EXT_MECHA_ESC			= BIT7,
	EXT_MECHA_RSV			= BIT8,
	EXT_MECHA_SEP			= BIT9,
	EXT_MECHA_SHT			= BIT10,
	EXT_MECHA_FIT			= BIT11,
	EXT_MECHA_RJT			= BIT12,
	EXT_MECHA_CPT			= BIT13,
	EXT_MECHA_PAC_LENGTH	= BIT14,
	EXT_MECHA_PAC_RELEASE	= BIT15,
	EXT_MECHA_PAC_EMPTY		= BIT16,
	EXT_MECHA_PAC_JOIN		= BIT17,
	EXT_MECHA_TRANSPORT		= BIT18,

	EXT_MECHA_PAC_FRONT		= ( EXT_MECHA_PAC_LENGTH| EXT_MECHA_PAC_RELEASE ),
	EXT_MECHA_PAC_REAR		= ( EXT_MECHA_PAC_EMPTY	| EXT_MECHA_PAC_JOIN ),

	EXT_MECHA_UPPER				= ( EXT_MECHA_PAC_INSERT  | EXT_MECHA_PAC_LENGTH |
									EXT_MECHA_PAC_RELEASE | EXT_MECHA_PAC_EMPTY  |
									EXT_MECHA_PAC_JOIN    | EXT_MECHA_ESC		 |
									EXT_MECHA_RSV         | EXT_MECHA_SEP
								  ),
	EXT_MECHA_REJECT_BIN		= ( EXT_MECHA_FIT | EXT_MECHA_RJT | EXT_MECHA_CPT ),
	EXT_MECHA_LOWER				= BIT19,
	EXT_MECHA_LOWER_TRANSPORT	= BIT20,
	EXT_MECHA_BEFORE_BV			= BIT21,
	EXT_MECHA_UNDER_REJECT		= BIT22,
	EXT_MECHA_TOP_TRANSPORT		= BIT23,
	EXT_MECHA_BV				= BIT24,
	EXT_MECHA_CA1_FEED			= BIT25,
	EXT_MECHA_CA2_FEED			= BIT26,
	EXT_MECHA_CA3_FEED			= BIT27,
	EXT_MECHA_CA4_FEED			= BIT28,
	EXT_MECHA_CA5_FEED			= BIT29,
	EXT_MECHA_CA6_FEED			= BIT30,
	
	EXT_MECHA_CA_ALL		= ( EXT_MECHA_CA1 | EXT_MECHA_CA2 | EXT_MECHA_CA3 |
								EXT_MECHA_CA4 | EXT_MECHA_CA5 | EXT_MECHA_CA6 |
								EXT_MECHA_CA1_FEED | EXT_MECHA_CA2_FEED | EXT_MECHA_CA3_FEED |
								EXT_MECHA_CA4_FEED | EXT_MECHA_CA5_FEED | EXT_MECHA_CA6_FEED
							  ),
	EXT_MECHA_INTERLOCK			= BIT31,

	EXT_MECHA_NOTHING		= 0
};
typedef	ULONG	EXT_MECHA_PLACE;
/*--------------------------------------------------------------------------*/
/*																			*/
/*	Response Define															*/
/*																			*/
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/*	INT_END_FACTOR															*/
/*--------------------------------------------------------------------------*/
enum
{
	/*----------------------------------------------------------------------*/
	/*	LEVEL3(BIT30-BIT28)			Hard Stop								*/
	/*----------------------------------------------------------------------*/
	IEF_JAM			 		= BIT30,
	IEF_ILLEGAL		 		= BIT29,
	/*----------------------------------------------------------------------*/
	/*	LEVEL2(BIT27-BIT16)			Light Stop								*/
	/*	Rev.(ZZ06:BRZ-285)													*/
	/*	Different denominations number-of-sheets over is added.				*/
	/*	Rev.(ZY05:BRZ-610)													*/
	/*	Outside bill number-of-sheets exaggerated correspondence for payment*/
	/*	Rev.(ZV08:BRZ-1005)													*/
	/*	-add IEF_HALF_NOTE													*/
	/*	Rev.(AA18:BRZ-1395)													*/
	/*	-add IEF_BV_UNIT_NG													*/
	/*----------------------------------------------------------------------*/
	IEF_EMPTY		 		= BIT27,
	IEF_HALT		 		= BIT26,
	IEF_NOT_RECOGNIZED_OVER	= BIT25,
	IEF_COUNTERFEIT	 		= BIT24,
	IEF_FULL_STOP	 		= BIT23,
	IEF_COMPLETE_STOP		= BIT22,
	IEF_DIFFERENT_OVER		= BIT21,
	IEF_DAMAGED_OVER		= BIT20,			/* Un-supporting.			*/
	IEF_OUTSIDE_OVER		= BIT19,
	IEF_HALF_NOTE			= BIT18,
	IEF_BV_UNIT_NG			= BIT17,
	/*----------------------------------------------------------------------*/
	/*	LEVEL1(BIT15-BIT12)			Retry Factor & Error					*/
	/*	Rev.(ZZ06:BRZ-220)	add IEF_ROTARY_RETRY.							*/
	/*----------------------------------------------------------------------*/
	IEF_EMPTY_RETRY			= BIT15,
	IEF_FEED_RETRY	 		= BIT14,
	IEF_SKEW_RETRY			= BIT13,
	IEF_ROTARY_RETRY 		= BIT12,
	/*----------------------------------------------------------------------*/
	/*	LEVEL0(BIT11-BIT0)			Retry Factor							*/
	/*	Rev.(ZZ02:BRZ-003)													*/
	/*	-add IEF_ADJUST_ESC													*/
	/*	Rev.(ZZ06:BRZ-285)													*/
	/*	-add IEF_VALIDATE_AGAIN												*/
	/*	Rev.(ZY01:BRZ-428)													*/
	/*	Rev.(ZY01:BRZ-428)													*/
	/*	Rev.(ZV02:BRZ-919)													*/
	/*	-add IEF_TROUBLE_NOTE	(Delete IEF_VALIDATE_AGAIN)					*/
	/*	Rev.(ZV07:BRZ-989)													*/
	/*	-Delete factor according to place.( Adjust / Compress )				*/
	/*	Rev.(ZU03:BRZ-1050)													*/
	/*	-add IEF_CURRENT_STOP												*/
	/*	Rev.(AA06:BRZ-1246)													*/
	/*	-add IEF_FOREIGN_OBJECT												*/
	/*----------------------------------------------------------------------*/
	IEF_TROUBLE_NOTE		= BIT11,
	IEF_BV_SOIL		 		= BIT10,
	IEF_CURRENT_STOP 		= BIT9,
	IEF_FOREIGN_OBJECT 		= BIT8,
	IEF_ADJUST_STOP	 		= BIT1,
	IEF_COMPRESS_STOP 		= BIT0
};
typedef	ULONG				INT_END_FACTOR;
	/*----------------------------------------------------------------------*/
	/*	Rev.(ZZ04:BRZ-186)													*/
	/*	-add INT_END_LEVEL2_ERR												*/
	/*	Rev.(ZZ06:BRZ-242)	change value of INT_END_LEVELx.					*/
	/*	Rev.(ZZ06:BRZ-285)													*/
	/*	Different denominations number-of-sheets over(BIT21) is added.		*/
	/*	->INT_END_LEVEL2_ERROR								 				*/
	/*	Rev.(ZY05:BRZ-610)													*/
	/*	Outside bill number-of-sheets exaggerated correspondence for payment*/
	/*	->INT_END_LEVEL2_ERROR(BIT19)						 				*/
	/*	Rev.(ZV07:BRZ-989)	Delete label.( Adjust / Compress )				*/
	/*	Rev.(ZV08:BRZ-1005)	Add half note detection.( INT_END_LEVEL2_ERR )	*/
	/*	Rev.(ZT02:BRZ-1120)	add full stop in level2 error					*/
	/*	Rev.(AA18:BRZ-1395)	Add BV unit NG in level2 error.					*/
	/*----------------------------------------------------------------------*/
#define	INT_END_LEVEL3		( BIT30 | BIT29  | BIT28 )
#define	INT_END_LEVEL2		( BIT27 | BIT26 | BIT25 | BIT24 |\
							  BIT23 | BIT22 | BIT21 | BIT20 |\
							  BIT19 | BIT18 | BIT17 | BIT16 )
#define	INT_END_LEVEL2_ERR	( BIT25 | BIT24 | BIT23 | BIT21 |\
							  BIT20 | BIT19 | BIT18 | BIT17 )
#define	INT_END_LEVEL1		( BIT15 | BIT14 | BIT13 | BIT12 )
#define	INT_END_LEVEL0		( BIT11 | BIT10 | BIT9  | BIT8  |\
							  BIT7  | BIT6  | BIT5  | BIT4  |\
							  BIT3  | BIT2  | BIT1  | BIT0 )
/*--------------------------------------------------------------------------*/
/*	JOB_END_FACTOR															*/
/*	Rev.(ZZ06:BRZ-285)	add JOB_BAD_BILL_FEED.								*/
/*	Rev.(ZY01:BRZ-409)	add MOVE_END_FACTOR label.							*/
/*	Rev.(ZY01:BRZ-426)	add JOB_ABORT_END label.							*/
/*	Rev.(ZY02:BRZ-459)	add MOVE_DEST_ERR label.							*/
/*--------------------------------------------------------------------------*/
enum
{
	/*----------------------------------------------------------------------*/
	/*	task_job setup.(BIT0 - BIT15)										*/
	/*----------------------------------------------------------------------*/
	JOB_MECHA_ERR		= BIT0,
	JOB_FULL_ERR		= BIT1,
	JOB_NONE_FEED		= BIT2,
	JOB_TIMEOUT_CLOSE	= BIT3,
	JOB_BAD_BILL_FEED	= BIT4,
	JOB_ABORT_END		= BIT5,
	/*----------------------------------------------------------------------*/
	/*	task_move setup.(BIT16 - BIT31)										*/
	/*----------------------------------------------------------------------*/
	MOVE_TDCM_ERR		= BIT16,
	MOVE_BV_ERR			= BIT17,
	MOVE_DEST_ERR		= BIT18
};
typedef	ULONG	JOB_END_FACTOR;
/*--------------------------------------------------------------------------*/
/*	MEDIA_CHECK_VALUE														*/
/*--------------------------------------------------------------------------*/
enum
{
	MEDIA_NONE_REMAIN = 0x00,
	MEDIA_REMAIN	 = 0x01,
	MEDIA_RETRY_ERR	 = 0x02,
	MEDIA_MECHA_ERR	 = 0xFF
};
typedef	UCHAR	MEDIA_CHECK_VALUE;
/*--------------------------------------------------------------------------*/
/*	MECHA_END_VALUE															*/
/*--------------------------------------------------------------------------*/
enum
{
	MECHA_END_OK		= 0x00,
	MECHA_END_NG		= 0xFF,
	MECHA_END_STOP		= 0x01,
	MECHA_END_MEDIA		= 0x02,
	MECHA_END_TIMEOUT	= 0x03
	};
typedef	UCHAR	MECHA_END_VALUE;
/*--------------------------------------------------------------------------*/
/*	EXT_BOOL																*/
/*	Rev.(ZZ06:BRZ-285)	add extension bool type.							*/
/*--------------------------------------------------------------------------*/
enum
{
	EXT_FALSE			= 0x00,
	EXT_TRUE			= 0x01,
	EXT_UNSETTLED		= 0x02
};
typedef	ULONG	EXT_BOOL;
/*--------------------------------------------------------------------------*/
/*																			*/
/*	Request Define															*/
/*																			*/
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/*	TASK_MSG																*/
/*	Rev(ZZ03:BRZ-053)														*/
/*	add TASK_IO_LIMIT_TIMEUP												*/
/*	Rev(ZZ04:BRZ-128)														*/
/*	add TASK_CMD_HALT_RECEPTION,TASK_LINE_SEND_END							*/
/*	Rev(ZZ04:BRZ-143)														*/
/*	add TASK_LINE_SEND_xxx_REQUEST,TASK_LINE_SEND_xxx_END					*/
/*	Rev(ZZ04:BRZ-179)														*/
/*	add TASK_RESP_REQUEST_PROGRESS,TASK_RESP_END_PROGRESS					*/
/*	Rev(ZZ05:BRZ-189)														*/
/*	Rev(ZZ05:BRZ-206)	change label name.									*/
/*	( TASK_RESP_REQUEST_BETWEEN  -> TASK_RESP_REQUEST_PROGRESS )			*/
/*	( TASK_RESP_REQUEST_PROGRESS -> TASK_RESP_REQUEST_INTERVAL )			*/
/*	( TASK_RESP_END_BETWEEN      -> TASK_RESP_END_PROGRESS )				*/
/*	Rev(ZZ06:BRZ-237)														*/
/*	add TASK_LAN_TIME_OUT_SEND												*/
/*	Rev(ZZ06:BRZ-240)														*/
/*	add TASK_BV_RECEPTION_RESET,TASK_BV_RECEPTION_RESET_ERROR				*/
/*	Rev.(ZZ06:BRZ-321)														*/
/*	add TASK_LINE_RECEPTION_ERROR											*/
/*	Rev.(ZZ07:BRZ-340)														*/
/*	add TASK_STOP_REQUEST													*/
/*	Rev.(ZY01:BRZ-419)														*/
/*	add TASK_WATCH_MACHINE_TYPE												*/
/*	Rev.(ZY01:BRZ-421)														*/
/*	add TASK_RAS_RECEPTION													*/
/*	Rev.(ZY04:BRZ-566)														*/
/*	add TASK_RESP_REQUEST_DIVISION,TASK_RESP_END_DIVISION					*/
/*	Rev.(ZY06:BRZ-675)														*/
/*	add TASK_IO_REQUEST_SO													*/
/*	Rev.(ZY06:BRZ-684)														*/
/*	add TASK_WATCH_DISPENSE_ENABLE,TASK_WATCH_DISPENSE_DISABLE				*/
/*	Rev.(ZW01:BRZ-711)														*/
/*	add TASK_BV_TIMEUP_COMMAND												*/
/*	Rev.(ZT02:BRZ-1110)														*/
/*	add TASK_MECHA_WAIT_ALMIGHTY											*/
/*	Rev.(AA04:BRZ-1191)														*/
/*	add TASK_MECHA_REQUEST_ABORT_MOVE										*/
/*	Rev.(AA04:BRZ-1207)														*/
/*	add TASK_BV_RECEPTION_VD_ERROR											*/
/*--------------------------------------------------------------------------*/
enum
{
	TASK_NORMAL_END					= 0x00,
	TASK_UNUSUAL_END				= 0xFF,
	TASK_STOP_REQUEST				= 0x0F,
	TASK_LINE_RECEPTION				= 0x10,
	TASK_LINE_RETURN_BUF			= 0x11,
	TASK_LINE_SEND_REQUEST			= 0x12,
	TASK_LINE_SEND_END				= 0x13,
	TASK_LINE_RECEPTION_ERROR		= 0x1F,
	TASK_RESP_REQUEST_LAST			= 0x14,
	TASK_RESP_REQUEST_PROGRESS		= 0x15,
	TASK_RESP_END_LAST				= 0x16,
	TASK_RESP_END_PROGRESS			= 0x17,
	TASK_RESP_REQUEST_INTERVAL		= 0x18,
	TASK_RESP_REQUEST_DIVISION		= 0x19,
	TASK_RESP_END_DIVISION			= 0x1A,
	TASK_MOVE_REQUEST				= 0x20,
	TASK_MOVE_ERROR					= 0x21,
	TASK_IO_REQUEST_INSERT			= 0x30,
	TASK_IO_REQUEST_PRESENT			= 0x31,
	TASK_IO_LIMIT_TIMEUP			= 0x32,
	TASK_IO_REQUEST_SC				= 0x33,
	TASK_IO_REQUEST_SO				= 0x34,
	TASK_MECHA_REQUEST				= 0x40,
	TASK_MECHA_WAIT					= 0x41,
	TASK_MECHA_STATUS				= 0x42,
	TASK_MECHA_WAIT_ALMIGHTY		= 0x43,
	TASK_MECHA_REQUEST_ABORT_MOVE	= 0x44,
	TASK_BV_REQUEST					= 0x50,
	TASK_BV_INITIALIZE				= 0x51,
	TASK_BV_RECEPTION				= 0x52,
	TASK_BV_RECEPTION_VD			= 0x53,
	TASK_BV_RECEPTION_SENSOR		= 0x54,
	TASK_BV_RECEPTION_VALIDATE_START= 0x55,
	TASK_BV_RECEPTION_VALIDATE_ERROR= 0x56,
	TASK_BV_RECEPTION_VALIDATE_STOP	= 0x57,
	TASK_BV_RECEPTION_ERROR			= 0x58,
	TASK_BV_RESET					= 0x59,
	TASK_BV_RECEPTION_RESET			= 0x5A,
	TASK_BV_RECEPTION_RESET_ERROR	= 0x5B,
	TASK_BV_TIMEUP_COMMAND			= 0x5C,
	TASK_BV_RECEPTION_VD_ERROR		= 0x5D,
	TASK_CMD_DEBUG					= 0x60,
	TASK_CMD_HALT_RECEPTION			= 0x61,
	TASK_LAN_RECEPTION				= 0x70,
	TASK_LAN_RETURN_BUF				= 0x71,
	TASK_LAN_REQUEST				= 0x72,
	TASK_LAN_REQUEST_TEST			= 0x73,
	TASK_LAN_TIME_OUT_SEND			= 0x74,
	TASK_WATCH_START				= 0x80,
	TASK_WATCH_STOP					= 0x81,
	TASK_WATCH_SNS_ON				= 0x82,
	TASK_WATCH_SNS_OFF				= 0x83,
	TASK_WATCH_LOWER_ON				= 0x84,
	TASK_WATCH_LOWER_OFF			= 0x85,
	TASK_WATCH_MACHINE_TYPE			= 0x86,
	TASK_WATCH_DISPENSE_ENABLE		= 0x87,
	TASK_WATCH_DISPENSE_DISABLE		= 0x88,
	TASK_JOB_REQUEST				= 0x90,
	TASK_JOB_REQUEST_CLEAR_JAM		= 0x91,
	TASK_JOB_REQUEST_CHECK_TRANSPORT= 0x92,
	TASK_JOB_REQUEST_CONFIRM_MECHA	= 0x93,
	TASK_JOB_REQUEST_CLOSE_SHT		= 0x94,
	TASK_JOB_REQUEST_INSERT			= 0x95,
	TASK_JOB_REQUEST_PRESENT		= 0x96,
	TASK_JOB_REQUEST_FEED			= 0x97,
	TASK_RAS_REQUEST				= 0xA0,
	TASK_RAS_ABORT					= 0xA1,
	TASK_RAS_REQUEST_RESPONSE		= 0xA2,
	TASK_INTERRUPT					= 0xE0
};
typedef	UCHAR	TASK_MSG;

/*--------------------------------------------------------------------------*/
/*	MECHA_ORDER																*/
/*	Rev(ZZ06:BRZ-273)														*/
/*	MECHA_CA_BILL_STAY_CLEAR / MECHA_CA_CHECK_IMPELLER deletion				*/
/*	MECHA_CA_PHASE_ADJUST_FEEDING deletion									*/
/*	Rev.(ZZ07:BRZ-368)														*/
/*	The order for PAC taking-in operation of a restoration system is added.	*/
/*	:MECHA_UPPER_TAKE_BILL													*/
/*	:MECHA_SUB_PAC_ADJUST_MOVE												*/
/*	Rev.(ZY03:BRZ-515)														*/
/*	:MECHA_UPPER_TRANSPORT_CLEAR											*/
/*	Rev.(ZY03:BRZ-516)														*/
/*	:MECHA_CHECK_EMPTY														*/
/*	Rev.(ZY04:BRZ-584)														*/
/*	:MECHA_UPPER_PREPARE_PATH_CLEAR											*/
/*	Rev.(ZY06:BRZ-676)														*/
/*	:MECHA_UPPER_AUTO_PRESENT												*/
/*	Rev.(ZW01:BRZ-706)														*/
/*	:MECHA_UPPER_PRE_DRAW_BILL												*/
/*	Rev.(ZW03:BRZ-759)														*/
/*	:MECHA_CA_AFTER_STACK													*/
/*	Rev.(ZW04:BRZ-834)														*/
/*	:MECHA_DEPRESS															*/
/*	Rev.(ZW04:BRZ-877)														*/
/*	:MECHA_MORE_PRESS														*/
/*	Rev.(ZV05:BRZ-962)														*/
/*	:MECHA_UPPER_MORE_DISCHARGE												*/
/*	Rev.(ZU03:BRZ-1029)														*/
/*	:MECHA_UPPER_TAKE_IN													*/
/*	Rev.(ZU03:BRZ-1038)														*/
/*	:MECHA_UPPER_CHECK_REMAIN_PAC											*/
/*	Rev.(AA05:BRZ-1224)														*/
/*	:MECHA_UPPER_RELEASE_EJECT												*/
/*	Rev.(AA09:BRZ-1280)														*/
/*	:MECHA_UPPER_PRE_DRAW_BILL_SC											*/
/*	:MECHA_UPPER_DRAW_BILL_SC												*/
/*	Rev.(AA10:BRZ-1290)														*/
/*	:MECHA_UPPER_ESCAPE														*/
/*	Rev.(AA11:BRZ-1308)														*/
/*	:MECHA_UPPER_PREPARE_FEED_SEP											*/
/*	:MECHA_UPPER_ESCAPE_CLAMP												*/
/*	:MECHA_UPPER_PRESS_CLAMP												*/
/*	:MECHA_UPPER_PRE_RELEASE_CARRIER										*/
/*	:MECHA_UPPER_RELEASE_ESC												*/
/*	:MECHA_UPPER_STACK_ESC													*/
/*	Rev.(AA16:BRZ-1365)														*/
/*	:Deletion	MECHA_UPPER_BEFORE_MR										*/
/*	Rev.(AA19:BRZ-1405)														*/
/*	:add	MECHA_UPPER_LAST_DISCHARGE										*/
/*	Rev.(AA16:BRZ-1406)														*/
/*	:add	MECHA_UPPER_PREPARE_IDLE										*/
/*	Rev.(AA36:BRZ-1497)														*/
/*	:add	MECHA_RECOVERY_ADJUST_FEEDING									*/
/*	Rev.(AA46:BRZ-1533)														*/
/*	:add	MECHA_CA_BILL_REMOVAL											*/
/*	Rev.(AA48:BRZ-1540)														*/
/*	:add	MECHA_UPPER_DRAW_BILL_NON_HOOK									*/
/*	:del	MECHA_UPPER_DRAW_BILL_NON_HOOK									*/
/*	Rev.(AA49:BRZ-1543)														*/
/*	:add	MECHA_SHT_CLOSE_COMPULSORY										*/
/*--------------------------------------------------------------------------*/
enum
{
	MECHA_ORDER_NONE			= 0x0000,
	MECHA_PREPARE_FEED			= 0x0001,
	MECHA_PREPARE_STACK			= 0x0002,
	MECHA_CONFIRM_MOVEMENT		= 0x0003,
	MECHA_ADJUST_FEEDING		= 0x0004,
	MECHA_PRESS					= 0x0005,
	MECHA_SLEEP					= 0x0006,
	MECHA_ADJUST_STACK			= 0x0007,
	MECHA_CHECK_EMPTY			= 0x0008,		/* Rev.(ZY03:BRZ-516) add	*/
	MECHA_DEPRESS				= 0x0009,		/* Rev.(ZW04:BRZ-834) add	*/
	MECHA_MORE_PRESS			= 0x000A,		/* Rev.(ZW04:BRZ-877) add	*/
	MECHA_RECOVERY_ADJUST_FEEDING = 0x000B,		/* Rev.(AA36:BRZ-1497) add	*/
	MECHA_ADJUST_FEEDING_DETACHED = 0x000C,		/* Rev.(AA44:BRZ-1527) add	*/
	MECHA_CA_COMPRESS			= 0x0010,
	MECHA_CA_FEW_DOWN			= 0x0011,
	MECHA_CA_AFTER_STACK		= 0x0012,
	MECHA_CA_AFTER_STACK_DETACHED = 0x0013,		/* Rev.(AA44:BRZ-1527) add	*/
	MECHA_CA_BILL_REMOVAL 		= 0x0014,		/* Rev.(AA46:BRZ-1533) add	*/
	MECHA_UPPER_PREPARE_INSERT	= 0x0020,
	MECHA_UPPER_DRAW_BILL		= 0x0021,
	MECHA_UPPER_TAKE_BILL		= 0x002F,		/* Rev.(ZZ07:BRZ-368) add	*/
	MECHA_UPPER_MOVE_BILL		= 0x0022,
	MECHA_UPPER_PAY_BILL		= 0x0023,		/* Rev.(ZZ03:BRZ-074) add	*/
	MECHA_UPPER_REPAY_BILL		= 0x0024,
	MECHA_UPPER_DISCHARGE_BILL	= 0x0025,
	MECHA_UPPER_COLLECT_BILL	= 0x0026,		/* Rev.(ZZ03:BRZ-070) add	*/
	MECHA_UPPER_EJECT_BILL		= 0x0027,		/* Rev.(ZZ03:BRZ-075) add	*/
	MECHA_UPPER_HOME			= 0x0028,
	MECHA_UPPER_MOVE_BILL_ALWAYS= 0x0029,		/* Rev.(ZZ03:BRZ-064) add	*/
	MECHA_UPPER_REPAY_BILL_ALWAYS= 0x002A,		/* Rev.(ZZ07:BRZ-355) add	*/
	MECHA_UPPER_TRANSPORT_CLEAR	= 0x002B,		/* Rev.(ZY03:BRZ-515) add	*/
	MECHA_UPPER_PREPARE_PATH_CLEAR= 0x002C,		/* Rev.(ZY04:BRZ-584) add	*/
	MECHA_UPPER_REPAY_BILL_CHECK= 0x002D,
	MECHA_UPPER_AUTO_PRESENT	= 0x002E,
	MECHA_SHT_OPEN				= 0x0030,
	MECHA_SHT_CLOSE				= 0x0031,
	MECHA_SHT_CLOSE_COMPULSORY	= 0x0032,		/* Rev.(AA49:BRZ-1543) add	*/
	MECHA_UPPER_PRE_DRAW_BILL	= 0x0040,		/* Rev.(ZW01:BRZ-706) add	*/
	MECHA_UPPER_MORE_DISCHARGE	= 0x0041,		/* Rev.(ZV05:BRZ-962) add	*/
	MECHA_UPPER_TAKE_IN			= 0x0042,		/* Rev.(ZU03:BRZ-1029) add	*/
	MECHA_UPPER_CHECK_REMAIN_PAC= 0x0043,		/* Rev.(ZU03:BRZ-1038) add	*/
	MECHA_UPPER_RELEASE_EJECT	= 0x0044,		/* Rev.(AA05:BRZ-1224) add	*/
	MECHA_UPPER_PRE_DRAW_BILL_SC= 0x0045,		/* Rev.(AA09:BRZ-1280) add	*/
	MECHA_UPPER_DRAW_BILL_SC	= 0x0046,		/* Rev.(AA09:BRZ-1280) add	*/
	MECHA_UPPER_ESCAPE			= 0x0047,
	MECHA_UPPER_PREPARE_FEED_SEP= 0x0048,		/* Rev.(AA11:BRZ-1308) add	*/
	MECHA_UPPER_ESCAPE_CLAMP	= 0x0049,		/* Rev.(AA11:BRZ-1308) add	*/
	MECHA_UPPER_PRESS_CLAMP		= 0x004A,		/* Rev.(AA11:BRZ-1308) add	*/
	MECHA_UPPER_PRE_RELEASE_CARRIER	= 0x004B,	/* Rev.(AA11:BRZ-1308) add	*/
	MECHA_UPPER_RELEASE_ESC		= 0x004C,		/* Rev.(AA11:BRZ-1308) add	*/
	MECHA_UPPER_STACK_ESC		= 0x004D,		/* Rev.(AA11:BRZ-1308) add	*/
	MECHA_UPPER_BEFORE_SO		= 0x004E,		/* Rev.(AA13:BRZ-1339) add	*/
	MECHA_UPPER_LAST_DISCHARGE	= 0x004F,		/* Rev.(AA19:BRZ-1405) add	*/
	MECHA_UPPER_PREPARE_IDLE	= 0x0050,		/* Rev.(AA19:BRZ-1406) add	*/
	/*----------------------------------------------------------------------*/
	/*	SIDE ORDER															*/
	/*	Rev.(ZZ03:BRZ-036)	add	Order for PreAcceptor & Separator			*/
	/*----------------------------------------------------------------------*/
		/*------------------------------------------------------------------*/
		/*	for Cassette													*/
		/*	Rev.(ZZ03:BRZ-081)	Label name change							*/
		/*	Rev.(ZY06:BRZ-677)	add MECHA_SUB_CA_TRANSPORT_LEVEL_SET		*/
		/*	Rev.(ZT06:BRZ-1130)												*/
		/*	add MECHA_SUB_CA_STAGE_DOWN_STACK_2ND							*/
		/*	add MECHA_SUB_CA_STAGE_DOWN_STACK_3RD							*/
		/*	Rev.(AA23:BRZ-1453)												*/
		/*	add MECHA_SUB_CA_STAGE_UP_PRESS_SET								*/
		/*------------------------------------------------------------------*/
	MECHA_SUB_CA_STAGE_UP_PRESS				= 0x1001,
	MECHA_SUB_CA_STAGE_UP_TOP				= 0x1002,
	MECHA_SUB_CA_STAGE_UP_FEW				= 0x1003,
	MECHA_SUB_CA_STAGE_DOWN_STACK			= 0x1004,
	MECHA_SUB_CA_STAGE_DOWN_LEVEL			= 0x1005,
	MECHA_SUB_CA_TRANSPORT_LEVEL_SET		= 0x1006,
	MECHA_SUB_CA_STAGE_DOWN_STACK_2ND		= 0x1007,
	MECHA_SUB_CA_STAGE_DOWN_STACK_3RD		= 0x1008,
	MECHA_SUB_CA_STAGE_UP_PRESS_SET			= 0x1009,
		/*------------------------------------------------------------------*/
		/*	for PreAcceptor													*/
		/*	Rev.(ZZ03:BRZ-065)	MOVE_BILL is divided into two.  			*/
		/*	Rev.(ZZ06:BRZ-301)												*/
		/*	addtion order													*/
		/*	:MECHA_SUB_PAC_BEFORE_REPAY_BILL								*/
		/*	:MECHA_SUB_PAC_PREPARE_REPAY_BILL								*/
		/*	Rev.(ZZ06:BRZ-329)												*/
		/*	addtion order													*/
		/*	:MECHA_SUB_PAC_BEFORE_PAY_BILL									*/
		/*	Rev.(ZY01:BRZ-422)												*/
		/*	addtion order													*/
		/*	:MECHA_SUB_PAC_CHECK_LENGTH_EJECT								*/
		/*	Rev.(ZW01:BRZ-706)												*/
		/*	addtion order													*/
		/*	:MECHA_SUB_PAC_PRE_CHECK_LENGTH_EJECT							*/
		/*	Rev.(ZT06:BRZ-1133)												*/
		/*	addtion order													*/
		/*	:MECHA_SUB_PAC_BILL_TAKE_IN										*/
		/*	Rev.(AA06:BRZ-1250)												*/
		/*	addtion order													*/
		/*	:MECHA_SUB_PAC_JOIN_BUNCH										*/
		/*	Rev.(AA07:BRZ-1259)												*/
		/*	addtion order													*/
		/*	:MECHA_SUB_PAC_PSXS_ON_DRAW_BILL								*/
		/*	Rev.(AA48:BRZ-1540)												*/
		/*	addtion order													*/
		/*	:MECHA_SUB_PAC_MOVE_NON_HOOK									*/
		/*------------------------------------------------------------------*/
	MECHA_SUB_PAC_JOIN						= 0x1101,
	MECHA_SUB_PAC_PREPARE_MOVE				= 0x1102,	/* Rev.(ZZ03:BRZ-065)	*/
	MECHA_SUB_PAC_MOVE						= 0x1103,	/* Rev.(ZZ03:BRZ-065)	*/
	MECHA_SUB_PAC_BEFORE_REPAY_BILL			= 0x1104,	/* Rev.(ZZ06:BRZ-301)	*/
	MECHA_SUB_PAC_PREPARE_REPAY_BILL		= 0x1105,	/* Rev.(ZZ06:BRZ-301)	*/
	MECHA_SUB_PAC_MOVE_NON_HOOK				= 0x1108,	/* Rev.(AA48:BRZ-1540)	*/
	MECHA_SUB_PAC_PSXS_ON_DRAW_BILL			= 0x1109,	/* Rev.(AA07:BRZ-1259)	*/
	MECHA_SUB_PAC_JOIN_BUNCH				= 0x110A,	/* Rev.(AA06:BRZ-1250)	*/
	MECHA_SUB_PAC_BILL_TAKE_IN				= 0x110B,	/* Rev.(ZT06:BRZ-1133)	*/
	MECHA_SUB_PAC_PRE_CHECK_LENGTH_EJECT	= 0x110C,	/* Rev.(ZW01:BRZ-706)	*/
	MECHA_SUB_PAC_CHECK_LENGTH_EJECT		= 0x110D,	/* Rev.(ZY01:BRZ-422)	*/
	MECHA_SUB_PAC_ADJUST_MOVE				= 0x110E,	/* Rev.(ZZ07:BRZ-368)	*/
	MECHA_SUB_PAC_BEFORE_PAY_BILL			= 0x110F,
			/*--------------------------------------------------------------*/
			/*	for tray													*/
			/*	Rev.(AA24:BRZ-1457)											*/
			/*	addtion order												*/
			/*	:MECHA_SUB_PAC_TRAY_ESCAPE_DERIVARY_POSITION				*/
			/*	Rev.(AA48:BRZ-1531)											*/
			/*	addtion order												*/
			/*	:MECHA_SUB_PAC_TRAY_MOVE_SAVE_POSITION_HIGHSPEED			*/
			/*	:MECHA_SUB_PAC_TRAY_MOVE_RELEASE_POSITION_HIGHSPEED			*/
			/*--------------------------------------------------------------*/
	MECHA_SUB_PAC_TRAY_POSITION_DELIVERY	= 0x1111,
	MECHA_SUB_PAC_TRAY_BEFORE_JOIN			= 0x1112,	/* tray fwd 750step	*/
	MECHA_SUB_PAC_TRAY_PREPARE_JOIN			= 0x1113,	/* tray bwd 583step	*/
	MECHA_SUB_PAC_TRAY_MOVE_RELEASE_POSITION_HIGHSPEED	= 0x111A,	/* Rev.(AA48:BRZ-1531)	*/
	MECHA_SUB_PAC_TRAY_MOVE_SAVE_POSITION_HIGHSPEED		= 0x111B,	/* Rev.(AA48:BRZ-1531)	*/
	MECHA_SUB_PAC_TRAY_ESCAPE_DERIVARY_POSITION = 0x111C,	/* Rev.(AA24:BRZ-1457)	*/
	MECHA_SUB_PAC_TRAY_MOVE_RELEASE_POSITION= 0x111D,	/* Rev.(ZW03:BRZ-782)	*/
	MECHA_SUB_PAC_TRAY_ESCAPE_SAVE_POSITION	= 0x111E,	/* Rev.(ZY04:BRZ-574)	*/
	MECHA_SUB_PAC_TRAY_MOVE_SAVE_POSITION	= 0x111F,
			/*--------------------------------------------------------------*/
			/*	for carrier													*/
			/*	Rev.(ZY01:BRZ-397)											*/
			/*	addtion order												*/
			/*	:MECHA_SUB_PAC_CARRIER_POSITION_0_CHECK						*/
			/*	Rev.(ZW04:BRZ-842)											*/
			/*	addtion order												*/
			/*	:MECHA_SUB_PAC_CARRIER_POSITION_PRE_RELEASE					*/
			/*	Rev.(AA48:BRZ-1531)											*/
			/*	addtion order												*/
			/*	:MECHA_SUB_PAC_CARRIER_HOME_CLAMP_OFF						*/
			/*--------------------------------------------------------------*/
	MECHA_SUB_PAC_CARRIER_POSITION_ESCAPE	= 0x1121,
	MECHA_SUB_PAC_CARRIER_POSITION_SEP		= 0x1122,
	MECHA_SUB_PAC_CARRIER_POSITION_0_CHECK	= 0x1123,
	MECHA_SUB_PAC_CARRIER_POSITION_PRE_RELEASE = 0x1124,
	MECHA_SUB_PAC_CARRIER_MOVE				= 0x1125,
	MECHA_SUB_PAC_CARRIER_HOME_CLAMP_OFF	= 0x1126,		/* Rev.(AA48:BRZ-1531) add	*/
			/*--------------------------------------------------------------*/
			/*	for clamp													*/
			/*	Rev.(ZY04:BRZ-573)											*/
			/*	add order													*/
			/*	:MECHA_SUB_PAC_CLAMP_OFF_DSTOPPER_ON						*/
			/*	Rev.(ZW04:BRZ-795)											*/
			/*	add order													*/
			/*	:MECHA_SUB_PAC_CHECK_CLAMP									*/
			/*	Rev.(AA03:BRZ-1185)											*/
			/*	add order													*/
			/*	:MECHA_SUB_PAC_CLAMP_PRESS_DISCHAGE							*/
			/*--------------------------------------------------------------*/
	MECHA_SUB_PAC_CLAMP_OFF_DSTOPPER_ON		= 0x1131,
	MECHA_SUB_PAC_CHECK_CLAMP				= 0x1132,
	MECHA_SUB_PAC_CLAMP_PRESS_DISCHAGE		= 0x1133,
			/*--------------------------------------------------------------*/
			/*	for D-stopper												*/
			/*	Rev.(ZV08:BRZ-1004)											*/
			/*	add order													*/
			/*	:MECHA_SUB_PAC_DSTOPPER_ESCAPE								*/
			/*	Rev.(AA44:BRZ-1522)											*/
			/*	:MECHA_SUB_PAC_MOVE_3rd										*/
			/*	:MECHA_SUB_PAC_CLAMP_OFF_DSTOPPER_ON_3rd					*/
			/*	:MECHA_SUB_PAC_DSTOPPER_THRUST_CHECK						*/
			/*	:MECHA_SUB_PAC_DSTOPPER_THRUST_CHECK_3rd					*/
			/*	:MECHA_SUB_PAC_JOIN_BUNCH_3rd								*/
			/*	:MECHA_SUB_PAC_BILL_TAKE_IN_3rd								*/
			/*	Rev.(AA48:BRZ-1540)											*/
			/*	:MECHA_SUB_PAC_DRAW_BILL_NON_HOOK							*/
			/*	:MECHA_SUB_PAC_MOVE_NON_HOOK_3rd							*/
			/*--------------------------------------------------------------*/
	MECHA_SUB_PAC_DSTOPPER_ESCAPE				= 0x1141,
	MECHA_SUB_PAC_MOVE_3rd						= 0x1142,
	MECHA_SUB_PAC_CLAMP_OFF_DSTOPPER_ON_3rd		= 0x1143,
	MECHA_SUB_PAC_DSTOPPER_THRUST_CHECK			= 0x1144,
	MECHA_SUB_PAC_DSTOPPER_THRUST_CHECK_3rd		= 0x1145,
	MECHA_SUB_PAC_JOIN_BUNCH_3rd				= 0x1146,
	MECHA_SUB_PAC_BILL_TAKE_IN_3rd				= 0x1147,
	MECHA_SUB_PAC_DRAW_BILL_NON_HOOK			= 0x1148,
	MECHA_SUB_PAC_MOVE_NON_HOOK_3rd				= 0x1149,
			/*--------------------------------------------------------------*/
			/*	for Belt													*/
			/*	Rev.(AA12:BRZ-1330)											*/
			/*	add order													*/
			/*	:MECHA_SUB_PAC_BELT_BACKWARD								*/
			/*	Rev.(AA48:BRZ-1540)											*/
			/*	add order													*/
			/*	:MECHA_SUB_PAC_REMAIN_CHECK_BELT_BACKWARD					*/
			/*--------------------------------------------------------------*/
	MECHA_SUB_PAC_BELT_BACKWARD					= 0x1151,
	MECHA_SUB_PAC_REMAIN_CHECK_BELT_BACKWARD	= 0x1152,
		/*------------------------------------------------------------------*/
		/*	for Separator													*/
		/*	Rev.(ZZ06:BRZ-307)												*/
		/*	Deletion order													*/
		/*	:MECHA_SUB_SEP_ADJUST_CLAMP										*/
		/*	:MECHA_SUB_SEP_PRESS_OFF										*/
		/*	Rev.(ZZ06:BRZ-301)												*/
		/*	addtion order													*/
		/*	:MECHA_SUB_SEP_BEFORE_REPAY_BILL								*/
		/*	Rev.(ZY01:BRZ-394)												*/
		/*	addtion order													*/
		/*	:MECHA_SUB_SEP_BEFORE_BACKFEED									*/
		/*	:MECHA_SUB_SEP_ESCAPE_COMB										*/
		/*	Rev.(ZW03:BRZ-778)												*/
		/*	addtion order													*/
		/*	:MECHA_SUB_SEP_JOIN_FEED										*/
		/*	Rev.(ZW06:BRZ-905)												*/
		/*	addtion order													*/
		/*	:MECHA_SUB_SEP_TAKE_IN											*/
		/*	Rev.(ZV07:BRZ-978)												*/
		/*	addtion order													*/
		/*	:MECHA_SUB_SEP_PUSHER_FEW_DOWN									*/
		/*	Rev.(ZT06:BRZ-1133)												*/
		/*	addtion order													*/
		/*	:MECHA_SUB_SEP_TAKE_IN_DOWN										*/
		/*	Rev.(AA44:BRZ-1522)												*/
		/*	addtion order													*/
		/*	:MECHA_SUB_SEP_STAGE_FEW_DOWN									*/
		/*------------------------------------------------------------------*/
/*	MECHA_SUB_SEP_ADJUST_CLAMP				= 0x1201,	*/
	MECHA_SUB_SEP_DEPRESS					= 0x1202,
/*	MECHA_SUB_SEP_PRESS_OFF					= 0x1203,	*/
	MECHA_SUB_SEP_BEFORE_JOIN				= 0x1204,
	MECHA_SUB_SEP_PREPARE_JOIN				= 0x1205,
	MECHA_SUB_SEP_BEFORE_REPAY_BILL			= 0x1206,
	MECHA_SUB_SEP_BEFORE_BACKFEED			= 0x1207,
	MECHA_SUB_SEP_ESCAPE_COMB				= 0x1208,
	MECHA_SUB_SEP_JOIN_FEED					= 0x1209,
	MECHA_SUB_SEP_TAKE_IN					= 0x120A,
	MECHA_SUB_SEP_PUSHER_FEW_DOWN			= 0x120B,
	MECHA_SUB_SEP_TAKE_IN_DOWN				= 0x120C,
	MECHA_SUB_SEP_STAGE_FEW_DOWN			= 0x120D,
		/*------------------------------------------------------------------*/
		/*	Rev.(ZZ06:BRZ-329)												*/
		/*	addtion order													*/
		/*------------------------------------------------------------------*/
	MECHA_SUB_MOVE_INITAIAL_POSITION		= 0x1301,
		/*------------------------------------------------------------------*/
		/*	Rev.(ZZ07:BRZ-352)												*/
		/*	addtion order													*/
		/*	:MECHA_SUB_PAC_TRAY_MOVE_SAVE_POSITION							*/
		/*------------------------------------------------------------------*/
		/*------------------------------------------------------------------*/
		/*	Rev.(ZW04:BRZ-842)												*/
		/*	addtion order													*/
		/*	:MECHA_SUB_ESC_DOWN_RELEASE										*/
		/*	Rev.(AA08:BRZ-1263)												*/
		/*	addtion order													*/
		/*	:MECHA_SUB_ESC_STOPPER_CHECK									*/
		/*------------------------------------------------------------------*/
	MECHA_SUB_ESC_DOWN_RELEASE				= 0x1401,
	MECHA_SUB_ESC_STOPPER_CHECK				= 0x1402	/* Rev.(AA08:BRZ-1263)	*/
	};
typedef	USHORT	MECHA_ORDER;
/*--------------------------------------------------------------------------*/
/*	MECHA_POSITION															*/
/*	Rev.(ZZ02:BRZ-007)														*/
/*	Rev.(ZZ03:BRZ-043)	add upper part position								*/
/*	Rev.(ZZ03:BRZ-049)														*/
/*	It changes into MECHA_POSI_RELEASE from MECHA_POSI_DISCHAGE				*/
/*	add MECHA_POSI_RELEASE_ESC												*/
/*	add MECHA_POSI_RELEASE_RSV												*/
/*	It changes into MECHA_POSI_TOP from MECHA_POSI_UPPER					*/
/*	add	MECHA_POSI_BOTTOM													*/
/*	Rev.(ZZ03:BRZ-073)														*/
/*	add	MECHA_POSI_INSERT													*/
/*	Rev.(ZZ06:BRZ-261)														*/
/*	add	MECHA_POSI_AFTER_FEED												*/
/*	Rev.(ZZ07:BRZ-383)														*/
/*	add	MECHA_POSI_PAC_BEFORE_EJECT											*/
/*	Rev.(ZY02:BRZ-451)														*/
/*	add	MECHA_POSI_PAC_INITIAL												*/
/*	Rev.(ZW01:BRZ-706)														*/
/*	add	MECHA_POSI_PAC_PRE_CHECK_LENGTH										*/
/*	Rev.(ZW01:BRZ-707)														*/
/*	add	MECHA_POSI_PRESS													*/
/*	Rev.(ZW04:BRZ-834)														*/
/*	add	MECHA_POSI_DEPRESS													*/
/*	Rev.(ZV07:BRZ-978)														*/
/*	add	MECHA_POSI_TOP_FEW_DOWN												*/
/*--------------------------------------------------------------------------*/
enum {
	MECHA_POSI_UNKNOWN		= 0x0000,		/* position uncsetainty			*/
	MECHA_POSI_FEED			= 0x0001,		/* drawing out position			*/
	MECHA_POSI_STACK		= 0x0002,		/* store position				*/
	MECHA_POSI_RELEASE		= 0x0003,		/* release position				*/
	MECHA_POSI_HOME			= 0x0004,		/* home position				*/
	MECHA_POSI_TOP			= 0x0005,		/* top position					*/
	MECHA_POSI_BOTTOM		= 0x0006,		/* lower position				*/
	MECHA_POSI_BELOW_STACK	= 0x0007,		/* below store position			*/
	MECHA_POSI_RELEASE_ESC	= 0x0008,		/* ESC release position			*/
	MECHA_POSI_RELEASE_RSV	= 0x0009,		/* RSV release position			*/
	MECHA_POSI_INSERT		= 0x000A,		/* insert position				*/
	MECHA_POSI_DISCHARGE	= 0x000B,		/* discharge position			*/
	MECHA_POSI_AFTER_FEED	= 0x000C,		/* after feed position			*/
	MECHA_POSI_PRESS		= 0x000D,		/* press position				*/
	MECHA_POSI_DEPRESS		= 0x000E,		/* depress position				*/
	MECHA_POSI_TOP_FEW_DOWN	= 0x000F,		/* depress position				*/
		/*------------------------------------------------------------------*/
		/*	(PreAcceptor Only)												*/
		/*------------------------------------------------------------------*/
	MECHA_POSI_PAC_CHECK_LENGTH	= 0x0010,		/* 		*/
	MECHA_POSI_PAC_PREPARE_MOVE	= 0x0011,		/* 		*/
	MECHA_POSI_PAC_MOVE			= 0x0012,		/* 		*/
	MECHA_POSI_PAC_BEFORE_JOIN	= 0x0013,		/* 		*/
	MECHA_POSI_PAC_PREPARE_JOIN	= 0x0014,		/* 		*/
	MECHA_POSI_PAC_JOIN			= 0x0015,		/* 		*/
	MECHA_POSI_PAC_PRE_DISCHARGE= 0x0016,		/* 		*/
	MECHA_POSI_PAC_BEFORE_EJECT	= 0x0017,		/* before eject position		*/
	MECHA_POSI_PAC_INITIAL		= 0x0018,		/* 		*/
	MECHA_POSI_PAC_PRE_CHECK_LENGTH	= 0x0019,	/* Rev.(ZW01:BRZ-706) add		*/
		/*------------------------------------------------------------------*/
		/*	(Shutter Only)													*/
		/*	Rev.(ZY03:BRZ-XXX)	add position								*/
		/*------------------------------------------------------------------*/
	MECHA_POSI_SHT_OPEN			= 0x0020,	/* shutter open					*/
	MECHA_POSI_SHT_CLOSE		= 0x0021,	/* shutter close				*/
	/*----------------------------------------------------------------------*/
	/*	Cassette Position													*/
	/*----------------------------------------------------------------------*/
		/*------------------------------------------------------------------*/
		/*	Part1 (stage)													*/
		/*------------------------------------------------------------------*/
	MECHA_POSI_CA_FEED		= 0x1001,		/* drawing out position			*/
	MECHA_POSI_CA_STACK		= 0x1002,		/* store position				*/
		/*------------------------------------------------------------------*/
		/*	Part2 (pick roller)												*/
		/*------------------------------------------------------------------*/
	MECHA_POSI_CA_PICK_FEED	= 0x1101,		/* draw position				*/
	MECHA_POSI_CA_PICK_STOP	= 0x1102,		/* rubber position				*/
	/*----------------------------------------------------------------------*/
	/*	PreAcceptor Position												*/
	/*----------------------------------------------------------------------*/
		/*------------------------------------------------------------------*/
		/*	Part1 (tray)													*/
		/*	Rev.(ZZ06:BRZ-308)												*/
		/*	change position													*/
		/*	(MECHA_POSI_PAC_TRAY_PDPC_PLPC->MECHA_POSI_PAC_TRAY_PDPC_PRPC)	*/
		/*(MECHA_POSI_PAC_TRAY_PLPC_PRPC->MECHA_POSI_PAC_TRAY_SAVE_POSITION)*/
		/*	change MECHA_POSI_PAC_TRAY_PDPC_CHECKLENGTH						*/
		/*	add	   MECHA_POSI_PAC_TRAY_CHECKLENGTH_PRPC						*/
		/*	Rev.(ZW04:BRZ-858)												*/
		/*	add MECHA_POSI_PAC_TRAY_PDPC_PRECHECKLENGTH						*/
		/*	Rev.(ZW04:BRZ-871)												*/
		/*	add MECHA_POSI_PAC_TRAY_PDPC_PRECHECKLENGTH						*/
		/*	add MECHA_POSI_PAC_TRAY_PRECHECKLENGTH_CHECKLENGTH				*/
		/*------------------------------------------------------------------*/
	MECHA_POSI_PAC_TRAY_DELIVERY		= 0x2001,	/* delivery position	*/
	MECHA_POSI_PAC_TRAY_INSERT			= 0x2002,	/* insert position		*/
	MECHA_POSI_PAC_TRAY_CHECK_LENGTH	= 0x2003,	/* length check position*/
	MECHA_POSI_PAC_TRAY_RELEASE			= 0x2004,	/* release position		*/
	MECHA_POSI_PAC_TRAY_BEFORE_JOIN		= 0x2005,	/* before join position	*/
	MECHA_POSI_PAC_TRAY_PREPARE_JOIN	= 0x2006,	/* prepare join position*/
	MECHA_POSI_PAC_TRAY_PRE_DISCHARGE	= 0x2007,	/* pre-discharge position*/
	MECHA_POSI_PAC_TRAY_BEFORE_HOOK		= 0x2008,	/* before hook position	*/
	MECHA_POSI_PAC_TRAY_BEFORE_SEP		= 0x2009,	/* before separator position*/
	MECHA_POSI_PAC_TRAY_PRE_CHECK_LENGTH= 0x200A,	/* pre length check position*/
	
	MECHA_POSI_PAC_TRAY_PDPC_CHECKLENGTH= 0x2010,	/* position*/
	MECHA_POSI_PAC_TRAY_CHECKLENGTH_PRPC= 0x2011,	/* position*/
	MECHA_POSI_PAC_TRAY_SAVE_POSITION	= 0x2012,	/* position*/
	MECHA_POSI_PAC_TRAY_PDPC_PRECHECKLENGTH			= 0x2013,	/* position*/
	MECHA_POSI_PAC_TRAY_PRECHECKLENGTH_CHECKLENGTH	= 0x2014,	/* position*/
		/*------------------------------------------------------------------*/
		/*	Part2 (carrier)													*/
		/*	Rev.(ZY01:BRZ-397)												*/
		/*	MECHA_POSI_PAC_CARRIER_ZERO_CHECK add							*/
		/*------------------------------------------------------------------*/
	MECHA_POSI_PAC_CARRIER_ESCAPE		= 0x2101,	/* escape position		*/
	MECHA_POSI_PAC_CARRIER_SEPARATOR	= 0x2102,	/* separator position	*/
	MECHA_POSI_PAC_CARRIER_JOIN			= 0x2103,	/* join position		*/
	MECHA_POSI_PAC_CARRIER_PRE_RELEASE	= 0x2104,	/* pre-release position	*/
	
	MECHA_POSI_PAC_CARRIER_ECHC_ECCC	= 0x2110,	/* position	*/
	MECHA_POSI_PAC_CARRIER_ECCC_ECPC	= 0x2111,	/* position	*/
	MECHA_POSI_PAC_CARRIER_ECPC_SEP		= 0x2112,	/* position	*/
	MECHA_POSI_PAC_CARRIER_ZERO_CHECK	= 0x2113,	/* position	*/
		/*------------------------------------------------------------------*/
		/*	Part3 (clamp)													*/
		/*	Rev.(ZZ06:BRZ-308)												*/
		/*	add position													*/
		/*	(MECHA_POSI_PAC_CLAMP_DEPRESS_FEW)								*/
		/*------------------------------------------------------------------*/
	MECHA_POSI_PAC_CLAMP_ESCAPE			= 0x2201,	/* escape position		*/
	MECHA_POSI_PAC_CLAMP_DEPRESS		= 0x2202,	/* depress position		*/
	MECHA_POSI_PAC_CLAMP_PRESS			= 0x2203,	/* press position		*/
	MECHA_POSI_PAC_CLAMP_DEPRESS_FEW	= 0x2204,
	
	/*----------------------------------------------------------------------*/
	/*	Separator Position													*/
	/*----------------------------------------------------------------------*/
		/*------------------------------------------------------------------*/
		/*	Part1 (stage)													*/
		/*	Rev.(ZW03:BRZ-775)												*/
		/*	add position(MECHA_POSI_SEP_STAGE_TOP_OFF)						*/
		/*------------------------------------------------------------------*/
	MECHA_POSI_SEP_STAGE_JOIN			= 0x3001,	/* join position		*/
	MECHA_POSI_SEP_STAGE_TOP_OFF		= 0x3002,	/* SSUC-10mm			*/
		/*------------------------------------------------------------------*/
		/*	Part2 (pusher)													*/
		/*------------------------------------------------------------------*/
	MECHA_POSI_SEP_PUSHER_PRESS_OFF		= 0x3101,	/* press off position	*/
	MECHA_POSI_SEP_PUSHER_BEFORE_JOIN	= 0x3102	/* before join position	*/
	};
typedef USHORT MECHA_POSITION;

/*--------------------------------------------------------------------------*/
/*	MECHA_BILL_POSITION														*/
/*	Rev.(ZW04:BRZ-805)														*/
/*--------------------------------------------------------------------------*/
enum {
	MECHA_BILL_POSI_UNKNOWN		= 0x0000,		/* position uncsetainty			*/
	MECHA_BILL_POSI_FRONT		= 0x0001,		/* They are those with a medium before a hook	*/
	MECHA_BILL_POSI_BACK		= 0x0002,		/* They are those with a medium after a hook	*/
	MECHA_BILL_POSI_NONE		= 0x0003		/* With no medium				*/
	};
typedef USHORT MECHA_BILL_POSITION;
/*--------------------------------------------------------------------------*/
/*	Rev.(ZW04:BRZ-828)														*/
/*	enum addition(Encoder status)											*/
/*--------------------------------------------------------------------------*/
enum
{
	ENCODER_TRAY_NONE_WATCH		= EMPTY,
	ENCODER_BELT_NONE_WATCH		= EMPTY,
	ENCODER_TRAY_WATCH			= BIT0,
	ENCODER_BELT_WATCH			= BIT0,
	ENCODER_TRAY_STEP_OUT 		= BIT1,
	ENCODER_BELT_STEP_OUT		= BIT1
};

/*--------------------------------------------------------------------------*/
/*	BV_VALUE																*/
/*	Rev.(ZV05:BRZ-986)	Add BV_CLEAR_FEATURE_IMAGE.							*/
/*	Rev.(ZU03:BRZ-1042)	Add BV_CHANGE_CONNECTION_MODE.						*/
/*	Rev.(AA43:BRZ-1520)	add BV_READ_CHEQUE_IMAGE							*/
/*--------------------------------------------------------------------------*/
enum
{
	BV_READ						= 0x10,
	BV_CLEAR					= 0x20,
	BV_START_LOADING 			= 0x30,/* LPR			*/
	BV_END_LOADING				= 0x31,/* LEN			*/
	BV_START_VALIDATE			= 0x40,/* SVR			*/
	BV_STOP_VALIDATE			= 0x41,/* SPV			*/
	BV_SENSOR_ON				= 0x50,/* SON			*/
	BV_SENSOR_OFF				= 0x51,/* SOF			*/
	BV_SENSOR_LEVEL				= 0x52,/* SLV			*/
	BV_RESET					= 0x60,/* RRT			*/
	BV_SET_TIME					= 0x70,/* TM 	(notuse)*/
	BV_REVISE_SENSOR			= 0x80,/* SRE			*/
	BV_START_SERIAL_NUMBER		= 0x90,/* STNO	(notuse)*/
	BV_READ_IMAGE				= 0xA0,/* RGR 	(notuse)*/
	BV_READ_FEATURE_IMAGE		= 0xA1,/* RSG			*/
	BV_READ_FEATURE_NUMBER		= 0xA2,/* RNS			*/
	BV_WRITE_IMAGE				= 0xA3,/* WGR	(notuse)*/
	BV_READ_ALL_IMAGE			= 0xA4,/* RGP			*/
	BV_CLEAR_FEATURE_IMAGE		= 0xA5,/* CSG			*/
	BV_READ_CHEQUE_IMAGE		= 0xA6,/* RCQ			*/
	BV_CLEAR_ALL_MEMORY			= 0xB0,/* CAM	(notuse)*/
	BV_DURING_VALIDATE			= 0xC0,/* DINF			*/
	BV_SIMULATED_VALIDATE		= 0xC1,/* SDI	(notuse)*/
	BV_SAVE_POWER_MODE			= 0xC2,/* PSM	(notuse)*/
	BV_READ_AVAILABLE			= 0xD0,/* RBI			*/
	BV_SET_AVAILABLE			= 0xD1,/* SBI			*/
	BV_READ_SERIAL_NUMBER		= 0xD2,/* RNO			*/
	BV_CHANGE_CONNECTION_MODE	= 0xD3 /* MOD			*/
	};
typedef	UCHAR	BV_ORDER;


/*--------------------------------------------------------------------------*/
/*																			*/
/*	Information Define														*/
/*																			*/
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/*	TASK_ID																	*/
/*	Rev.(ZZ04:BRZ-142)		add TASK_DRAS									*/
/*	Rev.(ZZ07:BRZ-341)		add TASK_JOB									*/
/*	Rev.(ZY01:BRZ-421)		add TASK_RFNC									*/
/*--------------------------------------------------------------------------*/
enum
{
	TASK_SYS		= 0x01,
	TASK_CMD		= 0x02,
	TASK_RESP		= 0x03,
	TASK_LINE		= 0x04,
	TASK_BV			= 0x05,
	TASK_LAN		= 0x06,
	TASK_MOVE		= 0x07,
	TASK_IO			= 0x08,
	TASK_MECHA		= 0x09,
	TASK_CA_CTRL	= 0x0A,
	TASK_CA1		= 0x0B,
	TASK_CA2		= 0x0C,
	TASK_CA3		= 0x0D,
	TASK_CA4		= 0x0E,
	TASK_UPPER		= 0x0F,
	TASK_PAC		= 0x10,
	TASK_ESC		= 0x11,
	TASK_SEP		= 0x12,
	TASK_SHT		= 0x13,
	TASK_RAS		= 0x14,
	TASK_WATCH		= 0x15,
	TASK_PATROL		= 0x16,
	TASK_DBG		= 0x17,
	TASK_OTHER		= 0x18,
	TASK_DRAS		= 0x19,
	TASK_BV_API		= 0x1A,
	TASK_JOB		= 0x1B,
	TASK_RFNC		= 0x1C,
	TASK_END					/*	end point	*/
	};
typedef	UCHAR	TASK_ID;
/*--------------------------------------------------------------------------*/
/*	Error Informations														*/
/*--------------------------------------------------------------------------*/
	/*----------------------------------------------------------------------*/
	/*	Error Level															*/
	/*----------------------------------------------------------------------*/
enum
{
	ERR_L_NONE			= 0x00,		/*	Nothing							*/
	ERR_L_COMMAND_L		= 0x20,		/*	Command(low level) error level	*/
	ERR_L_COMMAND_H		= 0x40,		/*	Command(hi level) error level	*/
	ERR_L_MECHA			= 0x60,		/*	Mechanical error level			*/
	ERR_L_JAM			= 0x80,		/*	Jam error level					*/
	ERR_L_DIFF_COUNT	= 0xA0,		/*	Different counting error level	*/
	ERR_L_SYSTEM		= 0xFF		/*	System error level				*/
};	/* ERR_LEVEL	*/
typedef	UCHAR	ERR_LEVEL;

	/*----------------------------------------------------------------------*/
	/*	Error Place															*/
	/*	Rev.(ZZ06:BRZ-338)													*/
	/*	Rev.(ZV05:BRZ-970)	add ERR_P_UPPER_PCB / ERR_P_LOWER_PCB			*/
	/*	Rev.(ZT06:BRZ-1140)	add ERR_P_OC_xxxx								*/
	/*----------------------------------------------------------------------*/
enum
{
	ERR_P_NONE					= 0x00,		/*	Nothiing						*/
	ERR_P_SHT					= 0x01,		/*	Shutter							*/
	ERR_P_PAC					= 0x02,		/*	Pre-acceptor					*/
	ERR_P_TRANSPORT_PAC			= 0x03,		/*	Pre-acceptor transport			*/
	ERR_P_SEP					= 0x04,		/*	Separator						*/
	ERR_P_TRANSPORT_SEP			= 0x05,		/*	Separator transport				*/
	ERR_P_TRANSPORT_BEFORE_BV	= 0x06,		/*	Transport before BV				*/
	ERR_P_BV					= 0x07,		/*	BV								*/
	ERR_P_TRANSPORT_AFTER_BV	= 0x08,		/*	Transport after BV				*/
	ERR_P_TRANSPORT_ESCROW		= 0x09,		/*	Escrow transport				*/
	ERR_P_ESCROW				= 0x0A,		/*	Escrow							*/
	ERR_P_RESERVOIR				= 0x0B,		/*	Reservoir						*/
	ERR_P_TRANSPORT_BUNCH		= 0x0C,		/*	Bunch transport					*/
	ERR_P_TRANSPORT_REJECT		= 0x0D,		/*	Reject transport				*/
	ERR_P_REJECT_BIN			= 0x0E,		/*	Reject bin						*/
	ERR_P_COUNTERFEIT_AREA		= 0x0F,		/*	Counterfeit area				*/
	ERR_P_REJECT_AREA			= 0x10,		/*	Reject area						*/
	ERR_P_CAPTURED_AREA			= 0x11,		/*	Captured area					*/
	ERR_P_TRANSPORT_CA			= 0x12,		/*	Transport to cassettes			*/
	ERR_P_TRANSPORT_CA1			= 0x13,		/*	Cassette position 1 tranport	*/
	ERR_P_CASSETTE1				= 0x14,		/*	Cassette position 1				*/
	ERR_P_TRANSPORT_CA2			= 0x15,		/*	Cassette position 2 tranport	*/
	ERR_P_CASSETTE2				= 0x16,		/*	Cassette position 2				*/
	ERR_P_TRANSPORT_CA3			= 0x17,		/*	Cassette position 3 tranport	*/
	ERR_P_CASSETTE3				= 0x18,		/*	Cassette position 3				*/
	ERR_P_TRANSPORT_CA4			= 0x19,		/*	Cassette position 4 tranport	*/
	ERR_P_CASSETTE4				= 0x1A,		/*	Cassette position 4				*/
	ERR_P_OC_PAC				= 0xD0,		/*	Pre-acceptor (for over current)		*/
	ERR_P_OC_SEP				= 0xD1,		/*	Separator (for over current)		*/
	ERR_P_OC_ESC				= 0xD2,		/*	Escrow (for over current)			*/
	ERR_P_OC_UPPER_BASE			= 0xD4,		/*	Upper base (for over current)		*/
	ERR_P_OC_LOWER_TRANSPORT	= 0xD5,		/*	Lower transport (for over current)	*/
	ERR_P_OC_LOWER_BASE			= 0xD6,		/*	Lower base (for over current)		*/
	ERR_P_UPPER_PCB				= 0xE0,		/*	Upper PCB						*/
	ERR_P_LOWER_PCB				= 0xE1,		/*	Lower PCB						*/
	ERR_P_OTHER					= 0xFF		/*	Software, PCB, etc.				*/
};	/* ERR_PLACE	*/
typedef	UCHAR	ERR_PLACE;

	/*----------------------------------------------------------------------*/
	/*	Error Code															*/
	/*----------------------------------------------------------------------*/
typedef	USHORT	ERROR_CODE;

	/*----------------------------------------------------------------------*/
	/*	State of Processing													*/
	/*	Rev.(ZZ02:BRZ-002)	add PROCESS_CMD_DEBUG							*/
	/*	Rev.(ZZ03:BRZ-024)	add PROCESS_INSERT								*/
	/*						add PROCESS_PRESENT								*/
	/*	Rev.(ZZ04:BRZ-169)													*/
	/*	add PROCESS_CLEAR, PROCESS_MOVE, PROCESS_SNS_ADJUST,				*/
	/*		PROCESS_ILLEGAL_WATCH											*/
	/*	Rev.(ZZ06:BRZ-324)													*/
	/*	add PROCESS_LINE_RECEPTION											*/
	/*	Rev.(ZZ07:BRZ-340)													*/
	/*	add PROCESS_BV,PROCESS_MECHA										*/
	/*	Rev.(ZY03:BRZ-511)													*/
	/*	add PROCESS_CLEAR_FINAL												*/
	/*	Rev.(ZY05:BRZ-603)													*/
	/*	add PROCESS_CLEAR_HIGH												*/
	/*	Rev.(ZY05:BRZ-614)	add PROCESS_SIGNATURE_UPDATE					*/
	/*	Rev.(ZY05:BRZ-623)	add PROCESS_RECORD_DENOMINATION					*/
	/*	Rev.(ZY06:BRZ-675)	add PROCESS_OPEN								*/
	/*	Rev.(ZY06:BRZ-698)													*/
	/*	change label.	(SIGNATURE_UPDATE -> COMPARE_DENOMINATION)			*/
	/*	Rev.(ZW01:BRZ-713)	add PROCESS_COLLECT_MODE						*/
	/*	Rev.(ZW04:BRZ-831)	add PROCESS_LOG_DETERRENCE						*/
	/*	Rev.(ZW06:BRZ-899)	add PROCESS_SHT_MOVE							*/
	/*	Rev.(ZV04:BRZ-942)	change label.	(RECORD_DENOMINATION -> ACCEPT)	*/
	/*	Rev.(ZV05:BRZ-969)	add PROCESS_RESTORATION_MOVE					*/
	/*	Rev.(ZU03:BRZ-1029)	add PROCESS_RAS_COLLECT_DATA					*/
	/*	Rev.(ZT12:BRZ-1176)	add PROCESS_UNUSUAL_MASK						*/
	/*	Rev.(AA02:BRZ-1180)	add PROCESS_LOG_SAVE_FILE						*/
	/*----------------------------------------------------------------------*/
enum
{
	PROCESS_COMMAND				= BIT0,			/* Processing Command				*/
	PROCESS_RAS					= BIT1,			/* Processing Ras					*/
	PROCESS_INSERT				= BIT2,			/* Processing Insert				*/
	PROCESS_PRESENT				= BIT3,			/* Processing Present				*/
	PROCESS_DRAW				= BIT4,			/* Processing Drawing bill			*/
	PROCESS_SC					= BIT5,			/* Processing Shutter close			*/
	PROCESS_SO					= BIT6,			/* Processing Shutter open			*/
	PROCESS_CLEAR				= BIT7,			/* Processing Clear					*/
	PROCESS_CLEAR_FINAL			= BIT8,			/* Processing Clear final			*/
	PROCESS_CLEAR_HIGH			= BIT9,			/* Processing Under mechanism operation	*/
	PROCESS_MOVE				= BIT10,		/* Processing Move					*/
	PROCESS_SNS_ADJUST			= BIT11,		/* Processing Sensor adjust			*/
	PROCESS_ILLEGAL_WATCH		= BIT12,		/* Processing illegal Sensor watch	*/
	PROCESS_SNS_WATCH			= BIT13,		/* Processing Sensor watch			*/
	PROCESS_LINE_RECEPTION		= BIT14,		/* Processing USB reception command	*/
	PROCESS_BV					= BIT15,		/* Processing Under BV communication*/
	PROCESS_MECHA				= BIT16,		/* Processing Under mechanism operation	*/
	PROCESS_COMPARE_DENOMINATION= BIT17,		/* Processing Compare denomination	*/
	PROCESS_ACCEPT				= BIT18,		/* Processing Record denomination	*/
	PROCESS_COLLECT_MODE		= BIT19,		/* Processing Under picture collection mode	*/
	PROCESS_LOG_DETERRENCE		= BIT20,		/* Processing Under log deterrence	*/
	PROCESS_SHT_MOVE			= BIT21,		/* Processing Under shutter move	*/
	PROCESS_RESTORATION_MOVE	= BIT22,		/* Processing Under restoration		*/
	PROCESS_RAS_COLLECT_DATA	= BIT23,		/* Processing Under collect BV data	*/
	PROCESS_UNUSUAL_MASK		= BIT24,		/* Processing 						*/
	PROCESS_LOG_SAVE_FILE		= BIT25,		/* Processing saving log to file	*/
	PROCESS_CMD_DEBUG			= BIT31			/* Processing Command debug			*/
};
typedef	ULONG	STATE_PROCESS;
	/*----------------------------------------------------------------------*/
	/*	Ras Mode															*/
	/*----------------------------------------------------------------------*/
enum
{
	RAS_INPUT_PROCESS_COMMAND	= 0x00,	/* runnning RAS 			*/
	RAS_INPUT_COMMAND			= 0x10,	/* inputting command		*/
	RAS_INPUT_OPERAND			= 0x20,	/* inputting operand		*/
	RAS_INPUT_OPERAND1			= 0x21,	/* inputting op1			*/
	RAS_INPUT_OPERAND2			= 0x22,	/* inputting op2			*/
	RAS_INPUT_OPERAND3			= 0x23,	/* inputting op3			*/
	RAS_INPUT_CONFIRM_COMMAND	= 0x30,	/* after input command		*/
	RAS_INPUT_CONFIRM_OPERAND	= 0x40,	/* after input operand		*/
	RAS_INPUT_CONFIRM_OPERAND1	= 0x41,	/* after input op1			*/
	RAS_INPUT_CONFIRM_OPERAND2	= 0x42,	/* after input op2			*/
	RAS_INPUT_CONFIRM_OPERAND3	= 0x43,	/* after input op3			*/
	RAS_INPUT_STOP_ERR			= 0x50	/* unuse					*/
};
typedef	UCHAR	RAS_INPUT_MODE;
	/*----------------------------------------------------------------------*/
	/*	The bit for operation mode											*/
	/*	Rev(ZZ05:BRZ-193)	delete DENOMINATION_MIX, add DENOMINATION_CODE.	*/
	/*----------------------------------------------------------------------*/
enum
{
	MODE_OP_RETRY_FORBID		= BIT0,
	MODE_OP_ECB6				= BIT1,
	MODE_OP_NOTHING				= NULL
};
typedef	UCHAR	OPERATION_MODE;

/*--------------------------------------------------------------------------*/
/*	Interrupt Mask bit for SR(status Register)								*/
/*--------------------------------------------------------------------------*/
enum
{
	MASK_LEVEL0		=	0x00000000,
	MASK_LEVEL1		=	0x00000010,
	MASK_LEVEL2		=	0x00000020,
	MASK_LEVEL3		=	0x00000030,
	MASK_LEVEL4		=	0x00000040,
	MASK_LEVEL5		=	0x00000050,
	MASK_LEVEL6		=	0x00000060,
	MASK_LEVEL7		=	0x00000070,
	MASK_LEVEL8		=	0x00000080,
	MASK_LEVEL9		=	0x00000090,
	MASK_LEVEL10	=	0x000000A0,
	MASK_LEVEL11	=	0x000000B0,
	MASK_LEVEL12	=	0x000000C0,
	MASK_LEVEL13	=	0x000000D0,
	MASK_LEVEL14	=	0x000000E0,
	MASK_LEVEL15	=	0x000000F0,
	MASK_ALL		=	MASK_LEVEL15
};
typedef	int	MASK_LEVEL;
/*--------------------------------------------------------------------------*/
/*	MECHA_DEBUG_MODE														*/
/*	<BRZ-030>																*/
/*	The definition in the mode which returns a processing result, 			*/
/*	without carrying out mechanism operation								*/
/*--------------------------------------------------------------------------*/
enum {
	MECHA_DEBUG_CLR		= 0x00,
	MECHA_DEBUG_ERR		= BIT0,
	MECHA_DEBUG_NORMAL  = BIT1,
	MECHA_DEBUG_FULL	= BIT2,
	MECHA_DEBUG_EMPTY	= BIT3
	};
typedef UCHAR	MECHA_DEBUG_MODE;
/*--------------------------------------------------------------------------*/
/*	DATA_DEBUG_MODE															*/
/*	<BRZ-183>	add	DATA_DEBUG_MODE											*/
/*--------------------------------------------------------------------------*/
enum {
	DATA_DEBUG_INVALID	= 0x00,
	DATA_DEBUG_FULL		= 0x01,
	DATA_DEBUG_EMPTY	= 0x02,
	DATA_DEBUG_END		= 0x03
	};
typedef UCHAR	DATA_DEBUG_MODE;
/*--------------------------------------------------------------------------*/
/*	DATA_STATE_SETUP														*/
/*	<BRZ-285>	add	DATA_STATE_SETUP										*/
/*--------------------------------------------------------------------------*/
enum {
	DATA_SETUP_NONE		= 0x00,
	DATA_SETUP_A1		= 0x01,
	};
typedef UCHAR	DATA_STATE_SETUP;
/*--------------------------------------------------------------------------*/
/*	DATA_RSV_CTRL_SETUP(A1.No15:Improved Reservoir Control)					*/
/*	Rev(AA40:BRZ-1511)	add	DATA_RSV_CTRL_SETUP								*/
/*--------------------------------------------------------------------------*/
enum {
	DATA_RSV_CTRL_CLR		= 0x0000,
	DATA_RSV_CTRL_SLIP		= 0x0001
	};
typedef USHORT	DATA_RSV_CTRL_SETUP;
/*--------------------------------------------------------------------------*/
/*	Rev(AA48:BRZ-1530)		add												*/
/*	line frame mode															*/
/*--------------------------------------------------------------------------*/
enum {
	DATA_LINE_NML_FRAME	= 0,
	DATA_LINE_BIG_FRAME	= 1
	};
/*--------------------------------------------------------------------------*/
/*	cassette processing demand Code											*/
/*	Rev(ZZ06:BRZ-228)														*/
/*	Rev(ZZ06:BRZ-287)type / label change									*/
/*	Rev(ZY04:BRZ-584)														*/
/*	add code(MECHA_DEMAND_BACK_FEED_SEP)									*/
/*	Rev(ZW03:BRZ-759)														*/
/*	add code(MECHA_DEMAND_DOWN_NEAR_END_STAGE)								*/
/*	Rev(ZW04:BRZ-832)														*/
/*	add code(MECHA_DEMAND_COMPULSIVE_PRE_DRAW_BILL)							*/
/*	Rev(ZW04:BRZ-834)														*/
/*	add code(MECHA_DEMAND_DOWN_DEPRESS_STAGE)								*/
/*--------------------------------------------------------------------------*/
enum
{
	MECHA_DEMAND_NONE 						= EMPTY,
	MECHA_DEMAND_LOCK_RELEASE 				= BIT0,
	MECHA_DEMAND_AFTER_FEED					= BIT1,
	MECHA_DEMAND_LEVEL_SET					= BIT2,
	MECHA_DEMAND_DRAW_BILL					= BIT3,
	MECHA_DEMAND_TOP_SENSOR_LEVEL_SET		= BIT4,
	MECHA_DEMAND_FEED_END_SENSOR_LEVEL_SET	= BIT5,
	MECHA_DEMAND_DOWN_BREAK_STAGE			= BIT6,
	MECHA_DEMAND_DOWN_LIMIT_STAGE			= BIT7,
	MECHA_DEMAND_DOWN_STACK_STAGE			= BIT8,
	MECHA_DEMAND_UP_PRESS_STAGE				= BIT9,
	MECHA_DEMAND_UP_TOP_STAGE				= BIT10,
	MECHA_DEMAND_PHASE_IMPELLER				= BIT11,
	MECHA_DEMAND_ROTATION_IMPELLER			= BIT12,
	MECHA_DEMAND_DOWN_DEPRESS_STAGE			= BIT13,
	MECHA_DEMAND_BACK_FEED_SEP				= BIT13,
	MECHA_DEMAND_DOWN_NEAR_END_STAGE		= BIT14,
	MECHA_DEMAND_COMPULSIVE_PRE_DRAW_BILL	= BIT15
};
typedef	USHORT	MECHA_DEMAND_CODE;

	/*----------------------------------------------------------------------*/
	/*	kind of program name												*/
	/*	Rev.(ZZ07:BRZ-386)	add this definition								*/
	/*	Rev.(ZW01:BRZ-739)	add PRG_CTRL_DATA and renumber					*/
	/*----------------------------------------------------------------------*/
enum
{
	PRG_TOP			= 0x0000,		/*	TOP									*/
	PRG_NONE		= 0x0000,		/*	not downloading 					*/
	PRG_MAIN		= 0x0001,		/*	downloading(MAIN-firm)				*/
	PRG_SUB			= 0x0002,		/*	downloading(SUB-firm)				*/
	PRG_CTRL_DATA	= 0x0003,		/*	downloading(CONTROL-DATA-file)		*/
	PRG_DATA		= 0x0004,		/*	downloading(DATA-file)				*/
	PRG_BOOT		= 0x0005,		/*	downloading(BOOT-program)			*/
	PRG_BV_MAIN		= 0x0006,		/*	downloading(BV MAIN-firm)			*/
	PRG_BV_SUB		= 0x0007,		/*	downloading(BV SUB-firm)			*/
	PRG_BV_DATA		= 0x0008,		/*	downloading(BV DATA-file)			*/
	PRG_OTHER		= 0x0009,		/*	downloading(other)					*/
	PRG_TAIL		= 0x000A,		/*	END									*/
	PRG_MASK		= 0x00FF		/*	mask data of download kind			*/
};
	/*----------------------------------------------------------------------*/
	/*	kind of download-status												*/
	/*	Rev.(ZZ07:BRZ-386)	add this definition								*/
	/*----------------------------------------------------------------------*/
enum
{
	DOWNLOAD_NONE	= 0x0000,		/*	download initial					*/
	DOWNLOAD_LD		= 0x0100,		/*	LD received							*/
	DOWNLOAD_LE		= 0x0200,		/*	LE received							*/
	DOWNLOAD_RT		= 0x0300,		/*	RT received(after download)			*/
	DOWNLOAD_MASK	= 0xFF00		/*	mask data of download status		*/
};
	/*----------------------------------------------------------------------*/
	/*	Press control														*/
	/*	Rev.(ZW01:BRZ-707)	Add this definition								*/
	/*----------------------------------------------------------------------*/
enum
{
	PRESS_KEEP		= 0x00,
	PRESS_PLUS		= 0x01,
	PRESS_MINUS		= 0x02,
	PRESS_MAX		= 0x03,
};

	/*----------------------------------------------------------------------*/
	/*	Sensor level info							(J0)					*/
	/*	Rev.(ZW01:BRZ-710)	add												*/
	/*	Rev.(ZW04:BRZ-835)	Add	details of sensor name.						*/
	/*	Rev.(ZV01:BRZ-911)	Change sensor name.	( ETSS -> ETLS )			*/
	/*----------------------------------------------------------------------*/
enum
{
	STT_J0_DATA_TOP		=  0,	/*	(top of number for J0)				*/
	STT_J0_SNS_PS1S		=  0,	/*	 0									*/
	STT_J0_SNS_PS2S		=  1,	/*	 1									*/
	STT_J0_SNS_PS3S		=  2,	/*	 2									*/
	STT_J0_SNS_PS4S		=  3,	/*	 3									*/
	STT_J0_SNS_PTCS		=  4,	/*	 4									*/
	STT_J0_SNS_PASS		=  5,	/*	 5									*/
	STT_J0_SNS_PDSS		=  6,	/*	 6									*/
	STT_J0_SNS_SDIS		=  7,	/*	 7									*/
	STT_J0_SNS_SDOS		=  8,	/*	 8									*/
	STT_J0_SNS_SSLS		=  9,	/*	 9									*/
	STT_J0_SNS_SSRS		= 10,	/*	10									*/
	STT_J0_SNS_SSOS		= 11,	/*	11									*/
	STT_J0_SNS_EECS		= 12,	/*	12									*/
	STT_J0_SNS_ETLS		= 13,	/*	13									*/
	STT_J0_SNS_EELS		= 14,	/*	14									*/
	STT_J0_SNS_EERS		= 15,	/*	15									*/
	STT_J0_SNS_EDLS		= 16,	/*	16									*/
	STT_J0_SNS_EDRS		= 17,	/*	17									*/
	STT_J0_SNS_ERLS		= 18,	/*	18									*/
	STT_J0_SNS_ERRS		= 19,	/*	19									*/
	STT_J0_SNS_UGAS		= 20,	/*	20									*/
	STT_J0_SNS_URHS		= 21,	/*	21									*/
	STT_J0_SNS_UFHS		= 22,	/*	22									*/
	STT_J0_SNS_UGDS		= 23,	/*	23									*/
	STT_J0_SNS_UECS		= 24,	/*	24									*/
	STT_J0_SNS_UEFS		= 25,	/*	25									*/
	STT_J0_SNS_UERS		= 26,	/*	26									*/
	STT_J0_SNS_LT3S		= 27,	/*	27									*/
	STT_J0_SNS_LFHS		= 28,	/*	28									*/
	STT_J0_SNS_CL1S		= 29,	/*	29									*/
	STT_J0_SNS_CR1S		= 30,	/*	30									*/
	STT_J0_SNS_CL2S		= 31,	/*	31									*/
	STT_J0_SNS_CR2S		= 32,	/*	32									*/
	STT_J0_SNS_CL3S		= 33,	/*	33									*/
	STT_J0_SNS_CR3S		= 34,	/*	34									*/
	STT_J0_SNS_CL4S		= 35,	/*	35									*/
	STT_J0_SNS_CR4S		= 36,	/*	36									*/
	STT_J0_SNS_CT1S		= 37,	/*	37									*/
	STT_J0_SNS_CT2S		= 38,	/*	38									*/
	STT_J0_SNS_CT3S		= 39,	/*	39									*/
	STT_J0_SNS_CT4S		= 40,	/*	40									*/
	
	STT_J0_SNS_END		= 59,	/*	59									*/
	
	STT_J0_BV_SENSOR	= 60,	/*	BV sensor level						*/
	STT_J0_BV_BATTERY	= 61,	/*	BV battery level					*/
	STT_J0_BV_FUN		= 62,	/*	BV fun								*/
	STT_J0_BV_RSV		= 63,	/*	reserve for BV information			*/
	STT_J0_DATA_END		= 64	/*	(end of number for J0)				*/
};
	/*----------------------------------------------------------------------*/
	/*	Transaction information						(J4)					*/
	/*	Rev.(ZW01:BRZ-710)	add												*/
	/*----------------------------------------------------------------------*/
		/*------------------------------------------------------------------*/
		/*	kind of Transaction												*/
		/*	Rev.(ZU08:BRZ-1092)	Add counter of invalid insertion factor.	*/
		/*	Rev.(ZU08:BRZ-1093)	Add command CL.								*/
		/*	Rev.(AA48:BRZ-1535)	Add command BE.								*/
		/*------------------------------------------------------------------*/
enum
{
	STT_J4_TRANSACTION_TOP				=  0,	/*	(transaction kind top)	*/

	STT_J4_TRANSACTION_ACCEPT			=  0,	/*	IV						*/
	STT_J4_TRANSACTION_DEPOSIT			=  1,	/*	DP						*/
	STT_J4_TRANSACTION_DISPENSE			=  2,	/*	WC						*/
	STT_J4_TRANSACTION_REJECT			=  3,	/*	RJ						*/
	STT_J4_TRANSACTION_MECHANICAL		=  4,	/*	MR						*/
	STT_J4_TRANSACTION_RECONCILIATION	=  5,	/*	UC						*/
	STT_J4_TRANSACTION_COLLECT			=  6,	/*	CL						*/
	STT_J4_TRANSACTION_BACK_ESCROW		=  7,	/*	BE						*/

	STT_J4_FACTOR_INVALID_INSERTION		=  9,	/*	Factor of invalid insertion	*/

	STT_J4_TRANSACTION_END				= 10	/*	(transaction kind end)	*/
};
		/*------------------------------------------------------------------*/
		/*	kind of counter													*/
		/*	Rev.(ZU03:BRZ-1079)	Add counter of not recognized kind.			*/
		/*	Rev.(ZU08:BRZ-1092)	Add counter of invalid insertion factor.	*/
		/*	Rev.(AA05:BRZ-1224)	Add factor of fail to move.					*/
		/*------------------------------------------------------------------*/
enum
{
	STT_J4_COUNTER_TOP				=  0,	/*	(counter kind top)			*/

	STT_J4_COUNTER_TRANSACTION		=  0,	/*	transaction counter			*/
	STT_J4_COUNTER_GENUINE			=  1,	/*	genuine note counter		*/
	STT_J4_COUNTER_DAMAGED			=  2,	/*	damaged note counter		*/
	STT_J4_COUNTER_NOT_RECOGNIZED	=  3,	/*	not recognized note counter	*/
	STT_J4_COUNTER_SUSPECT			=  4,	/*	suspect note counter		*/
	STT_J4_COUNTER_COUNTERFEIT		=  5,	/*	counterfeit note counter	*/
	STT_J4_COUNTER_DOUBLE			=  6,	/*	Double note					*/
	STT_J4_COUNTER_LONG				=  7,	/*	Long note					*/
	STT_J4_COUNTER_SKEW				=  8,	/*	Skewd note					*/
	STT_J4_COUNTER_CLOSE			=  9,	/*	Notes too close				*/

	STT_J4_FACTOR_INSERTION			=  0,	/*	Insertion counter			*/
	STT_J4_FACTOR_LONG_1ST			=  1,	/*	Long   note	(1st check)		*/
	STT_J4_FACTOR_LONG_2ND			=  2,	/*	Long   note	(2nd check)		*/
	STT_J4_FACTOR_SHORT				=  3,	/*	Short  note					*/
	STT_J4_FACTOR_SKEW				=  4,	/*	Skewed note					*/
	STT_J4_FACTOR_THICK				=  5,	/*	Thickness over				*/
	STT_J4_FACTOR_DETECT			=  6,	/*	Detect inserted note after close	*/
	STT_J4_FACTOR_TAKE_OUT			=  7,	/*	Take out note				*/
	STT_J4_FACTOR_FAIL_MOVE			=  8,	/*	Fail to move note to Sep	*/

	STT_J4_COUNTER_END				= 10	/*	(counter kind end)			*/
};
	/*----------------------------------------------------------------------*/
	/*	Skew information							(J5)					*/
	/*	Rev.(ZW01:BRZ-710)	add												*/
	/*----------------------------------------------------------------------*/
		/*------------------------------------------------------------------*/
		/*	place															*/
		/*	Rev.(AA12:BRZ-1321)	add No.5 & No.6								*/
		/*------------------------------------------------------------------*/
enum
{
	STT_J5_PLACE_TOP		= 0,	/*	(top of place for J5)				*/
	STT_J5_PLACE_SEPARATOR	= 0,	/*	separator			(SSRS/SSLS)		*/
	STT_J5_PLACE_CASSETTE1	= 1,	/*	cassette position1	(CR1S/CL1S)		*/
	STT_J5_PLACE_CASSETTE2	= 2,	/*	cassette position2	(CR2S/CL2S)		*/
	STT_J5_PLACE_CASSETTE3	= 3,	/*	cassette position3	(CR3S/CL3S)		*/
	STT_J5_PLACE_CASSETTE4	= 4,	/*	cassette position4	(CR4S/CL4S)		*/
	STT_J5_PLACE_BVIN_SEP	= 5,	/*	BVIN from Separator	(BVIR/BVIL)		*/
	STT_J5_PLACE_BVIN_CA	= 6,	/*	BVIN from cassette  (BVIR/BVIL)		*/
	STT_J5_PLACE_END		= 8		/*	(end of place for J5)				*/
};
		/*------------------------------------------------------------------*/
		/*	kind of counter													*/
		/*------------------------------------------------------------------*/
enum
{
	STT_J5_COUNTER_TOP			= 0,	/*	(top of counter for J5)		*/
	STT_J5_COUNTER_PLUS8_OVER	= 0,	/*	+8 over						*/
	STT_J5_COUNTER_PLUS6_7		= 1,	/*	+6 to +7					*/
	STT_J5_COUNTER_PLUS3_5		= 2,	/*	+3 to +5					*/
	STT_J5_COUNTER_MINUS2_PLUS2	= 3,	/*	-2 to +2					*/
	STT_J5_COUNTER_MINUS3_5		= 4,	/*	-5 to -3					*/
	STT_J5_COUNTER_MINUS6_7		= 5,	/*	-7 to -6					*/
	STT_J5_COUNTER_MINUS8_UNDER	= 6,	/*	-8 under					*/
	STT_J5_COUNTER_END			= 7		/*	(end of counter for J5)		*/
};
	/*----------------------------------------------------------------------*/
	/*	Parameter information						(J7)					*/
	/*	Rev.(ZW01:BRZ-710)	add												*/
	/*----------------------------------------------------------------------*/
enum
{
	STT_J7_TOP		= 0,
	STT_J7_A1		= 1,
	STT_J7_A2		= 2,
	STT_J7_A5		= 3,
	STT_J7_A6		= 4,
	STT_J7_A8		= 5,
	STT_J7_END		= 6
};
	/*----------------------------------------------------------------------*/
	/*	Temperature information						(J8)					*/
	/*	Rev.(ZW01:BRZ-710)	add												*/
	/*----------------------------------------------------------------------*/
enum
{
	STT_J8_COUNTER_TOP				=  0,	/*	(top of counter for J8)		*/
	STT_J8_COUNTER_PLUS_70_OVER		=  0,	/*	+70 over					*/
	STT_J8_COUNTER_PLUS_60			=  1,	/*	+60 to +69					*/
	STT_J8_COUNTER_PLUS_50			=  2,	/*	+50 to +59					*/
	STT_J8_COUNTER_PLUS_40			=  3,	/*	+40 to +49					*/
	STT_J8_COUNTER_PLUS_30			=  4,	/*	+30 to +39					*/
	STT_J8_COUNTER_PLUS_20			=  5,	/*	+20 to +29					*/
	STT_J8_COUNTER_PLUS_10			=  6,	/*	+10 to +19					*/
	STT_J8_COUNTER_PLUS_0			=  7,	/*	  0 to  +9					*/
	STT_J8_COUNTER_MINUS_0			=  8,	/*	 -9 to  -1					*/
	STT_J8_COUNTER_MINUS_10			=  9,	/*	-19 to -10					*/
	STT_J8_COUNTER_MINUS_20_UNDER	= 10,	/*	-20 under					*/
	STT_J8_COUNTER_END				= 11	/*	(end of counter for J8)		*/
};

	/*----------------------------------------------------------------------*/
	/*	kind of Lx-information						(Lx)					*/
	/*	Rev.(ZW01:BRZ-710)	add												*/
	/*----------------------------------------------------------------------*/
enum
{
	STT_KIND_LX_TOP	= 0,	/*	(top of kind number for Lx)		*/
	STT_KIND_L0		= 0,
	STT_KIND_L1,
	STT_KIND_L2,
	STT_KIND_L3,
	STT_KIND_L4,
	STT_KIND_L5,
	STT_KIND_L6,
	STT_KIND_L7,
	STT_KIND_L8,
	STT_KIND_L9,
	STT_KIND_LA,
	STT_KIND_LB,
	STT_KIND_LC,
	STT_KIND_LD,
	STT_KIND_LE,
	STT_KIND_LF,
	STT_KIND_LG,
	STT_KIND_LH,
	STT_KIND_LX_END			/*	(end of kind number for Lx)		*/
};

	/*----------------------------------------------------------------------*/
	/*	kind of counter for Lx-information			(Lx)					*/
	/*	Rev.(ZW01:BRZ-710)	add												*/
	/*	Rev.(AA16:BRZ-1376)	add STT_xx_FEED_PHASE (L3,LC-LF)				*/
	/*	Rev.(AA22:BRZ-1451)	add label of L8 information.					*/
	/*	Rev.(AA48:BRZ-1540)	add label of L2 information.					*/
	/*----------------------------------------------------------------------*/
enum
{
	STT_LX_COUNTER_TOP				=  0,	/*	(top of counter for Lx)	*/
		/*	( L0 )		*/
	STT_USB_PROTOCOL_ERROR			=  0,	/*		*/
	STT_USB_LSI_ERROR				=  2,	/*		*/
	STT_USB_BUS_RESET				=  3,	/*		*/
	STT_LAN_PROTOCOL_ERROR_SEND		=  8,	/*		*/
	STT_LAN_PROTOCOL_ERROR_REC		=  9,	/*		*/
	STT_LAN_LSI_ERROR				= 10,	/*		*/
	STT_LAN_TEST_REQUEST			= 11,	/*		*/
		/*	( L1 )		*/
	STT_SHUTTER_OPEN_ERROR			=  0,	/*		*/
	STT_SHUTTER_CLOSE_ERROR			=  1,	/*		*/
	STT_SHUTTER_DRIVE				=  2,	/*		*/
		/*	( L2 )		*/
	STT_PAC_MECHA_ERROR				=  0,	/*		*/
	STT_PAC_RETRY_TRAY_FORWARD		=  1,	/*		*/
	STT_PAC_RETRY_TRAY_BACKWARD		=  2,	/*		*/
	STT_PAC_RETRY_CLAMP				=  3,	/*		*/
	STT_PAC_STEP_OUT_BELT			=  4,	/*		*/
	STT_PAC_PDSS_NOT_BLOCK			=  5,	/*		*/
	STT_PAC_PDSS_NOT_CLEAR			=  6,	/*		*/
	STT_PAC_PDSS_BLOCK_AFTER_CLAMP	=  7,	/*		*/
	STT_PAC_RETRY_BELT_TRANSPORT	=  8,	/*		*/
	STT_PAC_PAMG_ON					= 11,	/*		*/
	STT_PAC_PDMG_ON					= 12,	/*		*/
	STT_PAC_PHMG_ON					= 13,	/*		*/
		/*	( L3 )		*/
	STT_SEP_MECHA_ERROR				=  0,	/*	Document No.3	*/
	STT_SEP_RETRY_PUSHER_UP			=  1,	/*			 No.4	*/
	STT_SEP_RETRY_PUSHER_DOWN		=  2,	/*			 No.5	*/
	STT_SEP_RETRY_STAGE_UP			=  3,	/*			 No.6	*/
	STT_SEP_RETRY_STAGE_DOWN		=  4,	/*			 No.7	*/
	STT_SEP_FEED_ERROR				=  7,	/*			 No.10	*/
	STT_SEP_PICK_MISS				=  8,	/*			 No.11	*/
	STT_SEP_STEP_OUT_FEED			=  9,	/*			 No.12	*/
	STT_SEP_FED						= 11,	/*			 No.14	*/
	STT_SEP_SRMG_ON					= 12,	/*			 No.15	*/
	STT_SEP_FEED_PHASE				= 13,	/*			 No.16	*/
		/*	( L4 )		*/
	STT_ESC_MECHA_ERROR				=  0,	/*		*/
	STT_ESC_RETRY_ESCROW_UP			=  1,	/*		*/
	STT_ESC_RETRY_ESCROW_DOWN		=  2,	/*		*/
	STT_ESC_RETRY_RESERVOIR_UP		=  3,	/*		*/
	STT_ESC_RETRY_RESERVOIR_DOWN	=  4,	/*		*/
	STT_ESC_RETRY_CARRIER_FORWARD	=  5,	/*		*/
	STT_ESC_RETRY_CARRIER_BACKWARD	=  6,	/*		*/
		/*	( L8 )		*/
	STT_RJT_FIT_FULL_0_49			=  0,	/*	Document No.3	*/
	STT_RJT_FIT_FULL_50_99			=  1,	/*			 No.4	*/
	STT_RJT_FIT_FULL_100_149		=  2,	/*			 No.5	*/
	STT_RJT_FIT_FULL_150_199		=  3,	/*			 No.6	*/
	STT_RJT_FIT_FULL_200_OVER		=  4,	/*			 No.7	*/
	STT_RJT_RJT_FULL_0_49			=  5,	/*			 No.8	*/
	STT_RJT_RJT_FULL_50_99			=  6,	/*			 No.9	*/
	STT_RJT_RJT_FULL_100_149		=  7,	/*			 No.10	*/
	STT_RJT_RJT_FULL_150_199		=  8,	/*			 No.11	*/
	STT_RJT_RJT_FULL_200_OVER		=  9,	/*			 No.12	*/
	STT_RJT_CPT_FULL_0_49			=  10,	/*			 No.13	*/
	STT_RJT_CPT_FULL_50_99			=  11,	/*			 No.14	*/
	STT_RJT_CPT_FULL_100_149		=  12,	/*			 No.15	*/
	STT_RJT_CPT_FULL_150_199		=  13,	/*			 No.16	*/
	STT_RJT_CPT_FULL_200_OVER		=  14,	/*			 No.17	*/
		/*	( LC,LD,LE,LF )		*/
	STT_CA_MECHA_ERROR				=  0,	/*	Document No.3	*/
	STT_CA_RETRY_STAGE_UP			=  1,	/*			 No.4	*/
	STT_CA_RETRY_STAGE_DOWN			=  2,	/*			 No.5	*/
	STT_CA_RETRY_IMPELLER			=  3,	/*			 No.6	*/
	STT_CA_FEED_ERROR				=  7,	/*			 No.10	*/
	STT_CA_PICK_MISS				=  8,	/*			 No.11	*/
	STT_CA_STEP_OUT_FEED			=  9,	/*			 No.12	*/
	STT_CA_FED						= 11,	/*			 No.14	*/
	STT_CA_SOLENOID_ON				= 12,	/*			 No.15	*/
	STT_CA_FEED_PHASE				= 13,	/*			 No.16	*/
	
	STT_LX_COUNTER_END				= 22	/*	(end of counter for Lx)	*/
};

	/*----------------------------------------------------------------------*/
	/*	group for stop request												*/
	/*	Rev.(ZW04:BRZ-880)	add												*/
	/*----------------------------------------------------------------------*/
enum
{
	STOP_REQ_MOVEMENT	= BIT0,			/*	Mecha,Job,DC-Motor				*/
	STOP_REQ_MONITOR	= BIT1,			/*	Watch							*/
	STOP_REQ_ALL		= ( STOP_REQ_MOVEMENT | STOP_REQ_MONITOR )
};
/****************************************************************************/
/*																			*/
/*	structures																*/
/*																			*/
/****************************************************************************/
/*--------------------------------------------------------------------------*/
/*	PKT_DATA																*/
/*	Rev.(ZY01:BRZ-440)	change type of member								*/
/*--------------------------------------------------------------------------*/
typedef	struct
{
	TASK_ID			id;
	TASK_MSG		msg;
	union
	{
		USHORT	w;
		UCHAR	b[2];
	}param;
	ULONG			lparam;
} PKT_DATA;
#define		PARA_1ST	0
#define		PARA_2ND	1
/*--------------------------------------------------------------------------*/
/*	PKT_BILL																*/
/*	Rev.(ZZ02:BRZ-005)	change PKT_BILL type member, add define				*/
/*						: member "vd" is changed into union.				*/
/*						: delete member "read","write"						*/
/*	Rev.(ZZ04:BRZ-159)	add PKT_BILL type member (vd_log)					*/
/*	Rev.(ZZ06:BRZ-244)	change PKT_BILL type member name. (vd_log->vd_all)	*/
/*--------------------------------------------------------------------------*/
typedef	struct
{
	MECHA_PLACE		from;
	MECHA_PLACE		to;
	union
	{
		UCHAR		vd[4];
		ULONG		vd_all;
		struct
		{
			UCHAR	bdata[2];
			USHORT	wdata;
		}detail;
	} bill;
} PKT_BILL;
#define		VD_PRESENCE_BILL	0
#define		VD_TRUTH_BILL		1
#define		VD_COUNTRY_CODE		2
#define		VD_KIND_BILL		3
/*--------------------------------------------------------------------------*/
/*	Rev.(ZV05:BRZ-979)	add													*/
/*	PKT_BILL_TRILING														*/
/*	Rev.(AA25:BRZ-1461)														*/
/*	 add bStayedFlag, change size of reserve								*/
/*--------------------------------------------------------------------------*/
typedef	struct
{
	short	sNoteLength;
	short	sCorrectedCounter;
	ONOFF	bStayedFlag;
	char	cReserve[3];
}PKT_BILL_TRAILING;
/*--------------------------------------------------------------------------*/
/*	COMMUNICATION_HEADER													*/
/*	Rev(ZZ04:BRZ-133)														*/
/*	add Message communication header type									*/
/*	Rev(ZZ06:BRZ-283)														*/
/*	change reserve -> continuity											*/
/*--------------------------------------------------------------------------*/
typedef	struct
{
	UCHAR	encrypt;
	UCHAR	continuity;
	USHORT	length;
} COMMUNICATION_HEADER;
/*--------------------------------------------------------------------------*/
/*	MESSAGE_HEADER															*/
/*	Rev(ZZ04:BRZ-133)														*/
/*	add Request / Response message header type								*/
/*--------------------------------------------------------------------------*/
typedef	struct
{
	UCHAR	func[2];
	USHORT	cmd;
	UCHAR	rsv[2];
} MESSAGE_HEADER;
#define		HEADER_FUNCTION_H	0
#define		HEADER_FUNCTION_L	1
#define		HEADER_RESERVE_H	0
#define		HEADER_RESERVE_L	1
#define		HEADER_FUNCTION_PROGRESS_REQUEST	0x02
/*--------------------------------------------------------------------------*/
/*	DATA_HEADER																*/
/*	Rev(ZZ04:BRZ-133)														*/
/*	add Request / Response data header type									*/
/*--------------------------------------------------------------------------*/
typedef	struct
{
	USHORT	class;
	UCHAR	length[4];
} DATA_HEADER;
/*--------------------------------------------------------------------------*/
/*	FRAM_FORM																*/
/*	Rev(ZZ04:BRZ-160)	add FRAM_FORM type									*/
/*--------------------------------------------------------------------------*/
#define		MAX_SIZE_FRAME				1500
#define		MAX_SIZE_MESSAGE_DATA		1478

typedef	struct{
		COMMUNICATION_HEADER	ComHeader;
		union{
			UCHAR				Data[ MAX_SIZE_MESSAGE_DATA + sizeof(MESSAGE_HEADER) + sizeof(USHORT) ];
			struct
			{
				USHORT			MsgLength;
				MESSAGE_HEADER	MsgHeader;
				UCHAR			Data[ MAX_SIZE_MESSAGE_DATA ];
			}Msg;
		}Com;
}FRAME_FORM;
/*--------------------------------------------------------------------------*/
/*	Rev.(AA48:BRZ-1530)		add												*/
/*	frame format for send													*/
/*--------------------------------------------------------------------------*/
#define		MAX_SIZE_FRAME_SEND			4076
#define		MAX_SIZE_MESSAGE_DATA_SEND	( MAX_SIZE_FRAME_SEND - sizeof( COMMUNICATION_HEADER ) - sizeof( USHORT ) - sizeof( MESSAGE_HEADER ) - sizeof( USHORT ) )

typedef	struct{
		COMMUNICATION_HEADER	ComHeader;
		union{
			UCHAR				Data[ sizeof(USHORT) + sizeof(MESSAGE_HEADER) + MAX_SIZE_MESSAGE_DATA_SEND + sizeof(USHORT) ];
			struct
			{
				USHORT			MsgLength;
				MESSAGE_HEADER	MsgHeader;
				UCHAR			Data[ MAX_SIZE_MESSAGE_DATA_SEND + sizeof(USHORT) ];
			}Msg;
		}Com;
}FRAME_FORM_SEND;
/*--------------------------------------------------------------------------*/
/*	MOVE_REQUEST															*/
/*	Rev.(ZZ02:BRZ-005)	change MOVE_REQUEST type member						*/
/*						 : member deletion	to_old,prep						*/
/*						 : model change		to								*/
/*--------------------------------------------------------------------------*/
typedef	struct
{
	MECHA_PLACE		to;						/* 行き先候補テーブル			*/
	MECHA_PLACE		from;					/* 繰り出し元					*/
	short			max;					/* 繰り出し最大枚数				*/
	UCHAR			bv;						/* 鑑別モード					*/
	INT_END_FACTOR	end_factor;				/* 終了要因						*/
	INT_END_FACTOR	retry;					/* リカバリ要因					*/
	JOB_END_FACTOR	*jobstatus;				/* ジョブ終了要因格納エリア		*/
	INT_END_FACTOR	*movestatus;			/* 搬送制御タスク終了要因格納エリア	*/
} MOVE_REQUEST;
/*--------------------------------------------------------------------------*/
/*	IO_REQUEST																*/
/*	Rev.(ZZ03:BRZ-108)	add IO task request parameter						*/
/*	Rev.(AA19:BRZ-1405)	add control of additional pushing out.				*/
/*--------------------------------------------------------------------------*/
typedef	struct
{
	UCHAR			interval;					/*	Media Indicator interval timer		*/
	UCHAR			start;						/*	Draw / Close start timer			*/
	UCHAR			limit;						/*	Insertion / Presenting limit timer	*/
	ONOFF			limitdirect;				/*	A limit timer set is directed		*/
	UCHAR			AddPushCnt;					/*	Additional pushing out note number	*/
	UCHAR			AddPushTmr;					/*	Additional pushing out note Timer	*/
	JOB_END_FACTOR	*jobstatus;					/*	The end factor of job processing	*/
} IO_REQUEST;
/*--------------------------------------------------------------------------*/
/*	RESP_REQUEST															*/
/*	Rev.(ZY01:BRZ-433)	add RESP_REQUEST type.								*/
/*	Rev.(ZY04:BRZ-566)	add member of division response.					*/
/*	Rev.(ZV05:BRZ-985)	add member of sensor name.							*/
/*	Rev.(AA09:BRZ-1275)	change member.	( bSnsinfo -> bEncrypt )			*/
/*--------------------------------------------------------------------------*/
typedef	struct
{
	USHORT	cmd;
	UCHAR	order[RESP_ORDER_MAX];
	UCHAR	bEncrypt;						/*	Encryption								*/
	UCHAR	bReserve;						/*	Sensor name								*/
	USHORT	bBlock;							/*	block number of division response		*/
	USHORT	bClass;							/*	data class code of division response	*/
	ULONG	lRemainLen;						/*	Remain length of division response		*/
	ULONG	lStartAdr;						/*	Edit address of division response		*/
} RESP_REQUEST;
/*--------------------------------------------------------------------------*/
/*	MECHA_INFO																*/
/*	Rev.(ZW04:BRZ-805)	change resarve->bill_dir							*/
/*--------------------------------------------------------------------------*/
typedef	struct
{
	MECHA_ORDER		order;
	MECHA_END_VALUE	end_value;
	short			error_code;
	short			status;
	short			bill_dir;
	short			position;
	short			part_position1;
	short			part_position2;
	short			part_position3;
} MECHA_INFO;
/*--------------------------------------------------------------------------*/
/*	MECHA_RESPONSE															*/
/*	Rev.(ZZ05:BRZ-190)	The label addition for six cassettes				*/
/*--------------------------------------------------------------------------*/
typedef	struct
{
	MECHA_INFO		ca1;
	MECHA_INFO		ca2;
	MECHA_INFO		ca3;
	MECHA_INFO		ca4;
	MECHA_INFO		ca5;
	MECHA_INFO		ca6;
	MECHA_INFO		pac;
	MECHA_INFO		esc;
	MECHA_INFO		rsv;
	MECHA_INFO		sep;
	MECHA_INFO		sht;
	MECHA_INFO		upper;
} MECHA_RESPONSE;
/*--------------------------------------------------------------------------*/
/*	MECHA_STOP																*/
/*--------------------------------------------------------------------------*/
typedef	struct
{
	UCHAR			*flagadr;
	char			sns;
	short			step;
	char			stop;
	MECHA_END_VALUE	ret_value;
} MECHA_STOP;
/*--------------------------------------------------------------------------*/
/*	MECHA_CONTROL															*/
/*--------------------------------------------------------------------------*/
#define		MAX_STOP_CNT	5

typedef	struct
{
	char			motor;
	char			dir;
	char			speed;
	char			excit;
	USHORT			step;
	char			stop;
	char			reserve;
	long			tmr;
	long			funcadr;
	UCHAR			*tupadr;
	MECHA_STOP		*stopadr[MAX_STOP_CNT];
} MECHA_CONTROL;
/*--------------------------------------------------------------------------*/
/*	Error Informations														*/
/*--------------------------------------------------------------------------*/
	/*----------------------------------------------------------------------*/
	/*	Error Table															*/
	/*	Rev.(ZW04:BRZ-841)	Add member of read log data request.			*/
	/*	Rev.(ZV02:BRZ-922)	Add member of end code.							*/
	/*----------------------------------------------------------------------*/
typedef	struct
{
		USHORT		code;			/*	error code							*/
		ERR_LEVEL	level;			/*	error level							*/
		ERR_PLACE	place;			/*	place which the error generated		*/
		UCHAR		log;			/*	read log data request				*/
		UCHAR		bEndCode;		/*	end code			(ZV02:BRZ-922)	*/
		UCHAR		dummy3;			/*	(dummy)								*/
		UCHAR		dummy4;			/*	(dummy)								*/
} ERR_TBL;
	/*----------------------------------------------------------------------*/
	/*	Error Information													*/
	/*	Rev.(ZV02:BRZ-922)	Add member of end code.							*/
	/*	Rev.(AA18:BRZ-1397)	Add member of log & rsv.						*/
	/*----------------------------------------------------------------------*/
typedef	struct
{
		ERR_LEVEL	level;			/*	error level							*/
		UCHAR		bEndCode;		/*	end code			(ZV02:BRZ-922)	*/
		USHORT		code;			/*	error code							*/
		UCHAR		*address;		/*	address which the error generated	*/
		ERR_PLACE	place[4];		/*	place which the error generated		*/
		UCHAR		log;			/*	read log data request				*/
		UCHAR		rsv[3];			/*	reserve								*/
} ERROR_INFORMATION;
/*--------------------------------------------------------------------------*/
/*	Command Information														*/
/*	Rev(ZZ04:BRZ-143)	add CMD_INFORMATION type							*/
/*--------------------------------------------------------------------------*/
typedef	struct
{
	USHORT	cmd;
	USHORT	reserve1;
	USHORT	reserve2;
} CMD_INFORMATION;
/*--------------------------------------------------------------------------*/
/*	Rev.(ZY06:BRZ-690)														*/
/*	Buffer Information														*/
/*	Rev.(ZW03:BRZ-765)	Change size.	( USHORT -> ULONG )					*/
/*--------------------------------------------------------------------------*/
typedef	struct
{
	UCHAR*	address;
	ULONG	length;
} BUFFER_INFO;
/*--------------------------------------------------------------------------*/
/*	END INFORMATION															*/
/*--------------------------------------------------------------------------*/
	/*----------------------------------------------------------------------*/
	/*	Rev.(ZV02:BRZ-922)	Movement definition.( l_resp.h -> typedef.h )	*/
	/*	END CODE															*/
	/*----------------------------------------------------------------------*/
enum{
	END_INFO_END_NORMAL 	= 'N',
	END_INFO_END_ERROR 		= 'E',
	END_INFO_END_PROCESSING	= 'B',
	END_INFO_END_RETRY		= 'R'
	};
/*--------------------------------------------------------------------------*/
/*	CASSETTE STATUS( compulsory storing note in Cassette )					*/
/*--------------------------------------------------------------------------*/
	/*----------------------------------------------------------------------*/
	/*	Rev.(AA41:BRZ-1512)	Cassette status definition.						*/
	/*----------------------------------------------------------------------*/
enum{
	CASSETTE_STATUS_NORMAL 		= 0x00,
	CASSETTE_STATUS_FULL		= 0x01,
	CASSETTE_STATUS_FULL_JAM	= 0x02
	};
