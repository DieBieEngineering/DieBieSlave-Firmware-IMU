#include "driverSWMPU9250.h"

float driverSWMPU9250AccDivider;
float driverSWMPU9250GyroDivider;

bool driverSWMPU9250Init(void) {
	__HAL_RCC_GPIOA_CLK_ENABLE();
  GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
  GPIO_InitStruct.Pin = GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);	
	
	driverSWMPU9250DeviceSelect(IMU0,false);
	driverSWMPU9250DeviceSelect(IMU1,false);
	
	driverHWSPI3Init();
	
	return false;
}

bool driverSWMPU9250InitMPU(driverSWMPU9250IMUDeviceNumer devicePointer) {
  uint32_t driverSWMPU9250WriteRegisterDelayLastTick = HAL_GetTick();
  uint8_t registerPointer;
	
  uint8_t MPU_Init_Data[17][2] = {
        {BIT_H_RESET, MPUREG_PWR_MGMT_1},								// Reset Device
        {0x01, MPUREG_PWR_MGMT_1},											// Clock Source - Auto selects the best available clock source – PLL if ready, elseuse the Internal oscillator
        {0x00, MPUREG_PWR_MGMT_2},											// Enable all internal ADC's -> Acc & Gyro
        {BITS_DLPF_CFG_188HZ, MPUREG_CONFIG},						// Use DLPF set Gyroscope bandwidth 184Hz, temperature bandwidth 188Hz
        {BITS_FS_250DPS, MPUREG_GYRO_CONFIG},						// +-250dps set gyro sensitivity 
        {BITS_FS_2G, MPUREG_ACCEL_CONFIG},							// +-2G set accelero sensitivity
        {BITS_DLPF_CFG_188HZ, MPUREG_ACCEL_CONFIG_2},		// Set Acc Data Rates, Enable Acc LPF , Bandwidth 184Hz
        {0xD0, MPUREG_INT_PIN_CFG},											// Open drain, active low, max 50us, cleared when read,
        {0x30, MPUREG_USER_CTRL},												// I2C Master mode and set I2C_IF_DIS to disable slave mode I2C bus
        {0x0D, MPUREG_I2C_MST_CTRL},										// I2C configuration IIC 400KHz
				
        {AK8963_I2C_ADDR, MPUREG_I2C_SLV0_ADDR},				// Set the I2C slave addres of AK8963 and set for write.
				
        {AK8963_CNTL2, MPUREG_I2C_SLV0_REG},						// I2C slave 0 register address from where to begin data transfer
        {0x01, MPUREG_I2C_SLV0_DO},											// Reset AK8963
        {0x81, MPUREG_I2C_SLV0_CTRL},										// Enable I2C and set 1 byte
				
        {AK8963_CNTL1, MPUREG_I2C_SLV0_REG},						// I2C slave 0 register address from where to begin data transfer
        {0x16, MPUREG_I2C_SLV0_DO},											// Register value to 100Hz continuous measurement in 16bit
        {0x81, MPUREG_I2C_SLV0_CTRL}										// Enable I2C and set 1 byte
  };
	
	for(registerPointer = 0; registerPointer < 17; registerPointer++) {
		while(!modDelayTick1ms(&driverSWMPU9250WriteRegisterDelayLastTick,1)){};
    driverSWMPU9250WriteRegister(devicePointer,MPU_Init_Data[registerPointer][1], MPU_Init_Data[registerPointer][0]);		
	}

	return false;
}

uint8_t driverSWMPU9250GetID(driverSWMPU9250IMUDeviceNumer devicePointer){
	return driverSWMPU9250ReadSingleRegister(devicePointer, MPUREG_WHOAMI);
}

bool driverSWMPU9250CheckSensorPresent(driverSWMPU9250IMUDeviceNumer devicePointer) {
	uint8_t returnValue = driverSWMPU9250GetID(devicePointer);
	
	return (returnValue == 0x71);
}

uint8_t driverSWMPU9250SetAccRange(driverSWMPU9250IMUDeviceNumer devicePointer, uint8_t accRange){
	uint8_t returnScale;
	
	driverSWMPU9250WriteRegister(devicePointer, MPUREG_ACCEL_CONFIG, accRange);

	switch (accRange){
		case BITS_FS_2G:		driverSWMPU9250AccDivider=16384;		break;
		case BITS_FS_4G:		driverSWMPU9250AccDivider=8192;			break;
		case BITS_FS_8G:		driverSWMPU9250AccDivider=4096;			break;
		case BITS_FS_16G:		driverSWMPU9250AccDivider=2048;			break;   
	}

	returnScale = driverSWMPU9250ReadSingleRegister(devicePointer,MPUREG_ACCEL_CONFIG);

	switch (returnScale){
		case BITS_FS_2G:		returnScale=2;		break;
		case BITS_FS_4G:		returnScale=4;		break;
		case BITS_FS_8G:		returnScale=8;		break;
		case BITS_FS_16G:		returnScale=16;		break;   
	}
	
	return returnScale;
}

