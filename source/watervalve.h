/*
 * watervalve.h
 *
 *  Created on: 25/05/2016
 *      Author: michaelarthur
 */

#ifndef SOURCE_WATERVALVE_H_
#define SOURCE_WATERVALVE_H_

#include "fsl_port.h"
#include "fsl_gpio.h"


#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/


void openValve();
void closeValve();
void resetLow();
void initState();

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

#endif /* SOURCE_WATERVALVE_H_ */
