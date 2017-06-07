/***

	*************************************************************************
	*																		*
	*		header file for Mecha module									*
	*																		*
	*														MECHA.H			*
	*************************************************************************
	ALL RIGHTS RESERVED, COPYRIGHT(C) FUJITSU FRONTECH LIMITED. 2002-2007

	SN			Date		Name		Revision.No.	Contents
	-------------------------------------------------------------------------
	001-ZZ01	2002/11/07	M.Kibe		<BRZ-001>		The First Version
				2002/11/28	M.Kibe
				2003/03/24	M.Kibe						add MechaAbortProcess()
														add MechaAbortCancel()
	002-ZZ02	2003/04/02	M.Kibe		<BRZ-007>		add MechaWritePosition()
										<BRZ-007>		MECHA_POSITION is moved to Mecha.H from L_Mecha.H
				2003/04/04	M.Kibe		<BRZ-007>		add MechaReadPosition()
										<BRZ-007>		add MechaReadEndCode()
				2003/04/07	M.Kibe		<BRZ-007>		MECHA_POSITIN is moved to TYPEDEF.H
	003-ZZ03	2003/04/25	M.Kibe		<BRZ-030>		add MechaForceChange()
														add MechaCheckForceState()
				2003/05/07	M.Kamimura	<BRZ-077>		The position display function for debugging is added.
														:MechaDispPositionAll()
	004-ZZ04	2003/05/23	M.Kibe		<BRZ-030>		rename(MechaForceChange()->MechaSetDebugMode())
														      (MechaCheckForceState()->MechaGetDebugModeStatus())	
				2003/05/28	M.Kibe		<BRZ-145>		Cassette classification correspondence
	005-ZZ06	2003/07/15	M.Kibe		<BRZ-228>		add MechaSetProcessingDemand()
				2003/07/22	M.Kibe		<BRZ-228>		add MechaGetProcessingDemand()
				2003/08/13	M.Kibe		<BRZ-314>		add MechaSetMediaState()
														add MechaGetMediaState()
														add MechaClearMediaState()
	006-ZZ07	2003/09/09	M.Kibe		<BRZ-356>		add MechaGetEndCode()
				2003/09/12	M.Kibe		<BRZ-349>		add MechaAdjustSensorLevelTransport()
				2003/09/17	M.Kibe		<BRZ-368>		add MechaTakeBillEnd()
				2003/09/19	M.Kibe		<BRZ-349>		It change for sensor level set processing unification
														:MechaAdjustSensorLevelTransport()->MechaSetSensorLevel()
	007-ZY02	2003/11/07	M.Kibe		<BRZ-450>		add function of mecha position disp
														MechaDispPosition()
				2003/11/08	A.Maruyama	<BRZ-452>		add function of mecha error check and move
														:MechaCheckMoveErrorCode()
	008-ZY03	2003/12/05	M.Kibe		<BRZ-528>		add function of mecha information clear
														:MechaClearInfo()
	009-ZY04	2003/12/16	M.Kibe		<BRZ-555>		add function of preacceptor type acquisition
														:MechaGetTypePreAcceptor()
	010-ZW01	2004/02/03	M.Kibe		<BRZ-706>		add function
														:MechaGetBillThinck()
														:MechaSetBillThinck()
														:MechaClearBillThinck()
				2004/02/12	M.Kamimura	<BRZ-732>		add API function.
														:MechaClearEndCode()
	011-ZW04	2004/03/10	A.Maruyama	<BRZ-796>		add functions
														:MechaSetForbidRetry()
														:MechaCancelForbidRetry()
														:MechaClearForbidRetry()
														:MechaCheckForbidRetry()
														:MechaGetForbidRetry()
				2004/03/16	M.Kibe		<BRZ-828>		add functions
														:MechaCheckTrayEncoder()
														:MechaCheckBeltEncoder()
														:MechaSetTrayEncoderStatus()
														:MechaGetTrayEncoderStatus()
														:MechaClearTrayEncoderStatus()
														:MechaSetBeltEncoderStatus()
														:MechaGetBeltEncoderStatus()
														:MechaClearBeltEncoderStatus()
				2004/03/20	M.Kibe		<BRZ-828>		add functions
														:MechaStartTrayEncoderWatch()
														:MechaEndTrayEncoderWatch()
														:MechaStartBeltEncoderWatch()
														:MechaEndBeltEncoderWatch()
				2004/03/31	M.Kamimura	<BRZ-894>		add API function.
														:MechaCheckMediaRemainSensor()
	012-ZW06	2004/04/05	M.Kibe		<BRZ-900>		add function
														:MechaHaltProcess()
	013-ZV04	2004/04/19	M.Kibe		<BRZ-930>		add function
														:MechaPacHalfBillTimeUp()
														:MechaGetBillStatus()
														:MechaSetBillStatus()
														:MechaClearBillStatus()
														add enum
				2004/04/21	M.Kibe		<BRZ-949>		add function
														:MechaGetCarrierWatchStatus()
														:MechaSetCarrierWatchStatus()
														:MechaClearCarrierWatchStatus()
														add enum
	014-ZV05	2004/04/26	M.Kibe		<BRZ-963>		add function
														:MechaGetEscrowWatchStatus()
														:MechaSetEscrowWatchStatus()
														:MechaClearEscrowWatchStatus()
														add enum
				2004/04/27	M.Kibe		<BRZ-961>		add function
														:MechaPacDischargeTimeUp()
														:MechaCheckPacDischargeTimeUp()
	015-ZV07	2004/05/03	M.Kibe		<BRZ-978>		add function
														:MechaSepPusherFewDownTimeUp()
				2004/05/04	M.Kibe		<BRZ-978>		add enum
														add function
														:MechaGetPusherStartStatus()
														:MechaSetPusherStartStatus()
														:MechaClearPusherStartStatus()
	016-ZV08	2004/05/12	A.Maruyama	<BRZ-1011>		add function
														:MechaCheckMoving()
														:MechaCheckUnusualSensor()
							M.Kibe		<BRZ-1004>		add enum
														add function
														:MechaGetCassetteMoveStatus()
														:MechaSetCassetteMoveStatus()
														:MechaClearCassetteMoveStatus()
							M.Kibe		<BRZ-1023>		add function
														:MechaSetSensorLevelTemporarily()
	017-ZU08	2004/06/08	M.Kamimura	<BRZ-1092>		add label of BILL_STATUS.
														:BILL_STATUS_THICK
														:BILL_STATUS_LONG
	018-ZT02	2004/06/14	M.Kibe		<BRZ-1116>		add label of carrier watch status
														:CARRIER_STATUS_WATCH_PDSS
														add function
														:MechaSetMediaStatePdss()
				2004/06/15	M.Kibe		<BRZ-1124>		add function
														:MechaCheckSensorPartPosition()
	026-ZT10	2004/07/12	M.Kibe		<BRZ-1149>		add speed
														:PAC_TRAY_SPEED
														:PAC_BELT_SPEED
				2004/07/13	M.kibe		<BRZ-1151>		add length
														:PAC_PTCS_CHIP_LENGTH
														add motor speed
														:PAC_TRAY_MOTOR_SPEED
														:PAC_BELT_MOTOR_SPEED
														add timer
														PAC_TIME_WATCH_PTCS_CHIP
														add function
														:MechaPacPtcsOnTimeUp()
														:MechaClearPacPtcsOn()
				2004/07/14	M.Kibe		<BRZ-1151>		change length
														:PAC_PTCS_CHIP_LENGTH(3 -> 8)
	027-ZT11	2004/07/12	M.Kibe		<BRZ-1166>		add enum label
														:BILL_STATUS_2ND_LONG
	028-AA03	2004/07/30	M.Kibe		<BRZ-1185>		add function(PSxS surveillance time)
														:MechaGetPsxsSurveillanceTime()
														:MechaSetPsxsSurveillanceTime()
														:MechaClearPsxsSurveillanceTime()
	029-AA04	2004/08/06	M.Kibe		<BRZ-1183>		add Argument
														:MechaSetSensorLevelTemporarily()
										<BRZ-1191>		It corrects so that BackFeed of SEP after unjust interruption may be performed.
														:MechaGetAbortEnablePlace()
										<BRZ-1192>		HALT correspondence in shutter retry
														:MechaGetHaltEnablePlace()
														:MechaSetHaltEnablePlace()
														:MechaClearHaltEnablePlace()
				2004/08/10	M.Kibe		<BRZ-1191>		It corrects so that BackFeed of SEP after unjust interruption may be performed.
														:MechaAbortDisableProcess()
														:MechaClearAbortDisable()
														:MechaChangeAbortDisable()
														:MechaGetAbortEnable()
				2004/08/11	M.Kibe		<BRZ-1200>		Correction of the fault which is not processed after receipt 
														by the empty at the time of a sending out agency change etc.
														add function
														:MechaGetCassetteDownPlace()
														:MechaClearCassetteDownPlace()
														:MechaSetCassetteDownPlace()
														:MechaUpdateCassetteDownPlace()
	030-AA05	2004/08/26	M.Kibe		<BRZ-1224>		add enum label
														BILL_STATUS_FAIL_MOVE
	031-AA11	2004/10/19	M.Kibe		<BRZ-1309>		add enum (tray status)
														add function
														:MechaGetTrayStatus()
														:MechaClearTrayStatus()
														:MechaSetTrayStatus()
	032-AA13	2004/11/01	M.Kibe		<BRZ-1340>		It carrier-position-incorrect-detection-corresponds by the bill hologram
														add function
														:MechaSetCarrierHologramTime()
														:MechaClearCarrierHologramTime()
														:MechaPacCarrierHologramTimeUp()
														:MechaCheckPacCarrierHologramTimeUp()
				2004/11/04	M.Kibe		<BRZ-1340>		It carrier-position-incorrect-detection-corresponds by the bill hologram
														add function
														:MechaCarrierEcccOff()
														:MechaCarrierEcccOn()
														:MechaCarrierEcpcOff()
														:MechaCarrierEcpcOn()
	033-AA16	2004/12/07	M.Banba		<BRZ-1367>		Insertion surveillance under shutter closing.
														:MechaClearDetectMediumSC();
														:MechaSetDetectMediumSC();
														:MechaGetDetectMediumSC();
				2004/12/15	M.Kibe		<BRZ-1365>		MR operation order change correspondence
														:MechaCheckPrepareFeed()
				2004/12/20	M.Kibe		<BRZ-1372>		cassette hand stuffing full correspondence
														:MechaGetCassetteHandFullStatus()
														:MechaClearCassetteHandFullStatusAll()
														:MechaClearCassettePartsHandFullStatus()
														:MechaSetCassetteHandFullStatus()
				2004/12/24	M.Kibe		<BRZ-1372>		cassette hand stuffing full correspondence
														enum label change
														:CASSETTE_HAND_FULL_CHECK_YET
														Function name change
														:MechaClearCassetteHandFullStatus()
	034-AA17	2005/02/08	M.Kibe		<BRZ-1381>		Correspondence where medium flies to PDSS
														:MechaGetMediaStatePdss()
														:MechaClearMediaStatePdss()
														:MechaGetCarrierWatchStatusPdss()
														:MechaSetCarrierWatchStatusPdss()
														:MechaClearCarrierWatchStatus()
	035-AA18	2005/02/25	M.Kibe		<BRZ-1392>		Processing improvement when D-stopper cannot be saved
														add enum(PDAC status)
														:MechaSetPdacStatus()
														:MechaGetPdacStatus()
	038-AA25	2005/12/20	M.Kibe		<BRZ-1463>		How to stop change cassette phase is detected
														:MechaCheckStopImpeller()
														:MechaStartImpellerWatch()
														:MechaStopImpellerWatch()
				2005/12/22	M.Kibe		<BRZ-1463>		Function name change
														(MechaCheckStopImpeller()->MechaStopImpeller())
	039-AA28	2006/2/27	M.kibe		<BRZ-1468>		WC command speed-up correspondence
														:MechaClearCassettePrepareStatus()
														:MechaSetCassettePrepareStatus()
														:MechaGetCassettePrepareStatus()
	040-AA48	2006/06/18	T.Saji		<BRZ-1539>		WC command 10Euro double feed correspondence
														:MechaOnFeedRollerStatusSensor()
														:MechaStartFeedRollerPhaseWatch()
														:MechaStopFeedRollerPhaseWatch()
														:MechaCheckFeedRollerPhaseStatus()
				2006/06/21	M.Kibe		<BRZ-1540>		for transportation that doesn't use Hook
														add function
														:MechaSetHookUseStatus()
														:MechaGetHookUseStatus()
	041-AA49	2007/07/19	A.Maruyama	<BRZ-1543>		Shutter close when the error ended was supported
														add function for clear/set/get shutter error status
														:MechaClearErrorStatusShutter()
														:MechaSetErrorStatusShutter()
														:MechaGetErrorStatusShutter()
				2007/07/26	M.Kibe		<BRZ-1544>		for change of speed of separator
														add function
														:MechaSetSeparatorSpeedStatus()
														:MechaGetSeparatorSpeedStatus()
	042-AA52	2007/10/26	M.Kibe		<BRZ-1553>		Mechanism trouble correction when interlock comes off
														add function
														:MechaClearPosition()

COMMENT END
***/
/****************************************************************************/
/*																			*/
/*	defines																	*/
/*																			*/
/****************************************************************************/
			/*--------------------------------------------------------------*/
			/*	Speed														*/
			/*	Rev.(ZT10:BRZ-1149)											*/
			/*--------------------------------------------------------------*/
