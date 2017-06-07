/***

	*************************************************************************
	*																		*
	*		Header of Command Module										*
	*																		*
	*														CMD.H			*
	*************************************************************************
	ALL RIGHTS RESERVED, COPYRIGHT(C) FUJITSU FRONTECH LIMITED. 2002-2007

	SN			Date		Name		Revision.No.	Contents
	-------------------------------------------------------------------------
	001-ZZ01	2002/10/31	M.Banba						The First Version
				2003/02/28	M.Banba						add CmdGetDestinationNote
	002-ZZ02	2003/04/16	M.Kamimura	<BRZ-005>		add CmdGetDestination()
															CmdUpdateDestination()
	003-ZZ04	2003/05/26	M.Kamimura	<BRZ-142>		add API function(for debug)
														:CmdDispJobFactor()
														:CmdDispFactor()
														:CmdDispNumberPresentBill()
														:CmdGetTableDest()
														:CmdGetEntryDest()
										<BRZ-143>		add API function
														:CmdGetInfo()
	004-ZZ05	2003/07/01	M.Kamimura	<BRZ-192>		add API function(for update Gx information)
														:CmdGetNumberDenomination()
				2003/07/03	M.Kamimura	<BRZ-193>		Delete API function(for movement definition)
														:CmdGetNumberDenomination()
	005-ZZ06	2003/07/14	M.Kamimura	<BRZ-225>		change argument and return value.
														:CmdGetDestination()
										<BRZ-230>		add transacation number acquisition function.
														:CmdGetTransNumber()
				2003/07/18	M.Kamimura	<BRZ-246>		add inspection function before command start.
														:CmdCheckParameter()
														:CmdCheckUnitSet()
														:CmdCheckPathMedia()
														:CmdCheckUnitMedia()
										<BRZ-251>		add inspection function for every parameter class.
														:CmdCheckParameterAx()
				2003/07/28	M.Kamimura	<BRZ-246>		movement function of parameter inspection.(To tsk_cmd.c)
														:CmdCheckParameterAx()
				2003/07/29	M.Kamimura	<BRZ-286>		add argument.(for error code set specification)
														:CmdCheckPathMedia()
				2003/08/20	M.Kamimura	<BRZ-316>		add API function.(for debug ras_3x)
														:CmdGetNumberFeed()
														:CmdGetMoveRequest()
	006-ZZ07	2003/09/10	M.Kamimura	<BRZ-360>		add API function.
														:CmdCheckSnsPath()
	007-ZY01	2003/10/03	M.Kamimura	<BRZ-409>		add API function.
														:CmdEntryDest()
				2003/10/07	M.Kamimura	<BRZ-409>		add Insertion / presenting limit timer label.
														:CMD_LIMIT_TIMER_IMMEDIATELY
														:CMD_LIMIT_TIMER_INFINITY
														movement function of media inspection.
														:CmdCheckUpperMedia()
				2003/10/17	M.Kamimura	<BRZ-421>		Add structures / label of parameter.
														:CMD_PARAM_xx
				2003/10/28	M.Kamimura	<BRZ-435>		Add function of command code setup.
														:CmdSetCmdCode()
	008-ZY02	2003/11/10	M.Kamimura	<BRZ-456>		Add API function.
														:CmdCheckReject()
				2003/11/12	M.Kamimura	<BRZ-464>		Add definition of check denomination code.
														:CMD_GENERATION_xxx
														:CMD_PUBLICATION_x
				2003/11/27	M.Kamimura	<BRZ-506>		Change definition value.
														:CMD_CORRECT_xxx
	009-ZY03	2003/12/08	M.Kamimura	<BRZ-534>		Change max value of draw start.
														:CMD_IO_MAX_START_DRAW
	010-ZY04	2003/12/15	M.Kamimura	<BRZ-543>		Add detination of suspect note.
														:CMD_DEST_xxx
														:CMD_PARAM_A2
														:CMD_PARAM_A5
				2003/12/16	M.Kamimura	<BRZ-560>		Add API function.
														:CmdGetEntryFeedPlace()
				2003/12/17	M.Kamimura	<BRZ-566>		Division response correspondence.
														:CMD_DIVISION_INFO
														:CmdGetDivisionInfo()
														:CmdSetDivisionxxx()
														:CmdCntUpDivisionBlock()
				2003/12/18	M.Kamimura	<BRZ-567>		Add label of parameter A5.
														:CMD_SIGNATURE_xxx
				2003/12/22	M.Kamimura	<BRZ-543>		Add reserve area.
														:CMD_PARAM_A5
				2003/12/24	M.Kamimura	<BRZ-566>		Delete division information.(->RESP_REQUEST)
														:CMD_DIVISION_INFO
														:CmdGetDivisionInfo()
														:CmdSetDivisionxxx()
														:CmdCntUpDivisionBlock()
	011-ZY05	2004/01/06	M.Banba		<BRZ-610>		Outside bill number-of-sheets exaggerated correspondence for payment
				2004/01/13	M.Kamimura	<BRZ-616>		Add API function.
														:CmdGetCategorySignature()
														:CmdGetIndexSignature()
														:CmdxxxBvBlockNumber()
										<BRZ-623>		Add API function.
														:CmdClearAcceptDenomination()
	012-ZY06	2004/01/22	M.Kamimura	<BRZ-669>		Add API function.
														:CmdxxxEncryptType()
										<BRZ-671>		add definition of parameter A0 type.
														:CMD_PARAM_A0
				2004/01/26	M.Kamimura	<BRZ-688>		Add API function.
														:CmdCheckAcceptDenomination()
	013-ZW01	2004/02/03	M.Kamimura	<BRZ-708>		Add API function.
														:CmdCheckDisappearMedia()
				2004/02/05	M.Kamimura	<BRZ-714>		Add API function.
														:CmdSetTransNumber()
										<BRZ-718>		Add processing of accept note over.
														:CmdSetAcceptStartPtr()
				2004/02/07	M.Kamimura	<BRZ-707>		Add API function.
														:CmdxxxFactorAfterDraw()
										<BRZ-722>		Add definition of min length.
														:CMD_MIN_LENGTH_Ax
	014-ZW03	2004/02/17	M.Kamimura	<BRZ-742>		Add API function.
														:CmdCheckJobFactor()
				2004/02/24	M.Kamimura	<BRZ-764>		Add API function.
														:CmdCheckMoneyTrouble()
	015-ZW04	2004/03/05	M.Kamimura	<BRZ-800>		Add API function.
														:CmdGetFeedPlace()
										<BRZ-802>		Add API function.
														:CMD_REQUEST_BV_xxx
														:CmdxxxModeBV()
				2004/03/23	M.Kamimura	<BRZ-862>		Add API function.
														:CmdSetKeepTDCM()
														:CmdStopMotor()
				2004/03/27	M.Kamimura	<BRZ-877>		Add API function.
														:CmdInitializePressDraw()
														:CmdGetPressStep()
				2004/03/31	A.Maruyama	<BRZ-892>		add functions
														:CmdInitializeRecBuf()
														:CmdReleaseRecBuf()
							M.Kamimura	<BRZ-893>		Add API function.
														:CmdResponseBufFree()
	016-ZV03	2004/04/12	M.Kamimura	<BRZ-916>		Add API function.
														:CmdxxxPlaceAfterDraw()
														:CmdGetKeepTDCM()
	017-ZV08	2004/05/11	M.Kamimura	<BRZ-1005>		Add API function.
														:CmdCheckHalfNote()
				2004/05/14	M.Kamimura	<BRZ-1020>		Add argument of Reject inspection.
														:CmdCheckReject()
				2004/05/17	M.Kamimura	<BRZ-1026>		Add return value of get destination function.
														:CmdGetDestination()
	018-ZV10	2004/05/19	M.Kamimura	<BRZ-1031>		Add API function.
														:CmdIntervalTmrReStart()
	019-ZU03	2004/05/21	M.Kamimura	<BRZ-1029>		Add API function.
														:CmdFreeMotor()
														:CmdSetFeedInfo()
														:CmdGetJobEndFactor()
														:CmdGetIntEndFactor()
				2004/05/24	M.Kamimura	<BRZ-1041>		Add definition of Transport check disable.
														:CMD_PATH_CHECK_xxx
														:bPathCheck
	020-ZT02	2004/06/14	M.Kamimura	<BRZ-1111>		Add definition of Destination of damaged note.
														:bDamagedDest
	021-ZT10	2004/07/12	M.Kamimura	<BRZ-1149>		Add API function.
														:CmdGetDischargeLength()
				2004/07/14	M.Kamimura	<BRZ-1156>		Add API function.
														:CmdSetHandleDenomi()
														:CmdUpdateHandleDenomi()
										<BRZ-1158>		Add maximum number of accepted note. (A5-No.15)
														:bMaxAccept
										<BRZ-1159>		Add thickness of handling notes. (A1-No.5)
														:bThickness
										<BRZ-1160>		Delete priority of storing storage Ca.
														:bFeedPriority
	022-AA04	2004/08/06	M.Kamimura	<BRZ-1188>		Add API function.(Response request)
														:CmdResponseRequest()
										<BRZ-1190>		Add API function. (Sensor change record)
														:CmdxxxSensorChange()
				2004/08/12	M.Kamimura	<BRZ-1199>		Add API function. (Existence of insertion)
														:CmdxxxProcessInsert()
	023-AA06	2004/09/13	M.Kamimura	<BRZ-1244>		Add function for accept.(A5-No.34)
														:CMD_FUNC_xxx
														:bFuncAccept
				2004/09/14	M.Kamimura	<BRZ-1246>		Add control for foreign object.(A5-No.33)
														:CMD_CONTROL_xxx
														:bForeignObject
														:CmdCheckForeignObject()
	024-AA10	2004/10/08	M.Kamimura	<BRZ-1297>		Add API function.(Processing division)
														:CmdCheckTransportRemain()
	025-AA13	2004/11/08	M.Kamimura	<BRZ-1342>		Add control for acceptable denomination.(A5-No.46-174)
														:bNumberAcceptDenomi
														:CMD_PARAM_A5_ADD
														:CmdGetAddressA5Add()
	026-AA18	2005/03/07	M.Kamimura	<BRZ-1396>		Add validation mode of BV check.
														:CMD_VALIDATION_BV_CHECK
	027-AA19	2005/03/22	M.Kamimura	<BRZ-1405>		Add parameter A5-No.35,36.(Additional pushing out note)
														:CMD_PARAM_A5
										<BRZ-1406>		Add SK mode of idle preparation.
														:CMD_SK_IDLE
	028-AA21	2005/06/01	M.Kamimura	<BRZ-1429>		Add label of destination specify.(A5-No.12,13)
														:CMD_DEST_SAME_GENUINE
														Add type of parameter AA.
														:CMD_PARAM_AA
	029-AA31	2006/05/31	M.Kamimura	<BRZ-1482>		Add label of destination specify.(A5-No.10)
														:CMD_SPECIFY_DEST_3
	030-AA33	2006/07/03	M.Kamimura	<BRZ-1486>		Signature near full measures
														- Add function of set / get BV signature mode.
														:CmdSetExtSignatureBV()
														:CmdGetExtSignatureBV()
														- Add function of counterfeit over check.
														:CmdCheckCounterfeitOver()
	031-AA35	2006/09/14	M.Kamimura	<BRZ-1494>		Escrow reject measures
														- Add label of destination specify.(A5-No.10)
														:CMD_SPECIFY_DEST_4
	032-AA36	2006/11/01	M.Banba		<BRZ-1498>		for Direct deposit
														- Add label of Function for accept(A5-No.34)
														:CMD_FUNC_DIRECT_DEPOSIT
	033-AA38	2006/12/18	M.Banba		<BRZ-1509>		for Direct deposit function enhancing
														- Add label of destination for direct deposit(A5-No.16)
														- Add function
														  :CmdSetRejectFullDirectDeposit()
	034-AA40	2007/01/18	M.Kibe		<BRZ-1511>		Making to option for Reservoir stage diving crowding.
														- Add label of destination for Improved Reservoir Control(A1-No.15)
	035-AA41	2007/01/23	M.Kibe		<BRZ-1512>		for cassette storage capacity improvement FW.
														- Add label of destination for Minimum dimensiton for compulsory storing note in cassette(A5-No.9-12)
				2007/01/24	A.Maruyama	<BRZ-1514>		Add ECB6-Certification-Mode
	036-AA43	2007/02/27	A.Kojima	<BRZ-1520>		support for cheque
														:CMD_VALIDATION_CHEQUE add
														:CMD_PARAM_A5
	037-AA44	2007/04/09	A.Maruyama	<BRZ-1527>		support for detached processing
														add functions
														:CmdSetDetachedRequestPlace()
														:CmdGetDetachedRequestPlace()
														:CmdUpdateDetachedDrawPlace()
														:CmdGetDetachedDrawPlace()
														:CmdUpdateDetachedStackPlace()
														:CmdGetDetachedStackPlace()
														:CmdClearDetachedPlace()
	038-AA48	2007/05/24	A.Maruyama	<BRZ-1535>		support PD,BE-command
														:CmdSetDisableFullStopPlase()
														:CmdCheckDisableFullStopPlase()
														Add argument on CmdCheckMoneyTrouble()
														:CmdCheckMoneyTrouble()
				2007/06/07	A.Kojima	<BRZ-1530>		improve the data transfer speed
														-change for D-Level frame size change
														:CMD_VARIOUS_LINE_FRAME_MODE add
														:CMD_PARAM_A1
				2007/06/22	A.Maruyama	<BRZ-1540>		Add Pre-acceptor transport control mode
														:CMD_PARAM_A5
	039-AA49	2007/07/25	M.Kibe		<BRZ-1544>		Add Separator Stage control mode
														:CMD_PARAM_A5
														Add enum 
				2007/07/26	M.Kibe		<BRZ-1545>		change Pre-acceptor transport control mode
														(The logic of a specified value is changed oppositely. )
COMMENT END
***/

