/**
 **************************************************************************************
 * @file    key_interface.c
 * @brief   Platform Adapter
 *
 * @author  halley
 * @version V1.0.0
 *
 * $Created: 2016-6-29 13:06:47$
 *
 * @Copyright (C) 2016, Shanghai Mountain View Silicon Co.,Ltd. All rights reserved.
 **************************************************************************************
 */


#include "type.h"
#include "key_interface.h"
#include "timeout.h"
#include "rtos_api.h"

#define DBG		printf

/***************************************************************************************
 *
 * Internal defines
 *
 */



/***************************************************************************************
 *
 * Internal varibles
 *
 */



/***************************************************************************************
 *
 * Internal functions
 *
 */


/***************************************************************************************
 *
 * APIs
 *
 */

TIMER			AdcKeyWaitTimer;
TIMER			AdcKeyScanTimer;
ADC_KEY_STATE	AdcKeyState;

/**
 * @brief
 *		Get ADC Key index
 *
 * @param
 *		scan channel
 *
 * @return
 *		Adc Key Index(current channel)
 */
// Key process, image key value to key event.
static uint8_t AdcChannelKeyGet(uint8_t Channel)
{
	uint16_t	Val;
	uint8_t		KeyIndex;

	Val = SarAdcChannelGetValue(Channel);

	if(Val >= (ADC_KEY_FULL_VAL - (ADC_KEY_FULL_VAL / ADC_KEY_COUNT)))
	{
		return 0xFF;	//no pressed key.
	}
	KeyIndex = (Val + (ADC_KEY_FULL_VAL / ADC_KEY_COUNT) / 2) * ADC_KEY_COUNT / ADC_KEY_FULL_VAL;
	return KeyIndex;
}

static uint8_t GetAdcKeyIndex(void)
{
	uint8_t KeyIndex = 0xFF;

#ifdef ADC_KEY_PORT_CH1
	KeyIndex = AdcChannelKeyGet(ADC_KEY_PORT_CH1);
#endif

#ifdef ADC_KEY_PORT_CH2
	if(KeyIndex == 0xFF)
	{
		KeyIndex = AdcChannelKeyGet(ADC_KEY_PORT_CH2);
#ifdef ADC_KEY_PORT_CH1
		if(KeyIndex != 0xFF)
		{
			KeyIndex += ADC_KEY_COUNT;
		}
#endif
	}
#endif

	return KeyIndex;
}

/**
 * @brief
 *		ADC Key init function
 *
 * @param
 *		void
 *
 * @return
 *		NONE
 */
void AdcKeyInit(void)
{
	DBG("AdcKeyInit()\n");

	AdcKeyState = ADC_KEY_STATE_IDLE;
	TimeOutSet(&AdcKeyScanTimer, 0);
	
#ifdef ADC_KEY_PORT_CH1
	SarAdcGpioSel(ADC_KEY_PORT_CH1);
#endif

#ifdef ADC_KEY_PORT_CH2
	SarAdcGpioSel(ADC_KEY_PORT_CH2);
#endif
}

/**
 * @brief
 *		ADC Key scan function
 *
 * @param
 *		void
 *
 * @return
 *		Key value
 */