uint8_t driverSWMPU9250SetGyroRange(driverSWMPU9250IMUDeviceNumer devicePointer, uint8_t gyroRange){
    unsigned int returnScale;
	
    driverSWMPU9250WriteRegister(devicePointer, MPUREG_GYRO_CONFIG, gyroRange);

    switch (gyroRange){
        case BITS_FS_250DPS:   driverSWMPU9250GyroDivider = 131;  break;
        case BITS_FS_500DPS:   driverSWMPU9250GyroDivider = 65.5; break;
        case BITS_FS_1000DPS:  driverSWMPU9250GyroDivider = 32.8; break;
        case BITS_FS_2000DPS:  driverSWMPU9250GyroDivider = 16.4; break;   
    }

    returnScale = driverSWMPU9250ReadSingleRegister(devicePointer, MPUREG_GYRO_CONFIG);

    switch (returnScale){
        case BITS_FS_250DPS:   returnScale = 250;    break;
        case BITS_FS_500DPS:   returnScale = 500;    break;
        case BITS_FS_1000DPS:  returnScale = 1000;   break;
        case BITS_FS_2000DPS:  returnScale = 2000;   break;   
    }
		
    return returnScale;
}

driverSWMPU9250IMUAxis driverSWMPU9250ReadAcc(driverSWMPU9250IMUDeviceNumer devicePointer){
	driverSWMPU9250IMUAxis returnData;
	float driverSWMPU9250AccData[3];
	uint8_t responseArray[6];
	uint8_t responsePointer;
	int16_t bit_data;
	float data;
	
	driverSWMPU9250ReadRegisters(devicePointer,MPUREG_ACCEL_XOUT_H,responseArray,6);
	
	for(responsePointer = 0; responsePointer < 3; responsePointer++) {
			bit_data = ((int16_t)responseArray[responsePointer*2]<<8)|responseArray[responsePointer*2+1];
			data = (float)bit_data;
			driverSWMPU9250AccData[responsePointer] = data/driverSWMPU9250AccDivider;// - a_bias[i];
	}
	
	returnData.x = driverSWMPU9250AccData[0];
	returnData.y = driverSWMPU9250AccData[1];
	returnData.z = driverSWMPU9250AccData[2];
	
	return returnData;
}

driverSWMPU9250IMUAxis driverSWMPU9250ReadGyro(driverSWMPU9250IMUDeviceNumer devicePointer) {
	driverSWMPU9250IMUAxis returnData;
	float driverSWMPU9250GyroData[3];
	uint8_t responseArray[6];
	uint8_t responsePointer;
	int16_t bit_data;
	float data;
	
	driverSWMPU9250ReadRegisters(devicePointer,MPUREG_GYRO_XOUT_H,responseArray,6);
	
	for(responsePointer = 0; responsePointer < 3; responsePointer++) {
		bit_data = ((int16_t)responseArray[responsePointer*2]<<8) | responseArray[responsePointer*2+1];
		data = (float)bit_data;
		driverSWMPU9250GyroData[responsePointer] = data/driverSWMPU9250GyroDivider;// - g_bias[i];
	}
	
	returnData.x = driverSWMPU9250GyroData[0];
	returnData.y = driverSWMPU9250GyroData[1];
	returnData.z = driverSWMPU9250GyroData[2];
	
	return returnData;
}

float driverSWMPU9250ReadTemperature(driverSWMPU9250IMUDeviceNumer devicePointer) {
	uint8_t responseArray[2];
	int16_t bit_data;
	float data;

	driverSWMPU9250ReadRegisters(devicePointer, MPUREG_TEMP_OUT_H, responseArray, 2);

	bit_data = ((int16_t)responseArray[0]<<8) | responseArray[1];
	data = (float)bit_data;
	return (data/(333.87f))+21.0f;
}

void driverSWMPU9250ReadAllInternalSensors(driverSWMPU9250IMUDeviceNumer devicePointer, driverSWMPU9250IMUDataStructTypedef *dataStructPointer) {
	float driverSWMPU9250AccData[3];
	float driverSWMPU9250GyroData[3];
	uint8_t responseArray[14];
	uint8_t responsePointer;
	int16_t bit_data;
	float data;
	
	driverSWMPU9250ReadRegisters(devicePointer,MPUREG_ACCEL_XOUT_H,responseArray,14);
	
	// Extract accelerometer data.
	for(responsePointer = 0; responsePointer < 3; responsePointer++) {
			bit_data = ((int16_t)responseArray[responsePointer*2]<<8)|responseArray[responsePointer*2+1];
			data = (float)bit_data;
			driverSWMPU9250AccData[responsePointer] = data/driverSWMPU9250AccDivider;// - a_bias[i];
	}
	
	dataStructPointer->acceleroMeter.x = driverSWMPU9250AccData[0];
	dataStructPointer->acceleroMeter.y = driverSWMPU9250AccData[1];
	dataStructPointer->acceleroMeter.z = driverSWMPU9250AccData[2];
	
	// Extract temperature data
	bit_data = ((int16_t)responseArray[6]<<8) | responseArray[7];
	data = (float)bit_data;
	dataStructPointer->temperature = (data/(333.87f))+21.0f;
	
	// Extract gyroscope data
	for(responsePointer = 4; responsePointer < 7; responsePointer++) {
		bit_data = ((int16_t)responseArray[responsePointer*2]<<8) | responseArray[responsePointer*2+1];
		data = (float)bit_data;
		driverSWMPU9250GyroData[responsePointer - 4] = data/driverSWMPU9250GyroDivider;// - g_bias[i];
	}
	
	dataStructPointer->gyroscope.x = driverSWMPU9250GyroData[0];
	dataStructPointer->gyroscope.y = driverSWMPU9250GyroData[1];
	dataStructPointer->gyroscope.z = driverSWMPU9250GyroData[2];
	
}