/****************************************************************************/
/*																			*/
/*	defines																	*/
/*																			*/
/****************************************************************************/
	/*----------------------------------------------------------------------*/
	/*	Table size															*/
	/*	Rev.(ZY01:BRZ-421)	add definition of parameter.					*/
	/*----------------------------------------------------------------------*/
#define		CMD_MAX_KIND_FEED		0x06
#define		CMD_MAX_ENTRY_FEED		0x06
#define		CMD_MAX_ENTRY_DEST_CA	0x06
#define		CMD_MAX_ENTRY_DEST		0x05
	/*----------------------------------------------------------------------*/
	/*	Parameter data definition.											*/
	/*	Rev.(ZY01:BRZ-421)	add definition of parameter.					*/
	/*----------------------------------------------------------------------*/
		/*------------------------------------------------------------------*/
		/*	Common															*/
		/*------------------------------------------------------------------*/
			/*--------------------------------------------------------------*/
			/*	Maximum number definition									*/
			/*--------------------------------------------------------------*/
enum
{
	CMD_MAX_NOT_RECOGNIZED		= 0x32,
	CMD_MAX_DIFFERENT			= 0x32,
	CMD_MAX_COUNTERFEIT			= 0x19,
	CMD_MAX_DISPENSE			= 0xC8,
	CMD_MAX_PAYMENT				= 0xC8,
	CMD_MAX_OUTSIDE				= 0x1E,				/* Rev.(ZY05:BRZ-610)	*/
	CMD_MAX_RECORD_DENOMINATION	= 0xD2				/* Rev.(ZY05:BRZ-623)	*/
};
			/*--------------------------------------------------------------*/
			/*	Validation mode												*/
			/*	Rev.(AA18:BRZ-1396)	Add validation mode of BV check.		*/
			/*	Rev.(AA43:BRZ-1520)	Add validation mode of cheque.			*/
			/*--------------------------------------------------------------*/
