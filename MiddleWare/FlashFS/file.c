//#include <stdio.h>
#include <string.h>
#include "file.h"

#define FREERTOS   0

static int Flopen(const char* name, const char* mode, char* _ioflag);
static int stricmp(const char* str1, const char* str2);
static void* Malloc(size_t size);
static void Free(void* ptr);
static char* Sbrk( unsigned long size);

#define WRITE_ERROR 0x01
#define CLOSE_ERROR 0x02
#define RAM_END 0x7FFFFFFF
#define _EOL    (0X0A)                  /* end of line                 */

struct __FILE   _iob[_NFILE];
extern int		BiosEntry(int R0, int R1, int R2, int R3);

#if FREERTOS == 0

#define SIZE_1K 1024
const int _sbrk_size = SIZE_1K;

struct Header{
	unsigned long len;
	struct Header* next;
};

unsigned char heap_area[0x800];

static struct Header* freeptr = 0;

static unsigned char* brk = heap_area;
#endif


unsigned char sml_buf[_NFILE];


//???????? 1K,?????????????,??????


FILE* Fopen(const char* name, const char* mode)
{
    int fd;
    FILE* fp;
    //?? FILE ????,???? FILE ??
    for( fp = _iob; fp < _iob + _NFILE; fp++ )
      if( !( fp->_ioflag1 & ( _IOREAD | _IOWRITE | _IORW ) ) )
         break;

	 //????,?? NULL
	if( fp >= ( _iob + _NFILE ) ){
	    return NULL;
	}
    
	//?? flopen ????
    fd = Flopen(name, mode, (char*)&fp->_ioflag1 );

	//??
    if( fd < 0 ){
       fp->_ioflag1 = 0x00;
       return NULL;
    }
	
	fp->_iofd = fd;
	fp->_bufbase = NULL;
	fp->_bufptr = NULL;
	fp->_buflen = 0;
	fp->_bufcnt = 0;
	fp->_ioflag2 = 0;
	return fp;
}




int Open(const char* name, int mode)
{
	int handle;
	int file_mode ;
	int handle1;
	
//stdin,stdout,stderr ? FILE ???? 0,1,2,?? stdin ?????,???????
  /*  if( !stricmp( name, "stdin" ) ) {
      if( mode == O_RDONLY ){
        return 0;
      }else{
         return -1;
        }
    }
	
	if( !stricmp( name, "stdout" ) ){
	   if( mode == O_WRONLY ) {
	     return 0;
	    } else {
	       return -1;
	    }
	}

	if( !stricmp( name, "stderr" ) ){
	    if( mode == O_WRONLY ){
	       return 0;
	    } else {
	       return -1;
	    }
	}*/
	
    file_mode = mode & ( O_RDONLY | O_WRONLY | O_RDWR );
//???????,?? O_TRUNC ? O_CREAT,?????
	if( file_mode == O_RDONLY ) {
	    if( mode & ( O_TRUNC | O_CREAT ) ){
	       return -1;
	    }

    //????????,????
    handle = BiosEntry( (int)name, CODE_READ_ONLY, 0x00, FILE_OPEN );
		if( handle < 0){//??????,??-1
		   return -1;
		}
	   /* handle += 3;*///?? stdin stdout stderr ????
//  flmode[ handle ] = mode;//??????
        return handle;
    }
	
//????????,???????? 1 ?,????O_RDONLY ??? O_WRONLY,???	
	if( file_mode != O_WRONLY ) {
        return -1;
    } else {//?,????????????,??,????????,????,?????,????? O_CREAT ??,????-1,????????
	   handle = BiosEntry( (int)name, CODE_READ_ONLY, 0x00, FILE_OPEN );
	   if( handle >= 0 ) {
	      BiosEntry( handle , 0x00, 0x00, FILE_CLOSE );
	    } 
	}
	
	if( !( mode & O_CREAT ) ) {//?? O_CREAT ???????,???-1
		if( handle < 0 ) {
		   return -1;
	    }
    }
	
//O_TRUNC ? O_APPEND ?????,?????,????????????????? O_TRUNC ? O_APPEND ??????
	if( !( mode & ( O_TRUNC | O_APPEND ) ) ) {
		return -1;
	}
//????????,????? O_TRUNC ??,????????
	if( handle >= 0 ){
//L153,? O_TRUNC,? L42,?? L154
		if( ( mode & O_TRUNC ) ){ 
			handle1 = BiosEntry( (int)name, 0x00, 0x00, FILE_REMOVE );
			if( handle1 < 0 ){
				return -1;
			}
		} 
	}
	
//???????????????,?????,????????????
    if( handle < 0 || handle1 >= 0 ){
           handle = BiosEntry( (int)name, __A_ARCH, 0x00, FILE_CREATE );//????????R5 ?????? 0x20(__A_ARCH),?????
    } else {
           handle = BiosEntry( (int)name, CODE_WRITE_ONLY, 0x00, FILE_OPEN );
    }
	
//?????????,??-1
   if( handle < 0 )
      return -1;
  
   if( mode & O_APPEND ){  //???O_APPEND??,???FILE_SEEK???????
      BiosEntry( handle, 0x00, SEEK_END, FILE_LSEEK );//offset = 0 , base =SEEK_END
    }
	  
    //handle += 3;//?? stdin stdout, stderr
    //  flmode[ handle ] = mode;//????????
    return handle;
}


