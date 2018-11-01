#include "stm32f3xx_hal.h"
#include "usb_device.h"
#include "modDelay.h"
#include "modEffect.h"
#include "middleSOES.h"
#include "middleNunChuck.h"
#include "middleMPU.h"
#include "driverSWStorageManager.h"
#include "modConfig.h"

void SystemClock_Config(void);
void Error_Handler(void);

middleMPUDataStructTypedef mainMPUSensorDataStruct[2];
middleMPUConfigStructTypedef mainMPUConfig;
modConfigGeneralConfigStructTypedef *generalSensorConfig;

void newIMUDataEventHandler(driverSWMPU9250IMUDataStructTypedef *newData);
void mainSOESReadBufferUpdateHandler(void);
void mainSOESConfigBufferUpdateHandler(void);


int main(void) {
  HAL_Init();
  SystemClock_Config();
	
	modDelayInit();
	modEffectInit();
	middleSOESInit();
	middleSOESReadBufferUpdateEvent(&mainSOESReadBufferUpdateHandler);
	middleSOESConfigBufferUpdateEvent(&mainSOESConfigBufferUpdateHandler);
	
	// All following functions should be called in exactly this order
	generalSensorConfig = modConfigInit();																		// Tell EEPROM the needed size for ConfigStruct
	driverSWStorageManagerInit();																							// Initializes EEPROM Memory
	modConfigStoreAndLoadDefaultConfig();																	    // Store default config if needed -> load config from EEPROM
	// Until here
	
	middleSOESConfigBuffer.Sensitivity.Accelerometer  = generalSensorConfig->sensitivityAccelerometer;
	middleSOESConfigBuffer.Sensitivity.Gyroscope			= generalSensorConfig->sensitivityGyroscope;
	
	mainMPUConfig.accelerometerSensitivity 						= generalSensorConfig->sensitivityAccelerometer;
	mainMPUConfig.gyroSensitivity          						= generalSensorConfig->sensitivityGyroscope;
	
	middleMPUInit(mainMPUConfig);
	middleMPUNewDataEvent(&newIMUDataEventHandler);

  while(true) {
		modEffectTask();
		
		if(middleMPUTask())
			middleSOESTask();
  }
}

void newIMUDataEventHandler(driverSWMPU9250IMUDataStructTypedef *newData) {
	memcpy(&mainMPUSensorDataStruct,newData,sizeof(middleMPUDataStructTypedef)*2);
}

void mainSOESReadBufferUpdateHandler(void) {
	// Update the SOES readbuffer
	middleSOESReadBuffer.IMU0.AccelerometerX = mainMPUSensorDataStruct[0].acceleroMeter.x;
	middleSOESReadBuffer.IMU0.AccelerometerY = mainMPUSensorDataStruct[0].acceleroMeter.y;
	middleSOESReadBuffer.IMU0.AccelerometerZ = mainMPUSensorDataStruct[0].acceleroMeter.z;
	middleSOESReadBuffer.IMU0.GyroscopeX     = mainMPUSensorDataStruct[0].gyroscope.x;
	middleSOESReadBuffer.IMU0.GyroscopeY     = mainMPUSensorDataStruct[0].gyroscope.y;
	middleSOESReadBuffer.IMU0.GyroscopeZ     = mainMPUSensorDataStruct[0].gyroscope.z;
	middleSOESReadBuffer.IMU0.SensorPresent  = mainMPUSensorDataStruct[0].sensorPresent;

	middleSOESReadBuffer.IMU1.AccelerometerX = mainMPUSensorDataStruct[1].acceleroMeter.x;
	middleSOESReadBuffer.IMU1.AccelerometerY = mainMPUSensorDataStruct[1].acceleroMeter.y;
	middleSOESReadBuffer.IMU1.AccelerometerZ = mainMPUSensorDataStruct[1].acceleroMeter.z;
	middleSOESReadBuffer.IMU1.GyroscopeX     = mainMPUSensorDataStruct[1].gyroscope.x;
	middleSOESReadBuffer.IMU1.GyroscopeY     = mainMPUSensorDataStruct[1].gyroscope.y;
	middleSOESReadBuffer.IMU1.GyroscopeZ     = mainMPUSensorDataStruct[1].gyroscope.z;
	middleSOESReadBuffer.IMU1.SensorPresent  = mainMPUSensorDataStruct[1].sensorPresent;
}

void mainSOESConfigBufferUpdateHandler(void) {
	mainMPUConfig.accelerometerSensitivity 				= middleSOESConfigBuffer.Sensitivity.Accelerometer;
	mainMPUConfig.gyroSensitivity 								= middleSOESConfigBuffer.Sensitivity.Gyroscope;
	middleMPUUpdateConfig(mainMPUConfig);
	
	generalSensorConfig->sensitivityAccelerometer = middleSOESConfigBuffer.Sensitivity.Accelerometer;
	generalSensorConfig->sensitivityGyroscope     = middleSOESConfigBuffer.Sensitivity.Gyroscope;
	modConfigStoreConfig();
}

void SystemClock_Config(void) {
  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
	
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
    Error_Handler();
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB|RCC_PERIPHCLK_USART1
                              |RCC_PERIPHCLK_USART2|RCC_PERIPHCLK_I2C1
                              |RCC_PERIPHCLK_I2C3|RCC_PERIPHCLK_TIM2;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_SYSCLK;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_SYSCLK;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_SYSCLK;
  PeriphClkInit.I2c3ClockSelection = RCC_I2C3CLKSOURCE_SYSCLK;
  PeriphClkInit.USBClockSelection = RCC_USBCLKSOURCE_PLL_DIV1_5;
  PeriphClkInit.Tim2ClockSelection = RCC_TIM2CLK_PLLCLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
    Error_Handler();
  }

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

void Error_Handler(void) {
  while(1);
}