enum
{
	CMD_VALIDATION_REAL			= 0x00,
	CMD_VALIDATION_TEST			= 0x01,
	CMD_VALIDATION_BV_CHECK		= 0x02,
	CMD_VALIDATION_CHEQUE		= 0x03
};
			/*--------------------------------------------------------------*/
			/*	Cassette priority											*/
			/*--------------------------------------------------------------*/
enum
{
	CMD_PRIORITY_NONE			= 0x00,
	CMD_PRIORITY_CA1			= 0x01,
	CMD_PRIORITY_CA2			= 0x02,
	CMD_PRIORITY_CA3			= 0x03,
	CMD_PRIORITY_CA4			= 0x04
};
			/*--------------------------------------------------------------*/
			/*	Destination													*/
			/*	Rev.(ZY04:BRZ-543)	Add detination specify label.			*/
			/*	Rev.(ZT02:BRZ-1111)	Add damaged note specify label.			*/
			/*	Rev.(AA21:BRZ-1429)	Add same as genuine note specify label.	*/
			/*--------------------------------------------------------------*/
enum
{
	CMD_DEST_DEFAULT			= 0x00,
	CMD_DEST_ESC				= 0x00,
	CMD_DEST_RSV				= 0x01,
	CMD_DEST_RJT				= 0x02,
	CMD_DEST_CPT				= 0x03,
	CMD_DEST_SUSPECT_CA			= 0x04,
	CMD_DEST_TEMP_CA			= 0x05,
	CMD_DEST_DAMAGED_CA			= 0x06,
	CMD_DEST_SAME_GENUINE		= 0x07
};
			/*--------------------------------------------------------------*/
			/*	Destination	of direct deposit								*/
			/*	Rev.(AA38:BRZ-1509)	Add detination specify label.			*/
			/*--------------------------------------------------------------*/
enum
{
	CMD_DEST_DIRECT_0			= 0x00,
	CMD_DEST_DIRECT_CPT			= 0x01,
	CMD_DEST_DIRECT_RJT			= 0x02,
	CMD_DEST_DIRECT_FIT			= 0x04
};
		/*------------------------------------------------------------------*/
		/*	Prameter A0														*/
		/*------------------------------------------------------------------*/
#define		CMD_MAX_TARGET_INFO		0x1F
		/*------------------------------------------------------------------*/
		/*	Prameter A1														*/
		/*------------------------------------------------------------------*/
			/*--------------------------------------------------------------*/
			/*	Rev.(ZW01:BRZ-722)	Add definition of min length.			*/
			/*--------------------------------------------------------------*/
#define		CMD_MIN_LENGTH_A1		0x14
			/*--------------------------------------------------------------*/
			/*	No.3		Mechanical retry forbid							*/
			/*--------------------------------------------------------------*/
enum
{
	CMD_RETRY_DISABLE			= 0x00,
	CMD_RETRY_ENABLE			= 0x01
};
			/*--------------------------------------------------------------*/
			/*	No.4		ECB6 mode										*/
			/*--------------------------------------------------------------*/
enum
{
	CMD_ECB6_DISABLE			= 0x00,
	CMD_ECB6_ENABLE				= 0x01
};
			/*--------------------------------------------------------------*/
			/*	No.5		Thickness of handlinig notes					*/
			/*	Rev.(ZT10:BRZ-1159)	Add definition of thickness specify. 	*/
			/*--------------------------------------------------------------*/
enum
{
	CMD_THICKNESS_DEFAULT		= 0x00,
	CMD_THICKNESS_THIN			= 0x01,
	CMD_THICKNESS_THICK			= 0x02
};
			/*--------------------------------------------------------------*/
			/*	No.6		ECB6 certification mode							*/
			/*	Rev.(AA41:BRZ-1514)	Add this mode							*/
			/*--------------------------------------------------------------*/
