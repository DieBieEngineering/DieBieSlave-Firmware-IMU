#include "middleMPU.h"

uint32_t middleMPUGetSamplesLastTick;
uint32_t middleMPUGetMagnetoLastTick;
uint32_t middleMPUGetPresentLastTick;
uint32_t middleMPUInitDelayLastTick;

middleMPUDataStructTypedef middleMPUData[2];
middleMPUConfigStructTypedef middleMPUSensorConfig;

void (*middleMPUEventFunctionPointer)(middleMPUDataStructTypedef *newData);

void middleMPUInit(middleMPUConfigStructTypedef initConfig){
	driverSWMPU9250Init();
	driverSWMPU9250InitMPU(IMU0);
	driverSWMPU9250InitMPU(IMU1);
	
	middleMPUUpdateConfig(initConfig);
	
	driverSWMPU9250SMagnetometerStartTranfer(IMU0);
	driverSWMPU9250SMagnetometerStartTranfer(IMU1);	
	
	middleMPUData[IMU0].sensorPresent = driverSWMPU9250CheckSensorPresent(IMU0);
	middleMPUData[IMU1].sensorPresent = driverSWMPU9250CheckSensorPresent(IMU1);
}

middleMPUConfigStructTypedef middleMPUGetConfig(void){
	middleMPUConfigStructTypedef temp;
	return temp;
}

void middleMPUUpdateConfig(middleMPUConfigStructTypedef newConfig){
	middleMPUSensorConfig = newConfig;
	
	driverSWMPU9250SetAccRange(IMU0,middleMPUSensorConfig.accelerometerSensitivity);
	driverSWMPU9250SetGyroRange(IMU0,middleMPUSensorConfig.gyroSensitivity);
	driverSWMPU9250SetAccRange(IMU1,middleMPUSensorConfig.accelerometerSensitivity);
	driverSWMPU9250SetGyroRange(IMU1,middleMPUSensorConfig.gyroSensitivity);
}

void middleMPUNewDataEvent(void (*eventFunctionPointer)(middleMPUDataStructTypedef *newData)){
  if(eventFunctionPointer)
		middleMPUEventFunctionPointer = eventFunctionPointer;
}

void middleMPUTaskManagePresence(void) {
	static bool IMUPresentLastState[2] = {true, true};
	
	middleMPUData[IMU0].sensorPresent = driverSWMPU9250CheckSensorPresent(IMU0);
	middleMPUData[IMU1].sensorPresent = driverSWMPU9250CheckSensorPresent(IMU1);
	
	if(IMUPresentLastState[IMU0] != middleMPUData[IMU0].sensorPresent) {
		if(middleMPUData[IMU0].sensorPresent) {
			middleMPUInitDelayLastTick = HAL_GetTick();

			while(!modDelayTick1ms(&middleMPUInitDelayLastTick,100)){};

			driverSWMPU9250InitMPU(IMU0);
			middleMPUUpdateConfig(middleMPUSensorConfig);
		}
		IMUPresentLastState[IMU0] = middleMPUData[IMU0].sensorPresent;
	}
	
	if(IMUPresentLastState[IMU1] != middleMPUData[IMU1].sensorPresent) {
		if(middleMPUData[IMU1].sensorPresent) {
			middleMPUInitDelayLastTick = HAL_GetTick();

			while(!modDelayTick1ms(&middleMPUInitDelayLastTick,100)){};

			driverSWMPU9250InitMPU(IMU1);
			middleMPUUpdateConfig(middleMPUSensorConfig);
		}
		IMUPresentLastState[IMU1] = middleMPUData[IMU1].sensorPresent;
	}	
	
	//detect re-appearance and do a re-init
}

bool middleMPUTask(void){
	if(modDelayTick1ms(&middleMPUGetPresentLastTick,1000)) {
		middleMPUTaskManagePresence();
	}
	
	if(modDelayTick1ms(&middleMPUGetSamplesLastTick,1)) {				
		driverSWMPU9250ReadAllInternalSensors(IMU0,&middleMPUData[IMU0]);
		driverSWMPU9250ReadAllInternalSensors(IMU1,&middleMPUData[IMU1]);

		if(middleMPUEventFunctionPointer)
			middleMPUEventFunctionPointer(middleMPUData);
		
		return true;
	}else{
		return false;
	}
}
