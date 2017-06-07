

#include	<stdio.h>
#include	<string.h>
#include	<stdlib.h>
#include	<eosdef.h>
#include	<eos_boot.h>
#include	<boot_def.h>
#include	"type.h"
#include "spi_flash.h"

#include "stdint.h"
#include "file.h"

#define PAGE_OFFSET  16

#define	MAX_NAME			8
#define	MAX_EXT				3

typedef	struct	tagDIRECTORY	{
	TCHAR		szName[MAX_NAME];
	TCHAR		szExt[MAX_EXT];
	BYTE		bAttrib;
	BYTE		bReserve[10];
	WORD		wTime;
	WORD		wDate;
	WORD		wTopCluster;
	DWORD		dwSize;
}DIRECTORY, *PDIRECTORY;

	/************************************************************************/
	/************************************************************************/
#define	NUM_OF_FILE			_NFILE
#define	NUM_OF_CLUSTER		((SIZE_128K ) / SIZE_2K)


#define	FAT_FREE			0xfff
#define	FAT_FAT				0xffe
#define	FAT_EOF				0x800
#define	FAT_VOID			0


typedef	struct	tagFAT	{
	DIRECTORY	dir[ NUM_OF_FILE ];
	BYTE		bFAT[ NUM_OF_CLUSTER * 3 / 2 ];
}FAT, *PFAT;
	/************************************************************************/
	/************************************************************************/
#define	DATA_PER_CLUSTER	   2040
#define	DATA_PER_CLUSTER_3	(DATA_PER_CLUSTER * 5)
#define	DATA_PER_CLUSTER_4	(DATA_PER_CLUSTER * 10)
#define	DATA_PER_CLUSTER_5	(DATA_PER_CLUSTER * 50)
#define	DATA_PER_CLUSTER_6	(DATA_PER_CLUSTER * 100)


#define	DATA_PER_CLUSTER_2	102000

#define	CM_FREE				0xffff
#define	CM_BUSY				0x7fff
#define	CM_FAT				0x04
#define	CM_FAT_ID			0x03
#define	CM_DATA				1
#define	CM_VOID				0

typedef	struct	tagCLUSTER	{
	WORD	wClusterMark;
	WORD	wReserve;
	union	{
		BYTE	byte[DATA_PER_CLUSTER];
		FAT		fat;
	}data;
}CLUSTER, *PCLUSTER; 
	


#define	NUM_OF_PAGE			(SIZE_128K/SIZE_64K)   //32		

typedef	struct	tagPAGE	{
	DWORD		dwRewriteCounter;//record the page(sector) has been written times
	CLUSTER		cluster[SIZE_64K / sizeof(CLUSTER)];
}PAGE, *PPAGE;

	/************************************************************************/
	/************************************************************************/
typedef	struct	tagFCB	{
	BYTE			nBusyFlag;
	TCHAR		szName[MAX_NAME];
	TCHAR		szExt[MAX_EXT];
	BYTE		bAttrib;
	BYTE		nIndexOfDir;
	DWORD		dwSize;
	DWORD		dwOffset;
}FCB, *PFCB;

#define		fcb_busy_free		0
#define		fcb_busy_read		1
#define		fcb_busy_write		2


//Each SPI FLASH block 
#define FLASH_BASE        ( 0x1D0000 )//the first 1MB has been defined as code area
#define	PAGE_ADDRESS1		  ( FLASH_BASE )
#define	PAGE_ADDRESS2		  (PAGE_ADDRESS1	+ SIZE_64K)
#define	PAGE_ADDRESS3		  (PAGE_ADDRESS2	+ SIZE_64K)
#define	PAGE_ADDRESS4		  (PAGE_ADDRESS3	+ SIZE_64K)
#define	PAGE_ADDRESS5		  (PAGE_ADDRESS4	+ SIZE_64K)
#define	PAGE_ADDRESS6		  (PAGE_ADDRESS5	+ SIZE_64K)
#define	PAGE_ADDRESS7		  (PAGE_ADDRESS6	+ SIZE_64K)
#define	PAGE_ADDRESS8		  (PAGE_ADDRESS7	+ SIZE_64K)
#define	PAGE_ADDRESS9		  (PAGE_ADDRESS8	+ SIZE_64K)
#define	PAGE_ADDRESS10		(PAGE_ADDRESS9	+ SIZE_64K)
#define	PAGE_ADDRESS11		(PAGE_ADDRESS10	+ SIZE_64K)
#define	PAGE_ADDRESS12		(PAGE_ADDRESS11	+ SIZE_64K)
#define	PAGE_ADDRESS13		(PAGE_ADDRESS12	+ SIZE_64K)
#define	PAGE_ADDRESS14		(PAGE_ADDRESS13	+ SIZE_64K)
#define	PAGE_ADDRESS15		(PAGE_ADDRESS14	+ SIZE_64K)
#define	PAGE_ADDRESS16		(PAGE_ADDRESS15	+ SIZE_64K)



static	const	uint32_t/*PPAGE*/	PageAddress[ NUM_OF_PAGE ]	= {

	PAGE_ADDRESS1,	  PAGE_ADDRESS2,	  /* PAGE_ADDRESS3,	  PAGE_ADDRESS4,	//1
	PAGE_ADDRESS5,	  PAGE_ADDRESS6,	   PAGE_ADDRESS7,	  PAGE_ADDRESS8,	//2
	PAGE_ADDRESS9,	  PAGE_ADDRESS10,	   PAGE_ADDRESS11,	PAGE_ADDRESS12, //3	
	PAGE_ADDRESS13,	  PAGE_ADDRESS14,	   PAGE_ADDRESS15,	PAGE_ADDRESS16, //4	*/
};

#define	GetPageAddress(n)		( PageAddress[ n ]  )
	/************************************************************************/
	/************************************************************************/
#define	CLUSTER_PER_PAGE8K		  (SIZE_8K / sizeof(CLUSTER))
#define	CLUSTER_PER_PAGE16K		  (CLUSTER_PER_PAGE8K * 2)
#define	CLUSTER_PER_PAGE32K		  (CLUSTER_PER_PAGE8K * 4)
#define	CLUSTER_PER_PAGE64K		  (CLUSTER_PER_PAGE8K * 8)
#define CLUSTER_PER_PAGE128K    ( 16 * CLUSTER_PER_PAGE8K)

static	const	BYTE	clusterPerPage[ NUM_OF_PAGE ]	= {
	
	CLUSTER_PER_PAGE64K,	CLUSTER_PER_PAGE64K,	/*CLUSTER_PER_PAGE64K,	CLUSTER_PER_PAGE64K,	//1
	CLUSTER_PER_PAGE64K,	CLUSTER_PER_PAGE64K,	CLUSTER_PER_PAGE64K,	CLUSTER_PER_PAGE64K,	//2
	CLUSTER_PER_PAGE64K,	CLUSTER_PER_PAGE64K,	CLUSTER_PER_PAGE64K,	CLUSTER_PER_PAGE64K,	//3
	CLUSTER_PER_PAGE64K,	CLUSTER_PER_PAGE64K,	CLUSTER_PER_PAGE64K,	CLUSTER_PER_PAGE64K,	//4
	*/
};
#define	GetClusterPerPage(n)	clusterPerPage[n]

#define CLUSTER_OFFSET   sizeof(CLUSTER) 

