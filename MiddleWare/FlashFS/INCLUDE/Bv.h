/***

	*************************************************************************
	*																		*
	*		header file for bv module										*
	*																		*
	*														BV.H			*
	*************************************************************************
	ALL RIGHTS RESERVED, COPYRIGHT(C) FUJITSU FRONTECH LIMITED. 2002-2003

	SN			Date		Name		Revision.No.	Contents
	-------------------------------------------------------------------------
	001-ZZ01	2002/11/07	M.Kibe		<BRZ-001>		The First Version
	002-ZZ02	2003/04/16	M.Kamimura	<BRZ-015>		Coding for setting dummy VD
	003-ZZ03	2003/04/18	M.Kamimura	<BRZ-015>		Add BvSetVdCodeDummy()
	004-ZZ04	2003/06/23	M.Kibe		<BRZ-175>		Add BvSetDebugMode()
														Add BvClearDebugMode()
	005-ZZ05	2003/07/07	Y.Saito		<BRZ-191>		
	006-ZZ06	2003/07/18	M.Banba		<BRZ-250>		add function prottype
														:BvReset()
														:BvCancel()
				2003/07/23	Y.Saito		<BRZ-267>		add BV reset mode
				2003/07/23	Y.Saito		<BRZ-268>		change definition of BV information area
	007-ZY01	2003/10/27	M.Banba		<BRZ-434>		BV available validate information added
	008-ZY02	2003/11/11	M.Banba		<BRZ-462>		add function(Display last validation data)
	009-ZY04	2003/12/20	A.Maruyama	<BRZ-582>		add prototypes of BV-firm loading
														:BvDownload()
														:BvDownloadEnd()
				2003/12/24	M.Kamimura	<BRZ-567>		Add definition of signature data.
														:BV_SIZE_SIGNATURE_AREA
														:BV_SIGNATURE_INFO
				2003/12/25	M.Bnaba		<BRZ-592>		Add Function prottype
														:BvRead()
	010-ZY05	2004/01/07	M.Kamimura	<BRZ-616>		Add structure of bv read result.
														:BV_READ_RESULT
														:BvReadRequest()
														:BvReadWait()
							Y.Saito						:BvCheckContinuity()
														:BvInitializeReception()
														:BvEndReception()
														:BvGetReceptionLength()
				2004/01/08	Y.Saito		<BRZ-624>		Add area definition.
														:BvAllImageData[][]
														:BV_SIZE_ALL_IMAGE_AREA
														:BV_BLOCK_DATA
														:BV_FEATURE_NUMBER_INFO
														:BV_SERIAL_NUMBER_INFO
														Review and improve area definition.
														:BV_RECOGNITION_INFO
														:BV_VALIDATION_INFO
				2004/01/14	Y.Saito		<BRZ-653>		Add area definition.
														:stBvChargeVdInfo
				2004/01/16	Y.Saito		<BRZ-661>		Change area definition.
	011-ZY06	2004/01/27	M.Banba		<BRZ-693>		add function for SB command
														:BvGetInfo()
	012-ZW01	2004/02/02	Y.Saito		<BRZ-701>		add definition
														:BV_SIZE_VD
														:BV_GET_LAN_BUF
														:BV_GET_VD
										<BRZ-703>		Add definition of near alarm.
														:BV_NEAR_ALARM
										<BRZ-705>		Add area definition.
														:stBvShortSideLength
	013-ZW03	2004/02/25	Y.Saito		<BRZ-768>		add definition
														:BV_LAST_BLOCK_SIZE_RECOGNITION
														:BV_LAST_BLOCK_SIZE_ALL_IMAGE
				2004/02/26	A.Maruyama	<BRZ-768>		change value
														:BV_LAST_BLOCK_SIZE_RECOGNITION
														:BV_LAST_BLOCK_NUMBER_RECOGNITION
														:BV_LAST_BLOCK_SIZE_ALL_IMAGE
														:BV_LAST_BLOCK_NUMBER_ALL_IMAGE
				2004/02/27	M.Kamimura	<BRZ-773>		Add definition of judgment BV information.
														:BV_ALARM_ALM_ERROR
														:BV_ALARM_MDR_xxx
	014-ZW04	2004/03/05	Y.Saito		<BRZ-800>		Add Function prottype.
														:BvDuringValidate()
														Add definition of BV status.
				2004/03/25	M.Kamimura	<BRZ-873>		Change type of SON response.
														:BV_NEAR_ALARM
	015-ZV05	2004/04/28	Y.Saito		<BRZ-986>		Add Function prottype.
														:BvClearFeatureImage()
				2004/04/29	M.Kamimura	<BRZ-973>		Add member of Unit information.
														:BV_UNIT_INFO
														Add member of BV sub program.
														:BV_REVISION_INFO
	016-ZU03	2004/05/24	Y.Saito		<BRZ-1042>		Add Function prottype.
														:BvChangeConnectionMode()
	017-AA08	2004/09/27	Y.Saito		<BRZ-1269>		Add member of Near Alarm information.
														:BV_NEAR_ALARM
	018-AA21	2005/06/23	M.Kamimura	<BRZ-1436>		Add work area of short side length.
														:stBvShortLengthWork[]
														:BvSetAvailable()
	019-AA25	2005/12/05	M.Kamimura	<BRZ-1461>		Polymer note measures
														- Add function that notifies note type.
														:BvGetNoteType()
	020-AA33	2006/07/03	M.Kamimura	<BRZ-1486>		Signature near full measures
														- Add function that notifies signature near full status.
														:BvCheckNearFullSignature()
	021-AA43	2007/02/27	A.Kojima	<BRZ-1520>		support for cheque
														:BV_SIZE_CHEQUE_IMAGE_AREA add
														:BV_CHEQUE_IMAGE_INFO add
														:BV_BLOCK_DATA
														:BvBeginReadChequeImage(),BvWaitReadChequeImage() add
	022-AA48	2007/06/07	A.Kojima	<BRZ-1530>		improve the data transfer speed
														-change for D-Level frame size change
														:BV_READ_SIZE_CHEQUE_IMAGE_0,
														 BV_READ_SIZE_CHEQUE_IMAGE_1 add
														:BV_SIZE_CHEQUE_IMAGE_AREA
COMMENT END
***/

