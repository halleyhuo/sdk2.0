

#include <string.h>
#include "type.h"
#include "FreeRTOS.h"
#include "audio_core_service.h"
#include "chip_info.h"
#include "app_config.h"

#include "audio_core_mix.h"
#include "virtual_bass.h"
#include "three_d.h"

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

#define DEFAULT_MIX_SRC_SAMPLE_LEN				192
#define MIX_SRC_BUFFER_LEN						(DEFAULT_MIX_SRC_SAMPLE_LEN * 4)

#define DEFAULT_MIX_SAMPLE_LEN					DEFAULT_MIX_SRC_SAMPLE_LEN
#define MIXED_BUFFER_LEN						(DEFAULT_MIX_SAMPLE_LEN * 4)

#define MAX_SOURCE_NUM						2
#define MAX_SINK_NUM						2

typedef enum
{
	MixStateStateGetData,
	MixStateMix,
	MixStateStartPutData,
	MixStatePuttingData
}MixState;

typedef struct _MixAcSource
{
	AudioCoreSource		source;
	uint8_t				*sourceBuf;
	uint16_t			validSampleLen;
	int16_t				gain;	
}MixAcSource;

typedef struct _MixAcSink
{
	AudioCoreSink		sink;
	BOOL				sinkPutDone;
	int16_t				gain;
}MixAcSink;

typedef struct _VbEffect
{
	VBContext			vbContext;
	BOOL				enable;
	uint32_t			cutoffFreq;
	uint32_t			intensity;
	uint32_t			enhanced;
}VbEffect;

typedef struct _ThrDimEffect
{
	ThreeDContext		thrDimContext;
	BOOL				enable;
	uint32_t			depth;
	uint32_t			preGain;
	uint32_t			postGain;
}ThrDimEffect;

typedef struct _MixAcContext
{
	MixAcSource			mixSource[MAX_SOURCE_NUM];
	MixAcSink			mixSink[MAX_SINK_NUM];

	MixState			mixState;
	AudioCorePcmParams	mixedPcmParams;
	uint32_t			mixedSampleLen;
	int16_t				*mixedBuf;

	// VB
	BOOL				vbInited;
	VbEffect			vbEffect;

	// 3D
	BOOL				thrDimInited;
	ThrDimEffect		thrDimEffect;
}MixAcContext;


/***************************************************************************************
 *
 * Internal varibles
 *
 */

static MixAcContext		mixAudioCore;

#define AC_MIX(x)			(mixAudioCore.x)
/***************************************************************************************
 *
 * Internal functions
 *
 */

static BOOL MixGetAndPreProcess(void)
{
	uint16_t				tempSampleLen = 0;
	uint8_t					i;


	for(i = 0; i < MAX_SOURCE_NUM; i++)
	{
		mixAudioCore.mixSource[i].validSampleLen = 0;

		if(mixAudioCore.mixSource[i].source.enable)
		{
			if(mixAudioCore.mixSource[i].source.funcGetData)
			{
				mixAudioCore.mixSource[i].validSampleLen = mixAudioCore.mixSource[i].source.funcGetData(
																				mixAudioCore.mixSource[i].sourceBuf, 
																				DEFAULT_MIX_SRC_SAMPLE_LEN);

				/*
				 * TO DO : pre-process here
				 */

			}
		}

		tempSampleLen = tempSampleLen > mixAudioCore.mixSource[i].validSampleLen ? 
						tempSampleLen : mixAudioCore.mixSource[i].validSampleLen;
	}

	if(tempSampleLen == 0)
		return FALSE;

	return TRUE;
}

static uint32_t EffectVbParams(uint32_t cmd, uint32_t param)
{
	switch(cmd)
	{
		case VbCmdEnDis:
			if(param == 0)
			{
				mixAudioCore.vbEffect.enable = FALSE;
			}
			else
			{
				mixAudioCore.vbEffect.enable = TRUE;
			}
			break;

		case VbCmdCutoffFreq:
			mixAudioCore.vbEffect.cutoffFreq = param;
			mixAudioCore.vbInited = FALSE;
			break;

		case VbCmdIntensity:
			mixAudioCore.vbEffect.intensity = param;
			break;

		case VbCmdEnhanced:
			mixAudioCore.vbEffect.enhanced = param;
			break;

		default:
			break;
	}
}

