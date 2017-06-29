

typedef enum
{
	EffectTypeVb,
	EffectType3D
}EffectType;

typedef enum
{
	VbCmdEnDis,
	VbCmdCutoffFreq,
	VbCmdIntensity,
	VbCmdEnhanced
}EffectVbCmd;

typedef enum
{
	ThrDimEnDis,
	ThrDimDepth,
	ThrDimPreGain,
	ThrDimPostGain
}EffectThrDimCmd;

BOOL AudioCoreMixInit(void);

BOOL AudioCoreMixDeinit(void);

/**
 * Source related functions
 */
BOOL AudioCoreMixSourceRegister(AudioCoreIndex srcIndex, AudioCoreGetData getSrcData);

BOOL AudioCoreMixEnable(AudioCoreIndex srcIndex);

BOOL AudioCoreMixSourceDisable(AudioCoreIndex srcIndex);

BOOL AudioCoreMixSourcePcmConfig(AudioCoreIndex srcIndex, AudioCorePcmParams *pcmParams);

BOOL AudioCoreMixSourceGainConfig(AudioCoreIndex srcIndex, int16_t gain);

/**
 * Sink related functions
 */
BOOL AudioCoreMixSinkRegister(AudioCoreIndex sinkIndex, AudioCorePutData putSinkData);

BOOL AudioCoreMixSinkEnable(AudioCoreIndex sinkIndex);

BOOL AudioCoreMixSinkDisable(AudioCoreIndex sinkIndex);

BOOL AudioCoreMixSinkPcmConfig(AudioCoreIndex sinkIndex, AudioCorePcmParams *pcmParams);

BOOL AudioCoreMixSinkGainConfig(AudioCoreIndex sinkIndex, int16_t gain);


uint32_t AudioCoreMixPostEffectConfig(EffectType effectType, uint32_t cmd, uint32_t param);


void AudioCoreMixProcess(void);