/****************************************************************************/
/*																			*/
/*	defines																	*/
/*																			*/
/****************************************************************************/
	/*----------------------------------------------------------------------*/
	/*	(ZW01:BRZ-701)	add BV_SIZE_VD										*/
	/*----------------------------------------------------------------------*/
#define		BV_SUM_CHECK_LENGTH			2
#define 	BV_SIZE_DATA_LENGTH			4
#define 	BV_SIZE_MAKER_NAME			2
#define 	BV_SIZE_ENTRY_DATE			6
#define 	BV_SIZE_REVISION_NUMBER		12
#define 	BV_SIZE_VD					4
	/*----------------------------------------------------------------------*/
	/*	Alarm information area												*/
	/*----------------------------------------------------------------------*/
	/*----------------------------------------------------------------------*/
	/*	Revision Number information area									*/
	/*----------------------------------------------------------------------*/
	/*----------------------------------------------------------------------*/
	/*	Unit information area												*/
	/*----------------------------------------------------------------------*/
	/*----------------------------------------------------------------------*/
	/*	Validation information area											*/
	/*----------------------------------------------------------------------*/
#define		BV_MAX_SIZE_VALIDATE		80032
#define		BV_SIZE_STX					12
#define		BV_SIZE_ETX					12
	/*----------------------------------------------------------------------*/
	/*	Recognition information area										*/
	/*	Rev.(ZY05:BRZ-661) Add definition of block number.					*/
	/*	Rev.(ZW03:BRZ-768) Add definition of last block data size.			*/
	/*----------------------------------------------------------------------*/
#define 	BV_MAX_SIZE_RECOGNITION				180000
#define 	BV_LAST_BLOCK_SIZE_RECOGNITION		65156+4
#define 	BV_SIZE_BLOCK_NUMBER				4
#define 	BV_LAST_BLOCK_NUMBER_RECOGNITION	2
	/*----------------------------------------------------------------------*/
	/*	Static Characteristic information area								*/
	/*----------------------------------------------------------------------*/
#define 	BV_SIZE_MAGNETIC_HEAD		8
#define 	BV_SIZE_MAGNETIC_LINE		32
#define 	BV_SIZE_THICKNESS_DATA		8
#define 	BV_SIZE_SENSOR_DATA			16
	/*----------------------------------------------------------------------*/
	/*	Correction of picture information area								*/
	/*----------------------------------------------------------------------*/
#define 	BV_SIZE_PICTURE_DATA		2072
	/*----------------------------------------------------------------------*/
	/*	Statistics information area											*/
	/*----------------------------------------------------------------------*/
#define 	BV_SIZE_RECOGNITION_LENGTH	1184
#define 	BV_SIZE_NUMBER_OF_SHEETS	4
#define 	BV_SIZE_ERROR_COUNT			512
#define 	BV_SIZE_ALARM_CODE_COUNT	206
	/*----------------------------------------------------------------------*/
	/*	Message information area											*/
	/*----------------------------------------------------------------------*/
#define 	BV_SIZE_FREEZE_AREA			1024
	/*----------------------------------------------------------------------*/
	/*	Available information area											*/
	/*----------------------------------------------------------------------*/
#define 	BV_SIZE_AVAILABLE_AREA		512
	/*----------------------------------------------------------------------*/
	/*	Signature data area													*/
	/*	Rev.(ZY04:BRZ-567)	Add definition of signature data size.			*/
	/*----------------------------------------------------------------------*/
#define 	BV_SIZE_SIGNATURE_AREA		32768
#define 	BV_SIZE_SIGNATURE_RESERVE	12
	/*----------------------------------------------------------------------*/
	/*	Serial number data area												*/
	/*	Rev.(ZY04:BRZ-567)	Add definition of signature data size.			*/
	/*----------------------------------------------------------------------*/
#define		BV_SIZE_SERIAL_CHARACTER	15
#define		BV_SIZE_SERIAL_INFO			260
	/*----------------------------------------------------------------------*/
	/*	Rev.(ZY05:BRZ-624)	Add definition of all image area size.			*/
	/*	Rev.(ZW03:BRZ-768) Add definition of last block data size.			*/
	/*----------------------------------------------------------------------*/