#define		PAC_TRAY_SPEED				0.14
#define		PAC_BELT_SPEED				0.14
			/*--------------------------------------------------------------*/
			/*	length														*/
			/*	Rev.(ZT10:BRZ-1151)											*/
			/*--------------------------------------------------------------*/
#define		PAC_PTCS_CHIP_LENGTH		8
			/*--------------------------------------------------------------*/
			/*	motor speed(pps)											*/
			/*	Rev.(ZT10:BRZ-1151)											*/
			/*--------------------------------------------------------------*/
#define		PAC_TRAY_MOTOR_SPEED				667
#define		PAC_BELT_MOTOR_SPEED				667
			/*--------------------------------------------------------------*/
			/*	timer(ms)													*/
			/*	Rev.(ZT10:BRZ-1151)											*/
			/*--------------------------------------------------------------*/
#define		PAC_TIME_WATCH_PTCS_CHIP			(long)PAC_PTCS_CHIP_LENGTH/PAC_TRAY_SPEED*1000/PAC_TRAY_MOTOR_SPEED
/****************************************************************************/
/*																			*/
/*	enum prototypes								 							*/
/*																			*/
/****************************************************************************/
	/*----------------------------------------------------------------------*/
	/*	Rev.(ZV04:BRZ-930)													*/
	/*	bill status type													*/
	/*	Rev.(ZU08:BRZ-1092)	Add label of thickness over.(Over road detect)	*/
	/*	Rev.(ZT11:BRZ-1166)	Add label of 2nd length over(PASS COVER)		*/
	/*	Rev.(AA05:BRZ-1224)	Add label of d-stopper thrust ng				*/
	/*----------------------------------------------------------------------*/
