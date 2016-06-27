/*
 * Copyright (c) 2013 - 2016, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * This is template for main module created by New Kinetis SDK 2.x Project Wizard. Enjoy!
 **/

#include "board.h"
#include "pin_mux.h"
#include "fsl_debug_console.h"
#include "fsl_gpio.h"

#include "fsl_lptmr.h"

#include "watervalve.h"
#include "flowsensor.h"
#include "rtc.h"

#include "clock_config.h"

void Setup_Pins();


// vars for the flow sensor pulse code

// The hall-effect flow sensor outputs approximately 4.5 pulses per second per
// litre/minute of flow.
float calibrationFactor = 4.5;

//volatile byte pulseCount;

float flowRate = 0;
int flowMilliLitres = 0U;
long totalMilliLitres = 0U;
long oldTime = 0U;


/* Whether the SW button is pressed */
volatile bool sw2_ButtonPress = false;
volatile bool sw1_ButtonPress = false;
volatile bool mode_automatic = true;

int sw2_counter = 0;
int readingCount = 0;
int lastReading = 0;
int pulseCount = 0U;

void BOARD_SW2_IRQ_HANDLER(void)
{
    /* Clear external interrupt flag. */
    GPIO_ClearPinsInterruptFlags(BOARD_SW2_GPIO, 1U << BOARD_SW2_GPIO_PIN);
    /* Change state of button. */
    sw2_ButtonPress = true;
    mode_automatic = false;
    sw2_counter++;
    /* Toggle LED. */
    openValve();
}

void BOARD_SW3_IRQ_HANDLER(void)
{

	uint32_t number = GPIO_GetPinsInterruptFlags(FLOW_SENSOR_INPUT_GPIO);
	PRINTF("Pin number: %d\r\n", number);

	if(number == 8U) {
		GPIO_ClearPinsInterruptFlags(FLOW_SENSOR_INPUT_GPIO, 1U << FLOW_SENSOR_INPUT_PIN);
		uint32_t reading = GPIO_ReadPinInput(FLOW_SENSOR_INPUT_GPIO, FLOW_SENSOR_INPUT_PIN);
		PRINTF("sensor reading: %d\r\n", reading);
		if (lastReading != reading) {
			pulseCount++;
			lastReading = reading;
		}
		PRINTF("Pulses %d \r\n", pulseCount);
	}

    /* Toggle LED. */
	if(number == 64U) {
	 /* Clear external interrupt flag. */
		GPIO_ClearPinsInterruptFlags(BOARD_SW3_GPIO, 1U << BOARD_SW3_GPIO_PIN);
		/* Change state of button. */
		sw1_ButtonPress = true;
		mode_automatic = false;
		sw2_counter = 0;
		closeValve();
	}
}






/*!
 * @brief Application entry point.
 */
int main(void) {
  /* Init board hardware. */
  BOARD_InitPins();
  BOARD_BootClockRUN();
  BOARD_InitDebugConsole();

  init_clock();
  Setup_Pins();


  resetLow();
  while(1) { /* Infinite loop to avoid leaving the main function */
	  waterFlow flow = litresPerMinute(&pulseCount);

	  if (sw2_ButtonPress)
		  {
			  PRINTF(" %s is pressed \r\n", BOARD_SW2_NAME);
			  /* Reset state of button. */
			  if(sw2_counter == 2) {
				  //reset to automatic
				  mode_automatic = true;
				  sw2_counter = 0;
			  }
			  sw2_ButtonPress = false;
		  }

	  if (sw1_ButtonPress)
	  		  {
	  			  PRINTF(" %s is pressed \r\n", BOARD_SW3_NAME);
	  			  /* Reset state of button. */
	  			  sw1_ButtonPress = false;
	  		  }

	  if(mode_automatic) {
//		  control the valve based on the flow
		  if(flow.litresPerMinute > 1U) {
			  openValve();
		  } else {
			  closeValve();
		  }
	  }


  }
}





void Setup_Pins() {
	initState();
	initSensor();
}


//#define BOARD_LED_GPIO BOARD_LED_RED_GPIO
//#define BOARD_LED_GPIO_PIN BOARD_LED_RED_GPIO_PIN
//
///*******************************************************************************
// * Prototypes
// ******************************************************************************/
///*!
// * @brief delay a while.
// */
//void delay(void);
//
///*******************************************************************************
// * Variables
// ******************************************************************************/
//
///*******************************************************************************
// * Code
// ******************************************************************************/
void delay(void)
{
    volatile uint32_t i = 0;
    for (i = 0; i < 800000; ++i)
    {
        __asm("NOP"); /* delay */
    }
}

