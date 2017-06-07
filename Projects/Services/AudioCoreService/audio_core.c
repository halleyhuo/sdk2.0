/**
 **************************************************************************************
 * @file    audio_core.c
 * @brief   audio core 
 *
 * @author  Sam
 * @version V1.0.0
 *
 * $Created: 2016-6-29 13:06:47$
 *
 * @Copyright (C) 2016, Shanghai Mountain View Silicon Co.,Ltd. All rights reserved.
 **************************************************************************************
 */
#include <string.h>

#include "type.h"
#include "audio_core.h"
#include "audio_core_i.h"




extern AudioCoreModeFunc * MixModeFuncGet(void);
extern AudioCoreModeFunc * AecModeFuncGet(void);


static AudioCoreContext		audioCore;
//static AudioCoreContext		*audioCore;

#define AUDIO_CORE(x)		(audioCore.x)
//#define AUDIO_CORE(x)		(audioCore->x)

AudioCoreModeFunc		*modeFunc = NULL;

/*************************************************************************************
 *
 * List related functions
 */

/**
 * Add the node into the tail of souce list
 */
static AudioCoreHandle AddToSourceList(AudioCoreSourceNode *node)
{
	AudioCoreHandle		handle = 0;

	if(node == NULL)
		return 0;

	if(AUDIO_CORE(sourceList).head == NULL) /* First node*/
	{
		/* set Handle */
		handle = 1;

		AUDIO_CORE(sourceList).head = node;
		AUDIO_CORE(sourceList).tail = node;
		AUDIO_CORE(sourceList).count = 1;

	}
	else
	{
		/* set handle*/
		handle = AUDIO_CORE(sourceList).tail->source.handle + 1;

		node->pre = AUDIO_CORE(sourceList).tail;
		AUDIO_CORE(sourceList).tail->next = node;
		AUDIO_CORE(sourceList).tail = node;
		AUDIO_CORE(sourceList).count++;
	}

	return handle;
}

/**
 * Remove the node from the source list
 * And return the removed node
 */
static AudioCoreSourceNode * RemoveFromSourceList(AudioCoreHandle handle)
{
	AudioCoreSourceNode *pTemp;

	pTemp = AUDIO_CORE(sourceList).head;

	while(pTemp)
	{
		if(pTemp->source.handle == handle)
			break;

		pTemp = pTemp->next;
	}

	/*
	 * If find the node, remove it from list
	 */
	if(pTemp) // find the node
	{
		if(pTemp->next == NULL)	// the tail node
		{
			AUDIO_CORE(sourceList).tail = pTemp->pre;
			AUDIO_CORE(sourceList).tail->next = NULL;
		}
		else // other nodes
		{
			pTemp->pre->next = pTemp->next;
			pTemp->next->pre = pTemp->pre;
		}

		AUDIO_CORE(sourceList).count--;
	}

	/* Can't find the node*/
	return pTemp;
}

static AudioCoreSourceNode * GetFromSourceList(AudioCoreHandle handle)
{
	AudioCoreSourceNode *pTemp;

	pTemp = AUDIO_CORE(sourceList).head;

	while(pTemp)
	{
		if(pTemp->source.handle == handle)
			break;

		pTemp = pTemp->next;
	}

	/* Can't find the node*/
	return pTemp;
}

static AudioCoreSourceNode * RemoveHeadNodeFromSourceList(void)
{
	AudioCoreSourceNode *pTemp;

	pTemp = AUDIO_CORE(sourceList).head;

	if(pTemp != NULL)
	{
		if(pTemp->next == NULL) // only one node in list
		{
			AUDIO_CORE(sourceList).head = NULL;
			AUDIO_CORE(sourceList).tail = NULL;
		}
		else // two or more nodes in list
		{
			AUDIO_CORE(sourceList).head = pTemp->next;
			pTemp->next->pre = AUDIO_CORE(sourceList).head;
		}

		AUDIO_CORE(sourceList).count--;
	}

	return pTemp;
}

/**
 * Add the node into the tail of sink list
 */