#define 	BV_SIZE_ALL_IMAGE_AREA				180000
#define 	BV_LAST_BLOCK_SIZE_ALL_IMAGE		130336+4
#define 	BV_LAST_BLOCK_NUMBER_ALL_IMAGE		9
	/*----------------------------------------------------------------------*/
	/*	Rev.(AA43:BRZ-1520)		add											*/
	/*	cheque image data area												*/
	/*	Rev.(AA48:BRZ-1530)													*/
	/*	 add read size define												*/
	/*	 change value from 2888 to 8060										*/
	/*----------------------------------------------------------------------*/
#define		BV_READ_SIZE_CHEQUE_IMAGE_0		2888	/* for D-Level frame size 1.5K	*/
#define		BV_READ_SIZE_CHEQUE_IMAGE_1		8060	/* for D-Level frame size 4K	*/
#define		BV_SIZE_CHEQUE_IMAGE_AREA		8060
	/*----------------------------------------------------------------------*/
	/*	Rev.(ZY05:BRZ-658)	Add definition.									*/
	/*----------------------------------------------------------------------*/
#define 	BV_SIZE_SENSOR_LEVEL		1
	/*----------------------------------------------------------------------*/
	/*	Rev.(ZW01:BRZ-701)	Add definition.									*/
	/*----------------------------------------------------------------------*/
#define 	BV_SIZE_GET_LAN				180004
	/*----------------------------------------------------------------------*/
	/*	Judgment of BV information.											*/
	/*	Rev.(ZW03:BRZ-773)	Add definition.									*/
	/*----------------------------------------------------------------------*/
#define 	BV_ALARM_ALM_ERROR			0x80
#define 	BV_ALARM_MDR_OPEN			0x80
#define 	BV_ALARM_MDR_REMAIN			0x40

/*--------------------------------------------------------------------------*/
/*	BV reset mode															*/
/*--------------------------------------------------------------------------*/
enum
{
	BV_RESET_MODE_NORMAL	= 0x00,
	BV_RESET_MODE_ERROR		= 0xFF
};

/*--------------------------------------------------------------------------*/
/*	Definition of area														*/
/*	Rev.(ZZO6:BRZ-268) change definition of BV information area				*/
/*--------------------------------------------------------------------------*/
	/*----------------------------------------------------------------------*/
	/*	Alarm information area												*/
	/*----------------------------------------------------------------------*/
typedef struct
{
	UCHAR	length[BV_SIZE_DATA_LENGTH];/* data length						*/
	UCHAR	alm;						/* kind of alarm					*/
	UCHAR	mrd;						/* mode of operation				*/
	UCHAR	amc;						/* alarm code						*/
	UCHAR	mdr;						/* medium register					*/
	UCHAR	rrr;						/* restoration demand register		*/
	UCHAR	gbvm[4];					/* GBVM								*/
	UCHAR	ginf;						/* demand of information acquisition */
	UCHAR	reserve[118];				/* reserve							*/
}BV_ALARM_INFO;
	/*----------------------------------------------------------------------*/
	/*	Revision Number information area									*/
	/*	Rev.(ZV05:BRZ-973)	Add member of Sub program information.			*/
	/*----------------------------------------------------------------------*/
typedef struct
{
	UCHAR	length[BV_SIZE_DATA_LENGTH];			/* data length				*/
	UCHAR	entry_date[BV_SIZE_ENTRY_DATE];			/* entry date				*/
	UCHAR	revision[BV_SIZE_REVISION_NUMBER];		/* revision number			*/
	UCHAR	maker[BV_SIZE_MAKER_NAME];				/* maker name				*/
	UCHAR	sub_entry_date[BV_SIZE_ENTRY_DATE];		/* entry date		(Sub)	*/
	UCHAR	sub_revision[BV_SIZE_REVISION_NUMBER];	/* revision number	(Sub)	*/
	UCHAR	sub_maker[BV_SIZE_MAKER_NAME];			/* maker name		(Sub)	*/
	UCHAR	reserve[88];							/* reserve					*/
}BV_REVISION_INFO;
	/*----------------------------------------------------------------------*/
	/*	Unit information area												*/
	/*	Rev.(ZV05:BRZ-973)	Add member.	(Optional reflection sensor)		*/
	/*----------------------------------------------------------------------*/
typedef struct
{
	UCHAR	length[BV_SIZE_DATA_LENGTH];		/* data length		*/
	UCHAR	maker[BV_SIZE_MAKER_NAME];			/* maker name		*/
	UCHAR	option;								/* option sensor	*/
	UCHAR	reserve[125];						/* reserve			*/
}BV_UNIT_INFO;
	/*----------------------------------------------------------------------*/
	/*	Validation information area											*/
	/*	Rev.(ZY05:BRZ-624)	review and improve definition					*/
	/*----------------------------------------------------------------------*/
typedef struct
{
	UCHAR	length[BV_SIZE_DATA_LENGTH];		/* data length		*/
	UCHAR	vd[BV_MAX_SIZE_VALIDATE];			/* vaidation data	*/
}BV_VALIDATION_INFO;
	/*----------------------------------------------------------------------*/
	/*	Recognition information area										*/
	/*	Rev.(ZY05:BRZ-624)	review and improve definition					*/
	/*	Rev.(ZY05:BRZ-661) Add definition of block number.					*/
	/*----------------------------------------------------------------------*/
