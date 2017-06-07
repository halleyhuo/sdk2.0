/***

	*************************************************************************
	*																		*
	*		header file for real time monitor module						*
	*																		*
	*														RTMSH.H			*
	*************************************************************************
	ALL RIGHTS RESERVED, COPYRIGHT(C) FUJITSU FRONTECH LIMITED. 2002-2003

	SN			Date		Name		Revision.No.	Contents
	-------------------------------------------------------------------------
	001-ZZ01	2002/10/28	A.Maruyama	<BRZ-001>		The First Version

COMMENT END
***/

/*----------------------------------------------------------------------*/
/*	定数データ形式														*/
/*----------------------------------------------------------------------*/
#define		ERROR	(-1)
#define		EOF		(-1)
/*----------------------------------------------------------------------*/
/*	データポインタ														*/
/*----------------------------------------------------------------------*/
typedef struct {
	short		len;		/* データ長									*/
	char		*ptr;		/* データ格納ポインタ						*/
}	DATA_PTR;

/*----------------------------------------------------------------------*/
/*	ｃｈａｒ／ｓｈｏｒｔ／ｉｎｔ／ｌｏｎｇ共有体						*/
/*----------------------------------------------------------------------*/
typedef union {
	uchar	cdata[4];
	ushort	sdata[2];
	uint	idata;
	ulong	ldata;
}	DATA_UNION;

/*----------------------------------------------------------------------*/
/*	ｃｈａｒ／ｓｈｏｒｔ共有体											*/
/*----------------------------------------------------------------------*/
typedef union {
	uchar	cdata[2];
	ushort	sdata;
}	DATA_UNION_S;

/*----------------------------------------------------------------------*/
/*	ｃｈａｒ／ｓｈｏｒｔ／ｉｎｔ／ｌｏｎｇポインタ共有体				*/
/*----------------------------------------------------------------------*/
typedef union {
	char	*charptr;
	short	*shortptr;
	int		*intptr;
	long	*longptr;
	void	*voidptr;
}	DATA_UNION_PTR;

/************************************************************************/
/*	定数定義															*/
/************************************************************************/
	/*------------------------------------------------------------------*/
	/*	MASK_PTNは 割り込みマスクの値を指定								*/
	/*	STACK_SIZEは タスクを生成した際に割当られるスタックのサイズを	*/
	/*	指定															*/
	/*	STACK_RANGEは forkでタスク生成した際にコピーされるスタックの	*/
	/*	範囲を指定														*/
	/*------------------------------------------------------------------*/
#define	MASK_PTN		0x10
#define	MASK_PRIORITY	15

#define	STACK_SIZE		2048

#define	STACK_RANGE		8
#define	DESCRIPTOR_SIZE	0
#define	NUM_OF_SIG		4			/*	２の冪乗のこと	*/

/************************************************************************/
/*	データ型定義														*/
/************************************************************************/
	/*------------------------------------------------------------------*/
	/*	レジスタ退避領域												*/
	/*------------------------------------------------------------------*/
typedef struct	st_reg{
	
	long	reg_4;
	long	reg_5;
	long	reg_6;
	long	reg_7;
	long	reg_8;
	long	reg_9;
	long	reg_10;
	long	reg_11;
	long  lr_int;//return from interrupt
	
	long	reg_0;
	long	reg_1;
	long	reg_2;
	long	reg_3;
	long	reg_12;
	long	LR;
	long	pc;
	long	xPSR;
}	REG,	*PtrToREG;
	/*------------------------------------------------------------------*/
	/*	メッセージ用構造体												*/
	/*------------------------------------------------------------------*/
typedef struct	st_mes{
	struct	st_mes	*next;
	short			mes_len;
}	MES,	*PtrToMES;
	/*------------------------------------------------------------------*/
	/*	メイル用構造体													*/
	/*------------------------------------------------------------------*/
typedef struct	st_mail{
	int			semaphore;
	PtrToMES	mes_link_head;
	PtrToMES	mes_link_tail;
}	MAIL,	*PtrToMAIL;

typedef long	DesType, *PtrToDes;
	/*------------------------------------------------------------------*/
	/*	タスク制御ブロック（ＴＣＢ）									*/
	/*------------------------------------------------------------------*/
typedef	struct	st_tcb{
	struct	st_tcb	*next;
	short			priority;			
	short			wd_time_val;		
	struct	st_reg	*stack_buf;			
	long			ini_stack;			
	ulong			time_buf;
	short			semaphore;
	ushort			status;
	ushort			sig_bit;
	ushort			sig_mask;
	int				(*sig_func[NUM_OF_SIG])( void );
	struct	st_tcb/*sttcb*/	*ppid;
	PtrToMAIL		id;
	char			*parm_ad;
}	TCB,	*PtrToTCB;

	/*------------------------------------------------------------------*/	
	/*------------------------------------------------------------------*/
typedef struct {
	TCB		*tcb;					
	void	(*task)(void);
	int		prty;					
	int		time;					
}	TASK;

	
typedef	struct {
	int				fifo_id;			
	DATA_UNION_PTR	bufbase_ptr;		
	DATA_UNION_PTR	bufend_ptr;			
	DATA_UNION_PTR	cur_read_pt;		
	DATA_UNION_PTR	cur_write_pt;		
	int				size;				
	int				max;				
	int				number;				
}	FIFO,PKT;

