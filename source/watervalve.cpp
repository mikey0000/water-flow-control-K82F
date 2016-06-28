/*
 * watervalve.cpp
 *
 *  Created on: 25/05/2016
 *      Author: michael arthur
 */

#include "../board/board.h"
#include "watervalve.h"

bool openValveState = false;

/**
 * Switch pins around and wait x seconds until valve has fully opened
 *
 */

/* Output pin configuration */
	gpio_pin_config_t valve_config =
	{
		kGPIO_DigitalOutput, 0,
	};

	gpio_pin_config_t power_config =
		{
			kGPIO_DigitalOutput, 0,
		};


	gpio_pin_config_t sw2_config =
		{
				kGPIO_DigitalInput,
		0, };




	/*  Sets the configuration */

void initState() {
	GPIO_PinInit(VALVE_VCC1_GPIO, VALVE_VCC1_PIN, &valve_config);
	GPIO_PinInit(VALVE_VCC2_GPIO, VALVE_VCC2_PIN, &valve_config);

//	this lets us get an interrupt when we press the buttons
	PORT_SetPinInterruptConfig(BOARD_SW2_PORT, BOARD_SW2_GPIO_PIN, kPORT_InterruptFallingEdge);
	EnableIRQ(BOARD_SW2_IRQ);

	PORT_SetPinInterruptConfig(BOARD_SW3_PORT, BOARD_SW3_GPIO_PIN, kPORT_InterruptFallingEdge);
	EnableIRQ(BOARD_SW3_IRQ);



	GPIO_PinInit(BOARD_SW2_GPIO, BOARD_SW2_GPIO_PIN, &sw2_config);
	GPIO_PinInit(BOARD_SW3_GPIO, BOARD_SW3_GPIO_PIN, &sw2_config);

//PTB17
//	PORTB_PCR17[MUX] = 001; //GPIO function
//	PORTB_PCR17[PE] = 1; //internal pullup or pulldown resistor enable
//	PORTB_PCR17[PS] = 1; //internal pullup resistor is enabled
	GPIO_PinInit(HBRIDGE_POWER_GPIO, HBRIDGE_POWER_PIN ,&power_config);
//	GPIO_TogglePinsOutput(HBRIDGE_POWER_GPIO, 1U << HBRIDGE_POWER_PIN);
//
	GPIO_PinInit(HBRIDGE_MOTOR_ENABLE_GPIO, HBRIDGE_MOTOR_ENABLE_PIN ,&power_config);
//	GPIO_TogglePinsOutput(HBRIDGE_MOTOR_ENABLE_GPIO, 1U << HBRIDGE_MOTOR_ENABLE_PIN);

}


//stop when flow is going.
void openValve() {
	if(!openValveState) {
		GPIO_WritePinOutput(VALVE_VCC2_GPIO, VALVE_VCC2_PIN, 1U);
		GPIO_WritePinOutput(VALVE_VCC1_GPIO, VALVE_VCC1_PIN, 0U);
		openValveState = !openValveState;
	}
	//extra could work out how many seconds it takes for the valve to open then resetLow again.
}


//stop when flow stops
void closeValve() {
	if(openValveState) {
		GPIO_WritePinOutput(VALVE_VCC1_GPIO, VALVE_VCC1_PIN, 1U);
		GPIO_WritePinOutput(VALVE_VCC2_GPIO, VALVE_VCC2_PIN, 0U);
		openValveState = !openValveState;
	}
	//extra could work out how many seconds it takes for the valve to open then resetLow again.
}

// drop power to ball valve
void resetLow() {
	GPIO_WritePinOutput(VALVE_VCC1_GPIO, VALVE_VCC1_PIN, 0U);
	GPIO_WritePinOutput(VALVE_VCC2_GPIO, VALVE_VCC2_PIN, 0U);
}