typedef struct
{
	UCHAR	block[BV_SIZE_BLOCK_NUMBER];					/* block number				*/
	UCHAR	recognition[BV_MAX_SIZE_RECOGNITION];			/* 1 block data				*/
}BV_RECOGNITION_INFO;
	/*----------------------------------------------------------------------*/
	/*	Static Characteristic information area								*/
	/*----------------------------------------------------------------------*/
typedef struct
{
	UCHAR	length[BV_SIZE_DATA_LENGTH];					/* data length				*/
	UCHAR	attribute;										/* attribute				*/
	UCHAR	treatment_num;									/* treatment number			*/
	UCHAR	trans_num[2];									/* transaction number		*/
	UCHAR	none_reserve[2];								/* not use					*/
	UCHAR	entry_date[BV_SIZE_ENTRY_DATE];					/* entry date				*/
	UCHAR	revision[BV_SIZE_REVISION_NUMBER];				/* revision number			*/
	UCHAR	maker[BV_SIZE_MAKER_NAME];						/* maker name				*/
	UCHAR	image_degital[1584];							/* image sensor				*/
	UCHAR	image_analog[1584];								/* image sensor				*/
	UCHAR	shading[4752];									/* shading					*/
	UCHAR	optical_penetration[BV_SIZE_SENSOR_DATA];		/* optical penetration		*/
	UCHAR	magnetic_head_offset[BV_SIZE_MAGNETIC_HEAD];	/* magnetic head			*/
	UCHAR	magnetic_head_data[BV_SIZE_MAGNETIC_HEAD];		/* magnetic head 			*/
	UCHAR	magnetic_line_offset[BV_SIZE_MAGNETIC_LINE];	/* magnetic line 			*/
	UCHAR	magnetic_line_data[BV_SIZE_MAGNETIC_LINE];		/* magnetic line 			*/
	UCHAR	uv_sensor_offset[BV_SIZE_SENSOR_DATA];			/* UV sensor 				*/
	UCHAR	uv_sensor_data[BV_SIZE_SENSOR_DATA];			/* UV sensor 				*/
	UCHAR	thickness_left_offset[BV_SIZE_THICKNESS_DATA];	/* thickness of left side	*/
	UCHAR	thickness_right_offset[BV_SIZE_THICKNESS_DATA];	/* thickness of right side	*/
	UCHAR	thickness_left_data[BV_SIZE_THICKNESS_DATA];	/* thickness of left side	*/
	UCHAR	thickness_right_data[BV_SIZE_THICKNESS_DATA];	/* thickness of right side	*/
	UCHAR	reserve[244];									/* reserve 					*/
	UCHAR	check_sum_code[2];								/* check sum code			*/
}BV_STATIC_CHARACTERISTIC_INFO;
	/*----------------------------------------------------------------------*/
	/*	Correction of picture information area								*/
	/*----------------------------------------------------------------------*/
typedef struct
{
	UCHAR	length[BV_SIZE_DATA_LENGTH];		/* data length		*/
	UCHAR	picture_data[BV_SIZE_PICTURE_DATA];	/* picture data		*/
}BV_CORRECTION_PICTURE_INFO;
	/*----------------------------------------------------------------------*/
	/*	Statistics information area											*/
	/*----------------------------------------------------------------------*/