KeyValue AdcKeyScan(KeyEvent *event)
{
	static 	uint8_t	PreKeyIndex = 0xFF;
	uint8_t			KeyIndex;

	*event = KEY_EVENT_NONE;

	if(!IsTimeOut(&AdcKeyScanTimer))
	{
		return INVAILD_KEY_VALUE;
	}
	TimeOutSet(&AdcKeyScanTimer, ADC_KEY_SCAN_TIME);

	KeyIndex = GetAdcKeyIndex();

	switch(AdcKeyState)
	{
		case ADC_KEY_STATE_IDLE:
			if(KeyIndex == 0xFF)
			{
				return INVAILD_KEY_VALUE;
			}

			PreKeyIndex = KeyIndex;
			TimeOutSet(&AdcKeyWaitTimer, ADC_KEY_JITTER_TIME);
			//DBG("GOTO JITTER!\n");
			AdcKeyState = ADC_KEY_STATE_JITTER;

		case ADC_KEY_STATE_JITTER:
			if(PreKeyIndex != KeyIndex)
			{
				//DBG("GOTO IDLE Because jitter!\n");
				AdcKeyState = ADC_KEY_STATE_IDLE;
			}
			else if(IsTimeOut(&AdcKeyWaitTimer))
			{
				//DBG("GOTO PRESS_DOWN!\n");
				TimeOutSet(&AdcKeyWaitTimer, ADC_KEY_CP_TIME);
				AdcKeyState = ADC_KEY_STATE_PRESS_DOWN;
				return INVAILD_KEY_VALUE;
			}
			break;

		case ADC_KEY_STATE_PRESS_DOWN:
			if(PreKeyIndex != KeyIndex)
			{
				//return key sp value
				//DBG("ADC KEY SP%bu\n", PreKeyIndex);
				AdcKeyState = ADC_KEY_STATE_IDLE;
				*event = KEY_EVENT_PRESS;
				return PreKeyIndex;
				
			}
			else if(IsTimeOut(&AdcKeyWaitTimer))
			{
				//return key cp value
				//DBG("ADC KEY CPS!\n");
				TimeOutSet(&AdcKeyWaitTimer, ADC_KEY_CPH_TIME);
				AdcKeyState = ADC_KEY_STATE_CP;
				*event = KEY_EVENT_HOLD;
				return PreKeyIndex;
			}
			break;

		case ADC_KEY_STATE_CP:
			if(PreKeyIndex != KeyIndex)
			{
				//return key cp value
				//DBG("ADC KEY CPR!\n");
				AdcKeyState = ADC_KEY_STATE_IDLE;
				*event = KEY_EVENT_RELEASE;
				return PreKeyIndex;
			}
			else if(IsTimeOut(&AdcKeyWaitTimer))
			{
				//return key cph value
				//DBG("ADC KEY CPH!\n");
				TimeOutSet(&AdcKeyWaitTimer, ADC_KEY_CPH_TIME);
				*event = KEY_EVENT_HOLDON;
				return PreKeyIndex;
			}
			break;

		default:
			AdcKeyState = ADC_KEY_STATE_IDLE;
			break;
	}

	return INVAILD_KEY_VALUE;
}

//clockwise rotation
//    ----|		   |--------|		 |-------------------
//A       |        |        |        |
//        |--------|        |--------|

//     -------|        |--------|		 |---------------
//B           |        |        |		 |
//            |--------|        |--------|


//counterclockwise rotation
//    --------|		   |--------|		 |---------------
//A           |		   |        |		 |
//            |--------|        |--------|

//     ---|        |--------|		 |-------------------
//B       |        |        |		 |
//        |--------|        |--------|


static uint8_t ClockWiseCnt;
static uint8_t CounterClockWiseCnt;

/**
 * @brief
 *		Coding key signal-A interrupt.
 *
 * @param
 *		void
 *
 * @return
 *		NONE
 */
 /*
__attribute__((section(".driver.isr"))) void GpioInterrupt(void)
{
	if(GpioIntFlagGet(CODING_KEY_A_PORT_INT) == CODING_KEY_A_BIT)
	{
		GpioIntClr(CODING_KEY_A_PORT_INT, CODING_KEY_A_BIT);
		if((GpioGetReg(CODING_KEY_A_PORT_IN) & CODING_KEY_A_BIT) || (ClockWiseCnt != 0) || (CounterClockWiseCnt != 0))
		{			
			return;
		}

		if(GpioGetReg(CODING_KEY_B_PORT_IN) & CODING_KEY_B_BIT)
		{
			//clockwise rotation
			ClockWiseCnt++;
		}
		else
		{
			//counterclockwise rotation
			CounterClockWiseCnt++;
		}
	}
}*/

