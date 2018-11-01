#ifndef __OBJECTLIST_H
#define __OBJECTLIST_H

#include "esc_coe.h"
#include <stddef.h>

typedef struct CC_PACKED {
   struct CC_PACKED {
      float AccelerometerX;
      float AccelerometerY;
      float AccelerometerZ;
      float GyroscopeX;
      float GyroscopeY;
      float GyroscopeZ;
      uint8_t SensorPresent:1;
      uint8_t pad0:7;
   } IMU0;
   struct CC_PACKED {
      float AccelerometerX;
      float AccelerometerY;
      float AccelerometerZ;
      float GyroscopeX;
      float GyroscopeY;
      float GyroscopeZ;
      uint8_t SensorPresent:1;
      uint8_t pad0:7;
   } IMU1;
} middleSOESReadbufferTypedef;

typedef struct {
		int8_t IMU0SensorPresent;
		int8_t IMU1SensorPresent;
		int8_t LED0;
} middleSOESReadBufferBooleansTypedef;

typedef struct CC_PACKED {
   struct CC_PACKED {
      uint8_t LED0:1;
      uint8_t pad0:7;
   } Digital_ouputs;
} middleSOESWritebufferTypedef;

typedef struct CC_PACKED {
	struct CC_PACKED {
		int8_t Accelerometer;
		int8_t Gyroscope;
	} Sensitivity;
} middleSOESConfigBufferTypedef;

extern middleSOESReadbufferTypedef 					middleSOESReadBuffer;
extern middleSOESReadBufferBooleansTypedef	middleSOESReadBufferBooleansBuffer;
extern middleSOESWritebufferTypedef 				middleSOESWriteBuffer;
extern middleSOESConfigBufferTypedef 				middleSOESConfigBuffer;

#endif //__OBJECTLIST_H