static AudioCoreHandle AddToSinkList(AudioCoreSinkNode *node)
{

	AudioCoreHandle		handle = 0;

	if(node == NULL)
		return 0;

	if(AUDIO_CORE(sinkList).head == NULL) /* First node*/
	{
		/* set Handle */
		handle = 1;

		AUDIO_CORE(sinkList).head = node;
		AUDIO_CORE(sinkList).tail = node;
		AUDIO_CORE(sinkList).count = 1;
	}
	else
	{
		/* set handle*/
		handle = AUDIO_CORE(sinkList).tail->sink.handle + 1;

		node->pre = AUDIO_CORE(sinkList).tail;
		AUDIO_CORE(sinkList).tail->next = node;
		AUDIO_CORE(sinkList).tail = node;
		AUDIO_CORE(sinkList).count++;
	}

	return handle;
}

/**
 * Remove the node from the sink list
 * And return the removed node
 */
static AudioCoreSinkNode * RemoveFromSinkList(AudioCoreHandle handle)
{
	AudioCoreSinkNode *pTemp;

	pTemp = AUDIO_CORE(sinkList).head;

	while(pTemp)
	{
		if(pTemp->sink.handle == handle)
			break;

		pTemp = pTemp->next;
	}

	/*
	 * If find the node, remove it from list
	 */
	if(pTemp) // find the node
	{
		if(pTemp->next == NULL) // the tail node
		{
			AUDIO_CORE(sinkList).tail = pTemp->pre;
			AUDIO_CORE(sinkList).tail->next = NULL;
		}
		else // other nodes
		{
			pTemp->pre->next = pTemp->next;
			pTemp->next->pre = pTemp->pre;
		}

		AUDIO_CORE(sinkList).count--;
	}

	return pTemp;
}

static AudioCoreSinkNode * GetFromSinkList(AudioCoreHandle handle)
{
	AudioCoreSinkNode *pTemp;

	pTemp = AUDIO_CORE(sinkList).head;

	while(pTemp)
	{
		if(pTemp->sink.handle == handle)
			break;

		pTemp = pTemp->next;
	}

	return pTemp;
}


static AudioCoreSinkNode * RemoveHeadNodeFromSinkList(void)
{
	AudioCoreSinkNode *pTemp;

	pTemp = AUDIO_CORE(sinkList).head;

	if(pTemp != NULL)
	{
		if(pTemp->next == NULL) // only one node in list
		{
			AUDIO_CORE(sinkList).head = NULL;
			AUDIO_CORE(sinkList).tail = NULL;
		}
		else // two or more nodes in list
		{
			AUDIO_CORE(sinkList).head = pTemp->next;
			pTemp->next->pre = AUDIO_CORE(sinkList).head;
		}

		AUDIO_CORE(sinkList).count--;
	}

	return pTemp;
}


/**************************************************************************
 *
 * Audio Core APIs
 */


AudioCoreContext *GetAudioCoreContext(void)
{
	return &audioCore;
}

bool AuidoCoreInit(AudioCoreMode mode)
{
	AUDIO_CORE(mode)				= mode;

	AUDIO_CORE(sourceList).head		= NULL;
	AUDIO_CORE(sourceList).tail		= NULL;
	AUDIO_CORE(sourceList).count	= 0;

	AUDIO_CORE(sinkList).head		= NULL;
	AUDIO_CORE(sinkList).tail		= NULL;
	AUDIO_CORE(sinkList).count		= 0;

	switch(AUDIO_CORE(mode))
	{
		case AUDIO_CORE_MODE_MIX:
			modeFunc = MixModeFuncGet();
			break;
		case AUDIO_CORE_MODE_AEC:
			modeFunc = AecModeFuncGet();
			break;

		default:
			return FALSE;
	}

	if(modeFunc == NULL)
		return FALSE;

	modeFunc->initFunc();

	return TRUE;
}

void AudioCoreDeinit(void)
{
	AudioCoreSourceNode	*tempSrcNode;
	AudioCoreSinkNode	*tempSinkNode;

	/* Remove head of source list*/
	tempSrcNode = RemoveHeadNodeFromSourceList();
	while(tempSrcNode)
	{
		modeFunc->deregSrcFunc(tempSrcNode);

		/*Get next node*/
		tempSrcNode = RemoveHeadNodeFromSourceList();
	}

	/* Remove head of sink list*/
	tempSinkNode = RemoveHeadNodeFromSinkList();
	while(tempSinkNode)
	{
		modeFunc->deregSinkFunc(tempSinkNode);

		/*Get next node*/
		tempSinkNode = RemoveHeadNodeFromSinkList();
	}

	modeFunc->deinitFunc();

}

