/***

	*************************************************************************
	*																		*
	*		header file for general subroutines module						*
	*																		*
	*														GSUB.H			*
	*************************************************************************
	ALL RIGHTS RESERVED, COPYRIGHT(C) FUJITSU FRONTECH LIMITED. 2002-2003

	SN			Date		Name		Revision.No.	Contents
	-------------------------------------------------------------------------
	001-ZZ01	2002/10/30	A.Maruyama	<BRZ-001>		The First Version
				2003/03/10	A.Maruyama					add prototypes for error information
				2003/03/14	A.Maruyama					move prototypes of time-up fanction from GSUB_ERR.C
	002-ZZ04	2003/06/12	A.Maruyama	<BRZ-162>		add functions of ASCII to HEX & HEX to ASCII
	003-ZZ07	2003/09/20	A.Maruyama	<BRZ-385>		add functions of ASCII(8bytes) to HEX(long)
														:GsubAsc8ToHex()
	004-ZY02	2003/11/14	Y.Saito		<BRZ-472>		add functions of ASCII(2bytes) to BCD(char)
														:GsubAscToBCD()
	005-AA48	2007/06/07	A.Kojima	<BRZ-1530>		improve the data transfer speed
														-change the method of sum calculation
														:GsubCalcSum() add
COMMENT END
***/

/****************************************************************************/
/*																			*/
/*	function prototypes														*/
/*																			*/
/****************************************************************************/
/*--------------------------------------------------------------------------*/
/*	interrupt mask routines													*/
/*--------------------------------------------------------------------------*/
//MASK_LEVEL	mask_set		( MASK_LEVEL mask );
//MASK_LEVEL	mask_set_upper	( MASK_LEVEL mask );
//MASK_LEVEL	mask_level_get	( void );

/*--------------------------------------------------------------------------*/
/*	buffer (memory) manipulation routines									*/
/*--------------------------------------------------------------------------*/
UCHAR	*memcpy	( UCHAR *dst,	UCHAR *src,		ULONG len );
int		memcmp	( UCHAR *buf1,	UCHAR *buf2,	ULONG len );
void	memclr	( UCHAR *dst,					ULONG len );
UCHAR	*memset	( UCHAR *dst,	UCHAR value,	ULONG len );

BOOL	GsubAsc2ToHex( UCHAR  *pbSrc, UCHAR  *pbDst );
BOOL	GsubAsc4ToHex( UCHAR  *pbSrc, USHORT *pwDst );
void	GsubAsc8ToHex( UCHAR  *pbSrc, ULONG  *pnDst );
void	GsubHexToAsc2( UCHAR  bData,  UCHAR  *pbDst );
void	GsubHexToAsc4( USHORT wData,  UCHAR  *pbDst );
void	GsubLongToChar4( ULONG lData, UCHAR	 *pbDst );
ULONG	GsubChar4ToLong( UCHAR *pbData );
UCHAR	GsubAscToBcd( UCHAR *pbSrc );
void	GsubDump( UCHAR *p, ULONG size );
USHORT	GsubCalcSum( UCHAR *, ULONG );							/* Rev.(AA48:BRZ-1530)	add	*/
/*--------------------------------------------------------------------------*/
/*	error informations														*/
/*--------------------------------------------------------------------------*/
//void	GsubDisplayErrorCode( void );
//void	GsubStopDisplayErrorCode( void );

//void	GsubDisplayRas( UCHAR s1, UCHAR s2, RAS_INPUT_MODE mode );
//void	GsubStopDisplayRas( void );

int		GsubTimeUpDisplayErrorCode( void );
int		GsubTimeUpDisplayRas( void );