typedef struct
{
	UCHAR	length[BV_SIZE_DATA_LENGTH];		/* data length		*/
	UCHAR	maker;								/* maker name		*/
	UCHAR	entry_date[BV_SIZE_ENTRY_DATE];		/* entry date		*/
	UCHAR	none_reserve;						/* not use			*/
	UCHAR	normal_1A[BV_SIZE_NUMBER_OF_SHEETS];
	UCHAR	normal_1B[BV_SIZE_NUMBER_OF_SHEETS];
	UCHAR	normal_1C[BV_SIZE_NUMBER_OF_SHEETS];
	UCHAR	normal_1D[BV_SIZE_NUMBER_OF_SHEETS];
	UCHAR	normal_2A[BV_SIZE_NUMBER_OF_SHEETS];
	UCHAR	normal_2B[BV_SIZE_NUMBER_OF_SHEETS];
	UCHAR	normal_2C[BV_SIZE_NUMBER_OF_SHEETS];
	UCHAR	normal_2D[BV_SIZE_NUMBER_OF_SHEETS];
	UCHAR	normal_3A[BV_SIZE_NUMBER_OF_SHEETS];
	UCHAR	normal_3B[BV_SIZE_NUMBER_OF_SHEETS];
	UCHAR	normal_3C[BV_SIZE_NUMBER_OF_SHEETS];
	UCHAR	normal_3D[BV_SIZE_NUMBER_OF_SHEETS];
	UCHAR	normal_4A[BV_SIZE_NUMBER_OF_SHEETS];
	UCHAR	normal_4B[BV_SIZE_NUMBER_OF_SHEETS];
	UCHAR	normal_4C[BV_SIZE_NUMBER_OF_SHEETS];
	UCHAR	normal_4D[BV_SIZE_NUMBER_OF_SHEETS];
	UCHAR	normal_5A[BV_SIZE_NUMBER_OF_SHEETS];
	UCHAR	normal_5B[BV_SIZE_NUMBER_OF_SHEETS];
	UCHAR	normal_5C[BV_SIZE_NUMBER_OF_SHEETS];
	UCHAR	normal_5D[BV_SIZE_NUMBER_OF_SHEETS];
	UCHAR	normal_6A[BV_SIZE_NUMBER_OF_SHEETS];
	UCHAR	normal_6B[BV_SIZE_NUMBER_OF_SHEETS];
	UCHAR	normal_6C[BV_SIZE_NUMBER_OF_SHEETS];
	UCHAR	normal_6D[BV_SIZE_NUMBER_OF_SHEETS];
	UCHAR	normal_recognition_length[BV_SIZE_RECOGNITION_LENGTH];/* 金種判定距離	*/
	UCHAR	suspect_1A[BV_SIZE_NUMBER_OF_SHEETS];
	UCHAR	suspect_1B[BV_SIZE_NUMBER_OF_SHEETS];
	UCHAR	suspect_1C[BV_SIZE_NUMBER_OF_SHEETS];
	UCHAR	suspect_1D[BV_SIZE_NUMBER_OF_SHEETS];
	UCHAR	suspect_2A[BV_SIZE_NUMBER_OF_SHEETS];
	UCHAR	suspect_2B[BV_SIZE_NUMBER_OF_SHEETS];
	UCHAR	suspect_2C[BV_SIZE_NUMBER_OF_SHEETS];
	UCHAR	suspect_2D[BV_SIZE_NUMBER_OF_SHEETS];
	UCHAR	suspect_3A[BV_SIZE_NUMBER_OF_SHEETS];
	UCHAR	suspect_3B[BV_SIZE_NUMBER_OF_SHEETS];
	UCHAR	suspect_3C[BV_SIZE_NUMBER_OF_SHEETS];
	UCHAR	suspect_3D[BV_SIZE_NUMBER_OF_SHEETS];
	UCHAR	suspect_4A[BV_SIZE_NUMBER_OF_SHEETS];
	UCHAR	suspect_4B[BV_SIZE_NUMBER_OF_SHEETS];
	UCHAR	suspect_4C[BV_SIZE_NUMBER_OF_SHEETS];
	UCHAR	suspect_4D[BV_SIZE_NUMBER_OF_SHEETS];
	UCHAR	suspect_5A[BV_SIZE_NUMBER_OF_SHEETS];
	UCHAR	suspect_5B[BV_SIZE_NUMBER_OF_SHEETS];
	UCHAR	suspect_5C[BV_SIZE_NUMBER_OF_SHEETS];
	UCHAR	suspect_5D[BV_SIZE_NUMBER_OF_SHEETS];
	UCHAR	suspect_6A[BV_SIZE_NUMBER_OF_SHEETS];
	UCHAR	suspect_6B[BV_SIZE_NUMBER_OF_SHEETS];
	UCHAR	suspect_6C[BV_SIZE_NUMBER_OF_SHEETS];
	UCHAR	suspect_6D[BV_SIZE_NUMBER_OF_SHEETS];
	UCHAR	suspect_recognition_length[BV_SIZE_RECOGNITION_LENGTH];/* 金種判定距離	*/
	UCHAR	counterfeit[BV_SIZE_NUMBER_OF_SHEETS];			/* counterfeit				*/
	UCHAR	unknown[BV_SIZE_NUMBER_OF_SHEETS];				/* unknown					*/
	UCHAR	none_valid_data[BV_SIZE_NUMBER_OF_SHEETS];		/* 鑑別情報なし格納枚数		*/
	UCHAR	unit_error[BV_SIZE_NUMBER_OF_SHEETS];			/* 装置異常格納枚数			*/
	UCHAR	move_error[BV_SIZE_NUMBER_OF_SHEETS];			/* 搬送異常格納枚数			*/
	UCHAR	shape_error[BV_SIZE_NUMBER_OF_SHEETS];			/* 形状異常格納枚数			*/
	UCHAR	recognition_error[BV_SIZE_NUMBER_OF_SHEETS];	/* 認識異常格納枚数			*/
	UCHAR	none_reserve1[4];								/* 未使用					*/
	UCHAR	none_valid_data_count[BV_SIZE_ERROR_COUNT];		/* 鑑別情報なしエラー発生回数 */
	UCHAR	unit_error_count[BV_SIZE_ERROR_COUNT];			/* ユニット異常発生回数		*/
	UCHAR	move_error_count[BV_SIZE_ERROR_COUNT];			/* 搬送異常発生回数			*/
	UCHAR	shape_error_count[BV_SIZE_ERROR_COUNT];			/* 形状異常発生回数			*/
	UCHAR	recognition_error_count[BV_SIZE_ERROR_COUNT];	/* 認識異常発生回数			*/
	UCHAR	AMC[BV_SIZE_ALARM_CODE_COUNT];					/* アラームコード発生回数	*/
	UCHAR	alarm_ptr[2];									/* アラーム履歴ポインタ		*/
	UCHAR	AMC_record[32];									/* アラーム履歴				*/
	UCHAR	reserve[48];									/* 予備						*/
}BV_STATISTICS_INFO;
	/*----------------------------------------------------------------------*/
	/*	Message information area											*/
	/*----------------------------------------------------------------------*/
