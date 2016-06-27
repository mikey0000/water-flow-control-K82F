#include "fsl_flexio.h"


void run() {
	flexio_shifter_config_t shifterConfig;
	flexio_timer_config_t timerConfig;

	memset(&shifterConfig, 0, sizeof(shifterConfig));
	memset(&timerConfig, 0, sizeof(timerConfig));

//	after board pin init and clockstuff

	CLOCK_SetFlexio0Clock(2U);


	/* Configure the shifter 7 for rx. */
	shifterConfig.timerSelect = 2;
	shifterConfig.timerPolarity = kFLEXIO_ShifterTimerPolarityOnNegitive;
	shifterConfig.pinConfig = kFLEXIO_PinConfigOutputDisabled;
//	shifterConfig.pinSelect = FLEXIO_I2C_SDA_PIN;
	shifterConfig.pinPolarity = kFLEXIO_PinActiveHigh;
	shifterConfig.shifterMode = kFLEXIO_ShifterModeMatchStore;
	shifterConfig.inputSource = kFLEXIO_ShifterInputFromPin;
	shifterConfig.shifterStop = kFLEXIO_ShifterStopBitLow;
	shifterConfig.shifterStart = kFLEXIO_ShifterStartBitDisabledLoadDataOnEnable;

	FLEXIO0->SHIFTBUFBIS[7] =0xFF3F00C0;

	FLEXIO_SetShifterConfig(FLEXIO0, 7, &shifterConfig);

	/* Configure the shifter 6-2 for rx. */
	shifterConfig.timerSelect = 2;
	shifterConfig.timerPolarity = kFLEXIO_ShifterTimerPolarityOnNegitive;
	shifterConfig.pinConfig = kFLEXIO_PinConfigOutputDisabled;
//	shifterConfig.pinSelect = FLEXIO_I2C_SDA_PIN;
	shifterConfig.pinPolarity = kFLEXIO_PinActiveHigh;
	shifterConfig.shifterMode = kFLEXIO_ShifterModeReceive;
	shifterConfig.inputSource = kFLEXIO_ShifterInputFromNextShifterOutput;
	shifterConfig.shifterStop = kFLEXIO_ShifterStopBitLow;
	shifterConfig.shifterStart = kFLEXIO_ShifterStartBitDisabledLoadDataOnEnable;

	FLEXIO_SetShifterConfig(FLEXIO0, 6, &shifterConfig);
	FLEXIO_SetShifterConfig(FLEXIO0, 5, &shifterConfig);
	FLEXIO_SetShifterConfig(FLEXIO0, 4, &shifterConfig);
	FLEXIO_SetShifterConfig(FLEXIO0, 3, &shifterConfig);
	FLEXIO_SetShifterConfig(FLEXIO0, 2, &shifterConfig);


	timerConfig.triggerSelect = FLEXIO_TIMER_TRIGGER_SEL_SHIFTnSTAT(7);
	timerConfig.triggerPolarity = kFLEXIO_TimerTriggerPolarityActiveHigh;
	timerConfig.triggerSource = kFLEXIO_TimerTriggerSourceInternal;
	timerConfig.pinConfig = kFLEXIO_PinConfigOutput;
	timerConfig.pinSelect = 17;
	timerConfig.pinPolarity = kFLEXIO_PinActiveLow;
	timerConfig.timerMode = kFLEXIO_TimerModeDual8BitPWM;
	timerConfig.timerOutput = kFLEXIO_TimerOutputOneNotAffectedByReset;
	timerConfig.timerDecrement = kFLEXIO_TimerDecSrcOnFlexIOClockShiftTimerOutput;
	timerConfig.timerReset = kFLEXIO_TimerResetNever;
	timerConfig.timerDisable = kFLEXIO_TimerDisableOnTimerCompare;
	timerConfig.timerEnable = kFLEXIO_TimerEnableOnTriggerHigh;
	timerConfig.timerStop = kFLEXIO_TimerStopBitDisabled;
	timerConfig.timerStart = kFLEXIO_TimerStartBitDisabled;


	timerConfig.timerCompare = 0x000ff01;

	FLEXIO_SetTimerConfig(FLEXIO0, 3 , &timerConfig);



	timerConfig.triggerSelect = FLEXIO_TIMER_TRIGGER_SEL_SHIFTnSTAT(0);
	timerConfig.triggerPolarity = kFLEXIO_TimerTriggerPolarityActiveLow;
	timerConfig.triggerSource = kFLEXIO_TimerTriggerSourceInternal;
	timerConfig.pinConfig = kFLEXIO_PinConfigOutputDisabled;
//	timerConfig.pinSelect = FLEXIO_I2C_SCL_PIN;
	timerConfig.pinPolarity = kFLEXIO_PinActiveLow;
	timerConfig.timerMode = kFLEXIO_TimerModeSingle16Bit;
	timerConfig.timerOutput = kFLEXIO_TimerOutputOneNotAffectedByReset;
	timerConfig.timerDecrement = kFLEXIO_TimerDecSrcOnPinInputShiftPinInput;
	timerConfig.timerReset = kFLEXIO_TimerResetNever;
	timerConfig.timerDisable = kFLEXIO_TimerDisableNever;
	timerConfig.timerEnable = kFLEXIO_TimerEnabledAlways;
	timerConfig.timerStop = kFLEXIO_TimerStopBitEnableOnTimerDisable;
	timerConfig.timerStart = kFLEXIO_TimerStartBitEnabled;


	timerConfig.timerCompare = 161;

	FLEXIO_SetTimerConfig(FLEXIO0, 2 , &timerConfig);






}
