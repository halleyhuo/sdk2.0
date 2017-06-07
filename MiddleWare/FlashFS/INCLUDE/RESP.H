/***

	*************************************************************************
	*																		*
	*		header file for response module									*
	*																		*
	*														RESP.H			*
	*************************************************************************
	ALL RIGHTS RESERVED, COPYRIGHT(C) FUJITSU FRONTECH LIMITED. 2002-2004

	SN			Date		Name		Revision.No.	Contents
	-------------------------------------------------------------------------
	001-ZZ04	2003/06/13	M.Banba						The First Version
	002-ZZ05	2003/07/01	M.Banba		<BRZ-192>		It corresponds to renewal of Denomination information.
	003-ZZ07	2003/10/01	M.Banba		<BRZ-405>		The updating method change of medium remains.
	004-ZY01	2003/10/09	M.Banba		<BRZ-417>		 delivery number-of-sheets inspection function is added.
	005-ZY04	2003/12/16	M.Banba		<BRZ-543>		Renewal function addition of fake bill number of sheets
				2003/12/18	M.Banba		<BRZ-543>		add DATA CODE(from LRESP.H)
							M.Kamimura	<BRZ-566>		add DATA CODE(DATA_Sx,DATA_T0,DATA_T1)
				2003/12/19	M.Banba		<BRZ-543>		add CATEGORY NUMBER
	006-ZY05	2004/01/08	M.Kamimura	<BRZ-623>		Change label of End status information.
														:STATUS_INFO_END_xxx
				2004/01/09	M.Kamimura	<BRZ-614>		Add function of signature count setup.
														:RespSetSignatureCount()
	007-ZY06	2004/01/20	M.Banba		<BRZ-668>		add response order
														:RESP_J0Å`JF,RESP_L0Å`LH
				2004/01/27	M.Kamimura	<BRZ-690>		Add data code.
														:DATA_O0
	008-ZW03	2004/02/23	M.Kamimura	<BRZ-759>		Add function of store check.
														:RespCheckStore()
	009-ZW04	2004/03/17	M.Kamimura	<BRZ-841>		Movement definition.( l_resp.h -> resp.h )
														:STATUS_INFO_READ_xxx
				2004/03/24	M.Kamimura	<BRZ-868>		Add function of update set status. (Only non-ready)
														:RespNoneReadySetStatus()
	010-ZW06	2004/04/05	M.Kamimura	<BRZ-895>		Add member of Set status information.
														:STATUS_INFO_SET_BEFORE_BV
														:STATUS_INFO_SET_UNDER_REJECT
	011-ZV01	2004/04/08	M.Kamimura	<BRZ-912>		Add member of Set status information.
														:STATUS_INFO_SET_TOP_TRANSPORT
	012-ZV03	2004/04/14	A.Maruyama	<BRZ-920>		Add member of Set status information.
														:STATUS_INFO_SET_INTERLOCK
										<BRZ-923>		Add processing of unusual changed sensor.(SHCC/SHOC)
														:STATUS_INFO_UNUSUAL_xxx
														:RespxxxUnusualSensor()
	013-ZV05	2004/04/30	A.Kojima	<BRZ-979>		Add special category number for transport control
														:RESP_NO_VALIDATED,RESP_NO_COUNT
	014-ZU08	2004/06/07	M.Kamimura	<BRZ-1092>		Add function of update invalid insertion factor.
														:STATUS_INFO_INVALID_xxx
														:RespxxxFactorInvalidInsertion()
				2004/06/09	A.Maruyama	<BRZ-1100>		Add function for update mechanical error location
														:RespAddMechaErrorLocation()
														:RespGetMechaErrorLocation()
														:RespClearMechaErrorLocation()
	015-AA05	2004/08/26	M.Kamimura	<BRZ-1222>		Add factor of invalid insertion.(Fail to move note to Sep)
														:STATUS_INFO_INVALID_FAIL_MOVE
	016-AA07	2004/09/23	A.Kojima	<BRZ-1261>		Add feed counter decrement
	017-AA10	2004/10/07	N.Banba		<BRZ-1293>		Add response information is changed the first stage.
														:RespDecFeedCount() add
	018-AA20	2005/04/26	M.Kamimura	<BRZ-1420>		Add function of BV kind updating.(For edit I3-"Kind of BV")
														:RespxxxKindBv()
	019-AA22	2005/08/23	M.Kamimura	<BRZ-1449>		Add function of update Damaged counter.(For GI information)
														:DATA_GI
														:RespIncDamagedCount()
	020-AA25	2005/12/26	A.Kojima	<BRZ-1461>		add special category number for transport control
														:RESP_NO_COUNT_RECOGNIZED add
	021-AA38	2006/12/19	M.Banba		<BRZ-1509>		for Direct deposit function enhancing
														-Change label (STATUS_INFO_END_NO_DIRECT_DEPOSIT)
	022-AA43	2007/02/27	A.Kojima	<BRZ-1520>		support for cheque
														:DATA_S4 add
														:MAX_DATA_CODE_NUMBER
COMMENT END
***/
/****************************************************************************/
/*																			*/
/*	define										 							*/
/*																			*/
/****************************************************************************/
/*--------------------------------------------------------------------------*/
/*	STATUS INFORMATION														*/
/*--------------------------------------------------------------------------*/
	/*----------------------------------------------------------------------*/
	/*	SET_STATUS															*/
	/*	Rev.(ZW06:BRZ-895)	Add before BV,under reject.						*/
	/*	Rev.(ZV01:BRZ-912)	Add top transport.								*/
	/*	Rev.(ZV02:BRZ-920)	Add interlock.									*/
	/*----------------------------------------------------------------------*/
