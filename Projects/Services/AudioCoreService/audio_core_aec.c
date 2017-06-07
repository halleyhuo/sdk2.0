
#include <string.h>
#include "type.h"
#include "FreeRTOS.h"



/***************************************************************************************
 *
 * External defines
 *
 */
#define DEFAULT_AEC_SAMPLE_LEN			128

/***************************************************************************************
 *
 * Internal defines
 *
 */

static BOOL AecInitFunc(void);
static BOOL AecDeinitFunc(void);
static AudioCoreSourceNode * AecRegisterSrcFunc(AudioCoreGetData getSrcData, AudioCoreSrcType srcType);
static BOOL AecConfigSrcFunc(AudioCoreConfigType configType, void * configParams);
static BOOL AecDeregisterSrcFunc(AudioCoreSourceNode *node);
static AudioCoreSinkNode * AecRegisterSinkFunc(AudioCorePutData putSinkData, AudioCoreSinkType sinkType);
static BOOL AecDeregisterSinkFunc(AudioCoreSinkNode *node);
static BOOL AecConfigSinkFunc(AudioCoreConfigType configType, void * configParams);
static void AecProcessFunc(void);

/***************************************************************************************
 *
 * Internal varibles
 *
 */


static AudioCoreContext *pAudioCore = NULL;


static AudioCoreModeFunc	aecModeFunc = 
{
	AecInitFunc,
	AecDeinitFunc,
	AecRegisterSrcFunc,
	AecDeregisterSrcFunc,
	AecConfigSrcFunc,
	AecRegisterSinkFunc,
	AecDeregisterSinkFunc,
	AecConfigSinkFunc,
	AecProcessFunc
};

/***************************************************************************************
 *
 * Internal functions
 *
 */

static BOOL AecInitFunc(void)
{
	pAudioCore = GetAudioCoreContext();

	return TRUE;
}

static BOOL AecDeinitFunc(void)
{
	pAudioCore = NULL;

	return TRUE;
}

static AudioCoreSourceNode * AecRegisterSrcFunc(AudioCoreGetData getSrcData, AudioCoreSrcType srcType)
{
	AudioCoreSourceNode				*node;

	node = (AudioCoreSourceNode *)pvPortMalloc(sizeof(AudioCoreSourceNode));

	if(node == NULL)
		return NULL;

	node->next = NULL;
	node->pre = NULL;
	node->validSampleLen = 0;

	node->source.handle		= 0;
	node->source.enable		= FALSE;
	node->source.srcType	= srcType;
	node->source.getSrcData	= getSrcData;
	node->source.srcBuf		= (int16_t *)pvPortMalloc(DEFAULT_AEC_SAMPLE_LEN*4);

	return node;
}

static BOOL AecDeregisterSrcFunc(AudioCoreSourceNode *node)
{
	if(node == NULL)
		return FALSE;

	if(node->source.srcBuf)
	{
		vPortFree(node->source.srcBuf);
	}

	vPortFree(node);

	return TRUE;
}

static BOOL AecConfigSrcFunc(AudioCoreConfigType configType, void * configParams)
{
	return TRUE;
}

static AudioCoreSinkNode * AecRegisterSinkFunc(AudioCorePutData putSinkData, AudioCoreSinkType sinkType)
{
	AudioCoreSinkNode		*node;

	node = (AudioCoreSinkNode *)pvPortMalloc(sizeof(AudioCoreSinkNode));

	if(node == NULL)
		return NULL;

	node->next = NULL;
	node->pre = NULL;
	node->sinkPutDone = TRUE;

	node->sink.handle		= 0;
	node->sink.enable		= 0;
	node->sink.putSinkData	= putSinkData;
	node->sink.sinkType		= sinkType;

	return node;
}

static BOOL AecConfigSinkFunc(AudioCoreConfigType configType, void * configParams)
{
	return TRUE;
}

static BOOL AecDeregisterSinkFunc(AudioCoreSinkNode *node)
{
	if(node)
	{
		vPortFree(node);
		return TRUE;
	}

	return FALSE;
}



static void AecProcessFunc(void)
{


}



/***************************************************************************************
 *
 * APIs
 *
 */

AudioCoreModeFunc * AecModeFuncGet(void)
{
	return &aecModeFunc;
}