#define PAGE_GLUSTER(nPage,nCluster)  ( nPage + 4 + CLUSTER_OFFSET * nCluster )
static	const DWORD	ClusterMap[ NUM_OF_CLUSTER ]={
//page 1
PAGE_GLUSTER(PAGE_ADDRESS1, 0 ),  PAGE_GLUSTER(PAGE_ADDRESS1, 1 ),  PAGE_GLUSTER(PAGE_ADDRESS1, 2 ),  PAGE_GLUSTER(PAGE_ADDRESS1, 3 ),	
PAGE_GLUSTER(PAGE_ADDRESS1, 4 ),  PAGE_GLUSTER(PAGE_ADDRESS1, 5 ),  PAGE_GLUSTER(PAGE_ADDRESS1, 6 ),	PAGE_GLUSTER(PAGE_ADDRESS1, 7 ),
PAGE_GLUSTER(PAGE_ADDRESS1, 8 ),  PAGE_GLUSTER(PAGE_ADDRESS1, 9 ),	PAGE_GLUSTER(PAGE_ADDRESS1, 10 ), PAGE_GLUSTER(PAGE_ADDRESS1, 11 ),
PAGE_GLUSTER(PAGE_ADDRESS1, 12 ),	PAGE_GLUSTER(PAGE_ADDRESS1, 13 ), PAGE_GLUSTER(PAGE_ADDRESS1, 14 ), PAGE_GLUSTER(PAGE_ADDRESS1, 15 ),
PAGE_GLUSTER(PAGE_ADDRESS1, 16 ),	PAGE_GLUSTER(PAGE_ADDRESS1, 17 ), PAGE_GLUSTER(PAGE_ADDRESS1, 18 ), PAGE_GLUSTER(PAGE_ADDRESS1, 19 ),
PAGE_GLUSTER(PAGE_ADDRESS1, 20 ),	PAGE_GLUSTER(PAGE_ADDRESS1, 21 ), PAGE_GLUSTER(PAGE_ADDRESS1, 22 ), PAGE_GLUSTER(PAGE_ADDRESS1, 23 ),
PAGE_GLUSTER(PAGE_ADDRESS1, 24 ),	PAGE_GLUSTER(PAGE_ADDRESS1, 25 ), PAGE_GLUSTER(PAGE_ADDRESS1, 26 ), PAGE_GLUSTER(PAGE_ADDRESS1, 27 ),
PAGE_GLUSTER(PAGE_ADDRESS1, 28 ),	PAGE_GLUSTER(PAGE_ADDRESS1, 29 ), PAGE_GLUSTER(PAGE_ADDRESS1, 30 ), PAGE_GLUSTER(PAGE_ADDRESS1, 31 ),
//page2	
PAGE_GLUSTER(PAGE_ADDRESS2, 0 ),  PAGE_GLUSTER(PAGE_ADDRESS2, 1 ),  PAGE_GLUSTER(PAGE_ADDRESS2, 2 ),  PAGE_GLUSTER(PAGE_ADDRESS2, 3 ),	
PAGE_GLUSTER(PAGE_ADDRESS2, 4 ),  PAGE_GLUSTER(PAGE_ADDRESS2, 5 ),  PAGE_GLUSTER(PAGE_ADDRESS2, 6 ),	PAGE_GLUSTER(PAGE_ADDRESS2, 7 ),
PAGE_GLUSTER(PAGE_ADDRESS2, 8 ),  PAGE_GLUSTER(PAGE_ADDRESS2, 9 ),	PAGE_GLUSTER(PAGE_ADDRESS2, 10 ), PAGE_GLUSTER(PAGE_ADDRESS2, 11 ),
PAGE_GLUSTER(PAGE_ADDRESS2, 12 ),	PAGE_GLUSTER(PAGE_ADDRESS2, 13 ), PAGE_GLUSTER(PAGE_ADDRESS2, 14 ), PAGE_GLUSTER(PAGE_ADDRESS2, 15 ),
PAGE_GLUSTER(PAGE_ADDRESS2, 16 ),	PAGE_GLUSTER(PAGE_ADDRESS2, 17 ), PAGE_GLUSTER(PAGE_ADDRESS2, 18 ), PAGE_GLUSTER(PAGE_ADDRESS2, 19 ),
PAGE_GLUSTER(PAGE_ADDRESS2, 20 ),	PAGE_GLUSTER(PAGE_ADDRESS2, 21 ), PAGE_GLUSTER(PAGE_ADDRESS2, 22 ), PAGE_GLUSTER(PAGE_ADDRESS2, 23 ),
PAGE_GLUSTER(PAGE_ADDRESS2, 24 ),	PAGE_GLUSTER(PAGE_ADDRESS2, 25 ), PAGE_GLUSTER(PAGE_ADDRESS2, 26 ), PAGE_GLUSTER(PAGE_ADDRESS2, 27 ),
PAGE_GLUSTER(PAGE_ADDRESS2, 28 ),	PAGE_GLUSTER(PAGE_ADDRESS2, 29 ), PAGE_GLUSTER(PAGE_ADDRESS2, 30 ), PAGE_GLUSTER(PAGE_ADDRESS2, 31 ),

	/*//page3	
PAGE_GLUSTER(PAGE_ADDRESS3, 0 ),  PAGE_GLUSTER(PAGE_ADDRESS3, 1 ),  PAGE_GLUSTER(PAGE_ADDRESS3, 2 ),  PAGE_GLUSTER(PAGE_ADDRESS3, 3 ),	
PAGE_GLUSTER(PAGE_ADDRESS3, 4 ),  PAGE_GLUSTER(PAGE_ADDRESS3, 5 ),  PAGE_GLUSTER(PAGE_ADDRESS3, 6 ),	PAGE_GLUSTER(PAGE_ADDRESS3, 7 ),
PAGE_GLUSTER(PAGE_ADDRESS3, 8 ),  PAGE_GLUSTER(PAGE_ADDRESS3, 9 ),	PAGE_GLUSTER(PAGE_ADDRESS3, 10 ), PAGE_GLUSTER(PAGE_ADDRESS3, 11 ),
PAGE_GLUSTER(PAGE_ADDRESS3, 12 ),	PAGE_GLUSTER(PAGE_ADDRESS3, 13 ), PAGE_GLUSTER(PAGE_ADDRESS3, 14 ), PAGE_GLUSTER(PAGE_ADDRESS3, 15 ),
PAGE_GLUSTER(PAGE_ADDRESS3, 16 ),	PAGE_GLUSTER(PAGE_ADDRESS3, 17 ), PAGE_GLUSTER(PAGE_ADDRESS3, 18 ), PAGE_GLUSTER(PAGE_ADDRESS3, 19 ),
PAGE_GLUSTER(PAGE_ADDRESS3, 20 ),	PAGE_GLUSTER(PAGE_ADDRESS3, 21 ), PAGE_GLUSTER(PAGE_ADDRESS3, 22 ), PAGE_GLUSTER(PAGE_ADDRESS3, 23 ),
PAGE_GLUSTER(PAGE_ADDRESS3, 24 ),	PAGE_GLUSTER(PAGE_ADDRESS3, 25 ), PAGE_GLUSTER(PAGE_ADDRESS3, 26 ), PAGE_GLUSTER(PAGE_ADDRESS3, 27 ),
PAGE_GLUSTER(PAGE_ADDRESS3, 28 ),	PAGE_GLUSTER(PAGE_ADDRESS3, 29 ), PAGE_GLUSTER(PAGE_ADDRESS3, 30 ), PAGE_GLUSTER(PAGE_ADDRESS3, 31 ),	
//page4
PAGE_GLUSTER(PAGE_ADDRESS4, 0 ),  PAGE_GLUSTER(PAGE_ADDRESS4, 1 ),  PAGE_GLUSTER(PAGE_ADDRESS4, 2 ),  PAGE_GLUSTER(PAGE_ADDRESS4, 3 ),	
PAGE_GLUSTER(PAGE_ADDRESS4, 4 ),  PAGE_GLUSTER(PAGE_ADDRESS4, 5 ),  PAGE_GLUSTER(PAGE_ADDRESS4, 6 ),	PAGE_GLUSTER(PAGE_ADDRESS4, 7 ),
PAGE_GLUSTER(PAGE_ADDRESS4, 8 ),  PAGE_GLUSTER(PAGE_ADDRESS4, 9 ),	PAGE_GLUSTER(PAGE_ADDRESS4, 10 ), PAGE_GLUSTER(PAGE_ADDRESS4, 11 ),
PAGE_GLUSTER(PAGE_ADDRESS4, 12 ),	PAGE_GLUSTER(PAGE_ADDRESS4, 13 ), PAGE_GLUSTER(PAGE_ADDRESS4, 14 ), PAGE_GLUSTER(PAGE_ADDRESS4, 15 ),
PAGE_GLUSTER(PAGE_ADDRESS4, 16 ),	PAGE_GLUSTER(PAGE_ADDRESS4, 17 ), PAGE_GLUSTER(PAGE_ADDRESS4, 18 ), PAGE_GLUSTER(PAGE_ADDRESS4, 19 ),
PAGE_GLUSTER(PAGE_ADDRESS4, 20 ),	PAGE_GLUSTER(PAGE_ADDRESS4, 21 ), PAGE_GLUSTER(PAGE_ADDRESS4, 22 ), PAGE_GLUSTER(PAGE_ADDRESS4, 23 ),
PAGE_GLUSTER(PAGE_ADDRESS4, 24 ),	PAGE_GLUSTER(PAGE_ADDRESS4, 25 ), PAGE_GLUSTER(PAGE_ADDRESS4, 26 ), PAGE_GLUSTER(PAGE_ADDRESS4, 27 ),
PAGE_GLUSTER(PAGE_ADDRESS4, 28 ),	PAGE_GLUSTER(PAGE_ADDRESS4, 29 ), PAGE_GLUSTER(PAGE_ADDRESS4, 30 ), PAGE_GLUSTER(PAGE_ADDRESS4, 31 ),	
//page5
PAGE_GLUSTER(PAGE_ADDRESS5, 0 ),  PAGE_GLUSTER(PAGE_ADDRESS5, 1 ),  PAGE_GLUSTER(PAGE_ADDRESS5, 2 ),  PAGE_GLUSTER(PAGE_ADDRESS5, 3 ),	
PAGE_GLUSTER(PAGE_ADDRESS5, 4 ),  PAGE_GLUSTER(PAGE_ADDRESS5, 5 ),  PAGE_GLUSTER(PAGE_ADDRESS5, 6 ),	PAGE_GLUSTER(PAGE_ADDRESS5, 7 ),
PAGE_GLUSTER(PAGE_ADDRESS5, 8 ),  PAGE_GLUSTER(PAGE_ADDRESS5, 9 ),	PAGE_GLUSTER(PAGE_ADDRESS5, 10 ), PAGE_GLUSTER(PAGE_ADDRESS5, 11 ),
PAGE_GLUSTER(PAGE_ADDRESS5, 12 ),	PAGE_GLUSTER(PAGE_ADDRESS5, 13 ), PAGE_GLUSTER(PAGE_ADDRESS5, 14 ), PAGE_GLUSTER(PAGE_ADDRESS5, 15 ),
PAGE_GLUSTER(PAGE_ADDRESS5, 16 ),	PAGE_GLUSTER(PAGE_ADDRESS5, 17 ), PAGE_GLUSTER(PAGE_ADDRESS5, 18 ), PAGE_GLUSTER(PAGE_ADDRESS5, 19 ),
PAGE_GLUSTER(PAGE_ADDRESS5, 20 ),	PAGE_GLUSTER(PAGE_ADDRESS5, 21 ), PAGE_GLUSTER(PAGE_ADDRESS5, 22 ), PAGE_GLUSTER(PAGE_ADDRESS5, 23 ),
PAGE_GLUSTER(PAGE_ADDRESS5, 24 ),	PAGE_GLUSTER(PAGE_ADDRESS5, 25 ), PAGE_GLUSTER(PAGE_ADDRESS5, 26 ), PAGE_GLUSTER(PAGE_ADDRESS5, 27 ),
PAGE_GLUSTER(PAGE_ADDRESS5, 28 ),	PAGE_GLUSTER(PAGE_ADDRESS5, 29 ), PAGE_GLUSTER(PAGE_ADDRESS5, 30 ), PAGE_GLUSTER(PAGE_ADDRESS5, 31 ),	
//page6
PAGE_GLUSTER(PAGE_ADDRESS6, 0 ),  PAGE_GLUSTER(PAGE_ADDRESS6, 1 ),  PAGE_GLUSTER(PAGE_ADDRESS6, 2 ),  PAGE_GLUSTER(PAGE_ADDRESS6, 3 ),	
PAGE_GLUSTER(PAGE_ADDRESS6, 4 ),  PAGE_GLUSTER(PAGE_ADDRESS6, 5 ),  PAGE_GLUSTER(PAGE_ADDRESS6, 6 ),	PAGE_GLUSTER(PAGE_ADDRESS6, 7 ),
PAGE_GLUSTER(PAGE_ADDRESS6, 8 ),  PAGE_GLUSTER(PAGE_ADDRESS6, 9 ),	PAGE_GLUSTER(PAGE_ADDRESS6, 10 ), PAGE_GLUSTER(PAGE_ADDRESS6, 11 ),
PAGE_GLUSTER(PAGE_ADDRESS6, 12 ),	PAGE_GLUSTER(PAGE_ADDRESS6, 13 ), PAGE_GLUSTER(PAGE_ADDRESS6, 14 ), PAGE_GLUSTER(PAGE_ADDRESS6, 15 ),
PAGE_GLUSTER(PAGE_ADDRESS6, 16 ),	PAGE_GLUSTER(PAGE_ADDRESS6, 17 ), PAGE_GLUSTER(PAGE_ADDRESS6, 18 ), PAGE_GLUSTER(PAGE_ADDRESS6, 19 ),
PAGE_GLUSTER(PAGE_ADDRESS6, 20 ),	PAGE_GLUSTER(PAGE_ADDRESS6, 21 ), PAGE_GLUSTER(PAGE_ADDRESS6, 22 ), PAGE_GLUSTER(PAGE_ADDRESS6, 23 ),
PAGE_GLUSTER(PAGE_ADDRESS6, 24 ),	PAGE_GLUSTER(PAGE_ADDRESS6, 25 ), PAGE_GLUSTER(PAGE_ADDRESS6, 26 ), PAGE_GLUSTER(PAGE_ADDRESS6, 27 ),
PAGE_GLUSTER(PAGE_ADDRESS6, 28 ),	PAGE_GLUSTER(PAGE_ADDRESS6, 29 ), PAGE_GLUSTER(PAGE_ADDRESS6, 30 ), PAGE_GLUSTER(PAGE_ADDRESS6, 31 ),	
//page7
PAGE_GLUSTER(PAGE_ADDRESS7, 0 ),  PAGE_GLUSTER(PAGE_ADDRESS7, 1 ),  PAGE_GLUSTER(PAGE_ADDRESS7, 2 ),  PAGE_GLUSTER(PAGE_ADDRESS7, 3 ),	
PAGE_GLUSTER(PAGE_ADDRESS7, 4 ),  PAGE_GLUSTER(PAGE_ADDRESS7, 5 ),  PAGE_GLUSTER(PAGE_ADDRESS7, 6 ),	PAGE_GLUSTER(PAGE_ADDRESS7, 7 ),
PAGE_GLUSTER(PAGE_ADDRESS7, 8 ),  PAGE_GLUSTER(PAGE_ADDRESS7, 9 ),	PAGE_GLUSTER(PAGE_ADDRESS7, 10 ), PAGE_GLUSTER(PAGE_ADDRESS7, 11 ),
PAGE_GLUSTER(PAGE_ADDRESS7, 12 ),	PAGE_GLUSTER(PAGE_ADDRESS7, 13 ), PAGE_GLUSTER(PAGE_ADDRESS7, 14 ), PAGE_GLUSTER(PAGE_ADDRESS7, 15 ),
PAGE_GLUSTER(PAGE_ADDRESS7, 16 ),	PAGE_GLUSTER(PAGE_ADDRESS7, 17 ), PAGE_GLUSTER(PAGE_ADDRESS7, 18 ), PAGE_GLUSTER(PAGE_ADDRESS7, 19 ),
PAGE_GLUSTER(PAGE_ADDRESS7, 20 ),	PAGE_GLUSTER(PAGE_ADDRESS7, 21 ), PAGE_GLUSTER(PAGE_ADDRESS7, 22 ), PAGE_GLUSTER(PAGE_ADDRESS7, 23 ),
PAGE_GLUSTER(PAGE_ADDRESS7, 24 ),	PAGE_GLUSTER(PAGE_ADDRESS7, 25 ), PAGE_GLUSTER(PAGE_ADDRESS7, 26 ), PAGE_GLUSTER(PAGE_ADDRESS7, 27 ),
PAGE_GLUSTER(PAGE_ADDRESS7, 28 ),	PAGE_GLUSTER(PAGE_ADDRESS7, 29 ), PAGE_GLUSTER(PAGE_ADDRESS7, 30 ), PAGE_GLUSTER(PAGE_ADDRESS7, 31 ),	
//page8
PAGE_GLUSTER(PAGE_ADDRESS8, 0 ),  PAGE_GLUSTER(PAGE_ADDRESS8, 1 ),  PAGE_GLUSTER(PAGE_ADDRESS8, 2 ),  PAGE_GLUSTER(PAGE_ADDRESS8, 3 ),	
PAGE_GLUSTER(PAGE_ADDRESS8, 4 ),  PAGE_GLUSTER(PAGE_ADDRESS8, 5 ),  PAGE_GLUSTER(PAGE_ADDRESS8, 6 ),	PAGE_GLUSTER(PAGE_ADDRESS8, 7 ),
PAGE_GLUSTER(PAGE_ADDRESS8, 8 ),  PAGE_GLUSTER(PAGE_ADDRESS8, 9 ),	PAGE_GLUSTER(PAGE_ADDRESS8, 10 ), PAGE_GLUSTER(PAGE_ADDRESS8, 11 ),
PAGE_GLUSTER(PAGE_ADDRESS8, 12 ),	PAGE_GLUSTER(PAGE_ADDRESS8, 13 ), PAGE_GLUSTER(PAGE_ADDRESS8, 14 ), PAGE_GLUSTER(PAGE_ADDRESS8, 15 ),
PAGE_GLUSTER(PAGE_ADDRESS8, 16 ),	PAGE_GLUSTER(PAGE_ADDRESS8, 17 ), PAGE_GLUSTER(PAGE_ADDRESS8, 18 ), PAGE_GLUSTER(PAGE_ADDRESS8, 19 ),
PAGE_GLUSTER(PAGE_ADDRESS8, 20 ),	PAGE_GLUSTER(PAGE_ADDRESS8, 21 ), PAGE_GLUSTER(PAGE_ADDRESS8, 22 ), PAGE_GLUSTER(PAGE_ADDRESS8, 23 ),
PAGE_GLUSTER(PAGE_ADDRESS8, 24 ),	PAGE_GLUSTER(PAGE_ADDRESS8, 25 ), PAGE_GLUSTER(PAGE_ADDRESS8, 26 ), PAGE_GLUSTER(PAGE_ADDRESS8, 27 ),
PAGE_GLUSTER(PAGE_ADDRESS8, 28 ),	PAGE_GLUSTER(PAGE_ADDRESS8, 29 ), PAGE_GLUSTER(PAGE_ADDRESS8, 30 ), PAGE_GLUSTER(PAGE_ADDRESS8, 31 ),	
//page9
PAGE_GLUSTER(PAGE_ADDRESS9, 0 ),  PAGE_GLUSTER(PAGE_ADDRESS9, 1 ),  PAGE_GLUSTER(PAGE_ADDRESS9, 2 ),  PAGE_GLUSTER(PAGE_ADDRESS9, 3 ),	
PAGE_GLUSTER(PAGE_ADDRESS9, 4 ),  PAGE_GLUSTER(PAGE_ADDRESS9, 5 ),  PAGE_GLUSTER(PAGE_ADDRESS9, 6 ),	PAGE_GLUSTER(PAGE_ADDRESS9, 7 ),
PAGE_GLUSTER(PAGE_ADDRESS9, 8 ),  PAGE_GLUSTER(PAGE_ADDRESS9, 9 ),	PAGE_GLUSTER(PAGE_ADDRESS9, 10 ), PAGE_GLUSTER(PAGE_ADDRESS9, 11 ),
PAGE_GLUSTER(PAGE_ADDRESS9, 12 ),	PAGE_GLUSTER(PAGE_ADDRESS9, 13 ), PAGE_GLUSTER(PAGE_ADDRESS9, 14 ), PAGE_GLUSTER(PAGE_ADDRESS9, 15 ),
PAGE_GLUSTER(PAGE_ADDRESS9, 16 ),	PAGE_GLUSTER(PAGE_ADDRESS9, 17 ), PAGE_GLUSTER(PAGE_ADDRESS9, 18 ), PAGE_GLUSTER(PAGE_ADDRESS9, 19 ),
PAGE_GLUSTER(PAGE_ADDRESS9, 20 ),	PAGE_GLUSTER(PAGE_ADDRESS9, 21 ), PAGE_GLUSTER(PAGE_ADDRESS9, 22 ), PAGE_GLUSTER(PAGE_ADDRESS9, 23 ),
PAGE_GLUSTER(PAGE_ADDRESS9, 24 ),	PAGE_GLUSTER(PAGE_ADDRESS9, 25 ), PAGE_GLUSTER(PAGE_ADDRESS9, 26 ), PAGE_GLUSTER(PAGE_ADDRESS9, 27 ),
PAGE_GLUSTER(PAGE_ADDRESS9, 28 ),	PAGE_GLUSTER(PAGE_ADDRESS9, 29 ), PAGE_GLUSTER(PAGE_ADDRESS9, 30 ), PAGE_GLUSTER(PAGE_ADDRESS9, 31 ),	
//page10
PAGE_GLUSTER(PAGE_ADDRESS10, 0 ),  PAGE_GLUSTER(PAGE_ADDRESS10, 1 ),  PAGE_GLUSTER(PAGE_ADDRESS10, 2 ),  PAGE_GLUSTER(PAGE_ADDRESS10, 3 ),	
PAGE_GLUSTER(PAGE_ADDRESS10, 4 ),  PAGE_GLUSTER(PAGE_ADDRESS10, 5 ),  PAGE_GLUSTER(PAGE_ADDRESS10, 6 ),	PAGE_GLUSTER(PAGE_ADDRESS10, 7 ),
PAGE_GLUSTER(PAGE_ADDRESS10, 8 ),  PAGE_GLUSTER(PAGE_ADDRESS10, 9 ),	PAGE_GLUSTER(PAGE_ADDRESS10, 10 ), PAGE_GLUSTER(PAGE_ADDRESS10, 11 ),
PAGE_GLUSTER(PAGE_ADDRESS10, 12 ),	PAGE_GLUSTER(PAGE_ADDRESS10, 13 ), PAGE_GLUSTER(PAGE_ADDRESS10, 14 ), PAGE_GLUSTER(PAGE_ADDRESS10, 15 ),
PAGE_GLUSTER(PAGE_ADDRESS10, 16 ),	PAGE_GLUSTER(PAGE_ADDRESS10, 17 ), PAGE_GLUSTER(PAGE_ADDRESS10, 18 ), PAGE_GLUSTER(PAGE_ADDRESS10, 19 ),
PAGE_GLUSTER(PAGE_ADDRESS10, 20 ),	PAGE_GLUSTER(PAGE_ADDRESS10, 21 ), PAGE_GLUSTER(PAGE_ADDRESS10, 22 ), PAGE_GLUSTER(PAGE_ADDRESS10, 23 ),
PAGE_GLUSTER(PAGE_ADDRESS10, 24 ),	PAGE_GLUSTER(PAGE_ADDRESS10, 25 ), PAGE_GLUSTER(PAGE_ADDRESS10, 26 ), PAGE_GLUSTER(PAGE_ADDRESS10, 27 ),
PAGE_GLUSTER(PAGE_ADDRESS10, 28 ),	PAGE_GLUSTER(PAGE_ADDRESS10, 29 ), PAGE_GLUSTER(PAGE_ADDRESS10, 30 ), PAGE_GLUSTER(PAGE_ADDRESS10, 31 ),	
//page11
PAGE_GLUSTER(PAGE_ADDRESS11, 0 ),  PAGE_GLUSTER(PAGE_ADDRESS11, 1 ),  PAGE_GLUSTER(PAGE_ADDRESS11, 2 ),  PAGE_GLUSTER(PAGE_ADDRESS11, 3 ),	
PAGE_GLUSTER(PAGE_ADDRESS11, 4 ),  PAGE_GLUSTER(PAGE_ADDRESS11, 5 ),  PAGE_GLUSTER(PAGE_ADDRESS11, 6 ),	PAGE_GLUSTER(PAGE_ADDRESS11, 7 ),
PAGE_GLUSTER(PAGE_ADDRESS11, 8 ),  PAGE_GLUSTER(PAGE_ADDRESS11, 9 ),	PAGE_GLUSTER(PAGE_ADDRESS11, 10 ), PAGE_GLUSTER(PAGE_ADDRESS11, 11 ),
PAGE_GLUSTER(PAGE_ADDRESS11, 12 ),	PAGE_GLUSTER(PAGE_ADDRESS11, 13 ), PAGE_GLUSTER(PAGE_ADDRESS11, 14 ), PAGE_GLUSTER(PAGE_ADDRESS11, 15 ),
PAGE_GLUSTER(PAGE_ADDRESS11, 16 ),	PAGE_GLUSTER(PAGE_ADDRESS11, 17 ), PAGE_GLUSTER(PAGE_ADDRESS11, 18 ), PAGE_GLUSTER(PAGE_ADDRESS11, 19 ),
PAGE_GLUSTER(PAGE_ADDRESS11, 20 ),	PAGE_GLUSTER(PAGE_ADDRESS11, 21 ), PAGE_GLUSTER(PAGE_ADDRESS11, 22 ), PAGE_GLUSTER(PAGE_ADDRESS11, 23 ),
PAGE_GLUSTER(PAGE_ADDRESS11, 24 ),	PAGE_GLUSTER(PAGE_ADDRESS11, 25 ), PAGE_GLUSTER(PAGE_ADDRESS11, 26 ), PAGE_GLUSTER(PAGE_ADDRESS11, 27 ),
PAGE_GLUSTER(PAGE_ADDRESS11, 28 ),	PAGE_GLUSTER(PAGE_ADDRESS11, 29 ), PAGE_GLUSTER(PAGE_ADDRESS11, 30 ), PAGE_GLUSTER(PAGE_ADDRESS11, 31 ),	
//page12
PAGE_GLUSTER(PAGE_ADDRESS12, 0 ),  PAGE_GLUSTER(PAGE_ADDRESS12, 1 ),  PAGE_GLUSTER(PAGE_ADDRESS12, 2 ),  PAGE_GLUSTER(PAGE_ADDRESS12, 3 ),	
PAGE_GLUSTER(PAGE_ADDRESS12, 4 ),  PAGE_GLUSTER(PAGE_ADDRESS12, 5 ),  PAGE_GLUSTER(PAGE_ADDRESS12, 6 ),	PAGE_GLUSTER(PAGE_ADDRESS12, 7 ),
PAGE_GLUSTER(PAGE_ADDRESS12, 8 ),  PAGE_GLUSTER(PAGE_ADDRESS12, 9 ),	PAGE_GLUSTER(PAGE_ADDRESS12, 10 ), PAGE_GLUSTER(PAGE_ADDRESS12, 11 ),
PAGE_GLUSTER(PAGE_ADDRESS12, 12 ),	PAGE_GLUSTER(PAGE_ADDRESS12, 13 ), PAGE_GLUSTER(PAGE_ADDRESS12, 14 ), PAGE_GLUSTER(PAGE_ADDRESS12, 15 ),
PAGE_GLUSTER(PAGE_ADDRESS12, 16 ),	PAGE_GLUSTER(PAGE_ADDRESS12, 17 ), PAGE_GLUSTER(PAGE_ADDRESS12, 18 ), PAGE_GLUSTER(PAGE_ADDRESS12, 19 ),
PAGE_GLUSTER(PAGE_ADDRESS12, 20 ),	PAGE_GLUSTER(PAGE_ADDRESS12, 21 ), PAGE_GLUSTER(PAGE_ADDRESS12, 22 ), PAGE_GLUSTER(PAGE_ADDRESS12, 23 ),
PAGE_GLUSTER(PAGE_ADDRESS12, 24 ),	PAGE_GLUSTER(PAGE_ADDRESS12, 25 ), PAGE_GLUSTER(PAGE_ADDRESS12, 26 ), PAGE_GLUSTER(PAGE_ADDRESS12, 27 ),
PAGE_GLUSTER(PAGE_ADDRESS12, 28 ),	PAGE_GLUSTER(PAGE_ADDRESS12, 29 ), PAGE_GLUSTER(PAGE_ADDRESS12, 30 ), PAGE_GLUSTER(PAGE_ADDRESS12, 31 ),	
//page13
PAGE_GLUSTER(PAGE_ADDRESS13, 0 ),  PAGE_GLUSTER(PAGE_ADDRESS13, 1 ),  PAGE_GLUSTER(PAGE_ADDRESS13, 2 ),  PAGE_GLUSTER(PAGE_ADDRESS13, 3 ),	
PAGE_GLUSTER(PAGE_ADDRESS13, 4 ),  PAGE_GLUSTER(PAGE_ADDRESS13, 5 ),  PAGE_GLUSTER(PAGE_ADDRESS13, 6 ),	PAGE_GLUSTER(PAGE_ADDRESS13, 7 ),
PAGE_GLUSTER(PAGE_ADDRESS13, 8 ),  PAGE_GLUSTER(PAGE_ADDRESS13, 9 ),	PAGE_GLUSTER(PAGE_ADDRESS13, 10 ), PAGE_GLUSTER(PAGE_ADDRESS13, 11 ),
PAGE_GLUSTER(PAGE_ADDRESS13, 12 ),	PAGE_GLUSTER(PAGE_ADDRESS13, 13 ), PAGE_GLUSTER(PAGE_ADDRESS13, 14 ), PAGE_GLUSTER(PAGE_ADDRESS13, 15 ),
PAGE_GLUSTER(PAGE_ADDRESS13, 16 ),	PAGE_GLUSTER(PAGE_ADDRESS13, 17 ), PAGE_GLUSTER(PAGE_ADDRESS13, 18 ), PAGE_GLUSTER(PAGE_ADDRESS13, 19 ),
PAGE_GLUSTER(PAGE_ADDRESS13, 20 ),	PAGE_GLUSTER(PAGE_ADDRESS13, 21 ), PAGE_GLUSTER(PAGE_ADDRESS13, 22 ), PAGE_GLUSTER(PAGE_ADDRESS13, 23 ),
PAGE_GLUSTER(PAGE_ADDRESS13, 24 ),	PAGE_GLUSTER(PAGE_ADDRESS13, 25 ), PAGE_GLUSTER(PAGE_ADDRESS13, 26 ), PAGE_GLUSTER(PAGE_ADDRESS13, 27 ),
PAGE_GLUSTER(PAGE_ADDRESS13, 28 ),	PAGE_GLUSTER(PAGE_ADDRESS13, 29 ), PAGE_GLUSTER(PAGE_ADDRESS13, 30 ), PAGE_GLUSTER(PAGE_ADDRESS13, 31 ),	
//page14
PAGE_GLUSTER(PAGE_ADDRESS14, 0 ),  PAGE_GLUSTER(PAGE_ADDRESS14, 1 ),  PAGE_GLUSTER(PAGE_ADDRESS14, 2 ),  PAGE_GLUSTER(PAGE_ADDRESS14, 3 ),	
PAGE_GLUSTER(PAGE_ADDRESS14, 4 ),  PAGE_GLUSTER(PAGE_ADDRESS14, 5 ),  PAGE_GLUSTER(PAGE_ADDRESS14, 6 ),	PAGE_GLUSTER(PAGE_ADDRESS14, 7 ),
PAGE_GLUSTER(PAGE_ADDRESS14, 8 ),  PAGE_GLUSTER(PAGE_ADDRESS14, 9 ),	PAGE_GLUSTER(PAGE_ADDRESS14, 10 ), PAGE_GLUSTER(PAGE_ADDRESS14, 11 ),
PAGE_GLUSTER(PAGE_ADDRESS14, 12 ),	PAGE_GLUSTER(PAGE_ADDRESS14, 13 ), PAGE_GLUSTER(PAGE_ADDRESS14, 14 ), PAGE_GLUSTER(PAGE_ADDRESS14, 15 ),
PAGE_GLUSTER(PAGE_ADDRESS14, 16 ),	PAGE_GLUSTER(PAGE_ADDRESS14, 17 ), PAGE_GLUSTER(PAGE_ADDRESS14, 18 ), PAGE_GLUSTER(PAGE_ADDRESS14, 19 ),
PAGE_GLUSTER(PAGE_ADDRESS14, 20 ),	PAGE_GLUSTER(PAGE_ADDRESS14, 21 ), PAGE_GLUSTER(PAGE_ADDRESS14, 22 ), PAGE_GLUSTER(PAGE_ADDRESS14, 23 ),
PAGE_GLUSTER(PAGE_ADDRESS14, 24 ),	PAGE_GLUSTER(PAGE_ADDRESS14, 25 ), PAGE_GLUSTER(PAGE_ADDRESS14, 26 ), PAGE_GLUSTER(PAGE_ADDRESS14, 27 ),
PAGE_GLUSTER(PAGE_ADDRESS14, 28 ),	PAGE_GLUSTER(PAGE_ADDRESS14, 29 ), PAGE_GLUSTER(PAGE_ADDRESS14, 30 ), PAGE_GLUSTER(PAGE_ADDRESS14, 31 ),	
//page15
PAGE_GLUSTER(PAGE_ADDRESS15, 0 ),  PAGE_GLUSTER(PAGE_ADDRESS15, 1 ),  PAGE_GLUSTER(PAGE_ADDRESS15, 2 ),  PAGE_GLUSTER(PAGE_ADDRESS15, 3 ),	
PAGE_GLUSTER(PAGE_ADDRESS15, 4 ),  PAGE_GLUSTER(PAGE_ADDRESS15, 5 ),  PAGE_GLUSTER(PAGE_ADDRESS15, 6 ),	PAGE_GLUSTER(PAGE_ADDRESS15, 7 ),
PAGE_GLUSTER(PAGE_ADDRESS15, 8 ),  PAGE_GLUSTER(PAGE_ADDRESS15, 9 ),	PAGE_GLUSTER(PAGE_ADDRESS15, 10 ), PAGE_GLUSTER(PAGE_ADDRESS15, 11 ),
PAGE_GLUSTER(PAGE_ADDRESS15, 12 ),	PAGE_GLUSTER(PAGE_ADDRESS15, 13 ), PAGE_GLUSTER(PAGE_ADDRESS15, 14 ), PAGE_GLUSTER(PAGE_ADDRESS15, 15 ),
PAGE_GLUSTER(PAGE_ADDRESS15, 16 ),	PAGE_GLUSTER(PAGE_ADDRESS15, 17 ), PAGE_GLUSTER(PAGE_ADDRESS15, 18 ), PAGE_GLUSTER(PAGE_ADDRESS15, 19 ),
PAGE_GLUSTER(PAGE_ADDRESS15, 20 ),	PAGE_GLUSTER(PAGE_ADDRESS15, 21 ), PAGE_GLUSTER(PAGE_ADDRESS15, 22 ), PAGE_GLUSTER(PAGE_ADDRESS15, 23 ),
PAGE_GLUSTER(PAGE_ADDRESS15, 24 ),	PAGE_GLUSTER(PAGE_ADDRESS15, 25 ), PAGE_GLUSTER(PAGE_ADDRESS15, 26 ), PAGE_GLUSTER(PAGE_ADDRESS15, 27 ),
PAGE_GLUSTER(PAGE_ADDRESS15, 28 ),	PAGE_GLUSTER(PAGE_ADDRESS15, 29 ), PAGE_GLUSTER(PAGE_ADDRESS15, 30 ), PAGE_GLUSTER(PAGE_ADDRESS15, 31 ),	
//page16
PAGE_GLUSTER(PAGE_ADDRESS16, 0 ),  PAGE_GLUSTER(PAGE_ADDRESS16, 1 ),  PAGE_GLUSTER(PAGE_ADDRESS16, 2 ),  PAGE_GLUSTER(PAGE_ADDRESS16, 3 ),	
PAGE_GLUSTER(PAGE_ADDRESS16, 4 ),  PAGE_GLUSTER(PAGE_ADDRESS16, 5 ),  PAGE_GLUSTER(PAGE_ADDRESS16, 6 ),	PAGE_GLUSTER(PAGE_ADDRESS16, 7 ),
PAGE_GLUSTER(PAGE_ADDRESS16, 8 ),  PAGE_GLUSTER(PAGE_ADDRESS16, 9 ),	PAGE_GLUSTER(PAGE_ADDRESS16, 10 ), PAGE_GLUSTER(PAGE_ADDRESS16, 11 ),
PAGE_GLUSTER(PAGE_ADDRESS16, 12 ),	PAGE_GLUSTER(PAGE_ADDRESS16, 13 ), PAGE_GLUSTER(PAGE_ADDRESS16, 14 ), PAGE_GLUSTER(PAGE_ADDRESS16, 15 ),
PAGE_GLUSTER(PAGE_ADDRESS16, 16 ),	PAGE_GLUSTER(PAGE_ADDRESS16, 17 ), PAGE_GLUSTER(PAGE_ADDRESS16, 18 ), PAGE_GLUSTER(PAGE_ADDRESS16, 19 ),
PAGE_GLUSTER(PAGE_ADDRESS16, 20 ),	PAGE_GLUSTER(PAGE_ADDRESS16, 21 ), PAGE_GLUSTER(PAGE_ADDRESS16, 22 ), PAGE_GLUSTER(PAGE_ADDRESS16, 23 ),
PAGE_GLUSTER(PAGE_ADDRESS16, 24 ),	PAGE_GLUSTER(PAGE_ADDRESS16, 25 ), PAGE_GLUSTER(PAGE_ADDRESS16, 26 ), PAGE_GLUSTER(PAGE_ADDRESS16, 27 ),
PAGE_GLUSTER(PAGE_ADDRESS16, 28 ),	PAGE_GLUSTER(PAGE_ADDRESS16, 29 ), PAGE_GLUSTER(PAGE_ADDRESS16, 30 ), PAGE_GLUSTER(PAGE_ADDRESS16, 31 ),	
*/
};	


