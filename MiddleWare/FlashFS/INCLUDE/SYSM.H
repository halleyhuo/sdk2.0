/***

	*************************************************************************
	*																		*
	*		header file for system management module						*
	*																		*
	*														SYSM.H			*
	*************************************************************************
	ALL RIGHTS RESERVED, COPYRIGHT(C) FUJITSU FRONTECH LIMITED. 2002-2007

	SN			Date		Name		Revision.No.	Contents
	-------------------------------------------------------------------------
	001-ZZ01	2002/10/28	A.Maruyama	<BRZ-001>		The First Version
	002-ZZ04	2003/05/28	A.Maruyama	<BRZ-146>		add function prototype which get machine-type
	003-ZZ04	2003/06/17	A.Maruyama	<BRZ-167>		add functions of program's version get/set/clear
														:SysmGetProgramVersion()
														:SysmSetProgramVersion()
														:SysmClearProgramVersion()
	004-ZZ05	2003/07/05	A.Maruyama	<BRZ-203>		add process for re-download
														:SysmDownloadJump()
														:SysmDisableInterrupt()
	005-ZZ07	2003/09/20	A.Maruyama	<BRZ-386>		add process of re-download for BOOT-Program
														:SysmFlashWriteBOOT()
														:SysmFlashEraseBOOT()
														:SysmFlashEraseOldBOOT()
														:SysmFlashCheckBOOT()
														:SysmDownloadJumpToROM()
										<BRZ-387>		add process of re-start for RT-Command
														:SysmJumpToMAIN()
	006-ZY03	2003/12/12	A.Maruyama	<BRZ-548>		add shutter mode function prototypes
														:SysmSetShutterUsable()
														:SysmCheckShutterUsable()
	007-ZY04	2003/12/16	A.Maruyama	<BRZ-563>		reject bin type get function was added
														:SysmGetRejectBinType()
	008-ZY05	2004/01/11	A.Maruyama	<BRZ-639>		add function for file control
														:SysmFlashWriteINF()
														:SysmFlashWriteFIX()
														:SysmFlashReadINF()
														:SysmFlashReadFIX()
														:SysmFlashDeleteINF()
														:SysmFlashDeleteFIX()
	009-ZW01	2004/02/14	A.Maruyama	<BRZ-739>		add functions for control-data-file
														:SysmFlashWriteControlData()
														:SysmFlashReadControlData()
														:SysmFlashDeleteControlData()
														:SysmClearControlData()
														:SysmCopyControlData()
														:SysmCheckControlData()
	010-ZW03	2004/02/28	A.Maruyama	<BRZ-780>		add function
														:SysmRestartMain()
	011-ZW04	2004/03/17	A.Maruyama	<BRZ-841>		add functions for error analysis log
														:SysmFlashWriteAnalysisLog()
														:SysmFlashReadAnalysisLog()
														:SysmFlashDeleteAnalysisLog()
														:SysmFlashWriteSavingLog()
														:SysmFlashReadSavingLog()
														:SysmFlashDeleteSavingLog()
				2004/03/18	A.Maruyama	<BRZ-841>		move section address from L_SYSM.H
				2004/03/23	A.Maruyama	<BRZ-855>		add SECTION for Des Key
														:pTopAddressDesKey/pEndAddressDesKey
										<BRZ-865>		add function of periodic data save
														:SysmFlashWritePeriodic()
	012-ZV05	2004/04/27	A.Maruyama	<BRZ-965>		add function of file system initialize
														:SysmFlashFileSystemInitialize()
										<BRZ-971>		add SECTION for D-section on SRAM with parity
														:D_BGN,D_END,D_WITH_P_start
				2004/04/28								add start/end address for P-section
														:piProgramStart,piProgramEnd
														add function for memory break check
														:SysmCheckMemoryBreak()
				2004/04/29								add functions for stop/start memory check
														:SysmStopCheckMemory()
														:SysmStartCheckMemory()
	013-AA04	2004/08/09	A.Maruyama	<BRZ-1196>		add function of checked communication error between upper and lower PCB.
														:SysmCheckCommunicationPCB()
										<BRZ-1201>		add SECTION for loging data expand area
														:pTopAddressLogExpand
														:pEndAddressLogExpand
	014-AA14	2004/11/29	A.Maruyama	<BRZ-1360>		add SECTION for mecha-position-information data
														:pTopAddressMechaInfo
														:pEndAddressMechaInfo
	015-AA21	2005/06/09	A.Maruyama	<BRZ-1431>		add SECTION for Unit Serial Number data
														:pTopAddressSerialNumber,pEndAddressSerialNumber
														add functions for Unit Serial Number
														:SysmFlashWriteSerialNumber()
														:SysmFlashReadSerialNumber()
														:SysmFlashDeleteSerialNumber()
	016-AA37	2006/12/11	A.Maruyama	<BRZ-1507>		When the HT-command is received in state watch type ST-command,
														the trouble that becomes the command processing overtime is corrected.
														 Add functions.
														 :SysmSetHTatWatch()
														 :SysmCheckHTatWatch()
	017-AA45	2007/04/23	A.Maruyama	<BRZ-1528>		Power-ON report is supported
														Add functions
														:SysmSetStatusPowerOn()
														:SysmClearStatusPowerOn()
														:SysmGetStatusPowerOn()

COMMENT END
***/


