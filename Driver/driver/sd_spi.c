/**
 *****************************************************************************
 * @file     sdspi_card.c
 * @author   KK
 * @version  V1.0
 * @date     2-Dec-2016
 * @brief    sd memory card driver (spi mode)
 * 			 此文件包含SD卡SPI通讯方式的相关初始化及驱动接口
 *****************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT 2013 MVSilicon </center></h2>
 */
#include <string.h>
#include "type.h"
#include "sd_spi.h"
#include "spim.h"
#include "gpio.h"
#include "timeout.h"
#include "debug.h"
#include "delay.h"
#include "watchdog.h"
#include "rtos_api.h"

#define DBG printf

/**
 * SDIO BUS MODE
 * In terms of operating supply voltage, two types of SD Memory Cards are defined:
 * SD Memory Cards which supports initialization/identification process with a range of 2.0-3.6v
 * and operating voltage within this range as defined in the CSD register.
 * SDLV Memory Cards - Low Voltage SD Memory Cards, that can be operate in voltage range of
 * 1.6-3.6V. The SDLV Memory Cards will be labeled differently then SD Memory Cards.
 */
#define CMD0_GO_IDLE_STATE				0   /**<reset command and sets each card into Idle State regardless of the current card state*/
#define CMD1_SEND_OP_COND				1	/**<in idle state, only CMD1,ACMD41 and CMD58 are legal host CMD,response R1*/
//#define	CMD2_ALL_SEND_CID				2	/**<to each card to get its unique card identification (CID) number*/
//#define	CMD3_SEND_RELATIVE_ADDR			3   /**<asks the card to publish a new relative card address*/
//#define	CMD4_SET_DSR					4   /**<programs their DSP registers*/
#define	CMD6_SWITCH_FUNC				6   /** */
//#define	CMD7_SELECT_DESELECT_CARD		7   /**<used to select one card and put it into thansfer states */
#define	CMD8_SEND_IF_COND				8	/**<get the range of the volatage of the card support*/
#define	CMD9_SEND_CSD					9
#define	CMD10_SEND_CID					10
#define	CMD12_STOP_TRANSMISSION			12
#define	CMD13_SEND_STATUS				13
//#define	CMD15_GO_INACTIVE_STATE			15

/**<block oriented read commands (class 2)*/
#define	CMD16_SET_BLOCKLEN				16
#define	CMD17_READ_SINGLE_BLOCK			17
#define	CMD18_READ_MULTIPLE_BLOCK		18

/**<block oriented write commands (class 4)*/
#define	CMD24_WRITE_BLOCK				24
#define	CMD25_WRITE_MULTIPLE_BLOCK		25
#define	CMD27_PROGRAM_CSD				27

/**<block oriented write protection commands (class 6)*/
#define	CMD28_SET_WRITE_PROT			28
#define	CMD29_CLR_WRITE_PROT			29
#define	CMD30_SEND_WRITE_PROT			30

/**<erase commands (class 5)*/
#define	CMD32_ERASE_WR_BLK_START		32
#define	CMD33_ERASE_WR_BLK_END			33
#define	CMD38_ERASE						38

/**<lock card (class 7)*/
#define	CMD42_LOCK_UNLOCK				42

/**<application specific commands (class 8)*/
#define	CMD55_APP_CMD					55
#define	CMD56_GEN_CMD					56
#define	CMD58_READ_OCR					58
#define	CMD59_CRC_ON_OFF				59

/**<define ACMD index (ACMD6 ~ ACMD51)*/
/**<application specific commands used/reserved by SD memory card*/
//#define	ACMD6_SET_BUS_WIDTH				70	//6+64
#define	ACMD13_SD_STATUS				77	//13+64
#define	ACMD22_SEND_NUM_WR_BLOCKS		86	//22+64
#define	ACMD23_SET_WR_BLK_ERASE_COUNT	87	//23+64
#define	ACMD41_SD_SEND_OP_COND			105	//41+64             /**<The response to ACMD41 is the operation condition register of the card*/
#define	ACMD42_SET_CLR_CARD_DETECT		106	//42+64
#define	ACMD51_SEND_SCR					115	//51+64

/**<传输状态 */
#define SD_STATUS_ACCEPTED				0x02
#define SD_STATUS_CRC_ERROR				0x05
#define SD_STATUS_WRITE_ERROR			0x06

/**<卡类型*/
#define	MC_MCDMAS_MMC					1
#define	MC_MCDMAS_SD					2

#define	SD_BLOCK_SIZE					512             /**<块大小固定为512字节*/

/**<卡状态定义*/
#define	CURRENT_STATE_IDLE				0
#define	CURRENT_STATE_READY				1
#define	CURRENT_STATE_IDENT				2              /**<identification*/
#define	CURRENT_STATE_STBY				3
#define	CURRENT_STATE_TRAN				4
#define	CURRENT_STATE_DATA				5              /**<sending data*/
#define	CURRENT_STATE_RCV				6
#define	CURRENT_STATE_PRG				7
#define	CURRENT_STATE_DIS				8              /**<disconnect*/

