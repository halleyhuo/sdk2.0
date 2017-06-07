/***

	*************************************************************************
	*																		*
	*		header file for external interrupt request handler				*
	*																		*
	*														IRQ.H			*
	*************************************************************************
	ALL RIGHTS RESERVED, COPYRIGHT(C) FUJITSU FRONTECH LIMITED. 2002-2004

	SN			Date		Name		Revision.No.	Contents
	-------------------------------------------------------------------------
	001-ZZ01	2002/10/30	A.Maruyama	<BRZ-001>		The First Version
	002-ZW03	2004/02/18	A.Maruyama	<BRZ-753>		change/add function for IRQ-0
				2004/02/27	A.Maruyama	<BRZ-776>		change function type
														:Irq0Handler()

COMMENT END
***/

/****************************************************************************/
/*																			*/
/*	function prototypes														*/
/*																			*/
/****************************************************************************/
/*--------------------------------------------------------------------------*/
/*	external interrupt request handler										*/
/*--------------------------------------------------------------------------*/
void	IrqNMIHandler( void );
void	Irq0Entry( void );		/*	Rev.(ZW03:BRZ-753)	add						*/
ULONG	Irq0Handler( void );	/*	Rev.(ZW03:BRZ-753/776)	change function type	*/
void	Irq1Handler( void );
void	Irq2Handler( void );
void	Irq3Handler( void );