enum
{
	BILL_STATUS_NORMAL			= 0,
	BILL_STATUS_HALF			= BIT0,
	BILL_STATUS_SKEW			= BIT1,
	BILL_STATUS_THICK			= BIT2,
	BILL_STATUS_LONG			= BIT3,
	BILL_STATUS_2ND_LONG		= BIT4,
	BILL_STATUS_FAIL_MOVE	= BIT5
};
	/*----------------------------------------------------------------------*/
	/*	Rev.(ZV04:BRZ-949)													*/
	/*	carrier watch status												*/
	/*	Rev.(ZT02:BRZ-1116)													*/
	/*	add CARRIER_STATUS_WATCH_PDSS										*/
	/*----------------------------------------------------------------------*/
enum
{
	CARRIER_STATUS_NONE_WATCH	= 0,
	CARRIER_STATUS_WATCH		= BIT0,
	CARRIER_STATUS_WATCH_PDSS	= BIT1
};
	/*----------------------------------------------------------------------*/
	/*	Rev.(ZV05:BRZ-963)													*/
	/*	escrow watch status													*/
	/*----------------------------------------------------------------------*/
enum
{
	ESCROW_STATUS_CLEAR				= 0,
	ESCROW_STATUS_NONE_CHANGE_TOP	= BIT0
};
	/*----------------------------------------------------------------------*/
	/*	Rev.(ZV05:BRZ-978)													*/
	/*	pusher start status													*/
	/*----------------------------------------------------------------------*/
