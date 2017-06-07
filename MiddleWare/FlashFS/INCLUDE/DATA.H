/***

	*************************************************************************
	*																		*
	*		header file for data											*
	*																		*
	*														DATA.H			*
	*************************************************************************
	ALL RIGHTS RESERVED, COPYRIGHT(C) FUJITSU FRONTECH LIMITED. 2002-2007

	SN			Date		Name		Revision.No.	Contents
	-------------------------------------------------------------------------
	001-ZZ01	2002/11/07	M.Kamimura	<BRZ-001>		The First Version
				2002/11/28	M.Kibe
				2002/12/02	M.Kibe
				2002/12/18	Y.Saito
				2003/01/13	M.Kibe
				2003/01/21  M.Banba						Add packet
														-for transportation processing data
														-for discrimination data
				2003/02/04  M.Banba						Add packet
														:pktSDIS,pktUFHS
				2003/02/13	M.Kibe						Add present condition number of sheets
														:wNumberPresentBill
				2003/03/04	A.Maruyama					Add processing flags
														:bProcessingCommand
														:bProcessingRas
	002-ZZ02	2003/03/31	M.Banba						Add Data module function
														-DataIncNumberJam()
														-DataDecNumberJam()
														-DataGetNumberJam()
				2003/04/02	M.Banba						Add wStateProcessing
														Delete bProcessingRas
														Delete bProcessingCommand
				2003/04/16	A.Kojima	<BRZ-019>		Delete bSnsAdjustingFlag
	003-ZZ03	2003/04/22	A.Kojima	<BRZ-021>		Change sensor flag for new upper(A3 Mech.)
				2003/04/23	M.Banba		<BRZ-021>		Change sensor flag for new upper(A3 Mech.)
	004-ZZ04	2003/05/22	M.Banba		<BRZ-142>		add pktDrasReq,pktDrasResp
				2003/05/26	M.Kamimura	<BRZ-128>		Change packet of Command task
				2003/06/04	M.Kibe		<BRZ-149>		add informational model definition
				2003/06/25	M.Banba		<BRZ-183>		add DATA_DEBUG_MODE
	005-ZZ05	2003/07/04	M.Kamimura	<BRZ-193>		add Unit information update function
														:DataxxxOperationMode()
														:DataxxxNumberDenomination()
														:DataxxxCodeDenomination()
														:DataxxxBitDenominationCa()
				2003/07/07	M.Banba		<BRZ-205>		add BV-API packet
				2003/07/11	M.Kamimura	<BRZ-193>		Change function type.(ONOFF->BOOL)
														:DataSetDenominationCa()
														:DataGetDenominationCa()
														:DataClearDenominationCa()
														:DataClearAllDenominationCa()
	006-ZZ06	2003/07/29	M.Kamimura	<BRZ-193>		rename function.
														:DataCheckDenominationCa()
				2003/08/01	M.Kamimura	<BRZ-285>		add Unit information update function
														:DataSetNumberDenominationCa()
														:DataGetNumberDenominationCa()
														:DataxxxCompletionSetup()
														:DataxxxMaxNumberNotRecognized()
														:DataxxxMaxNumberDifferent()
				2003/08/07	A.Kojima	<BRZ-295>		change for A4 Pre-Acceptor
														:bSnsPTPC,bSnsPBPC,bSnsPDSS
	007-ZZ07	2003/09/02	M.Banba		<BRZ-341>		add packet
														:pktJobReq
														:pktJobResp
							M.Kibe		<BRZ-344>		add Upper part medium remains information update function
														:DataSetUpperBillRemainInfo()
														:DataClearUpperBillRemainInfo()
														:DataGetUpperBillRemainInfo()
														:DataInitUpperBillRemainInfo()
										<BRZ-349>		sensor level set correspondence addition
														:DataInitSeneorLevelInfo()
														:DataSetSensorLevelInfo()
														:DataClearSensorLevelInfo()
														:DataGetSensorLevelInfo()
				2003/09/04	M.Banba		<BRZ-344>		add remains information update function
														:DataSetRemainInfo();
														:DataClearRemainInfo();
														:DataGetRemainInfo();
										<BRZ-349>		add sensor level set request control function				
														DataInitRemainInfo();
														DataSetLevelSetRequest();
														DataClearLevelSetRequest();
														DataGetLevelSetRequest();
				2003/09/20	A.Maruyama	<BRZ-386>		function relevant to re-download was added
														:DataDivideProgram()
														:DataClearDownloadStatus()
														:DataGetDownloadStatus()
														:DataSetDownloadStatus()
	008-ZY01	2003/10/02	A.Kojima	<BRZ-406>		change for B'-model
							M.Banba		<BRZ-408>		Escrow receipt control change
														:pktLenEDxS
				2003/10/09	M.Banba		<BRZ-418>		Forcing demand correspondence by receipt number of sheets
				2003/10/14	Y.Saito		<BRZ-421>		add pktRfnc
				2003/10/21	A.Kojima	<BRZ-429>		Delete bSaveWLENCS
							M.Banba		<BRZ-432>		Renewal correspondence of unit set information
				2003/10/27	M.Kamimura	<BRZ-434>		add function of get denomination table address.
														:DataGetTblDenomination()
	009-ZY02	2003/11/08	M.Kibe		<BRZ-452>		Mechanism error code set function addition
														:DataGetErrorInformationMecha()
														:DataCheckErrorMecha()
														:DataSetErrorCodeMecha()
														:DataMoveErrorCodeMecha()
														:DataCancelErrorCodeMecha()
				2003/11/12	M.Kamimura	<BRZ-461>		Delete function.
														:DataxxxNumberDenominationCa()
														Add API function.(Cassette denomination type)
														:DataxxxDenominationTypeCa()
														:DataCheckDenomiCodeCa()
														Add 3rd argument.(Cassette denomination type)
														:DataCheckDenominationCa()
										<BRZ-471>		Add Data API function.
														:DataSetNumberDenominationBv()
														:DataGetNumberDenominationBv()
														:DataSetCodeDenominationBv()
														:DataClearCodeDenominationBv()
				2003/11/25	M.Kamimura	<BRZ-503>		Add function of decrement positive value.
														:DataDecNumberPresentPositive()
	010-ZY03	2003/12/05	M.Banba		<BRZ-528>		It is the addition of the renewal function
														of information at the time of a breakaway.	
	011-ZY04	2003/12/15	Y.Saito		<BRZ-531>		Add response to setting CP for RAS.
														:DataRasGetDenominationTypeCa()
														:DataRasGetDenominationCa()
	012-ZY05	2004/01/08	A.Kojima	<BRZ-619>		Add ILOF
														:bSnsILOF
										<BRZ-620>		Add bSaveWSINTEN
				2004/01/14	A.Maruyama	<BRZ-641>		add function of sensor level save/get
														:DataSaveSensorLevel()
														:DataGetSensorLevel()
	013-ZY06	2004/01/20	Y.Saito		<BRZ-665>		Add statistics information definition
	014-ZY06	2004/01/20	Y.Saito		<BRZ-669>		Change format.
				2004/01/20	M.Kibe		<BRZ-671>		Add function(statistics information clear)
														:DataClearStatisticsInformation()
				2004/01/20	M.Kibe		<BRZ-677>		Add function(sensor level set part is set)
														:DataSetPartLevelSetRequest()
				2004/01/24	A.Kojima	<BRZ-681>		add pktBVIN
							A.Maruyama	<BRZ-682>		add function
														:DataSetMaintenanceRequest()
				2004/01/25	M.Banba		<BRZ-684>		Dispense Enable Switch correspondence
				2004/01/26	A.Maruyama	<BRZ-669>		add function of Clear Encryption(session) Key
														:DataClearEncryptionKey()
	015-ZW01	2004/01/31	A.Maruyama	<BRZ-702>		delete code for A-model
				2004/02/02	A.Maruyama	<BRZ-704>		add function of add/edit information for J1
														:DataAddInformationError()
														:DataEditInformationError()
														:wDataSttErrorCodeLogCounter
				2004/02/03	A.Maruyama	<BRZ-710>		Statistics information delete
														(move to "L_DATA.H")
														add function of update statistics information
				2004/02/07	A.Kojima	<BRZ-723>		add sensor of B2-model
														:bSnsPHPC,bSnsESPC,bSnsPLPC
	016-ZW03	2004/02/24	Y.Saito		<BRZ-761>		add function of statistics information reading.
														:DataGetStatisticsInformation()
														:DataGetSizeStatisticsInfo()
				2004/02/27	A.Maruyama	<BRZ-759>		add function for cassette near end
														:DataCheckStatusMedia()
	017-ZW04	2004/03/08	M.Kamimura	<BRZ-811>		add sensor of BV.
														:bSnsBVIN
														:bSnsBVOUT
				2004/03/18	M.Kamimura	<BRZ-841>		add function of read request setup.
														:DataxxxReadRequest()
														:DataxxxReadLogRequest
				2004/03/29	A.Maruyama	<BRZ-884>		add function
														:DataRestoreErrorInformation()
				2004/03/31	A.Maruyama	<BRZ-893>		add PKT for TaskResp
														:pktRespReq
	018-ZW06	2004/04/05	M.Kamimura	<BRZ-899>		add function of shutter close emergency.
														:DataxxxCloseEmergency()
	019-ZV01	2004/04/09	M.Kamimura	<BRZ-911>		add sensor of ETRS.(for B3-model)
														:bSnsETLS,bSnsETRS,bSnsETxS
										<BRZ-912>		add sensor of ETLC.(for B3-model)
														:bSnsETLC()
	020-ZV05	2004/04/26	M.Kamimura	<BRZ-961>		add bSnsPSxS.
														:bSnsPSxS
				2004/04/30	A.Kojima	<BRZ-979>		add pktxxxxt,pktSDISs
	021-ZT02	2004/06/14	A.Maruyama	<BRZ-1119>		add functions
														:DataRefreshTimeLevelSetRequest()
														:DataTimeUpLevelSetRequest()
	022-ZT10	2004/07/13	M.Kamimura	<BRZ-1156>		add function.
														:DataGetCodeNumberDenomiSelect()
				2004/07/14	M.Kamimura	<BRZ-1159>		add function.
														:DataxxxThicknessMode
	023-ZT12	2004/07/21	M.Kamimura	<BRZ-1174>		add function.
														:DataMoveErrorCodeMechaForce()
	024-AA04	2004/08/05	A.Kojima	<BRZ-1189>		add PDAC sensor
														:bSnsPDAC add
				2004/08/19	M.Kibe		<BRZ-1213>		add function
														:DataClearLevelSetTemporarilyRequest()
														:DataGetLevelSetTemporarilyRequest()
														add Argument
														:DataSetLevelSetRequest()
	025-AA05	2004/08/25	Y.Saito		<BRZ-1219>		add argument.
														:DataAddErrorCode()
				2004/09/02	M.Kamimura	<BRZ-1229>		add flag of sensor fix state.
														:bSnsFixPSxS, bSnsFixPTCS
	026-AA09	2004/10/01	M.Kamimura	<BRZ-1280>		add bSnsPacFront.
														:bSnsPacFront
	027-AA12	2004/10/21	Y.Saito		<BRZ-1315>		add function definition.
														:bDataDispCmdTime
														:DataSetCmdTimeDisplay()
							A.Maruyama	<BRZ-1324>		add flag of sensor fix state.
														:bSnsFixBLLC
				2004/10/22	M.Banba		<BRZ-1321>		add function
														:DataGetSkewClass()
	028-AA14	2004/11/20	A.Maruyama	<BRZ-1357>		add flag of sensor fix state.
														:bSnsFixPASS,bSnsFixPDSS,
														 bSnsFixEECS,bSnsFixEERS,bSnsFixEELS
	029-AA16	2004/12/08	Y.Saito		<BRZ-1368>		Add processing of BV alarm information setup. (For analysis log)
														:DataSetBvAlarmLog()
														:DataClearBvAlarmLog()
	030-AA21	2005/06/09	A.Maruyama	<BRZ-1431>		Add functions for Unit Serial Number
														 :DataRegisterSerialNumber()
														 :DataSetSerialNumber()
				2005/06/14	A.Kojima	<BRZ-1430>		add SSRS,SSLS,SSOS sensor
														:bSnsSSRS,bSnsSSLS,bSnsSSOS
	031-AA25	2005/12/05	M.Kamimura	<BRZ-1461>		Polymer note measures
														- Add function of note type setup / notice.
														:DataSetNoteType()
														:DataxxxPolymerNote
	032-AA27	2006/01/19	M.Kamimura	<BRZ-1464>		The condition to assume Reject area to be a full state is changed.
														:DataSetFullStatusReject()
	033-AA28	2006/03/03	A.Kojima	<BRZ-1471>		add ERLS,ERRS,EDLS,EDRS sensor state flag
														:bSnsERLS,bSnsERRS,bSnsEDLS,bSnsEDRS
	034-AA30	2006/04/18	M.Kamimura	<BRZ-1480>		The condition to assume Captured area / Counterfeit area to be a
														full state is changed.
														:DataSetFullStatusCaptured()
														:DataSetFullStatusCounterfeit()
	035-AA40	2007/01/16	M.Kibe		<BRZ-1511>		Making to option for Reservoir stage diving crowding.
														:DataSetReservoirControl()
														:DataGetReservoirControl()
														:DataClearReservoirControl()
	036-AA41	2007/01/23	M.Kibe		<BRZ-1512>		for cassette storage capacity improvement FW.
														add function
														:DataSetCompulsoryStoringCassette()
														:DataGetCompulsoryStoringCassette()
														:DataSetCompulsoryStoringCassetteStatus()
														:DataGetCompulsoryStoringCassetteStatus()
														:DataClearCompulsoryStoringCassetteStatusAll()
														:DataSetCompulsoryStoringJamStatus()
														:DataGetCompulsoryStoringJamStatus()
				2007/01/24	A.Maruyama	<BRZ-1514>		Add functions for ECB6-Certification-Mode
														:DataSetCertificationModeECB6()
														:DataGetCertificationModeECB6()
				2007/01/31	M.Kibe		<BRZ-1512>		for cassette storage capacity improvement FW.
														del function
														:DataSetCompulsoryStoringJamStatus()
														:DataGetCompulsoryStoringJamStatus()
														add function
														:DataCheckCompulsoryStoringJamCassette()
														:DataGetCompulsoryStoringJamError()
				2007/02/02	M.Kibe		<BRZ-1512>		for cassette storage capacity improvement FW.
														add function
														:DataCancelCompulsoryStoringCassetteStatus()
				2007/02/05	M.Kibe		<BRZ-1512>		for cassette storage capacity improvement FW.
														-Review result reflection
														-del function
														:DataClearCompulsoryStoringCassetteStatusAll()
														:DataGetCompulsoryStoringJamError()
				2007/02/07	M.Kibe		<BRZ-1512>		for cassette storage capacity improvement FW.
														-Review result reflection
														-add function
														:DataClearCompulsoryStoringCassetteStatus()
	037-AA48	2007/06/07	A.Kojima	<BRZ-1530>		improve the data transfer speed
														-change for D-Level frame size change
														:DataSetLineFrameMode(),DataGetLineFrameMode() add
				2006/07/03	M.Kibe		<BRZ-1540>		add flag of sensor fix state.
														:bSnsFixPSxS
	038-AA54	2008/01/24	A.Kojima	<BRZ-1557>		add flag of sensor
														:bSnsCS1E,bSnsCS2E,bSnsCS3E,bSnsCS4E
COMMENT END
***/
/****************************************************************************/
/*																			*/
/*	defines																	*/
/*																			*/
/****************************************************************************/
/****************************************************************************/
/*																			*/
/*	variables																*/
/*																			*/
/****************************************************************************/
/*--------------------------------------------------------------------------*/
/*	packet																	*/
/*--------------------------------------------------------------------------*/
	/*----------------------------------------------------------------------*/
	/*	for the communication between tasks									*/
	/*	Rev.(ZZ04:BRZ-142)	add pktDrasReq,pktDrasResp						*/
	/*	Rev.(ZZ04:BRZ-128)	delete pktCmdResp,								*/
	/*						change name( pktCmdReq -> pktCmd )				*/
	/*	Rev.(ZZ05:BRZ-205)	add pktBvApi									*/
	/*	Rev.(ZZ07:BRZ-341)	add pktJobReq,pktJobResp						*/
	/*	Rev.(ZY01:BRZ-421)	add pktRfnc										*/
	/*	Rev.(ZW04:BRZ-893)	add pktRespReq									*/
	/*----------------------------------------------------------------------*/