enum
{
	CMD_ECB6_CERTIFICATION_DISABLE		= 0x00,
	CMD_ECB6_CERTIFICATION_ENABLE		= 0x01
};
			/*--------------------------------------------------------------*/
			/*	No.7		Various mode									*/
			/*	Rev.(AA48:BRZ-1530)	Add this mode							*/
			/*--------------------------------------------------------------*/
enum
{
	CMD_VARIOUS_LINE_FRAME_MODE			= 0x01
};
			/*--------------------------------------------------------------*/
			/*	No.15		Improved Reservoir Control						*/
			/*	Rev.(AA40:BRZ-1511)											*/
			/*	Add definition of Improved Reservoir Control.				*/
			/*--------------------------------------------------------------*/
enum
{
	CMD_IMPROVED_CONTROL_DISABLE		= 0x00,
	CMD_IMPROVED_CONTROL_ENABLE			= 0x01
};
			/*--------------------------------------------------------------*/
			/*	No.17-144	Denomination code								*/
			/*				- Generation label								*/
			/*				- Publication label								*/
			/*	Rev.(ZY02:BRZ-464)	Add definition of check denomination.	*/
			/*--------------------------------------------------------------*/
enum
{
	CMD_GENERATION_1ST			= 0x00,
	CMD_GENERATION_2ND			= 0x10,
	CMD_GENERATION_3RD			= 0x20,
	CMD_GENERATION_4TH			= 0x30,
	CMD_GENERATION_5TH			= 0x40,
	CMD_GENERATION_6TH			= 0x50,
	CMD_GENERATION_7TH			= 0x60,
	CMD_GENERATION_8TH			= 0x70,
	CMD_GENERATION_MASK			= 0xFF
};
enum
{
	CMD_PUBLICATION_1			= 0x00,
	CMD_PUBLICATION_2			= 0x01,
	CMD_PUBLICATION_3			= 0x02,
	CMD_PUBLICATION_4			= 0x03,
	CMD_PUBLICATION_5			= 0x04,
	CMD_PUBLICATION_6			= 0x05,
	CMD_PUBLICATION_7			= 0x06,
	CMD_PUBLICATION_8			= 0x07,
	CMD_PUBLICATION_MASK		= 0xFF
};
		/*------------------------------------------------------------------*/
		/*	Prameter A2														*/
		/*------------------------------------------------------------------*/
		/*------------------------------------------------------------------*/
		/*	Prameter A5														*/
		/*------------------------------------------------------------------*/
			/*--------------------------------------------------------------*/
			/*	SK mode 													*/
			/*	Rev.(AA19:BRZ-1406)	Add mode of idle preparation.			*/
			/*--------------------------------------------------------------*/
enum
{
	CMD_SK_DEPOSIT				= 0x00,
	CMD_SK_DISPENSE				= 0x01,
	CMD_SK_ACCEPT				= 0x02,
	CMD_SK_IDLE					= 0x03
};
			/*--------------------------------------------------------------*/
			/*	Draw / Close start timer (Max value)						*/
			/*	Rev.(ZY03:BRZ-534)	Change value of draw. ( 0x63 -> 0xFF )	*/
			/*--------------------------------------------------------------*/
enum
{
	CMD_IO_MAX_START_DRAW		= 0xFF,
	CMD_IO_MAX_START_CLOSE		= 0x63
};
			/*--------------------------------------------------------------*/
			/*	Insertion / Presenting limit timer							*/
			/*	Rev.(ZY01:BRZ-409)	Add limit timer label.					*/
			/*--------------------------------------------------------------*/
enum
{
	CMD_LIMIT_TIMER_IMMEDIATELY	= 0x00,
	CMD_LIMIT_TIMER_INFINITY	= 0xFF
};
			/*--------------------------------------------------------------*/
			/*	Back mode 													*/
			/*	Rev(ZZ06:BRZ-319)	add back mode definition				*/
			/*--------------------------------------------------------------*/
enum
{
	CMD_MODE_BACK_0				= 0x00,
	CMD_MODE_BACK_1				= 0x01
};
			/*--------------------------------------------------------------*/
			/*	Destination of note											*/
			/*	Rev.(AA31:BRZ-1482)	add label of CMD_SPECIFY_DEST_3.		*/
			/*	Rev.(AA35:BRZ-1494)	add label of CMD_SPECIFY_DEST_4.		*/
			/*--------------------------------------------------------------*/
enum
{
	CMD_SPECIFY_DEST_0			= 0x00,
	CMD_SPECIFY_DEST_1			= 0x01,
	CMD_SPECIFY_DEST_2			= 0x02,
	CMD_SPECIFY_DEST_3			= 0x03,
	CMD_SPECIFY_DEST_4			= 0x04
};
			/*--------------------------------------------------------------*/
			/*	Transport check disable										*/
			/*	Rev.(ZU03:BRZ-1041)	Add transport check disable.			*/
			/*--------------------------------------------------------------*/
enum
{
	CMD_PATH_CHECK_ENABLE		= 0x00,
	CMD_PATH_CHECK_DISABLE		= 0x01
};
			/*--------------------------------------------------------------*/
			/*	Category of signature										*/
			/*	Rev.(ZY04:BRZ-567)	Add category of signature.				*/
			/*--------------------------------------------------------------*/
enum
{
	CMD_SIGNATURE_GENUINE		= 0x00,
	CMD_SIGNATURE_DAMAGED		= 0x01,
	CMD_SIGNATURE_SUSPECT		= 0x03,
	CMD_SIGNATURE_COUNTERFEIT	= 0x04
};
			/*--------------------------------------------------------------*/
			/*	Control for foreign object									*/
			/*	Rev.(AA06:BRZ-1246)	Add control for foreign object.			*/
			/*--------------------------------------------------------------*/
enum
{
	CMD_CONTROL_NORMAL			= 0x00,
	CMD_CONTROL_FOREIGN_OBJECT	= 0x01
};
			/*--------------------------------------------------------------*/
			/*	Function for accept											*/
			/*	Rev.(AA06:BRZ-1244)	Add function for accept.				*/
			/*	Rev.(AA36:BRZ-1498)	Add	CMD_FUNC_DIRECT_DEPOSIT				*/
			/*--------------------------------------------------------------*/
