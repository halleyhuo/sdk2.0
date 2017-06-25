/******************************************************************************
 * @file    app_config.h
 * @author  Peter
 * @version V1.0.0
 * @date    02-03-2017
 * @maintainer
 * @brief
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT 2013 MVSilicon </center></h2>
 */

#ifndef APP_CONFIG_H_
#define APP_CONFIG_H_

#define SDRAM_BASE_ADDR				0x60000000
#define SDRAM_SIZE					(1024*1024*2)

#define DECODER_MEM_OFFSET			(2*1024)
#define SDIO_SEND_RECV_BUF_SIZE		128

#define AUDIOC_CORE_TRANSFER_OFFSET	(30*1024)
#define AUDIOC_CORE_TRANSFER_SIZE	(2*1024)

#define PCM_FIFO_SIZE				(8*1024)
#define PCM_FIFO_OFFSET				(32*1024-PCM_FIFO_SIZE)
#define ADC_MEM_FIFO_SIZE			(2*1024)
#define ADC_MEM_OFFSET 				0
#define WEIXIN_BUF_SIZE  		 	(22*1024)
#define WEIXIN_BUF_ADDR 			(0x20018000+ADC_MEM_FIFO_SIZE)

#define	DBG(format, ...)		printf(format, ##__VA_ARGS__)

#define	APP_DBG(format, ...)	printf(format, ##__VA_ARGS__)

#define	FS_DBG(format, ...)		printf(format, ##__VA_ARGS__)

#define wifi_audio_debug(format, ...)	printf(format, ##__VA_ARGS__)

#define ASSERT(x)

#define FUNC_CARD_EN		//CARD

#endif /* APP_CONFIG_H_ */
