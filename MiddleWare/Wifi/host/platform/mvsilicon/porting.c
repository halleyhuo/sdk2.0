/*
* MV platform RAM only 128K, so need to reduce code size.
* Modify as follows:
* 1. lwip use resource 0 .
* 	 #define LWIP_PARAM_SET       0
* 2. Iperf runninig server or client independent by compiling option.
* 	 #define HAVE_CLIENT          0
* 	 #define HAVE_SERVER          1
* 3. Disable CLI_HISTORY_ENABLE
* 	 #define CLI_HISTORY_ENABLE   0
* 4. Set SSV_TMR_MAX  10
*    #define SSV_TMR_MAX	      10
* 5. Create net_app_task only one.
* 6. Do not compiling SmartConfig module.
*/

#include <ssv_lib.h>
//#include <config.h>
#include <log.h>
//#include <host_global.h>
#include <rtos.h>
#include "gpio.h"

extern bool sdio_if_load_fw(u8* fw_bin, u32 fw_bin_len);

extern void *pvPortMalloc( size_t size );
extern void vPortFree( void *pv );

static unsigned char IsSwUartActedAsFuartFlag = 0;
extern void EnableSwUartAsFuart(unsigned char EnableFlag);

int hal_putchar(int c)
{
    if(IsSwUartActedAsFuartFlag)
    {
        if((unsigned char)c == '\n')
        {
            const char lfca[2] = "\r\n";
            SwUartSend((unsigned char*)lfca, 2);
        }
        else
        {
            SwUartSend((unsigned char*)&c, 1);
        }
    }
    else
    {
        if((unsigned char)c == '\n')
        {
            const char lfca[2] = "\r\n";
            FuartSend((unsigned char*)lfca, 2);
        }
        else
        {
            FuartSend((unsigned char*)&c, 1);
        }
    }

    return c;
}

u8 hal_getchar(void)
{
    char data = 0;
    FuartRecv(&data, 1, 0);
    return (u8)data;
}

#ifndef __MTRACE_CHECK__

OS_APIs void *OS_MemAlloc( u32 size )
{
//    printf("======================OS_MemAlloc size: %d \r\n", size);
    /**
        *  Platform dependent code. Please rewrite
        *  this piece of code for different system.
        */
    return pvPortMalloc(size);
}


/**
 *  We do not recommend using OS_MemFree() API
 *  because we do not want to support memory
 *  management mechanism in embedded system.
 */
OS_APIs void __OS_MemFree( void *m )
{
    /**
        *  Platform depedent code. Please rewrite
        *  this piece of code for different system.
        */

//    printf("======================__OS_MemFree size: %d \r\n", m);
    vPortFree(m);
}
#endif//#ifdef __MTRACE_CHECK__

void OS_MemCPY(void *pdest, const void *psrc, u32 size)
{
    memcpy(pdest,psrc,size);
}

void OS_MemSET(void *pdest, u8 byte, u32 size)
{
    memset(pdest,byte,size);
}

void platform_ldo_en_pin_init(void)
{
    GpioClrRegOneBit(GPIO_C_IE,GPIOC2);
    GpioSetRegOneBit(GPIO_C_OE,GPIOC2);
                          
    GpioSetRegOneBit(GPIO_C_PU,GPIOC2);
    GpioClrRegOneBit(GPIO_C_PD,GPIOC2);
}
void platform_ldo_en(bool en)
{
    if ( 1 == en)
    {
//        GpioClrRegOneBit(GPIO_C_PU, GPIOC2);
//        GpioClrRegOneBit(GPIO_C_PD, GPIOC2);
        GpioSetRegBits( GPIO_C_OUT, GPIOC2);
    }
    else
    {
//        GpioSetRegOneBit(GPIO_C_PU,GPIOC2);
//        GpioSetRegOneBit(GPIO_C_PD,GPIOC2);
        GpioClrRegBits(GPIO_C_OUT, GPIOC2);
    }
}

//=====================find fw to download=======================
#if 0
#include <firmware/ssv6200_uart_bin.h>
void platform_download_firmware(void)
{
    //LOG_PRINTF("bin size =%d\r\n",sizeof(ssv6200_uart_bin));
    ssv6xxx_download_fw((u8 *)ssv6200_uart_bin,sizeof(ssv6200_uart_bin));
#else
bool platform_download_firmware(void)
{
    unsigned int fw_size, i;

    extern const unsigned char RES_WIFI_FW_START[];
    extern const unsigned char RES_WIFI_END[];
    unsigned char* fw = (unsigned char*)&RES_WIFI_FW_START;
    fw_size = ((unsigned int)&RES_WIFI_END) - ((unsigned int)&RES_WIFI_FW_START);
    printf("fw_size=%d,%x, fw=%x,%x\r\n",fw_size,*fw ,(unsigned int)fw,(unsigned int)&RES_WIFI_FW_START);
    return ssv6xxx_download_fw((u8 *)&RES_WIFI_FW_START-1,fw_size);//??? u8* bin

#endif
}
void platform_read_firmware(void *d,void *s,u32 len)
{
    OS_MemCPY(d,(void *)s,len);
}