/****************************************************************************/
/*																			*/
/*	variables																*/
/*																			*/
/****************************************************************************/
/*--------------------------------------------------------------------------*/
/*	section address															*/
/*--------------------------------------------------------------------------*/
extern	int		*B_BGN,				*B_END;
extern	int		*ISRAM_start,		*ISRAM_tail;

extern	int		*P_ISRAM_start,		*P_ISRAM_tail;
extern	int		*P_ISRAM_EX_start,	*P_ISRAM_EX_tail;

extern	long	*SysmStackTop;
extern	long	*VectorTop;
extern	long	*VectorEnd;

	/*----------------------------------------------------------------------*/
	/*	Rev.(AA04:BRZ-1201)	add B_ESRAM_SAVE_LOG_EXPAND						*/
	/*----------------------------------------------------------------------*/
extern	int		*pTopAddressLogExpand,	*pEndAddressLogExpand;

extern	int		*pTopAddressCtrlData,	*pEndAddressCtrlData;

extern	int		*pTopAddressSYS1,	*pEndAddressSYS1;
extern	int		*pTopAddressSTT1,	*pEndAddressSTT1;
extern	int		*pTopAddressLOG1,	*pEndAddressLOG1;
extern	int		*pTopAddressINF,	*pEndAddressINF;
extern	int		*pTopAddressFIX,	*pEndAddressFIX;
	/*----------------------------------------------------------------------*/
	/*	Rev.(AA14:BRZ-1360)	add top/end address for B_ESRAM_MECHA_INFO		*/
	/*----------------------------------------------------------------------*/
extern	int		*pTopAddressMechaInfo,	*pEndAddressMechaInfo;
	/*----------------------------------------------------------------------*/
	/*	Rev.(ZW04:BRZ-841)	add top/end address for B_ESRAM_ANALYSIS_LOG	*/
	/*----------------------------------------------------------------------*/
extern	int		*pTopAddressAnalysisLog,	*pEndAddressAnalysisLog;
	/*----------------------------------------------------------------------*/
	/*	Rev.(AA21:BRZ-1431)	add top/end address for Unit Serial No.			*/
	/*----------------------------------------------------------------------*/
extern	int		*pTopAddressSerialNumber,	*pEndAddressSerialNumber;
	/*----------------------------------------------------------------------*/
	/*	Rev.(ZW04:BRZ-855)	add top/end address for Des Key Section			*/
	/*----------------------------------------------------------------------*/
extern	int		*pTopAddressDesKey,		*pEndAddressDesKey;

extern	int		*pTopAddressINF_DVR,	*pEndAddressINF_DVR;

	/*----------------------------------------------------------------------*/
	/*	Rev.(ZV05:BRZ-971)	add top/end address for P-section				*/
	/*----------------------------------------------------------------------*/
extern	int		*piProgramStart,	*piProgramEnd;
	/*----------------------------------------------------------------------*/
	/*	Rev.(ZV05:BRZ-971)	add top/end address for D-section				*/
	/*----------------------------------------------------------------------*/
extern	int		*D_BGN,	*D_END;
extern	int		*D_WITH_P_start;

/****************************************************************************/
/*																			*/
/*	function prototypes														*/
/*																			*/
/****************************************************************************/
TCB		*SysmGetTCB( TASK_ID );
UCHAR	SysmGetMachineType( void );		/*	Rev.(ZZ04:BRZ-146)	add			*/
void	SysmCheckMachineType( void );

void	SysmSetShutterUsable( BOOL mode );	/*	Rev.(ZY03-BRZ-548)	add		*/
BOOL	SysmCheckShutterUsable( void );		/*	Rev.(ZY03-BRZ-548)	add		*/

void	SysmSetCassetteType( void );
UCHAR	SysmGetCassetteType( PLACE_NO place );
void	SysmSetCassetteDenomination( PLACE_NO place, UCHAR denomi );
UCHAR	SysmGetCassetteDenomination( PLACE_NO place );
MECHA_PLACE	SysmGetSetCassette( UCHAR type );
UCHAR	SysmGetRejectBinType( void );
void	SysmDebugModeOn( MECHA_PLACE mecha, UCHAR type );
void	SysmDebugModeOff( void );


void	SysmWatchDogRefresh( void );

void	SysmDownReset( long );
#define	SYSDOWN(err,cd)	SysmDownReset((long)((cd<<16)|err)) /* 		*/

