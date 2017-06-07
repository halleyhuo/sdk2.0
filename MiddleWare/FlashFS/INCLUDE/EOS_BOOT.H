/*	$inc		*/
/*	$each		*/
/*	$<	
	**************************************************************************	
	*	
	*	ＥＯＳ＿ＢＯＯＴプログラム公開ヘッダファイル
	*	
	*	EOS_BOOT.HD
	*	
	**************************************************************************	
	All	Rights Reserved, Copyright (C) FUJITSU LIMITED. 1997-98.
	版数	日付 担当 改版内容
	--------------------------------------------------------------------------	
	ZZ01	97/03/18 中野 コーディング開始
	YY08	98/05/15 根岸 ファイル処理種別用の定義を追加
	YY09	98/06/01 広木 １０Ｂａｓｅ－Ｔ用コーディング開始
	PM03	98/10/30 広木 フラッシュサイズ情報追加
	AA02	1999/07/16 根岸 セクタの書き換え回数通知処理追加
	$>	*/
/*	$<	
	**************************************************************************	
	*	機種情報
	**************************************************************************	
	$>	*/
	#define	PORT_IO_PCDR	(0x05FFFFD0)
extern	int	nMachineType;
	#define	MT_CIP	0
	#define	MT_BRU	1
/*	$<	
	**************************************************************************	
	*	フラッシュサイズ情報 ●PM03
	**************************************************************************	
	$>	*/
extern	int	nFlashType;
	#define	FT_1_0M	0
	#define	FT_1_5M	1
	#define	FT_2_0M	2
/*	$<	
	**************************************************************************	
	*	BASIC IO SYSTEM
	*	<bios.c>
	**************************************************************************	
	$>	*/
	#define	FILE_CREATE	1
	#define	FILE_OPEN	2
	#define	FILE_CLOSE	3
	#define	FILE_READ	4
	#define	FILE_WRITE	5
	#define	FILE_REMOVE	6
	#define	FILE_RENAME	7
	#define	FILE_LSEEK	8
	#define	FILE_GETATTR	9
	#define	FILE_SETATTR	10
	#define	FILE_NAMESET	11
	#define	FILE_PAGESET	12
	#define	GET_PROG_VER	13
	#define	SCI_READ	20
	#define	SCI_WRITE	21
	#define	__A_RDONLY	0x01
	#define	__A_HIDDEN	0x02
	#define	__A_SYSTEM	0x04
	#define	__A_VOLID	0x08
	#define	__A_SUBDIR	0x10
	#define	__A_ARCH	0x20
	#define	CODE_READ_ONLY	0x0
	#define	CODE_WRITE_ONLY	0x1
	#define	CODE_READ_WRITE	0x2
/*	$<	
	**************************************************************************	
	*	FILE SYSTEM
	*	<flash.c>
	**************************************************************************	
	$function	void dbg_directory_data(void)
	$function	void dbg_fat_data(void)
	$>	*/
/*	$inc		*/