extern	PKT		*pktSys;
extern	PKT		*pktCmd;
extern	PKT		*pktResp;
extern	PKT		*pktRespReq;
extern	PKT		*pktLine;
extern	PKT		*pktBv;
extern	PKT		*pktLan;
extern	PKT		*pktMoveReq;
extern	PKT		*pktMoveResp;
extern	PKT		*pktIo;
extern	PKT		*pktMechaCtrl;
extern	PKT		*pktCaCtrlReq;
extern	PKT		*pktCaCtrlResp;
extern	PKT		*pktCa1;
extern	PKT		*pktCa2;
extern	PKT		*pktCa3;
extern	PKT		*pktCa4;
extern	PKT		*pktUpperCtrlReq;
extern	PKT		*pktUpperCtrlResp;
extern	PKT		*pktPac;
extern	PKT		*pktEsc;
extern	PKT		*pktSep;
extern	PKT		*pktSht;
extern	PKT		*pktRas;
extern	PKT		*pktWatch;
extern	PKT		*pktDrasReq;
extern	PKT		*pktDrasResp;
extern	PKT		*pktBvApi;
extern	PKT		*pktJobReq;
extern	PKT		*pktJobResp;
extern	PKT		*pktRfnc;
	/*----------------------------------------------------------------------*/
	/*	for transportation processing data									*/
	/*	Rev.(ZZ03:BRZ-021)	for A3 Mecha	(UTGS->UGAS)(UTFS->UGDS)		*/
	/*	Rev.(ZY01:BRZ-408) 	for B model										*/
	/*	Rev.(ZY06:BRZ-681)	add BVIN										*/
	/*	Rev.(ZV05:BRZ-979)	add pktxxxxt,pktSDISs							*/
	/*----------------------------------------------------------------------*/
