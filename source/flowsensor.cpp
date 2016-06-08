/*
 * flowsensor.cpp
 *
 *  Created on: 8/06/2016
 *      Author: michaelarthur
 */

#include "flowsensor.h"
#include "fsl_debug_console.h"

    adc16_config_t adc16ConfigStruct;
    adc16_channel_config_t adc16ChannelConfigStruct;

    gpio_pin_config_t power_config =
	{
		kGPIO_DigitalOutput, 1,
	};


void initSensor() {
	GPIO_PinInit(FLOW_SENSOR_VCC_GPIO, FLOW_SENSOR_VCC_PIN, &power_config);
	GPIO_WritePinOutput(FLOW_SENSOR_VCC_GPIO, FLOW_SENSOR_VCC_PIN, 1U);


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
    ADC16_GetDefaultConfig(&adc16ConfigStruct);
    ADC16_Init(FLOW_SENSOR_BASE, &adc16ConfigStruct);
    ADC16_EnableHardwareTrigger(FLOW_SENSOR_BASE, false); /* Make sure the software trigger is used. */
#if defined(FSL_FEATURE_ADC16_HAS_CALIBRATION) && FSL_FEATURE_ADC16_HAS_CALIBRATION
    if (kStatus_Success == ADC16_DoAutoCalibration(FLOW_SENSOR_BASE))
    {
        PRINTF("ADC16_DoAutoCalibration() Done.\r\n");
    }
    else
    {
        PRINTF("ADC16_DoAutoCalibration() Failed.\r\n");
    }
#endif /* FSL_FEATURE_ADC16_HAS_CALIBRATION */
    PRINTF("Press any key to get user channel's ADC value ...\r\n");

    adc16ChannelConfigStruct.channelNumber = FLOW_SENSOR_USER_CHANNEL;
    adc16ChannelConfigStruct.enableInterruptOnConversionCompleted = false;
#if defined(FSL_FEATURE_ADC16_HAS_DIFF_MODE) && FSL_FEATURE_ADC16_HAS_DIFF_MODE
    adc16ChannelConfigStruct.enableDifferentialConversion = false;
#endif /* FSL_FEATURE_ADC16_HAS_DIFF_MODE */



}

uint32_t readSensor() {
	ADC16_SetChannelConfig(FLOW_SENSOR_BASE, FLOW_SENSOR_CHANNEL_GROUP, &adc16ChannelConfigStruct);
	while (0U == (kADC16_ChannelConversionDoneFlag &
				  ADC16_GetChannelStatusFlags(FLOW_SENSOR_BASE, FLOW_SENSOR_CHANNEL_GROUP)))
	{
	}
	PRINTF("ADC Value: %d\r\n", ADC16_GetChannelConversionValue(FLOW_SENSOR_BASE, FLOW_SENSOR_CHANNEL_GROUP));
}