//#define	VOLTAGE_WINDOWS					0x40FF8000     /**<2.7v~3.6v*/
#define VOLTAGE_PATTERN                 0x000001AA     /**<0x01:2.7-3.6V,0xAA:check pattern,pattern can use any 8-bit*/

#define	CMD0_CRC						0x95
#define CMD8_CRC						0x87
#define CMD_STUFF_CRC					0xff

#define ACMD41_PARAM					0x40000000
#define CMD_PARAM_STUFF					0

const uint8_t CmdRespType[128] =
{
	SDSPI_RESP_TYPE_R1,		//	CMD0_GO_IDLE_STATE				0
	SDSPI_RESP_TYPE_R1,		//	CMD1_SEND_OP_COND				1
	0,0,0,0, 
	SDSPI_RESP_TYPE_R1,		//	CMD6_SWITCH_FUNC				6
	0,
	SDSPI_RESP_TYPE_R7,		//	CMD8_SEND_IF_COND				8
	SDSPI_RESP_TYPE_R1,		//	CMD9_SEND_CSD					9
	SDSPI_RESP_TYPE_R1,		//	CMD10_SEND_CID					10
	0,
	SDSPI_RESP_TYPE_R1B,	//	CMD12_STOP_TRANSMISSION			12
	SDSPI_RESP_TYPE_R2,		//	CMD13_SEND_STATUS				13
	0,0,
	SDSPI_RESP_TYPE_R1,		//	CMD16_SET_BLOCKLEN				16
	SDSPI_RESP_TYPE_R1,		//	CMD17_READ_SINGLE_BLOCK			17
	SDSPI_RESP_TYPE_R1,		//	CMD18_READ_MULTIPLE_BLOCK		18
	0, 0, 0, 0, 0,
	SDSPI_RESP_TYPE_R1,		//	CMD24_WRITE_BLOCK				24
	SDSPI_RESP_TYPE_R1,		//	CMD25_WRITE_MULTIPLE_BLOCK		25
	0,
	SDSPI_RESP_TYPE_R1,		//	CMD27_PROGRAM_CSD				27
	SDSPI_RESP_TYPE_R1B,	//	CMD28_SET_WRITE_PROT			28
	SDSPI_RESP_TYPE_R1B,	//	CMD29_CLR_WRITE_PROT			29
	SDSPI_RESP_TYPE_R1,		//	CMD30_SEND_WRITE_PROT			30
	0,
	SDSPI_RESP_TYPE_R1,		//	CMD32_ERASE_WR_BLK_START		32
	SDSPI_RESP_TYPE_R1,		//	CMD33_ERASE_WR_BLK_END			33
	0, 0, 0, 0,
	SDSPI_RESP_TYPE_R1B,	//	CMD38_ERASE						38
	0, 0, 0,
	SDSPI_RESP_TYPE_R1,		//	CMD42_LOCK_UNLOCK				42
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	SDSPI_RESP_TYPE_R1,		//	CMD55_APP_CMD					55
	SDSPI_RESP_TYPE_R1,		//	CMD56_GEN_CMD					56
	0, 
	SDSPI_RESP_TYPE_R3,		//	CMD58_EAD_OCR					58
	SDSPI_RESP_TYPE_R1,		//	CMD59_CRC_ON_OFF				59
	0, 0, 0, 0,
	//--------------------------------ACMD-----------------------------------
	0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0,
	SDSPI_RESP_TYPE_R2,		//	ACMD13_SD_STATUS				77	//13 + 64
	0, 0, 0, 0, 0, 0, 0, 0,
	SDSPI_RESP_TYPE_R1,		//	ACMD22_SEND_NUM_WR_BLOCKS		86	//22 + 64
	SDSPI_RESP_TYPE_R1,		//	ACMD23_SET_WR_BLK_ERASE_COUNT	87	//23 + 64
	0, 0, 0, 0, 0, 0, 0, 0,	0, 0, 0, 0, 0, 0, 0, 0, 0,
	SDSPI_RESP_TYPE_R1,		//	ACMD41_SD_SEND_OP_COND			105	//41 + 64
	SDSPI_RESP_TYPE_R1,		//	ACMD42_SET_CLR_CARD_DETECT		106	//42 + 64
	0, 0, 0, 0, 0, 0, 0, 0,
	SDSPI_RESP_TYPE_R1,		//	ACMD51_SEND_SCR					115	//51 + 64
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};


/**
 * SD CARD attribute definition
 */
typedef struct _SD_CARD
{
	uint8_t	CardType;
	uint32_t	RCA;
	bool	IsCardIn;
	bool	IsSDHC;
	uint32_t	BlockNum;
	uint8_t    MaxTransSpeed;

} SD_CARD;

SD_CARD		    SdCard;
SD_CARD_ID	    SdCardId;

#define RESPLEN_MAX		20
uint8_t RespBuffer[RESPLEN_MAX];

uint8_t testblock=3;

