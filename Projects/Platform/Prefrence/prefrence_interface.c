/******************************************************************************

                  版权所有 (C), 2017-2027, 上海山景集成电路股份有限公司

 ******************************************************************************
  文 件 名   : prefrence_interface.c
  版 本 号   : 初稿
  功能描述   : 偏好存储，负责对小数据量的数据进行存储读取等操作
  函数列表   :
  修改历史   :

******************************************************************************/

/*----------------------------------------------*
 * 包含头文件                                   *
 *----------------------------------------------*/
#include	"type.h"
#include "spi_flash.h"
#include "file.h"
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#include "prefrence_interface.h"
/*----------------------------------------------*
 * 外部变量说明                                 *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 外部函数原型说明                             *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 内部函数原型说明                             *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 全局变量                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 模块级变量                                   *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 常量定义                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 宏定义                                       *
 *----------------------------------------------*/

 #define PIPE_FREERTOS 1
 #if PIPE_FREERTOS==0
   //方案1
 typedef enum STORAGE_TYPE//命名规则暂时是通讯在前存储介质在后
 {
     SpiFlash=1,
     SdCard,
     UsbPan,
     I2cFlash,
     UartTerminal,
     WifiTerminal,
     WifiCloudPan
 }STORAGE_TYPE_ENUM;
 typedef struct STORERAGE_AREA_MES
{
     uint8_t sName[4];
     uint8_t sIandle;
     uint8_t sIndex;
     STORAGE_TYPE_ENUM sStoretype;
     uint32_t sStartAddr;
     uint16_t sStoreareasize;//0 to chose the min block size              
}STORERAGE_AREA_MES_STRU;


#else
//方案2   基于OS

typedef enum MEDIA_ACCESS_TYPE
{
     SpiFlashMEM=1,
     SpiFlashMXM,
     SdCard,
     UsbPan,
     WifiLed,
     UartDebuger          
}MEDIA_ACCESS_TYPE_ENUM;
typedef struct PIPELINE_CONTROL_MES
{
    uint32_t sName;
    int32_t sHandle;  
    uint32_t sStartAddr;
    uint32_t sLength; 
	  uint8_t sInOutMode;//write only  read only  both
    MEDIA_ACCESS_TYPE_ENUM sVirtualPipeline;
	
	  uint8_t sIndex;  //管道号索引  
}PIPELINE_CONTROL_MES_STRU;
typedef struct PIPELINE_MES_NODE
{
   PIPELINE_CONTROL_MES_STRU sPcms;
   struct PIPELINE_MES_NODE_STRU *next;	
}PIPELINE_MES_NODE_STRU;

/*静态管道配置  */
#define PIPELINE_1   1
#define PIPELINE_2   2
#define PIPELINE_3   3
#define PIPELINE_4   4
//Init pipeline
#define Pipeline1Init(name) 
//DeInit pipeline
#define Pipeline1DeInit(handle)  
//Open pipeline
#define PipelineOpen(name) Open(name,0x04)
//Close pipeline
#define PipelineClose(handle)  Close(handle)
//load data by pipeline
#define Pipeline1LoadData(handle,buf,len)  Read(handle, buf,len) 
//save data by pipeline
#define Pipeline1SaveData(handle,buf,len) Write(handle, buf,len) 
//pipeline num set
#define PIPELINE_STATIC_CHN_NUM 1
PIPELINE_CONTROL_MES_STRU  gStaticPipeline[PIPELINE_STATIC_CHN_NUM];

/*动态管道配置  */

//地址映射机制   将每个通道的地址映射到对应的0x00000000起始
//区域保护机制  保证每个通道不会被写溢出    判断管道信息并与
//文件重入问题请考虑。通过信号量互斥自生过程
//高速低速管道分配 高速管道是为静态管带，配静态变量配合；低速管道是为动态管道，临时配置用完即收  静态为0-15 动态为16-255

/*****************************************************************************
 函 数 名  : PipelineRegister
 功能描述  : 数据管道注册
 
      0-15通道为固定通道，满足速度和效率比较快的   这类通道往往一次性初始化并长期开通
      16-255 为动态通道，由单链表来管理   这类通道使用频率不高，每次使用完毕之后，把相应的资源释放，该注销的注销


      如果添加固定通道信息不全， 会作为动态链表自动添加
   
 输入参数  : void* prs
 输出参数  : 无
 返 回 值  : uint32_t
 调用函数  : 
 被调函数  : 
 函数层级  :
*****************************************************************************/
#if PIPE_FREERTOS==1
  #define PreferenceInit(mes)  PipelineRegister(mes)//宏定义API接口