enum
{
	CMD_FUNC_ALL				= 0x00,
	CMD_FUNC_VALIDATION			= 0x02,
	CMD_FUNC_DIRECT_DEPOSIT		= 0x03
};
			/*--------------------------------------------------------------*/
			/*	Pre-acceptor transport control mode							*/
			/*	Rev.(AA48:BRZ-1540)	Add this control-mode					*/
			/*	Rev.(AA49:BRZ-1545)											*/
			/*	The logic of a specified value is changed oppositely. 		*/
			/*--------------------------------------------------------------*/
enum
{
	CMD_PAC_CONTROL_DISABLE		= 0x00,
	CMD_PAC_CONTROL_ENABLE		= 0x01
};
			/*--------------------------------------------------------------*/
			/*	Separator Stage control mode								*/
			/*	Rev.(AA49:BRZ-1544)	Add this control-mode					*/
			/*--------------------------------------------------------------*/
enum
{
	CMD_SEP_CONTROL_DISABLE		= 0x00,
	CMD_SEP_CONTROL_ENABLE		= 0x01
};
		/*------------------------------------------------------------------*/
		/*	Prameter A6														*/
		/*------------------------------------------------------------------*/
			/*--------------------------------------------------------------*/
			/*	Correct place number										*/
			/*	Rev.(ZY02:BRZ-506)	Change value.(FIT,RJT,CPT)				*/
			/*--------------------------------------------------------------*/
enum
{
	CMD_CORRECT_CA1				= 0x00,
	CMD_CORRECT_CA2				= 0x01,
	CMD_CORRECT_CA3				= 0x02,
	CMD_CORRECT_CA4				= 0x03,
	CMD_CORRECT_FIT				= 0x06,
	CMD_CORRECT_RJT				= 0x07,
	CMD_CORRECT_CPT				= 0x08,
	CMD_CORRECT_END				= 0x0C,
};
			/*--------------------------------------------------------------*/
			/*	Correct specify												*/
			/*--------------------------------------------------------------*/
enum
{
	CMD_CORRECT_DISABLE			= 0x00,
	CMD_CORRECT_ENABLE			= 0x01
};
			/*--------------------------------------------------------------*/
			/*	Correct maximum number	(9999)								*/
			/*--------------------------------------------------------------*/
#define		CMD_MAX_NUMBER_CORRECT	0x270F
		/*------------------------------------------------------------------*/
		/*	Prameter A9														*/
		/*------------------------------------------------------------------*/
			/*--------------------------------------------------------------*/
			/*	Rev.(ZW01:BRZ-722)	Add definition of min length.			*/
			/*--------------------------------------------------------------*/
#define		CMD_MIN_LENGTH_A9		0x08
	/*----------------------------------------------------------------------*/
	/*	BV request mode definition.											*/
	/*	Rev.(ZW04:BRZ-802)	add definition of BV request mode.				*/
	/*----------------------------------------------------------------------*/
enum
{
	CMD_REQUEST_BV_NOTHING		= 0x00,
	CMD_REQUEST_BV_VALIDATE		= 0x01,
	CMD_REQUEST_BV_SNS_ON		= 0x02
};

/****************************************************************************/
/*																			*/
/*	structures									 							*/
/*																			*/
/****************************************************************************/
	/*----------------------------------------------------------------------*/
	/*	Parameter parts definition.											*/
	/*----------------------------------------------------------------------*/
typedef	struct{
	ULONG			code;						/*	Denomination Code		*/
	USHORT			number;						/*	Number of note			*/
	USHORT			reserve;					/*	Reserve					*/
	} CMD_DISPENSE;
	/*----------------------------------------------------------------------*/
	/*	Parameter storing domain.											*/
	/*	Rev.(ZY01:BRZ-421)	add definition of parameter.					*/
	/*----------------------------------------------------------------------*/
		/*------------------------------------------------------------------*/
		/*	Prameter A0														*/
		/*	Rev.(ZY06:BRZ-671)	add definition of parameter A0 type.		*/
		/*------------------------------------------------------------------*/
typedef	struct{
	USHORT			wTargetInfoCode[CMD_MAX_TARGET_INFO];		/*	Target information code			*/
	} CMD_PARAM_A0;
		/*------------------------------------------------------------------*/
		/*	Prameter A1														*/
		/*	Rev.(ZT10:BRZ-1159)	Add thickness of handlinig notes.			*/
		/*	Rev.(AA40:BRZ-1511)	Add  Improved Reservoir Control.			*/
		/*	Rev.(AA41:BRZ-1512)	Add  compulsory storing note in CAx.		*/
		/*	Rev.(AA41:BRZ-1514)	Add  ECB6 certification mode.				*/
		/*	Rev.(AA48:BRZ-1530)	Add  Various mode.							*/
		/*------------------------------------------------------------------*/
typedef	struct{
	UCHAR			bMaxNotRecognized;							/*	Maximum not recognized			*/
	UCHAR			bMaxDifferent;								/*	Maximum different denomination	*/
	UCHAR			bRetryForbid;								/*	Mechanical retry forbid			*/
	UCHAR			bModeECB6;									/*	ECB6 mode						*/
	UCHAR			bThickness;									/*	Thickness of handlinig notes	*/
	UCHAR			bModeCertificationECB6;						/*	ECB6 certification mode			*/
	UCHAR			bVariousMode;								/*	Various mode					*/
	UCHAR			bReserve4;									/*	Reserve							*/
	UCHAR			bCompulsoryStoringCa1;						/*	Compulsory storing note in CA1	*/
	UCHAR			bCompulsoryStoringCa2;						/*	Compulsory storing note in CA2	*/
	UCHAR			bCompulsoryStoringCa3;						/*	Compulsory storing note in CA3	*/
	UCHAR			bCompulsoryStoringCa4;						/*	Compulsory storing note in CA4	*/
	UCHAR			bReserve9;									/*	Reserve							*/
	UCHAR			bReserve10;									/*	Reserve							*/
	UCHAR			bImprovedReservoirControl;					/*	Reservoir Control				*/
	UCHAR			bNumberDenomination;						/*	Number of handling denomination	*/
	ULONG			lCodeDenomination[KIND_BILL_GENUINE_MAX];	/*	Handling denominations			*/
	} CMD_PARAM_A1;
		/*------------------------------------------------------------------*/
		/*	Prameter A2														*/
		/*	Rev.(ZY04:BRZ-543)	Add destination of suspect note.			*/
		/*	Rev.(ZT02:BRZ-1111)	Add destination of damaged note.			*/
		/*------------------------------------------------------------------*/