enum
{
	PUSHER_STATUS_CLEAR				= 0,
	PUSHER_STATUS_NG				= BIT0,
	PUSHER_STATUS_START				= BIT1,
	PUSHER_STATUS_NONE_MOVE			= BIT2
};
	/*----------------------------------------------------------------------*/
	/*	Rev.(ZV08:BRZ-1004)													*/
	/*	cassette move status												*/
	/*----------------------------------------------------------------------*/
enum
{
	CASSETTE_MOVE_STATUS_NORMAL		= 0,
	CASSETTE_MOVE_STATUS_WAIT		= BIT0
};
	/*----------------------------------------------------------------------*/
	/*	Rev.(AA11:BRZ-1309)													*/
	/*	tray status															*/
	/*----------------------------------------------------------------------*/
enum
{
	TRAY_STATUS_CLEAR			= 0,
	TRAY_STATUS_CLAMP_PRESS		= BIT0
};
	/*----------------------------------------------------------------------*/
	/*	Rev.(AA16:BRZ-1372)													*/
	/*	cassette hand full status											*/
	/*----------------------------------------------------------------------*/
enum
{
	CASSETTE_HAND_FULL_CHECK_YET	= 0,
	CASSETTE_HAND_FULL_NONE 		= 1,
	CASSETTE_HAND_FULL				= 2
};
	/*----------------------------------------------------------------------*/
	/*	Rev.(AA18:BRZ-1392)													*/
	/*	PDAC status															*/
	/*----------------------------------------------------------------------*/