extern	PKT		*pktUGAS;			/* trigger for UA-UD Gate	*/
extern	PKT		*pktUGDS;			/* trigger for UE    Gate	*/
extern	PKT		*pktURHS;			/* trigger for L1/L2-Gate	*/
extern	PKT		*pktUFHS;			/* Detect Remained Notes at Front-Hole	*/
extern	PKT		*pktSDIS;			/* Detect Deskew-in Position			*/
extern	PKT		*pktLT3S;			/* trigger for L3/L4-Gate	*/
extern	PKT		*pktERxS;			/* Reservoir	*/
extern	PKT		*pktEDxS;			/* Escrow		*/
extern	PKT		*pktCx1S;			/* cassette 1 	*/
extern	PKT		*pktCx2S;			/* cassette 2 	*/
extern	PKT		*pktCx3S;			/* cassette 3 	*/
extern	PKT		*pktCx4S;			/* cassette 4 	*/
extern	PKT		*pktUEFS;			/* forgary area	*/
extern	PKT		*pktUERS;			/* reject  area	*/
extern	PKT		*pktUECS;			/* capture area	*/
extern	PKT		*pktBVIN;			/* BV			*/
extern	PKT		*pktUGASt;
extern	PKT		*pktUGDSt;
extern	PKT		*pktURHSt;
extern	PKT		*pktUFHSt;
extern	PKT		*pktSDISt;
extern	PKT		*pktLT3St;
extern	PKT		*pktERxSt;
extern	PKT		*pktEDxSt;
extern	PKT		*pktCx1St;
extern	PKT		*pktCx2St;
extern	PKT		*pktCx3St;
extern	PKT		*pktCx4St;
extern	PKT		*pktUEFSt;
extern	PKT		*pktUERSt;
extern	PKT		*pktUECSt;
extern	PKT		*pktBVINt;
extern	PKT		*pktSDISs;
extern	PKT		*pktLenEDxS;
	/*----------------------------------------------------------------------*/
	/*	for discrimination data 											*/
	/*----------------------------------------------------------------------*/
