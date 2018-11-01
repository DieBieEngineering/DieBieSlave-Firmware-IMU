#include "driverHWSPI1.h"

SPI_HandleTypeDef driverHWSPI3Handle;

void driverHWSPI3Init(void) {
	__HAL_RCC_GPIOC_CLK_ENABLE();
	
  driverHWSPI3Handle.Instance = SPI3;
  driverHWSPI3Handle.Init.Mode = SPI_MODE_MASTER;
  driverHWSPI3Handle.Init.Direction = SPI_DIRECTION_2LINES;
  driverHWSPI3Handle.Init.DataSize = SPI_DATASIZE_8BIT;
  driverHWSPI3Handle.Init.CLKPolarity = SPI_POLARITY_HIGH;
  driverHWSPI3Handle.Init.CLKPhase = SPI_PHASE_2EDGE;
  driverHWSPI3Handle.Init.NSS = SPI_NSS_SOFT;
  driverHWSPI3Handle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
  driverHWSPI3Handle.Init.FirstBit = SPI_FIRSTBIT_MSB;
  driverHWSPI3Handle.Init.TIMode = SPI_TIMODE_DISABLE;
  driverHWSPI3Handle.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  driverHWSPI3Handle.Init.CRCPolynomial = 7;
  driverHWSPI3Handle.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  driverHWSPI3Handle.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
  if (HAL_SPI_Init(&driverHWSPI3Handle) != HAL_OK)
    while(true);
};

bool driverHWSPI3Write(uint8_t *writeBuffer, uint8_t noOfBytesToWrite) {
	uint8_t *readBuffer;																																					// Make fake buffer holder
	HAL_StatusTypeDef halReturnStatus;																														// Make holder for HAL state
	readBuffer = malloc(noOfBytesToWrite);																												// Make fake buffer for
	
	halReturnStatus = HAL_SPI_TransmitReceive(&driverHWSPI3Handle,writeBuffer,readBuffer,noOfBytesToWrite,driverHWSPI1DefaultTimout);	// Write desired data to slave and store the received data in readBuffer
	while( driverHWSPI3Handle.State == HAL_SPI_STATE_BUSY );  																		// Wait until transmission is complete
	
	free(readBuffer);																																							// Dump de fake buffer
	
	return (halReturnStatus == HAL_OK);																														// Return true if all went OK
};

bool driverHWSPI3WriteSingleByte(uint8_t data) {
	uint8_t  writeByte[1] = {data};
	return driverHWSPI1Write(writeByte,1);
}


bool driverHWSPI3WriteRead(uint8_t *writeBuffer, uint8_t noOfBytesToWrite, uint8_t *readBuffer, uint8_t noOfBytesToRead) {
	uint8_t *writeArray, *readArray;
	HAL_StatusTypeDef halReturnStatus;																														// Make holder for HAL state
	
	writeArray = malloc(sizeof(uint8_t)*(noOfBytesToWrite+noOfBytesToRead));
	readArray = malloc(sizeof(uint8_t)*(noOfBytesToWrite+noOfBytesToRead));	
	memset(writeArray,0xFF,noOfBytesToWrite+noOfBytesToRead);
	memcpy(writeArray,writeBuffer,noOfBytesToWrite);
	
	halReturnStatus = HAL_SPI_TransmitReceive(&driverHWSPI3Handle,writeArray,(uint8_t*)readArray,noOfBytesToWrite+noOfBytesToRead,driverHWSPI1DefaultTimout);
	while( driverHWSPI3Handle.State == HAL_SPI_STATE_BUSY );  																		// wait xmission complete

	memcpy(readBuffer,(uint8_t*)readArray+noOfBytesToWrite,noOfBytesToRead);
	
	free(writeArray);
	free(readArray);
	
	return (halReturnStatus == HAL_OK);																														// Return true if all went OK
};
