/**
 **************************************************************************************
 * @file    main_app.h
 * @brief   Program Entry 
 *
 * @author  halley
 * @version V1.0.0
 *
 * $Created: 2016-6-29 13:06:47$
 *
 * @Copyright (C) 2016, Shanghai Mountain View Silicon Co.,Ltd. All rights reserved.
 **************************************************************************************
 */

#ifndef __MAIN_APP_H__
#define __MAIN_APP_H__


#include "type.h"
#include "rtos_api.h"

/**
 * @brief
 *		Start a main program task.
 * @param
 *		NONE
 * @return	
 */
int32_t MainAppTaskStart(void);


/**
 * @brief
 *		Get message receive handle of main app
 * 
 * @param
 *		NONE
 *
 * @return
 *		MessageHandle
 */

MessageHandle GetMainMessageHandle(void);

#endif /*__MAIN_APP_H__*/