static int Flopen(const char* name, const char* mode, char* _ioflag)
{
	int param_num;
	char param[4] = {0x00,0x00,0x00,0x00};
	const char* ptr;
	int handle;
	int flags ;

	param_num = 0;
	
	ptr = mode;
	
	while( *ptr ){
		param[ param_num++ ] = *ptr++;
	}
	
//??????? 1-3
	if( ( param_num > 3 ) || ( param == 0 ) ){
		return -1;
	}
	
//????????'a','w','r'
	if( param_num >= 1 ){
		switch( param[ 0 ] ){
			case 'r':break;
			case 'w':break;
			case 'a':break;
			default:return -1;
		}
	}
	
//????????'+','b'
	if( param_num >= 2 ){
		if( param[ 1 ] == '+' ){
			*_ioflag |= _IORW;
		}else if( param[ 1 ] == 'b' ){
			*_ioflag |= _IOBIN;
	//?????'b',?????????????,?? param[1]????????
			param[ 1 ] = 0x00;
        }else {
          return -1;
       }
    }
	
     //????????'b'
    if( param_num == 3 ){
      if( param[ 2 ] == '+' ){
        *_ioflag |= _IOBIN;
        param[ 2 ] = 0x00;
      }else{		  
         return -1;
      }
    }
    
	flags = 0;//open ????? flags ??? 0


    if( !stricmp(param, "r" ) ){
			*_ioflag |= _IOREAD;
			flags |= O_RDONLY;
		}
	
		if( !stricmp( param, "w" ) ){
				*_ioflag |= _IOWRITE;
				flags |= ( O_TRUNC | O_CREAT | O_WRONLY );
		}
	
		if( !stricmp( param, "a" ) ) {
				*_ioflag |= _IOWRITE;
				flags |= ( O_APPEND | O_CREAT | O_WRONLY );
		}
	
		if( !stricmp( param, "r+" ) ){
				flags |= O_RDWR;
		}
	
		if( !stricmp( param, "w+" ) ){
				flags |= ( O_TRUNC | O_CREAT | O_RDWR );
		}
	
		if( !stricmp(param, "a+" ) ){
			 flags |= ( O_APPEND | O_CREAT | O_RDWR );
		}
	
	handle = Open( name, flags);
	
	if( handle < 0 ){
	   *_ioflag = 0x00;//????,? FILE ?????_ioflag1 ? 0,???? FILE
	   return -1;
	}
	
    return handle;
}

static int stricmp(const char* str1, const char* str2)
{
    char a;
    char b;
	
	while(1) {
	    a = *str1++;
	    b = *str2++;
	    if( ( a >= 'A' ) && ( a <= 'Z' ) )
	        a += 0x20;
	    if( ( b >= 'A' ) && ( b <= 'Z' ) )
	        b += 0x20;
	    if( ( !a ) || ( a != b ) )
	        return a - b;
	}
}


int Write( int handle, const void* buf, size_t len)
{
	int result;
	
	if( handle >= _NFILE || handle < 0 )
		return -1;
	
	result = BiosEntry( handle /*- 3*/ , (int)buf, len , FILE_WRITE );
	if( result < 0 )
       return -1;
   
    return result;
}

int Close( int handle )
{
	if( ( handle < 0 ) || ( handle >= _NFILE ) )
		return -1;
	
    //?? stdin stdout stderr ????
   // handle -= 3;
    if( handle < 0 ){ //????????????/??????
    // flmode[ handle + 3 ] = 0x00;
       return 0;
    }
	
    if( BiosEntry( handle, 0, 0, FILE_CLOSE ) >= 0 ) {
       // flmode[ handle + 3 ] = 0x00;//???????????
       return 0;
    }
    return -1;
}