enum
{
	STATUS_INFO_SET_UNIT				= (UCHAR)0x00,
	STATUS_INFO_SET_UPPER				= (UCHAR)0x01,
	STATUS_INFO_SET_LOWER				= (UCHAR)0x02,
	STATUS_INFO_SET_LOWER_TRANSPORT		= (UCHAR)0x03,
	STATUS_INFO_SET_CA1					= (UCHAR)0x04,
	STATUS_INFO_SET_CA2					= (UCHAR)0x05,
	STATUS_INFO_SET_CA3					= (UCHAR)0x06,
	STATUS_INFO_SET_CA4					= (UCHAR)0x07,
	STATUS_INFO_SET_REJECT				= (UCHAR)0x08,
	STATUS_INFO_SET_BEFORE_BV			= (UCHAR)0x09,
	STATUS_INFO_SET_UNDER_REJECT		= (UCHAR)0x0A,
	STATUS_INFO_SET_TOP_TRANSPORT		= (UCHAR)0x0B,
	STATUS_INFO_SET_RESERVE4			= (UCHAR)0x0C,
	STATUS_INFO_SET_RESERVE5			= (UCHAR)0x0D,
	STATUS_INFO_SET_RESERVE6			= (UCHAR)0x0E,
	STATUS_INFO_SET_INTERLOCK			= (UCHAR)0x0F,
	STATUS_INFO_SET_END					= (UCHAR)0x10
};
	/*----------------------------------------------------------------------*/
	/*	END_STATUS															*/
	/*	Rev.(ZY05:BRZ-623)	Change label name.	(No.13,22,27,28,29)			*/
	/*	Rev.(AA38:BRZ-1509)	Change label name.	(No.30)						*/
	/*----------------------------------------------------------------------*/
