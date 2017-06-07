/**
 **************************************************************************************
 * @file    key.c
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


#include "type.h"
#include "key.h"
#include "mv_list.h"
#include "freertos.h"
#include "app_message.h"

/***************************************************************************************
 *
 * External defines
 *
 */



/***************************************************************************************
 *
 * Internal defines
 *
 */

typedef struct _KeyNode
{
	KeyType				type;
	KeyContext			key;
}KeyNode;

/***************************************************************************************
 *
 * Internal varibles
 *
 */

static MVList	keyList;


/***************************************************************************************
 *
 * Internal functions
 *
 */

static MVListNode * FindKeyNodeWithType(KeyType keyType)
{
	KeyNode 		*keyNode = NULL;
	MVListNode		*tempNode;
	
	if(MVIsListEmpty(&keyList))
		return NULL;

	tempNode = MVGetHeadNode(&keyList);
	
	while(tempNode)
	{
		keyNode = (KeyNode*)MVGetNodeContext(tempNode);

		if(keyNode->type == keyType)
			break;

		tempNode = MVGetNextNode(tempNode);
	}

	return tempNode;
}

/***************************************************************************************
 *
 * APIs
 *
 */

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
KeyStatus KeyInit(void)
{
	MVListInit(&keyList);
	return KEY_STATUS_SUCCESS;
}

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
void KeyDeinit(void)
{
	MVListNode	*tempNode;
	KeyNode		*keyNode;

	/* Clear the key list */
	while(!MVIsListEmpty(&keyList))
	{
		tempNode = MVGetHeadNode(&keyList);

		keyNode = (KeyNode *)MVGetNodeContext(tempNode);
		vPortFree(keyNode);

		MVRemoveNode(&keyList, tempNode);
	}
}

/**
 * @brief
 *		Register a callback function for a type of key
 *
 * @param
 *		keyType	Key type
 * @param
 *		callback Callback function for receiving key event
 *
 * @return
 *		0 for registering successful, otherwise failed
 */
KeyStatus KeyRegister(KeyType keyType, KeyContext * keyCt)
{
	KeyNode 		*keyNode = NULL;
	MVListNode		*tempNode;

	/* Parameters check */
	if(keyCt == NULL)
		return KEY_STATUS_FAILED;


	/*
	 * Check the key type whether it has been registered
	 */
	tempNode = FindKeyNodeWithType(keyType);
	if(tempNode)
		return KEY_STATUS_ALREADY_EXIST;


	/*
	 * Make a new key node
	 */
	keyNode = (KeyNode*)pvPortMalloc(sizeof(KeyNode));

	if(keyNode == NULL)
	{
		return KEY_STATUS_FAILED;
	}

	keyNode->type				= keyType;
	keyNode->key.callbackFunc	= keyCt->callbackFunc;
	keyNode->key.initFunc		= keyCt->initFunc;
	keyNode->key.scanFunc		= keyCt->scanFunc;

	MVInsertNodeToTail(&keyList, keyNode);

	/* Init the key */
	keyCt->initFunc();

	return KEY_STATUS_SUCCESS;
}

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
KeyStatus KeyDeregister(KeyType keyType)
{
	KeyNode			*keyNode;
	MVListNode		*tempNode;

	tempNode = FindKeyNodeWithType(keyType);

	if(!tempNode)
		return KEY_STATUS_NOT_FOUND;

	keyNode = (KeyNode *)MVGetNodeContext(tempNode);
	vPortFree(keyNode);

	MVRemoveNode(&keyList, tempNode);

	return KEY_STATUS_SUCCESS;
}


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
void KeyScan(void)
{
	MVListNode		*tempNode;

	if(MVIsListEmpty(&keyList))
		return;

	tempNode = MVGetHeadNode(&keyList);

	while(tempNode)
	{
		KeyNode 	*keyNode;
		KeyValue	value;
		KeyEvent	event;

		keyNode = (KeyNode *)MVGetNodeContext(tempNode);

		value = keyNode->key.scanFunc(&event);

		if(value != INVAILD_KEY_VALUE)
		{
			KeyCbParam		keyParams;

			keyParams.event	= event;
			keyParams.type	= keyNode->type;
			keyParams.value = value;

			keyNode->key.callbackFunc(&keyParams);
		}

		tempNode = MVGetNextNode(tempNode);
	}
}