typedef	struct{
	USHORT			wTransactionNumber;							/*	Transaction number				*/
	UCHAR			bValidationMode;							/*	Validation mode					*/
	UCHAR			bSuspectDest;								/*	Destination of Suspect note		*/
	UCHAR			bDamagedDest;								/*	Destination of Damaged note		*/
	UCHAR			bReserve3;									/*	Reserve							*/
	UCHAR			bReserve4;									/*	Reserve							*/
	UCHAR			bReserve5;									/*	Reserve							*/
	UCHAR			bDispensePriority[CMD_MAX_ENTRY_FEED];		/*	Dispensing cassette priority	*/
	UCHAR			bReserve6;									/*	Reserve							*/
	UCHAR			bReserve7;									/*	Reserve							*/
	CMD_DISPENSE	stDispenseNote[CMD_MAX_KIND_FEED];			/*	Dispense denomination / number	*/
	} CMD_PARAM_A2;
		/*------------------------------------------------------------------*/
		/*	Prameter A5														*/
		/*	Rev.(ZY04:BRZ-543)												*/
		/*	Add destination of suspect note.								*/
		/*	Add Category / Index of signature.								*/
		/*	Change parameter size.	( 32 -> 48 )							*/
		/*	Rev.(ZU03:BRZ-1041)												*/
		/*	Add Transport check disable.									*/
		/*	Rev.(ZT02:BRZ-1111)	Add destination of damaged note.			*/
		/*	Rev.(ZT10:BRZ-1158)	Add maximum number of accepted note.		*/
		/*	Rev.(ZT10:BRZ-1160)	Delete priority of storing storage Ca.		*/
		/*	Rev.(AA06:BRZ-1244)	Add function for accept.					*/
		/*	Rev.(AA06:BRZ-1246)	Add control for foreign object.				*/
		/*	Rev.(AA13:BRZ-1342)	Add control for acceptable denomination.	*/
		/*	Rev.(AA19:BRZ-1405)	Add parameter A5-No.35,36. (Add push out)	*/
		/*	Rev.(AA38:BRZ-1509)	Add destination of direct deposit.			*/
		/*	Rev.(AA43:BRZ-1520)	Add kind of cheque image.					*/
		/*	Rev.(AA48:BRZ-1540)	Add Pre-acceptor transport control mode		*/
		/*	Rev.(AA49:BRZ-1544)	Add Separator Stage control mode			*/
		/*------------------------------------------------------------------*/
typedef	struct{
	USHORT			wTransactionNumber;							/*	Transaction number				*/
	UCHAR			bValidationMode;							/*	Validation mode					*/
	UCHAR			bModeSK;									/*	SK mode							*/
	UCHAR			bIndicatorTmr;								/*	Media Indicator interval timer	*/
	UCHAR			bDrawStartTmr;								/*	Media draw start timer			*/
	UCHAR			bInsertLimitTmr;							/*	Insertion limit timer			*/
	UCHAR			bCloseStartTmr;								/*	Shutter close start timer		*/
	UCHAR			bPresentLimitTmr;							/*	Presenting limit timer			*/
	UCHAR			bModeBK;									/*	Back mode						*/
	UCHAR			bSpecifyDest;								/*	Destination of note				*/
	UCHAR			bTargetCa;									/*	Target cassette					*/
	UCHAR			bSuspectDest;								/*	Destination of Suspect note		*/
	UCHAR			bDamagedDest;								/*	Destination of Damaged note		*/
	UCHAR			bPathCheck;									/*	Transport check disable			*/
	UCHAR			bMaxAccept;									/*	Maximum number of accepted note	*/
	UCHAR			bDirectDopositDest;							/*	Destination of direct deposit	*/
	UCHAR			bReserve2;									/*	Reserve							*/
	UCHAR			bReserve3;									/*	Reserve							*/
	UCHAR			bReserve4;									/*	Reserve							*/
	UCHAR			bReserve5;									/*	Reserve							*/
	UCHAR			bReserve6;									/*	Reserve							*/
	UCHAR			bReserve7;									/*	Reserve							*/
	UCHAR			bReserve8;									/*	Reserve							*/
	UCHAR			bStorePriority[CMD_MAX_ENTRY_DEST_CA];		/*	Priority of storing storage Ca	*/
	UCHAR			bReserve9;									/*	Reserve							*/
	UCHAR			bCategorySignature;							/*	Category of signature			*/
	USHORT			wIndexSignature;							/*	Index of signature				*/
	UCHAR			bForeignObject;								/*	Control for foreign object		*/
	UCHAR			bFuncAccept;								/*	Function for accept				*/
	UCHAR			bAddPushCnt;								/*	Additional pushing out number	*/
	UCHAR			bAddPushTmr;								/*	Additional pushing out timer	*/
	UCHAR			bKindChequeImage;							/*	Kind of cheque image			*/
	UCHAR			bControlPAC;								/*	Pre-acceptor transport control mode	*/
	UCHAR			bControlSEP;								/*	Separator Stage control mode	*/
	UCHAR			bReserve17;									/*	Reserve							*/
	UCHAR			bReserve18;									/*	Reserve							*/
	UCHAR			bReserve19;									/*	Reserve							*/
	UCHAR			bReserve20;									/*	Reserve							*/
	UCHAR			bReserve21;									/*	Reserve							*/
	UCHAR			bReserve22;									/*	Reserve							*/
	UCHAR			bNumberAcceptDenomi;						/*	Number of acceptable denomi		*/
	} CMD_PARAM_A5;
		/*------------------------------------------------------------------*/
		/*	Additional A5 parameter	(Acceptabl denomination code)			*/
		/*	Rev.(AA13:BRZ-1342)	Add definition of additional A5.			*/
		/*------------------------------------------------------------------*/
typedef	struct{
	ULONG			lCodeDenomination[KIND_BILL_GENUINE_MAX];	/*	Handling denominations			*/
	} CMD_PARAM_A5_ADD;
		/*------------------------------------------------------------------*/
		/*	Prameter A6														*/
		/*------------------------------------------------------------------*/
typedef	struct{
	UCHAR			bCorrectPlace[CMD_CORRECT_END];				/*	Correct place					*/
	USHORT			wCorrectNumber[CMD_CORRECT_END];			/*	Correction number of note		*/
	} CMD_PARAM_A6;
		/*------------------------------------------------------------------*/
		/*	Prameter A7														*/
		/*------------------------------------------------------------------*/
typedef	struct{
	USHORT			wTargetCode;								/*	Target information code			*/
	} CMD_PARAM_A7;
		/*------------------------------------------------------------------*/
		/*	Prameter A8														*/
		/*------------------------------------------------------------------*/
typedef	struct{
	UCHAR			bEncryptionKey[16];							/*	Encryption key					*/
	} CMD_PARAM_A8;
		/*------------------------------------------------------------------*/
		/*	Prameter A9														*/
		/*------------------------------------------------------------------*/
