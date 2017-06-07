/**
 **************************************************************************************
 * @file    app_mode.c
 * @brief   APP mode
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
#include "app_mode.h"

/**
 * @brief
 *		Enter a new app mode
 *
 * @param
 *		mode The new app mode
 *
 * @return 
 *		NONE
 */
void EnterMode(AppMode mode)
{
//	WifiAudioPlayStart();
	WifiAudioPlayCreate(GetMainMessageHandle());
}

/**
 * @brief
 *		Exit a app mode
 *
 * @param
 *		mode The app mode to exit
 *
 * @return 
 *		NONE
 */
void ExitMode(AppMode mode)
{
	
}




