#include "modEffect.h"

STATStatusStruct STATStatuses[NoOfSTATs] = 								// Hold all STAT StateIndicator data
{
	{STAT_OFF,0}																						// STAT_LED_DEBUG
};

void modEffectInit(void) {
	driverHWStatusInit();																		// Init GPIO direction and state
	modDelayInit();																					// Init delay mechanism
}

void modEffectChangeState(STATIDTypedef id, STATStateTypedef NewState) {
	if(STATStatuses[id].State != NewState) {
		STATStatuses[id].State = NewState;
		STATStatuses[id].Count = 1;
	}else{
		STATStatuses[id].Count++;
	}
}

void modEffectTask(void) {
	uint32_t LEDPointer;
	
	for(LEDPointer = 0; LEDPointer < NoOfSTATs; LEDPointer++) {
		switch(STATStatuses[LEDPointer].State) {
			case STAT_RESET:
			case STAT_OFF:
				driverHWSetOutput((STATIDTypedef)LEDPointer,STAT_RESET);
				break;
			case STAT_SET:
			case STAT_ON:
				driverHWSetOutput((STATIDTypedef)LEDPointer,STAT_SET);
				break;
			case STAT_FLASH:
				driverHWSetOutput((STATIDTypedef)LEDPointer,modEffectTaskFlash());
				break;
			case STAT_FLASH_FAST:
				driverHWSetOutput((STATIDTypedef)LEDPointer,modEffectTaskFlashFast());
				break;
			case STAT_BLINKSHORT:
				driverHWSetOutput((STATIDTypedef)LEDPointer,modEffectTaskBlinkShort(LEDPointer,50));
				break;
			case STAT_BLINKLONG:
				driverHWSetOutput((STATIDTypedef)LEDPointer,modEffectTaskBlinkLong(LEDPointer,500));
				break;
			default:
				break;
		}
	}
}

STATStateTypedef modEffectTaskFlash(void) {
	static uint32_t lastTick;
	static STATStateTypedef LEDOnState = STAT_RESET;
	
	if(modDelayTick100ms(&lastTick,5)) {
		if(LEDOnState){
			LEDOnState = STAT_RESET;
		}else{
			LEDOnState = STAT_SET;
		}
	}
	
	return LEDOnState;
}

STATStateTypedef modEffectTaskFlashFast(void) {
	static uint32_t lastTick;
	static STATStateTypedef LEDOnState = STAT_RESET;
	
	if(modDelayTick1ms(&lastTick,100)) {
		if(LEDOnState){
			LEDOnState = STAT_RESET;
		}else{
			LEDOnState = STAT_SET;
		}
	}
	
	return LEDOnState;
}

STATStateTypedef modEffectTaskBlinkShort(uint32_t LEDPointer, uint32_t blinkTime) {
	static uint32_t lastTick;
	static STATStateTypedef LEDOnState = STAT_RESET;
	
	if(LEDOnState) {
		if(modDelayTick1ms(&lastTick,blinkTime)) {
			LEDOnState = STAT_RESET;
			lastTick = HAL_GetTick();
		}
	}else{
		if(modDelayTick1ms(&lastTick,blinkTime)) {
			if(STATStatuses[LEDPointer].Count > MAX_BLINKSHORT_CYCLES) {
				STATStatuses[LEDPointer].Count = MAX_BLINKSHORT_CYCLES;
			}
			if(STATStatuses[LEDPointer].Count > 0) {
				STATStatuses[LEDPointer].Count--;
				LEDOnState = STAT_SET;
			}
			lastTick = HAL_GetTick();
		}
	}
	
	return LEDOnState;
}

STATStateTypedef modEffectTaskBlinkLong(uint32_t LEDPointer, uint32_t blinkTime) {
	static uint32_t lastTick;
	static STATStateTypedef LEDOnState = STAT_RESET;
	
	if(LEDOnState) {
		if(modDelayTick1ms(&lastTick,blinkTime)) {
			LEDOnState = STAT_RESET;
			lastTick = HAL_GetTick();
		}
	}else{
		if(modDelayTick1ms(&lastTick,blinkTime)) {
			if(STATStatuses[LEDPointer].Count > MAX_BLINKLONG_CYCLES) {
				STATStatuses[LEDPointer].Count = MAX_BLINKLONG_CYCLES;
			}
			if(STATStatuses[LEDPointer].Count > 0) {
				STATStatuses[LEDPointer].Count--;
				LEDOnState = STAT_SET; 
			}
			lastTick = HAL_GetTick();
		}
	}
	
	return LEDOnState;
}