/**
 * @brief
 *		Coding Key init function
 *
 * @param
 *		void
 *
 * @return
 *		NONE
 */
void CodingKeyInit(void)
{
	//enable pull up resister.
	GpioClrRegOneBit(CODING_KEY_A_PORT_OE, CODING_KEY_A_BIT);
	GpioClrRegOneBit(CODING_KEY_A_PORT_PU, CODING_KEY_A_BIT);
	GpioClrRegOneBit(CODING_KEY_A_PORT_PD, CODING_KEY_A_BIT);

	//enable pull up resister.
	GpioClrRegOneBit(CODING_KEY_B_PORT_OE, CODING_KEY_B_BIT);
	GpioClrRegOneBit(CODING_KEY_B_PORT_PU, CODING_KEY_B_BIT);
	GpioClrRegOneBit(CODING_KEY_B_PORT_PD, CODING_KEY_B_BIT);

	ClockWiseCnt = 0;
	CounterClockWiseCnt = 0;
	
	//GPIO中断和SDIO冲突,暂不处理
	/*
	//enable int
	GpioIntEn(CODING_KEY_A_PORT_INT, CODING_KEY_A_BIT, GPIO_NEG_EDGE_TRIGGER);

	//enable gpio irqc
	NVIC_EnableIRQ(GPIO_IRQn);
	*/
}

/**
 * @brief
 *		Coding Key scan function
 *
 * @param
 *		void
 *
 * @return
 *		Coding Key value
 */
KeyValue CodingKeyScan(KeyEvent *event)
{
	KeyValue keyValue = INVAILD_KEY_VALUE;
	
	*event = KEY_EVENT_NONE;

	if(ClockWiseCnt)
	{
		*event = KEY_EVENT_CLOCKWISE;
		keyValue = 0x00;
	}
	else if(CounterClockWiseCnt)
	{
		*event = KEY_EVENT_COUNTER_CLOCKWISE;
		keyValue = 0x01;
	}
	ClockWiseCnt = 0;
	CounterClockWiseCnt = 0;

	return keyValue;
}

static TIMER			IrKeyHoldTimer;
static TIMER			IrKeyWaitTimer;
static TIMER			IrKeyScanTimer;
static IR_KEY_STATE		IrKeyState;

static uint32_t 		IrKeyVal;

// Customer IR key value table, fix it by case.
static const uint8_t gIrVal[IR_KEY_SUM] =
{
	0xED,		// POWER
	0xE5,		// MODE
	0xE1,		// MUTE

	0xFE,		// PLAY/PAUSE
	0xFD,		// PRE
	0xFC,		// NEXT
};

/**
 * @brief
 *		Get IR Key index
 *
 * @param
 *		void
 *
 * @return
 *		IR Key index
 */
static uint8_t GetIrKeyIndex(void)
{
	static uint8_t KeyIndex = 0xFF;
	static uint8_t IrCphCnt = 0;
	bool IsIrShortPrs, IsIrContinuePrs;

	//DBG("[IR] Enter GetIrKeyIndex()\n");
	if(IrIsKeyCome())
	{
		IsIrShortPrs = TRUE;
		IsIrContinuePrs = FALSE;
		IrKeyVal = IrGetKeyCode();
		DBG("Key: %08LX\n", IrKeyVal);
	}
	else if(IrIsContinuePrs())
	{
		IsIrShortPrs = FALSE;
		IsIrContinuePrs = TRUE;
	}
	else
	{
		IsIrShortPrs = FALSE;
		IsIrContinuePrs = FALSE;
	}
	if(IsIrShortPrs || IsIrContinuePrs)
	{
		//fast response
		if(IsIrShortPrs)
		{
			IrCphCnt = 0;
		}
		if(IrCphCnt < 5)
		{
			IrCphCnt++;
		}
		TimeOutSet(&IrKeyHoldTimer, 70 * IrCphCnt);

		if(((IrKeyVal >> 24) & 0x000000FF) + ((IrKeyVal >> 16) & 0x000000FF) != 0xFF)
		{
			KeyIndex = 0xFF;
			return 0xFF;
		}

		if((IrKeyVal & 0x0000FFFF) == IR_MANU_ID)
		{
			for(KeyIndex = 0; KeyIndex < IR_KEY_SUM; KeyIndex++)
			{
				if(((IrKeyVal >> 24) & 0x000000FF) == gIrVal[KeyIndex])
				{
					return KeyIndex;
				}
			}
		}
		KeyIndex = 0xFF;
		return 0xFF;
	}
	else if(!IsTimeOut(&IrKeyHoldTimer))
	{
		return KeyIndex;
	}
	else
	{
		IrKeyVal = 0;
		return 0xFF;
	}
}