extern	PKT		*pktVd;
/*--------------------------------------------------------------------------*/
/*	packet id address														*/
/*--------------------------------------------------------------------------*/
extern	PKT		**PktIdAddress[];
/*--------------------------------------------------------------------------*/
/*	sensor state flag														*/
/*	Rev.(ZZ06:BRZ-295)														*/
/*	 Change PLPC->PTPC,PPRC->PBPC											*/
/*	 Add PDSS																*/
/*	Rev.(ZY01:BRZ-406)														*/
/*	 Delete SWLC,SWRC and add SFIC,SFOC,SHDC,SBLC,UGLC,LFHS					*/
/*	Rev.(ZY05:BRZ-619)														*/
/*	 Add ILOF																*/
/*	Rev.(ZW01:BRZ-723)														*/
/*	 Add PHPC,ESPC,PLPC														*/
/*	Rev.(ZW04:BRZ-811)														*/
/*	 Add BVIN,BVOUT															*/
/*	Rev.(ZV01:BRZ-911)														*/
/*	 Add ETLS,ETRS,ETxS.													*/
/*	Rev.(ZV01:BRZ-912)														*/
/*	 Add ETLC.																*/
/*	Rev.(ZV05:BRZ-961)														*/
/*	 Add PSxS.																*/
/*	Rev.(AA04:BRZ-1189)														*/
/*	 add PDAC																*/
/*	Rev.(AA09:BRZ-1280)														*/
/*	 Add bSnsPacFront														*/
/*	Rev.(AA21:BRZ-1430)														*/
/*	 add SSRS,SSLS,SSOS														*/
/*	Rev.(AA28:BRZ-1471)														*/
/*	 add ERLS,ERRS,EDLS,EDRS												*/
/*	Rev.(AA54:BRZ-1557)														*/
/*	 add CS1E,CS2E,CS3E,CS4E												*/
/*--------------------------------------------------------------------------*/
extern	ONOFF	bSnsPTHC;
extern	ONOFF	bSnsPOLC;
extern	ONOFF	bSnsPDPC;
extern	ONOFF	bSnsPTPC;
extern	ONOFF	bSnsPRPC;
extern	ONOFF	bSnsPBPC;
extern	ONOFF	bSnsPCEC;
extern	ONOFF	bSnsECHC;
extern	ONOFF	bSnsECCC;
extern	ONOFF	bSnsECPC;
extern	ONOFF	bSnsERUC;
extern	ONOFF	bSnsERRC;
extern	ONOFF	bSnsERLC;
extern	ONOFF	bSnsPHPC;
extern	ONOFF	bSnsEEUC;
extern	ONOFF	bSnsEELC;
extern	ONOFF	bSnsEERC;
extern	ONOFF	bSnsESPC;
extern	ONOFF	bSnsETLC;
extern	ONOFF	bSnsPLPC;
extern	ONOFF	bSnsSPUC;
extern	ONOFF	bSnsSPPC;
extern	ONOFF	bSnsSPBC;
extern	ONOFF	bSnsSSUC;
extern	ONOFF	bSnsSSLC;
extern	ONOFF	bSnsSSEC;
extern	ONOFF	bSnsPDAC;
extern	ONOFF	bSnsSFIC;
extern	ONOFF	bSnsSFOC;
extern	ONOFF	bSnsSPCC;
extern	ONOFF	bSnsSFPC;
extern	ONOFF	bSnsSCDC;
extern	ONOFF	bSnsSHDC;
extern	ONOFF	bSnsSBLC;
extern	ONOFF	bSnsUULC;
extern	ONOFF	bSnsURLC;
extern	ONOFF	bSnsUCFC;
extern	ONOFF	bSnsUFFC;
extern	ONOFF	bSnsURFC;
extern	ONOFF	bSnsULPC;
extern	ONOFF	bSnsUGLC;
extern	ONOFF	bSnsPS1S;
extern	ONOFF	bSnsPS2S;
extern	ONOFF	bSnsPS3S;
extern	ONOFF	bSnsPS4S;
extern	ONOFF	bSnsPTCS;
extern	ONOFF	bSnsPASS;
extern	ONOFF	bSnsPDSS;
extern	ONOFF	bSnsETRS;
extern	ONOFF	bSnsEELS;
extern	ONOFF	bSnsEERS;
extern	ONOFF	bSnsEECS;
extern	ONOFF	bSnsETLS;
extern	ONOFF	bSnsSW1;
extern	ONOFF	bSnsSW2;
extern	ONOFF	bSnsSW3;
extern	ONOFF	bSnsLOCK;
extern	ONOFF	bSnsFLT;
extern	ONOFF	bSnsBLLC;
extern	ONOFF	bSnsILOF;
extern	ONOFF	bSnsSHCC;
extern	ONOFF	bSnsSHOC;
extern	ONOFF	bSnsD10C;
extern	ONOFF	bSnsD11C;
extern	ONOFF	bSnsD12C;
extern	ONOFF	bSnsD13C;
extern	ONOFF	bSnsC1SET;
extern	ONOFF	bSnsD20C;
extern	ONOFF	bSnsD21C;
extern	ONOFF	bSnsD22C;
extern	ONOFF	bSnsD23C;
extern	ONOFF	bSnsC2SET;
extern	ONOFF	bSnsD30C;
extern	ONOFF	bSnsD31C;
extern	ONOFF	bSnsD32C;
extern	ONOFF	bSnsD33C;
extern	ONOFF	bSnsC3SET;
extern	ONOFF	bSnsD40C;
extern	ONOFF	bSnsD41C;
extern	ONOFF	bSnsD42C;
extern	ONOFF	bSnsD43C;
extern	ONOFF	bSnsC4SET;
extern	ONOFF	bSnsCF1C;
extern	ONOFF	bSnsNF1C;
extern	ONOFF	bSnsNE1C;
extern	ONOFF	bSnsCT1S;
extern	ONOFF	bSnsC1NR;
extern	ONOFF	bSnsCS1E;
extern	ONOFF	bSnsCE1C;
extern	ONOFF	bSnsCP1C;
extern	ONOFF	bSnsCS1C;
extern	ONOFF	bSnsCD1C;
extern	ONOFF	bSnsCO1C;
extern	ONOFF	bSnsCC1C;
extern	ONOFF	bSnsCV1C;
extern	ONOFF	bSnsCF2C;
extern	ONOFF	bSnsNF2C;
extern	ONOFF	bSnsNE2C;
extern	ONOFF	bSnsCT2S;
extern	ONOFF	bSnsC2NR;
extern	ONOFF	bSnsCS2E;
extern	ONOFF	bSnsCE2C;
extern	ONOFF	bSnsCP2C;
extern	ONOFF	bSnsCS2C;
extern	ONOFF	bSnsCD2C;
extern	ONOFF	bSnsCO2C;
extern	ONOFF	bSnsCC2C;
extern	ONOFF	bSnsCV2C;
extern	ONOFF	bSnsCF3C;
extern	ONOFF	bSnsNF3C;
extern	ONOFF	bSnsNE3C;
extern	ONOFF	bSnsCT3S;
extern	ONOFF	bSnsC3NR;
extern	ONOFF	bSnsCS3E;
extern	ONOFF	bSnsCE3C;
extern	ONOFF	bSnsCP3C;
extern	ONOFF	bSnsCS3C;
extern	ONOFF	bSnsCD3C;
extern	ONOFF	bSnsCO3C;
extern	ONOFF	bSnsCC3C;
extern	ONOFF	bSnsCV3C;
extern	ONOFF	bSnsCF4C;
extern	ONOFF	bSnsNF4C;
extern	ONOFF	bSnsNE4C;
extern	ONOFF	bSnsCT4S;
extern	ONOFF	bSnsC4NR;
extern	ONOFF	bSnsCS4E;
extern	ONOFF	bSnsCE4C;
extern	ONOFF	bSnsCP4C;
extern	ONOFF	bSnsCS4C;
extern	ONOFF	bSnsCD4C;
extern	ONOFF	bSnsCO4C;
extern	ONOFF	bSnsCC4C;
extern	ONOFF	bSnsCV4C;
extern	ONOFF	bSnsUGAS;
extern	ONOFF	bSnsUGDS;
extern	ONOFF	bSnsURHS;
extern	ONOFF	bSnsUFHS;
extern	ONOFF	bSnsUECS;
extern	ONOFF	bSnsUEFS;
extern	ONOFF	bSnsUERS;
extern	ONOFF	bSnsSSRS;
extern	ONOFF	bSnsSSLS;
extern	ONOFF	bSnsSSOS;
extern	ONOFF	bSnsSSxS;
extern	ONOFF	bSnsSDIS;
extern	ONOFF	bSnsSDOS;
extern	ONOFF	bSnsERLS;
extern	ONOFF	bSnsERRS;
extern	ONOFF	bSnsERxS;
extern	ONOFF	bSnsEDLS;
extern	ONOFF	bSnsEDRS;
extern	ONOFF	bSnsEDxS;
extern	ONOFF	bSnsLT3S;
extern	ONOFF	bSnsLFHS;
extern	ONOFF	bSnsCx1S;
extern	ONOFF	bSnsCx2S;
extern	ONOFF	bSnsCx3S;
extern	ONOFF	bSnsCx4S;
extern	ONOFF	bSnsBVIN;
extern	ONOFF	bSnsBVOUT;
extern	ONOFF	bSnsETxS;
extern	ONOFF	bSnsPSxS;
extern	ONOFF	bSnsPacFront;
/*--------------------------------------------------------------------------*/
/*	Sensor fix state flag	(After piece-of-paper time up)					*/
/*	Rev.(AA05:BRZ-1229)	Add fix state flag.	(PS1S->PS4S,PTCS)				*/
/*	Rev.(AA12:BRZ-1324)	Add fix state flag.	(BLLC)							*/
/*	Rev.(AA14:BRZ-1357)	Add fix state flag.	(PASS,PDSS,EERS,EELS,EECS)		*/
/*	Rev.(AA48:BRZ-1540)	Add fix state flag.	(PSxS)							*/
/*--------------------------------------------------------------------------*/
extern	ONOFF	bSnsFixPS1S;
extern	ONOFF	bSnsFixPS2S;
extern	ONOFF	bSnsFixPS3S;
extern	ONOFF	bSnsFixPS4S;
extern	ONOFF	bSnsFixPTCS;
extern	ONOFF	bSnsFixPSxS;

