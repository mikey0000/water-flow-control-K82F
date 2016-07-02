/*
 * co2sensor.cpp
 *
 *  Created on: 28/06/2016
 *      Author: michaelarthur
 */

#include "fsl_adc16.h"
#include "fsl_debug_console.h"
#include "fsl_port.h"
#include "fsl_gpio.h"
#include "clock_config.h"
#include "board.h"

adc16_config_t adc16ConfigStruct;
adc16_channel_config_t adc16ChannelConfigStruct;


void init_co2sensor() {

 /*
     * adc16ConfigStruct.referenceVoltageSource = kADC16_ReferenceVoltageSourceVref;
     * adc16ConfigStruct.clockSource = kADC16_ClockSourceAsynchronousClock;
     * adc16ConfigStruct.enableAsynchronousClock = true;
     * adc16ConfigStruct.clockDivider = kADC16_ClockDivider8;
     * adc16ConfigStruct.resolution = kADC16_ResolutionSE12Bit;
     * adc16ConfigStruct.longSampleMode = kADC16_LongSampleDisabled;
     * adc16ConfigStruct.enableHighSpeed = false;
     * adc16ConfigStruct.enableLowPower = false;
     * adc16ConfigStruct.enableContinuousConversion = false;
     */
	//     adc16ConfigStruct.referenceVoltageSource = kADC16_ReferenceVoltageSourceVref;
	//     adc16ConfigStruct.clockSource = kADC16_ClockSourceAsynchronousClock;
	//     adc16ConfigStruct.enableAsynchronousClock = true;
	//     adc16ConfigStruct.clockDivider = kADC16_ClockDivider8;
	//     adc16ConfigStruct.resolution = kADC16_ResolutionSE8Bit;
	//     adc16ConfigStruct.longSampleMode = kADC16_LongSampleDisabled;
	//     adc16ConfigStruct.enableHighSpeed = false;
	//     adc16ConfigStruct.enableLowPower = false;
	//     adc16ConfigStruct.enableContinuousConversion = true;


    ADC16_GetDefaultConfig(&adc16ConfigStruct);
    ADC16_Init(CO2_SENSOR_BASE, &adc16ConfigStruct);
    ADC16_EnableHardwareTrigger(CO2_SENSOR_BASE, false); /* Make sure the software trigger is used. */
	#if defined(FSL_FEATURE_ADC16_HAS_CALIBRATION) && FSL_FEATURE_ADC16_HAS_CALIBRATION
		if (kStatus_Success == ADC16_DoAutoCalibration(CO2_SENSOR_BASE))
		{
			PRINTF("ADC16_DoAutoCalibration() Done.\r\n");
		}
		else
		{
			PRINTF("ADC16_DoAutoCalibration() Failed.\r\n");
		}
	#endif /* FSL_FEATURE_ADC16_HAS_CALIBRATION */
		PRINTF("Press any key to get user channel's ADC value ...\r\n");

		adc16ChannelConfigStruct.channelNumber = CO2_SENSOR_USER_CHANNEL;
		adc16ChannelConfigStruct.enableInterruptOnConversionCompleted = false;
	#if defined(FSL_FEATURE_ADC16_HAS_DIFF_MODE) && FSL_FEATURE_ADC16_HAS_DIFF_MODE
		adc16ChannelConfigStruct.enableDifferentialConversion = false;
	#endif /* FSL_FEATURE_ADC16_HAS_DIFF_MODE */


}

uint32_t readCO2Sensor() {
	ADC16_SetChannelConfig(CO2_SENSOR_BASE, CO2_SENSOR_CHANNEL_GROUP, &adc16ChannelConfigStruct);
	while (0U == (kADC16_ChannelConversionDoneFlag &
				  ADC16_GetChannelStatusFlags(CO2_SENSOR_BASE, CO2_SENSOR_CHANNEL_GROUP)))
	{
	}
	PRINTF("ADC Value: %d\r\n", ADC16_GetChannelConversionValue(CO2_SENSOR_BASE, CO2_SENSOR_CHANNEL_GROUP));
}