enum
{
	PDAC_NOT_USE	= 0,
	PDAC_USE 		= 1
};

/****************************************************************************/
/*																			*/
/*	function prototypes							 							*/
/*																			*/
/****************************************************************************/
/*--------------------------------------------------------------------------*/
/*	mecha API function														*/
/*	Rev.(ZZ04:BRZ-145)														*/
/*	Model change of an argument(CASSETTE_TYPE->UCHAR)						*/
/*--------------------------------------------------------------------------*/
MECHA_PLACE	SysmGetSetCassette( UCHAR type );
/*--------------------------------------------------------------------------*/
/*	mecha control task main													*/
/*	Rev.(ZZ02:BRZ-007)														*/
/*	Rev.(ZZ03:BRZ-030)														*/
/*	Rev.(ZZ03:BRZ-077)	add MechaDispPositionAll()							*/
/*	Rev.(ZZ04:BRZ-030)														*/
/*		rename(MechaForceChange() ->MechaSetDebugMode())					*/
/*		rename(MechaCheckForceState()->MechaGetDebugModeStatus())			*/
/*	Rev.(ZZ06:BRZ-228)	add MechaSetProcessingDemand()						*/
/*	Rev.(ZZ06:BRZ-228)	add MechaGetProcessingDemand()						*/
/*	Rev.(ZZ06:BRZ-314)	add MechaSetMediaState()							*/
/*						add MechaGetMediaState()							*/
/*						add MechaClearMediaState()							*/
/*	Rev.(ZZ07:BRZ-356)	add MechaGetEndCode()								*/
/*	Rev.(ZZ07:BRZ-349)	add MechaAdjustSensorLevelTransport()				*/
/*	Rev.(ZZ07:BRZ-368)	add MechaTakeBillEnd()								*/
/*	Rev.(ZY02:BRZ-450)	add MechaDispPosition()								*/
/*	Rev.(ZY02:BRZ-452)	add MechaCheckMoveErrorCode()						*/
/*							MechaDisableErrorCode()							*/
/*	Rev.(ZY03:BRZ-528)	add MechaClearInfo()								*/
/*	Rev.(ZY04:BRZ-555)	add MechaGetTypePreAcceptor()						*/
/*	Rev.(ZW01:BRZ-706)	add MechaGetBillThinck()							*/
/*						add MechaSetBillThinck()							*/
/*						add MechaClearBillThinck()							*/
/*	Rev.(ZW01:BRZ-732)	add MechaClearEndCode()								*/
/*	Rev.(ZW04:BRZ-796)	add function for forbid retry						*/
/*							Mecha***ForbidRetry()							*/
/*									*** : Set,Cancel,Clear,Check,Get		*/
/*	Rev.(ZW04:BRZ-828)	add function for encoder							*/
/*							Mecha***Tray(Belt)EncoderStatus()				*/
/*									*** : Set,Clear,Get						*/
/*							Mecha***Tray(Belt)Encoder()						*/
/*									*** : Check								*/
/*	Rev.(ZW06:BRZ-902)	add function 										*/
/*							MechaHaltProcess()								*/
/*	Rev.(ZV08:BRZ-1023)	add function 										*/
/*							MechaSetSensorLevelTemporarily()				*/
/*	Rev.(ZT02:BRZ-1116)	add function 										*/
/*							MechaSetMediaStatePdss()						*/
/*	Rev.(AA04:BRZ-1183)	add Argument 										*/
/*							MechaSetSensorLevelTemporarily()				*/
/*	Rev.(AA17:BRZ-1381)	add function 										*/
/*							MechaGetMediaStatePdss()						*/
/*							MechaClearMediaStatePdss()						*/
/*	Rev.(AA52:BRZ-1553)	add function										*/
/*							MechaClearPosition()							*/
/*--------------------------------------------------------------------------*/
void TaskMecha( void );
void MechaUrgencyStop( MECHA_PLACE mecha );
void MechaAbortProcess( void );
void MechaAbortCancel( void );
void MechaHaltProcess( void );
void MechaWritePosition( PLACE_NO place , MECHA_POSITION position );
MECHA_POSITION	MechaReadPosition( PLACE_NO place );
MECHA_END_VALUE	MechaReadEndCode( PLACE_NO place );
void	MechaSetDebugMode( MECHA_DEBUG_MODE mode , MECHA_PLACE place );
MECHA_PLACE	MechaGetDebugModeState( MECHA_DEBUG_MODE mode );
void	MechaDispPositionAll( void );
void	MechaSetProcessingDemand( PLACE_NO ca , MECHA_DEMAND_CODE req );
MECHA_DEMAND_CODE	MechaGetProcessingDemand( PLACE_NO ca );
void	MechaSetMediaState( MEDIA_CHECK_VALUE state );
void	MechaSetMediaStatePdss( MEDIA_CHECK_VALUE state );
MEDIA_CHECK_VALUE	MechaGetMediaState( void );
void	MechaClearMediaState( void );
MEDIA_CHECK_VALUE	MechaGetMediaStatePdss( void );
void	MechaClearMediaStatePdss( void );