extern	ONOFF	bSnsFixPASS;
extern	ONOFF	bSnsFixPDSS;
extern	ONOFF	bSnsFixEERS;
extern	ONOFF	bSnsFixEELS;
extern	ONOFF	bSnsFixEECS;

extern	ONOFF	bSnsFixBLLC;

/*--------------------------------------------------------------------------*/
/*	saved data of port														*/
/*	Rev.(ZY01:BRZ-429)														*/
/*	 Delete WLENCS															*/
/*	Rev.(ZY05:BRZ-620)														*/
/*	 Add WSINTEN															*/
/*--------------------------------------------------------------------------*/
extern	UCHAR	bSaveWUCLR;
extern	UCHAR	bSaveWLCLR;
extern	UCHAR	bSaveWSINTEN;
/*--------------------------------------------------------------------------*/
/*	Rev.(AA12:BRZ-1315)	Definition addition.								*/
/*--------------------------------------------------------------------------*/
extern	ONOFF	bDataDispCmdTime;
/*--------------------------------------------------------------------------*/
/*	Rev.(ZY06:BRZ-669)														*/
/*--------------------------------------------------------------------------*/
typedef struct
{
	UCHAR	bDataEncryptKey1[8];
	UCHAR	bDataEncryptKey2[8];
}DATA_ENCRYPT_KEY;
/****************************************************************************/
/*																			*/
/*	function prototypes							 							*/
/*																			*/
/****************************************************************************/
	/*----------------------------------------------------------------------*/
	/*	error information													*/
	/*	Rev.(ZY02:BRZ-452)													*/
	/*	 add DataGetErrorInformationMecha / DataSetErrorCodeMecha /			*/
	/*		 DataCancelErrorCodeMecha / DataCheckErrorMecha /				*/
	/*		 DataMoveErrorMecha												*/
	/*	Rev.(ZW04:BRZ-884)													*/
	/*	 add DataRestoreErrorInformation()									*/
	/*	Rev.(ZT12:BRZ-1174)	add fucntion of mecha error move force.			*/
	/*	Rev.(AA05:BRZ-1219)	add argument to DataAddErrorCode().				*/
	/*----------------------------------------------------------------------*/
