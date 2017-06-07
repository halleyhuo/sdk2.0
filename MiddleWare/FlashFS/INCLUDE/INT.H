/***

	*************************************************************************
	*																		*
	*		header file for interrupt module								*
	*																		*
	*														INT.H			*
	*************************************************************************
	ALL RIGHTS RESERVED, COPYRIGHT(C) FUJITSU FRONTECH LIMITED. 2002-2003

	SN			Date		Name		Revision.No.	Contents
	-------------------------------------------------------------------------
	001-ZZ01	2002/10/28	M.Banba		BRZ-001			The First Version
				2003/02/28	M.Banba						add Function prototype
														:IntOn
														:IntOFF
														:IntInitialize
														:IntPrepare
														:IntDrawStart
				2003/03/14	A.Maruyama					move prototypes of time-up fanction for ras from INT_API.C
				2003/04/16	M.Kamimura	BRZ-015			Delete IntSetVdDummy()
	002-ZZ03	2003/04/22	A.Kojima	BRZ-021			change function for new upper(A3 Mech.)
				2003/05/12	M.Kamimura	BRZ-100			Add Insertion / presenting completion condition clear processing
				2003/05/14	M.Banba		<BRZ-117>		Int debug mode
	003-ZZ06	2003/08/19	M.Kamimura	<BRZ-316>		add draw number-of-sheets increment / get function.
														:IntIncDrawRequest()
														:IntGetDrawRequest()
				2003/08/20	A.Kojima	<BRZ-295>		change for A4 Pre-Acceptor
														:OnPTPC(),OffPTPC(),OnPBPC(),
														 OffPBPC(),OnPDSS(),OffPDSS()
	004-ZY01	2003/10/02	A.Kojima	<BRZ-406>		change for B'-model
				2003/10/06	M.Kamimura	<BRZ-413>		Add processing of change media.
														:IntTimeUpIoChangeMedia()
	004-ZY03	2003/12/02	M.Banba		<BRZ-513>		add check stay bill
														:IntStartCheckStay()
	005-ZY04	2003/12/19	M.Kamimura	<BRZ-572>		Add processing of invalid operation.
														:IntTimeUpIoInvalidOperation()
	006-ZY05	2004/01/06	M.Banba		<BRZ-604>		DESKEW is moved during a high-speed rotation check at a home.
				2004/01/07	A.Kojima	<BRZ-619>		Add ILOF
														:OnILOF(),OffILOF()
	007-ZY06	2004/01/25	M.Banba		<BRZ-684>		Dispense Enable Switch correspondence
	008-ZW01	2004/02/07	A.Kojima	<BRZ-723>		add sensor of B2-model
														:OnPHPC(),OffPHPC(),OnESPC(),OffESPC(),
														 OnPLPC(),OffPLPC()
	009-ZV01	2004/04/08	M.Kamimura	<BRZ-911>		add sensor of B3-model.
														:OnETLS(),OffETLS(),OnETRS(),OffETRS()
										<BRZ-912>		add sensor of B3-model.
														:OnETLC(),OffETLC()
	010-ZV03	2004/04/12	M.Kamimura	<BRZ-917>		add function of Re-Feed.
														:IntReFeedRequest()
	011-ZV05	2004/04/27	M.Kamimura	<BRZ-961>		Add processing of add discharge.
														:IntTimeUpIoAddDischarge()
										<BRZ-962>		Add processing of more discharge.
														:IntTimeUpIoMoreDischarge()
				2004/04/30	A.Kojima	<BRZ-979>		add argument for BVxx function
														:OnBVIN(),OffBVIN(),OnBVOUT(),OffBVOUT()
	012-AA04	2004/08/05	M.Kamimura	<BRZ-1189>		add sensor of D stopper projection detection.
														:OnPDAC(),OffPDAC()
	013-AA09	2004/10/04	A.Kojima	<BRZ-1284>		add function of print transport control table
														:IntPrintTransportControlTable() add
	014-AA10	2004/10/12	A.Kojima	<BRZ-1303>		add function of print feed pass & phase counter
														:IntPrintFeedPassPhaseCounter() add
	015-AA14	2004/11/29	A.Kojima	<BRZ-1362>		add function of adjusting de-skew roller to home
														:IntAdjustDeSkewHome() add
	016-AA17	2005/02/10	A.Kojima	<BRZ-1388>		add function of checking de-skew
														:IntCheckDeSkew() add
	017-AA19	2005/03/31	A.Kojima	<BRZ-1419>		add function of printing for skew data of note
														delete function of printing for skew data of note
														:IntPrintSkew() add & delete
	018-AA20	2005/05/13	A.Kojima	<BRZ-1428>		add function of clearing data for compress
														:IntClearDataForCompress() add
	019-AA21	2005/06/08	A.Kojima	<BRZ-1430>		add function for SSRS,SSLS,SSOS
														:OnSSRS(),OffSSRS(),OnSSLS(),OffSSLS(),OnSSOS(),OffSSOS() add
	020-AA25	2005/12/26	A.Kojima	<BRZ-1461>		change for polymer note
														:IntPrintTransportControlTable()
	021-AA28	2006/03/03	A.Kojima	<BRZ-1471>		add function for ERLS,ERRS,EDLS,EDRS
														:OnERLS(),OffERLS(),OnERRS(),OffERRS(),
														 OnEDLS(),OffEDLS(),OnEDRS(),OffEDRS() add
	022-AA54	2008/01/24	A.Kojima	<BRZ-1557>		add function for CS1E,CS2E,CS3E,CS4E
														:OnCS1E(),OffCS1E(),OnCS2E(),OffCS2E(),
														 OnCS3E(),OffCS3E(),OnCS4E(),OffCS4E() add
COMMENT END
***/
/****************************************************************************/
/*																			*/
/*	function prototypes														*/
/*																			*/
/****************************************************************************/
/*--------------------------------------------------------------------------*/
/*	sensor edge																*/
/*	 Change PLPC->PTPC,PPRC->PBPC											*/
/*	 Add PDSS																*/
/*	Rev.(ZY01:BRZ-406)														*/
/*	 Delete SWLC,SWRC and add SFIC,SFOC,SHDC,SBLC,UGLC,LFHS					*/
/*	Rev.(ZY05:BRZ-619)														*/
/*	 Add ILOF																*/
/*	Rev.(ZW01:BRZ-723)														*/
/*	 Add PHPC,ESPC,PLPC														*/
/*	Rev.(ZV01:BRZ-911)														*/
/*	 Add ETLS,ETRS.															*/
/*	Rev.(ZV01:BRZ-912)														*/
/*	 Add ETLC.																*/
/*	Rev.(AA04:BRZ-1189)														*/
/*	 Add PDAC.																*/
/*	Rev.(AA21:BRZ-1430)														*/
/*	 add SSRS,SSLS,SSOS														*/
/*	Rev.(AA28:BRZ-1471)														*/
/*	 add ERLS,ERRS,EDLS,EDRS												*/
/*	Rev.(AA54:BRZ-1557)														*/
/*	 add CS1E,CS2E,CS3E,CS4E												*/
/*--------------------------------------------------------------------------*/
void	OnPTHC( void );
void	OffPTHC( void );
void	OnPOLC( void );
void	OffPOLC( void );
void	OnPDPC( void );
void	OffPDPC( void );
void	OnPTPC( void );
void	OffPTPC( void );
void	OnPRPC( void );
void	OffPRPC( void );
void	OnPBPC( void );
void	OffPBPC( void );
void	OnPCEC( void );
void	OffPCEC( void );
void	OnECHC( void );
void	OffECHC( void );
void	OnECCC( void );
void	OffECCC( void );
void	OnECPC( void );
void	OffECPC( void );
void	OnERUC( void );
void	OffERUC( void );
void	OnERRC( void );
void	OffERRC( void );
void	OnERLC( void );
void	OffERLC( void );
void	OnPHPC( void );
void	OffPHPC( void );
void	OnEEUC( void );
void	OffEEUC( void );
void	OnEELC( void );
void	OffEELC( void );
void	OnEERC( void );
void	OffEERC( void );
void	OnESPC( void );
void	OffESPC( void );
void	OnETLC( void );
void	OffETLC( void );
void	OnPLPC( void );
void	OffPLPC( void );
void	OnSPUC( void );
void	OffSPUC( void );
void	OnSPPC( void );
void	OffSPPC( void );
void	OnSPBC( void );
void	OffSPBC( void );
void	OnSSUC( void );
void	OffSSUC( void );
void	OnSSLC( void );
void	OffSSLC( void );
void	OnSSEC( void );
void	OffSSEC( void );
void	OnPDAC( void );
void	OffPDAC( void );
void	OnSFIC( void );
void	OffSFIC( void );
void	OnSFOC( void );
void	OffSFOC( void );
void	OnSPCC( void );
void	OffSPCC( void );
void	OnSFPC( void );
void	OffSFPC( void );
void	OnSCDC( void );
void	OffSCDC( void );
void	OnSHDC( void );
void	OffSHDC( void );
void	OnSBLC( void );
void	OffSBLC( void );
void	OnUULC( void );
void	OffUULC( void );
void	OnURLC( void );
void	OffURLC( void );
void	OnUCFC( void );
void	OffUCFC( void );
void	OnUFFC( void );
void	OffUFFC( void );
void	OnURFC( void );
void	OffURFC( void );
void	OnULPC( void );
void	OffULPC( void );
void	OnUGLC( void );
void	OffUGLC( void );
void	OnPS1S( void );
void	OffPS1S( void );
void	OnPS2S( void );
void	OffPS2S( void );
void	OnPS3S( void );
void	OffPS3S( void );
void	OnPS4S( void );
void	OffPS4S( void );
void	OnPTCS( void );
void	OffPTCS( void );
void	OnPASS( void );
void	OffPASS( void );
void	OnPDSS( void );
void	OffPDSS( void );
void	OnETRS( void );
void	OffETRS( void );
void	OnEELS( void );
void	OffEELS( void );
void	OnEERS( void );
void	OffEERS( void );
void	OnEECS( void );
void	OffEECS( void );
void	OnETLS( void );
void	OffETLS( void );
void	OnSW1( void );
void	OffSW1( void );
void	OnSW2( void );
void	OffSW2( void );
void	OnSW3( void );
void	OffSW3( void );
void	OnLOCK( void );
void	OffLOCK( void );
void	OnFLT( void );
void	OffFLT( void );
void	OnBLLC( void );
void	OffBLLC( void );
void	OnILOF( void );
void	OffILOF( void );
void	OnSHCC( void );
void	OffSHCC( void );
void	OnSHOC( void );
void	OffSHOC( void );
void	OnD10C( void );
void	OffD10C( void );
void	OnD11C( void );
void	OffD11C( void );
void	OnD12C( void );
void	OffD12C( void );
void	OnD13C( void );
void	OffD13C( void );
void	OnC1SET( void );
void	OffC1SET( void );
void	OnD20C( void );
void	OffD20C( void );
void	OnD21C( void );
void	OffD21C( void );
void	OnD22C( void );
void	OffD22C( void );
void	OnD23C( void );
void	OffD23C( void );
void	OnC2SET( void );
void	OffC2SET( void );
void	OnD30C( void );
void	OffD30C( void );
void	OnD31C( void );
void	OffD31C( void );
void	OnD32C( void );
void	OffD32C( void );
void	OnD33C( void );
void	OffD33C( void );
void	OnC3SET( void );
void	OffC3SET( void );
void	OnD40C( void );
void	OffD40C( void );
void	OnD41C( void );
void	OffD41C( void );
void	OnD42C( void );
void	OffD42C( void );
void	OnD43C( void );
void	OffD43C( void );
void	OnC4SET( void );
void	OffC4SET( void );
void	OnCF1C( void );
void	OffCF1C( void );
void	OnNF1C( void );
void	OffNF1C( void );
void	OnNE1C( void );
void	OffNE1C( void );
void	OnCT1S( void );
void	OffCT1S( void );
void	OnC1NR( void );
void	OffC1NR( void );
void	OnCS1E( void );
void	OffCS1E( void );
void	OnCE1C( void );
void	OffCE1C( void );
void	OnCP1C( void );
void	OffCP1C( void );
void	OnCS1C( void );
void	OffCS1C( void );
void	OnCD1C( void );
void	OffCD1C( void );
void	OnCO1C( void );
void	OffCO1C( void );
void	OnCC1C( void );
void	OffCC1C( void );
void	OnCV1C( void );
void	OffCV1C( void );
void	OnCF2C( void );
void	OffCF2C( void );
void	OnNF2C( void );
void	OffNF2C( void );
void	OnNE2C( void );
void	OffNE2C( void );
void	OnCT2S( void );
void	OffCT2S( void );
void	OnC2NR( void );
void	OffC2NR( void );
void	OnCS2E( void );
void	OffCS2E( void );
void	OnCE2C( void );
void	OffCE2C( void );
void	OnCP2C( void );
void	OffCP2C( void );
void	OnCS2C( void );
void	OffCS2C( void );
void	OnCD2C( void );
void	OffCD2C( void );
void	OnCO2C( void );
void	OffCO2C( void );
void	OnCC2C( void );
void	OffCC2C( void );
void	OnCV2C( void );
void	OffCV2C( void );
void	OnCF3C( void );
void	OffCF3C( void );
void	OnNF3C( void );
void	OffNF3C( void );
void	OnNE3C( void );
void	OffNE3C( void );
void	OnCT3S( void );
void	OffCT3S( void );
void	OnC3NR( void );
void	OffC3NR( void );
void	OnCS3E( void );
void	OffCS3E( void );
void	OnCE3C( void );
void	OffCE3C( void );
void	OnCP3C( void );
void	OffCP3C( void );
void	OnCS3C( void );
void	OffCS3C( void );
void	OnCD3C( void );
void	OffCD3C( void );
void	OnCO3C( void );
void	OffCO3C( void );
void	OnCC3C( void );
void	OffCC3C( void );
void	OnCV3C( void );
void	OffCV3C( void );
void	OnCF4C( void );
void	OffCF4C( void );
void	OnNF4C( void );
void	OffNF4C( void );
void	OnNE4C( void );
void	OffNE4C( void );
void	OnCT4S( void );
void	OffCT4S( void );
void	OnC4NR( void );
void	OffC4NR( void );
void	OnCS4E( void );
void	OffCS4E( void );
void	OnCE4C( void );
void	OffCE4C( void );
void	OnCP4C( void );
void	OffCP4C( void );
void	OnCS4C( void );
void	OffCS4C( void );
void	OnCD4C( void );
void	OffCD4C( void );
void	OnCO4C( void );
void	OffCO4C( void );
void	OnCC4C( void );
void	OffCC4C( void );
void	OnCV4C( void );
void	OffCV4C( void );
void	OnUGAS( void );
void	OffUGAS( void );
void	OnUGDS( void );
void	OffUGDS( void );
void	OnURHS( void );
void	OffURHS( void );
void	OnUFHS( void );
void	OffUFHS( void );
void	OnUECS( void );
void	OffUECS( void );
void	OnUEFS( void );
void	OffUEFS( void );
void	OnUERS( void );
void	OffUERS( void );
void	OnSSRS( void );
void	OffSSRS( void );
void	OnSSLS( void );
void	OffSSLS( void );
void	OnSSOS( void );
void	OffSSOS( void );
void	OnSSxS( void );
void	OffSSxS( void );
void	OnSDIS( void );
void	OffSDIS( void );
void	OnSDOS( void );
void	OffSDOS( void );
void	OnERLS( void );
void	OffERLS( void );
void	OnERRS( void );
void	OffERRS( void );
void	OnERxS( void );
void	OffERxS( void );
void	OnEDLS( void );
void	OffEDLS( void );
void	OnEDRS( void );
void	OffEDRS( void );
void	OnEDxS( void );
void	OffEDxS( void );
void	OnLT3S( void );
void	OffLT3S( void );
void	OnLFHS( void );
void	OffLFHS( void );
void	OnCx1S( void );
void	OffCx1S( void );
void	OnCx2S( void );
void	OffCx2S( void );
void	OnCx3S( void );
void	OffCx3S( void );
void	OnCx4S( void );
void	OffCx4S( void );
/*--------------------------------------------------------------------------*/
/*	BV Sensor																*/
/*	Rev.(ZV05:BRZ-979)	add argument										*/
/*--------------------------------------------------------------------------*/
void	OnBVIN( ULONG );
void	OffBVIN( ULONG );
void	OnBVOUT( ULONG );
void	OffBVOUT( ULONG );
/*--------------------------------------------------------------------------*/
/*	skew on																	*/
/*--------------------------------------------------------------------------*/
void	OnSkewSSxS( UCHAR );
void	OnSkewCx1S( UCHAR );
void	OnSkewCx2S( UCHAR );
void	OnSkewCx3S( UCHAR );
void	OnSkewCx4S( UCHAR );
/*--------------------------------------------------------------------------*/
/*	time up function for ras												*/
/*--------------------------------------------------------------------------*/
int		IntTimeUpSW1( void );
int		IntTimeUpSW2( void );
int		IntTimeUpSW3( void );
int		IntTimeUpKeepSW1( void );
int		IntTimeUpKeepSW2( void );
int		IntTimeUpRaskeyPlural( void );
/*--------------------------------------------------------------------------*/
/*	Rev.(ZY06:BRZ-684)														*/
/*	time up function for Dispense Enable Switch								*/
/*--------------------------------------------------------------------------*/
int		IntTimeUpDispenseEnableSwitch( void );
/*--------------------------------------------------------------------------*/
/*	time up function for io													*/
/*	Rev.(ZZ03:BRZ-100)														*/
/*	Rev.(ZY01:BRZ-413)	Add time up function.(IntTimeUpIoChangeMedia())		*/
/*	Rev.(ZY04:BRZ-572)	Add time up function.(IntTimeUpIoInvalidOperation())*/
/*	Rev.(ZV05:BRZ-961)	Add time up function.(IntTimeUpIoAddDischarge())	*/
/*	Rev.(ZV05:BRZ-962)	Add time up function.(IntTimeUpIoMoreDischarge())	*/
/*--------------------------------------------------------------------------*/
int		IntTimeUpIoComplete( void );
int		IntTimeUpIoCancel( void );
int		IntTimeUpIoChangeMedia( void );
int		IntTimeUpIoInvalidOperation( void );
int		IntTimeUpIoAddDischarge( void );
int		IntTimeUpIoMoreDischarge( void );
/*--------------------------------------------------------------------------*/
/*																			*/
/*	API function prototypes													*/
/*																			*/
/*	Rev.(ZZ06:BRZ-316)														*/
/*	add draw number-of-sheets Increment / get function.						*/
/*	Rev.(ZY03:BRZ-513)	add Check stay bill									*/
/*	Rev.(ZY05:BRZ-604)	add IntHomeDeskew()									*/
/*	Rev.(ZV02:BRZ-917)	add IntReFeedRequest()								*/
/*	Rev.(AA09:BRZ-1284)	add IntPrintTransportControlTable()					*/
/*	Rev.(AA10:BRZ-1303)	add IntPrintFeedPassPhaseCounter()					*/
/*	Rev.(AA14:BRZ-1362)	add IntAdjustDeSkewHome()							*/
/*	Rev.(AA17:BRZ-1388)	add IntCheckDeSkew()								*/
/*	Rev.(AA20:BRZ-1428)	add IntClearDataForCompress()						*/
/*	Rev.(AA25:BRZ-1461)	add argument in IntPrintTransportControlTable()		*/
/*--------------------------------------------------------------------------*/
void	IntOn ( void );
void	IntOff( void );
void	IntInitialize( MOVE_REQUEST *inst );
void	IntPrepare( MOVE_REQUEST *inst );
void	IntDrawStart( MECHA_PLACE from );
void	IntEnd( INT_END_FACTOR factor );
void	IntIncDrawRequest( void );
short	IntGetDrawRequest( void );
void	IntInitSpot( void );
void	IntSetSpot( INT_END_FACTOR ief, MECHA_PLACE mecha );
MECHA_PLACE		IntGetSpot( INT_END_FACTOR ief );
void	IntStartCheckStay( void );
void	IntHomeDeskew( void );
void	IntAdjustDeSkewHome( void );
BOOL	IntCheckDeSkew( void );
void	IntReFeedRequest( void );
void	IntClearDataForCompress( MECHA_PLACE );
void	IntPrintTransportControlTable( BOOL );
void	IntPrintFeedPassPhaseCounter( MECHA_PLACE );
	/*----------------------------------------------------------------------*/
	/*	Rev.(ZZ03:BRZ-117)													*/
	/*	transport interrupt debug mode										*/
	/*----------------------------------------------------------------------*/
BOOL	IntCheckDebugMode( void );
void	IntDebugModeOn( INT_END_FACTOR ief );
void	IntDebugModeOff( void );