#define	GetClusterAddress(n)	ClusterMap[n-1]

static	WORD		wFATCluster;				
static	FAT			ramFAT;						
static	FCB			fcb[ _NFILE  ];				/*	FCB						*/

/****************************************************************************/
/*																			*/
/*																			*/
/****************************************************************************/
static	int		FCB_GetFree(int nBusyFlag);
static	int		FCB_Free(int handle);
static	int		FCB_OpenCheck(const char* name);
static	WORD	FCB_GetTergetCluster(int handle);
static	int		FCB_GetNewCluster(int handle);

static	int		SplitFileName(PCSTR pcszFilename, PSTR szName, PSTR szExt);
#define	FCB_SetName(handle, name)	SplitFileName(name, fcb[handle].szName, fcb[handle].szExt)

static	WORD	GetNumOfCluster(VOID);
static	int		GetNumOfPage(VOID);
static	int		PageFromCluster(WORD wCluster);
static	int		ClusterFromPage(int nPage);

static	int		ramFAT_GetFileIndex(const char* name);
static	WORD	ramFAT_GetNextCluster(WORD wCluster);
static	VOID	ramFAT_SetNextCluster(WORD wCluster, WORD wNextCluster);
static	int		ramFAT_Update(VOID);
static	int		ramFAT_GetFreeDirectory(VOID);

static	int		ByteWrite(  DWORD pbAdr, BYTE bData);
static	int		WordWrite(  DWORD pwAdr, WORD wData);
static	int		DwordWrite( DWORD pdwAdr, DWORD dwData);
static	int		BufferWrite(DWORD pvDest, PCVOID pcvSrc, unsigned int nCount);
static  WORD  GetClusterMark( WORD cluster);

static	int		CleanupCluster(BOOL bBusyCluster);
static	int		SetClusterMark(WORD wCluster, WORD wMark, WORD wFATData);
static	int		EraseCluster(WORD wCluster);
static	int		ErasePage(int nPage);
static	int		GetFreeCluster(int nFlag);

#define		TARGET_LO_VOID	0
#define		TARGET_ALL		1

static	int		VoidClusterFree(VOID);

static	VOID	Dir(PFAT pFAT);
static	VOID	FatStatus(VOID);
static	VOID	ClusterStatus(VOID);
static	VOID	PageStatus(VOID);
static	int	GetFileName(PFAT pFAT,F_NAME* pfile);				
static DWORD GetPageRewriteCounter( WORD nPage );

/****************************************************************************/
/*																			*/
/*																			*/
/****************************************************************************/
#define	min(a, b)	(((a) < (b)) ? (a) : (b))
#define	max(a, b)	(((a) > (b)) ? (a) : (b))


