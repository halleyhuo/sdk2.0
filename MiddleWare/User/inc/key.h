/**
 **************************************************************************************
 * @file    key.h
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



#ifndef __KEY_H__
#define __KEY_H__

#include "type.h"
/***************************************************************************************
 *
 * Internal varibles
 *
 */

typedef int32_t						KeyStatus;

#define KEY_STATUS_SUCCESS			0

#define KEY_STATUS_FAILED			-1

#define KEY_STATUS_ALREADY_EXIST	-2

#define KEY_STATUS_NOT_FOUND		-3








/**
 * Key Type
 */
typedef uint8_t						KeyType;

/** ADC key*/
#define KEY_TYPE_ADC					1

/** Coding key*/
#define KEY_TYPE_CODING					2

/** IR key*/
#define KEY_TYPE_IR						3


/**
 * Key event
 */
typedef uint8_t						KeyEvent;

#define KEY_EVENT_NONE					0

/** Key press */
#define KEY_EVENT_PRESS					1

/** Key hold */
#define KEY_EVENT_HOLD					2

/** Key hold on */
#define KEY_EVENT_HOLDON				3

/** Key release */
#define KEY_EVENT_RELEASE				4

/** Coding Key clockwise */
#define KEY_EVENT_CLOCKWISE				5

/** Coding Key counter clockwise */
#define KEY_EVENT_COUNTER_CLOCKWISE		6

/**
 * Key value
 */
//typedef uint16_t					KeyValue;
//#define INVAILD_KEY_VALUE				0xFFFF

typedef uint8_t					KeyValue;

#define INVAILD_KEY_VALUE				0xFF

/**
 * Parameters for key callback function
 */
typedef struct _KeyCbParam
{
	KeyType			type;
	KeyEvent		event;
	KeyValue		value;
}KeyCbParam;

/**
 * @brief
 *		Callback function for key. This function
 *		will be called when a key event generated.
 *
 * @param
 *		params Parameter for key callback function
 *
 * @return
 *		NONE
 */
typedef void (*KeyCallbackFunc)(KeyCbParam * params);


/**
 * @brief
 *		Key init function
 *
 * @param
 *		void
 *
 * @return
 *		NONE
 */
typedef void (*KeyInitFunc)(void);

/**
 * @brief
 *		Key scan function
 *
 * @param
 *		event Key event with key value
 *
 * @return
 *		Key value
 */
typedef KeyValue (*KeyScanFunc)(KeyEvent *event);




/**
 * Key context
 */
typedef struct _KeyContext
{
	KeyCallbackFunc		callbackFunc;
	KeyInitFunc			initFunc;
	KeyScanFunc			scanFunc;
}KeyContext;


/**
 * @brief
 *		Key initialization function
 *
 * @param
 *		callback Callback function for receiving key event
 *
 * @return
 *		0 for initializing successful, otherwise failed
 */
KeyStatus KeyInit(void);

/**
 * @brief
 *		Key deinit function
 *
 * @param
 *		NONE
 *
 * @return
 *		NONE
 */
void KeyDeinit(void);

/**
 * @brief
 *		Register a callback function for a type of key
 *
 * @param
 *		keyCt	Key context
 * @param
 *		keyType	Key type
 *
 * @return
 *		0 for registering successful, otherwise failed
 */
KeyStatus KeyRegister(KeyType keyType, KeyContext * keyCt);

/**
 * @brief
 *		Deregister a key type
 *
 * @param
 *		keyType	Key type
 *
 * @return
 *		0 for registering successful, otherwise failed
 */
KeyStatus KeyDeregister(KeyType keyType);


/**
 * @brief
 *		Key scan function
 *
 * @param
 *		NONE
 *
 * @return
 *		NONE
 */
void KeyScan(void);

#endif /*__KEY_H__*/

