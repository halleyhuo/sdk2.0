/**
 **************************************************************************************
 * @file    mv_list.c
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
#include "mv_list.h"
#include "freertos.h"

bool MVListInit(MVList *list)
{
	/* Parameters check */
	if(list == NULL)
		return FALSE;
	
	list->head = list->tail = NULL;
	list->count = 0;

	return TRUE;
}

bool MVInsertNodeToHead(MVList *list, void * context)
{
	MVListNode		*node;

	/* Parameters check */
	if(list == NULL || context == NULL)
		return FALSE;

	/* Create a node*/
	node = (MVListNode *)pvPortMalloc(sizeof(MVListNode));
	if(node == NULL)
		return FALSE;
	node->pre = NULL;
	node->next = NULL;
	node->context = context;

	/* Insert to head */
	if(list->count == 0)
	{
		list->head = node;
		list->tail = node;
	}
	else
	{
		node->next = list->head;
		list->head->pre = node;
		list->head = node;
	}

	/* count */
	list->count++;
	return TRUE;
	
}

bool MVInsertNodeToTail(MVList *list, void * context)
{
	MVListNode		*node;

	/* Parameters check */
	if(list == NULL || context == NULL)
		return FALSE;

	/* Create a node*/
	node = (MVListNode *)pvPortMalloc(sizeof(MVListNode));
	if(node == NULL)
		return FALSE;
	node->pre = NULL;
	node->next = NULL;
	node->context = context;

	/* Insert to tail */
	if(list->count == 0)
	{
		list->head = node;
		list->tail = node;
	}
	else
	{
		node->pre = list->tail;
		list->tail->next = node;
		list->tail = node;
	}
	/* count */
	list->count++;

	return TRUE;
}

bool MVRemoveNode(MVList *list, MVListNode *node)
{

	/* Parameters check */
	if(list == NULL || node == NULL)
		return FALSE;

	if(list->count == 0)	/*list is empty*/
		return FALSE;

	if(list->count == 1)
	{
		list->head = list->tail = NULL;
	}
	else
	{
		if(list->head == node)	/* head node*/
		{
			list->head = node->next;
		}
		else if(list->tail == node) /* tail node*/
		{
			list->tail = node->pre;
		}
		else
		{
			node->next->pre = node->pre;
			node->pre->next = node->next;
		}
	}
	
	vPortFree(node);
	list->count--;

	return TRUE;
}