int		BiosEntry(int R0, int R1, int R2, int R3)
{
	switch (R3){
		case	FILE_CREATE	:	  return(b_file_create((const char*)R0, R1));
		case	FILE_OPEN	:	    return(b_file_open((const char*)R0, R1));
		case	FILE_CLOSE	:	  return(b_file_close(R0));
		case	FILE_READ	:	    return(b_file_read(R0, (char*)R1, (unsigned int)R2));
		case	FILE_WRITE	:	  return(b_file_write(R0, (const char*)R1, (unsigned int)R2));
		case	FILE_REMOVE	:	  return(b_file_remove((const char*)R0));
		case	FILE_RENAME	:	  return(b_file_rename((const char*)R0, (const char*)R1));
		case	FILE_LSEEK	:	  return(b_file_lseek(R0, (long)R1, R2));
		case	FILE_GETATTR:	  return(b_file_getattr((const char*)R0));
		case	FILE_SETATTR:	  return(b_file_setattr((const char*)R0, (unsigned char)R1));
		case	FILE_NAMESET:	  return(b_file_getfilename((F_NAME*)R0) );
		case	FILE_PAGESET:	  return(b_file_getSecterStatus( (PAGE_INFO*)R0 ));
		
			break;
	}
	return(-1);
}



/****************************************************************************/
/*	int		b_file_initialize(void)											                      */
/*	funciton :  initialize file system		   */
/*																			*/
/*	input:	None															*/
/*																			*/
/*	output:	0	:	OK												*/
/*			   -1	:	fail												*/
/*																			*/
/****************************************************************************/

int		b_file_initialize(void)
{
	int			nLoop;
	int			nRet;
	int			nFATCount;
	int			nNumOfPage	;
	DWORD		dwMinRewrite;
	WORD		wCluster;
	DWORD /*PCLUSTER*/	pCluster;
	PCLUSTER	pFATCluster;
	WORD ClusterMark;
/*
	DBG_MSG1("ClusterMap address : %08lX\n",	&ClusterMap);
	DBG_MSG1("ramFAT address     : %08lX\n",	&ramFAT);
	DBG_MSG1(" ->bFAT address    : %08lX\n",	&ramFAT.bFAT);
	DBG_MSG1("fcb address        : %08lX\n",	&fcb);
	DBG_MSG1("max page ID        : %ld\n",		nNumOfPage);
	DBG_MSG1("max cluster ID     : %04X\n",		GetNumOfCluster());
*/
	
	
	nNumOfPage	= GetNumOfPage();
	dwMinRewrite	= 0xffffffff;
	for (nLoop = nNumOfPage - 1; nLoop >= 0; nLoop--){
		dwMinRewrite	= min(dwMinRewrite, GetPageRewriteCounter( nLoop ));
	}
	
/*
	for( nLoop = 1; nLoop <= NUM_OF_CLUSTER; nLoop++)
	    printf("cluster number =%d,cluster add = 0x%08x\n",nLoop, GetClusterAddress(nLoop));
*/
	
	/*-----------------------------------------------------------------------*/
	/*  a page can not be written to 0xffffffff times,it maybe free page     */
	/*  so if dwMinRewrite == 0xffffffff change to 0x00                      */
  /*-----------------------------------------------------------------------*/	
	if (dwMinRewrite == 0xffffffff)
		dwMinRewrite++;
	for (nLoop = nNumOfPage - 1; nLoop >= 0; nLoop--){
		if (GetPageRewriteCounter( nLoop ) == 0xffffffff){		
      /*-------------------------------------------------------------------*/
      /*    if the 	dwMinRewrite  of page has not be written               */
      /*     write 	dwMinRewrite to update it                              */
      /*-------------------------------------------------------------------*/			
			DwordWrite( GetPageAddress( nLoop ), dwMinRewrite);
		}
	}
	/*----------------------------------------------------------------------*/
	/*                     initialize the fcb                               */ 
	/*----------------------------------------------------------------------*/
	memset(&fcb, 0, sizeof(fcb));
	
	
	memset(&ramFAT, 0xff, sizeof(FAT));
	wFATCluster	= FAT_VOID;
	pFATCluster	= NULL;
	/*----------------------------------------------------------------------*/
	/*         search the FAT cluster and copy to RAMFAT                    */
	/*----------------------------------------------------------------------*/
	nFATCount	= 0;
	for (wCluster = GetNumOfCluster(); wCluster > 0; wCluster--){
		
		if (( GetClusterMark(wCluster) & ~CM_FAT_ID) == CM_FAT){
/*		DBG_MSG(" find FAT \n");*/
			if (++nFATCount >= 3){				
				ERR_MSG("find more than 3 FAT\n");
				memset(&ramFAT, 0xff, sizeof(FAT));
				wFATCluster	= FAT_VOID;
				pFATCluster	= NULL;
				break;
			}
			/*--------------------------------------------------------------*/
			/*	               Update fat cluster										        */
			/*--------------------------------------------------------------*/
			if (wFATCluster == FAT_VOID){				
				wFATCluster	= wCluster;
			}else{				
				if ((( GetClusterMark(wFATCluster) + 1) & CM_FAT_ID)
				== ( GetClusterMark(wCluster) & CM_FAT_ID)){
					if (((nRet = SetClusterMark(wFATCluster, CM_VOID, FAT_VOID)) < 0)
					&&	((pFATCluster->wClusterMark & ~CM_FAT_ID) == CM_FAT)){						
						return(nRet);
					}
					wFATCluster	= wCluster;					
				}else if (((GetClusterMark(wFATCluster) - 1) & CM_FAT_ID)
				== (GetClusterMark(wCluster) & CM_FAT_ID)){
					if (((nRet = SetClusterMark(wCluster, CM_VOID, FAT_VOID)) < 0)
					&&	((GetClusterMark(wCluster) & ~CM_FAT_ID) == CM_FAT)){						
						return(nRet);
					}
					continue;
				}else{					
					memset(&ramFAT, 0xff, sizeof(FAT));
					wFATCluster	= FAT_VOID;
					pFATCluster	= NULL;
					break;
				}
			}
			/*--------------------------------------------------------------*/
			/*--------------------------------------------------------------*/
			SpiFlashRead( GetClusterAddress( wFATCluster ) + 4, ( uint8_t* )&ramFAT, sizeof( FAT ) );			
		}
	}
	/*----------------------------------------------------------------------*/
	/*	                       Clean up cluster													    */
	/*----------------------------------------------------------------------*/
	if ((nRet = CleanupCluster(TRUE)) < 0)
		return(nRet);
	
	/*----------------------------------------------------------------------*/
	/*                 Update FAT to flash                                  */
	/*----------------------------------------------------------------------*/
	if (nRet){		
		if ((nRet = ramFAT_Update()) < 0){
			return(nRet);
		}
	}
	/*----------------------------------------------------------------------*/
	/*	         release void cluster to reuse again												*/
	/*----------------------------------------------------------------------*/
	return(VoidClusterFree());
}

/****************************************************************************/
/*																			                                    */
/*	int		b_file_create(const char* name, int mode)						              */
/*																			                                    */
/*	function :	create file												                          */
/*																			                                    */
/*	input :	name	:	file name									                              */
/*			    mode	:	file mode									                              */
/*																			                                    */
/*	return :	0 or more	  :	return the file handle									        */
/*			      -1 or less	:	fail											                      */
/*																			                                    */
/****************************************************************************/
int		b_file_create(const char* name, int mode)
{
	int			nIndexOfDir;
	PDIRECTORY	pDir;
	int			handle;
	PFCB		pFCB;
/*
	DBG_MSG2("b_file_create(\"%s\", %02X)\n", name, mode);
*/
	/*----------------------------------------------------------------------*/
	/*	         if the file has existed return -80									        */
	/*----------------------------------------------------------------------*/
	if ((nIndexOfDir = ramFAT_GetFileIndex(name)) >= 0){
		ERR_MSG("File has existed,can not create\n");
		return(-80);
	}
	/*----------------------------------------------------------------------*/
	/*	                  Get free file directory slot									    */
	/*----------------------------------------------------------------------*/
	nIndexOfDir	= ramFAT_GetFreeDirectory();
	if (nIndexOfDir < 0){
		ERR_MSG("can not allocate file slot\n");
		return(-82);
	}
	pDir	= &ramFAT.dir[nIndexOfDir];
	/*----------------------------------------------------------------------*/
	/*	                  check the slot atrribute												  */
	/*----------------------------------------------------------------------*/
	handle	= FCB_GetFree(fcb_busy_write);
	if (handle < 0){
		return(handle);
	}
	pFCB	= &fcb[handle];
	/*----------------------------------------------------------------------*/
	/*	                       set FCB attribute														*/
	/*----------------------------------------------------------------------*/
	FCB_SetName(handle, name);
	pFCB->bAttrib		= LOBYTE(LOWORD(mode));
	pFCB->nIndexOfDir	= nIndexOfDir;
	pFCB->dwSize		= 0;
	pFCB->dwOffset		= 0;
	/*----------------------------------------------------------------------*/
	/*	                    set directory attribute													*/
	/*----------------------------------------------------------------------*/
	memset(pDir, 0xff, sizeof(DIRECTORY));
	memcpy(pDir->szName, pFCB->szName, MAX_NAME);
	memcpy(pDir->szExt,  pFCB->szExt,  MAX_EXT);
	
	pDir->bAttrib		  = LOBYTE(LOWORD(mode));
	pDir->wTopCluster	= FAT_EOF;
	pDir->dwSize		  = 0;
	return(handle);
}

/****************************************************************************/
/*																			                                    */
/*	int		b_file_open(const char* name, int code)							              */
/*                                                                          */
/*   function: open the file with name string                               */
/*   input   :name : file name string                                       */
/*            mode : file open mode                                         */
/*   output  : 0 or more :file handle                                       */
/*             -1 or less: open file error                                  */
/****************************************************************************/
int		b_file_open(const char* name, int code)
{
	int			nIndexOfDir;
	PDIRECTORY	pDir;
	int			handle;
	PFCB		pFCB;
/*
	DBG_MSG2("b_file_open(\"%s\", %02X)\n", name, code);
*/
	/*----------------------------------------------------------------------*/
	/*----------------------------------------------------------------------*/
	nIndexOfDir	= ramFAT_GetFileIndex(name);
	if (nIndexOfDir < 0){
/*		ERR_MSG("file does not exist\n");*/
		return(-2);
	}
	pDir	= &ramFAT.dir[nIndexOfDir];
	/*----------------------------------------------------------------------*/
	/*	                         check atrribute												    */
	/*----------------------------------------------------------------------*/
	switch (code){
		/*------------------------------------------------------------------*/
		/*	                     open for read											        */
		/*------------------------------------------------------------------*/
		case	CODE_READ_ONLY:
			break;
		/*------------------------------------------------------------------*/
		/*	                      Open for write											      */
		/*------------------------------------------------------------------*/
		case	CODE_WRITE_ONLY:
		case	CODE_READ_WRITE:
			if (pDir->bAttrib & __A_RDONLY){
				/*----------------------------------------------------------*/
				/*	               Atrribute error		                      */
				/*----------------------------------------------------------*/
				ERR_MSG("b_file_open:The file can not be opend for write\n");
				return(-1);
			}
			break;
	}
	/*----------------------------------------------------------------------*/
	/*	                    check whether file	exist												*/
	/*----------------------------------------------------------------------*/
	handle	= FCB_OpenCheck(name);
	if (handle < 0){
		return(handle);
	}
	/*----------------------------------------------------------------------*/
	/*	                 Get free FCB  handle												        */
	/*----------------------------------------------------------------------*/
	handle	= FCB_GetFree(code == CODE_READ_ONLY ? fcb_busy_read : fcb_busy_write);
	if (handle < 0){
		DBG_MSG1("can not allocate file slot%d", handle);
		return(handle);
	}
	pFCB	= &fcb[handle];
	/*----------------------------------------------------------------------*/
	/*	                       set FCB param									              */
	/*----------------------------------------------------------------------*/
	FCB_SetName(handle, name);
	pFCB->bAttrib		= pDir->bAttrib;
	pFCB->nIndexOfDir	= nIndexOfDir;
	pFCB->dwSize		= pDir->dwSize;
	pFCB->dwOffset		= 0;
	return(handle);
}

/****************************************************************************/
/*																			                                    */
/*	int		b_file_close(int handle)										                      */
/*																			                                    */
/*	function :	close the file with handle												          */
/*																			                                    */
/*	input :	handle	:	file handle									                          */
/*																			                                    */
/*	output :	0		      :	ok											                          */
/*			     -1 or less	:	fail											                        */
/*																			                                    */
/****************************************************************************/
int		b_file_close(int handle)
{
	PFCB	pFCB	= &fcb[handle];
	int			nRet;
/*
	DBG_MSG1("b_file_close(%d)\n", handle);
*/
	/*----------------------------------------------------------------------*/
	/*	              check file handle validation													*/
	/*----------------------------------------------------------------------*/
	if ((handle < 0)
	||	(_NFILE/*-3*/ <= handle)
	||	(pFCB->nBusyFlag == fcb_busy_free)){
		ERR_MSG("b_file_close:file parameter error\n");
		return(-6);
	}
	pFCB	= &fcb[handle];
	/*----------------------------------------------------------------------*/
	/*	               check the fcb atrribute										          */
	/*----------------------------------------------------------------------*/
	if (pFCB->nBusyFlag == fcb_busy_read){
		/*------------------------------------------------------------------*/
		/*	                      free the handle													  */
		/*------------------------------------------------------------------*/
		FCB_Free(handle);
		return(0);
	}
	/*----------------------------------------------------------------------*/
	/*	Update cluster mark and update fat to flash,then free void cluster	*/
	/*----------------------------------------------------------------------*/
	else{
		/*------------------------------------------------------------------*/
		/*	                  Update cluster mark				                    */
		/*------------------------------------------------------------------*/
		WORD	wCluster	= ramFAT.dir[pFCB->nIndexOfDir].wTopCluster & 0xfff;
		while (wCluster != FAT_EOF){
			if ((nRet = WordWrite(GetClusterAddress( wCluster ), CM_DATA)) < 0){
				return(nRet);
			}
			wCluster	= ramFAT_GetNextCluster(wCluster);
		}
		/*------------------------------------------------------------------*/
		/*	                           free handle													*/
		/*------------------------------------------------------------------*/
		FCB_Free(handle);
		/*------------------------------------------------------------------*/
		/*	                Update ramFat to flash													*/
		/*------------------------------------------------------------------*/
		if ((nRet = ramFAT_Update()) < 0){
			return(nRet);
		}
		/*------------------------------------------------------------------*/
		/*	                    free void cluster													  */
		/*------------------------------------------------------------------*/
		return(VoidClusterFree());
	}
}

/****************************************************************************/
/*																			                                    */
/*	int		b_file_read(int handle, char* buf, unsigned int count)			      */
/*																			                                    */
/*	function :	read data from file to buffer												        */
/*																			                                    */
/*	input :	handle	:	file handle									                          */
/*			    buf		  :	buffer whitch store the data reading from file				*/
/*			    count	  :	the byte number to read from file								      */
/*																			                                    */
/*	output :	0 or more	:	the byte number read from file in fact						*/
/*			    -1 or less	:	fail											                        */
/*																			                                    */
/****************************************************************************/
int		b_file_read(int handle, char* buf, unsigned int count)
{
	PFCB	pFCB	= &fcb[handle];
	int		nRet;
	int		nReadCount;
	WORD	wCluster;
/*
	DBG_MSG3("b_file_read(%d, %08lX, %d)\n", handle, buf, count);
*/
	/*----------------------------------------------------------------------*/
	/*	                      parameter check													      */
	/*----------------------------------------------------------------------*/
	if ((handle < 0)
	||	(_NFILE/*-3*/ <= handle)
	||	(pFCB->nBusyFlag != fcb_busy_read)){
		ERR_MSG("b_file_read:parameter error\n");
		return(-6);
	}
	pFCB	= &fcb[handle];
	/*----------------------------------------------------------------------*/
	/*	            decide the min count to be read											    */
	/*----------------------------------------------------------------------*/
	nReadCount	= min(pFCB->dwSize - pFCB->dwOffset, count);
	if (!nReadCount)
		return((int)nReadCount);
	/*----------------------------------------------------------------------*/
	/*	                get the target cluster to read											*/
	/*----------------------------------------------------------------------*/
	nRet		= FCB_GetTergetCluster(handle);
	if (nRet < 0){
		return(nRet);
	}
	wCluster	= LOWORD(nRet);
	nRet		= nReadCount;
	/*----------------------------------------------------------------------*/
	/*	      read data until the readcount changed to zero									*/
	/*----------------------------------------------------------------------*/
	while (nReadCount > 0){
		
		int			nOffset;
		size_t		nRead;

		nOffset		= pFCB->dwOffset;
		
		if   ( nOffset >= DATA_PER_CLUSTER_6 ){	nOffset	-= DATA_PER_CLUSTER_6; }
		if   ( nOffset >= DATA_PER_CLUSTER_5 ){	nOffset	-= DATA_PER_CLUSTER_5; }
		while( nOffset >= DATA_PER_CLUSTER_4 ){	nOffset	-= DATA_PER_CLUSTER_4; }
		if   ( nOffset >= DATA_PER_CLUSTER_3 ){	nOffset	-= DATA_PER_CLUSTER_3; }
		while( nOffset >= DATA_PER_CLUSTER   ){	nOffset	-= DATA_PER_CLUSTER;   }

		nRead		= min(DATA_PER_CLUSTER - nOffset, nReadCount);
		if( SpiFlashRead( GetClusterAddress(wCluster) + 4 + nOffset,(uint8_t*)buf, nRead) < 0 )
			break;

		pFCB->dwOffset	+= nRead;
		buf				      += nRead;
		nReadCount		  -= nRead;
		wCluster		     = ramFAT_GetNextCluster(wCluster);

	}
	return(nRet);
}

