/***

	*************************************************************************
	*																		*
	*		header file for des module										*
	*																		*
	*														DES.H			*
	*************************************************************************
	ALL RIGHTS RESERVED, COPYRIGHT(C) FUJITSU FRONTECH LIMITED. 2004

	SN			Date		Name		Revision.No.	Contents
	-------------------------------------------------------------------------
	001-ZY06	2004/01/20	Y.Saito		<BRZ-669>		The First Version
	002-ZV04	2004/04/21	A.Maruyama	<BRZ-951>		add function
														:DesInitialize()
COMMENT END
***/
/****************************************************************************/
/*																			*/
/*	defines																	*/
/*																			*/
/****************************************************************************/
	/*----------------------------------------------------------------------*/
	/*	Rev.(ZZ04:BRZ-137)	add	DES_ENC/DES_DEC								*/
	/*----------------------------------------------------------------------*/
#define		DES_ENC			0
#define		DES_DEC			1

#define		DES_MAX_SIZE_KEY	8

enum
{
	DES_MODE_NOT_ENCRYPT	=	0,
	DES_MODE_FIXED_KEY		=	1,
	DES_MODE_GET_KEY		=	2
};
/****************************************************************************/
/*																			*/
/*	function prototypes														*/
/*																			*/
/****************************************************************************/
short			Des3Encryption(	unsigned char*	srcp,	short	len,
								unsigned char*	destp,	char	flag,	unsigned char mode );

void	DesInitialize( void );				/*			Rev.(ZV04:BRZ-951>	*/
