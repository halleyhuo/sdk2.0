/******************************************************************************

                  版权所有 (C), 2016-2026, 上海山景集成电路股份有限公司

 ******************************************************************************
  文 件 名   : Encoder_servic.c
  版 本 号   : 初稿
  作    者   : Ben
  生成日期   : 2017年3月27日
  最近修改   :
  功能描述   : 音频编码器
                            例如将PCM数据变成MP3/MP2等
  函数列表   :
  修改历史   :
  1.日    期   : 2017年3月27日
    作    者   : Ben
    修改内容   : 创建文件

******************************************************************************/

/*----------------------------------------------*
 * 包含头文件                                   *
 *----------------------------------------------*/
#include "Audio_encoder.h"
#include "Adpcm_encoder.h"
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
typedef enum ENCODER_STATE
{
    eEncoderStateNone = 0, 
    eEncoderStateReady,
    eEncoderStateInitilized,
    eEncoderStateEncoding,
    eEncoderStateWaitXrDone,
    eEncoderStateWaitTxDone,
}ENCODER_STATE_ENUM;

typedef struct ENCODER_SERVICE_CONTEX
{
    xTaskHandle sTaskHandle;
    MessageHandle sMsgHandle;
    ServiceState sServiceState;
    MemHandle *sMemHande;
    ENCODER_STATE sEncoderState;
}ENCODER_SERVICE_CONTEX_STRU;

const char encoderServiceName[]="EncoderService";

static ENCODER_SERVICE_CONTEX_STRU encoderServiceCt;

                 *
 *----------------------------- * 内部函数 internal functions              *
 *----------------------------------------------*/
void audio_encoder_interrupt_callback(int32_t intterupt_type)
{

    ReleaseAudioMutex();
}

static int32_t EncoderServiceInit(void)
{


    return 0;
}

static int32_t EncoderServiceDeinit(void)
{



    return 0;
}
//encoderMode enum
static  void EncoderInit(uint16_t encoderMode)
{
    switch ( encoderMode )
    {
        case 1 :
            
            break;
        case 2 :
            
            break;
        case 3 :
            
            break;
        default:
            break;
    }

}

static void EncoderDeinit(void)
{
    encoderServiceCt.encoderState = eEncoderStateReady;
}

static void EncoderProcess(void)
{
    if(RT_SUCCESS == audio_encoder_initialize(...)
   {

        while(1)

        {

           if(pcm_samples_avariable() >= SAMPLES_PER_FRAME)

          {

              if(RT_SUCCESS == audio_encoder_encode(...))

                {

                  //Get the encoded data to save or transfer

                  //TODO

               }

          }

        }

    }


}

static void EncoderServiceEntrance(void* param)
{

}
  /*----------------------------------------------*
-----*/
#define RECORD_TASK_STACK_SIZE  1024
#define RECORD_TASK_PR *----------------------------------------------*/

 MessageHandle GetEncoderMessageHandle(void)
 {
    MessageHandle encoderServiceCt;
    return encoderServiceCt.msgHandle;
 }

 ServiceState GetEncodeServiceState(void)
 {


 }

#define ENCODER_SERVICE_SIZE    1024
#define ENCODER_SERVICE_PRIO   3
#define ENCODER_SERVICE_TIMEOUT  1
 int32_t EncoderServiceCreate(void)
 {
        EncoderServiceInit();
        xTaskCreate(EncoderServiceEntrance,decoderServiceName)

 }