/****************************************************************************/
/*	function:	write data to the specified file												      */
/*																			                                    */
/*	input :	handle	:	file handle											                      */
/*			    buf		  :	data to be written buffer starting address						*/
/*			    count	  :	byte count to be written to file								      */
/*																			                                    */
/*	output :	0 or more	  :	ok									                            */
/*			      -1 or less	:	fail											                      */
/*																			                                    */
/****************************************************************************/
int		b_file_write(int handle, const char* buf, unsigned int count)
{
	PFCB	pFCB	= &fcb[handle];
	int		nRet;
	WORD	wCluster;
	int		nWriteCount;
	DWORD	dwOffset;
/*
	DBG_MSG3("b_file_write(%d, %08lX, %d)\n", handle, buf, count);
*/
	/*----------------------------------------------------------------------*/
	/*	                parameter  validation  check												*/
	/*----------------------------------------------------------------------*/
	if ((handle < 0)
	||	(_NFILE/*-3*/ <= handle)
	||	(pFCB->nBusyFlag != fcb_busy_write)){
		ERR_MSG("b_file_write:paramter error\n");
		return(-6);
	}
	pFCB	= &fcb[handle];
	/*----------------------------------------------------------------------*/
	/*	            check if the free disk is enough to write								*/
	/*----------------------------------------------------------------------*/
	if (count > (unsigned int)b_file_getdiskfree()){
		ERR_MSG("not enough free disk\n");
		return(-39);
	}
	
	
	if ((nRet = FCB_GetTergetCluster(handle)) < 0){
		return(nRet);
	}
	wCluster	= LOWORD(nRet);
	/*----------------------------------------------------------------------*/
	/*	                write data to physical flash area										*/
	/*----------------------------------------------------------------------*/
	nWriteCount	= 0;
	dwOffset	= pFCB->dwOffset;
	while (count > 0){
					DWORD	pCluster;
					int			nOffset;
		unsigned	int			nWrite;
		if (wCluster == FAT_EOF){
			if ((nRet = FCB_GetNewCluster(handle)) < 0){
				ERR_MSG("Get free cluster error\n");
				return(-39);
			}
			wCluster	= LOWORD(nRet);
		}
		pCluster	= GetClusterAddress(wCluster);
		
		nOffset		= pFCB->dwOffset;
		if   ( nOffset >= DATA_PER_CLUSTER_6 ){	nOffset	-= DATA_PER_CLUSTER_6; }
		if   ( nOffset >= DATA_PER_CLUSTER_5 ){	nOffset	-= DATA_PER_CLUSTER_5; }
		while( nOffset >= DATA_PER_CLUSTER_4 ){	nOffset	-= DATA_PER_CLUSTER_4; }
		if   ( nOffset >= DATA_PER_CLUSTER_3 ){	nOffset	-= DATA_PER_CLUSTER_3; }
		while( nOffset >= DATA_PER_CLUSTER   ){	nOffset	-= DATA_PER_CLUSTER;   }
		nWrite		= min((unsigned int)(DATA_PER_CLUSTER - nOffset), count);	
		
		
		if ((nRet = BufferWrite(pCluster + 4 + nOffset, buf, nWrite)) < 0){
			return(nRet);
		}		
		nWriteCount	                          += nWrite;
		buf			                              += nWrite;
		count		                              -= nWrite;
		wCluster	                             = FAT_EOF;				
		dwOffset	                             = 0;
		ramFAT.dir[pFCB->nIndexOfDir].dwSize  += nWrite;
		pFCB->dwSize							            += nWrite;
	  pFCB->dwOffset							          += nWrite;
	}
		
	return(nWriteCount);
}

/****************************************************************************/
/*																			                                    */
/*	int		b_file_remove(const char* path)									                  */
/*                                                                          */
/*   function: remove the file with path/name                               */
/*      input: path: file path or name                                      */
/*      output: 0 or more :remove ok                                        */
/*              -1 or less: fail                                            */
/****************************************************************************/
int		b_file_remove(const char* path)
{
	int			nIndexOfDir;
	PDIRECTORY	pDir;
	int			nRet;
	WORD		wCluster;
/*
	DBG_MSG1("b_file_remove(\"%s\")\n", path);
*/
	/*----------------------------------------------------------------------*/
	/*	            param valid check,return value should be zero		        */
	/*----------------------------------------------------------------------*/
	nIndexOfDir	= FCB_OpenCheck(path);
	if (nIndexOfDir < 0){
		return(nIndexOfDir);
	}else if (nIndexOfDir > 0){
		ERR_MSG("b_file_remove: parameter check error\n");
		return(-33);
	}
	/*----------------------------------------------------------------------*/
	/*	                    Get file Index										              */
	/*----------------------------------------------------------------------*/
	nIndexOfDir	= ramFAT_GetFileIndex(path);
	if (nIndexOfDir < 0){
/*		ERR_MSG("file does not exist,can not remove\n");*/
		return(-2);
	}
	pDir	= &ramFAT.dir[nIndexOfDir];
	/*----------------------------------------------------------------------*/
	/*	set the first bytes to 0x00 which means the file has been removed		*/
	/*----------------------------------------------------------------------*/
	pDir->szName[0]	= '\0';
	/*----------------------------------------------------------------------*/
	/*	                      erase the cluster															*/
	/*----------------------------------------------------------------------*/
	wCluster	= pDir->wTopCluster & 0xfff;
	while (wCluster != FAT_EOF){
		WORD	wNextCluster	= ramFAT_GetNextCluster(wCluster);
		if (EraseCluster(wCluster) < 0){
			/*
			**	cluster erase error
			*/
		}
		wCluster	= wNextCluster;
	}
	pDir->wTopCluster	= FAT_VOID;
	/*----------------------------------------------------------------------*/
	/*	                  Update the FAT to flash														*/
	/*----------------------------------------------------------------------*/
	if ((nRet = ramFAT_Update()) < 0){
		return(nRet);
	}
	
	
	/*----------------------------------------------------------------------*/
	return(VoidClusterFree());
}

/****************************************************************************/
/*																			                                    */
/*	int		b_file_rename(const char* old, const char* new)					          */
/*																			                                    */
/*	function :	rename the file 													                  */
/*	input:	old		:	old file name string								                    */
/*			   new		:	new file name string								                    */
/*																			                                    */
/*	output :	0		:	ok											                                */
/*			-1 or less:	fail											                              */
/*																			                                    */
/****************************************************************************/
int		b_file_rename(const char* old, const char* new)
{
	int			nRet;
	int			nIndexOfDir;
	PDIRECTORY	pDir;
/*
	DBG_MSG2("b_file_rename(\"%s\", \"%s\")\n", old, new);
*/
	/*----------------------------------------------------------------------*/
	/*	           check if the new file name has existed								    */
	/*----------------------------------------------------------------------*/
	if (ramFAT_GetFileIndex(new) >= 0){
		ERR_MSG("The name of new file has existed \n");
		return(-80);
	}
	/*----------------------------------------------------------------------*/
	/*	                old file fcb atrribute check					              */
	/*----------------------------------------------------------------------*/
	nRet	= FCB_OpenCheck(old);
	if (nRet < 0){
		return(nRet);
	}else if (nRet > 0){
		ERR_MSG("b_file_rename:fcb check error\n");
		return(-33);
	}
	/*----------------------------------------------------------------------*/
	/*	             get the old file index in the fat											*/
	/*----------------------------------------------------------------------*/
	if ((nIndexOfDir = ramFAT_GetFileIndex(old)) < 0){
/*		ERR_MSG("file does not exist,can not rename\n");*/
		return(-2);
	}
	pDir	= &ramFAT.dir[nIndexOfDir];
	/*----------------------------------------------------------------------*/
	/*	       split the new file name to directory													*/
	/*----------------------------------------------------------------------*/
	SplitFileName(new, pDir->szName, pDir->szExt);
	/*----------------------------------------------------------------------*/
	/*	        RAM fat modified ,update to flash														*/
	/*----------------------------------------------------------------------*/
	if ((nRet = ramFAT_Update()) < 0){
		return(nRet);
	}
	/*----------------------------------------------------------------------*/
	/*	                       free void cluster														*/
	/*----------------------------------------------------------------------*/
	return(VoidClusterFree());
}

/****************************************************************************/
/*																			                                    */
/*	int		b_file_lseek(int handle, long offset, int base)					          */
/*																			                                    */
/*	function :	set file offset											                        */
/*																			                                    */
/*	input :	handle	:	file index									                          */
/*			    offset	:	read /write offset in the file											  */
/*			    base	  :	offset base									                          */
/*						0     :	no base,start of stream										            */
/*						1     :	current position in stream									          */
/*						2     :	end of stream										                      */
/*																			                                    */
/*	output :	0 or more	:	the file new offset				                        */
/*			    -1 or less	: set new offset error											        */
/*																			                                    */
/****************************************************************************/
int		b_file_lseek(int handle, long offset, int base)
{
	DWORD	dwNewOffset;
	PFCB	pFCB	= &fcb[handle];
/*
	DBG_MSG3("b_file_lseek(%d, %ld, %d)\n", handle, offset, base);
*/
	/*----------------------------------------------------------------------*/
	/*	                     parameter check													      */
	/*----------------------------------------------------------------------*/
	if ((handle < 0)
	||	(_NFILE/*-3*/ <= handle)
	||	(pFCB->nBusyFlag == fcb_busy_free)){
		ERR_MSG("b_file_lseek: parameter check error\n");
		return(-6);
	}
	pFCB	= &fcb[handle];
	/*----------------------------------------------------------------------*/
	/*	                    set the file new offset											    */
	/*----------------------------------------------------------------------*/
	switch (base){
		case	SEEK_SET:
			dwNewOffset	= (DWORD)offset;
			break;
		case	SEEK_CUR:
			dwNewOffset	= pFCB->dwOffset + offset;
			break;
		case	SEEK_END:
			dwNewOffset	= pFCB->dwSize + offset;
			break;
		default:
			ERR_MSG("b_file_lseek:base parameter error\n");
			return(-12);
	}
	/*----------------------------------------------------------------------*/
	/*	                 check new offset validation										    */
	/*----------------------------------------------------------------------*/
	if (pFCB->dwSize < dwNewOffset){
		ERR_MSG("b_file_lseek:new offset error\n");
		return(-25);
	}
	/*----------------------------------------------------------------------*/
	/*	              set the file new offset of fcb										    */
	/*----------------------------------------------------------------------*/
	pFCB->dwOffset	= dwNewOffset;
	return( ( int )dwNewOffset );
}

/****************************************************************************/
/*																			                                    */
/*	int		b_file_getattr(const char* name)								                  */
/*																			                                    */
/*     function: get the attribute of the file                              */
/*		 input   : name :file name																            */
/*     output  : -2 fail                                                    */
/*               0 or more : file atrribute                                 */
/****************************************************************************/
int		b_file_getattr(const char* name)
{
	int		nIndexOfDir;
/*
	DBG_MSG1("b_file_getattr(\"%s\")\n", name);
*/
	/*----------------------------------------------------------------------*/
	/*	                check if the file exist or not										  */
	/*----------------------------------------------------------------------*/
	if ((nIndexOfDir = ramFAT_GetFileIndex(name)) < 0){
/*		ERR_MSG("file does not exist\n");*/
		return(-2);
	}
	/*----------------------------------------------------------------------*/
	/*	                   return file attrib											          */
	/*----------------------------------------------------------------------*/
	return(ramFAT.dir[nIndexOfDir].bAttrib);
}

/****************************************************************************/
/*																			                                    */
/*	int		b_file_setattr(const char* name, unsigned char attr)			        */
/*																			                                    */
/*	function :	set the file attribut												                */
/*																			                                    */
/*	input :	name	:	file name string											                  */
/*			    attr	:	new attribute										                        */
/*																			                                    */
/*	output :	0		  :	ok											                              */
/*			-1 or less	:	fail											                            */
/*																			                                    */
/****************************************************************************/
int		b_file_setattr(const char* name, unsigned char attr)
{
	int		nIndexOfDir;
	int		nRet;
/*
	DBG_MSG2("b_file_setattr(\"%s\", %02X)\n", name, attr);
*/
	/*----------------------------------------------------------------------*/
	/*	             check whether file exists or not 										  */
	/*----------------------------------------------------------------------*/
	if ((nIndexOfDir = ramFAT_GetFileIndex(name)) < 0){
/*		ERR_MSG("file does not exist\n");*/
		return(-2);
	}
	/*----------------------------------------------------------------------*/
	/*	              Update the file attribute											        */
	/*----------------------------------------------------------------------*/
	ramFAT.dir[nIndexOfDir].bAttrib	= (BYTE)attr;
  /************************************************************************/
	/*                Update ram fat to flash                               */
	/*----------------------------------------------------------------------*/
	if ((nRet = ramFAT_Update()) < 0){
		return(nRet);
	}

	/*----------------------------------------------------------------------*/
	/*----------------------------------------------------------------------*/
	return(VoidClusterFree());
}

/****************************************************************************/
/*																			                                    */
/*	int		b_file_getdiskfree(void)										                      */
/*																			                                    */
/*	funtion :	get disk free space												                    */
/*																			                                    */
/*	input   :	None															                            */
/*																			                                    */
/*	output  :	disk space								                                    */
/*																			                                    */
/****************************************************************************/
int		b_file_getdiskfree(void)
{
	int		nLoop;
	int		nCount	= 0;
/*
	DBG_MSG("b_file_getdiskfree(void)\n");
*/
	/*----------------------------------------------------------------------*/	
	/*	caculate the FAT_FREE cluster 				*/
	/*----------------------------------------------------------------------*/
	for (nLoop = GetNumOfCluster(); nLoop > 0; nLoop--){
		switch (ramFAT_GetNextCluster(LOWORD(nLoop))){
			case	FAT_FREE:
				nCount	+= DATA_PER_CLUSTER;
				break;
		}
	}
	return(nCount ? (nCount - DATA_PER_CLUSTER) : 0);
}
/****************************************************************************/
/*																			*/
/*	int		b_file_getfilename(void)										*/
/****************************************************************************/
int	b_file_getfilename( F_NAME * pfile )
{
	return( GetFileName(&ramFAT,pfile) );
}
/****************************************************************************/
/*																			*/
/*	int 	getSecterStatus(VOID)											*/
/****************************************************************************/
int 	b_file_getSecterStatus( PAGE_INFO* psect )
{
	
	return( 0 );
}


/****************************************************************************/
/*																			                                    */
/*	void	dbg_fat_data(void)												                        */
/*																			                                    */
/*	function :	print the fat data										                      */
/*																			                                    */
/*	input  :	none															                            */
/*																			                                    */
/*	output :	none															                            */
/*																			                                    */
/****************************************************************************/
void	dbg_fat_data(void)
{
#ifdef	_DEBUG
	nChipErase	= 0;
#endif
	FatStatus();
}