AudioCoreHandle AudioCoreRegisterSource(AudioCoreGetData getSrcData, AudioCoreSrcType srcType)
{
	AudioCoreSourceNode		*node;
	AudioCoreHandle			handle = (AudioCoreHandle)0;

	if(modeFunc && modeFunc->regSrcFunc)
	{
		node = modeFunc->regSrcFunc(getSrcData, srcType);
	}
	else
	{
		goto ERR_END;
	}

	/* Add the node to audio core source list*/
	handle = AddToSourceList(node);
	if(handle == 0)
	{
		modeFunc->deregSrcFunc(node);
		goto ERR_END;
	}

	/*save the handle*/
	node->source.handle = handle;
	return handle;


ERR_END:
	return (AudioCoreHandle)0;
}


bool AudioCoreDisableSource(AudioCoreHandle srcHandle)
{
	AudioCoreSourceNode		*node;

	node = GetFromSourceList(srcHandle);
	if(node)
	{
		node->source.enable = FALSE;
		return TRUE;
	}

	return FALSE;
}

bool AudioCoreEnableSource(AudioCoreHandle srcHandle)
{
	AudioCoreSourceNode		*node;

	node = GetFromSourceList(srcHandle);
	if(node)
	{
		node->source.enable = TRUE;
		return TRUE;
	}

	return FALSE;
}

bool AudioCoreSourceConfig(AudioCoreHandle srcHandle, AudioCoreConfigType configType, void * configParams)
{
	AudioCoreSourceNode 	*node;

	node = GetFromSourceList(srcHandle);
	if(node)
	{
		if(modeFunc && modeFunc->configSrcFunc)
		{
			return modeFunc->configSrcFunc(node, configType, configParams);
		}
	}

	return FALSE;
}

bool AudioCoreDeregisterSource(AudioCoreHandle srcHandle)
{
	AudioCoreSourceNode		*node;

	if(srcHandle == 0)
		return TRUE;

	node = RemoveFromSourceList(srcHandle);

	/* release resouces of the node*/
	if(modeFunc && modeFunc->deregSrcFunc)
	{
		modeFunc->deregSrcFunc(node);
	}
	
	return TRUE;
}

AudioCoreHandle AudioCoreRegisterSink(AudioCorePutData putSinkData, AudioCoreSinkType sinkType)
{
	AudioCoreSinkNode		*node;
	AudioCoreHandle			handle = (AudioCoreHandle)0;


	if(modeFunc && modeFunc->regSinkFunc)
	{
		node = modeFunc->regSinkFunc(putSinkData, sinkType);
	}
	else
	{
		goto ERR_END;
	}


	/* Add the node to audio core sink list*/
	handle = AddToSinkList(node);
	if(handle == (AudioCoreHandle)0)
	{
		modeFunc->deregSinkFunc(node);
		goto ERR_END;
	}

	/*save the handle*/
	node->sink.handle = handle;

	return handle;


ERR_END:
	return (AudioCoreHandle)0;
}

bool AudioCoreEnableSink(AudioCoreHandle sinkHandle)
{
	AudioCoreSinkNode		*node;

	node = GetFromSinkList(sinkHandle);
	if(node)
	{
		node->sink.enable = TRUE;
		return TRUE;
	}

	return FALSE;
}

bool AudioCoreDisableSink(AudioCoreHandle sinkHandle)
{
	AudioCoreSinkNode		*node;

	node = GetFromSinkList(sinkHandle);
	if(node)
	{
		node->sink.enable = FALSE;
		return TRUE;
	}

	return FALSE;
}

bool AudioCoreSinkConfig(AudioCoreHandle sinkHandle, AudioCoreConfigType configType, void * configParams)
{
	AudioCoreSinkNode 	*node;

	node = GetFromSinkList(sinkHandle);
	if(node)
	{
		if(modeFunc && modeFunc->configSinkFunc)
		{
			return modeFunc->configSinkFunc(node, configType, configParams);
		}
	}

	return FALSE;
}

bool AudioCoreDeregisterSink(AudioCoreHandle sinkHandle)
{
	AudioCoreSinkNode		*node;

	if(sinkHandle == 0)
		return TRUE;

	node = RemoveFromSinkList(sinkHandle);

	/* release resouces of the node*/
	if(modeFunc && modeFunc->deregSinkFunc)
	{
		modeFunc->deregSinkFunc(node);
	}

	return TRUE;
}

void AudioCoreRun(void)
{
	modeFunc->processFunc();
}