ERROR_INFORMATION*	DataGetErrorInformation( void );
ERROR_INFORMATION*	DataGetErrorInformationMecha( PLACE_NO place );
void	DataRestoreErrorInformation( ERROR_INFORMATION* pSrc );
void	DataSetErrorCode( ERROR_CODE code );
void	DataSetErrorCodeMecha( ERROR_CODE code , PLACE_NO place );
void	DataAddErrorCode( UCHAR detail, ERROR_CODE code );
void	DataCancelErrorCode( ERR_LEVEL lvl );
void	DataCancelErrorCodeMecha( ERR_LEVEL lvl, PLACE_NO place );
ERR_TBL	*DataSearchErrTable( ERROR_CODE code );
BOOL	DataCheckError( void );
BOOL	DataCheckErrorMecha( PLACE_NO place );
BOOL	DataMoveErrorMecha( PLACE_NO place );
void	DataMoveErrorCodeMecha( PLACE_NO place );
void	DataMoveErrorCodeMechaForce( PLACE_NO place );
	/*----------------------------------------------------------------------*/
	/*	Set Status Information												*/
	/*----------------------------------------------------------------------*/
void	DataResetStatusSet( void );
BOOL	DataGetStatusSet( UCHAR bSetNo );
	/*----------------------------------------------------------------------*/
	/*	Rev.(ZY01:BRZ-432) Renewal correspondence of unit set information	*/
	/*	Unit Set Information												*/
	/*----------------------------------------------------------------------*/
void			DataSetUnitSet( EXT_MECHA_PLACE mecha );
void			DataClearUnitSet( EXT_MECHA_PLACE mecha );
EXT_MECHA_PLACE	DataGetUnitSet( void );
BOOL			DataCheckUnitSet( EXT_MECHA_PLACE mecha );
	/*----------------------------------------------------------------------*/
	/*	present condition number of sheets									*/
	/*	Rev.(ZY02:BRZ-503) Add function of decrement positive value.		*/
	/*----------------------------------------------------------------------*/
void	DataIncNumberPresent( PLACE_NO no );
void	DataDecNumberPresent( PLACE_NO no );
void	DataDecNumberPresentPositive( PLACE_NO no );
short	DataGetNumberPresent( PLACE_NO no );
void	DataSetNumberPresent( PLACE_NO no, short cnt );
void	DataAddNumberPresent( PLACE_NO no, short cnt );
void	DataMovNumberPresent( PLACE_NO dest, PLACE_NO src );
void	DataClearNumberPresent( PLACE_NO no );
	/*----------------------------------------------------------------------*/
	/*	number of jam														*/
	/*----------------------------------------------------------------------*/
void	DataIncNumberJam( USHORT jam_place );
void	DataDecNumberJam( USHORT jam_place );
short	DataGetNumberJam( USHORT jam_place );
void	DataInitNumberJam( void );
	/*----------------------------------------------------------------------*/
	/*	number of in														*/
	/*----------------------------------------------------------------------*/
void	DataIncNumberIn( PLACE_NO no );
short	DataGetNumberIn( PLACE_NO no );
void	DataInitNumberIn( void );
	/*----------------------------------------------------------------------*/
	/*	unit process														*/
	/*----------------------------------------------------------------------*/
BOOL			DataStartProcess( STATE_PROCESS process );
void			DataEndProcess( STATE_PROCESS process );
STATE_PROCESS	DataGetProcess( void );
	/*----------------------------------------------------------------------*/
	/*	empty full information												*/
	/*	Rev.(ZW03:BRZ-759)	add DataCheckStatusMedia()						*/
	/*----------------------------------------------------------------------*/
UCHAR	DataGetStatusMedia( PLACE_NO place );
BOOL	DataCheckStatusMedia( PLACE_NO place, UCHAR kind );
void	DataSetStatusMedia( PLACE_NO place, UCHAR kind );
void	DataClearStatusMedia( PLACE_NO place, UCHAR kind );
	/*----------------------------------------------------------------------*/
	/*	Rev.(AA27:BRZ-1464)	Add function of Reject full updating.			*/
	/*	Rev.(AA30:BRZ-1480)	Add function of Captured / Counterfeit area.	*/
	/*----------------------------------------------------------------------*/
BOOL	DataSetFullStatusReject( void );
BOOL	DataSetFullStatusCaptured( void );
BOOL	DataSetFullStatusCounterfeit( void );
	/*----------------------------------------------------------------------*/
	/*	debug mode															*/
	/*----------------------------------------------------------------------*/
void	DataInitializeDebugMode( void );
void	DataSetDebugMode( PLACE_NO place, DATA_DEBUG_MODE mode );
DATA_DEBUG_MODE	DataGetDebugMode( PLACE_NO place );
	/*----------------------------------------------------------------------*/
	/*	Completion setup status												*/
	/*	Rev.(ZZ06:BRZ-285)													*/
	/*----------------------------------------------------------------------*/
void				DataSetCompletionSetup( DATA_STATE_SETUP info );
DATA_STATE_SETUP	DataGetCompletionSetup( void );
void				DataCancelCompletionSetup( DATA_STATE_SETUP info );
	/*----------------------------------------------------------------------*/
	/*	Maximum number of not recognized / different notes					*/
	/*	Rev.(ZZ06:BRZ-285)													*/
	/*----------------------------------------------------------------------*/
void	DataSetMaxNumberNotRecognized( UCHAR number );
UCHAR	DataGetMaxNumberNotRecognized( void );
void	DataSetMaxNumberDifferent( UCHAR number );
UCHAR	DataGetMaxNumberDifferent( void );
	/*----------------------------------------------------------------------*/
	/*	operation mode														*/
	/*	Rev.(ZZ05:BRZ-193)													*/
	/*----------------------------------------------------------------------*/
void			DataSetOperationMode( OPERATION_MODE mode );
OPERATION_MODE	DataGetOperationMode( void );
void			DataCancelOperationMode( OPERATION_MODE mode );
void			DataClearOperationMode( void );
	/*----------------------------------------------------------------------*/
	/*	Thickness mode														*/
	/*	Rev.(ZT10:BRZ-1159)	Add function.									*/
	/*----------------------------------------------------------------------*/
void			DataSetThicknessMode( UCHAR mode );
UCHAR			DataGetThicknessMode( void );
void			DataClearThicknessMode( void );
	/*----------------------------------------------------------------------*/
	/*	for ECB6 Certification mode											*/
	/*	Rev.(AA41:BRZ-1514)													*/
	/*----------------------------------------------------------------------*/
