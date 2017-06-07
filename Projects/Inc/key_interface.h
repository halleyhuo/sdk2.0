/**
 **************************************************************************************
 * @file    key_interface.h
 * @brief   
 *
 * @author  halley
 * @version V1.0.0
 *
 * $Created: 2016-6-29 13:06:47$
 *
 * @Copyright (C) 2016, Shanghai Mountain View Silicon Co.,Ltd. All rights reserved.
 **************************************************************************************
 */

#ifndef __KEY_INTERFACE_H__
#define __KEY_INTERFACE_H__

#include "type.h"
#include "key.h"
#include "app_message.h"
//ADC-KEY
#include "adc.h"
//CODING-KEY
#include "gpio.h"
//IR-KEY
#include "ir.h"

//ADC-KEY
//#define ADC_KEY_PORT_CH1	ADC_CHANNEL_B22
//#define	ADC_KEY_PORT_CH2	ADC_CHANNEL_B5
#define ADC_KEY_PORT_CH1	ADC_CHANNEL_C8

#define ADC_KEY_SCAN_TIME			10
#define ADC_KEY_JITTER_TIME			30
#define ADC_KEY_CP_TIME				1000
#define ADC_KEY_CPH_TIME			200
#define	ADC_KEY_COUNT				10 			//key count per adc channel
#define	ADC_KEY_FULL_VAL			4096		//

typedef enum _ADC_KEY_STATE
{
    ADC_KEY_STATE_IDLE,
    ADC_KEY_STATE_JITTER,
    ADC_KEY_STATE_PRESS_DOWN,
    ADC_KEY_STATE_CP

} ADC_KEY_STATE;

//CODING-KEY
#define CODING_KEY_A_PORT_IN	GPIO_B_IN	
#define	CODING_KEY_A_PORT_OE	GPIO_B_OE 			
#define	CODING_KEY_A_PORT_PU	GPIO_B_PU 
#define	CODING_KEY_A_PORT_PD	GPIO_B_PD 					
#define	CODING_KEY_A_PORT_INT	GPIO_B_INT 				
#define	CODING_KEY_A_BIT		(1 << 21)	//GPIO_B[21] for signal A 

#define	CODING_KEY_B_PORT_IN	GPIO_B_IN 				
#define	CODING_KEY_B_PORT_OE	GPIO_B_OE 			
#define	CODING_KEY_B_PORT_PU	GPIO_B_PU 
#define	CODING_KEY_B_PORT_PD	GPIO_B_PD 					
#define	CODING_KEY_B_BIT		(1 << 20)	//GPIO_B[20] for signal B

//IR-KEY
#define IR_KEY_PORT				IR_USE_GPIOC2 //IR使用的端口：IR_USE_GPIOA10, IR_USE_GPIOB7 or IR_USE_GPIOC2

#define	IR_KEY_SCAN_TIME		5
#define	IR_KEY_JITTER_TIME		30
#define	IR_KEY_CP_TIME			1000	//CP condition is 1s
#define	IR_KEY_CPH_TIME			350

#define	IR_KEY_SUM				6		//IR KEY SUM

//IrKeyVal[31:16]: key value
//IrKeyVal[15:0]: manu id
#define IR_MANU_ID				0x7F80

typedef enum _IR_KEY_STATE
{
    IR_KEY_STATE_IDLE,
    IR_KEY_STATE_JITTER,
    IR_KEY_STATE_PRESS_DOWN,
    IR_KEY_STATE_CP

} IR_KEY_STATE;

//ADC-KEY
void AdcKeyInit(void);
KeyValue AdcKeyScan(KeyEvent *event);

//CODING-KEY
void CodingKeyInit(void);
KeyValue CodingKeyScan(KeyEvent *event);

//IR-KEY
void IrKeyInit(void);
KeyValue IrKeyScan(KeyEvent *event);

#endif /*__KEY_INTERFACE_H__*/