//下面使用函数重载
//如果不使用OS的信号量机制，则上层不定义这两个函数，本模块将会调用下面这两个空函数
//如果使用OS信号量机制，则上层需要重写这两个函数，
__attribute__((weak))
void LockSdClk(void)
{

}

__attribute__((weak))
void UnLockSdClk(void)
{

}

//send 8*n clocks
void SdSpi_SendClocks(uint8_t num)
{
	uint8_t i;

	for(i=0;i<num;i++)
	{
		SpiMasterSendByte(0xff);
	}
}

void SdSpi_CS_Enable(void)
{
	//set CS low
	GpioClrRegOneBit(SD_SPI_CS_OUT, SD_SPI_CS_IO);
}

void SdSpi_CS_Disable(void)
{
	//set CS high and send 8 clocks
	GpioSetRegOneBit(SD_SPI_CS_OUT, SD_SPI_CS_IO);
	SdSpi_SendClocks(2);
}

//sd spi mode initial
void SdSpiControllerInit(void)
{
    //CS - A1
	GpioSetRegOneBit(SD_SPI_CS_OUT, SD_SPI_CS_IO);
	GpioSetRegOneBit(SD_SPI_CS_OE, SD_SPI_CS_IO);
	GpioClrRegOneBit(SD_SPI_CS_IE, SD_SPI_CS_IO);
	GpioClrRegOneBit(SD_SPI_CS_PU, SD_SPI_CS_IO);
	GpioClrRegOneBit(SD_SPI_CS_PD, SD_SPI_CS_IO);

	//CMD - A2
	GpioClrRegOneBit(SD_SPI_CMD_PU, SD_SPI_CMD_IO);
	GpioClrRegOneBit(SD_SPI_CMD_PD, SD_SPI_CMD_IO);
	
	//CLK - A3
	GpioClrRegOneBit(SD_SPI_CLK_PU, SD_SPI_CLK_IO);
	GpioClrRegOneBit(SD_SPI_CLK_PD, SD_SPI_CLK_IO);
	
	//DAT - A4
	GpioClrRegOneBit(SD_SPI_DAT_PU, SD_SPI_DAT_IO);
	GpioClrRegOneBit(SD_SPI_DAT_PD, SD_SPI_DAT_IO);
	
	
	//spim0
	//spim_mosi a[2]
	//spim_clk  a[3]
	//spim_miso a[4]
	GpioSpimIoConfig(0);
	//spi mode: 0 or 3
	//spi clk speed: 0=24M, 1=12M, 2=6M, 3=3M, 4=1M5, 5=750K, 6=375K, 7=187.5K
	SpiMasterInit(0, SD_SPI_SPEED_INIT);
}

//get card special data(CID/CSD)
//wait for token(0xfe)
//length = 16bytes(data) + 2bytes(CRC)
SD_CARD_ERR_CODE SdSpiRecvData(uint8_t *buf, uint16_t len)  
{  
    uint8_t i,time = 0;
    uint8_t RespStart=0;

	do
	{
    	RespStart = SpiMasterRecvByte();
    	time++;
    	if(time>250) break;
    }while(RespStart != 0xfe);

	if(RespStart != 0xfe)
	{
		return CMD_SEND_TIME_OUT_ERR;
	}

	for(i=0;i<len;i++)
	{
		buf[i]=SpiMasterRecvByte();
	}
	return NONE_ERR;
}  

SD_CARD_ERR_CODE SdSpiSendCommand(uint8_t cmd, uint32_t param, uint8_t crc)  
{  
    uint8_t i,time = 0;
    SDSPI_RESP_TYPE Rsp_type;
    uint8_t RespLen;

	RespLen=1;
    if(cmd>128)
		return CMD_SEND_ERR;

	RespBuffer[0]=0xff;
    if(cmd>=64)
    {
    	cmd -= 64;
    }
    Rsp_type = CmdRespType[cmd];
    
    //send the command,arguments and CRC  
    SpiMasterSendByte((cmd & 0x3f) | 0x40);  
    SpiMasterSendByte((uint8_t)(param >> 24));  
    SpiMasterSendByte((uint8_t)(param >> 16));  
    SpiMasterSendByte((uint8_t)(param >> 8));  
    SpiMasterSendByte((uint8_t)param);  
	SpiMasterSendByte(crc);  

    if(cmd == CMD12_STOP_TRANSMISSION)
    {
        //read the respond until responds is not '0xff' or timeout  
        do{  
            RespBuffer[0] = SpiMasterRecvByte();  
            time ++;
            
            //if time out,return  
            if(time > 254) break;  
        }while(RespBuffer[0] == 0x00);  

    	//DBG("CMD Resp[0] = [0x%x]\n", RespBuffer[0]);
    	if(RespBuffer[0] == 0x00)
    		return SD_CARD_IS_BUSY_TIME_OUT_ERR;
    }
    else
    {
        //read the respond until responds is not '0xff' or timeout  
        do{  
            RespBuffer[0] = SpiMasterRecvByte();  
            time ++;
            
            //if time out,return  
            if(time > 254) break;  
        }while((RespBuffer[0]&0x80) == 0x80);  

    	//DBG("CMD Resp[0] = [0x%x]\n", RespBuffer[0]);
    	if(RespBuffer[0] == 0xff)
    		return GET_RESPONSE_STATUS_ERR;
    }

	if(Rsp_type == SDSPI_RESP_TYPE_R2)
	{
		//format R2 -- 2Bytes
		RespLen = 2;
	}
	else if((Rsp_type == SDSPI_RESP_TYPE_R3)||(Rsp_type == SDSPI_RESP_TYPE_R7))
	{
		//format R3/R7 -- 5Bytes
		RespLen = 5;
	}

	if(RespLen>1)
	{
		for(i=1;i<RespLen;i++)
		{
			RespBuffer[i] = SpiMasterRecvByte();
		}
	}
	return NONE_ERR;
}  