typedef struct
{
	UCHAR	length[BV_SIZE_DATA_LENGTH];	/* data length			*/
	UCHAR	getgbvm[32768];					/* contents transmitted and received GBVM */
	UCHAR	freeze1[BV_SIZE_FREEZE_AREA];	/* freeze area 1		*/
	UCHAR	freeze2[BV_SIZE_FREEZE_AREA];	/* freeze area 2		*/
	UCHAR	freeze3[BV_SIZE_FREEZE_AREA];	/* freeze area 3		*/
}BV_MESSAGE_INFO;
	/*----------------------------------------------------------------------*/
	/*	Rev.(ZY01:BRZ-434) BV available validate information added			*/
	/*	Available information area											*/
	/*----------------------------------------------------------------------*/
typedef struct
{
	UCHAR	data[BV_SIZE_AVAILABLE_AREA];
}BV_AVAILABLE_INFO;
	/*----------------------------------------------------------------------*/
	/*	All image data area													*/
	/*	Rev.(ZY05:BRZ-661) Add definition of all image data area.			*/
	/*----------------------------------------------------------------------*/
typedef struct
{
	UCHAR	block[BV_SIZE_BLOCK_NUMBER];			/* block number			*/
	UCHAR	image[BV_SIZE_ALL_IMAGE_AREA];
}BV_ALL_IMAGE_INFO;
	/*----------------------------------------------------------------------*/
	/*	Rev.(AA43:BRZ-1520)		add											*/
	/*	cheque image data area												*/
	/*----------------------------------------------------------------------*/
typedef struct
{
	UCHAR	block[BV_SIZE_BLOCK_NUMBER];			/* block number			*/
	UCHAR	image[BV_SIZE_CHEQUE_IMAGE_AREA];
}BV_CHEQUE_IMAGE_INFO;
	/*----------------------------------------------------------------------*/
	/*	Signature data area													*/
	/*	Rev.(ZY04:BRZ-567)	Add definition of signature data size.			*/
	/*----------------------------------------------------------------------*/
typedef struct
{
	UCHAR	category;
	UCHAR	reserve1;
	UCHAR	sheets[2];
	UCHAR	reserve2[4];
	UCHAR	size[4];
	UCHAR	data[BV_SIZE_SIGNATURE_AREA];
}BV_SIGNATURE_INFO;
	/*----------------------------------------------------------------------*/
	/*	Rev.(ZY05:BRZ-624)	Add	BV_SERIAL_NUMBER_INFO						*/
	/*----------------------------------------------------------------------*/
typedef struct
{
	UCHAR	validation[4];
	UCHAR	serial_data[BV_SIZE_SERIAL_CHARACTER][5];
	UCHAR	reserve;
}BV_SERIAL_INFO;
typedef struct
{
	USHORT			sheets;
	USHORT			reserve;
	BV_SERIAL_INFO	serial_info[BV_SIZE_SERIAL_INFO];
}BV_SERIAL_NUMBER_INFO;
	/*----------------------------------------------------------------------*/
	/*	Rev.(ZY05:BRZ-624)	Add	BV_FEATURE_NUMBER_INFO						*/
	/*----------------------------------------------------------------------*/
typedef struct
{
	USHORT	genuine;
	USHORT	damage;
	USHORT	recognized;
	USHORT	suspect;
	USHORT	counterfeit;
	USHORT	reserve[3];
}BV_FEATURE_NUMBER_INFO;
	/*----------------------------------------------------------------------*/
	/*	bv info																*/
	/*	Rev.(ZZ06:BRZ-191)													*/
	/*	Rev.(ZZO6:BRZ-268) change definition of BV information area			*/
	/*	Rev.(ZY01:BRZ-434) BV available validate information added			*/
	/*	Rev.(ZY04:BRZ-567)	Add definition of signature data size.			*/
	/*----------------------------------------------------------------------*/
typedef	union
{
	struct
	{
		BV_REVISION_INFO				Revision;				/* RRV		*/
		BV_UNIT_INFO					Unit;					/* RUN		*/
		BV_ALARM_INFO					alarm;					/* RAL, CAL	*/
		BV_STATISTICS_INFO				Statistics;				/* RST, CST	*/
		BV_VALIDATION_INFO				Validation;				/* RVR, RVR2, DVR*/
		BV_MESSAGE_INFO					Message;				/* RMG, CMG	*/
		BV_STATIC_CHARACTERISTIC_INFO	StaticCharacteristis;	/* RVP, CVP	*/
		BV_CORRECTION_PICTURE_INFO		CorrectionPicture;		/* RVP, CVP	*/
		BV_AVAILABLE_INFO				available;				/* RBI		*/
		BV_SIGNATURE_INFO				Signature;				/* RSG		*/
		BV_FEATURE_NUMBER_INFO			FeatureNumber;			/* RNS		*/
		BV_SERIAL_NUMBER_INFO			SerialNumber;			/* RNO		*/
	}Kind;
}BV_DATA;
	/*----------------------------------------------------------------------*/
	/*	Result of BV read													*/
	/*	Rev.(ZY05:BRZ-616)	Add	BV_READ_RESULT.								*/
	/*----------------------------------------------------------------------*/
