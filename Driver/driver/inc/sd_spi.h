/**
 *****************************************************************************
 * @file     sd_spi.h
 * @author   KK
 * @version  V1.0
 * @date     2-Dec-2016
 * @brief    sd memory card driver interface (spi mode)
 *****************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT 2013 MVSilicon </center></h2>
 */

/**
* @addtogroup Çý¶¯
* @{
* @defgroup Card Card
* @{
*/

#ifndef __SPI_CARD_H__
#define __SPI_CARD_H__

#ifdef __cplusplus
extern "C" {
#endif//__cplusplus

#include "type.h"
#include "gpio.h"

//SPI CONFIG
#define SD_SPI_CS_IE			GPIO_A_IE
#define SD_SPI_CS_OE			GPIO_A_OE
#define SD_SPI_CS_PU			GPIO_A_PU
#define SD_SPI_CS_PD			GPIO_A_PD
#define SD_SPI_CS_OUT			GPIO_A_OUT
#define SD_SPI_CS_IO			GPIOA1

#define SD_SPI_CMD_IE			GPIO_A_IE
#define SD_SPI_CMD_OE			GPIO_A_OE
#define SD_SPI_CMD_PU			GPIO_A_PU
#define SD_SPI_CMD_PD			GPIO_A_PD
#define SD_SPI_CMD_OUT			GPIO_A_OUT
#define SD_SPI_CMD_IO			GPIOA2

#define SD_SPI_CLK_IE			GPIO_A_IE
#define SD_SPI_CLK_OE			GPIO_A_OE
#define SD_SPI_CLK_PU			GPIO_A_PU
#define SD_SPI_CLK_PD			GPIO_A_PD
#define SD_SPI_CLK_OUT			GPIO_A_OUT
#define SD_SPI_CLK_IO			GPIOA3

#define SD_SPI_DAT_IE			GPIO_A_IE
#define SD_SPI_DAT_OE			GPIO_A_OE
#define SD_SPI_DAT_PU			GPIO_A_PU
#define SD_SPI_DAT_PD			GPIO_A_PD
#define SD_SPI_DAT_OUT			GPIO_A_OUT
#define SD_SPI_DAT_IO			GPIOA4

#define CARD_DETECT_PORT_IE		GPIO_A_IE
#define CARD_DETECT_PORT_OE		GPIO_A_OE
#define CARD_DETECT_PORT_PU		GPIO_A_PU
#define CARD_DETECT_PORT_PD		GPIO_A_PD
#define CARD_DETECT_PORT_OUT	GPIO_A_OUT
#define CARD_DETECT_PORT_IN		GPIO_A_IN
#define CARD_DETECT_IO			GPIOA3

#define SD_PORT_NUM				0

//spi clk speed: 0=24M, 1=12M, 2=6M, 3=3M, 4=1M5, 5=750K, 6=375K, 7=187.5K
#define SD_SPI_SPEED_INIT		7
#define SD_SPI_SPEED_TRANS		1

/**
 * SD CARD CID definition
 */
typedef struct _SD_CARD_ID
{
	uint8_t	MID;					/**< Manufacturer ID CID[127:120]*/
	uint8_t	OID[2];					/**< OEM/Application ID CID[119:104]*/
	uint8_t	PNM[5];					/**< Product name CID[103:64]*/
	uint8_t	PRV;					/**< Product revision CID[63:56]*/
	uint8_t	PSN[4];					/**< Product serial number CID[55:24]*/
	uint16_t	Rsv : 4;			/**< reserved CID[23:20]*/
	uint16_t	MDT : 12;			/**< Manufacturing date CID[19:8]*/
	uint8_t	CRC : 7;				/**< CRC7 checksum CID[7:1]*/
	uint8_t	NoUse : 1;				/**< not used, always 1  CID[0:0]*/

} SD_CARD_ID;

/**
 * err code definition
 */
typedef enum _SD_CARD_ERR_CODE
{
    CMD_SEND_TIME_OUT_ERR = -255,   /**<cmd send time out*/
    GET_RESPONSE_STATUS_ERR,        /**<get surrent transfer status err*/
    READ_SD_CARD_TIME_OUT_ERR,      /**<sd card read time out*/
    WRITE_SD_CARD_TIME_OUT_ERR,     /**<sd card write time out*/
    SD_CARD_IS_BUSY_TIME_OUT_ERR,   /**<sd card is busy time out*/
    NOCARD_LINK_ERR,                /**<sd card link err*/
    ACMD41_SEND_ERR,                /**<send ACMD41 err*/
    CMD1_SEND_ERR,                  /**<send CMD1 err*/
    CMD2_SEND_ERR,                  /**<get CID err*/
    ACMD6_SEND_ERR,                 /**<set bus witdh err*/
    CMD7_SEND_ERR,                  /**<select and deselect card err*/
    CMD9_SEND_ERR,                  /**<get CSD err*/
    CMD12_SEND_ERR,                 /**<stop cmd send err*/
    CMD13_SEND_ERR,                 /**<CMD13 read card status err*/
    CMD16_SEND_ERR,                 /**<set block length err*/
    CMD18_SEND_ERR,                 /**<CMD18 send err*/
    CMD25_SEND_ERR,                 /**<multi block write cmd send err*/
    CMD55_SEND_ERR,                 /**<send cmd55 err*/
    GET_SD_CARD_INFO_ERR,           /**<get sd card info err*/
    BLOCK_NUM_EXCEED_BOUNDARY,      /**<read block exceed boundary err*/

    CMD0_SEND_ERR,					/**<CMD0 send err/go idle state err*/

    CMD_SEND_ERR,
    CMD58_SEND_ERR,
    CARD_VERSION_ERR,
    SD_CARD_INIT_ERR,
    UNUSED_ERROR,

    WRITE_NO_RESPONSE,
    WRITE_BUSY,
    
    NONE_ERR = 0,
} SD_CARD_ERR_CODE;

typedef enum
{
	SDSPI_RESP_TYPE_R0 = 0,
	SDSPI_RESP_TYPE_R1,
	SDSPI_RESP_TYPE_R1B,
	SDSPI_RESP_TYPE_R2,
	SDSPI_RESP_TYPE_R3,
	SDSPI_RESP_TYPE_R7
}SDSPI_RESP_TYPE;

/**
 * @brief  Sdio Controller and sd memory card Init
 * @param  NONE
 * @return NONE
 * @note
 */
void SdControllerInit(void);

/**
 * @brief  identify sd memory card
 * @param  NONE
 * @return SD_CARD_ERR_CODE
 * @note
 */
SD_CARD_ERR_CODE SdCardInit(void);

/**
 * @brief  get sd memory card transfer frequency division coefficient
 * @param  NONE
 * @return transfer speed 
 * @note   used after SdCardInit()
 * 		   0: 24M, 1: 12M, 2: 6M, 3: 3M, 4:1.5M, 5:750K, 6:375K, 7:187500, 8:93760, 9:46875, 10:23437.5, 11:11718.75
 */
uint8_t SdCardGetTransSpeed(void);

/**
 * @brief  set sd memory card transfer frequency division coefficient
 * @param  ClkIndex 0 ~ 11
 * @return SD_CARD_ERR_CODE
 * @note   0: 24M, 1: 12M, 2: 6M, 3: 3M, 4:1.5M, 5:750K, 6:375K, 7:187500, 8:93760, 9:46875, 10:23437.5, 11:11718.75
 */
SD_CARD_ERR_CODE SdCardSetTransSpeed(uint32_t ClkIndex);

/**
 * @brief  detect sd memory card.
 * @param  NONE
 * @return SD_CARD_ERR_CODE
 *         @arg  CMD13_SEND_ERR  read card status err
 *         @arg  NOCARD_LINK_ERR undetect card insert
 *         @arg  NONE_ERR
 * @note
 */
SD_CARD_ERR_CODE SdCardDetect(void);

/**
 * @brief  get the capacity of the sd memory card, unit is block
 * @param  NONE
 * @return the card capacity
 * @note
 */
uint32_t SdCardCapacityGet(void);

/**
 * @brief  read data from sd memory card
 * @param  Block specified block num
 * @param  Buffer save data into this buffer
 * @param  Size how many blocks will read
 * @return SD_CARD_ERR_CODE
 * @note
 */
SD_CARD_ERR_CODE SdReadBlock(uint32_t Block, uint8_t* Buffer, uint8_t Size);

/**
 * @brief  write data into sd memory card
 * @param  Block specified block num
 * @param  Buffer read data from this buffer
 * @param  Size how many blocks will write
 * @return SD_CARD_ERR_CODE
 * @note
 */
SD_CARD_ERR_CODE SdWriteBlock(uint32_t Block, const uint8_t* Buffer, uint8_t Size);


/**
 * @brief  start read sd memory card, each time read one block
 * @param  Block specified block num
 * @param  Buffer save data into this buffer
 * @return SD_CARD_ERR_CODE
 * @note
 */
SD_CARD_ERR_CODE SdCardReadBlockStart(uint32_t block, uint8_t* buffer);

/**
 * @brief  start read next block, before read must wait last block transfer finished
 * @param  Buffer save data into this buffer
 * @return SD_CARD_ERR_CODE
 * @note
 */
SD_CARD_ERR_CODE SdCardReadBlockNext(uint8_t* buffer);

/**
 * @brief  end read sd memory card
 * @param  NONE
 * @return SD_CARD_ERR_CODE
 * @note
 */
SD_CARD_ERR_CODE SdCardReadBlockEnd(void);

/**
 * @brief  start write block
 * @param  block  Block specified block num
 * @return SD_CARD_ERR_CODE
 * @note
 */
SD_CARD_ERR_CODE SdCardWriteBlockStart(uint32_t Block);

/**
 * @brief  ready to write next block, before write function must wait last block write finished
 * @param  Buffer read data from this buffer
 * @return SD_CARD_ERR_CODE
 * @note
 */
SD_CARD_ERR_CODE SdCardWriteBlockNext(uint8_t* Buffer);

/**
 * @brief  end write sd memory card
 * @param  NONE
 * @return SD_CARD_ERR_CODE
 * @note
 */
SD_CARD_ERR_CODE SdCardWriteBlockEnd(void);

#ifdef  __cplusplus
}
#endif//__cplusplus

#endif

/**
 * @}
 * @}
 */