SD_CARD_ERR_CODE SdSpiAppSendCommand(uint8_t cmd, uint32_t arg, uint8_t crc)  
{
	if(SdSpiSendCommand(CMD55_APP_CMD, CMD_PARAM_STUFF, CMD_STUFF_CRC) == 0)
	{
		if(RespBuffer[0] != 0x01)
		{
			return CMD55_SEND_ERR;
		}
		//send 32 clocks
		SdSpi_SendClocks(4);
		
		if(SdSpiSendCommand(cmd, arg, crc))
		{
			return CMD_SEND_TIME_OUT_ERR;
		}
		return NONE_ERR;
	}
	return CMD_SEND_TIME_OUT_ERR;
}

//reset SD card
SD_CARD_ERR_CODE SdSpiReset(void)  
{  
	uint8_t i,time = 0;  

	//set CS high  
	SdSpi_CS_Disable();  

	//send 128(16*8) clocks  
	SdSpi_SendClocks(16);

	//set CS low  
	SdSpi_CS_Enable();  

	//send CMD0 till the response is 0x01  
	do{  
		SdSpiSendCommand(CMD0_GO_IDLE_STATE,CMD_PARAM_STUFF,CMD0_CRC);
		time ++;  
		//if time out,set CS high and return r1  
		if(time > 254)  
		{  
			DBG("****** Err: reset err... ******\n");
			DBG("response data = [0x%x] ******\n", RespBuffer[0]);
			return CMD0_SEND_ERR;  
		} 
	}while(RespBuffer[0] != 0x01);  

	SdSpi_SendClocks(2);
	
	DBG("\n****** sd-spi reset ok... ******\n");
	return NONE_ERR;  
}  

//initial SD card
//send CMD55+ACMD41
SD_CARD_ERR_CODE SdSpiInit_Sd(void)  
{  
	uint8_t time = 0;  

	//check interface operating condition  
	SdSpiSendCommand(CMD8_SEND_IF_COND,VOLTAGE_PATTERN,CMD8_CRC); 
	//if support Ver1.x,but do not support Ver2.0,set CS high and return r1  
	if(RespBuffer[0] == 0x05)
	{   
		DBG("sd not support Ver2.0 \n");
		//return CARD_VERSION_ERR;
	} 
	
	time = 0;
	do{  
		//send 32 clocks
		SdSpi_SendClocks(8);

		//send ACMD41 to initial SD card  
		SdSpiAppSendCommand(ACMD41_SD_SEND_OP_COND,ACMD41_PARAM,CMD_STUFF_CRC);
		time ++;  

		//if time out,set CS high and return r1  
		if(time > 254)  
		{  
			return SD_CARD_INIT_ERR;  
		}
	}while(RespBuffer[0] != 0x00);
	
	SdCard.CardType = MC_MCDMAS_SD;
	DBG("\n****** SD init ok... ******\n");
	return NONE_ERR;  
}  


//initial MMC card
//send CMD0
SD_CARD_ERR_CODE SdSpiInit_MMC(void)  
{  
	uint8_t time = 0;  

	//check interface operating condition  
	SdSpiSendCommand(CMD8_SEND_IF_COND,VOLTAGE_PATTERN,CMD8_CRC); 
	//if support Ver1.x,but do not support Ver2.0,set CS high and return r1  
	if(RespBuffer[0] == 0x05)
	{   
		DBG("sd not support Ver2.0 \n");
		//return CARD_VERSION_ERR;
	} 
	
	time = 0;
	do{  
		//send 32 clocks
		SdSpi_SendClocks(8);

		SdSpiSendCommand(CMD1_SEND_OP_COND,0,CMD_STUFF_CRC);
		time ++;  

		//if time out,set CS high and return r1  
		if(time > 254)  
		{  
			return SD_CARD_INIT_ERR;  
		}
	}while(RespBuffer[0] != 0x00);
	
	SdCard.CardType = MC_MCDMAS_MMC;
	DBG("\n****** MMC init ok... ******\n");
	return NONE_ERR;  
} 


void SdSpiStartReciveData(uint8_t* InBuf, uint16_t DataLen)
{
	if(DataLen > 512)
	{
		DataLen = 512;
	}
	SpiMasterStartData(InBuf, DataLen, 1);
}