int Fclose(FILE* fp)
{
	int result =0;//result ? BIT0 ? 1 ?? write ??,BIT1 ? 1 ??close ??
	int cnt;//???????????
	
	if( !fp ) {
//	   errno = PTRERR;
	   return -1;
	}
	//_IOREAD _IOWRITE ??_IORW ????,????
	if( !( fp->_ioflag1 & ( _IOREAD | _IOWRITE | _IORW) ) ) {
	//   errno = NOTOPN;
	   return -1;
	}

	//?? IO ??
   if( ( fp->_ioflag1 & _IOERR ) )
     return -1;
 
//???????????,?? write ??,? write ??,?? result ? 1
	if( fp->_ioflag1 & _IOWRITE ){
		cnt = fp->_bufptr - fp->_bufbase;
		if( cnt ){
			if( Write( fp->_iofd, fp->_bufbase, cnt ) != cnt )
			result |= WRITE_ERROR; 
		}
	}
	
//???????? bufbase ???,?????,??_bufbase ?? 0,?????????
	if( ( fp->_ioflag1 & _IOBGBUF ) && ( fp->_bufbase ) )
#if FREERTOS == 0
		Free( fp->_bufbase );
#else
    vPortFree(fp->_bufbase);
#endif	
	
	fp->_bufptr = NULL;
	fp->_bufcnt = 0;
	fp->_bufbase = NULL;
	fp->_buflen = 0;
	fp->_ioflag1 = 0;
	fp->_ioflag2 =0;
	if( Close( fp->_iofd ) < 0 ){
		result |= CLOSE_ERROR;
	}
	
	if( result )//result ?? 0,?? write ?? read ?????
		return -1;
		
	return 0;
}





int Read(int handle, char* buffer, size_t size)
{
	int result;
	
	if( handle >= _NFILE || handle < 0 )
       return -1;
   
    result = BiosEntry( handle/* - 3*/, (int)buffer, size, FILE_READ );
    if ( result < 0 )
        return -1;
	
    return result;
}


#if FREERTOS == 0
char* Sbrk( unsigned long size)
{
	unsigned char* p;
	
	if( ( brk + size ) > (heap_area + sizeof( heap_area ) ) ){
       return ( char* )(-1);
    }
	
    p = brk;
    brk += size;
    return (char*)p;
}


char* _morecor(unsigned long len)
{
	char* p;
	unsigned long size;
	
	size = len / _sbrk_size;
	if( len % _sbrk_size )
		size +=1;
	
	size = size * _sbrk_size;
	p = Sbrk( size );
	if( p == (char*)(-1) ){
		return NULL;
	}
	
	*(unsigned long*)p = size - 4;//?????????????????????? 4 ??
	return p;
}
#endif

void allocbuf(FILE* fp)
{
	char* p;
	
	if( fp->_bufbase ){//?????? 0,?????
		return ;
	}
	
	if( fp->_ioflag1 & _IOUNBUF ) {//??????,????? id ? sml_buf ?????????,sml_buf ???? 20,??? 20 ???
		fp->_buflen = 1;
		fp->_bufbase = &sml_buf[ fp->_iofd ];
	} else {
		#if FREERTOS == 0
		p = (char*)Malloc( BUFSIZ );//?? BUFSIZ(512)??????
		#else
		p = ( char* )pvPortMalloc( BUFSIZ );
		#endif
		if( p ) {//??????,??????? malloc ????,??_ioflag1 ??_IOBGBUF ??(???)
			fp->_bufbase = p;
			fp->_buflen = BUFSIZ;
			fp->_ioflag1 |= _IOBGBUF;
		} else {//????,?? sml_buf ??
			fp->_buflen = 1;
			fp->_bufbase = &sml_buf[ fp->_iofd ];
			fp->_ioflag1 |= _IOUNBUF;
		}
	}
	
	if( fp->_ioflag1 & _IOREAD ){//?? READ ??,?????????????,??????? 0
	    fp->_bufptr = fp->_bufbase + fp->_buflen;
	    fp->_bufcnt = 0;
	}
	
    if( fp->_ioflag1 & _IOWRITE ) {//?? WRITE ??,??????????????,????????????
        fp->_bufptr = fp->_bufbase;
        fp->_bufcnt = fp->_buflen;
    }
}


