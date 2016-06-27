/*
 * rtc.c
 *
 *  Created on: 27/06/2016
 *      Author: michaelarthur
 */

#include "fsl_rtc.h"
#include "rtc.h"


uint32_t sec;
uint32_t currSeconds;
rtc_datetime_t date;


void BOARD_SetRtcClockSource(void)
{
    /* Enable the RTC 32KHz oscillator */
    RTC->CR |= RTC_CR_OSCE_MASK;
}


void init_clock() {

	rtc_config_t rtcConfig;

	/* Init RTC */
	/*
	 * rtcConfig.wakeupSelect = false;
	 * rtcConfig.updateMode = false;
	 * rtcConfig.supervisorAccess = false;
	 * rtcConfig.compensationInterval = 0;
	 * rtcConfig.compensationTime = 0;
	 */
	RTC_GetDefaultConfig(&rtcConfig);
	RTC_Init(RTC, &rtcConfig);
	/* Select RTC clock source */
	BOARD_SetRtcClockSource();


	/* Set a start date time and start RT */
	date.year = 2016U;
	date.month = 3U;
	date.day = 25U;
	date.hour = 0U;
	date.minute = 0;
	date.second = 0;

	/* RTC time counter has to be stopped before setting the date & time in the TSR register */
	RTC_StopTimer(RTC);

	/* Set RTC time to default */
	RTC_SetDatetime(RTC, &date);

	/* Start the RTC time counter */
	RTC_StartTimer(RTC);
}