void SdSpiStartSendData(uint8_t* OutBuf, uint16_t DataLen)
{
	if(DataLen > 512)
	{
		DataLen = 512;
	}
	SpiMasterStartData(OutBuf, DataLen, 0);
}


SD_CARD_ERR_CODE SdSpiWaitDataToken(uint8_t cmd)
{
	uint16_t time=0;
	uint8_t ret;

	do
	{
		ret = SpiMasterRecvByte(); 
		time++;
		if(time>10000) break;
	}
	while(ret!=0xfe);

	//DBG("SdSpiWaitDataToken = [0x%x]\n", ret);
	//DBG("time = [%d]\n", time);
	if(ret == 0xfe)
		return NONE_ERR;
	else
	{
		DBG("SdSpiWaitDataToken = [0x%x]\n", ret);
		DBG("time = [%d]\n", time);
		return SD_CARD_IS_BUSY_TIME_OUT_ERR;
	}
}

/**
 * @brief  get sd memory card info
 * @param  NONE
 * @return SD_CARD_ERR_CODE
 * @note
 */
SD_CARD_ERR_CODE SdCardGetInfo(void)
{
	uint8_t  i;

	SdSpi_CS_Enable();
	SdSpi_SendClocks(8);
	
	memset(RespBuffer,0xff,20);
	//获取CID(unique card identification)
	if(SdSpiSendCommand(CMD10_SEND_CID, 0, 0xff))
	//if(RespBuffer[0]!=0x00)      //success card will from ready switch to identification
	{
		DBG("SdCardInit() ERROR 005!\n");
		return CMD_SEND_ERR;
	}
	SdSpiRecvData(RespBuffer,18);
	memcpy(&SdCardId, &RespBuffer, 16);
	/*DBG("CID = ");
	for(i=0;i<20;i++)
	{
		DBG("[0x%x]", RespBuffer[i]);
	}
	DBG("\n\n");
	*/
	SdSpi_SendClocks(2);
	
	memset(RespBuffer,0xff,20);
	//SdSpi_CS_Enable();
	//获取CSD寄存器（Card Specific Data）里面的描述值，譬如，块长度，卡容量信息等。
	if(SdSpiSendCommand(CMD9_SEND_CSD, CMD_PARAM_STUFF, CMD_STUFF_CRC))
	//if(RespBuffer[0]!=0x00)
	{
		return CMD9_SEND_ERR;
	}
	SdSpiRecvData(RespBuffer,18);
	/*for(i=0;i<20;i++)
	{
		DBG("[0x%x]", RespBuffer[i]);
	}
	DBG("\n\n");
	*/
	SdCard.BlockNum=0;
	if(SdCard.CardType == MC_MCDMAS_SD)
	{
		DBG("CardType: MC_MCDMAS_SD\n");
		//根据CSD计算BlockNum
		if(RespBuffer[0])	//CSD V2
		{
			SdCard.BlockNum = ((RespBuffer[7] & 0x3f) << 16)
							  + ((RespBuffer[8] << 8))
							  + ((RespBuffer[9]))
							  + 1;
			SdCard.BlockNum <<= 10;
		}
		else                    //CSD V1
		{
			uint8_t Exp;

			// 计算卡中块的个数														// calculate the sector numbers of the SD Card
			SdCard.BlockNum = ((RespBuffer[6] & 0x03) << 10)
							  + ((RespBuffer[7] << 2))
							  + ((RespBuffer[8] & 0xC0) >> 6)
							  + 1;				// (C_SIZE + 1)

			Exp = ((RespBuffer[9] & 0x03) << 1)
				  + ((RespBuffer[10] & 0x80) >> 7)
				  + 2				// (C_SIZE_MULT + 2)
				  + ((RespBuffer[5] & 0x0F) - 9);

			// 获得卡中块的数量														// get the block numbers in card
			SdCard.BlockNum <<= Exp;							                    // (C_SIZE + 1) * 2 ^ (C_SIZE_MULT + 2)
		}
	}
	else if(SdCard.CardType == MC_MCDMAS_MMC)
	{
		uint8_t Exp;

		DBG("CardType: MC_MCDMAS_MMC\n");
		// 计算卡中块的个数														// calculate the sector numbers of the SD Card
		SdCard.BlockNum = ((RespBuffer[6] & 0x03) << 10)
						  + ((RespBuffer[7] << 2))
						  + ((RespBuffer[8] & 0xC0) >> 6)
						  + 1;				// (C_SIZE + 1)
		if(SdCard.BlockNum != 0x1000)
		{
			Exp = ((RespBuffer[9] & 0x03) << 1)
				  + ((RespBuffer[10] & 0x80) >> 7)
				  + 2				// (C_SIZE_MULT + 2)
				  + ((RespBuffer[5] & 0x0F) - 9);

			// 获得卡中块的数量														// get the block numbers in card
			SdCard.BlockNum <<= Exp;							                    // (C_SIZE + 1) * 2 ^ (C_SIZE_MULT + 2)
		}
	}
	//DBG("get sdcard block_number = [0x%04x]\n",SdCard.BlockNum);
	
	//set card max transfer data speed
	SdCard.MaxTransSpeed = 0x02;  //can use 6M clk
	
	/*if(SdCard.CardType == MC_MCDMAS_MMC && SdCard.BlockNum == 0x1000)
	{
		uint8_t ext_csd_buf[512];
		MMCReadExtCSD(ext_csd_buf);
		SdCard.BlockNum = *((uint32_t *)&ext_csd_buf[212]);
	}*/
	
	SdSpi_SendClocks(8);
	//设置块长度
	if(SdSpiSendCommand(CMD16_SET_BLOCKLEN, SD_BLOCK_SIZE, CMD_STUFF_CRC))
	{
		DBG("CMD16 send error\n");
		return CMD16_SEND_ERR;
	}

	SdSpi_SendClocks(8);
	//获取状态
	if(SdSpiSendCommand(CMD13_SEND_STATUS, CMD_PARAM_STUFF, CMD_STUFF_CRC))		//JACK-100701
	{
		DBG("CMD13 send error\n");
		return CMD13_SEND_ERR;
	}

	return NONE_ERR;
}