#if FREERTOS == 0
void* Malloc(size_t size)
{
	struct Header* p;
	if( !size )
		return NULL;
	
	size += 3;
	size &= (~3);//??? 4 ?????
	size += 4;//???????????
	
	if( size > RAM_END )
		return NULL;
	
	if ( !freeptr ){//? freeptr ??,????_morecor ????,??????????,????,??????????
		p = ( struct Header* )_morecor( size );
		if( p == (struct Header*)(-1) ){
			printf("morecor fail\n");
			return NULL;
		}
		if( p->len == size ){//???????,?????,???? free ?????????,?????????
			printf("Malloc ok\n");
			return (void*)( (char*)p + 0x04 );
		}
		Free( (void*)( (char*)p + 0x04 ) );
	}
	
	for( p = freeptr; ; p = p->next )
	{
		if( p->len >= size ) {
			if( p->len == size ){//????,?????????,?????,?? freeptr,??????
				if( p == freeptr ){
					freeptr = p->next;
				}
				return (void*)( (char*)p + 0x04 );
			} else {//??????,??????,??????????
				p->len -= size + 0x04;
				p = (struct Header*)( (char*)p + p->len + 0x04 );//????????
				p->len = size;//????
				return (void*)( (char*)p + 0x04 );
			}
		}		
        if( p ->next == NULL ){//??????????,???_morecor ????,??????????????????
            p = ( struct Header* )_morecor( size );
            if( p == (struct Header*)-1 )
               return NULL;
            if( p->len == size )
                return (void*)( (char*)p + 0x04 );
            Free( (void*)( (char*)p + 0x04 ) ); //??????????,??????,???????????
            p = freeptr;
        }
    }
}

void Free(void* ptr)
{
	struct Header* bp;
	struct Header* p;
	
	if( !ptr )
		return;
	
	bp = (struct Header*)( (char*)ptr - 4);//??????
	if( !freeptr ){//freeptr ??,???????????
		freeptr = bp;
		bp->next = NULL;
		return ;
	}
	
	if( bp < freeptr ){//????????? freeptr????????,???????????
		if ( ( bp + bp->len + 0x04 ) == freeptr ){//????????? freeptr ?????????,?????,?????????
			bp->len += freeptr->len + 0x04;//??? size ??????????(4 ??)
			bp->next = freeptr->next;
			freeptr = bp;
			return;
		}
//?????,??????
		bp->next = freeptr->next;
		freeptr = bp;
		return;
	}
//????,?????????,????????,??????
	for( p = freeptr ; !( ( bp >= p ) && ( bp <= p->next ) );p = p->next ){ 
		if( !p->next )
			break;
	}
//??????,?????????,?????????????,????????
	if( ( p + p->len + 0x04 ) == bp ){
		p->len += bp->len + 0x04;
	} else {
		bp->next = p->next;
		p->next = bp;
	}
	
//???????????,???????,???????????????
	if( ( p + p->len + 0x04 ) == p->next ){
		p->len = p->next->len + 0x04;
		p->next = p->next->next;
	} 
}
#endif

