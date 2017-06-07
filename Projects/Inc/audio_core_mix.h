

BOOL AC_MixInit(void);

BOOL AC_MixDeinit(void);

/**
 * Source related functions
 */
BOOL AC_MixSourceGetDataRegister(AudioCoreIndex srcIndex, AudioCoreGetData getSrcData);

BOOL AC_MixSourceEnable(AudioCoreIndex srcIndex);

BOOL AC_MixSourceDisable(AudioCoreIndex srcIndex);

BOOL AC_MixSourcePcmParamsConfig(AudioCoreIndex srcIndex, AudioCorePcmParams *pcmParams);

BOOL AC_MixSourceGainConfig(AudioCoreIndex srcIndex, int16_t gain);

/**
 * Sink related functions
 */
BOOL AC_MixSinkPutDataRegister(AudioCoreIndex sinkIndex, AudioCorePutData putSinkData);

BOOL AC_MixSinkEnable(AudioCoreIndex sinkIndex);

BOOL AC_MixSinkDisable(AudioCoreIndex sinkIndex);

BOOL AC_MixSinkPcmParamsConfig(AudioCoreIndex sinkIndex, AudioCorePcmParams *pcmParams);

BOOL AC_MixSinkGainConfig(AudioCoreIndex sinkIndex, int16_t gain);


void AC_MixProcess(void);