/**
 * @brief  Sdio Controller and sd memory card Init
 * @param  NONE
 * @return NONE
 * @note
 */
void SdControllerInit(void)
{
	SdCard.RCA = 0;
	SdCard.IsSDHC = FALSE;
	SdCard.IsCardIn = FALSE;

	SdSpiControllerInit();
}

/**
 * @brief  detect sd memory card.
 * @param  NONE
 * @return SD_CARD_ERR_CODE
 *         @arg  CMD13_SEND_ERR  read card status err
 *         @arg  NOCARD_LINK_ERR undetect card insert
 *         @arg  NONE_ERR
 * @note
 */
SD_CARD_ERR_CODE SdCardDetect(void)
{
	uint8_t ret;
	//卡已连接
	if(SdCard.IsCardIn)
	{
		SdSpi_CS_Enable();
	
		if(!SdSpiSendCommand(CMD13_SEND_STATUS, 0, 0xff))              	//read card status
		{
			SdSpi_CS_Disable();
			//SdSpi_SendClocks(1);
			return NONE_ERR;
		}
		else
		{
			SdSpi_CS_Disable();
			//SdSpi_SendClocks(1);
			SdControllerInit();
			return CMD13_SEND_ERR;
		}
	}

	SdControllerInit();

	//卡未连接
	//SD card init
	if(!SdSpiReset())
	{
		if(!SdSpiInit_Sd())
		{
			SdSpi_SendClocks(8);
			SdSpiSendCommand(CMD58_READ_OCR, 0, 0xff);
			if(RespBuffer[0] == 0x00)
			{
				if(RespBuffer[1] & 0x40)
				{
					//SDHC
					SdCard.IsSDHC = TRUE;
				}
				return NONE_ERR;
			}
		}
	}
	
	//MMC card init
	if(!SdSpiReset())
	{
		if(!SdSpiInit_MMC())
		{
			SdSpi_SendClocks(8);
			SdSpiSendCommand(CMD58_READ_OCR, 0, 0xff);
			if(RespBuffer[0] == 0x00)
			{
				if(RespBuffer[1] & 0x40)
				{
					//SDHC
					SdCard.IsSDHC = TRUE;
				}
				return NONE_ERR;
			}
		}
	}
	SdSpi_CS_Disable();
	//SdSpi_SendClocks(1);
	return NOCARD_LINK_ERR;
}

/**
 * @brief  get sd memory card transfer frequency division coefficient
 * @param  NONE
 * @return transfer speed 
 * @note   used after SdCardInit()
 */
uint8_t SdCardGetTransSpeed()
{
	return SdCard.MaxTransSpeed;
}

/**
 * @brief  set sd memory card transfer frequency division coefficient
 * @param  ClkIndex 0 ~ 11
 * @return SD_CARD_ERR_CODE
 * @note   0: 24M, 1: 12M, 2: 6M, 3: 3M, 4:1.5M, 5:750K, 6:375K, 7:187500, 8:93760, 9:46875, 10:23437.5, 11:11718.75
 */
SD_CARD_ERR_CODE SdCardSetTransSpeed(uint32_t ClkIndex)
{
	SpiMasterInit(0, ClkIndex);
	SdCard.MaxTransSpeed = ClkIndex;
}


/**
 * @brief  init sd memory card
 * @param  NONE
 * @return SD_CARD_ERR_CODE
 * @note
 */
