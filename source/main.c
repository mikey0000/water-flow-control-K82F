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

#include "clock_config.h"

void Setup_Pins();



/* Whether the SW button is pressed */
volatile bool sw2_ButtonPress = false;
volatile bool sw1_ButtonPress = false;

void BOARD_SW2_IRQ_HANDLER(void)
{
    /* Clear external interrupt flag. */
    GPIO_ClearPinsInterruptFlags(BOARD_SW2_GPIO, 1U << BOARD_SW2_GPIO_PIN);
    /* Change state of button. */
    sw2_ButtonPress = true;
    /* Toggle LED. */
    openValve();
}

void BOARD_SW3_IRQ_HANDLER(void)
{
    /* Clear external interrupt flag. */
    GPIO_ClearPinsInterruptFlags(BOARD_SW3_GPIO, 1U << BOARD_SW3_GPIO_PIN);
    /* Change state of button. */
    sw1_ButtonPress = true;
    /* Toggle LED. */
    closeValve();
}






/*!
 * @brief Application entry point.
 */
int main(void) {
  /* Init board hardware. */
  BOARD_InitPins();
  BOARD_BootClockRUN();
  BOARD_InitDebugConsole();


  Setup_Pins();
//  openValve();
//  closeValve();
  /* Add your code here */

  while(1) { /* Infinite loop to avoid leaving the main function */
	  if (sw2_ButtonPress)
		  {
			  PRINTF(" %s is pressed \r\n", BOARD_SW2_NAME);
			  /* Reset state of button. */
			  sw2_ButtonPress = false;
		  }

	  if (sw1_ButtonPress)
	  		  {
	  			  PRINTF(" %s is pressed \r\n", BOARD_SW3_NAME);
	  			  /* Reset state of button. */
	  			  sw1_ButtonPress = false;
	  		  }

//    __asm("NOP"); /* something to use as a breakpoint stop while looping */

	  readSensor();
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