/****************************************************************************/
/*																			                                    */
/*	int		FCB_GetFree(int nBusyFlag)										                    */
/*																			                                    */
/*	function :	get free file handle 										                    */
/*																			                                    */
/*	input :	nBusyFlag	:	BUSY flag										                        */
/*																			                                    */
/*	output :	0 or more		:	file handle									                    */
/*			-35			:	get file handle error							                        */
/*																			                                    */
/****************************************************************************/
static	int		FCB_GetFree(int nBusyFlag)
{
	int		handle;
	/*----------------------------------------------------------------------*/
	/*	               search free file handle												      */
	/*----------------------------------------------------------------------*/
	for (handle = 0; handle < _NFILE/*-3*/; handle++){
		PFCB	pFCB	= &fcb[handle];
		if (pFCB->nBusyFlag == fcb_busy_free){
			pFCB->nBusyFlag	= nBusyFlag;
			return(handle);
		}
	}
	/*----------------------------------------------------------------------*/
	/*	                 get free fcb slot error														*/
	/*----------------------------------------------------------------------*/
	ERR_MSG("FCB_GetFree:get file handle error\n");
	return(-35);
}

/****************************************************************************/
/*																			                                    */
/*	int		FCB_Free(int handle)											                        */
/****************************************************************************/
static	int		FCB_Free(int handle)
{
	PFCB	pFCB;
	pFCB	= &fcb[handle];
	/*----------------------------------------------------------------------*/
	/*----------------------------------------------------------------------*/
	ASSERT(pFCB->nBusyFlag != fcb_busy_free);
	pFCB->nBusyFlag	= fcb_busy_free;
	return(0);
}

/****************************************************************************/
/*																			                                    */
/*	int		FCB_OpenCheck(const char* name)									                  */
/****************************************************************************/
static	int		FCB_OpenCheck(const char* name)
{
	int		nRet	= 0;
	int		nLoop;
	TCHAR	szName[MAX_NAME+MAX_EXT];
	TCHAR	szExt[MAX_EXT];
	/*----------------------------------------------------------------------*/
	/*													*/
	/*----------------------------------------------------------------------*/
	SplitFileName(name, szName, szExt);
	/*----------------------------------------------------------------------*/
	/*															*/
	/*----------------------------------------------------------------------*/
	for (nLoop = 0; nLoop < _NFILE/*-3*/; nLoop++){
		PFCB	pFCB	= &fcb[nLoop];
		/*------------------------------------------------------------------*/
		/*										*/
		/*------------------------------------------------------------------*/
		if (pFCB->nBusyFlag == fcb_busy_free)
			continue;
		/*------------------------------------------------------------------*/
		/*													              */
		/*------------------------------------------------------------------*/
		if (!strncmp(szName, pFCB->szName, MAX_NAME)){
			if (!strncmp(szExt, pFCB->szExt, MAX_EXT)){
				/*----------------------------------------------------------*/
				/*					*/
				/*----------------------------------------------------------*/
				if (pFCB->nBusyFlag == fcb_busy_write){
					//ERR_MSG("FCB_OpenCheck:file busy\n");
					return(-33);
				}
				/*----------------------------------------------------------*/
				/*										*/
				/*----------------------------------------------------------*/
				nRet++;
			}
		}
	}
	return(nRet);
}

/****************************************************************************/
/*																			                                    */
/*	WORD	FCB_GetTergetCluster(int handle)								                  */
/*																			                                    */
/*	function :	Get target cluster			                                    */
/*																			                                    */
/*	input :	handle	:	file handle											                      */
/*																			                                    */
/*	output :	0 or more	:	cluster index										                  */
/*			    -1 or less	:	fail											                        */
/*																			                                    */
/****************************************************************************/
static	WORD	FCB_GetTergetCluster(int handle)
{
	DWORD	dwOffset;
	PFCB	pFCB;
	WORD	wCluster;
	pFCB	= &fcb[handle];
/*
	DBG_MSG1("FCB_GetTergetCluster(%d)\n ", handle);
*/
	/*----------------------------------------------------------------------*/
	/*----------------------------------------------------------------------*/
	dwOffset	= pFCB->dwOffset;
	wCluster	= ramFAT.dir[pFCB->nIndexOfDir].wTopCluster & 0xfff;
	while (dwOffset >= DATA_PER_CLUSTER){
		ASSERT(wCluster != FAT_EOF);
		wCluster	= ramFAT_GetNextCluster(wCluster);
		dwOffset	-= DATA_PER_CLUSTER;
	}
	return(wCluster);
}

/****************************************************************************/
/*																			                                    */
/*	int		FCB_GetNewCluster(int handle)									                    */
/*                                                                          */
/*  function: get a new  cluster                                            */
/*  input   :  file handle                                                  */
/*  output  :  0 or more: cluster index                                     */
/*             -1 or less: fail                                             */
/****************************************************************************/
static	int		FCB_GetNewCluster(int handle)
{
	int			nRet;
	WORD		wNewCluster;
	PFCB		pFCB;
	PDIRECTORY	pDir;
	for ( ; ; ) {
		if ((nRet = GetFreeCluster(TARGET_ALL)) < 0){
			return(nRet);
		}
		wNewCluster	= LOWORD(nRet);
		if ((nRet = SetClusterMark(wNewCluster, CM_BUSY, FAT_EOF)) < 0){
			continue;
		}
		break;
	}
	/*----------------------------------------------------------------------*/
	/*	                      get the file index														*/
	/*----------------------------------------------------------------------*/
	pFCB	= &fcb[handle];
	pDir	= &ramFAT.dir[pFCB->nIndexOfDir];
	if (!pDir->dwSize){
		/*------------------------------------------------------------------*/
		/*	     if the size of the file is zero,set the first cluster		  */
		/*------------------------------------------------------------------*/
		pDir->wTopCluster	= wNewCluster	/*	& 0xfff	*/;
	}else{
		/*------------------------------------------------------------------*/
		/*	   get the last cluster then link the new cluster into FAT			*/
		/*------------------------------------------------------------------*/
		WORD	wCluster	= pDir->wTopCluster & 0xfff;
		for ( ; ; ){
			WORD	wNextCluster	= ramFAT_GetNextCluster(wCluster);
			if (wNextCluster == FAT_EOF){
				ramFAT_SetNextCluster(wCluster, wNewCluster);
				break;
			}
			wCluster	= wNextCluster;
		}
	}
	return((int)wNewCluster);
}

/****************************************************************************/
/*																			*/
/*	int		SplitFileName(PCSTR pcszFilename, PSTR szName, PSTR szExt)		*/
/****************************************************************************/
static	int		SplitFileName(PCSTR pcszFilename, PSTR szName, PSTR szExt)
{
	TCHAR	szNameWork[MAX_NAME+MAX_EXT+2];
	PSTR	pszExt;
	/*----------------------------------------------------------------------*/
	/*	                       copy name string 												    */
	/*----------------------------------------------------------------------*/
	strncpy(szNameWork, pcszFilename, MAX_NAME+MAX_EXT+2);
	szNameWork[MAX_NAME+MAX_EXT+1]	= '\0';
	pszExt	= szNameWork;
	while (*pszExt){
		if (*pszExt == '.'){
			*pszExt++	= '\0';
			break;
		}
		pszExt++;
	}
	/*----------------------------------------------------------------------*/
	/*----------------------------------------------------------------------*/
	memset(szName,	0xff,		MAX_NAME);
	memset(szExt,	0xff,		MAX_EXT);
	strncpy(szName,	szNameWork,	MAX_NAME);
	strncpy(szExt,	pszExt,		MAX_EXT);
	return(0);
}

/****************************************************************************/
/*																			                                    */
/*	WORD	GetNumOfCluster(VOID)											                        */
/*                                                                          */
/*   function: get the number of the total cluster                          */
/*   input   : none                                                         */
/*   output  : the total cluster number of the disk                         */
/****************************************************************************/
static	WORD	GetNumOfCluster(VOID)
{	
	return NUM_OF_CLUSTER;
}

/****************************************************************************/
/*																			                                    */
/*	int		GetNumOfPage(VOID)												                        */
/*                                                                          */
/*  function: get the total page number of the disk                         */
/*  input   : none                                                          */
/*  output  : number of the page                                            */
/*                                                                          */
/****************************************************************************/
static	int		GetNumOfPage(VOID)
{	
	return( NUM_OF_PAGE );
}

/****************************************************************************/
/*																			                                    */
/*	int		PageFromCluster(WORD wCluster)									                  */
/*																			                                    */
/*   function: caculate the page number from cluster number                 */
/*    input  : cluster number                                               */
/*    output : page number which the cluster located                        */
/*                                                                          */
/****************************************************************************/
static	int		PageFromCluster(WORD wCluster)
{
	int		nPage;
	int		nNumOfPage	= GetNumOfPage();
	/*----------------------------------------------------------------------*/
	/*	            cluster parameter invalidation check										*/
	/*----------------------------------------------------------------------*/
	if ((0 < wCluster) && (wCluster <= GetNumOfCluster())){
		/*------------------------------------------------------------------*/
		/*	caculate the page number according to the cluster number				*/
		/*------------------------------------------------------------------*/
		for (nPage = 0; nPage < nNumOfPage; nPage++){
			if (wCluster <= GetClusterPerPage(nPage))
				return(nPage);
			wCluster	-= GetClusterPerPage(nPage);
		}
		ASSERT(0);
	}
	ERR_MSG("translate from cluster to page error\n");
	return(-1);
}

/****************************************************************************/
/*																			                                    */
/*	int		ClusterFromPage(int nPage)										                    */
/*  fcuntion:  get the starting cluster number of a page                          */
/****************************************************************************/
static	int		ClusterFromPage(int nPage)
{
	int		nLoop;
	int		nNumOfPage	= GetNumOfPage();
	WORD	wCluster;
	/*----------------------------------------------------------------------*/
	/*	if the page number is valid, get the total cluster number of a page	*/
	/*----------------------------------------------------------------------*/
	if ((0 <= nPage) && (nPage < nNumOfPage)){
		/*------------------------------------------------------------------*/
		/*------------------------------------------------------------------*/
		wCluster	= 1;
		for (nLoop = 0; nLoop < nPage; nLoop++)
			wCluster	+= GetClusterPerPage(nLoop);
		return((int)wCluster);
	}
	ERR_MSG("Error  page  number\n");
	return(-1);
}

/****************************************************************************/
/*																			                                    */
/*	int		ramFAT_GetFileIndex(const char* name)							                */
/****************************************************************************/
static	int		ramFAT_GetFileIndex(const char* name)
{
	TCHAR	szName[MAX_NAME];
	TCHAR	szExt[MAX_EXT];
	int		nIndexOfDir;
/*
	DBG_MSG1("ramFAT_GetFileIndex(\"%s\")\n", name);
*/
	/*----------------------------------------------------------------------*/
	/*	                split the file name 											          */
	/*----------------------------------------------------------------------*/
	SplitFileName(name, szName, szExt);
	/*----------------------------------------------------------------------*/
	/*	               look for the matching file														*/
	/*----------------------------------------------------------------------*/
	for (nIndexOfDir = 0; nIndexOfDir < NUM_OF_FILE; nIndexOfDir++){
		PDIRECTORY	pDir	= &ramFAT.dir[nIndexOfDir];
		if ((!strncmp(szName, pDir->szName, MAX_NAME))
		&&	(!strncmp(szExt,  pDir->szExt,  MAX_EXT)))
			return(nIndexOfDir);
	}
	/*----------------------------------------------------------------------*/
	/*	if the matching file does not exist ,return -1										  */
	/*----------------------------------------------------------------------*/
	return(-1);
}

/****************************************************************************/
/*																			                                    */
/*	WORD	ramFAT_GetNextCluster(WORD wCluster)							                */
/*																			                                    */
/****************************************************************************/
static	WORD	ramFAT_GetNextCluster(WORD wCluster)
{
	
	int		nIndex;
	WORD	wNextCluster;
	
	
	wCluster--;
	/*----------------------------------------------------------------------*/
	/*	                  get 12bitsFAT index							                  */
	/*----------------------------------------------------------------------*/
	nIndex			= wCluster + (wCluster >> 1);
	/*----------------------------------------------------------------------*/
	/*	                   get  Next  FAT postion													  */
	/*----------------------------------------------------------------------*/
	wNextCluster	= MAKEWORD(ramFAT.bFAT[nIndex + 1], ramFAT.bFAT[nIndex]);
	/*----------------------------------------------------------------------*/
	/*	       return next cluster index according to wCluster							*/
	/*----------------------------------------------------------------------*/
	return((wCluster & 1) ? (wNextCluster & 0x0fff) : (wNextCluster >> 4));
}

/****************************************************************************/
/*																			                                    */
/*	VOID	ramFAT_SetNextCluster(WORD wCluster, WORD wNextCluster)			      */
/*                                                                          */
/*  function: set the next cluster index                                    */
/*  input   : wCluster: current cluster postion                             */
/*                      which store the nex cluster number                  */
/*            wNextCluster: next cluster index                              */
/****************************************************************************/
static	VOID	ramFAT_SetNextCluster(WORD wCluster, WORD wNextCluster)
{
		int		nIndex;
/*
	DBG_MSG2("ramFAT_SetNextCluster(%04X, %04X)\n", wCluster, wNextCluster);
*/
	
	wCluster--;
	/*----------------------------------------------------------------------*/
	/*	                       get 12bitsFAT index 					                */
	/*----------------------------------------------------------------------*/
	nIndex			= wCluster + (wCluster >> 1);
	/*----------------------------------------------------------------------*/
	/*	               check whether  FAT is odd  													*/
	/*----------------------------------------------------------------------*/
	if (wCluster & 1){		
		ramFAT.bFAT[ nIndex ]		  &= 0xf0;
		ramFAT.bFAT[ nIndex ]		  |= HIBYTE(wNextCluster);
		ramFAT.bFAT[ nIndex + 1 ]	 = LOBYTE(wNextCluster);
	}else{		
		wNextCluster <<= 4;
		ramFAT.bFAT[ nIndex ]		  = HIBYTE(wNextCluster);
		ramFAT.bFAT[ nIndex + 1 ]	&= 0x0f;
		ramFAT.bFAT[ nIndex + 1 ]	|= LOBYTE(wNextCluster);
	}
	return;
}

