/*
 * flowsensor.h
 *
 *  Created on: 8/06/2016
 *      Author: michaelarthur
 */

#ifndef SOURCE_FLOWSENSOR_H_
#define SOURCE_FLOWSENSOR_H_


#include "fsl_port.h"
#include "fsl_gpio.h"
#include "fsl_adc16.h"
#include "clock_config.h"
#include "board.h"


#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

void initSensor();
uint32_t readSensor();

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

#endif /* SOURCE_FLOWSENSOR_H_ */
