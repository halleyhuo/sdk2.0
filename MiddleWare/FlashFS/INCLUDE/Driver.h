/***

	*************************************************************************
	*																		*
	*		header file for actuator & sensor driver module					*
	*																		*
	*														Driver.h		*
	*************************************************************************
	ALL RIGHTS RESERVED, COPYRIGHT(C) FUJITSU FRONTECH LIMITED. 2002-2007

	SN			Date		Name		Revision.No.	Contents
	-------------------------------------------------------------------------
	001-ZZ01	2003/03/xx	A.Kojima	<BRZ-001>		The First Version
	002-ZZ02	2003/04/08	A.Kojima	<BRZ-010>		Add disable starting of
														stepping motor
				2003/04/16	A.Kojima	<BRZ-019>		Add adjust level of sensor
	003-ZY01	2003/10/21	A.Kojima	<BRZ-429>		change for B-model
	004-ZY02	2003/11/21	A.Kojima	<BRZ-476>		Add shutter DC motor
														:DrvDcmInitialize(),
														 DrvDcmStartShutter() add
	005-ZY04	2003/12/18	A.Kojima	<BRZ-568>		Add function of get direction & on/off
														for linear solenoid
														:DrvLsolGetDirection(),
														 DrvLsolGetOnOff() add
	006-ZY05	2004/01/08	A.Kojima	<BRZ-569>		Add function for over current
														:DrvOcCheck(),DrvOcGetLocationPort() add
										<BRZ-628>		Add function of abort for transport DC motor
														:DrvTdcmAbortStart(),DrvTdcmCancelAbort() add
	007-ZY06	2004/01/23	A.Kojima	<BRZ-680>		Add function of fix & free status for sensor status
														:DrvSnsFixStatus(),DrvSnsFreeStatus() add
				2004/01/26	A.Maruyama	<BRZ-684>		add function of display idle code
														:DrvLed7DisplayIdle()
	008-ZW01	2004/01/31	A.Maruyama	<BRZ-702>		delete code for A-model
	009-ZW04	2004/03/23	A.Kojima	<BRZ-863>		add function which check rotating
														:DrvTdcmCheckRotating() add
				2004/03/26	A.Kojima	<BRZ-875>		add function which get on/off for
														rotary solenoid
														:DrvRsolGetOnOff() add
	009-ZU03	2004/05/26	A.Kojima	<BRZ-1050>		add function of exciting counter
														:DrvSmGetExcitingCounter(),
														 DrvSmSetEnableExcitingCounter(),
														 DrvLsolGetExcitingCounter(),
														 DrvRsolGetExcitingCounter() add
	010-ZT02	2004/06/11	A.Kojima	<BRZ-1108>		add function of temperature sensor
														:DrvTmpsGetTemperature() add
														add function of A/D converter
														:DrvAdcInitialize(),DrvAdcStart(),
														 DrvAdcGetData(),DrvAdcIrq() add
										<BRZ-1109>		add function of ICS
														:DrvIcsCheck() add
	011-AA04	2004/08/03	A.Kojima	<BRZ-1187>		add function of disabling out
														:DrvDisableOutAll(),DrvSmDisableOut(),
														 DrvDcmInitializeDisable(),DrvDcmDisableOut(),
														 DrvTdcmInitializeDisable(),DrvTdcmDisableOut(),
														 DrvSolInitializeDisable(),DrvSolDisableOut(),
														 DrvMeiInitializeDisable(),DrvMeiDisableOut() add
				2004/08/06	A.Kojima	<BRZ-1193>		add function of power off infinity
														:DrvPowerOffInfinity() add
				2004/08/09	A.Kojima	<BRZ-1195>		add function of get out direction
														:DrvDcmGetOutDirectionShutter() add
	012-AA12	2004/10/19	A.Kojima	<BRZ-1311>		add function for read mask
														:DrvSnsReadMask(),DrvSnsReadMaskRemove() add
	013-AA18	2005/03/03	A.Kojima	<BRZ-1393>		add function for setting mecha error place
														at sensor adjusting
														:DrvSnsSetAdjustErrorMechaPlace() add
	014-AA19	2005/03/18	A.Kojima	<BRZ-1407>		add function of chopping for single
														pupose operation
														:DrvLsolSwitchForSingle(),
														 DrvLsolOnOffForSingle() add
	015-AA21	2005/06/21	A.Kojima	<BRZ-1435>		add function of out direction
														:DrvDcmOutDirectionShutter() add
	016-AA48	2007/05/07	T.Saji		<BRZ-1531>		support 2000pps for SESM,SEPM,EESM,ERSM
														:DrvSmIrqCommon2() add
														:DrvSmIrqSingle4() delete
COMMENT END
***/
/****************************************************************************/
/*																			*/
/*	function prototypes														*/
/*																			*/
/****************************************************************************/
/*--------------------------------------------------------------------------*/
/*	Common																	*/
/*	Rev.(ZY01:BRZ-429)														*/
/*	 Change argument of DrvPowerSwitchCassette()							*/
/*	Rev.(ZY05:BRZ-569)														*/
/*	 Add DrvOcCheck(),DrvOcGetLocationPort()								*/
/*	Rev.(AA04:BRZ-1187)														*/
/*	 add DrvDisableOutAll()													*/
/*	Rev.(AA04:BRZ-1193)														*/
/*	 add DrvPowerOffInfinity()												*/
/*--------------------------------------------------------------------------*/
void	DrvInitialize( void );						/* Initialize									*/
void	DrvStart( void );							/* Start										*/
void	DrvOffAll( void );							/* Off all actuators							*/
void	DrvDisableOutAll( ONOFF );					/* Disable all actuators						*/
void	DrvPowerSwitch( ONOFF );					/* Switch power									*/
void	DrvPowerOffInfinity( void );				/* Off power infinity							*/
void	DrvPowerSwitchCassette( ONOFF );			/* Switch power for cassette					*/
BOOL	DrvOcCheck( void );							/* Check over current							*/
UCHAR	DrvOcGetLocationPort( int );				/* Get data of location port for over current	*/
void	DrvOcIrq( void );							/* Interrupt processing for over current		*/
/*--------------------------------------------------------------------------*/
/*	Stepping Motor															*/
/*	Rev.(ZU03:BRZ-1050)														*/
/*	 add DrvSmGetExcitingCounter(),DrvSmSetEnableExcitingCounter()			*/
/*	Rev.(AA04:BRZ-1187)														*/
/*	 add DrvSmDisableOut()													*/
/*	Rev.(AA48:BRZ-1531)														*/
/*	 add DrvSmIrqCommon2()													*/
/*	 delete DrvSmIrqSingle4()												*/
/*--------------------------------------------------------------------------*/
void	DrvSmInitialize( void );								/* Initialize											*/
void	DrvSmInitializeDisable( void );							/* Initialize disabling									*/
void	DrvSmInitializeAddOnFunction( void );					/* Initialize add on function							*/
void	DrvSmStartTimer( void );								/* Start timer											*/
BOOL	DrvSmStart( char, char, char, char, USHORT, char );		/* Start												*/
BOOL	DrvSmStop( char, USHORT, char );						/* Stop													*/
BOOL	DrvSmChangeSpeed( char, char, USHORT, char );			/* Change speed											*/
void	DrvSmDisableOut( ONOFF );								/* Disable out											*/
void	DrvSmDisableStart( char, char, ONOFF );					/* Disable or enable starting							*/
char	DrvSmGetStatus( char );									/* Get status											*/
char	DrvSmGetPhaseStatus( char );							/* Get status of phase									*/
char	DrvSmGetDirection( char );								/* Get direction										*/
char	DrvSmGetSpeed( char );									/* Get speed											*/
long	DrvSmGetRemainingStep( char );							/* Get number of remaining step							*/
ONOFF	DrvSmGetStatusDisableStart( char, char );				/* Get status of disable starting						*/
char	DrvSmGetExcitingCounter( void );						/* Get number of exciting motor							*/
void *	DrvSmSetAddOnFunctionStart( char, void ( * )( void ) );	/* Set add on function (call when the motor start)		*/
void	DrvSmSetEnableExcitingCounter( ONOFF *tbl );			/* Set enable motor for exciting counter				*/
void	DrvSmIrqCommon( void );									/* Interrupt handler (control for common)				*/
void	DrvSmIrqCommon2( void );								/* Interrupt handler (control for common 100 micro)		*/
void	DrvSmIrqSingle0( void );								/* Interrupt handler (control for single motor)			*/
void	DrvSmIrqSingle1( void );								/* Interrupt handler (control for single motor)			*/
void	DrvSmIrqSingle2( void );								/* Interrupt handler (control for single motor)			*/
void	DrvSmIrqSingle3( void );								/* Interrupt handler (control for single motor)			*/
/*--------------------------------------------------------------------------*/
/*	Rev.(ZY02:BRZ-476)	add													*/
/*	DC Motor																*/
/*	Rev.(AA04:BRZ-1187)														*/
/*	 add DrvDcmInitializeDisable(),DrvDcmDisableOut()						*/
/*	Rev.(AA04:BRZ-1195)														*/
/*	 add DrvDcmGetOutDirectionShutter()										*/
/*	Rev.(AA21:BRZ-1435)														*/
/*	 add DrvDcmOutDirectionShutter()										*/
/*--------------------------------------------------------------------------*/
void	DrvDcmInitialize( void );				/* Initialize							*/
void	DrvDcmInitializeDisable( void );		/* Initialize disabling					*/
void	DrvDcmDisableOut( ONOFF );				/* Disable out							*/
BOOL	DrvDcmStartShutter( char );				/* Start shutter motor					*/
BOOL	DrvDcmOutDirectionShutter( char );		/* Out direction of shutter motor		*/
char	DrvDcmGetOutDirectionShutter( void );	/* Get out direciton of shutter motor	*/
/*--------------------------------------------------------------------------*/
/*	Transport DC Motor														*/
/*	Rev.(ZY05:BRZ-628)														*/
/*	 Add DrvTdcmAbortStart(),DrvTdcmCancelAbort()							*/
/*	Rev.(ZW04:BRZ-863)														*/
/*	 add DrvTdcmCheckRotating()												*/
/*	Rev.(AA04:BRZ-1187)														*/
/*	 add DrvTdcmInitializeDisable(),DrvTdcmDisableOut()						*/
/*--------------------------------------------------------------------------*/
void	DrvTdcmInitialize( void );					/* Initialize			*/
void	DrvTdcmInitializeDisable( void );			/* Initialize disabling	*/
void	DrvTdcmDisableOut( ONOFF );					/* Disable out			*/
BOOL	DrvTdcmStart( char, char );					/* Start				*/
BOOL	DrvTdcmStop( char, char );					/* Stop					*/
char	DrvTdcmGetStatus( void );					/* Get status			*/
char	DrvTdcmGetDir( void );						/* Get direction		*/
BOOL	DrvTdcmCheckRotating( void );				/* Check rotating		*/
void	DrvTdcmAbortStart( void );					/* Abort start			*/
void	DrvTdcmCancelAbort( void );					/* Cancel abort			*/
/*--------------------------------------------------------------------------*/
/*	Solenoid ( Common )														*/
/*	Rev.(AA04:BRZ-1187)														*/
/*	 add DrvSolInitializeDisable(),DrvSolDisableOut()						*/
/*--------------------------------------------------------------------------*/
void	DrvSolInitialize( void );					/* Initialize			*/
void	DrvSolInitializeDisable( void );			/* Initialize disabling	*/
void	DrvSolDisableOut( ONOFF );					/* Disable out			*/
void	DrvSolIrq( void );							/* Interrupt processing	*/
/*--------------------------------------------------------------------------*/
/*	Linear Solenoid															*/
/*	Rev.(ZY04:BRZ-568)														*/
/*	 add DrvLsolGetDirection(),DrvLsolGetOnOff()							*/
/*	Rev.(ZU03:BRZ-1050)														*/
/*	 add DrvLsolGetExcitingCounter()										*/
/*	Rev.(AA19:BRZ-1407)														*/
/*	 add DrvLsolSwitchForSingle(),DrvLsolOnOffForSingle()					*/
/*--------------------------------------------------------------------------*/
BOOL	DrvLsolSwitch( char, char );			/* Switch a direction								*/
BOOL	DrvLsolOnOff( char, ONOFF );			/* ON or OFF										*/
BOOL	DrvLsolSwitchForSingle( char, char );	/* Switch a direction for single pupose operation	*/
BOOL	DrvLsolOnOffForSingle( char, ONOFF );	/* ON or OFF for single pupose operation			*/
char	DrvLsolGetDirection( char );			/* Get current direction							*/
ONOFF	DrvLsolGetOnOff( char );				/* Get current ON/OFF								*/
char	DrvLsolGetExcitingCounter( void );		/* Get number of exciting solenoid					*/
/*--------------------------------------------------------------------------*/
/*	Rotary Solenoid															*/
/*	Rev.(ZW04:BRZ-875)														*/
/*	 DrvRsolGetOnOff()														*/
/*	Rev.(ZU03:BRZ-1050)														*/
/*	 DrvRsolGetExcitingCounter()											*/
/*--------------------------------------------------------------------------*/
BOOL	DrvRsolSwitch( char, char );		/* Switch a direction				*/
void	DrvRsolOffAll( void );				/* All off							*/
ONOFF	DrvRsolGetOnOff( char );			/* Get current direction			*/
char	DrvRsolGetExcitingCounter( void );	/* Get number of exciting solenoid	*/
/*--------------------------------------------------------------------------*/
/*	Media Indicator															*/
/*	Rev.(AA04:BRZ-1187)														*/
/*	 add DrvMeiInitializeDisable(),DrvMeiDisableOut()						*/
/*--------------------------------------------------------------------------*/
void	DrvMeiInitialize( void );					/* Initialize			*/
void	DrvMeiInitializeDisable( void );			/* Initialize disabling	*/
void	DrvMeiDisableOut( ONOFF );					/* Disable out			*/
BOOL	DrvMeiSwitch( ONOFF, int );					/* Switch on or off		*/
/*--------------------------------------------------------------------------*/
/*	Sensor ( Write )														*/
/*	Rev.(AA18:BRZ-1393)														*/
/*	 add DrvSnsSetAdjustErrorMechaPlace()									*/
/*--------------------------------------------------------------------------*/
void	DrvSnsWriteInitialize( void );						/* Initialize							*/
BOOL	DrvSnsAdjustLevel( const char * );					/* Adjust level							*/
BOOL	DrvSnsAdjustLevelTemporarily( const char * );		/* Adjust level temporarily				*/
BOOL	DrvSnsCheckAdjusting( char );						/* Check whether adjusting				*/
void	DrvSnsInitializeLevel( char );						/* Initialize sensor level				*/
UCHAR	DrvSnsGetLevel( char );								/* Get sensor level						*/
void	DrvSnsSetLevel( char, UCHAR );						/* Set sensor level						*/
void	DrvSnsSetLevelAll( UCHAR * );						/* Set all sensor level					*/
BOOL	DrvSnsRewriteLevel( void );							/* Write memorized all sensor level		*/
void	DrvSnsSetAdjustErrorMechaPlace( char, PLACE_NO );	/* Set mecha place of adjusting error	*/
BOOL	DrvSnsWriteLevel( char, UCHAR );					/* Write level							*/
BOOL	DrvSnsWriteLevelAll( UCHAR * );						/* Write level all sensors				*/
BOOL	DrvSnsWriteHardLevel( char, UCHAR );				/* Write hardware level					*/
/*--------------------------------------------------------------------------*/
/*	Sensor ( Read )															*/
/*	Rev.(ZY06:BRZ-680)														*/
/*	 add DrvSnsFixStatus(),DrvSnsFreeStatus()								*/
/*	Rev.(AA12:BRZ-1311)														*/
/*	 add DrvSnsReadMask(),DrvSnsReadMaskRemove()							*/
/*--------------------------------------------------------------------------*/
void	DrvSnsReadInitialize( void );		/* Initialize										*/
void	DrvSnsReadStart( void );			/* Start											*/
ONOFF	DrvSnsRead( USHORT );				/* Read a sensor									*/
char	DrvSnsPairRead( USHORT );			/* Read a pair of sensors							*/
UCHAR	DrvSnsPortRead( USHORT );			/* Read sensor port									*/
void	DrvSnsSkewEnableAll( void );		/* Enable to count skew condition (all sensors)		*/
BOOL	DrvSnsSkewEnable( char );			/* Enable to count skew condition					*/
void	DrvSnsSkewDisableAll( void );		/* Disable to count skew condition (all sensors)	*/
void	DrvSnsFixStatus( PLACE_NO );		/* Fix sensor status								*/
void	DrvSnsFreeStatus( PLACE_NO );		/* Free sensor status								*/
void	DrvSnsReadMask( USHORT );			/* Mask read										*/
void	DrvSnsReadMaskRemove( USHORT );		/* Remove mask read									*/
void	DrvSnsIrq( void );					/* Interrupt processing								*/
void	DrvSnsIrqTransport( void );			/* Interrupt processing (sensor of transporter)		*/
/*--------------------------------------------------------------------------*/
/*	7 segments LED															*/
/*	Rev.(ZY06:BRZ-684)														*/
/*	 add DrvLed7DisplayIdle()												*/
/*--------------------------------------------------------------------------*/
void	DrvLed7Display( UCHAR, UCHAR );						/* Display code					*/
void	DrvLed7DisplayHex( UCHAR, ONOFF, UCHAR, ONOFF );	/* Display hexadecimal number	*/
void	DrvLed7DisplayIdle( void );							/* Display idle code			*/
/*--------------------------------------------------------------------------*/
/*	Rev.(ZT02:BRZ-1108)														*/
/*	Temperature sensor														*/
/*--------------------------------------------------------------------------*/
short	DrvTmpsGetTemperature( void );					/* Get temperature	*/
/*--------------------------------------------------------------------------*/
/*	Rev.(ZT02:BRZ-1108)														*/
/*	ICS																		*/
/*--------------------------------------------------------------------------*/
BOOL	DrvIcsCheck( void );						/* check dead or alive	*/
/*--------------------------------------------------------------------------*/
/*	Rev.(ZT02:BRZ-1108)														*/
/*	A/D converter															*/
/*--------------------------------------------------------------------------*/
void	DrvAdcInitialize( void );					/* Initialize			*/
void	DrvAdcStart( void );						/* Start				*/
short	DrvAdcGetData( int );						/* Get data				*/
void	DrvAdcIrq( void );							/* Interrupt processing	*/