/****************************************************************************/
/*																			                                    */
/*	int		ramFAT_Update(VOID)												                        */
/*																			                                    */
/*	function  :	update 	ram fat to flash and update the mark							  */
/*																			                                    */
/*	input :	none															                              */
/*																			                                    */
/*	return :	0		       ----	ok											                      */
/*			     -1 or less	 ----	fail											                    */
/*																			                                    */
/****************************************************************************/
static	int		ramFAT_Update(VOID)
{
	int			nIndexOfDir;
	WORD		wCluster;
	WORD		wClusterNext;
	int			nRet;
	WORD		wClusterMark;
	DWORD   wClusterAdd;
/*
	DBG_MSG("ramFAT_Update(VOID)\n");
*/
	/*----------------------------------------------------------------------*/
	/*	       release the remove file occupied cluster if found						*/
	/*----------------------------------------------------------------------*/
	for (nIndexOfDir = 0; nIndexOfDir < NUM_OF_FILE; nIndexOfDir++){
		PDIRECTORY	pDir	= &ramFAT.dir[nIndexOfDir];
		if (pDir->szName[0] == 0){
			/*--------------------------------------------------------------*/
			/*	               look for used cluster to release 						*/
			/*--------------------------------------------------------------*/
			wClusterNext	= pDir->wTopCluster & 0xfff;
			while (	(wClusterNext != FAT_FREE)
			&&		(wClusterNext != FAT_EOF)
			&&		(wClusterNext != FAT_VOID)	){
				wCluster		= wClusterNext;
				wClusterNext	= ramFAT_GetNextCluster(wCluster);
				EraseCluster(wCluster);
			}
			/*--------------------------------------------------------------*/
			/*	reset the directory slot to free(0xff)							        */
			/*--------------------------------------------------------------*/
			memset(pDir, 0xff, sizeof(DIRECTORY));
		}
	}
	/*----------------------------------------------------------------------*/
	/*	            Upadate the FAT cluster  												        */
	/*----------------------------------------------------------------------*/
	if (wFATCluster == FAT_VOID){
		wClusterMark	= CM_FAT;
	}else{
		wClusterAdd = GetClusterAddress(wFATCluster);
		SpiFlashRead( wClusterAdd, (uint8_t*)&wClusterMark, sizeof( wClusterMark ));
		wClusterMark	+= 1;
		wClusterMark	&= CM_FAT_ID;
		wClusterMark	|= CM_FAT;
	}
	/*----------------------------------------------------------------------*/
	/*	            look for a free cluster to update the fat								*/
	/*----------------------------------------------------------------------*/
	for ( ; ; ){
		/*------------------------------------------------------------------*/
		/*	                          find free cluster								      */
		/*------------------------------------------------------------------*/
		nRet	= GetFreeCluster(TARGET_ALL);
		if (nRet < 0){
			ERR_MSG("can not find free cluster to update the FAT\n");
			return(nRet);
		}
		wCluster	= LOWORD(nRet);
		/*------------------------------------------------------------------*/
		/*	                  set the ram fat mark								          */
		/*------------------------------------------------------------------*/
		if (wFATCluster != FAT_VOID){
			ramFAT_SetNextCluster(wFATCluster, FAT_VOID);
		}
		ramFAT_SetNextCluster(wCluster, FAT_FAT);
		/*------------------------------------------------------------------*/
		/*	              update ram fat mark to flash											*/
		/*------------------------------------------------------------------*/
		wClusterAdd	= GetClusterAddress(wCluster);
		if ((WordWrite( wClusterAdd, CM_BUSY ) < 0)
		||	(BufferWrite( wClusterAdd + 4, &ramFAT, sizeof(FAT)) < 0)
		||	(WordWrite( wClusterAdd, wClusterMark) < 0)){
			
			 SpiFlashRead(wClusterAdd,(uint8_t*)wClusterMark,sizeof( wClusterMark ));
			
			if (((nRet = SetClusterMark(wCluster, CM_VOID, FAT_VOID)) < 0)
			&&	(( wClusterMark & ~CM_FAT_ID) == CM_FAT)){
				ERR_MSG("Update ram fat to flash fail\n");
				return(nRet);
			}
			continue;
		}
/*
		FATINFO(&ramFAT);
		CHAININFO();
*/
		break;
	}
	/*----------------------------------------------------------------------*/
	/*	          update the old fat mark to FAT_VOID and CM_VOID						*/	
	/*----------------------------------------------------------------------*/
	if (wFATCluster != FAT_VOID){
		wClusterAdd	= GetClusterAddress(wFATCluster);
		SpiFlashRead(wClusterAdd,(uint8_t*)wClusterMark,sizeof( wClusterMark ));
		
		if (((nRet = SetClusterMark(wFATCluster, CM_VOID, FAT_VOID)) < 0)
		&&	((wClusterMark & ~CM_FAT_ID) == CM_FAT)){
			ERR_MSG("set fat cluster mark error\n");
			return(nRet);
		}
	}
	/*----------------------------------------------------------------------*/
	/*	               Update Fat cluster number										        */
	/*----------------------------------------------------------------------*/
	wFATCluster	= wCluster;
	return(0);
}

/****************************************************************************/
/*																			*/
/*	int		ramFAT_GetFreeDirectory(VOID)									*/
/****************************************************************************/
static	int		ramFAT_GetFreeDirectory(VOID)
{
	int		nIndex;
/*
	DBG_MSG("ramFAT_GetFreeDirectory(VOID)\n");
*/
	/*----------------------------------------------------------------------*/
	/*	       if the szName is 0xff return the slot										    */
	/*----------------------------------------------------------------------*/
	for (nIndex = 0; nIndex < NUM_OF_FILE; nIndex++){
		if (ramFAT.dir[nIndex].szName[0] == (TCHAR)0xff){
			return(nIndex);
		}
	}
	/*----------------------------------------------------------------------*/
	/*	      can not alloc the slot return -82										          */
	/*----------------------------------------------------------------------*/
	ERR_MSG("ramFAT_GetFreeDirectory:can not allocate the file slot\n");
	return(-82);
}

/****************************************************************************/
/*																			*/
/*	int		ByteWrite(PBYTE pbAdr, BYTE bData)								*/
/****************************************************************************/
static	int		ByteWrite(DWORD pbAdr, BYTE bData)
{
	return(BufferWrite(pbAdr, &bData, sizeof(BYTE)));
}

/****************************************************************************/
/*	int		WordWrite(PWORD pwAdr, WORD wData)								                */
/****************************************************************************/
static	int		WordWrite(DWORD pwAdr, WORD wData)
{
	return(BufferWrite(pwAdr, &wData, sizeof(WORD)));
}

/****************************************************************************/
/*																			                                    */
/*	int		DwordWrite(PDWORD pdwAdr, DWORD dwData)							              */
/*																			                                    */
/*	funciton :	write 4 bytes to memory												              */
/*																			                                    */
/*	input :	pdwAdr	:	flash memory address(DwordWrite)							        */
/*			    dwData	:	data to be written(DwordWrite)							          */
/*																			                                    */
/*	return :	0		:	suceed											                            */
/*			      less 0	:	fail											                          */
/*																			                                    */
/****************************************************************************/
static	int		DwordWrite(DWORD  pdwAdr, DWORD dwData)
{
	return(BufferWrite(pdwAdr, &dwData, sizeof(DWORD)));
}

/****************************************************************************/
/*																			                                    */
/*	int		BufferWrite(PVOID pvDest, PCVOID pcvSrc, unsigned int nCount)	    */
/****************************************************************************/
static	int		BufferWrite(DWORD pvDest, PCVOID pcvSrc, unsigned int nCount)
{
	
	  if( SpiFlashWrite( pvDest, (uint8_t*)pcvSrc, nCount) < 0 ){
		/*------------------------------------------------------------------*/
		/*	if fail reset the flash						                              */
		/*------------------------------------------------------------------*/
		ERR_MSG3("BufferWrite(%08lX, %08lX, %d)\n", pvDest, pcvSrc, nCount);
		ERR_MSG("write to flash error\n");
		ASSERT(0);
		return(-29);
	}
	return(0);
}

/****************************************************************************/
/*																			*/
/*	int		CleanupCluster(BOOL bBusyCluster)								*/
/****************************************************************************/
static	int		CleanupCluster(BOOL bBusyCluster)
{
		int			nIndexOfDir;
		WORD		wCluster;
		int			nUpdateFlag	= 0;
	  uint32_t ClusterAdd;
	  
    BYTE		bClusterChain[ NUM_OF_CLUSTER ];
/*
	DBG_MSG(bBusyCluster ? "CleanupCluster(TRUE)\n" : "CleanupCluster(FALSE)\n");
*/
	/*----------------------------------------------------------------------*/
	/*----------------------------------------------------------------------*/
Restart:
	memset(bClusterChain, 0, sizeof(bClusterChain));
	if (wFATCluster != FAT_VOID)
		bClusterChain[wFATCluster-1]++;
	
	for (nIndexOfDir = NUM_OF_FILE - 1; nIndexOfDir >= 0; nIndexOfDir--){
		PDIRECTORY	pDir	= &ramFAT.dir[nIndexOfDir];
		switch (pDir->szName[0]){
			case	0:		/*	file has been removed	*/
			case	0xff:	/*	not use,free	*/
				break;
			default:		/*	file exist	*/
				wCluster	= pDir->wTopCluster & 0xfff;
				if (wCluster == FAT_FREE)
					break;
				while (wCluster != FAT_EOF){
					WORD wClusterMark;
					ClusterAdd = GetClusterAddress(wCluster);
					SpiFlashRead( ClusterAdd, (uint8_t*)&wClusterMark, sizeof(wClusterMark));
					switch ( wClusterMark/*GetClusterAddress(wCluster)->wClusterMark*/ ){
						case	CM_DATA:
							break;
						case	CM_BUSY:
							if (bBusyCluster)
								break;
						default:
							CLUSTERINFO(wCluster);							
							pDir->szName[0]	= 0;
							nUpdateFlag		= 1;
							goto	Restart;
					}
					if (bClusterChain[wCluster-1]++){						
						return(-23);
					}
					wCluster	= ramFAT_GetNextCluster(wCluster);
				}
				break;
		}
	}
	/*----------------------------------------------------------------------*/
	/*	                Erase the void cluster								              */
	/*----------------------------------------------------------------------*/
	for (wCluster = GetNumOfCluster(); wCluster > 0; wCluster--){
		if (!bClusterChain[wCluster-1]){
			WORD	wClusterMark;
			ClusterAdd = GetClusterAddress( wCluster );
			SpiFlashRead( ClusterAdd, (uint8_t*)&wClusterMark, sizeof( wClusterMark ));
			if (wClusterMark != CM_FREE){
				int		nRet;
				if (wClusterMark != CM_VOID){
					nUpdateFlag	= 1;
				}
				nRet	= EraseCluster(wCluster);
				if (nRet == 1){
					nUpdateFlag	= 1;
				}else if (nRet < 0){
					ERR_MSG("Erase cluster error\n");					
				}
			}else{
				if (ramFAT_GetNextCluster(wCluster) != FAT_FREE){
					nUpdateFlag	= 1;
					SetClusterMark(wCluster, CM_FREE, FAT_FREE);
				}
			}
		}
	}
	return(nUpdateFlag);
}

/****************************************************************************/
/*	int		SetClusterMark(WORD wCluster, WORD wMark, WORD wFATData);		*/
/****************************************************************************/
static	int		SetClusterMark(WORD wCluster, WORD wMark, WORD wFATData)
{
	/*PCLUSTER	pCluster	= GetClusterAddress(wCluster);*/
	DWORD ClusterAdd = GetClusterAddress(wCluster);
	 
/*
	DBG_MSG3("SetClusterMark(0x%04X, 0x%04X, 0x%04X)\n", wCluster, wMark, wFATData);
	CLUSTERINFO(wCluster);
*/
	
	if (wFATData == FAT_FREE){
		/*------------------------------------------------------------------*/
		/*	if the mark is FAT_FREE,the data should be 0xffffffff						*/
		/*  if not change to FAT_VOID and CM_VOID,then set again            */
		/*   call ramFAT_SetNextCluster directly and return ok              */
		/*------------------------------------------------------------------*/
		DWORD	pdwCheck	;
	  SpiFlashRead(ClusterAdd, (uint8_t*)&pdwCheck, sizeof( pdwCheck ) );
		if ( pdwCheck != 0xffffffff ){				
				wMark		= CM_VOID;
				wFATData	= FAT_VOID;
				goto NotFreeCluster;
			}
		
		ramFAT_SetNextCluster(wCluster, wFATData);
		return(0);
	}
NotFreeCluster:
	/*----------------------------------------------------------------------*/
	/*	                  set the ram FAT mark													    */
	/*----------------------------------------------------------------------*/
	ramFAT_SetNextCluster(wCluster, wFATData);
	/*----------------------------------------------------------------------*/
	/*	           write the mark to spi cluster												    */
	/*----------------------------------------------------------------------*/
	if (WordWrite( ClusterAdd, wMark) < 0){
		/*------------------------------------------------------------------*/
		/*	           if write cluster mark to flash fail                  */
		/* set the corespoding ram fat to FAT_VOID,cluster mark to CM_VOID  */
		/*------------------------------------------------------------------*/
		ERR_MSG("SetClusterMark:write cluster mark to flash fail\n");
		ramFAT_SetNextCluster( wCluster, FAT_VOID );
		WordWrite( ClusterAdd, CM_VOID );
		return(-29);
	}
	return(0);
}

/****************************************************************************/
/*	                   int		EraseCluster(WORD wCluster)										*/
/*  function: Erase a cluster ,if the cluster all void ,erase the page      */
/*            else set the specified cluster to void cluster                */
/*  input : cluster                                                         */
/*  output: 0 or more-------succed                                          */
/*          0 less   -------fail                                            */
/****************************************************************************/
static	int		EraseCluster(WORD wCluster)
{
	int		nPage;
	int		nLoop;
	int		nRet;
/*
	DBG_MSG1("EraseCluster(0x%04X)\n", wCluster);
*/
	/*----------------------------------------------------------------------*/
	/*     set the cluste in fat to FAT_VOID and cluster mark to CM_VOID    */
	/*----------------------------------------------------------------------*/
	SetClusterMark(wCluster, CM_VOID, FAT_VOID);
	/*----------------------------------------------------------------------*/
	/*if the clusters in the page are not all FAT_VOID,discard and return 0	*/
	/*----------------------------------------------------------------------*/
	nPage		= PageFromCluster(wCluster);
	wCluster	= ClusterFromPage(nPage);
	for (nLoop = GetClusterPerPage(nPage); nLoop > 0; nLoop--){
		if (ramFAT_GetNextCluster(wCluster) != FAT_VOID)
			return(0);
		wCluster++;
	}
	/*----------------------------------------------------------------------*/
	/*	then erase the page and return the result			                      */
	/*----------------------------------------------------------------------*/
	nRet = ErasePage(nPage);
	return(nRet ? nRet : 1);
}

/****************************************************************************/
/****************************************************************************/
static	int		ErasePage(int nPage)
{
	int		nLoop;
	WORD	wCluster;
	DWORD	dwRewriteCounter;	
	DWORD PageAdd = GetPageAddress( nPage );
	/*----------------------------------------------------------------------*/
  /*      read from flash to get the current dwRewriteCounter             */   
	/*----------------------------------------------------------------------*/
	SpiFlashRead( ( PageAdd ), ( uint8_t* )&dwRewriteCounter, sizeof( dwRewriteCounter ) );

/*	
	DBG_MSG1("ErasePage(%ld)\n", nPage);
*/  
	/*----------------------------------------------------------------------*/
	/*	Erase the specified page if fail return -29												  */
	/*----------------------------------------------------------------------*/	
	
	if( SpiFlashErase( PageAdd , SIZE_64K ) < 0){
		ERR_MSG("Erase page error\n");
		return(-29);
	}
	
	/*----------------------------------------------------------------------*/
	/*    inc  dwRewriteCounter then write to the page again                */
	/*----------------------------------------------------------------------*/
  dwRewriteCounter++;
  DwordWrite( PageAdd , dwRewriteCounter );
	/*----------------------------------------------------------------------*/
	/*	then set the FatMark to FAT_FREE and the cluster	mark to CM_FREE		*/
	/*----------------------------------------------------------------------*/
	wCluster	= ClusterFromPage(nPage);
	for (nLoop = GetClusterPerPage(nPage); nLoop > 0; nLoop--){
		SetClusterMark(wCluster, CM_FREE, FAT_FREE);
		wCluster++;
	}
	return(0);
}

/****************************************************************************/
static	int		GetFreeCluster(int nFlag)
{
	int		nPage;
	int		nNumOfPage		= GetNumOfPage();
	DWORD	dwMinRewrite	= 0;
/*
	DBG_MSG(nFlag == TARGET_LO_VOID ? "GetFreeCluster(TARGET_LO_VOID)\n" : "GetFreeCluster(TARGET_ALL)\n");
*/

	for ( ; ; ){
		/*------------------------------------------------------------------*/
		/*------------------------------------------------------------------*/
		DWORD	dwSearchRewrite ;
		dwSearchRewrite	= 0;
		dwSearchRewrite--;				/*	dwSearchRewrite	= (DWORD)-1		*/
		for (nPage = 0; nPage < nNumOfPage; nPage++){
			DWORD	dwRewrite;			
			SpiFlashRead( GetPageAddress( nPage ), (uint8_t*)&dwRewrite, sizeof( dwRewrite ) );
			if (dwMinRewrite <= dwRewrite){
				dwSearchRewrite	= min(dwSearchRewrite, dwRewrite);
			}
		}
		/*------------------------------------------------------------------*/
		/*------------------------------------------------------------------*/
		if ( !(dwSearchRewrite + 1 )){		
			switch (nFlag){
				case	TARGET_LO_VOID:
					return(GetFreeCluster(TARGET_ALL));
				case	TARGET_ALL:
					ERR_MSG("can not get free cluster\n");					
					return(-39);
			}
		}
		/*------------------------------------------------------------------*/
		/*------------------------------------------------------------------*/
		for (nPage = 0; nPage < nNumOfPage; nPage++){
			DWORD	dwRewrite;
			
			SpiFlashRead(GetPageAddress(nPage), (uint8_t*)&dwRewrite, sizeof( dwRewrite ) );//modifyied
			
			if (dwSearchRewrite == dwRewrite){
				int		nLoop;
				WORD	wCluster		= ClusterFromPage(nPage);
				int		nVoidCount		= 0;
				WORD	wFreeCluster	= 0;
				switch (nFlag){					
					case	TARGET_LO_VOID:
						for (nLoop = GetClusterPerPage(nPage); nLoop > 0; nLoop--){
							switch (ramFAT_GetNextCluster(wCluster)){
								case	FAT_FREE:
									if (!wFreeCluster)
										wFreeCluster	= wCluster;
									break;
								case	FAT_VOID:
									nVoidCount++;
									break;
							}
							wCluster++;
						}
						if ((wFreeCluster)
						&&	(nVoidCount < (GetClusterPerPage(nPage) >> 2))){
							return((int)wFreeCluster);
						}
						break;
					/*------------------------------------------------------*/
					/*------------------------------------------------------*/
					case	TARGET_ALL:
						for (nLoop = GetClusterPerPage(nPage); nLoop > 0; nLoop--){
							if (ramFAT_GetNextCluster(wCluster) == FAT_FREE){
								return((int)wCluster);
							}
							wCluster++;
						}
						break;
				}
			}
		}
		/*------------------------------------------------------------------*/
		/*------------------------------------------------------------------*/
		dwMinRewrite	= dwSearchRewrite + 1;
	}
}