enum{
	STATUS_INFO_END_ERROR_COMMAND			= 0x00,
	STATUS_INFO_END_ERROR_PARAMETER			= 0x01,
	STATUS_INFO_END_ERROR_MEMORY			= 0x02,
	STATUS_INFO_END_POWER_DOWN				= 0x03,
	STATUS_INFO_END_MEDIA_DETECT_EXCEPT		= 0x04,
	STATUS_INFO_END_DIFFERENT_COUNTING		= 0x05,
	STATUS_INFO_END_ERROR_JAM				= 0x06,
	STATUS_INFO_END_ERROR_BV				= 0x07,
	STATUS_INFO_END_OVER_RECOGNIZED			= 0x08,
	STATUS_INFO_END_OVER_COUNTERFEIT		= 0x09,
	STATUS_INFO_END_NO_DISPENSING			= 0x0A,
	STATUS_INFO_END_ERROR_MECHANICAL		= 0x0B,
	STATUS_INFO_END_UNUSUAL_SENSOR_DETECT	= 0x0C,
	STATUS_INFO_END_OVER_DISPENSABLE		= 0x0D,
	STATUS_INFO_END_INVALID_INSERTION		= 0x0E,
	STATUS_INFO_END_OVER_RETURNED_ACCEPT	= 0x0F,
	STATUS_INFO_END_REMAINING_UNACCEPTABLE	= 0x10,
	STATUS_INFO_END_FULL_STORAGES			= 0x11,
	STATUS_INFO_END_MISFEEDING				= 0x12,
	STATUS_INFO_END_BEFORE_REQUESTED		= 0x13,
	STATUS_INFO_END_NO_TARGET_CASSETTE		= 0x14,
	STATUS_INFO_END_OVER_REJECT				= 0x15,
	STATUS_INFO_END_REMAINING_MEDIA			= 0x16,
	STATUS_INFO_END_TRANSPORT_NOT_CHECK		= 0x17,
	STATUS_INFO_END_OPEN_UNIT				= 0x18,
	STATUS_INFO_END_OPEN_SHUTTER			= 0x19,
	STATUS_INFO_END_DOUBLE_NOTE_DETECT		= 0x1A,
	STATUS_INFO_END_CHANGE_DENOMINATION		= 0x1B,
	STATUS_INFO_END_CHANGE_CATEGORY			= 0x1C,
	STATUS_INFO_END_NO_DIRECT_DEPOSIT		= 0x1D,
	STATUS_INFO_END_RESERVE5				= 0x1E,
	STATUS_INFO_END_RESERVE6				= 0x1F,
	STATUS_INFO_END_END						= 0x20
	};
	/*----------------------------------------------------------------------*/
	/*	Unusual changed sensor												*/
	/*	Rev.(ZV02:BRZ-923)	Add definition of unusual changed sensor.		*/
	/*----------------------------------------------------------------------*/
enum{
	STATUS_INFO_UNUSUAL_CLEAR				= 0x00,
	STATUS_INFO_UNUSUAL_BLOCK				= 0x80,

	STATUS_INFO_UNUSUAL_SHCC				= 0x01,
	STATUS_INFO_UNUSUAL_SHOC				= 0x02,
	STATUS_INFO_UNUSUAL_PS1S				= 0x03,
	STATUS_INFO_UNUSUAL_PS2S				= 0x04,
	STATUS_INFO_UNUSUAL_PS3S				= 0x05,
	STATUS_INFO_UNUSUAL_PS4S				= 0x06,
	STATUS_INFO_UNUSUAL_PTCS				= 0x07,
	STATUS_INFO_UNUSUAL_PASS				= 0x08,
	STATUS_INFO_UNUSUAL_PDSS				= 0x09,
	STATUS_INFO_UNUSUAL_EERS				= 0x0A,
	STATUS_INFO_UNUSUAL_EELS				= 0x0B,
	STATUS_INFO_UNUSUAL_EECS				= 0x0C,
	STATUS_INFO_UNUSUAL_PTPC				= 0x0D,
	STATUS_INFO_UNUSUAL_PBPC				= 0x0E
	};
	/*----------------------------------------------------------------------*/
	/*	Invalid insertion factor											*/
	/*	Rev.(ZU08:BRZ-1092)	Add definition of invalid insertion factor.		*/
	/*	Rev.(AA05:BRZ-1224)	Add definition of fail to move.					*/
	/*----------------------------------------------------------------------*/
enum{
	STATUS_INFO_INVALID_OTHER				= 0x00,
	STATUS_INFO_INVALID_LONG_1ST			= 0x01,
	STATUS_INFO_INVALID_LONG_2ND			= 0x02,
	STATUS_INFO_INVALID_SHORT				= 0x03,
	STATUS_INFO_INVALID_SKEW				= 0x04,
	STATUS_INFO_INVALID_THICK				= 0x05,
	STATUS_INFO_INVALID_DETECT				= 0x06,
	STATUS_INFO_INVALID_TAKE_OUT			= 0x07,
	STATUS_INFO_INVALID_FAIL_MOVE			= 0x08
	};
	/*----------------------------------------------------------------------*/
	/*	READ REQUEST														*/
	/*	Rev.(ZY04:BRZ-543)	Change definition of name.						*/
	/*	Rev.(ZW04:BRZ-841)	Movement definition.	( l_resp.h -> resp.h )	*/
	/*----------------------------------------------------------------------*/
