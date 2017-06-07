/**
 **************************************************************************************
 * @file    mv_list.h
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


#ifndef __MV_LIST_H__
#define __MV_LIST_H__

#include "type.h"

typedef struct _MVListNode
{
    struct _MVListNode *pre;
    struct _MVListNode *next;
    void	*context;
}MVListNode;

typedef struct  _MVList 
{
    MVListNode	*head;
    MVListNode	*tail;
    uint32_t	count;
}MVList;

bool MVListInit(MVList *list);

bool MVInsertNodeToHead(MVList *list, void * context);

bool MVInsertNodeToTail(MVList *list, void * context);

bool MVRemoveNode(MVList *list, MVListNode *node);

#define MVGetNodeContext(node)		(node)->context

#define MVGetHeadNode(list)			((list)->head)
#define MVGetHeadContext(list)		((list)->head->context)

#define MVGetTailNode(list)			((list)->tail)
#define MVGetTailContext(list)		((list)->tail->context)

#define MVGetNextNode(node)			((node)->next)
#define MVGetNextContext(node)		((node)->next->context)

#define MVGetPreNode(node)			((node)->pre)
#define MVGetPreContext(node)		((node)->pre->context)

#define MVIsListEmpty(list)			((list)->count == 0)


#endif /*__MV_LIST_H__*/