void			MechaClearEndCode( void );
MECHA_END_VALUE	MechaGetEndCode( void );
BOOL	MechaSetSensorLevel( EXT_MECHA_PLACE place , BOOL sw );
BOOL	MechaSetSensorLevelTemporarily( EXT_MECHA_PLACE place );
int	MechaTakeBillEnd( void );
void	MechaDispPosition( UCHAR part );
BOOL	MechaCheckMoveErrorCode( MECHA_PLACE mpReferent );
MECHA_PLACE		MechaDisableErrorCode( ONOFF bSw, MECHA_PLACE mpReferent );
void	MechaClearInfo( MECHA_PLACE place );
void	MechaClearPosition( MECHA_PLACE place );
UCHAR	MechaGetTypePreAcceptor( void );

USHORT	MechaGetBillThick( void );
void	MechaSetBillThick( void );
void	MechaClearBillThick( void );

void	MechaSetForbidRetry( MECHA_PLACE wPlace );
void	MechaCancelForbidRetry( MECHA_PLACE wPlace );
void	MechaClearForbidRetry( void );
BOOL	MechaCheckForbidRetry( MECHA_PLACE wPlace );
MECHA_PLACE	MechaGetForbidRetry( void );

void	MechaCheckTrayEncoder( void );
void	MechaCheckBeltEncoder( void );
void	MechaSetTrayEncoderStatus( UCHAR status );
UCHAR	MechaGetTrayEncoderStatus( void );
void	MechaClearTrayEncoderStatus( void );
void	MechaSetBeltEncoderStatus( UCHAR status );
UCHAR	MechaGetBeltEncoderStatus( void );
void	MechaClearBeltEncoderStatus( void );
void	MechaStartTrayEncoderWatch( void );
void	MechaEndTrayEncoderWatch( void );
void	MechaStartBeltEncoderWatch( void );
void	MechaEndBeltEncoderWatch( void );

	/*----------------------------------------------------------------------*/
	/*	Rev.(ZW04:BRZ-894)													*/
	/*----------------------------------------------------------------------*/
BOOL	MechaCheckMediaRemainSensor( EXT_MECHA_PLACE e_mecha );
	/*----------------------------------------------------------------------*/
	/*	Rev.(ZV04:BRZ-930)													*/
	/*----------------------------------------------------------------------*/
int		MechaPacHalfBillTimeUp( void );
UCHAR	MechaGetBillStatus( void );
void	MechaSetBillStatus( UCHAR status );
void	MechaClearBillStatus( void );
	/*----------------------------------------------------------------------*/
	/*	Rev.(ZV04:BRZ-949)													*/
	/*----------------------------------------------------------------------*/
UCHAR	MechaGetCarrierWatchStatus( void );
void	MechaSetCarrierWatchStatus( UCHAR status );
void	MechaClearCarrierWatchStatus( void );
	/*----------------------------------------------------------------------*/
	/*	Rev.(AA17:BRZ-1381)													*/
	/*----------------------------------------------------------------------*/
UCHAR	MechaGetCarrierWatchStatusPdss( void );
void	MechaSetCarrierWatchStatusPdss( void );
void	MechaClearCarrierWatchStatusPdss( void );
	/*----------------------------------------------------------------------*/
	/*	Rev.(ZV05:BRZ-963)													*/
	/*----------------------------------------------------------------------*/
UCHAR	MechaGetEscrowWatchStatus( void );
void	MechaSetEscrowWatchStatus( UCHAR status );
void	MechaClearEscrowWatchStatus( void );
	/*----------------------------------------------------------------------*/
	/*	Rev.(ZV05:BRZ-961)													*/
	/*----------------------------------------------------------------------*/
int		MechaPacDischargeTimeUp( void );
void	MechaCheckPacDischargeTimeUp( void );
	/*----------------------------------------------------------------------*/
	/*	Rev.(ZV07:BRZ-978)													*/
	/*----------------------------------------------------------------------*/
int		MechaSepPusherFewDownTimeUp( void );
UCHAR	MechaGetPusherStartStatus( void );
void	MechaSetPusherStartStatus( UCHAR status );
void	MechaClearPusherStartStatus( void );
	/*----------------------------------------------------------------------*/
	/*	Rev.(ZV08:BRZ-XXXX)													*/
	/*----------------------------------------------------------------------*/
