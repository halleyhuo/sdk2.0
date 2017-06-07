/**
******************************************************************************
* @file    shell.c
* @brief   This file API is for debug
* @author  Peter Zhai
* @date    21-7-2015
* @version
*
* &copy
******************************************************************************
*/

#include "type.h"
#include "debug.h"
#include "uart.h"
#include "FreeRTOS.h"
#include "task.h"
#include "rtos_api.h"

#define cmdMAX_INPUT_SIZE 64
#define cmdMAX_OUTPUT_SIZE 1024

typedef portBASE_TYPE (*ShellCommandCallback)( int8_t *WriteBuffer, uint16_t WriteBufferLen, const int8_t * Command );

static portBASE_TYPE DisplayTaskInf( int8_t *pcWriteBuffer, uint16_t xWriteBufferLen, const int8_t *pcCommandString );
static portBASE_TYPE DisplayRunTimeStatesInf( int8_t *pcWriteBuffer, uint16_t xWriteBufferLen, const int8_t *pcCommandString );
static portBASE_TYPE DisplayMemInf( int8_t *pcWriteBuffer, uint16_t xWriteBufferLen, const int8_t *pcCommandString );
static portBASE_TYPE DisplayTaskRunningPlace( int8_t *pcWriteBuffer, uint16_t xWriteBufferLen, const int8_t *pcCommandString );

typedef struct ShellCommand
{
    const int8_t * const Command;
    const int8_t * const HelpString;
    const ShellCommandCallback CommandInterpreter;
    const int8_t NumberOfParameters;
} ShellCommandDefinition_t;

typedef struct ShellCommandList
{
    const ShellCommandDefinition_t *Command;
    struct ShellCommandList *Next;
} ShellCommandList_t;

static portBASE_TYPE prvHelpCommand( int8_t *pcWriteBuffer, uint16_t xWriteBufferLen, const int8_t *pcCommandString );

static const ShellCommandDefinition_t HelpCommand =
{
    ( const int8_t * const ) "help",
    ( const int8_t * const ) "\nhelp : Lists all the registered commands\r\n",
    prvHelpCommand,
    0
};

static const ShellCommandDefinition_t ListTaskPcCommand =
{
    ( const int8_t * const ) "list-pc",
    ( const int8_t * const ) "list-pc: Show pc value of each task\r\n",
    DisplayTaskRunningPlace,
    0
};

static const ShellCommandDefinition_t ListTaskCommand =
{
    ( const int8_t * const ) "list-task",
    ( const int8_t * const ) "list-task : Lists all the task states\r\n",
    DisplayTaskInf,
    0
};

static const ShellCommandDefinition_t ListCPUCommand =
{
    ( const int8_t * const ) "list-cpu",
    ( const int8_t * const ) "list-cpu : Show how much processing time each task has used\r\n",
    DisplayRunTimeStatesInf,
    0
};

static const ShellCommandDefinition_t ListMemCommand =
{
    ( const int8_t * const ) "list-mem",
    ( const int8_t * const ) "list-mem : Show how much memory we can use\r\n",
    DisplayMemInf,
    0
};

static ShellCommandList_t xRegisteredCommands =
{
    &HelpCommand,
    NULL
};

static portBASE_TYPE DisplayTaskRunningPlace( int8_t *pcWriteBuffer, uint16_t xWriteBufferLen, const int8_t *pcCommandString )
{
    const int8_t *const pcPlaceTableHeader = ( int8_t * ) "\nTask       SP            PC\n----     ---------     ----------\n";

    /* Generate a table of task stats. */
    strcpy( ( char * ) pcWriteBuffer, ( char * ) pcPlaceTableHeader );

    vTaskGetRunningPlace(pcWriteBuffer + strlen( ( char * )pcPlaceTableHeader) );

    return pdFALSE;
}

static portBASE_TYPE DisplayMemInf( int8_t *pcWriteBuffer, uint16_t xWriteBufferLen, const int8_t *pcCommandString )
{
    const int8_t *const pcMemTableHeader = ( int8_t * ) "\nRemainingMemoryInBytes: ";

    /* Generate a table of task stats. */
    strcpy( ( char * ) pcWriteBuffer, ( char * ) pcMemTableHeader );

    sprintf( pcWriteBuffer + strlen( ( char * ) pcMemTableHeader ), "%d\r\n",xPortGetFreeHeapSize());

    return pdFALSE;

}

