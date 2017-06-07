/***

	*************************************************************************
	*																		*
	*		Header of Insert and Take Out Module							*
	*																		*
	*														IO.H			*
	*************************************************************************
	ALL RIGHTS RESERVED, COPYRIGHT(C) FUJITSU FRONTECH LIMITED. 2002-2003

	SN			Date		Name		Revision.No.	Contents
	-------------------------------------------------------------------------
	001-ZZ03	2003/05/12	M.Kamimura	<BRZ-100>		The First Version
	002-ZV04	2004/04/21	M.Kamimura	<BRZ-941>		Add function of draw media check.
	003-AA05	2004/09/06	M.Kamimura	<BRZ-1229>		Delete API function.( -> static function)
														:IoCheckDrawMedia()
				2004/09/08	M.Kamimura	<BRZ-1234>		Add function of remain information mask.
														:IoxxxRemainInfoKeep()
	004-AA16	2004/12/20	M.Kamimura	<BRZ-1373>		Add function of drawing-in decision update.
														:IoClearFixInfoDraw()
														:IoSetFixInfoDraw()
														:IoGetFixInfoDraw()

COMMENT END
***/

/****************************************************************************/
/*																			*/
/*	function prototypes							 							*/
/*																			*/
/****************************************************************************/
/*--------------------------------------------------------------------------*/
/*	API function															*/
/*--------------------------------------------------------------------------*/
	/*----------------------------------------------------------------------*/
	/*	Sensor interruption surveillance function							*/
	/*	Rev.(AA05:BRZ-1229)	Add argument.	(Sensor name)					*/
	/*----------------------------------------------------------------------*/
void	IoMediaOn( USHORT sns );
void	IoMediaOff( USHORT sns );
	/*----------------------------------------------------------------------*/
	/*	Function of remains information mask.	(PAC_INSERT)				*/
	/*	Rev.(AA05:BRZ-1234)	Add function.									*/
	/*----------------------------------------------------------------------*/
void	IoSetRemainInfoKeep( BOOL sw );
BOOL	IoGetRemainInfoKeep( void );
	/*----------------------------------------------------------------------*/
	/*	The drawing-in check of a medium.									*/
	/*	Rev.(AA16:BRZ-1373)	Renewal of information of drawing-in decision.	*/
	/*----------------------------------------------------------------------*/
void	IoClearFixInfoDraw( void );
void	IoSetFixInfoDraw( void );
BOOL	IoGetFixInfoDraw( void );