BOOL	MechaCheckActuatorOff( MECHA_PLACE place );
	/*----------------------------------------------------------------------*/
	/*	Rev.(ZV08:BRZ-1011)													*/
	/*----------------------------------------------------------------------*/
BOOL	MechaCheckMoving( PLACE_NO bPlaceNo );
BOOL	MechaCheckUnusualSensor( UCHAR bSnsName );
	/*----------------------------------------------------------------------*/
	/*	Rev.(ZV08:BRZ-1004)													*/
	/*----------------------------------------------------------------------*/
UCHAR	MechaGetCassetteMoveStatus( void );
void	MechaSetCassetteMoveStatus( UCHAR status );
void	MechaClearCassetteMoveStatus( void );
	/*----------------------------------------------------------------------*/
	/*	Rev.(ZT02:BRZ-1124)													*/
	/*----------------------------------------------------------------------*/
BOOL	MechaCheckSensorPartPosition( PLACE_NO bPlaceNo );
	/*----------------------------------------------------------------------*/
	/*	Rev.(ZT10:BRZ-1151)													*/
	/*----------------------------------------------------------------------*/
int		MechaPacPtcsOnTimeUp( void );
void	MechaClearPacPtcsOn( void );
	/*----------------------------------------------------------------------*/
	/*	Rev.(AA03:BRZ-1185)													*/
	/*----------------------------------------------------------------------*/
long	MechaGetPsxsSurveillanceTime( void );
void	MechaSetPsxsSurveillanceTime( void );
void	MechaClearPsxsSurveillanceTime( void );
	/*----------------------------------------------------------------------*/
	/*	Rev.(AA04:BRZ-1191)													*/
	/*----------------------------------------------------------------------*/
void		MechaAbortDisableProcess( MECHA_PLACE place );
MECHA_PLACE	MechaGetAbortEnablePlace( void );
void		MechaClearAbortDisable( void );
void		MechaChangeAbortDisable( MECHA_PLACE place );
ONOFF		MechaGetAbortEnable( PLACE_NO place );
	/*----------------------------------------------------------------------*/
	/*	Rev.(AA04:BRZ-1192)													*/
	/*----------------------------------------------------------------------*/
MECHA_PLACE	MechaGetHaltEnablePlace( void );
void		MechaSetHaltEnablePlace( MECHA_PLACE place );
void		MechaClearHaltEnablePlace( void );
	/*----------------------------------------------------------------------*/
	/*	Rev.(AA04:BRZ-1200)													*/
	/*----------------------------------------------------------------------*/
MECHA_PLACE	MechaGetCassetteDownPlace( void );
void		MechaClearCassetteDownPlace( void );
void		MechaSetCassetteDownPlace( MECHA_PLACE place );
void		MechaUpdateCassetteDownPlace( MECHA_PLACE place );
	/*----------------------------------------------------------------------*/
	/*	Rev.(AA11:BRZ-1309)													*/
	/*----------------------------------------------------------------------*/
UCHAR	MechaGetTrayStatus( void );
void	MechaClearTrayStatus( void );
void	MechaSetTrayStatus( void );
	/*----------------------------------------------------------------------*/
	/*	Rev.(AA13:BRZ-1340)													*/
	/*----------------------------------------------------------------------*/
MECHA_END_VALUE	MechaSetCarrierHologramTime( long time );
void			MechaClearCarrierHologramTime( void );
int				MechaPacCarrierHologramTimeUp( void );
BOOL			MechaCheckPacCarrierHologramTimeUp( void );

void	MechaCarrierEcccOff( void );
void	MechaCarrierEcccOn( void );
void	MechaCarrierEcpcOff( void );
void	MechaCarrierEcpcOn( void );
	/*----------------------------------------------------------------------*/
	/*	Rev.(AA16:BRZ-1367)	Insertion surveillance under shutter closing.	*/
	/*----------------------------------------------------------------------*/
void	MechaClearDetectMediumSC( void );
void	MechaSetDetectMediumSC( void );
BOOL	MechaGetDetectMediumSC( void );
	/*----------------------------------------------------------------------*/
	/*	Rev.(AA16:BRZ-1365)	Insertion surveillance under shutter closing.	*/
	/*----------------------------------------------------------------------*/
BOOL	MechaCheckPrepareFeed(void);
	/*----------------------------------------------------------------------*/
	/*	Rev.(AA16:BRZ-1372)	Insertion surveillance under shutter closing.	*/
	/*----------------------------------------------------------------------*/
