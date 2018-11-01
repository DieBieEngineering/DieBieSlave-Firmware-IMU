#include "driverSWMPU9250.h"
#include <stdint.h>

typedef driverSWMPU9250IMUDataStructTypedef middleMPUDataStructTypedef;

typedef struct {
	uint8_t accelerometerSensitivity;
	uint8_t gyroSensitivity;	
} middleMPUConfigStructTypedef;

void middleMPUInit(middleMPUConfigStructTypedef initConfig);
middleMPUConfigStructTypedef middleMPUGetConfig(void);
void middleMPUUpdateConfig(middleMPUConfigStructTypedef newConfig);
void middleMPUNewDataEvent(void (*eventFunctionPointer)(middleMPUDataStructTypedef *newData));
bool middleMPUTask(void);
