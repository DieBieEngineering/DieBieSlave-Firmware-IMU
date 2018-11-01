#include "driverSWStorageManager.h"

uint16_t *driverHWEEPROMVirtAddVarTab;

bool driverSWStorageManagerConfigEmpty = false;
bool driverSWStorageManagerStateOfChargeEmpty = false;
uint16_t driverSWStorageManagerDataSize = 0;
uint16_t driverSWStorageManagerConfigStructSize = 0;

void driverSWStorageManagerInit(void) {
	driverSWStorageManagerDataSize = driverSWStorageManagerConfigStructSize;																			// Calculate the total desired space
	
	// Generate EEPROM enviroment
	driverHWEEPROMVirtAddVarTab = malloc(driverSWStorageManagerDataSize*sizeof(uint16_t));												// Make room for the addres array
	HAL_FLASH_Unlock();																																														// Unlock FLASH to allow EEPROM lib to write
	
	if(driverHWEEPROMInit(driverSWStorageManagerDataSize) != HAL_OK)																							// Init EEPROM and tell EEPROM manager the disered size
		while(true);																																																// Something went wrong in the init
	
	for(uint16_t addresPointer=0 ; addresPointer < driverSWStorageManagerDataSize ; addresPointer++)
		driverHWEEPROMVirtAddVarTab[addresPointer] = addresPointer;																									// Generate addres array
	
	// Check EEPROM Contents
	uint16_t readVariable;																																												// Define variable to write EEPROM contents to if any
	if(driverHWEEPROMReadVariable(driverHWEEPROMVirtAddVarTab[0], &readVariable) == 1) {													// Try to read from first memory location, 1 == variable does not exist
		driverSWStorageManagerConfigEmpty = true;
	}
};

bool driverSWStorageManagerEraseData(void) {
	return (driverHWEEPROMEraseFlash() == HAL_OK);
}

bool driverSWStorageManagerStoreStruct(void *configStruct, StorageLocationTypedef storageLocation) {
	uint16_t *dataPointer = (uint16_t*)configStruct;																																// Trick to convert struct to a 16 bit pointer.
	uint16_t dataOffset = driverSWStorageManagerGetOffsetFromLocation(storageLocation);															// Get addres offset
	uint16_t dataSize = driverSWStorageManagerGetStructSize(storageLocation);																				// Get data size
	
	for(uint16_t addresPointer=0 ; addresPointer<dataSize ; addresPointer++) {																			// Scan trough all adresses
		driverHWEEPROMWriteVariable(driverHWEEPROMVirtAddVarTab[addresPointer+dataOffset],dataPointer[addresPointer]);// Store data in EEPROM
	}
	
	return false;
};

bool driverSWStorageManagerGetStruct(void *configStruct, StorageLocationTypedef storageLocation) {
	uint16_t *dataPointer = (uint16_t*)configStruct;																																// Trick to convert struct to a 16 bit pointer.
	uint16_t dataOffset = driverSWStorageManagerGetOffsetFromLocation(storageLocation);															// Get addres offset
	uint16_t dataSize = driverSWStorageManagerGetStructSize(storageLocation);																				// Get data size
	
	for(uint16_t addresPointer=0 ; addresPointer<dataSize ; addresPointer++)																				// Scan trough all adresses
		driverHWEEPROMReadVariable(driverHWEEPROMVirtAddVarTab[addresPointer+dataOffset],&dataPointer[addresPointer]);// Get data from EEPROM
	
	return false;
};

uint16_t driverSWStorageManagerGetOffsetFromLocation(StorageLocationTypedef storageLocation) {
	int16_t locationPointer = -1;
	switch(storageLocation) {
		case STORAGE_CONFIG:
		  locationPointer = 0;																																												// StorageStruct starts at addres 0
			break;
		default:
			break;
	};
	
	return locationPointer;
};

uint16_t driverSWStorageManagerGetStructSize(StorageLocationTypedef storageLocation) {
	int16_t sizeIndicator = -1;
	switch(storageLocation) {
		case STORAGE_CONFIG:
		  sizeIndicator = driverSWStorageManagerConfigStructSize;																											// Config struct size
			break;
		default:
			break;
	};
	
	return sizeIndicator;
};