void	DataSetCertificationModeECB6( BOOL mode );
BOOL	DataGetCertificationModeECB6( void );
	/*----------------------------------------------------------------------*/
	/*	Rev.(AA48:BRZ-1530)		add											*/
	/*	for Line frame mode													*/
	/*----------------------------------------------------------------------*/
void	DataSetLineFrameMode( UCHAR mode );
UCHAR	DataGetLineFrameMode( void );
	/*----------------------------------------------------------------------*/
	/*	Reservoir Control													*/
	/*	Rev.(AA40:BRZ-1511)	Add function.									*/
	/*----------------------------------------------------------------------*/
void					DataSetReservoirControl( DATA_RSV_CTRL_SETUP mode );
DATA_RSV_CTRL_SETUP		DataGetReservoirControl( void );
void					DataClearReservoirControl( void );
	/*----------------------------------------------------------------------*/
	/*	Minimum dimensiton for compulsory storing note in cassette			*/
	/*	Rev.(AA41:BRZ-1512)	Add function.(set/get)							*/
	/*----------------------------------------------------------------------*/
void		DataSetCompulsoryStoringCassette(UCHAR move , PLACE_NO ca);
ULONG		DataGetCompulsoryStoringCassette( PLACE_NO ca );

	/*----------------------------------------------------------------------*/
	/*	compulsory storing cassette status									*/
	/*	Rev.(AA41:BRZ-1512)	Add function.(set/get/cancel/clear)				*/
	/*----------------------------------------------------------------------*/
void		DataSetCompulsoryStoringCassetteStatus( UCHAR mode , PLACE_NO ca );
UCHAR		DataGetCompulsoryStoringCassetteStatus( PLACE_NO ca );
void		DataCancelCompulsoryStoringCassetteStatus( void );
void		DataClearCompulsoryStoringCassetteStatus( PLACE_NO ca );
	/*----------------------------------------------------------------------*/
	/*	compulsory storing jam cassette check								*/
	/*	Rev.(AA41:BRZ-1512)	Add function.(check)							*/
	/*----------------------------------------------------------------------*/
BOOL		DataCheckCompulsoryStoringJamCassette( void );
	/*----------------------------------------------------------------------*/
	/*	number of handling denomination										*/
	/*	Rev.(ZZ05:BRZ-193)													*/
	/*	Rev.(ZY02:BRZ-471)													*/
	/*----------------------------------------------------------------------*/
void			DataSetNumberDenomination( UCHAR number );
UCHAR			DataGetNumberDenomination( void );
void			DataSetNumberDenominationBv( UCHAR number );
UCHAR			DataGetNumberDenominationBv( void );
	/*----------------------------------------------------------------------*/
	/*	handling denomination code											*/
	/*	Rev.(ZZ05:BRZ-193)													*/
	/*	Rev.(ZY01:BRZ-434)	Add function of get table address.				*/
	/*	Rev.(ZY02:BRZ-471)													*/
	/*	Rev.(ZT10:BRZ-1156)	Add function of code number. (Selection formula)*/
	/*----------------------------------------------------------------------*/
void			DataSetCodeDenomination( UCHAR num, ULONG code );
ULONG			DataGetCodeDenomination( UCHAR num );
void			DataClearCodeDenomination( void );
UCHAR			DataGetCodeNumberDenomination( ULONG code );
UCHAR			DataGetCodeNumberDenomiSelect( ULONG code, ULONG *tbl );

UCHAR			*DataGetTblDenomination( void );
void			DataSetCodeDenominationBv( UCHAR num, ULONG code );
void			DataClearCodeDenominationBv( void );
	/*----------------------------------------------------------------------*/
	/*	Cassette denomination type											*/
	/*	Rev.(ZY02:BRZ-461)													*/
	/*----------------------------------------------------------------------*/
void			DataSetDenominationTypeCa( PLACE_NO place, UCHAR type );
UCHAR			DataGetDenominationTypeCa( PLACE_NO place );
	/*----------------------------------------------------------------------*/
	/*	denomination bit of cassette										*/
	/*	Rev.(ZZ05:BRZ-193)													*/
	/*	Rev.(ZZ06:BRZ-193)	rename DataGetxxx -> DataCheckxxx				*/
	/*	Rev.(ZY02:BRZ-461)	Add DataCheckDenomiCodeCa().					*/
	/*----------------------------------------------------------------------*/
void			DataSetDenominationCa( PLACE_NO place, UCHAR num );
BOOL			DataCheckDenominationCa( PLACE_NO place, UCHAR num, UCHAR type );
void			DataClearDenominationCa( PLACE_NO place );
void			DataClearAllDenominationCa( void );
BOOL			DataCheckDenomiCodeCa( PLACE_NO place, ULONG code );
	/*----------------------------------------------------------------------*/
	/*	Upper part medium remains information								*/
	/*	Rev.(ZZ07:BRZ-344)													*/
	/*----------------------------------------------------------------------*/
void			DataSetRemainInfo( EXT_MECHA_PLACE e_mecha );
void			DataClearRemainInfo( EXT_MECHA_PLACE e_mecha );
BOOL			DataCheckRemainInfo( EXT_MECHA_PLACE e_mecha );
EXT_MECHA_PLACE	DataGetRemainInfo( void  );
	/*----------------------------------------------------------------------*/
	/*	Sensor level set information										*/
	/*	Rev.(ZZ07:BRZ-349)													*/
	/*	Rev.(ZY06:BRZ-677)													*/
	/*	add DataSetPartLevelSetRequest()									*/
	/*	Rev.(ZT02:BRZ-1119)													*/
	/*	add DataRefreshTimeLevelSetRequest()/DataTimeUpLevelSetRequest()	*/
	/*	Rev.(AA04:BRZ-1213)													*/
	/*	add DataClearLevelSetTemporarilyRequest()							*/
	/*	add DataGetLevelSetTemporarilyRequest()								*/
	/*	add Argument(DataSetLevelSetRequest())								*/
	/*----------------------------------------------------------------------*/
void			DataInitRemainInfo( void );
void			DataSetLevelSetRequest( BOOL sw );
void			DataSetPartLevelSetRequest( EXT_MECHA_PLACE e_mecha );
void			DataClearLevelSetRequest( EXT_MECHA_PLACE e_mecha );
EXT_MECHA_PLACE	DataGetLevelSetRequest( void  );
void			DataRefreshTimeLevelSetRequest( void );
int				DataTimeUpLevelSetRequest( void );
void			DataClearLevelSetTemporarilyRequest( EXT_MECHA_PLACE e_mecha );
EXT_MECHA_PLACE	DataGetLevelSetTemporarilyRequest( void  );
	/*----------------------------------------------------------------------*/
	/*	function relevant to re-download									*/
	/*	Rev.(ZZ07:BRZ-386)	add these functions								*/
	/*----------------------------------------------------------------------*/