/**
 * @brief
 *		IR Key init function
 *
 * @param
 *		void
 *
 * @return
 *		NONE
 */
void IrKeyInit(void)
{
	DBG("IrKeyInit()\n");
	IrKeyState = IR_KEY_STATE_IDLE;
	TimeOutSet(&IrKeyScanTimer, 0);
	IrInit();
	IrGpioSel(IR_KEY_PORT);
	IrIgnoreLeadHeader(TRUE);
}

/**
 * @brief
 *		IR Key scan function
 *
 * @param
 *		void
 *
 * @return
 *		Key value
 */
KeyValue IrKeyScan(KeyEvent *event)
{
	static 	uint8_t 	PreKeyIndex = 0xFF;
	uint8_t				KeyIndex;
	
	*event = KEY_EVENT_NONE;

	if(!IsTimeOut(&IrKeyScanTimer))
	{
		return INVAILD_KEY_VALUE;
	}
	TimeOutSet(&IrKeyScanTimer, IR_KEY_SCAN_TIME);

	KeyIndex = GetIrKeyIndex();

	switch(IrKeyState)
	{
		case IR_KEY_STATE_IDLE:
			if(KeyIndex == 0xFF)
			{
				return INVAILD_KEY_VALUE;
			}

			//DBG("IR KEY PDS!\n");
			PreKeyIndex = KeyIndex;
			TimeOutSet(&IrKeyWaitTimer, IR_KEY_CP_TIME);
			IrKeyState = IR_KEY_STATE_PRESS_DOWN;
			return INVAILD_KEY_VALUE;

		case IR_KEY_STATE_PRESS_DOWN:
			if(PreKeyIndex != KeyIndex)
			{
				//return key sp value
				//DBG("IR KEY SP!%bu\n", PreKeyIndex);
				IrKeyState = IR_KEY_STATE_IDLE;
				*event = KEY_EVENT_PRESS;
				return PreKeyIndex;
			}
			else if(IsTimeOut(&IrKeyWaitTimer))
			{
				//return key cp value
				//DBG("IR KEY CPS!\n");
				TimeOutSet(&IrKeyWaitTimer, IR_KEY_CPH_TIME);
				IrKeyState = IR_KEY_STATE_CP;
				*event = KEY_EVENT_HOLD;
				return PreKeyIndex;
			}
			break;

		case IR_KEY_STATE_CP:
			if(PreKeyIndex != KeyIndex)
			{
				//return key cp value
				//DBG("IR CPR\n");
				IrKeyState = IR_KEY_STATE_IDLE;
				*event = KEY_EVENT_RELEASE;
				return PreKeyIndex;
			}
			else if(IsTimeOut(&IrKeyWaitTimer))
			{
				TimeOutSet(&IrKeyWaitTimer, IR_KEY_CPH_TIME);
				*event = KEY_EVENT_HOLDON;
				return PreKeyIndex;
			}
			break;

		default:
			IrKeyState = IR_KEY_STATE_IDLE;
			break;
	}
	//DBG("%d, %8X\n", IrIsKeyCome(), IrGetKeyCode());
	return INVAILD_KEY_VALUE;
}

