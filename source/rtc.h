/*
 * rtc.h
 *
 *  Created on: 27/06/2016
 *      Author: michaelarthur
 */

#ifndef SOURCE_RTC_H_
#define SOURCE_RTC_H_

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

void init_clock();
void BOARD_SetRtcClockSource(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

#endif /* SOURCE_RTC_H_ */