static uint32_t Effect3DParams(uint32_t cmd, uint32_t param)
{
	switch(cmd)
	{
		case ThrDimEnDis:
			if(param == 0)
			{
				mixAudioCore.thrDimEffect.enable = FALSE;
			}
			else
			{
				mixAudioCore.thrDimEffect.enable = TRUE;
			}
			break;

		case ThrDimDepth:
			mixAudioCore.thrDimEffect.depth = param;
			break;

		case ThrDimPreGain:
			mixAudioCore.thrDimEffect.preGain = param;
			break;

		case ThrDimPostGain:
			mixAudioCore.thrDimEffect.postGain = param;
			break;

		default:
			break;
	}
}

static void MixPostProcess(void)
{
	if(mixAudioCore.vbEffect.enable)
	{
		if(!mixAudioCore.vbInited)
		{
			vb_init(&mixAudioCore.vbEffect.vbContext,
					mixAudioCore.mixedPcmParams.channelNums,
					mixAudioCore.mixedPcmParams.samplingRate,
					mixAudioCore.vbEffect.cutoffFreq);

			mixAudioCore.vbInited = TRUE;
		}

		vb_apply(&mixAudioCore.vbEffect.vbContext,
				mixAudioCore.mixedBuf,
				mixAudioCore.mixedBuf,
				mixAudioCore.mixedSampleLen,
				mixAudioCore.vbEffect.intensity,
				mixAudioCore.vbEffect.enhanced);
	}

	if(mixAudioCore.thrDimEffect.enable)
	{
		if(!mixAudioCore.thrDimInited)
		{
			int32_t		ret;
			ret = init_3d(&mixAudioCore.thrDimEffect.thrDimContext,
						mixAudioCore.mixedPcmParams.channelNums,
						mixAudioCore.mixedPcmParams.samplingRate);

			if(ret == THREE_D_ERROR_OK)
			{
				mixAudioCore.thrDimInited = TRUE;
			}
			else
			{
				mixAudioCore.thrDimInited = FALSE;
			}
		}

		if(mixAudioCore.thrDimInited && mixAudioCore.mixedPcmParams.channelNums == 2)
		{
			apply_3d(&mixAudioCore.thrDimEffect.thrDimContext,
					mixAudioCore.mixedBuf,
					mixAudioCore.mixedBuf,
					mixAudioCore.mixedSampleLen,
					mixAudioCore.thrDimEffect.depth,
					mixAudioCore.thrDimEffect.preGain,
					mixAudioCore.thrDimEffect.postGain);
		}
	}
}

static BOOL MixProcess(void)
{
	uint8_t					index;


	if(!CheckTx())
		return FALSE;

	/*Mix data*/
	mixAudioCore.mixedSampleLen = 0;
	memset(mixAudioCore.mixedBuf, 0, MIXED_BUFFER_LEN);


	for(index = 0; index < MAX_SOURCE_NUM; index++)
	{
		uint16_t		sampleLen;

		sampleLen = mixAudioCore.mixSource[index].validSampleLen;
		if(mixAudioCore.mixSource[index].source.enable)
		{
			if(sampleLen != 0)
			{
				switch(mixAudioCore.mixSource[index].source.pcmParams.channelNums)
				{
					case 1:			/* mono */
						break;

					case 2:			/* stereo */
						{
							uint16_t		i;
							int16_t			*srcBuf;
							int16_t 		*mixedBuf;

							srcBuf = mixAudioCore.mixSource[index].sourceBuf;
							mixedBuf = mixAudioCore.mixedBuf;

							for(i = 0; i < sampleLen; i++)
							{
								mixedBuf[i * 2]		= __ssat(mixedBuf[i * 2 + 0] + (int16_t)(srcBuf[i * 2]), 16);
								mixedBuf[i * 2 + 1]	= __ssat(mixedBuf[i * 2 + 1] + (int16_t)(srcBuf[i * 2 + 1]), 16);
							}
						}
						break;

					default:
						break;
				}
			}
		}

		mixAudioCore.mixedSampleLen = sampleLen > mixAudioCore.mixedSampleLen ? 
										sampleLen : mixAudioCore.mixedSampleLen;
	}

	/* TO DO : Post-Process */
	// Add Post-Process here	
//	MixPostProcess();

	return TRUE;
}

