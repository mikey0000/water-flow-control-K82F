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
#include "clock_config.h"
#include "board.h"


#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/


typedef struct WaterFlow {
	float litresPerMinute;
	uint8_t millilitresPerSec;
} waterFlow;

void initSensor();
uint32_t readSensor();
waterFlow litresPerMinute(int *pulseCount);

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

#endif /* SOURCE_FLOWSENSOR_H_ */