UCHAR	MechaGetCassetteHandFullStatus( PLACE_NO place);
void	MechaClearCassetteHandFullStatus( PLACE_NO place );
void	MechaSetCassetteHandFullStatus( PLACE_NO place , UCHAR status );
	/*----------------------------------------------------------------------*/
	/*	Rev.(AA18:BRZ-1392)													*/
	/*	Processing improvement when D-stopper cannot be saved				*/
	/*----------------------------------------------------------------------*/
void	MechaSetPdacStatus( UCHAR status );
UCHAR	MechaGetPdacStatus( void );
	/*----------------------------------------------------------------------*/
	/*	Rev.(AA25:BRZ-1463)													*/
	/*	How to stop change cassette phase is detected						*/
	/*----------------------------------------------------------------------*/
void	MechaStopImpeller(PLACE_NO ca);
void	MechaStartImpellerWatch( PLACE_NO ca );
void	MechaStopImpellerWatch(PLACE_NO ca);
	/*----------------------------------------------------------------------*/
	/*	Rev.(AA28:BRZ-1468)													*/
	/*	WC command speed-up correspondence									*/
	/*	(PrepareStatus clear/set/get)										*/
	/*----------------------------------------------------------------------*/
void	MechaClearCassettePrepareStatus( MECHA_PLACE place );
void	MechaSetCassettePrepareStatus( MECHA_PLACE place );
BOOL	MechaGetCassettePrepareStatus( PLACE_NO ca );
	/*----------------------------------------------------------------------*/
	/*	Rev.(AA48:BRZ-1539)													*/
	/*	Processing improvement WC command double feed						*/
	/*----------------------------------------------------------------------*/
void	MechaOnFeedRollerStatusSensor(PLACE_NO ca );
void	MechaStartFeedRollerPhaseWatch( PLACE_NO ca );
void	MechaStopFeedRollerPhaseWatch(PLACE_NO ca);
ONOFF	MechaCheckFeedRollerPhaseStatus(PLACE_NO ca);
	/*----------------------------------------------------------------------*/
	/*	Rev.(AA48:BRZ-1540)													*/
	/*	for transportation that doesn't use Hook(set/get)					*/
	/*----------------------------------------------------------------------*/
void	MechaSetHookUseStatus( BOOL sw );
BOOL	MechaGetHookUseStatus( void );
	/*----------------------------------------------------------------------*/
	/*	Rev.(AA49:BRZ-1543)													*/
	/*	Shutter close when the error ended was supported					*/
	/*----------------------------------------------------------------------*/
void	MechaClearErrorStatusShutter( void );
void	MechaSetErrorStatusShutter( void );
BOOL	MechaGetErrorStatusShutter( void );
	/*----------------------------------------------------------------------*/
	/*	Rev.(AA49:BRZ-1544)													*/
	/*	for change of speed of separator(set/get)							*/
	/*----------------------------------------------------------------------*/
void	MechaSetSeparatorSpeedStatus( BOOL sw );
BOOL	MechaGetSeparatorSpeedStatus( void );
/*--------------------------------------------------------------------------*/
/*	cassette control task main												*/
/*--------------------------------------------------------------------------*/
void TaskCassetteControl( void );
/*--------------------------------------------------------------------------*/
/*	cassette1 task main														*/
/*--------------------------------------------------------------------------*/
void TaskCassette1( void );
/*--------------------------------------------------------------------------*/
/*	cassette2 task main														*/
/*--------------------------------------------------------------------------*/
void TaskCassette2( void );
/*--------------------------------------------------------------------------*/
/*	cassette3 task main														*/
/*--------------------------------------------------------------------------*/
void TaskCassette3( void );
/*--------------------------------------------------------------------------*/
/*	cassette4 task main														*/
/*--------------------------------------------------------------------------*/
void TaskCassette4( void );
/*--------------------------------------------------------------------------*/
/*	upper control task main													*/
/*--------------------------------------------------------------------------*/
void TaskUpper( void );
/*--------------------------------------------------------------------------*/
/*	preacceptor task main													*/
/*--------------------------------------------------------------------------*/
void TaskPreAcceptor( void );
/*--------------------------------------------------------------------------*/
/*	escrow task main														*/
/*--------------------------------------------------------------------------*/
void TaskEscrow( void );
/*--------------------------------------------------------------------------*/
/*	separator task main														*/
/*--------------------------------------------------------------------------*/
void TaskSeparator( void );
/*--------------------------------------------------------------------------*/
/*	shutter task main														*/
/*--------------------------------------------------------------------------*/
void TaskShutter( void );