typedef	struct{
	UCHAR			bTargetCassette;							/*	Target cassette position		*/
	UCHAR			bReserve1;									/*	Reserve							*/
	UCHAR			bReserve2;									/*	Reserve							*/
	UCHAR			bNumberDenomination;						/*	Number of denomination			*/
	ULONG			lCodeDenomination[KIND_BILL_GENUINE_MAX];	/*	Denomination					*/
	} CMD_PARAM_A9;
		/*------------------------------------------------------------------*/
		/*	Prameter AA														*/
		/*	Rev.(AA21:BRZ-1431)	Add definition of parameter AA type.		*/
		/*------------------------------------------------------------------*/
typedef	struct{
	UCHAR			bSerialNumber[64];							/*	Unit serial number				*/
	} CMD_PARAM_AA;
		/*------------------------------------------------------------------*/
		/*	Prameter H0														*/
		/*------------------------------------------------------------------*/
typedef	struct{
	UCHAR			bBlockNumber[4];							/*	block number					*/
	UCHAR			bFileName[12];								/*	file name						*/
	UCHAR			bProgramData[MAX_SIZE_MESSAGE_DATA-4-12];	/*	program datas					*/
	} CMD_PARAM_H0;
		/*------------------------------------------------------------------*/
		/*	Prameter K0														*/
		/*------------------------------------------------------------------*/
typedef	struct{
	UCHAR			bRasCmd[2];									/*	RAS command						*/
	UCHAR			bOperand1[2];								/*	Operand1						*/
	UCHAR			bOperand2[2];								/*	Operand2						*/
	UCHAR			bOperand3[2];								/*	Operand3						*/
	} CMD_PARAM_K0;
/****************************************************************************/
/*																			*/
/*	function prototypes							 							*/
/*																			*/
/****************************************************************************/
/*--------------------------------------------------------------------------*/
/*	API function															*/
/*	Rev.(ZZ06:BRZ-225)	change argument and return value.					*/
/*	Rev.(ZZ06:BRZ-230)	add CmdGetTransNumber().							*/
/*	Rev.(ZY01:BRZ-409)	add CmdEntryDest().									*/
/*	Rev.(ZY01:BRZ-435)	add CmdSetCmdCode().								*/
/*	Rev.(ZY05:BRZ-616)	add CmdxxxBvBlockNumber().							*/
/*						add CmdGetxxxSignature().							*/
/*	Rev.(ZY06:BRZ-669)	add CmdxxxEncrypt().								*/
/*	Rev.(ZW01:BRZ-714)	add CmdSetTransNumber().							*/
/*	Rev.(ZW04:BRZ-802)	add CmdxxxModeBV().									*/
/*	Rev.(ZW04:BRZ-862)	add CmdSetKeepTDCM(),CmdStopMotor().				*/
/*	Rev.(ZW04:BRZ-893)	add CmdResponseBufFree().							*/
/*	Rev.(ZV02:BRZ-916)	add CmdGetKeepTDCM().								*/
/*	Rev.(ZV08:BRZ-1026)	add return value of get destination function.		*/
/*	Rev.(ZV10:BRZ-1031)	add command interval timer of re-start function.	*/
/*	Rev.(ZU03:BRZ-1029)	add function of motor free.							*/
/*	Rev.(AA04:BRZ-1188)	add function of response send.						*/
/*	Rev.(AA04:BRZ-1190)	add function of sensor change record.				*/
/*	Rev.(AA04:BRZ-1199)	add function of insertion notice.					*/
/*	Rev.(AA06:BRZ-1246)	add function of foreign object control.				*/
/*	Rev.(AA13:BRZ-1342)	add function of get additional A5 address.			*/
/*	Rev.(AA33:BRZ-1486)	add function of BV signature mode.					*/
/*						add function of counterfeit over check.				*/
/*	Rev.(AA38:BRZ-1509)	add function of Set END STATUS for Direct deposit 	*/
/*--------------------------------------------------------------------------*/
char	 			*CmdGetBuffer( void );
char	 			*CmdGetAddressA5Add( void );
void				CmdInitializeRecBuf( void );
void				CmdReleaseRecBuf( char *cPtr );
void				CmdResponseBufFree( UCHAR *adr );
CMD_INFORMATION		*CmdGetInfo( void );
void				CmdSetCmdCode( USHORT code );
void				CmdSetTransNumber( USHORT num );
USHORT				CmdGetTransNumber( void );
void				CmdSetModeBV( UCHAR num );
UCHAR				CmdGetModeBV( void );
void				CmdSetExtSignatureBV( BOOL sw );	/*	Rev.(AA33:BRZ-1486)	*/
BOOL				CmdGetExtSignatureBV( void );		/*	Rev.(AA33:BRZ-1486)	*/
void				CmdSetKeepTDCM( BOOL sw );
BOOL				CmdGetKeepTDCM( void );
EXT_BOOL			CmdStopMotor( INT_END_FACTOR ief, BOOL sw );
void				CmdFreeMotor( void );
UCHAR				CmdGetCategorySignature( void );
USHORT				CmdGetIndexSignature( void );
ULONG				CmdGetBvBlockNumber( void );
void				CmdInitializeBvBlockNumber( void );
void				CmdIncBvBlockNumber( void );
void				CmdSetEncryptType( UCHAR enc );
UCHAR				CmdGetEncryptType( void );
void				CmdInitialize( void );
void				CmdEnd( void );
BOOL				CmdGetDestination( PKT_BILL *VdPkt, PKT_BILL *IntPkt );
BOOL				CmdUpdateDestination( MECHA_PLACE place );
BOOL				CmdEntryDest( MECHA_PLACE from, MECHA_PLACE to, MECHA_PLACE to_normal );
void				CmdIntervalTmrReStart( void );
BOOL				CmdResponseRequest( TASK_MSG msg, UCHAR factor, UCHAR sns );
void				CmdSetSensorChange( BOOL sw );
BOOL				CmdGetSensorChange( void );
void				CmdSetProcessInsert( BOOL sw );
BOOL				CmdGetProcessInsert( void );
BOOL				CmdCheckForeignObject( void );
BOOL				CmdCheckCounterfeitOver( void );/*	Rev.(AA33:BRZ-1486)	*/
void				CmdSetRejectFullDirectDeposit( MECHA_PLACE mecha );	/* Rev.(AA38:BRZ-1509)	*/
	/*----------------------------------------------------------------------*/
	/*	Inspection before command start										*/
	/*	Rev.(ZZ06:BRZ-246)	movement inspection function.(task_cmd->cmd_api)*/
	/*	Rev.(ZZ06:BRZ-251)													*/
	/*	add range inspection function for every parameter class.			*/
	/*	Rev.(ZZ06:BRZ-286)													*/
	/*	add argument.(CmdCheckPathMedia())									*/
	/*	Rev.(ZZ07:BRZ-360)													*/
	/*	add CmdCheckSnsPath().(l_cmd->cmd_api)								*/
	/*	Rev.(ZY01:BRZ-409)													*/
	/*	add CmdCheckUpperMedia().(l_cmd->cmd_api)							*/
	/*	Rev.(ZY02:BRZ-456)													*/
	/*	add CmdCheckReject().												*/
	/*	Rev.(ZW01:BRZ-708)													*/
	/*	add CmdCheckDisappearMedia().										*/
	/*	Rev.(ZV08:BRZ-1020)													*/
	/*	add argument of Reject inspection.									*/
	/*	Rev.(AA10:BRZ-1297)													*/
	/*	add CmdCheckTransportRemain().										*/
	/*----------------------------------------------------------------------*/