void driverSWMPU9250SMagnetometerStartTranfer(driverSWMPU9250IMUDeviceNumer devicePointer) {
	driverSWMPU9250WriteRegister(devicePointer, MPUREG_I2C_SLV0_ADDR,AK8963_I2C_ADDR|READ_FLAG);  // Set the I2C slave addres of AK8963 and set for read.
	driverSWMPU9250WriteRegister(devicePointer, MPUREG_I2C_SLV0_REG, AK8963_HXL);                 // I2C slave 0 register address from where to begin data transfer
	driverSWMPU9250WriteRegister(devicePointer, MPUREG_I2C_SLV0_CTRL, 0x87);                      // Read 6 bytes from the magnetometer
}

void driverSWMPU9250ReadMagnetometer(driverSWMPU9250IMUDeviceNumer devicePointer, driverSWMPU9250IMUDataStructTypedef *dataStructPointer) {
  uint8_t responseArray[7];
	int16_t mag_data_raw[3];  
	float driverSWMPU9250CompassData[3];
	float data;
	uint8_t i;
	
	// must start your read from AK8963A register 0x03 and read seven bytes so that upon read of ST2 register 0x09 the AK8963A will unlatch the data registers for the next measurement.
	driverSWMPU9250ReadRegisters(devicePointer, MPUREG_EXT_SENS_DATA_00, responseArray, 7);	

	for(i = 0; i < 3; i++) {
		mag_data_raw[i] = ((int16_t)responseArray[i*2+1]<<8) | responseArray[i*2];
		data = (float)mag_data_raw[i];
		//mag_data[i] = data*Magnetometer_ASA[i];
		driverSWMPU9250CompassData[i] = data;
	}
	
	dataStructPointer->compass.x = driverSWMPU9250CompassData[0];
	dataStructPointer->compass.y = driverSWMPU9250CompassData[1];
	dataStructPointer->compass.z = driverSWMPU9250CompassData[2];	
}

bool driverSWMPU9250WriteRegister(driverSWMPU9250IMUDeviceNumer devicePointer, uint8_t address, uint8_t writeData) {
	uint8_t  writeBuffer[2] = {address,writeData};
	
	driverSWMPU9250DeviceSelect(devicePointer,true);
	driverHWSPI3Write(writeBuffer, 2);
	driverSWMPU9250DeviceSelect(devicePointer,false);
	
	return false;
}

uint8_t driverSWMPU9250ReadSingleRegister(driverSWMPU9250IMUDeviceNumer devicePointer, uint8_t address) {
	uint8_t writeBytes[] = { READ_FLAG | address};
	uint8_t readResult = 0;
	
	driverSWMPU9250DeviceSelect(devicePointer,true);
	driverHWSPI3WriteRead(writeBytes, 1, &readResult, 1);
	driverSWMPU9250DeviceSelect(devicePointer,false);

	return readResult;
}

bool driverSWMPU9250ReadRegisters(driverSWMPU9250IMUDeviceNumer devicePointer, uint8_t addressPointer, uint8_t *readBuffer, uint8_t amountOfRegisters) {
	uint8_t writeBytes[] = { READ_FLAG | addressPointer};
	
	driverSWMPU9250DeviceSelect(devicePointer,true);
	driverHWSPI3WriteRead(writeBytes, 1,readBuffer, amountOfRegisters);
	driverSWMPU9250DeviceSelect(devicePointer,false);
	
	return false;
}

void driverSWMPU9250DeviceSelect(driverSWMPU9250IMUDeviceNumer devicePointer, bool selectState) {
	switch(devicePointer) {
		case IMU0:
			driverSWMPU9250SetMUX(false);
		  driverSWMPU9250SelectChipOnCS0(selectState);
		
			if(selectState)
				driverSWMPU9250SelectChipOnCS1(false);
				
			break;
		case IMU1:
			driverSWMPU9250SetMUX(true);
			driverSWMPU9250SelectChipOnCS1(selectState);

			if(selectState)
				driverSWMPU9250SelectChipOnCS0(false);
			
			break;
		default:
			break;
	}
}

void driverSWMPU9250SelectChipOnCS0(bool selectState) {
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,(GPIO_PinState)!selectState);
}

void driverSWMPU9250SelectChipOnCS1(bool selectState) {
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,(GPIO_PinState)!selectState);
}

void driverSWMPU9250SetMUX(bool PinState) {
	// Low = IMU0, High = IMU1
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,(GPIO_PinState)PinState);
}

bool driverSWMPU9250GetINT(GPIO_PinState PinState) {
	return HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2);
}
