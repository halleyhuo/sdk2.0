/***

	*************************************************************************
	*																		*
	*		Header of Ras Module											*
	*																		*
	*														RAS.H			*
	*************************************************************************
	ALL RIGHTS RESERVED, COPYRIGHT(C) FUJITSU FRONTECH LIMITED. 2002-2003

	SN			Date		Name		Revision.No.	Contents
	-------------------------------------------------------------------------
	001-ZZ01	2002/10/28	M.Banba						The First Version
	002-ZW03	2004/02/19	M.Kamimura					Add API function.
														:RasxxxPassword
				2004/02/20	Y.Saito		<BRZ-756>		Move function from L_RAS.H.
														:RasSetValidationMode() 
                                                        :RasGetValidationMode()
                                                        :RasClearValidationMode()
	003-ZW04	2004/03/09	Y.Saito		<BRZ-807>		Add API function.
														:RasRewriteSnsLevel()
														:RasSetlevelChange()
	004-ZW05	2004/05/20	Y.Saito		<BRZ-1029>		Add API function.
														:RasSetStopRequest
                                                        :RasGetStopRequest
	                                                    :RasClearStopRequest
COMMENT END
***/

/****************************************************************************/
/*																			*/
/*	defines																	*/
/*																			*/
/****************************************************************************/
/****************************************************************************/
/*																			*/
/*	function prototypes							 							*/
/*																			*/
/****************************************************************************/
	/*----------------------------------------------------------------------*/
	/*	Rev.(ZW03:BRZ-755)	Add function of password setup.					*/
	/*----------------------------------------------------------------------*/
void	RasSetPassword( UCHAR kind );
BOOL	RasCheckPassword( UCHAR kind );
void	RasClearPassword( void );
	/*----------------------------------------------------------------------*/
	/*	Rev.(ZW03:BRZ-xxx)													*/
	/*----------------------------------------------------------------------*/
void	RasSetValidationMode( UCHAR mode );
BOOL	RasGetValidationMode( void );
void	RasClearValidationMode( void );
	/*----------------------------------------------------------------------*/
	/*	Rev.(ZW04:BRZ-807)	Add function of rewrite sensor level.			*/
	/*----------------------------------------------------------------------*/
void	RasRewriteSnsLevel( void );
void	RasSetlevelChange( void );
	/*----------------------------------------------------------------------*/
	/*	Rev.(ZU03:BRZ-1029)	Add function for request stop.					*/
	/*----------------------------------------------------------------------*/
void	RasSetStopRequest( void );
ONOFF	RasGetStopRequest( void );
void	RasClearStopRequest( void );