SD_CARD_ERR_CODE SdCardInit(void)
{
	uint8_t 	Retry = 4;

	LockSdClk();

	SdControllerInit();

	//客户有张32GB TF卡，
	//在LINEIN模式下，插入SD卡，至少延时35ms，才能初始化成功。
	//在USB模式下，插入SD卡，至少延时80ms，才能初始化成功。
	//从SLEEP唤醒后至少延时1.5ms，才能初始化成功。orson 2012.02.29
	//客户有张32GB TF卡，在USB模式下，插入SD卡，至少延时110ms，才能初始化成功。orson 2012.07.02
	vTaskDelay(150);
	
	while(1)
	{
		if(!SdCardDetect())
		{
			if(!SdCardGetInfo())
			{
				DBG("CardGetInfo OK\n");
				break;
			}
		}
		
		if(!(--Retry))
		{
			SdSpi_CS_Disable();
			//SdSpi_SendClocks(1);
			UnLockSdClk();
			DBG("retry 4 times was still failed\n");
			return GET_SD_CARD_INFO_ERR;
		}
	}

	SdCard.IsCardIn = TRUE;
	
	SdSpi_CS_Disable();
	//SdSpi_SendClocks(1);
	SdCard.MaxTransSpeed = SD_SPI_SPEED_TRANS;//0=24M, 1=12M, 2=6M, 3=3M
	SpiMasterInit(0, SdCard.MaxTransSpeed);
	UnLockSdClk();
	
	//DBG("SD Card init OK\n");
	return NONE_ERR;
}

/**
 * @brief  read data from sd memory card
 * @param  Block specified block num
 * @param  Buffer save data into this buffer
 * @param  Size how many blocks will read
 * @return SD_CARD_ERR_CODE
 * @note
 */
SD_CARD_ERR_CODE SdReadBlock(uint32_t Block, uint8_t* Buffer, uint8_t Size)
{
	TIMER Timer;
	uint16_t time;
	uint16_t i;

	if(Block > SdCard.BlockNum)
	{
		DBG("SdReadBlock ERR: BLOCK_NUM_EXCEED_BOUNDARY\n");
		return BLOCK_NUM_EXCEED_BOUNDARY;
	}

	if(!SdCard.IsSDHC)
	{
		Block *= SD_BLOCK_SIZE;
	}
	
	//DBG("SdReadBlock....\n");
	//DBG("--- Block=[%d] ---\n", Block);
	
	LockSdClk();
	SdSpi_CS_Enable();
	
	if(SdSpiSendCommand(CMD18_READ_MULTIPLE_BLOCK, Block, 0xff))
	{
		SdSpi_CS_Disable();
		//SdSpi_SendClocks(1);
		UnLockSdClk();
		DBG("CMD18: CMD_SEND_TIME_OUT_ERR\n");
		return CMD_SEND_TIME_OUT_ERR;
	}
	
	if(SdSpiWaitDataToken(CMD18_READ_MULTIPLE_BLOCK))
	{
		DBG("CMD18-1: GET_RESPONSE_STATUS_ERR\n");
		SdSpi_CS_Disable();
		//SdSpi_SendClocks(1);
		UnLockSdClk();
		return GET_RESPONSE_STATUS_ERR;
	}

	SpiMasterIntClr();
	SpiMasterRecvBytes(Buffer, SD_BLOCK_SIZE);

	while(Size--)
	{
		//客户的某张KINGSTON 2GB MMC此处至少要180ms
		TimeOutSet(&Timer, 350); // update timeout to 350ms for new bad case
//		FeedWatchDog();

		while(!SpiMasterGetDmaDone())
		{
			if(IsTimeOut(&Timer))
			{
				WaitMs(5);
				if(SpiMasterGetDmaDone())
				{
					break;
				} // more one channel fortimeout
				DBG("SdReadBlock(%ld) error 003!\n", Block);
				SpiMasterIntClr();
				UnLockSdClk();
				return READ_SD_CARD_TIME_OUT_ERR;
			}
		}
		
		SpiMasterIntClr();
		//CRC
		SpiMasterRecvByte(); 
		SpiMasterRecvByte(); 

		if(Size)
		{
			Buffer += SD_BLOCK_SIZE;
			SpiMasterIntClr();

			if(SdSpiWaitDataToken(CMD18_READ_MULTIPLE_BLOCK))
			{
				SdSpi_CS_Disable();
				//SdSpi_SendClocks(1);
				UnLockSdClk();
				DBG("CMD18-2: GET_RESPONSE_STATUS_ERR\n");
				return GET_RESPONSE_STATUS_ERR;
			}
			
			SpiMasterIntClr();
			SdSpiStartReciveData(Buffer, SD_BLOCK_SIZE);
		}
	}
	
	//CMD12_STOP_TRANSMISSION
	time=0;
	do
	{
		SdSpiSendCommand(CMD12_STOP_TRANSMISSION, 0, 0xff);
		time++;
		if(time>6000)break;
	}while(RespBuffer[0]==0);
	
	SdSpi_CS_Disable();
	//SdSpi_SendClocks(1);
	UnLockSdClk();
	
	//if((RespBuffer[0]==0)||(RespBuffer[0]==0xff))
	if(RespBuffer[0]==0)
	{
		DBG("CMD12: CMD_SEND_TIME_OUT_ERR\n");
		return CMD_SEND_TIME_OUT_ERR;
	}

	return NONE_ERR;
}

/**
 * @brief  write data into sd memory card
 * @param  Block specified block num
 * @param  Buffer read data from this buffer
 * @param  Size how many blocks will write
 * @return SD_CARD_ERR_CODE
 * @note
 */