#else

#endif
int32_t PipelineRegister(void* prs,uint8_t chnnum )
{ 
    
}
/*****************************************************************************
 函 数 名  : PipelineCancel
 功能描述  :管道注销
 输入参数  : void* prs
 输出参数  : 无
 返 回 值  : uint32_t
 调用函数  : 
 被调函数  : 
 函数层级  :
*****************************************************************************/
#if PIPE_FREERTOS==1
  #define PreferenceDeinit(handle)  PipelineCancel(handle)//宏定义API接口
#else

#endif
int32_t PipelineCancel(void* prs,,uint8_t chnnum)
{
   
}

/*****************************************************************************
 函 数 名  : PipelineOpen
 功能描述  : 管道打开
 输入参数  : 
 输出参数  : 无
 返 回 值  : int32_t
 调用函数  : 
 被调函数  : 
 函数层级  :
*****************************************************************************/
int32_t PipelineOpen(int16_t pipenum)
{
     int32_t handle;
	PIPELINE_CONTROL_MES_STRU* p;
	p=prs;
   // PIPELINE_CONTROL_MES_STRU pcms = *(PIPELINE_CONTROL_MES_STRU*)prs;
    //注册完成之后，信息怎么存储
    //链表吗


    switch( (*p).sVirtualPipeline )
    {
        case PIPELINE_1 :
 
            handle = Pipeline1Init((char*)(*p).sHandle) ;
            break;
        case PIPELINE_2 :
            break;
        case PIPELINE_3 :           
            break;
        case PIPELINE_4 :           
            break;     
        default:
          //加单链表 动态管道
            break;  
    }
    return handle;
}

/*****************************************************************************
 函 数 名  : PipelineClose
 功能描述  : 管道关闭
 输入参数  : 
 输出参数  : 无
 返 回 值  : int32_t
 调用函数  : 
 被调函数  : 
 函数层级  :
*****************************************************************************/
int32_t PipelineClose(int16_t pipenum)
{
     PIPELINE_CONTROL_MES_STRU* p = prs;
    //注销对应的减少信息
     switch ( (*p).sVirtualPipeline)
    {
        case PIPELINE_1 :
        Pipeline1DeInit((*p).sName) ;
            break;
        case PIPELINE_2 :
            break;
        case PIPELINE_3 :            
            break;
        case PIPELINE_4 :            
            break;
       
        default:
          //加链表 动态管道
            break;
    }
    return 0;

}



/*****************************************************************************
 函 数 名  : PipleLoadData
 功能描述  : 虚拟存储区装载数据
 输入参数  : 
 输出参数  : 无
 返 回 值  : uint32_t
 调用函数  : 
 被调函数  : 
 函数层级  :
*****************************************************************************/
int32_t PiplelineLoad( void* prs, void* buf,uint32_t offset,uint32_t len)
{
   //区域保护机制  不越界
 //   地址还是用32bit   len 也可以用32bit  这样是为了包容其他接口
// 指针用void*?
	PIPELINE_CONTROL_MES_STRU* p = prs;
    //互斥信号量 来保证
    switch ( (*p).sVirtualPipeline)
    {
        case PIPELINE_1 :
            Pipeline1LoadData(offset,(char *)buf,len);
            break;
        case PIPELINE_2:
            break;
        case PIPELINE_3 :
            break;
        case PIPELINE_4:            
            break;
       
        default:
						break;
            
    }
		
		return 0;
   
}

/*****************************************************************************
 函 数 名  : PiplelineSave
 功能描述  : 虚拟存储区 保存数据
 输入参数  : 
 输出参数  : 无
 返 回 值  : uint32_t
 调用函数  : 
 被调函数  : 
 函数层级  :
*****************************************************************************/
int32_t  PiplelineSave( void* prs, void* buf,uint32_t offset,uint32_t len)
{
   //区域保护机制  不越界
	PIPELINE_CONTROL_MES_STRU* p = prs;
    switch ((*p).sVirtualPipeline)
    {
        case PIPELINE_1 :
            Pipeline1SaveData(offset,buf,len);
            break;
        case PIPELINE_2:
            break;
        case PIPELINE_3 :
            break;
        case PIPELINE_4:            
            break;
       
        default:
        
            break;
    }
		return 0;
}

#endif 
