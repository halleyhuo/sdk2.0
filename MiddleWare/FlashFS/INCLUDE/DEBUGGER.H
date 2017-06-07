/***

	*************************************************************************
	*																		*
	*		header file for debugger module									*
	*																		*
	*														DEBUGGER.H		*
	*************************************************************************
	ALL RIGHTS RESERVED, COPYRIGHT(C) FUJITSU FRONTECH LIMITED. 2002-2004

	SN			Date		Name		Revision.No.	Contents
	-------------------------------------------------------------------------
	001-ZZ01	2002/10/31	A.Maruyama	<BRZ-001>		The First Version
	002-ZZ03	2003/04/22	A.Kojima	<BRZ-027>		Change logging method for sensor
	003-ZZ04	2003/06/12	M.Kamimura	<BRZ-159>		Change argument of DbgLogVD()
														:DbgLogVD()
	004-ZZ06	2003/07/15	A.Kojima	<BRZ-236>		Add LAN log
				2003/07/31	M.Kamimura	<BRZ-285>		Add command log definition.
														:DBG_LOG_CMD_xxx
	005-ZY02	2003/11/08	A.Kojima	<BRZ-438>		Add dump using SCI
	006-ZY06	2004/01/26	M.Banba		<BRZ-690>		add DbgLogGetInfo()
	007-ZW04	2004/03/08	Y.Saito		<BRZ-807>		Add SciDumpSwitch()
														:SciDumpSwitch()
														add function for RAS-AA
														:DbgLogDispAll()
COMMENT END
***/

/****************************************************************************/
/*																			*/
/*	defines																	*/
/*																			*/
/****************************************************************************/
	/*----------------------------------------------------------------------*/
	/*	Command log															*/
	/*----------------------------------------------------------------------*/
#define		DBG_LOG_CMD_START			0x00
#define		DBG_LOG_CMD_END				0x01
#define		DBG_LOG_CMD_STATUS			0x02

/****************************************************************************/
/*																			*/
/*	function prototypes														*/
/*																			*/
/****************************************************************************/
/*--------------------------------------------------------------------------*/
/*																			*/
/*	Debugger Task															*/
/*																			*/
/*--------------------------------------------------------------------------*/
void	TaskDebug( void );

/*--------------------------------------------------------------------------*/
/*																			*/
/*	SCI																		*/
/*																			*/
/*--------------------------------------------------------------------------*/
	/*----------------------------------------------------------------------*/
	/*	SCI Interrupt Handler												*/
	/*----------------------------------------------------------------------*/
BOOL	SciIrqER( void );			/* (receive ERror)						*/
BOOL	SciIrqRX( void );			/* (Receive data register full)			*/
void	SciIrqTX( void );			/* (Transmit data register empty)		*/
void	SciIrqTE( void );			/* (Transmit End)						*/

	/*----------------------------------------------------------------------*/
	/*	SCI Initialize														*/
	/*----------------------------------------------------------------------*/
void	SciInitialize( void );

	/*----------------------------------------------------------------------*/
	/*	SCI select print													*/
	/*----------------------------------------------------------------------*/
ULONG	SciSelectPrint( ULONG, ONOFF );

	/*----------------------------------------------------------------------*/
	/*	SCI Transmit routines												*/
	/*----------------------------------------------------------------------*/
void	putchar	( uchar data );
int		sprintf	( char *, char *, ... );
int		printf	( char *, ... );
int		printf_f( char *, ... );				/* forcedly output		*/
int		printf_s( ULONG, char *, ... );			/* select output		*/
int		vprintf	( char *, int * );
int		vprintf_f( char *, int * );

	/*----------------------------------------------------------------------*/
	/*	SCI Receive routines												*/
	/*----------------------------------------------------------------------*/
int		getchar	( void );

	/*----------------------------------------------------------------------*/
	/*	SCI Dump routines													*/
	/*	Rev.(ZY02:BRZ-438)		add											*/
	/*	Rev.(ZW04:BRZ-807)		Add	SciDumpSwitch().						*/
	/*----------------------------------------------------------------------*/
void	SciDump( int, char *, char *, ... );
void	SciDumpForce( int, char *, char *, ... );
void	SciDumpSelect( ULONG, int, char *, char *, ... );
void	SciDumpSwitch( void );

/*--------------------------------------------------------------------------*/
/*																			*/
/*	Logging routines														*/
/*																			*/
/*--------------------------------------------------------------------------*/
	/*----------------------------------------------------------------------*/
	/*	Logging Area Information											*/
	/*----------------------------------------------------------------------*/
//BUFFER_INFO		*DbgLogGetInfo( UCHAR kind );
	/*----------------------------------------------------------------------*/
	/*	Logging Area Initialize												*/
	/*----------------------------------------------------------------------*/
void	DbgLogClear	( void );
void	DbgLogSequenceNumberReset( void );

	/*----------------------------------------------------------------------*/
	/*	Logging Process														*/
	/*	Rev.(ZZ04:BRZ-159)	change argument of DbgLogVD ( USHORT -> ULONG )	*/
	/*	Rev.(ZZ06:BRZ-236)	add for LAN										*/
	/*----------------------------------------------------------------------*/
void	DbgLogPacket	( UCHAR dir, char *pkt , char *value );
void	DbgLogSensor	( USHORT data );
void	DbgLogMotor		( UCHAR name, UCHAR cont, USHORT step );
void	DbgLogSolenoid	( UCHAR name, UCHAR cont );
void	DbgLogSkew		( UCHAR name, UCHAR data );
void	DbgLogTimeUp	( ULONG func );
void	DbgLogVD		( ULONG data );
void	DbgLogUSB		( UCHAR kind, UCHAR data );
void	DbgLogCommand	( UCHAR kind, USHORT data );
void	DbgLogLAN		( UCHAR id, UCHAR kind, ULONG data );
void	DbgLogOthers	( USHORT usdata, ULONG uldata );

	/*----------------------------------------------------------------------*/
	/*	Logging Data Display Process										*/
	/*	Rev.(ZZ06:BRZ-236)	add for LAN										*/
	/*	Rev.(ZW04:BRZ-807)	add DbgLogDispAll()								*/
	/*----------------------------------------------------------------------*/
void	DbgLogDispPacket	( void );
void	DbgLogDispSensor	( void );
void	DbgLogDispMotor		( void );
void	DbgLogDispSolenoid	( void );
void	DbgLogDispSkew		( void );
void	DbgLogDispTimeUp	( void );
void	DbgLogDispVD		( void );
void	DbgLogDispUSB		( void );
void	DbgLogDispCommand	( void );
void	DbgLogDispLAN		( void );
void	DbgLogDispOthers	( void );
void	DbgLogDispAll		( void );