SD_CARD_ERR_CODE SdWriteBlock(uint32_t Block, const uint8_t* Buffer, uint8_t Size)
{
	TIMER WriteBlockTimer;
	uint16_t time,timecnt;
	uint16_t i;
	uint8_t ret=0;

	//DBG("SdWriteBlock....\n");
	//DBG("--- Block=[%d] ---\n", Block);
	
	if(Block > SdCard.BlockNum)
	{
		return BLOCK_NUM_EXCEED_BOUNDARY;
	}

	LockSdClk();
	SdSpi_CS_Enable();
	
	if(!SdCard.IsSDHC)
	{
		Block *= SD_BLOCK_SIZE;
	}

	if(SdSpiSendCommand(CMD25_WRITE_MULTIPLE_BLOCK, Block, 0xff))
	{
		SdSpi_CS_Disable();
		//SdSpi_SendClocks(1);
		UnLockSdClk();
		DBG("SdWriteBlock Command Error!\n");
		return CMD25_SEND_ERR;
	}

	while(Size--)
	{
		//send a block
		time=0;
		do
		{
			//start
			SpiMasterSendByte(0xfc);
	        SpiMasterSendData((uint8_t*)Buffer, SD_BLOCK_SIZE);
	        
			Buffer += SD_BLOCK_SIZE;
			SpiMasterSendByte(0xff);
			SpiMasterSendByte(0xff);

			ret=SpiMasterRecvByte();
			time++;
			if(time>250)
			{
				DBG("--- ret=[0x%x] ---\n", ret);
				DBG("SdWriteBlock: no response\n");
				SdSpi_CS_Disable();
				//SdSpi_SendClocks(1);
				UnLockSdClk();
				return WRITE_NO_RESPONSE;
			}
		}while((ret&0x1f)!= 0x05);

		time=0;
        //check busy  
        do{  
            ret = SpiMasterRecvByte();
            time ++;  
            //if time out,set CS high and return r1  
            if(time > 30000)  
            {  
				DBG("--- ret=[0x%x] ---\n", ret);
				DBG("SdWriteBlock: busy\n");
				SdSpi_CS_Disable();
				//SdSpi_SendClocks(1);
				UnLockSdClk();
				return WRITE_BUSY;
            }  
        }while(ret != 0xff);  
        
		//数据全部传输完，则发送STOP命令
		if(Size == 0)
		{
			//send stop token
			SpiMasterSendByte(0xfd);
			
			time=0;
			do
			{
				ret=SpiMasterRecvByte();
				time++;
				
				if(time>30000)
				{
					DBG("SdWriteBlock: DataOut is busy!\n");
		            SdSpi_CS_Disable();
					UnLockSdClk();
		            return WRITE_SD_CARD_TIME_OUT_ERR;
				}
			}while(ret != 0xff);
		}
	}
	SdSpi_CS_Disable();
	//SdSpi_SendClocks(1);
	UnLockSdClk();

	//DBG("SdWriteBlock OK!\n");
	return NONE_ERR;
}

/**
 * @brief  get the capacity of the sd memory card, unit is block
 * @param  NONE
 * @return the card capacity
 * @note
 */
uint32_t SdCardCapacityGet(void)
{
	return SdCard.BlockNum;
}

/**
 * @brief  start read sd memory card, each time read one block
 * @param  Block specified block num
 * @param  Buffer save data into this buffer
 * @return SD_CARD_ERR_CODE
 * @note
 */
/* DMA */
SD_CARD_ERR_CODE SdCardReadBlockStart(uint32_t block, uint8_t* buffer)
{
	return UNUSED_ERROR;
}

/**
 * @brief  start read next block, before read must wait last block transfer finished
 * @param  Buffer save data into this buffer
 * @return SD_CARD_ERR_CODE
 * @note
 */
SD_CARD_ERR_CODE SdCardReadBlockNext(uint8_t* buffer)
{
	return UNUSED_ERROR;
}

/**
 * @brief  end read sd memory card
 * @param  NONE
 * @return SD_CARD_ERR_CODE
 * @note
 */
SD_CARD_ERR_CODE SdCardReadBlockEnd(void)
{
	return UNUSED_ERROR;
}


/**
 * @brief  start write block
 * @param  block  Block specified block num
 * @return SD_CARD_ERR_CODE
 * @note
 */
SD_CARD_ERR_CODE SdCardWriteBlockStart(uint32_t Block)
{
	return UNUSED_ERROR;;
}

/**
 * @brief  ready to write next block, before write function must wait last block write finished
 * @param  Buffer read data from this buffer
 * @return SD_CARD_ERR_CODE
 * @note
 */
SD_CARD_ERR_CODE SdCardWriteBlockNext(uint8_t* Buffer)
{
	return UNUSED_ERROR;
}

/**
 * @brief  end write sd memory card
 * @param  NONE
 * @return SD_CARD_ERR_CODE
 * @note
 */
SD_CARD_ERR_CODE SdCardWriteBlockEnd(void)
{
	return UNUSED_ERROR;
}