BOOL			CmdCheckUnitSet( void );
BOOL			CmdCheckPathMedia( BOOL sw );
BOOL			CmdCheckTransportRemain( BOOL sw );
BOOL			CmdCheckSnsPath( BOOL sw );
BOOL			CmdCheckUnitMedia( void );
BOOL			CmdCheckReject( BOOL sw );

BOOL			CmdCheckUpperMedia( MECHA_PLACE mecha1, MECHA_PLACE mecha2,
							 		MECHA_PLACE mecha3, MECHA_PLACE mecha4, BOOL sw );
BOOL			CmdCheckDisappearMedia( MECHA_PLACE mecha );
/*--------------------------------------------------------------------------*/
/*	Rev.(ZY04:BRZ-560)	add CmdGetEntryFeedPlace().							*/
/*	Rev.(ZY05:BRZ-623)	add CmdClearAcceptDenomination().					*/
/*	Rev.(ZY06:BRZ-688)	add CmdCheckAcceptDenomination().					*/
/*	Rev.(ZW01:BRZ-718)	add CmdSetAcceptStartPtr().							*/
/*	Rev.(ZW01:BRZ-707)	add CmdxxxFactorAfterDraw().						*/
/*	Rev.(ZW03:BRZ-742)	add CmdCheckJobFactor().							*/
/*	Rev.(ZW03:BRZ-764)	add CmdCheckMoneyTrouble().							*/
/*	Rev.(ZW04:BRZ-800)	add CmdGetFeedPlace().								*/
/*	Rev.(ZW04:BRZ-877)	add CmdInitializePressDraw(),CmdGetPressStep().		*/
/*	Rev.(ZV02:BRZ-916)	add CmdxxxPlaceAfterDraw().							*/
/*	Rev.(ZV08:BRZ-1005)	add CmdCheckHalfNote().								*/
/*	Rev.(ZT10:BRZ-1149)	add CmdGetDischargeLength().						*/
/*	Rev.(ZT10:BRZ-1156)	add CmdxxxHandleDenomi().							*/
/*	Rev.(AA48:BRZ-1535)	add argument on CmdCheckMoneyTrouble().				*/
/*--------------------------------------------------------------------------*/
MECHA_PLACE		CmdGetEntryFeedPlace( void );
MECHA_PLACE		CmdGetFeedPlace( void );
void			CmdClearAcceptDenomination( void );
void			CmdCheckAcceptDenomination( void );
void			CmdSetHandleDenomi( void );
void			CmdUpdateHandleDenomi( void );
/*BOOL			CmdCheckMoneyTrouble( void );*/
BOOL			CmdCheckMoneyTrouble( BOOL sw );
void			CmdSetAcceptStartPtr( void );
void			CmdInitializePressDraw( void );
short			CmdGetPressStep( void );
void			CmdClearFactorAfterDraw( void );
void			CmdSetFactorAfterDraw( ULONG factor );
UCHAR			CmdCheckFactorAfterDraw( void );
BOOL			CmdCheckJobFactor( JOB_END_FACTOR fact );
void			CmdSetPlaceAfterDraw( MECHA_PLACE mecha );
MECHA_PLACE		CmdGetPlaceAfterDraw( void );
void			CmdClearPlaceAfterDraw( MECHA_PLACE mecha );
void			CmdInitializePlaceAfterDraw( void );
BOOL			CmdCheckHalfNote( void );
UCHAR			CmdGetDischargeLength( void );
void			CmdClearDischargeLength( BOOL sw );
/*--------------------------------------------------------------------------*/
/*	The function for debugging												*/
/*	Rev.(ZZ04:BRZ-142)	add Command API function(for debug).				*/
/*	Rev.(ZU03:BRZ-1029)														*/
/*	add function of feed table entry.										*/
/*	add function of Job / Int end factor notice.							*/
/*--------------------------------------------------------------------------*/
MECHA_PLACE		CmdGetDestinationNote( UCHAR kind );
void			CmdDispJobFactor( JOB_END_FACTOR fact );
void			CmdDispFactor( INT_END_FACTOR fact );
void			CmdDispNumberPresentBill( void );
void			CmdDispDest( void );
void			CmdSetFeedInfo( MECHA_PLACE mecha, short number );
char			*CmdGetTableDest( void );
char			*CmdGetEntryDest( void );
char			*CmdGetNumberFeed( void );
char			*CmdGetMoveRequest( void );
JOB_END_FACTOR	*CmdGetJobEndFactor( void );
INT_END_FACTOR	*CmdGetIntEndFactor( void );


/*--------------------------------------------------------------------------*/
/*	Rev.(AA44:BRZ-1527)														*/
/*--------------------------------------------------------------------------*/
void		CmdSetDetachedRequestPlace( MECHA_PLACE mecha );
MECHA_PLACE	CmdGetDetachedRequestPlace( void );
void		CmdUpdateDetachedDrawPlace( MECHA_PLACE mecha );
MECHA_PLACE	CmdGetDetachedDrawPlace( void );
void		CmdUpdateDetachedStackPlace( MECHA_PLACE mecha );
MECHA_PLACE	CmdGetDetachedStackPlace( void );
void		CmdClearDetachedPlace( void );

/*--------------------------------------------------------------------------*/
/*	Rev.(AA48:BRZ-1535)		Add												*/
/*--------------------------------------------------------------------------*/
void		CmdSetDisableFullStopPlase( MECHA_PLACE mecha );
BOOL		CmdCheckDisableFullStopPlase( MECHA_PLACE mech );
