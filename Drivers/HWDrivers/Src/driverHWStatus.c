#include "driverHWStatus.h"

const STATPortStruct STATPorts[NoOfSTATs] = 							// Hold all status configuration data
{
	{GPIOB,RCC_AHBENR_GPIOBEN,GPIO_PIN_15}									// STAT_LED_DEBUG
};

void driverHWStatusInit(void) {
	GPIO_InitTypeDef STATPortHolder;
	uint8_t STATPointer;
	
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	
	for(STATPointer = 0; STATPointer < NoOfSTATs; STATPointer++) {
		RCC->AHBENR |= STATPorts[STATPointer].ClkRegister;						// Enable clock de desired port
		STATPortHolder.Mode = GPIO_MODE_OUTPUT_PP;										// Push pull output
		STATPortHolder.Pin = STATPorts[STATPointer].Pin;							// Points to status pin
		STATPortHolder.Pull = GPIO_NOPULL;														// No pullup
		STATPortHolder.Speed = GPIO_SPEED_HIGH;												// GPIO clock speed
		HAL_GPIO_Init(STATPorts[STATPointer].Port,&STATPortHolder);		// Perform the IO init 
	};
}

void driverHWSetOutput(STATIDTypedef LEDType,STATStateTypedef State) {
	HAL_GPIO_WritePin(STATPorts[LEDType].Port,STATPorts[LEDType].Pin,(GPIO_PinState)State); // Set desired pin to desired state
}
