/***

	*************************************************************************
	*																		*
	*		Header of Sensor Watch Module									*
	*																		*
	*														WATCH.H			*
	*************************************************************************
	ALL RIGHTS RESERVED, COPYRIGHT(C) FUJITSU FRONTECH LIMITED. 2002-2004

	SN			Date		Name		Revision.No.	Contents
	-------------------------------------------------------------------------
	001-ZY01	2003/10/22	M.Banba		<BRZ-432>		The First Version
	002-ZY04	2003/12/19	M.Banba		<BRZ-575>		The measure against knot jam
														:WatchGetKnotJam()
														:WatchClearKnotJam()
	003-AA10	2004/10/12	A.Maruyama	<BRZ-1301>		add functions for disable watching unusual-sensor
														:WatchDisableCheckSensorAll()
														:WatchDisableCheckSensor()
														:WatchEnableCheckSensorAll()
														:WatchEnableCheckSensor()
														:WatchCheckDisableCheckSensor()
	004-AA14	2004/11/20	A.Maruyama	<BRZ-1357>		add functions for unusual-changed-sensor
														:WatchDiagnoseUnusualSensor()
	005-AA54	2008/01/25	A.Maruyama	<BRZ-1557>		add functions for extended cassette
														:WatchGetCassetteExtendedType()

COMMENT END
***/

/****************************************************************************/
/*																			*/
/*	function prototypes							 							*/
/*																			*/
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/*	API function															*/
/*	Rev.(ZY04:BRZ-575)	add WatchGetKnotJam(),WatchClearKnotJam()			*/
/*	Rev.(AA10:BRZ-1301)	add functions for disable watching unusual-sensor	*/
/*				WatchDisableCheckSensorAll(),WatchDisableCheckSensor(),		*/
/*				WatchEnableCheckSensorAll(),WatchEnableCheckSensor(),		*/
/*				WatchCheckDisableCheckSensor()								*/
/*	Rev.(AA14:BRZ-1357)	add functions for unusual-changed-sensor			*/
/*				WatchDiagnoseUnusualSensor()								*/
/*	Rev.(AA54:BRZ-1557)	add functions for extended cassette					*/
/*				WatchGetCassetteExtendedType()								*/
/*--------------------------------------------------------------------------*/
MECHA_PLACE		WatchGetSetCassette( UCHAR type );
UCHAR			WatchGetCassetteType( PLACE_NO place );
UCHAR			WatchGetCassetteExtendedType( PLACE_NO place );		/*	Rev.(AA54:BRZ-1557)	add 	*/
BOOL			WatchGetKnotJam( void );
void			WatchClearKnotJam( void );

void			WatchDisableCheckSensorAll( void );
void			WatchDisableCheckSensor( USHORT wSns );
void			WatchEnableCheckSensorAll( BOOL fSwitch );
void			WatchEnableCheckSensor( USHORT wSns, BOOL fSwitch );
BOOL			WatchCheckDisableCheckSensor( USHORT wSns );

UCHAR			WatchDiagnoseUnusualSensor( USHORT wSns, ONOFF bOnOff );