static portBASE_TYPE DisplayTaskInf( int8_t *pcWriteBuffer, uint16_t xWriteBufferLen, const int8_t *pcCommandString )
{

    const int8_t *const pcTaskTableHeader = ( int8_t * ) "\nTask           State  Prio+3  FreeStack(word)  PID\n***************************************************\r\n";

    /* Generate a table of task stats. */
    strcpy( ( char * ) pcWriteBuffer, ( char * ) pcTaskTableHeader );
    vTaskList( pcWriteBuffer + strlen( ( char * ) pcTaskTableHeader ) );

    /* There is no more data to return after this single string, so return
    pdFALSE. */
    return pdFALSE;

}

static portBASE_TYPE DisplayRunTimeStatesInf( int8_t *pcWriteBuffer, uint16_t xWriteBufferLen, const int8_t *pcCommandString )
{
    const int8_t * const pcStatsTableHeader = ( int8_t * ) "\nTask           \tAbs Time\tPercent\r\n****************************************\r\n";

    strcpy( ( char * ) pcWriteBuffer, ( char * ) pcStatsTableHeader );
    vTaskGetRunTimeStats( pcWriteBuffer + strlen( ( char * ) pcStatsTableHeader ) );

    return pdFALSE;
}


static portBASE_TYPE prvHelpCommand( int8_t *pcWriteBuffer, uint16_t xWriteBufferLen, const int8_t *pcCommandString )
{
    ShellCommandList_t * pxCommand = NULL;
    signed portBASE_TYPE xReturn;
    uint16_t len;
    int16_t WriteBufferLen;

    /* Reset the pxCommand pointer back to the start of the list. */
    pxCommand = &xRegisteredCommands;

    WriteBufferLen=xWriteBufferLen;

    /* Return the next command help string, before moving the pointer on to
    the next command in the list. */
    while(pxCommand != NULL)
    {
        strncpy( ( char * ) pcWriteBuffer, ( const char * ) pxCommand->Command->HelpString ,WriteBufferLen);

        len=strlen( pcWriteBuffer );

        pcWriteBuffer += len;

        WriteBufferLen-=len;

        if(WriteBufferLen < 0)
        {
            break;
        }

        pxCommand = pxCommand->Next;
    }

    xReturn = pdTRUE;

    return xReturn;
}


portBASE_TYPE RegisterShellCommand( const ShellCommandDefinition_t * const pxCommandToRegister )
{
    static ShellCommandList_t *pxLastCommandInList = &xRegisteredCommands;
    ShellCommandList_t *pxNewListItem;
    portBASE_TYPE xReturn = pdFAIL;

    /* Create a new list item that will reference the command being registered. */
    pxNewListItem = ( ShellCommandList_t * ) pvPortMalloc( sizeof( ShellCommandList_t ) );

    if( pxNewListItem != NULL )
    {
        //taskENTER_CRITICAL();
        {
            /* Reference the command being registered from the newly created
            list item. */
            pxNewListItem->Command = pxCommandToRegister;

            /* The new list item will get added to the end of the list, so
            pxNext has nowhere to point. */
            pxNewListItem->Next = NULL;

            /* Add the newly created list item to the end of the already existing
            list. */
            pxLastCommandInList->Next = pxNewListItem;

            /* Set the end of list marker to the new list item. */
            pxLastCommandInList = pxNewListItem;
        }
        //taskEXIT_CRITICAL();

        xReturn = pdPASS;
    }

    return xReturn;
}