static bool MixPreparePut(void)
{
	uint8_t				index;

	for(index = 0; index < MAX_SINK_NUM; index++)
	{
		mixAudioCore.mixSink[index].sinkPutDone = FALSE;
	}
	return TRUE;
}

static BOOL MixPut(void)
{
	uint8_t				index;

	if(mixAudioCore.mixedSampleLen == 0)
	{
		return TRUE;
	}

	for(index = 0; index < MAX_SINK_NUM; index++)
	{
		if(mixAudioCore.mixSink[index].sinkPutDone)
		{
			continue;
		}

		if(mixAudioCore.mixSink[index].sink.enable)
		{
			if(mixAudioCore.mixSink[index].sink.funcPutData &&
				mixAudioCore.mixSink[index].sink.funcPutData(mixAudioCore.mixedBuf, mixAudioCore.mixedSampleLen))
			{
				mixAudioCore.mixSink[index].sinkPutDone = TRUE;
			}
		}
		else
		{
			mixAudioCore.mixSink[index].sinkPutDone = TRUE;
		}
	}

	/* Check whether all of sink have been put data*/
	for(index = 0; index < MAX_SINK_NUM; index++)
	{
		if(!mixAudioCore.mixSink[index].sinkPutDone)
		{
			break;
		}
	}

	if(index == MAX_SINK_NUM)
	{
		return TRUE;
	}

	return FALSE;
}




/***************************************************************************************
 *
 * APIs
 *
 */


BOOL AudioCoreMixInit(void)
{
	uint8_t			i;


	memset(&mixAudioCore, 0, sizeof(MixAcContext));

	/* Allocate source buffer */
	for(i = 0; i < MAX_SOURCE_NUM; i++)
	{
		mixAudioCore.mixSource[i].sourceBuf = (uint8_t *)pvPortMalloc(MIX_SRC_BUFFER_LEN);
		if(mixAudioCore.mixSource[i].sourceBuf == NULL)
			return FALSE;
	}

	/* Allocate mixed buffer */
	mixAudioCore.mixedBuf = (int16_t *)(VMEM_ADDR + AUDIOC_CORE_TRANSFER_OFFSET);

	if(mixAudioCore.mixedBuf == NULL)
		return FALSE;

	return TRUE;
}

BOOL AudioCoreMixDeinit(void)
{
	uint8_t			i;

	/* Free allocated source buffer */
	for(i = 0; i < MAX_SOURCE_NUM; i++)
	{
		if(mixAudioCore.mixSource[i].sourceBuf)
		{
			vPortFree(mixAudioCore.mixSource[i].sourceBuf);
			mixAudioCore.mixSource[i].sourceBuf = NULL;
		}
	}

	/* Free allocated mixed buffer */
	if(mixAudioCore.mixedBuf)
	{
		vPortFree(mixAudioCore.mixedBuf);
		mixAudioCore.mixedBuf = NULL;
	}

	return TRUE;
}

/**
 * Source related functions
 */
BOOL AudioCoreMixSourceRegister(AudioCoreIndex srcIndex, AudioCoreGetData getSrcData)
{
	if(srcIndex >= MAX_SOURCE_NUM)
		return FALSE;

	mixAudioCore.mixSource[srcIndex].source.funcGetData = getSrcData;

	return TRUE;
}

