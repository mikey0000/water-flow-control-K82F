/*
 * flowsensor.cpp
 *
 *  Created on: 8/06/2016
 *      Author: michaelarthur
 */

#include "flowsensor.h"
#include "fsl_debug_console.h"

//    adc16_config_t adc16ConfigStruct;
//    adc16_channel_config_t adc16ChannelConfigStruct;


// The hall-effect flow sensor outputs approximately 4.5 pulses per second per
// litre/minute of flow.
float calibrationFactor = 4.5;

float flowRate;
uint8_t flowMilliLitres;
long totalMilliLitres;
uint32_t oldTime;


    gpio_pin_config_t power_config =
	{
		kGPIO_DigitalOutput, 1,
	};

    gpio_pin_config_t sensor_config =
	{
		kGPIO_DigitalInput, 0,
	};


void initSensor() {
	GPIO_PinInit(FLOW_SENSOR_VCC_GPIO, FLOW_SENSOR_VCC_PIN, &power_config);
	GPIO_WritePinOutput(FLOW_SENSOR_VCC_GPIO, FLOW_SENSOR_VCC_PIN, 1U);

	PORT_SetPinInterruptConfig(FLOW_SENSOR_INPUT_PORT, FLOW_SENSOR_INPUT_PIN, kPORT_InterruptEitherEdge);
//	EnableIRQ(BOARD_PORTC_IRQ);

	GPIO_PinInit(FLOW_SENSOR_INPUT_GPIO, FLOW_SENSOR_INPUT_PIN, &sensor_config);

	flowRate          = 0.0;
	flowMilliLitres   = 0U;
	totalMilliLitres  = 0U;
	oldTime           = 0U;
}


waterFlow litresPerMinute(int *pulseCount) {
	waterFlow flow;

	if((RTC->TSR - oldTime) > 1)    // Only process counters once per second
	  {
	    // Because this loop may not complete in exactly 1 second intervals we calculate
	    // the number of seconds that have passed since the last execution and use
	    // that to scale the output. We also apply the calibrationFactor to scale the output
	    // based on the number of pulses per second per units of measure (litres/minute in
	    // this case) coming from the sensor.
	    flowRate = ((RTC->TSR - oldTime) * *pulseCount) / calibrationFactor;

	    oldTime = RTC->TSR;

	    // Divide the flow rate in litres/minute by 60 to determine how many litres have
	    // passed through the sensor in this 1 second interval, then multiply by 1000 to
	    // convert to millilitres.
	    flowMilliLitres = (flowRate / 60) * 1000;

	    // Add the millilitres passed in this second to the cumulative total
	    totalMilliLitres += flowMilliLitres;

	    PRINTF("Flow rate: %2.2f L/min \r\n", flowRate);
	    // Print the number of litres flowed in this second
	    PRINTF("Current Liquid Flowing: %d mL/Sec \r\n", flowMilliLitres);             // Output separator
	    // Print the cumulative total of litres flowed since starting
	    PRINTF("Output Liquid Quantity: %d ml \r\n", totalMilliLitres);             // Output separator
	    // Reset the pulse counter so we can start incrementing again
	    *pulseCount = 0U;

	    flow.litresPerMinute = flowRate;
	    flow.millilitresPerSec = flowMilliLitres;
	  }


	//return
	return flow;
}