/************************************************************************/
/************************************************************************/
	/*------------------------------------------------------------------*/
	/*	エクスターナル変数												*/
	/*------------------------------------------------------------------*/
extern	short	mem_head[ ];			
extern	short*	mem_tail;				
	/*------------------------------------------------------------------*/
	/*	グローバル変数													*/
	/*------------------------------------------------------------------*/
extern	long		rtm_time;				
extern	short		rtm_start_flag;			
extern	PtrToTCB	cur_tcb;				
extern	PtrToTCB	rtm_active_list_head;	
extern	PtrToTCB	rtm_timer_list_head;	
extern	short		rtm_wdog_out;			
extern	char		*mem_ptr;				

extern	ulong		timer_cntr;

/************************************************************************/
/************************************************************************/

void	task_change( void );
void	Exit       ( void );
void	delay      ( int  time );
#define DELAY(time)	delay((int)(time+TICK-1)/TICK)
void	create     ( TASK *tbl );
TCB		*fork      ( void );
void	wakeup     ( TCB *tcb );
void	int_wake_up( TCB *tcb );
int		suspend    ( int time );
void	kill       ( TCB *tcb,int mode);
void	(*signal   ( int mode,void (*func)(void)))(void);
void	task_level ( int prty );
int		task_check ( void );
char	*Malloc    ( int size );
void	Free       ( char *ptr );
long	itime      ( void );
int		get_des    ( void );
void	put_des    ( int ptr );
TCB		*getpid    ( void );
TCB		*getppid   ( void );
char	*getparmad ( void );
char	*putparmad ( char *ptr );
	/*------------------------------------------------------------------*/
	/*------------------------------------------------------------------*/
FIFO	*createfifo( int  vsize, int bsize);
int		setfifo    ( FIFO *fifo, int val  );
int		setfifo_irq( FIFO *fifo, int val  );
int		getfifo    ( FIFO *fifo, int *valptr ,int sw );
int		checkfifo  ( FIFO *fifo );
int		clrfifo    ( FIFO *fifo );
int		delfifo    ( FIFO *fifo );
	/*------------------------------------------------------------------*/	
	/*------------------------------------------------------------------*/
PKT	*createpkt ( int bsize );
int	setpkt     ( PKT *pkt ,char *ptr  );
int	setpkt_irq ( PKT *pkt ,char *ptr  );
int	getpkt     ( PKT *pkt ,char *ptr, int sw );
int	checkpkt   ( PKT *pkt );
int	clrpkt     ( PKT *pkt );
int	delpkt     ( PKT *pkt );
	/*------------------------------------------------------------------*/
	/*------------------------------------------------------------------*/
int		lock       ( char *ptr,int sw );
void	unlock     ( char *ptr );
	/*------------------------------------------------------------------*/
	/*------------------------------------------------------------------*/
BOOL	timer_set  ( int timer,QueueData );
BOOL	timer_reset( QueueData );
BOOL	timer_init ( void );
void	timer_irq  ( void );
	/*------------------------------------------------------------------*/
	/*------------------------------------------------------------------*/
int		rtm_init   ( PtrToREG sp );		
void	rtm_start  ( void );			
void	rtm_irq	   ( void );			
	/*------------------------------------------------------------------*/
	/*------------------------------------------------------------------*/
void	task_wait  ( void );

/*----------------------------------------------------------------------*/
	/*------------------------------------------------------------------*/
#define	SYS_CALL	0		
#define	TIME_UP_WD	1		
#define	TIME_UP		2		
#define	DEBUG_MODE	3		
	/*------------------------------------------------------------------*/
	/*------------------------------------------------------------------*/
#define	DEAD_STAT		0
#define	ACTIVE_STAT		1
#define	SUSPEND_STAT	2
#define	DELAY_STAT		3
#define	RECEIVE_STAT	4
#define	DEBUG_STAT		5
	/*------------------------------------------------------------------*/
	/*------------------------------------------------------------------*/
#define	LOWEST_LEVEL	0x7ffe
	/*------------------------------------------------------------------*/
	/*																	*/
	/*------------------------------------------------------------------*/
#define	SIG_MASK		((1 << NUM_OF_SIG) - 1)
#define	SYS_STACK_SIZE	128
#define	BREAK_PATTERN	0xa5a5

	/*------------------------------------------------------------------*/
	/*------------------------------------------------------------------*/
#define	FIFO_CTL_SIZE	sizeof(FIFO)	
#define FIFO_ID			0x4649464F		


/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
typedef struct st_tcb_ptr {
	PtrToTCB	head_ptr;
	PtrToTCB	tail_ptr;
}	TcbPtr,		*PtrToTcbPtr;

typedef struct st_mem {
	struct	st_mem	*next;
	long			length;
	PtrToTCB		req_tcb;
}	MEM,	*PtrToMEM;

struct	tcb_parm_list {
	PtrToTCB req_tcb;
	void	(*req_entry)();
	long	req_priority;
	long	req_wd_time_val;
};

struct mail_parm_list {
	PtrToMAIL	mail_adrs;
	char		*mes_adrs;
	long		mes_len;
};

/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
int	rtm		( void );
int	tchk	( void );
void		rtm_vect_set	( void );


extern	char	log_stack[0x200];	