typedef struct
{
	BOOL	ret;
	ULONG	adr;
	ULONG	size;
}BV_READ_RESULT;

extern	BV_DATA				stBvInfo;
extern	BV_ALARM_INFO		stBvAlarmInfo;
	/*----------------------------------------------------------------------*/
	/*	Rev.(ZW01:BRZ-701) Add definition.									*/
	/*----------------------------------------------------------------------*/
typedef struct
{
	UCHAR	buf[BV_SIZE_GET_LAN];					/* data					*/
}BV_GET_LAN_BUF;
	/*----------------------------------------------------------------------*/
	/*	Rev.(ZY05:BRZ-624)	Add	BV_BLOCK_DATA								*/
	/*	Rev.(ZY05:BRZ-661) Add definition of all image data area.			*/
	/*	Rev.(ZW01:BRZ-701) Add definition of BvGetLanBuf.					*/
	/*	Rev.(AA43:BRZ-1520)	Add definition of ChequeImage.					*/
	/*----------------------------------------------------------------------*/
typedef	union
{
		BV_ALL_IMAGE_INFO		BvAllImage[2];				/*	RGP			*/
		BV_CHEQUE_IMAGE_INFO	ChequeImage[2];				/*	RCQ			*/
		BV_RECOGNITION_INFO		RecognitionData[2];			/* 	RVP, CVP	*/
		BV_GET_LAN_BUF			BvGetLanBuf[2];				/*				*/
}BV_BLOCK_DATA;
extern	BV_BLOCK_DATA		stBvBlockData;
	/*----------------------------------------------------------------------*/
	/*	Rev.(ZY05:BRZ-653)	Add	stBvChargeVdInfo							*/
	/*----------------------------------------------------------------------*/
extern	BV_VALIDATION_INFO	stBvChargeVdInfo;
	/*----------------------------------------------------------------------*/
	/*	Rev.(ZW01:BRZ-701) Add definition of vd area.						*/
	/*----------------------------------------------------------------------*/
typedef struct
{
	UCHAR	vd[BV_SIZE_VD];							/* vd					*/
	UCHAR	shortlength;							/* short side length	*/
	UCHAR	reserve[3];								/* reserve				*/
}BV_GET_VD;
	/*----------------------------------------------------------------------*/
	/*	Rev.(ZW01:BRZ-703) Add definition of near alarm.					*/
	/*	Rev.(ZW04:BRZ-873) Add member of bvin / bvout.						*/
	/*	Rev.(AA08:BRZ-1269) Add member of remaining on BV line sensor.		*/
	/*----------------------------------------------------------------------*/
typedef struct
{
	UCHAR	sensor;									/* sensor level			*/
	UCHAR	fan;									/* fan information		*/
	UCHAR	battery;								/* buttery information	*/
	UCHAR	remain;									/* remain on line sensor*/
	UCHAR	reserve[2];								/* reserve				*/
	UCHAR	bvin;									/* BVIN  information	*/
	UCHAR	bvout;									/* BVOUT information	*/
}BV_NEAR_ALARM;
	/*----------------------------------------------------------------------*/
	/*	Rev.(ZW01:BRZ-705)	Add definition of short side length.			*/
	/*	Rev.(AA21:BRZ-1436)	Add work area of short side length.				*/
	/*	Rev.(AA25:BRZ-1461)	Add label of note type.							*/
	/*----------------------------------------------------------------------*/
typedef struct
{
	UCHAR	data;									/* Note information		*/
	UCHAR	shortside;								/* short side length	*/
}BV_SHORT_SIDE_LENGTH;
#define		BV_DATA_NOTE_TYPE		BIT0

extern	BV_SHORT_SIDE_LENGTH	stBvShortSideLength[KIND_BILL_GENUINE_MAX];
extern	BV_SHORT_SIDE_LENGTH	stBvShortLengthWork[KIND_BILL_GENUINE_MAX];
	/*----------------------------------------------------------------------*/
	/*	Rev.(ZW04:BRZ-800)	Add definition.									*/
	/*	BV task process & status											*/
	/*----------------------------------------------------------------------*/