void	SysmDebuggerJump( void );
void	SysmDownloadJump( UCHAR *ptr );
void	SysmDownloadJumpToROM( UCHAR *ptr );
void	SysmJumpToMAIN( UCHAR *ptr );
void	SysmRestartMain( void );

void	SysmDisableInterrupt( void );

void	_tim_irq(void);						/* À²ÏŠ„žˆ—ŽÀ‘Ì		*/
BOOL	_set_system_timer(uchar *s);		/* “úŽž¨•b•ÏŠ·			*/
BOOL	_edit_system_date(uchar *s);		/* •b¨“ú•t•ÏŠ·			*/
BOOL	_edit_system_date_yyyy(uchar *s);	/* •b¨“ú•t•ÏŠ·(”N4Œ…—p)*/
BOOL	_edit_system_time(uchar *s);		/* •b¨Žž•ª•b•ÏŠ·		*/
void	_get_system_timer(ulong *sec,ushort *ms);/* ÐØ•bÃÞ°ÀŽæ‚èo‚µ*/

void	SysmFlashFileSystemInitialize( void );	/*	Rev.(ZV05:BRZ-965)	*/

void	SysmFlashWritePeriodic( void );		/*	Rev.(ZW04:BRZ-865)	add	*/
void	SysmFlashWriteSYS1( void );
void	SysmFlashWriteSTT1( void );
void	SysmFlashWriteLOG1( void );
void	SysmFlashWriteINF( void );
void	SysmFlashWriteFIX( void );
void	SysmFlashWriteControlData( void );
void	SysmFlashWriteAnalysisLog( void );
void	SysmFlashWriteSavingLog( void );
void	SysmFlashWriteSerialNumber( void );		/*	Rev.(AA21:BRZ-1431)		*/

BOOL	SysmFlashReadSYS1( void );
BOOL	SysmFlashReadSTT1( void );
BOOL	SysmFlashReadLOG1( void );
BOOL	SysmFlashReadINF( void );
BOOL	SysmFlashReadFIX( void );
BOOL	SysmFlashReadControlData( void );
BOOL	SysmFlashReadAnalysisLog( void );
BOOL	SysmFlashReadSavingLog( void );
BOOL	SysmFlashReadSerialNumber( void );		/*	Rev.(AA21:BRZ-1431)		*/

void	SysmFlashDeleteSYS1( void );
void	SysmFlashDeleteSTT1( void );
void	SysmFlashDeleteLOG1( void );
void	SysmFlashDeleteINF( void );
void	SysmFlashDeleteFIX( void );
void	SysmFlashDeleteControlData( void );
void	SysmFlashDeleteAnalysisLog( void );
void	SysmFlashDeleteSavingLog( void );
void	SysmFlashDeleteSerialNumber( void );	/*	Rev.(AA21:BRZ-1431)		*/
void	SysmFlashDeleteFirm( void );

void	SysmClearControlData( void );
BOOL	SysmCopyControlData( UCHAR *pbSrc, ULONG nCount, ULONG nOffset );
BOOL	SysmCheckControlData( void );

void	SysmGetProgramVersion( UCHAR bKind, UCHAR *pbDst );
void	SysmSetProgramVersion( UCHAR bKind, UCHAR *pbSrc );
void	SysmClearProgramVersion( UCHAR bKind );

BOOL	SysmFlashWriteBOOT( UCHAR *pbSrc, ULONG nCount, ULONG nOffset );
BOOL	SysmFlashEraseBOOT( void );
BOOL	SysmFlashEraseOldBOOT( void );
BOOL	SysmFlashCheckBOOT( void );

int		open(char* name, int mode);
int		close(int fileno);
int		read(int fileno, char* buf, unsigned int count);
int		write(int fileno, char* buf, unsigned int count);
int		lseek(int fileno, long offset, int base);
int		remove(const char* pathname);
int		rename(const char* old, const char* new);

BOOL	SysmCheckMemoryBreak( void );		/*		Rev.(ZV05:BRZ-971)	*/
void	SysmStopCheckMemory( void );		/*		Rev.(ZV05:BRZ-971)	*/
void	SysmStartCheckMemory( void );		/*		Rev.(ZV05:BRZ-971)	*/

BOOL	SysmCheckCommunicationPCB( void );	/*		Rev.(AA04:BRZ-1196)	*/

/*--------------------------------------------------------------------------*/
/*	Rev.(AA37:BRZ-1507)		Add functions.									*/
/*--------------------------------------------------------------------------*/
void	SysmSetHTatWatch( BOOL sw );
BOOL	SysmCheckHTatWatch( void );
/*--------------------------------------------------------------------------*/
/*	Rev.(AA45:BRZ-1528)		Add functions.									*/
/*--------------------------------------------------------------------------*/
void	SysmSetStatusPowerOn( void );
void	SysmClearStatusPowerOn( void );
UCHAR	SysmGetStatusPowerOn( void );