/****************************************************************************/
/*																			                                    */
/*	int		VoidClusterFree(VOID)											                        */
/*																			                                    */
/*	function :	free void cluster							*/
/*																			*/
/*	input :	None															*/
/*																			*/
/*	return :	0		  :	succeed											*/
/*			-1 or less 	:	fail											*/
/*																			*/
/****************************************************************************/  
static	int		VoidClusterFree(VOID)
{
	int		nRet;
	int		nPage;
	int		nNumOfPage	= GetNumOfPage();
	int		nLoop;
	BYTE	bWeightRewrite[NUM_OF_PAGE];
	BYTE	bWeightVoid[NUM_OF_PAGE];
	BYTE	bCountFree[NUM_OF_PAGE];
	int		nFreePage;
	WORD	wFreeCluster;
	
	DWORD wFreeClusterAdd ;
	DWORD wNewClusterAdd ;
	BYTE  buffer[ 512 ];
	
/*
	DBG_MSG("VoidClusterFree(VOID)\n");
*/
	/*----------------------------------------------------------------------*/
	/*																		*/
	/*----------------------------------------------------------------------*/
	for ( ; ; ){
		/*------------------------------------------------------------------*/
		/*         get all page rewrite,each page void /free cluster        */
		/*------------------------------------------------------------------*/
		memset(bWeightRewrite, 0, sizeof(bWeightRewrite));
		memset(bWeightVoid, 0, sizeof(bWeightVoid));
		memset(bCountFree, 0, sizeof(bCountFree));
		for (nPage = nNumOfPage - 1; nPage >= 0; nPage--){
			DWORD		dwRewrite	= GetPageRewriteCounter(nPage);
			wFreeCluster	= ClusterFromPage(nPage);
			/*--------------------------------------------------------------*/
			/*--------------------------------------------------------------*/
			for (nLoop = nNumOfPage - 1; nLoop > nPage; nLoop--){
				if (dwRewrite < GetPageRewriteCounter(nLoop)){
					bWeightRewrite[nLoop]++;
				}else{
					bWeightRewrite[nPage]++;
				}
			}
			
			for (nLoop = GetClusterPerPage(nPage); nLoop > 0; nLoop--){
				switch (ramFAT_GetNextCluster(wFreeCluster)){
					case	FAT_FREE:
						bCountFree[nPage]++;
						break;
					case	FAT_VOID:
						bWeightVoid[nPage]++;
						break;
				}
				wFreeCluster++;
			}
			
			nLoop	= GetClusterPerPage(nPage);
			while (nLoop < CLUSTER_PER_PAGE64K){
				nLoop				<<= 1;
				bWeightVoid[nPage]	<<= 1;
			}
		}
		
		{
			BYTE	bFreeWeightRewrite	= 0;
			BYTE	bFreeCountFree		= (BYTE)-1;
			nFreePage	= -1;
			for (nPage = nNumOfPage - 1; nPage >= 0; nPage--){
				if (bWeightVoid[nPage] >= (CLUSTER_PER_PAGE64K / 4)){
					if ((nFreePage < 0)
					||	(bFreeWeightRewrite > bWeightRewrite[nPage])
					||	((bFreeWeightRewrite == bWeightRewrite[nPage])
					&&	 (bFreeCountFree > bCountFree[nPage]))){
						nFreePage			= nPage;
						bFreeWeightRewrite	= bWeightRewrite[nPage];
						bFreeCountFree		= bCountFree[nPage];
					}
				}
			}
			if (nFreePage < 0)
				break;
		}
		
		wFreeCluster	= ClusterFromPage(nFreePage);
		for (nLoop = GetClusterPerPage(nFreePage); nLoop > 0; nLoop--){
			if (ramFAT_GetNextCluster(wFreeCluster) == FAT_FREE){
				ramFAT_SetNextCluster(wFreeCluster, FAT_VOID);
			}
			wFreeCluster++;
		}
		/*------------------------------------------------------------------*/
		/*------------------------------------------------------------------*/
		wFreeCluster	= ClusterFromPage(nFreePage);
		for (nLoop = GetClusterPerPage(nFreePage); nLoop > 0; nLoop--){
			WORD	wNewCluster;
			int		nLoop2;
			switch (ramFAT_GetNextCluster(wFreeCluster)){
				
				case	FAT_FREE:
				case	FAT_VOID:
				case	FAT_FAT:
					break;
				
				default:
					if ((nRet = GetFreeCluster(TARGET_LO_VOID)) < 0){
						ERR_MSG("VoidClusterFree:Get free cluster fail\n");
						return(nRet);
					}
					wNewCluster	= LOWORD(nRet);
					/*-------------------------------------------------------------------*/
					/*                     cluster copy                                     */
					/*-------------------------------------------------------------------*/	          			
					 wFreeClusterAdd = GetClusterAddress(wFreeCluster);
					 wNewClusterAdd = GetClusterAddress(wNewCluster);
					
					SpiFlashRead( wFreeClusterAdd, buffer, sizeof(buffer));
					BufferWrite(  wNewClusterAdd,  buffer, sizeof(buffer));
					
					SpiFlashRead( wFreeClusterAdd + sizeof(buffer) ,    buffer, sizeof(buffer));
					BufferWrite(  wNewClusterAdd  + sizeof(buffer) ,    buffer, sizeof(buffer));
					
					SpiFlashRead( wFreeClusterAdd + sizeof(buffer) * 2, buffer, sizeof(buffer));
					BufferWrite(  wNewClusterAdd  + sizeof(buffer) * 2, buffer, sizeof(buffer));					
					
					
					SpiFlashRead( wFreeClusterAdd + sizeof(buffer) * 3, buffer,  (sizeof(CLUSTER)) % 512 );
					BufferWrite(  wNewClusterAdd  + sizeof(buffer) * 3, buffer,  (sizeof(CLUSTER)) % 512 );
					
					
					/*------------------------------------------------------*/
					/*------------------------------------------------------*/
					for (nLoop2 = NUM_OF_FILE-1; nLoop2 >= 0; nLoop2--){
						if ((ramFAT.dir[nLoop2].wTopCluster & 0xfff) == wFreeCluster){
							ramFAT.dir[nLoop2].wTopCluster	= wNewCluster		& 0xfff	;
						}
					}
					/*------------------------------------------------------*/
					/*------------------------------------------------------*/
					for (nLoop2 = GetNumOfCluster(); nLoop2 > 0; nLoop2--){
						if (wFreeCluster == ramFAT_GetNextCluster(LOWORD(nLoop2))){
							ramFAT_SetNextCluster(LOWORD(nLoop2), wNewCluster);
							break;
						}
					}
					/*------------------------------------------------------*/
					/*------------------------------------------------------*/
					ramFAT_SetNextCluster(wNewCluster, ramFAT_GetNextCluster(wFreeCluster));
					/*------------------------------------------------------*/
					/*------------------------------------------------------*/
					ramFAT_SetNextCluster(wFreeCluster, FAT_VOID);
					break;
			}
			wFreeCluster++;
		}
		/*------------------------------------------------------------------*/
		/*------------------------------------------------------------------*/
		if ((nRet = ramFAT_Update()) < 0)
			return(nRet);
		/*------------------------------------------------------------------*/
		/*------------------------------------------------------------------*/
		if ((nRet = ErasePage(nFreePage)) < 0)
			return(nRet);
	}
	return(0);
}


/****************************************************************************/
static	VOID	Dir(PFAT pFAT)
{
	int			nFileNum	= 0;
	DWORD		dwTotalSize	= 0;
	int			nIndexOfDir;
	PDIRECTORY	pDir;
	printf("%08lX directory data.\n", pFAT);
	for (nIndexOfDir = 0; nIndexOfDir < NUM_OF_FILE; nIndexOfDir++){
		pDir	= &pFAT->dir[nIndexOfDir];
		if ((pDir->szName[0] != 0)
		&&	(pDir->szName[0] != -1)){
			TCHAR	szWork[32];
			printf("[%2d]", nIndexOfDir);
			memcpy(szWork, pDir->szName, MAX_NAME);
			szWork[MAX_NAME]	= '\0';
			strcat(szWork, "        ");
			szWork[MAX_NAME]	= '\0';
			printf(" %s", szWork);
			memcpy(szWork, pDir->szExt, MAX_EXT);
			szWork[MAX_EXT]	= '\0';
			strcat(szWork, "   ");
			szWork[MAX_EXT]	= '\0';
			printf(" %s", szWork);
			printf(" %12ld  ", pDir->dwSize);
			nFileNum++;
			dwTotalSize	+= pDir->dwSize;
			printf ((pDir->bAttrib & __A_RDONLY)	? "R" : " ");
			printf ((pDir->bAttrib & __A_HIDDEN)	? "H" : " ");
			printf ((pDir->bAttrib & __A_SYSTEM)	? "S" : " ");
			printf ((pDir->bAttrib & __A_VOLID)		? "V" : " ");
			printf ((pDir->bAttrib & __A_SUBDIR)	? "D" : " ");
			printf ((pDir->bAttrib & __A_ARCH)		? "A\n" : " \n");
		}
	}
	DBG_MSG2("%10d File<s> %11ld bytes\n", nFileNum, dwTotalSize);
	DBG_MSG1("%30ld bytes free\n", b_file_getdiskfree());
}

/****************************************************************************/
//does not need modify
static	VOID	FatStatus(VOID)
{
	WORD	wNumOfCluster	= GetNumOfCluster();
	WORD	wCluster;
	for (wCluster = 1; wCluster <= wNumOfCluster; wCluster++){
		switch (ramFAT_GetNextCluster(wCluster)){
			case	FAT_FREE:	printf("_");	break;
			case	FAT_FAT:	printf("F");	break;
			case	FAT_EOF:	printf("e");	break;
			case	FAT_VOID:	printf("X");	break;
			default:			  printf("o");	break;
		}
		if (!(wCluster & 0x1f)){
			printf("\n");
		}
	}
}

/****************************************************************************/
/*																			                                    */
/*	VOID	ClusterStatus(VOID)												                        */
/*																			                                    */
/*	function :	print the status of the cluster					                    */
/*																			                                    */
/*	input :	none															                              */
/*																			                                    */
/*	output:	none															                              */
/*																			                                    */
/****************************************************************************/
static	VOID	ClusterStatus(VOID)
{
	WORD	wNumOfCluster	= GetNumOfCluster();
	WORD	wCluster;
	for (wCluster = 1; wCluster <= wNumOfCluster; wCluster++){
		switch ( GetClusterMark( wCluster )/*GetClusterAddress(wCluster)->wClusterMark*/){
			case	CM_FREE:	printf("_");	break;
			case	CM_BUSY:	printf("B");	break;
			case	CM_DATA:	printf("o");	break;
			case	CM_VOID:	printf("X");	break;
			default:				printf("F");	break;
		}
		if (!(wCluster & 0x1f)){
			printf("\n");
		}
	}
}

/******************************************************************/
/*                                                                */
/*    WORD GetClusterMark( WORD cluster)                          */
/*                                                                */
/*  function: get  cluster mark of the specified cluster          */
/*  input: cluster number                                         */
/*  output: cluster mark                                          */
/*          -1:     fail                                          */
/*          other:  ok                                            */
/*                                                                */
/******************************************************************/
static WORD GetClusterMark( WORD cluster)
{
	WORD wClusterMark;
	
	if( SpiFlashRead( GetClusterAddress( cluster ), (uint8_t*)&wClusterMark, sizeof( wClusterMark )) < 0 )
		return -1;
	return wClusterMark;
	
}

/****************************************************************************/
/*																			                                    */
/*	VOID	PageStatus(VOID)												                          */
/*                                                                          */
/*  function: print page status                                             */
/*  input   : none                                                          */
/*  output  : none                                                          */
/*                                                                          */
/****************************************************************************/
static	VOID	PageStatus(VOID)
{
	int		nNumOfPage	= GetNumOfPage();
	DWORD dwRewriteCounter;
	
	int		nLoop;
	for (nLoop = 0; nLoop < nNumOfPage; nLoop++){
		SpiFlashRead( GetPageAddress(nLoop), (uint8_t*)&dwRewriteCounter, sizeof( dwRewriteCounter ) );
		DBG_MSG2("Page[%2d] dwRewriteCounter:%08lX\n", nLoop, dwRewriteCounter);
	}
}


/****************************************************************************/
/*																			                                    */
/*	int		GetFileName(void)												                          */
/*                                                                          */
/****************************************************************************/
static	int	GetFileName(PFAT pFAT,  F_NAME* pName)
{
	int			nFileNum	= 0;
	DWORD		dwTotalSize	= 0;
	int			nIndexOfDir;
	PDIRECTORY	pDir;

/*	DBG_MSG1("%08lX directory data.\n", pFAT);
		DBG_MSG1("%08lX address data.\n", pName);
*/
	for (nIndexOfDir = 0; nIndexOfDir < NUM_OF_FILE; nIndexOfDir++){
		pDir	= &pFAT->dir[nIndexOfDir];
		if ((pDir->szName[0] != 0) && (pDir->szName[0] != -1)){
			TCHAR	szWork[32];
			int	loop_ctr;
/*
			DBG_MSG1("[%2d]", nIndexOfDir);
*/			
			for (loop_ctr=0;loop_ctr<MAX_NAME;loop_ctr++){
				if (pDir->szName[loop_ctr]=='\0'||pDir->szName[loop_ctr]==' ' ){
					szWork[loop_ctr] = ' ';
				}
				else{
					szWork[loop_ctr] = pDir->szName[loop_ctr];
				}
			}
			szWork[MAX_NAME]	= '.';
			for (loop_ctr=1;loop_ctr<MAX_EXT+1;loop_ctr++){
				szWork[MAX_NAME+loop_ctr] = pDir->szExt[loop_ctr-1];
			}
			szWork[MAX_NAME+MAX_EXT+1] = '\0';
			/*----------------------*/
			/*	copy file name	    */
			/*----------------------*/
			memcpy(pName->file_info[nFileNum].file_name ,szWork, MAX_NAME+MAX_EXT+1);

/*			
			DBG_MSG1(" %s  ", szWork );
			DBG_MSG1(" %12ld  \n", pDir->dwSize);
*/
			
			pName->file_info[nFileNum].file_size = pDir->dwSize;

			nFileNum++;
			dwTotalSize	+= pDir->dwSize;
		}
	}
	
	
	pName->File_Count = nFileNum;
	pName->Total_Size = dwTotalSize;

/*	
	DBG_MSG2("%10d File<s> %11ld bytes\n", nFileNum, dwTotalSize);
	DBG_MSG1("%30ld bytes free\n", b_file_getdiskfree());
*/
	return( 0 );

}


static DWORD GetPageRewriteCounter( WORD nPage )
{
	DWORD RewriteCounter;
	
	if( SpiFlashRead( GetPageAddress( nPage ), ( uint8_t* )&RewriteCounter, sizeof(  RewriteCounter ) ) < 0 )
		return -1;
	
	return RewriteCounter;
}