enum{
	BV_PROCESS					= 0xFF00,
	BV_PROCESS_IDLE				= 0x0000,
	BV_PROCESS_WAIT_RESULT		= 0x0100,
	BV_PROCESS_WAIT_RESULT_TEST	= 0x0200,
	BV_PROCESS_WAIT_RESPONSE	= 0x0300,
	BV_PROCESS_WAIT_RESET		= 0x0400,
	BV_PROCESS_DEBUG_ASYNC		= 0x0500,
	BV_STATUS					= 0x00FF,
	BV_STATUS_VALIDATE			= BIT0,
	BV_STATUS_DEBUG				= BIT1,
	BV_STATUS_SENSOR_ON			= BIT2
};
/****************************************************************************/
/*																			*/
/*	function prototypes							 							*/
/*																			*/
/****************************************************************************/
/*--------------------------------------------------------------------------*/
/*	bv task main															*/
/*--------------------------------------------------------------------------*/
void TaskBv( void );
/*--------------------------------------------------------------------------*/
/*	command																	*/
/*	Rev.(ZW04:BRZ-800)	Add	BV_DURING_VALIDATE.								*/
/*	Rev.(ZV05:BRZ-986)	Add	BV_CLEAR_FEATURE_IMAGE.							*/
/*	Rev.(ZU03:BRZ-1042)	Add	BV_CHANGE_CONNECTION_MODE.						*/
/*	Rev.(AA21:BRZ-1436)	Add argument of BvSetAvailable().					*/
/*	Rev.(AA25:BRZ-1461)	Add function that notifies note type.				*/
/*	Rev.(AA43:BRZ-1520)	add BvBeginReadChequeImage(),BvWaitReadChequeImage()*/
/*--------------------------------------------------------------------------*/
BOOL	BvBeginValidateStart( unsigned char mode );	/* validate start		*/
BOOL	BvWaitValidateStart( void );				/* validate start(wait)	*/
BOOL	BvBeginValidateStop( void );				/* validate stop		*/
BOOL	BvWaitValidateStop( void );					/* validate stop(wait)	*/
BOOL	BvReset( UCHAR );
void	BvCancel( void );
BOOL	BvBeginReadAllImage( void );
BOOL	BvBeginReadChequeImage( UCHAR );
BOOL	BvBeginReadRecognitionInfo( void );
BV_READ_RESULT*	BvWaitReadAllImage( void );
BV_READ_RESULT*	BvWaitReadChequeImage( void );
BV_READ_RESULT*	BvWaitReadRecognitionInfo( void );
BV_READ_RESULT*	BvRead( UCHAR info );
BV_READ_RESULT*	BvReadFeatureImage( void );
BV_READ_RESULT*	BvReadFeatureNumber( void );
BV_READ_RESULT*	BvReadSerialNumber( void );
BOOL	BvReadAvailable( void );
BOOL	BvSetAvailable( BOOL sw );
BOOL	BvClear( UCHAR info );
BOOL	BvDownload( char *pbBuffer );
BOOL	BvDownloadEnd( void );
BOOL	BvSensorOn( void );
BOOL	BvSensorOff( void );
int		BvSensorLevel( void );
BOOL	BvSetTime( void );
BOOL	BvReviseSensor( void );
BOOL	BvDuringValidate( void );
BOOL	BvClearFeatureImage( UCHAR mode );
BOOL	BvChangeConnectionMode( UCHAR mode );
BUFFER_INFO*	BvGetInfo( UCHAR kind );
UCHAR	BvGetNoteType( UCHAR num );
UCHAR	BvGetShortSideLength( UCHAR num );
void	BvSetStatus( USHORT status );
void	BvClearStatus( USHORT status );
USHORT	BvGetStatus( void );
	/*----------------------------------------------------------------------*/
	/*	Rev.(AA33:BRZ-1486)	Add function of signature near full inspection.	*/
	/*----------------------------------------------------------------------*/
BOOL	BvCheckNearFullSignature( void );
/*--------------------------------------------------------------------------*/
/*	for lan																	*/
/*--------------------------------------------------------------------------*/
TASK_MSG	BvGetMsg( USHORT len, UCHAR* buf );
BOOL		BvCheckContinuity( USHORT len, UCHAR* buf );
/*--------------------------------------------------------------------------*/
/*	for BV task																*/
/*--------------------------------------------------------------------------*/
void	BvInitializeReception( UCHAR* p );
void	BvEndReception( void );
ULONG	BvGetReceptionLength( void );
void	BvSetReceivingBufSize( UCHAR *buf );
/*--------------------------------------------------------------------------*/
/*	for debug																*/
/*	Rev.(ZZ02:BRZ-015)	API function to set dummy VD						*/
/*	Rev.(ZZ03:BRZ-015)	devide into two API function to set dummy VD		*/
/*	Rev.(ZZ04:BRZ-175)														*/
/*	Rev.(ZY02:BRZ-462)	add BvDispLastValidate()							*/
/*	Rev.(ZY04:BRZ-582)	add BvDownload() and BvDownloadEnd()				*/
/*	Rev.(ZY04:BRZ-592)	add BvRead()										*/
/*	Rev.(ZY05:BRZ-616)	add BvReadRequest(),BvReadWait()					*/
/*							BvCheckContinuity(),BvInitializeReception()		*/
/*							BvEndReception(),BvGetReceptionLength()			*/
/*--------------------------------------------------------------------------*/
void	BvDispLastValidate( void );
void	BvSetVdDummy( UCHAR vd1, UCHAR vd2 );
void	BvSetVdCodeDummy( ULONG vd1, ULONG vd2 );
void	BvSetVdDummyNumber( UCHAR num, UCHAR data );
UCHAR	BvGetVdDummyNumber( UCHAR num );
BOOL	BvDebugModeOn( BOOL db );
void	BvDebugModeOff( BOOL db );
EXT_BOOL	BvGetDebugMode( void );
void	BvSetAsyncVD( ULONG vd, int i );
ULONG	BvGetAsyncVD( int i );
