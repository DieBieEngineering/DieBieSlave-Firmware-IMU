#include "stm32f3xx_hal.h"
#include "stdbool.h"
#include "stdlib.h"
#include "string.h"

#define driverHWSPI3DefaultTimout										100

void driverHWSPI3Init(void);
bool driverHWSPI3Write(uint8_t *writeBuffer, uint8_t noOfBytesToWrite);
bool driverHWSPI3WriteSingleByte(uint8_t data);
bool driverHWSPI3WriteRead(uint8_t *writeBuffer, uint8_t noOfBytesToWrite, uint8_t *readBuffer, uint8_t noOfBytesToRead);
void driverHWSPI3SetCS(GPIO_PinState PinState);