enum{
	STATUS_INFO_READ_LOG			= 0x00,
	STATUS_INFO_READ_RESERVE1		= 0x01,
	STATUS_INFO_READ_RESERVE2		= 0x02,
	STATUS_INFO_READ_RESERVE3		= 0x03,
	STATUS_INFO_READ_RESERVE4		= 0x04,
	STATUS_INFO_READ_RESERVE5		= 0x05,
	STATUS_INFO_READ_RESERVE6		= 0x06,
	STATUS_INFO_READ_RESERVE7		= 0x07,
	STATUS_INFO_READ_END			= 0x08
	};
enum
{
	RESP_REASON_DOUBLE	= 0,
	RESP_REASON_LONG	= 1,
	RESP_REASON_SKEW	= 2,
	RESP_REASON_CLOSE	= 4,
	RESP_REASON_OTHER	= 7,
	RESP_REASON_MAX		= 8
};
/*--------------------------------------------------------------------------*/
/*	Rev.(ZY04:BRZ-543)	Category count correspondence						*/
/*	Rev.(ZV05:BRZ-979)														*/
/*	 add RESP_NO_VALIDATED,RESP_NO_COUNT									*/
/*	Rev.(AA25:BRZ-1461)														*/
/*	 add RESP_NO_COUNT_RECOGNIZED											*/
/*--------------------------------------------------------------------------*/
enum{
	RESP_GENUINE				= 0,
	RESP_DAMAGED				= 1,
	RESP_NOT_RECOGNIZED			= 2,
	RESP_SUSPECT				= 3,
	RESP_COUNTERFEIT			= 4,
	RESP_CATEGORY_END			= 8,
	RESP_NO_VALIDATED			= 9,
	RESP_NO_COUNT				= 10,
	RESP_NO_COUNT_RECOGNIZED	= 11
};
/*--------------------------------------------------------------------------*/
/*	DATA CODE																*/
/*	Rev.(ZY04:BRZ-543)	add DATA_GJ,DATA_GK									*/
/*	Rev.(ZY04:BRZ-566)	add DATA_Sx,DATA_T0,DATA_T1							*/
/*	Rev.(ZY06:BRZ-668)	add RESP_J0Å`JF,L0Å`LH								*/
/*	Rev.(ZY06:BRZ-671)	add DATA_JZ											*/
/*	Rev.(ZY06:BRZ-690)	add DATA_O0											*/
/*	Rev.(AA22:BRZ-1449)	add DATA_GI											*/
/*	Rev.(AA43:BRZ-1520)	add DATA_S4											*/
/*--------------------------------------------------------------------------*/
enum{
	DATA_NONE	=0xFFFF,		/*		*/
	DATA_F0		= 0x4630,		/*	1	*/
	DATA_FX		= 0x4658,		/*	2	*/
	DATA_G0		= 0x4730,		/*	3	*/
	DATA_G1		= 0x4731,		/*	4	*/
	DATA_G3		= 0x4733,		/*	5	*/
	DATA_G4		= 0x4734,		/*	6	*/
	DATA_G5		= 0x4735,		/*	7	*/
	DATA_G6		= 0x4736,		/*	8	*/
	DATA_G9		= 0x4739,		/*	9	*/
	DATA_GA		= 0x4741,		/*	10	*/
	DATA_GB		= 0x4742,		/*	11	*/
	DATA_GI		= 0x4749,		/*	12	*/
	DATA_GJ		= 0x474A,		/*	13	*/
	DATA_GK		= 0x474B,		/*	14	*/
	DATA_I3		= 0x4933,		/*	15	*/
	DATA_IX		= 0x4958,		/*	16	*/
	DATA_J0		= 0x4A30,		/*	17	*/
	DATA_J1		= 0x4A31,		/*	18	*/
	DATA_J2		= 0x4A32,		/*	19	*/
	DATA_J3		= 0x4A33,		/*	20	*/
	DATA_J4		= 0x4A34,		/*	21	*/
	DATA_J5		= 0x4A35,		/*	22	*/
	DATA_J6		= 0x4A36,		/*	23	*/
	DATA_J7		= 0x4A37,		/*	24	*/
	DATA_J8		= 0x4A38,		/*	25	*/
	DATA_J9		= 0x4A39,		/*	26	*/
	DATA_JA		= 0x4A41,		/*	27	*/
	DATA_JB		= 0x4A42,		/*	28	*/
	DATA_JC		= 0x4A43,		/*	29	*/
	DATA_JD		= 0x4A44,		/*	30	*/
	DATA_JE		= 0x4A45,		/*	31	*/
	DATA_JF		= 0x4A46,		/*	32	*/
	DATA_JG		= 0x4A47,		/*	33	*/
	DATA_JH		= 0x4A48,		/*	34	*/
	DATA_JI		= 0x4A49,		/*	35	*/
	DATA_JJ		= 0x4A4A,		/*	36	*/
	DATA_JK		= 0x4A4B,		/*	37	*/
	DATA_JL		= 0x4A4C,		/*	38	*/
	DATA_JM		= 0x4A4D,		/*	39	*/
	DATA_JN		= 0x4A4E,		/*	40	*/
	DATA_JO		= 0x4A4F,		/*	41	*/
	DATA_JP		= 0x4A50,		/*	42	*/
	DATA_JQ		= 0x4A51,		/*	43	*/
	DATA_JR		= 0x4A52,		/*	44	*/
	DATA_JS		= 0x4A53,		/*	45	*/
	DATA_JT		= 0x4A54,		/*	46	*/
	DATA_JU		= 0x4A55,		/*	47	*/
	DATA_JV		= 0x4A56,		/*	48	*/
	DATA_JW		= 0x4A57,		/*	49	*/
	DATA_JX		= 0x4A58,		/*	50	*/
	DATA_JY		= 0x4A59,		/*	51	*/
	DATA_JZ		= 0x4A5A,		/*	52	*/
	DATA_L0		= 0x4C30,		/*	53	*/
	DATA_L1		= 0x4C31,		/*	54	*/
	DATA_L2		= 0x4C32,		/*	55	*/
	DATA_L3		= 0x4C33,		/*	56	*/
	DATA_L4		= 0x4C34,		/*	57	*/
	DATA_L5		= 0x4C35,		/*	58	*/
	DATA_L6		= 0x4C36,		/*	59	*/
	DATA_L7		= 0x4C37,		/*	60	*/
	DATA_L8		= 0x4C38,		/*	61	*/
	DATA_L9		= 0x4C39,		/*	62	*/
	DATA_LA		= 0x4C41,		/*	63	*/
	DATA_LB		= 0x4C42,		/*	64	*/
	DATA_LC		= 0x4C43,		/*	65	*/
	DATA_LD		= 0x4C44,		/*	66	*/
	DATA_LE		= 0x4C45,		/*	67	*/
	DATA_LF		= 0x4C46,		/*	68	*/
	DATA_LG		= 0x4C47,		/*	69	*/
	DATA_LH		= 0x4C48,		/*	70	*/
	DATA_M1		= 0x4D31,		/*	71	*/
	DATA_M2		= 0x4D32,		/*	72	*/
	DATA_M3		= 0x4D33,		/*	73	*/
	DATA_M4		= 0x4D34,		/*	74	*/
	DATA_M5		= 0x4D35,		/*	75	*/
	DATA_M6		= 0x4D36,		/*	76	*/
	DATA_M7		= 0x4D37,		/*	77	*/
	DATA_M8		= 0x4D38,		/*	78	*/
	DATA_M9		= 0x4D39,		/*	79	*/
	DATA_O0		= 0x4F30,		/*	80	*/
	DATA_O1		= 0x4F31,		/*	81	*/
	DATA_O2		= 0x4F32,		/*	82	*/
	DATA_O3		= 0x4F33,		/*	83	*/
	DATA_O4		= 0x4F34,		/*	84	*/
	DATA_O5		= 0x4F35,		/*	85	*/
	DATA_O6		= 0x4F36,		/*	86	*/
	DATA_O7		= 0x4F37,		/*	87	*/
	DATA_O8		= 0x4F38,		/*	88	*/
	DATA_O9		= 0x4F39,		/*	89	*/
	DATA_OF		= 0x4F46,		/*	90	*/
	DATA_R1		= 0x5231,		/*	91	*/
	DATA_R2		= 0x5232,		/*	92	*/
	DATA_R3		= 0x5233,		/*	93	*/
	DATA_R4		= 0x5234,		/*	94	*/
	DATA_R5		= 0x5235,		/*	95	*/
	DATA_R6		= 0x5236,		/*	96	*/
	DATA_R7		= 0x5237,		/*	97	*/
	DATA_R8		= 0x5238,		/*	98	*/
	DATA_R9		= 0x5239,		/*	99	*/
	DATA_RA		= 0x5241,		/*	100	*/
	DATA_RB		= 0x5242,		/*	101	*/
	DATA_RC		= 0x5243,		/*	102	*/
	DATA_S0		= 0x5330,		/*	103	*/
	DATA_S1		= 0x5331,		/*	104	*/
	DATA_S2		= 0x5332,		/*	105	*/
	DATA_S3		= 0x5333,		/*	106	*/
	DATA_S4		= 0x5334,		/*	107	*/
	DATA_T0		= 0x5430,		/*	108	*/
	DATA_T1		= 0x5431		/*	109	*/
	};