int Fread(void* buffer ,size_t size, size_t block, FILE* fp)
{
	char* buf = (char*)buffer;
	int block_size;
	int block_num;
	int cnt;
/*	
  int result;
	char* _bufbase ;
*/	
	if( ! fp ){
		return 0;
	}
	
	if( ! (fp->_ioflag1 & _IORW ) ){
		if( fp->_ioflag1 & _IOWRITE ){
			return 0;
		}
	}
	
	if( ! (fp->_ioflag1 & ( _IOREAD | _IOWRITE | _IORW ) ) || ( !block ) || ( !size ) || fp->_ioflag1 & (_IOERR | _IOEOF ) ){
          return 0;
    }
	
	if( !fp->_bufbase )
		allocbuf( fp );
	if( fp->_ioflag1 & _IORW ){//?_IORW
		if( ( ( fp->_ioflag1 ) & _IOWRITE ) || !( ( fp->_ioflag1 ) & ( _IOWRITE | _IOREAD ) ) ){//?_IOWRITE
			fp->_bufcnt = 0;
			fp->_bufptr = fp->_bufbase + fp->_buflen;
		}
	}
	
	fp->_ioflag2 &= ~_UNGTC;
	block_num = 0;
	
	while(1){
		if( fp->_ioflag1 & ( _IOEOF | _IOERR ) )//????????????_IOEOF ??_IOERR ?,??
			break;
		if(block_num >= block )//???????,??
			break;
		
		block_size = size;//?????????
		
		while(block_size){
						if( fp->_ioflag1 &  _IOERR  )
							break;
						if( fp->_ioflag1 & _IOEOF  ){
							  if( block_size != size )
									block_num++;
								break;
							}
							
						if( block_size > ( fp->_bufcnt ) ){									
								if( fp->_ioflag1 & ( _IOEOF | _IOERR ) )//?????????,?????,????????????
									break;
								if( fp->_bufcnt ){//?????????? 0,????????,? block_size??_bufcnt ????,???????,????? read ??????
									memcpy( buf, fp->_bufptr, fp->_bufcnt );//??_bufcnt ???				
									buf += fp->_bufcnt;//?????????
									block_size -= fp->_bufcnt;//????? block_size
									fp->_bufcnt = 0;//???????? 0
								}
							
								if( ! ( fp->_ioflag2 & _IOLINBUF ) ){
									cnt = Read( fp->_iofd, fp->_bufbase, fp->_buflen );
									fp->_bufcnt = cnt;
									fp->_bufptr = fp->_bufbase;
									if( cnt == 0 ){//no data to read
										fp->_ioflag1 |= _IOEOF;
										fp->_bufptr = fp->_bufbase + fp->_buflen;
									} else if( cnt < 0 ){
										/**************************************************************/
										/*                  io error occured                          */
										/**************************************************************/
										fp->_bufcnt = 0;
										fp->_ioflag1 |= _IOERR;
										fp->_bufptr = fp->_bufbase + fp->_buflen;
									}
								} 
					}  else {
								if( ! ( fp->_ioflag1 & ( _IOERR | _IOEOF ) ) ){//??_IOERR ? _IOEOF ??,????? block_size,
									memcpy( buf, fp->_bufptr, block_size );
									buf += block_size;
									fp->_bufptr += block_size;
									fp->_bufcnt -= block_size;
									block_size = 0; 
								} 
					}
				}  //?? while ????
	
				//if( block_size )//block_size ?? 0,??????_IOEOF ??_IOERR ??,???????????,??????
					//continue;
				block_num++;//one block has read
			}
	
	fp->_ioflag1 |= _IOREAD;//??_IOREAD,??_IOWRITE ??
	fp->_ioflag1 &= ~_IOWRITE;
	return block_num;
}


/***********************************************************************/
/*                                                                     */
/*    function: write buffer data to the specified file                */
/*                                                                     */
/*    input: fp-------the FILE pointer                                 */
/*           block----write block number                               */
/*           size-----each block bytes number                          */
/*     output:the block has been written in fact                       */
/*                                                                     */
/***********************************************************************/
int Fwrite(void* buffer ,size_t size, size_t block, FILE* fp)
{
	size_t block_num;
	size_t block_size;
	char* buf = (char*)buffer;
	int result;	
/*
	int find_LR;	
	int linbuf_cnt;
*/	
	/******************************************/
	/*         file pointer check             */
	/******************************************/
	if( !fp ){
	  return 0;
	}
	
	/******************************************/
	/*        file atrribute check            */
	/******************************************/
	if( !( fp->_ioflag1 & _IORW ) ){
		if( fp->_ioflag1 & _IOREAD ){
			return 0;
		}
	}
	
	if( ! ( fp->_ioflag1 & ( _IOREAD | _IOWRITE | _IORW ) ) ){	
		return 0;
	}
	
	/*******************************************************/
	/*            parameter check                          */
	/*******************************************************/
	if( ( !size ) || ( !block ) || ( fp->_ioflag1 & _IOERR ) )//??? block_size ? 0
		return 0;
	
	/************************************************************/
	/*       if the write buffer is empty,allocate buffer       */
	/************************************************************/
	if( !fp->_bufbase ) 
		allocbuf( fp );
	
	if( fp->_ioflag1 & _IORW ){
		if( ( fp->_ioflag1 & _IOREAD ) || ( !( fp->_ioflag1 & ( _IOREAD | _IOWRITE ) ) ) ){
			fp->_bufptr = fp->_bufbase;
			fp->_bufcnt = fp->_buflen;
		}
	}
	
//???????
	block_num = 0;
	block_size = size;
/*
	linbuf_cnt = 0;
*/	
	if( fp->_buflen == 1 )
		fp->_bufcnt = 1;
	
	while(1){
		if( fp->_ioflag1 & _IOERR )
			break;
		if( block_num >= block )
			break;
		if( block_size == 0 )
			block_size = size;
		
		while( block_size ){
			  if( fp->_ioflag1 & _IOERR )
			      break;
				
				if( block_size >= fp->_bufcnt ){//if buffer which can be used is not enough 
					 memcpy(fp->_bufptr, buf, fp->_bufcnt);
					 block_size -= fp->_bufcnt;					 
					 buf        += fp->_bufcnt;					 		
					 fp->_bufcnt = 0;	
				}else{
					memcpy( fp->_bufptr, buf, block_size );//buf is enough					
					fp->_bufcnt -= block_size;
					fp->_bufptr += block_size;
					block_size = 0;
				}
				
				if( !fp->_bufcnt ){//buffer is full,write to disk
						result = Write( fp->_iofd, fp->_bufbase, fp->_buflen ); 
						fp->_bufptr = fp->_bufbase;
						fp->_bufcnt = fp->_buflen;		
						if( fp->_buflen != result ){//write error
								fp->_ioflag1 |= _IOERR; 
						}	
				}
				
			}			
			block_num++;	
		
		
	}
	
	
	fp->_ioflag1 |= _IOWRITE;
	fp->_ioflag1 &= ~_IOREAD;
	fp->_ioflag2 &= ~_UNGTC;
	return block_num;
}