portBASE_TYPE ShellProcessCommand( const int8_t * const pcCommandInput, int8_t * pcWriteBuffer, uint16_t xWriteBufferLen  )
{
    ShellCommandList_t *pxCommand = NULL;
    portBASE_TYPE xReturn = pdTRUE;
    const int8_t *pcRegisteredCommandString;
    uint16_t xCommandStringLength, CommandInputLen=0, i;

    /* Search for the command string in the list of registered commands. */
    for( pxCommand = &xRegisteredCommands; pxCommand != NULL; pxCommand = pxCommand->Next )
    {
        pcRegisteredCommandString = pxCommand->Command->Command;
        xCommandStringLength = strlen( ( const char * ) pcRegisteredCommandString );

        /* To ensure the string lengths match exactly, so as not to pick up
        	a sub-string of a longer command, check the byte after the expected
        	end of the string is either the end of the string or a space before
        	a parameter. */

        if( ( pcCommandInput[ xCommandStringLength ] == ' '  )||
                ( pcCommandInput[ xCommandStringLength ] == '\n' )||
                ( pcCommandInput[ xCommandStringLength ] == '\r' ))
        {
            if( strncmp( ( const char * ) pcCommandInput, ( const char * ) pcRegisteredCommandString, xCommandStringLength ) == 0 )
            {
                break;
            }
        }
    }

    if( pxCommand != NULL )
    {
        /* Call the callback function that is registered to this command. */
        xReturn = pxCommand->Command->CommandInterpreter( pcWriteBuffer, xWriteBufferLen, pcCommandInput );

    }
    else
    {
        /* pxCommand was NULL, the command was not found. */
        strncpy( ( char * ) pcWriteBuffer, ( const char * const ) "\nCommand not recognised.  Enter \"help\" to view a list of available commands.\r\n\r\n", xWriteBufferLen );
        xReturn = pdFALSE;
    }

    return xReturn;
}

uint8_t RcvedBuffer[cmdMAX_INPUT_SIZE],TransmitBuffer[cmdMAX_OUTPUT_SIZE];

QueueHandle_t ShellMsgID;

uint8_t shell_flag = 0;

void ShellTask(void)
{
    uint8_t c;
    uint16_t RcvedDataCnt=0,RcvedCharLen;
    osMessage event;
    ShellMsgID = xQueueCreate(16, sizeof(uint32_t));;
	
    GpioBuartRxIoConfig(1);
    GpioBuartTxIoConfig(1);
    BuartInit(115200, 8, 0, 1);
    //enblae buart interrupt
    BuartIOctl(UART_IOCTL_RXINT_SET, 1);
    NVIC_SetPriority(BUART_IRQn,2);

    RegisterShellCommand(&ListTaskCommand);
    RegisterShellCommand(&ListCPUCommand);
    RegisterShellCommand(&ListMemCommand);
    RegisterShellCommand(&ListTaskPcCommand);

    while(1)
    {
        event = osMessageRecv(ShellMsgID, 0xffffffff);
        RcvedBuffer[RcvedDataCnt++] = (uint8_t )event.value.v;
        if((RcvedBuffer[RcvedDataCnt-1] == '\n')||(RcvedBuffer[RcvedDataCnt-1] == '\r'))
        {
            ShellProcessCommand((uint8_t *)RcvedBuffer, (uint8_t *)TransmitBuffer, cmdMAX_OUTPUT_SIZE);

            memset(RcvedBuffer, 0, cmdMAX_INPUT_SIZE);

            RcvedDataCnt = 0;

            shell_flag = 1;
            printf(TransmitBuffer);
            shell_flag = 0;
        }
    }
}

__attribute__((section(".driver.isr")))
void BuartInterrupt(void)
{
    long Status;
    char c;
    /*
     * take datum reception proirity over transmittion
     */
    Status = BuartIOctl(UART_IOCTL_RXSTAT_GET,0);
    if(Status & 0x1)
    {
        /*
         * clear interrupt status firstly
         */
        BuartIOctl(UART_IOCTL_RXINT_CLR,0);
        //or you can receive data in interrupt context

        if(0 < BuartRecv((uint8_t *)&c,1,0))
        {
						xQueueSend(ShellMsgID, &c, 0);
            BuartSend(&c,1);
        }
    }

    if(Status & 0x1E)
    {
        /*
         * clear FIFO before clear other flags rudely
         */
        BuartIOctl(UART_IOCTL_RXFIFO_CLR,0);
        BuartIOctl(BUART_IOCTL_RXFIFO_CLR,0);
        /*
         * clear other error flags
         */
        BuartIOctl(UART_IOCTL_RX_ERR_INT_CLR,0);
    }
    if(BuartIOctl(UART_IOCTL_TXSTAT_GET,0) & 0x1)
    {
        /*
         * clear interrupt status
         */
        BuartIOctl(UART_IOCTL_TXINT_CLR,0);
    }
}
