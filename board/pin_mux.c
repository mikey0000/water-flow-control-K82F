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

/* This is a template file for pins configuration created by New Kinetis SDK 2.x Project Wizard. Enjoy! */

#include "fsl_port.h"
#include "fsl_gpio.h"
#include "pin_mux.h"
#include "fsl_common.h"
#include "board.h"

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Initialize all pins used in this example
 */
void BOARD_InitPins(void)
{
  /* This is a template function for pins configuration. Intentionally empty */
	CLOCK_EnableClock(kCLOCK_PortA);

/* sw2 button so we can use the two buttons */
	/* Affects PORTA_PCR4 register aka sw2 */
	port_pin_config_t config = {0};
	config.pullSelect = kPORT_PullUp;
	config.mux = kPORT_MuxAsGpio;
	PORT_SetPinConfig(PORTA, BOARD_SW2_GPIO_PIN, &config);




	CLOCK_EnableClock(kCLOCK_PortB);
//	port_pin_config_t config = {
//	    kPORT_PullUp,
//	    kPORT_FastSlewRate,
//	    kPORT_PassiveFilterDisable,
//	    kPORT_OpenDrainDisable,
//	    kPORT_LowDriveStrength,
//		kPORT_MuxAsGpio,
//		kPORT_UnlockRegister,
//	};

	/* Affects PORTB_PCR18 register */
	PORT_SetPinMux(PORTB, 18U, kPORT_PinDisabledOrAnalog); //why have I done this?
	/* Affects PORTB_PCR19 register */
	PORT_SetPinMux(PORTB, 19U, kPORT_PinDisabledOrAnalog); //why have I done this?

//	PORT_SetPinConfig(VALVE_VCC2_PORT, VALVE_VCC2_PIN, &config);

	PORT_SetPinMux(VALVE_VCC1_PORT, VALVE_VCC1_PIN, kPORT_MuxAsGpio);
	PORT_SetPinMux(VALVE_VCC2_PORT, VALVE_VCC2_PIN, kPORT_MuxAsGpio);



	CLOCK_EnableClock(kCLOCK_PortC);
	/* Debug uart port mux config */
	/* Enable uart port clock */
	/* Affects PORTC_PCR14 register */
	PORT_SetPinMux(PORTC, 14U, kPORT_MuxAlt3);
	/* Affects PORTC_PCR15 register */
	PORT_SetPinMux(PORTC, 15U, kPORT_MuxAlt3);
//	PORT_SetPinMux(HBRIDGE_MOTOR_ENABLE_PORT, HBRIDGE_MOTOR_ENABLE_PIN, kPORT_MuxAsGpio);

	//voltage for the flow sensor
	PORT_SetPinMux(FLOW_SENSOR_VCC_PORT, FLOW_SENSOR_VCC_PIN, kPORT_MuxAsGpio);

	// sw3 button
	PORT_SetPinConfig(PORTC, BOARD_SW3_GPIO_PIN, &config);

	CLOCK_EnableClock(kCLOCK_PortD);
//	PORT_SetPinMux(HBRIDGE_POWER_PORT, HBRIDGE_POWER_PIN, kPORT_MuxAsGpio);

//
//	    /* Led pin mux Configuration */
//	    PORT_SetPinMux(PORTC, 8U, kPORT_MuxAsGpio);

}