BOOL AudioCoreMixSourceEnable(AudioCoreIndex srcIndex)
{
	if(srcIndex >= MAX_SOURCE_NUM)
		return FALSE;

	mixAudioCore.mixSource[srcIndex].source.enable = TRUE;
}

BOOL AudioCoreMixSourceDisable(AudioCoreIndex srcIndex)
{
	if(srcIndex >= MAX_SOURCE_NUM)
		return FALSE;

	mixAudioCore.mixSource[srcIndex].source.enable = FALSE;
}

BOOL AudioCoreMixSourcePcmConfig(AudioCoreIndex srcIndex, AudioCorePcmParams *pcmParams)
{
	if(srcIndex >= MAX_SOURCE_NUM)
		return FALSE;

	memcpy(&mixAudioCore.mixSource[srcIndex].source.pcmParams, pcmParams, sizeof(AudioCorePcmParams));

	return TRUE;
}

BOOL AudioCoreMixSourceGainConfig(AudioCoreIndex srcIndex, int16_t gain)
{
	if(srcIndex >= MAX_SOURCE_NUM)
		return FALSE;

	mixAudioCore.mixSource[srcIndex].gain = gain;
}

/**
 * Sink related functions
 */
BOOL AudioCoreMixSinkRegister(AudioCoreIndex sinkIndex, AudioCorePutData putSinkData)
{
	if(sinkIndex >= MAX_SINK_NUM)
		return FALSE;

	mixAudioCore.mixSink[sinkIndex].sink.funcPutData = putSinkData;
}

BOOL AudioCoreMixSinkEnable(AudioCoreIndex sinkIndex)
{
	if(sinkIndex >= MAX_SINK_NUM)
		return FALSE;

	mixAudioCore.mixSink[sinkIndex].sink.enable = TRUE;
}

BOOL AudioCoreMixSinkDisable(AudioCoreIndex sinkIndex)
{
	if(sinkIndex >= MAX_SINK_NUM)
		return FALSE;

	mixAudioCore.mixSink[sinkIndex].sink.enable = FALSE;
}

BOOL AudioCoreMixSinkPcmConfig(AudioCoreIndex sinkIndex, AudioCorePcmParams *pcmParams)
{
	if(sinkIndex >= MAX_SINK_NUM)
		return FALSE;

	memcpy(&mixAudioCore.mixSink[sinkIndex].sink.pcmParams, pcmParams, sizeof(AudioCorePcmParams));

	return TRUE;
}

BOOL AudioCoreMixSinkGainConfig(AudioCoreIndex sinkIndex, int16_t gain)
{
	if(sinkIndex >= MAX_SINK_NUM)
		return FALSE;

	mixAudioCore.mixSink[sinkIndex].gain = gain;
}


uint32_t AudioCoreMixPostEffectConfig(EffectType effectType, uint32_t cmd, uint32_t param)
{
	switch(effectType)
	{
		case EffectTypeVb:
			EffectVbParams(cmd, param);
			break;

		case EffectType3D:
			Effect3DParams(cmd, param);
			break;

		default:
			break;
	}
}

void AudioCoreMixProcess(void)
{
	BOOL		ret;

	switch(mixAudioCore.mixState)
	{
		case MixStateStateGetData:
			ret = MixGetAndPreProcess();
			if(!ret)
			{
				return;
			}
			mixAudioCore.mixState = MixStateMix;

		case MixStateMix:
			ret = MixProcess();
			if(!ret)
			{
				return;
			}
			mixAudioCore.mixState = MixStateStartPutData;

		case MixStateStartPutData:
			ret = MixPreparePut();
			if(!ret)
			{
				return;
			}
			mixAudioCore.mixState = MixStatePuttingData;

		case MixStatePuttingData:
			ret = MixPut();
			if(!ret)
			{
				return;
			}
			mixAudioCore.mixState = MixStateStateGetData;

		default:
			break;
	}

}

