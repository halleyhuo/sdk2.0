#include <string.h>
#include <stdarg.h>
#include "airkiss_types.h"
#include "airkiss_cloudapi.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "semphr.h"
#include "sockets.h"

int airkiss_printfImp(const char *fmt, ...)
{
    va_list args;
    int ret_val;
    va_start(args, fmt);
    ret_val = vprintf(fmt, args);
    va_end(args);
    return ret_val;;
}

int airkiss_mutex_create(ak_mutex_t *mutex_ptr)
{
    mutex_ptr->xSemaphore = xSemaphoreCreateMutex();
    if ( mutex_ptr->xSemaphore == NULL )
        return 1;
    else
        return 0;
}

int airkiss_mutex_lock(ak_mutex_t *mutex_ptr)
{
    xSemaphoreTake(mutex_ptr->xSemaphore, 0xffffffff);
    return 0;
}

int airkiss_mutex_unlock(ak_mutex_t *mutex_ptr)
{
    xSemaphoreGive( mutex_ptr->xSemaphore );
    return 0;
}

int airkiss_mutex_delete(ak_mutex_t *mutex_ptr)
{
    vSemaphoreDelete( mutex_ptr->xSemaphore );
    return 0;
}

int airkiss_dns_gethost(char* url, uint32_t* ipaddr)
{
    struct ip_addr DNS_Addr;
    uint8_t ip_addr_s[24];
    printf("%s\n",url);
    if(netconn_gethostbyname(url, &DNS_Addr) == 0)
    {
        *ipaddr =  ((DNS_Addr.addr>>24)&0xFF)<<0;
        *ipaddr += ((DNS_Addr.addr>>16)&0xFF)<<8;
        *ipaddr += ((DNS_Addr.addr>>8)&0xFF)<<16;
        *ipaddr += ((DNS_Addr.addr>>0)&0xFF)<<24;
        printf("%d.%d.%d.%d\n",*ipaddr>>24,(*ipaddr>>16)&255,(*ipaddr>>8)&255,*ipaddr&0xFF);
        return 0;
    }
    else
    {
//        memset(ip_addr_s,0,24);
//        if(Resolve_IP_fromDNSPOD(url, ip_addr_s) == 1)
//        {
//            *ipaddr = inet_addr(ip_addr_s);
//            printf("DNS Get ip address success from DNSpod\n");
//            return 0;
//        }
//        else
//        {
//            printf("DNS Get ip address fail\n");
//            return -1;
//        }
    }
}

int airkiss_dns_checkstate(uint32_t* ipaddr)
{
    return -1;
}

ak_socket airkiss_tcp_socket_create()
{
    ak_socket sock;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        return -1;
    }
    printf("creat socket success\n");
    return sock;
}

int airkiss_tcp_connect(ak_socket sock, char* ipaddr, uint16_t port)
{
    struct sockaddr_in address;
    memset(&address,0,sizeof(struct sockaddr_in));
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = inet_addr(ipaddr);
    if(connect(sock,(struct sockaddr *)&address, sizeof (address))<0)
    {
        return -1;
    }
    printf("connect success\n");
    return 0;
}

int airkiss_tcp_checkstate(ak_socket sock)
{
    return -1;
}

int airkiss_tcp_send(ak_socket socket, char*buf, uint32_t len)
{
    int ret;
    ret = write(socket, buf,len);
    return ret;
}

void airkiss_tcp_disconnect(ak_socket socket)
{
    close(socket);
}

int airkiss_tcp_recv(ak_socket socket, char *buf, uint32_t size, uint32_t timeout)
{
    int ret;
    fd_set rfds;
    struct timeval tmo;
    tmo.tv_sec = timeout/1000;
    timeout = timeout%1000;
    tmo.tv_usec = timeout*1000;

    FD_ZERO(&rfds);
    FD_SET(socket, &rfds);
    ret = select(socket+1, &rfds, NULL, NULL, &tmo);
    if(ret != 0)
    {
        if(FD_ISSET(socket, &rfds))
        {
            ret = recv( socket, buf, size, 0);
            if(ret < 0)
            {
                return -1;
            }
            else
            {
                return ret;
            }
        }
    }
    return 0;
}

extern volatile unsigned int gSysTick;

uint32_t airkiss_gettime_ms()
{
    return gSysTick;
}