USHORT			DataDivideProgram( UCHAR *pbBuf );
void			DataClearDownloadStatus( void );
USHORT			DataGetDownloadStatus( void );
BOOL			DataSetDownloadStatus( USHORT sStatus );
	/*----------------------------------------------------------------------*/
	/*	Rev.(ZY03:BRZ-528)													*/
	/*----------------------------------------------------------------------*/
void	DataOnStorageInformation( PLACE_NO no );
void	DataOffStorageInformation( PLACE_NO no );
	/*----------------------------------------------------------------------*/
	/*	FP/CP for RAS setting function 										*/
	/*	Rev.(ZY04:BRZ-531)													*/
	/*----------------------------------------------------------------------*/
BOOL			DataRasCheckDenominationCa( PLACE_NO place, UCHAR num, UCHAR type );
UCHAR			DataGetHardDenomination( PLACE_NO place );
BOOL			DataSetFixedParameterUse( BOOL val );
BOOL			DataGetFixedParameterUse( void );
BOOL			DataSetAvailableBv( void );

	/*----------------------------------------------------------------------*/
	/*	Sensor level data save / get										*/
	/*	Rev.(ZY05:BRZ-641)	add												*/
	/*----------------------------------------------------------------------*/
void	DataSaveSensorLevel( void );
UCHAR	DataGetSensorLevel( char cSnsName );

	/*----------------------------------------------------------------------*/
	/*	Rev.(ZY06:BRZ-669)													*/
	/*----------------------------------------------------------------------*/
void				DataSetEncryptionKey( unsigned char mode, unsigned char* key1, unsigned char* key2 );
DATA_ENCRYPT_KEY*	DataGetEncryptionKey( UCHAR mode );
void				DataClearEncryptionKey( void );

	/*----------------------------------------------------------------------*/
	/*	Shutter close emergency												*/
	/*	Rev.(ZW06:BRZ-899)													*/
	/*----------------------------------------------------------------------*/
void	DataSetCloseEmergency( BOOL sw );
BOOL	DataGetCloseEmergency( void );

	/*----------------------------------------------------------------------*/
	/*	Polymer note measures												*/
	/*	Rev.(AA25:BRZ-1461)	Add function of note type setup / notice.		*/
	/*----------------------------------------------------------------------*/
void	DataSetNoteType( void );
BOOL	DataGetPolymerNote( void );
BOOL	DataCheckPolymerNote( UCHAR num );
BOOL	DataCheckPolymerNoteCa( PLACE_NO place );

	/*----------------------------------------------------------------------*/
	/*	Read request														*/
	/*	Rev.(ZW04:BRZ-841)	Add function of read request setup.				*/
	/*----------------------------------------------------------------------*/
void	DataSetReadRequest( UCHAR num );
UCHAR	DataGetReadRequest( UCHAR num );
void	DataClearReadRequest( UCHAR num );
BOOL	DataCheckReadLogRequest( void );
void	DataClearReadLogRequest( void );

	/*----------------------------------------------------------------------*/
	/*	Rev.(ZY06:BRZ-671)													*/
	/*----------------------------------------------------------------------*/
void	DataClearStatisticsInformation( UCHAR bOrder , BOOL sw);
void	DataSetStatisticsInformation( UCHAR bOrder , UCHAR *pbSrc );
	/*----------------------------------------------------------------------*/
	/*	set Maintenance Request data										*/
	/*	Rev.(ZY06:BRZ-682)	add												*/
	/*----------------------------------------------------------------------*/
void	DataSetMaintenanceRequest( UCHAR *pbPtr );
	/*----------------------------------------------------------------------*/
	/*	Rev.(ZY06:BRZ-684)	Dispense Enable Switch correspondence			*/
	/*----------------------------------------------------------------------*/
void	DataChangeDispenseEnableSwitch( void );
BOOL	DataGetDispenseEnableSwitch( void );
	/*----------------------------------------------------------------------*/
	/*	Rev.(ZW01:BRZ-704)	add function of add/edit information for J1		*/
	/*----------------------------------------------------------------------*/
void	DataAddInformationError( USHORT wCommand, USHORT wCode );
void	DataEditInformationError( UCHAR *pbBuf );

short	DataEditStatisticsInformation( UCHAR bOrder, UCHAR *pbDst );
	/*----------------------------------------------------------------------*/
	/*	Rev.(ZW03:BRZ-761)	add function of statistics information reading.	*/
	/*----------------------------------------------------------------------*/
UCHAR*	DataGetStatisticsInformation( UCHAR bOrder );
ULONG	DataGetSizeStatisticsInfo( UCHAR bOrder );
	/*----------------------------------------------------------------------*/
	/*	Rev.(ZW01:BRZ-710)	add function of update statistics information	*/
	/*----------------------------------------------------------------------*/
		/*------------------------------------------------------------------*/
		/*	increment														*/
		/*------------------------------------------------------------------*/
void	DataIncSttTransaction( char cTrans, char cKind );
void	DataIncSttSkew( char cPlace, char cKind );
void	DataIncSttTemperature( char cRank );
void	DataIncSttMechanicalData( char cKind, char cCntr );
		/*------------------------------------------------------------------*/
		/*	set																*/
		/*------------------------------------------------------------------*/
void	DataUpdateSttSnsLevel( char cNumber, UCHAR bValue );
void	DataUpdateSttParameter( char cKind, UCHAR *pbSrc, USHORT wSize );
void	DataUpdateSttCassetteDenomi( PLACE_NO bPno, UCHAR *pbSrc, USHORT wSize );
	/*----------------------------------------------------------------------*/
	/*	Rev.(AA12:BRZ-1315)	add function of time display flag change.		*/
	/*----------------------------------------------------------------------*/
void	DataSetCmdTimeDisplay( ONOFF val );
	/*----------------------------------------------------------------------*/
	/*	Rev.(AA12:BRZ-1321)	A classification is acquired from skew counter	*/
	/*----------------------------------------------------------------------*/
USHORT	DataGetSkewClass( UCHAR skewdata );
	/*----------------------------------------------------------------------*/
	/*	Rev.(AA16:BRZ-1368)	add function for BV alarm information setup.	*/
	/*----------------------------------------------------------------------*/
void	DataSetBvAlarmLog( void );
void	DataClearBvAlarmLog( void );
	/*----------------------------------------------------------------------*/
	/*	Rev.(AA16:BRZ-1368)	add function for BV alarm information setup.	*/
	/*----------------------------------------------------------------------*/
void	DataRegisterSerialNumber( UCHAR *pbSrc );
short	DataSetSerialNumber( UCHAR *pbDst );
