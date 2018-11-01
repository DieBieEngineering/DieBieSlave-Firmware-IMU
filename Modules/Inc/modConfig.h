#ifndef __MODCONFIG_H
#define __MODCONFIG_H

#include "stdint.h"
#include "stdbool.h"
#include "driverSWStorageManager.h"

typedef struct {
	uint8_t sensitivityAccelerometer;																				// Accelerometer sensitivity
	uint8_t sensitivityGyroscope;																						// Gyroscope sensitivity
} modConfigGeneralConfigStructTypedef;

modConfigGeneralConfigStructTypedef* modConfigInit(void);
bool modConfigStoreAndLoadDefaultConfig(void);
bool modConfigStoreConfig(void);
bool modConfigLoadConfig(void);
bool modConfigStoreDefaultConfig(void);

#endif
