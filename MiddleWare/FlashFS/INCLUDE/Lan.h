/***

	*************************************************************************
	*																		*
	*		header file for LAN module										*
	*																		*
	*														Lan.h			*
	*************************************************************************
	ALL RIGHTS RESERVED, COPYRIGHT(C) FUJITSU FRONTECH LIMITED. 2002-2003

	SN			Date		Name		Revision.No.	Contents
	-------------------------------------------------------------------------
	001-ZZ06	2003/07/15	A.Kojima	<BRZ-238>		The First Version

COMMENT END
***/
/****************************************************************************/
/*																			*/
/*	function prototypes														*/
/*																			*/
/****************************************************************************/
/*--------------------------------------------------------------------------*/
/*	LAN task functions														*/
/*--------------------------------------------------------------------------*/
void	TaskLan( void );
/*--------------------------------------------------------------------------*/
/*	device driver functions													*/
/*--------------------------------------------------------------------------*/
void	LanDrvInitialize( void );
void	LanDrvInterrupt( void );