#define		MAX_DATA_CODE_NUMBER	109
/****************************************************************************/
/*																			*/
/*	function prototypes							 							*/
/*																			*/
/****************************************************************************/
/*--------------------------------------------------------------------------*/
/*	<BRZ-192>	It corresponds to renewal of Denomination information.		*/
/*	<BRZ-543>	add func(Counterfeit number & Suspect number renewal) 		*/
/*	<BRZ-614>	add func(Set signature count) 								*/
/*	Rev.(ZW03:BRZ-759)	Add function of store check.						*/
/*	Rev.(ZW04:BRZ-868)	Add function of update set status. (Only non-ready)	*/
/*	Rev.(ZV02:BRZ-923)	Add function of update unusual changed sensor.		*/
/*	Rev.(ZU08:BRZ-1092)	Add function of update invalid insertion factor.	*/
/*	Rev.(ZU08:BRZ-1100)	Add function of update mechanical error location.	*/
/*	Rev.(AA07:BRZ-1261)	Add function of decrement feed counter.				*/
/*	Rev.(AA10:BRZ-1293)	Add response information is changed the first stage.*/
/*	Rev.(AA22:BRZ-1449)	Add function of update Damaged counter.				*/
/*--------------------------------------------------------------------------*/
void	RespIncReason( USHORT number );
void	RespIncFeedCount( PLACE_NO place );
void	RespDecFeedCount( PLACE_NO place );
BOOL	RespCheckFeed( void );
BOOL	RespCheckStore( PLACE_NO place );
void	RespIncStoreCount( PLACE_NO place, USHORT number );
void	RespSetEndStatus( UCHAR number );
void	RespClearEndStatus( UCHAR number );			/* Rev.(ZZ07:BRZ-405)	*/
BOOL	RespGetEndStatus( UCHAR number );
void	RespResetSetStatus( void );
void	RespNoneReadySetStatus( EXT_MECHA_PLACE mecha );
BOOL	RespGetSetStatus( UCHAR bSetNo );
void	RespIncCounterfeitCount( USHORT number );
void	RespIncSuspectCount( USHORT number );
void	RespIncDamagedCount( USHORT number );
void	RespIncCategoryCount( USHORT number );
void	RespIncSignatureCount( USHORT number );
void	RespSetSignatureCount( USHORT number, USHORT data );
void	RespSetUnusualSensor( UCHAR status );
UCHAR	RespGetUnusualSensor( void );
void	RespClearUnusualSensor( void );
void	RespAddMechaErrorLocation( MECHA_PLACE wLocation );
MECHA_PLACE		RespGetMechaErrorLocation( void );
void	RespClearMechaErrorLocation( void );
void	RespSetFactorInvalidInsertion( UCHAR factor );
UCHAR	RespGetFactorInvalidInsertion( void );
void	RespClearFactorInvalidInsertion( void );
void	RespInitializeInformation( void );
	/*----------------------------------------------------------------------*/
	/*	Rev.(AA20:BRZ-1420)													*/
	/*	Add function of BV kind updating.	(For edit I3-"Kind of BV")		*/
	/*----------------------------------------------------------------------*/
void	RespClearKindBv( void );
void	RespSetKindBv( UCHAR *pbSrc );
