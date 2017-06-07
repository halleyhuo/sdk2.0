/***

	*************************************************************************
	*																		*
	*		header file for task routines									*
	*																		*
	*														TASK.H			*
	*************************************************************************
	ALL RIGHTS RESERVED, COPYRIGHT(C) FUJITSU FRONTECH LIMITED. 2002-2003

	SN			Date		Name		Revision.No.	Contents
	-------------------------------------------------------------------------
	001-ZZ01	2002/11/07	M.Banba		<BRZ-001>			The First Version
	002-ZZ04	2003/05/22	M.Banba		<BRZ-142>			add TaskDras
	002-ZZ07	2003/09/02	M.Banba		<BRZ-341>			add TaskJob
	003-ZY01	2003/10/14	Y.Saito		<BRZ-421>			add TaskRfnc
COMMENT END
***/
/****************************************************************************/
/*																			*/
/*	function prototypes														*/
/*																			*/
/****************************************************************************/
/*--------------------------------------------------------------------------*/
/*																			*/
/*	declarations for prototype of task functions							*/
/*	Rev.(ZZ04:BRZ-142)	add TaskDras										*/
/*	Rev.(ZY01:BRZ-421)	add TaskRfnc										*/
/*																			*/
/*--------------------------------------------------------------------------*/
void	TaskSys				( void );
void	TaskCmd				( void );
void	TaskResp			( void );
void	TaskLine			( void );
void	TaskBv				( void );
void	TaskLan				( void );
void	TaskMove			( void );
void	TaskIo				( void );
void	TaskMecha			( void );
void	TaskCassetteControl	( void );
void	TaskCassette1		( void );
void	TaskCassette2		( void );
void	TaskCassette3		( void );
void	TaskCassette4		( void );
void	TaskUpper			( void );
void	TaskPreAcceptor		( void );
void	TaskEscrow			( void );
void	TaskSeparator		( void );
void	TaskShutter			( void );
void	TaskRas				( void );
void	TaskWatch			( void );
void	TaskPatrol			( void );
void	TaskDebug			( void );
void	TaskDras			( void );
void	TaskJob				( void );
void	TaskRfnc			( void );