int Remove(const char* filename)
{
	unsigned char NameCount=0;
	unsigned char ExtName=0;
	const char* p = filename;
	unsigned char Dot = 0;
	
	/*************************************************/
	/*    if the file pointer is NULL,return -1      */
	/*************************************************/
	if(!filename)
		return -1;
	
	/*************************************************/
	/*    check file name and extesion validation    */
	/*************************************************/
	while( *p ){
		NameCount++;
		if( *p == '.' ){
			Dot = 1;
			p++;
			break;
		}
		p++;
	}
	
	if( ( !Dot ) || ( NameCount > 8 ) )
		return -1;
	
	while(*p){
		ExtName++;
		p++;
	}
	
	if( ( ExtName > 3 ) || ( ExtName == 0 ) )
		return -1;
	
	return BiosEntry( (int)filename, 0, 0, FILE_REMOVE );
}

/**********************************************************************/
/*   function: if the oldname file exist,change name to newname       */
/**********************************************************************/
int Rename(char* oldname, char* newname)
{
	unsigned char NameCount=0;
	unsigned char ExtName=0;
	const char* p ;
	unsigned char Dot = 0;
	
	/*  file pointer is valid  */
	if(  ( !oldname ) || ( !newname ) )
		return -1;
	
	/* check file name string is valid*/
	p = oldname;
	while( *p ){
		NameCount++;
		if( *p == '.' ){
			Dot = 1;
			p++;
			break;
		}
		p++;
	}
	
	if( ( !Dot ) || ( NameCount > 8 ) )
		return -1;
	
	while(*p){
		ExtName++;
		p++;
	}
	
	if( ( ExtName > 3 ) || ( ExtName == 0 ) )
		return -1;
	
	/*       check new name is valid or not       */
	p = newname;
	NameCount = 0;
	ExtName =0;
	while( *p ){
		NameCount++;
		if( *p == '.' ){
			Dot = 1;
			p++;
			break;
		}
		p++;
	}
	
	if( ( !Dot ) || ( NameCount > 8 ) )
		return -1;
	
	while(*p){
		ExtName++;
		p++;
	}
	
	if( ( ExtName > 3 ) || ( ExtName == 0 ) )
		return -1;
	
	return BiosEntry( ( int )oldname, ( int )newname, 0, FILE_RENAME );
}

int Fseek(FILE *stream, long offset, int fromwhere)
{
	if( stream )
		return BiosEntry(stream->_iofd, offset, fromwhere, FILE_LSEEK);
	
	return -1;
	
}

int Fflush( FILE *stream )
{
	unsigned int cnt;
	
	if( stream ){
			if( stream->_ioflag1 & _IOWRITE ){
		       cnt = stream->_bufptr - stream->_bufbase;
		       if( cnt ){
			        if( Write( stream->_iofd, stream->_bufbase, cnt ) != cnt )
			           return EOF;
						}else
             return 0;
						
		   }else
			    return EOF;			 
	}
	  return EOF;	
}
