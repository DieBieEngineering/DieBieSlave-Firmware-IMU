#include "objectlist.h"

static const char acName1000[] = "Device Type";
static const char acName1000_0[] = "Device Type";
static const char acName1008[] = "Device Name";
static const char acName1008_0[] = "Device Name";
static const char acName1009[] = "Hardware Version";
static const char acName1009_0[] = "Hardware Version";
static const char acName100A[] = "Software Version";
static const char acName100A_0[] = "Software Version";
static const char acName1018[] = "Identity Object";
static const char acName1018_00[] = "Number of Elements";
static const char acName1018_01[] = "Vendor ID";
static const char acName1018_02[] = "Product Code";
static const char acName1018_03[] = "Revision Number";
static const char acName1018_04[] = "Serial Number";
static const char acName1600[] = "Digital ouputs";
static const char acName1600_00[] = "Number of Elements";
static const char acName1600_01[] = "LED0";
static const char acName1600_02[] = "Padding";
static const char acName1A00[] = "IMU0";
static const char acName1A00_00[] = "Number of Elements";
static const char acName1A00_01[] = "AccelerometerX";
static const char acName1A00_02[] = "AccelerometerY";
static const char acName1A00_03[] = "AccelerometerZ";
static const char acName1A00_04[] = "GyroscopeX";
static const char acName1A00_05[] = "GyroscopeY";
static const char acName1A00_06[] = "GyroscopeZ";
static const char acName1A00_07[] = "SensorPresent";
static const char acName1A00_08[] = "Padding";
static const char acName1A01[] = "IMU1";
static const char acName1A01_00[] = "Number of Elements";
static const char acName1A01_01[] = "AccelerometerX";
static const char acName1A01_02[] = "AccelerometerY";
static const char acName1A01_03[] = "AccelerometerZ";
static const char acName1A01_04[] = "GyroscopeX";
static const char acName1A01_05[] = "GyroscopeY";
static const char acName1A01_06[] = "GyroscopeZ";
static const char acName1A01_07[] = "SensorPresent";
static const char acName1A01_08[] = "Padding";
static const char acName1C00[] = "Sync Manager Communication Type";
static const char acName1C00_00[] = "Number of Elements";
static const char acName1C00_01[] = "Communications Type SM0";
static const char acName1C00_02[] = "Communications Type SM1";
static const char acName1C00_03[] = "Communications Type SM2";
static const char acName1C00_04[] = "Communications Type SM3";
static const char acName1C12[] = "Sync Manager 2 PDO Assignment";
static const char acName1C12_00[] = "Number of Elements";
static const char acName1C12_01[] = "PDO Mapping";
static const char acName1C13[] = "Sync Manager 3 PDO Assignment";
static const char acName1C13_00[] = "Number of Elements";
static const char acName1C13_01[] = "PDO Mapping";
static const char acName1C13_02[] = "PDO Mapping";
static const char acName6000[] = "IMU0";
static const char acName6000_00[] = "Number of Elements";
static const char acName6000_01[] = "AccelerometerX";
static const char acName6000_02[] = "AccelerometerY";
static const char acName6000_03[] = "AccelerometerZ";
static const char acName6000_04[] = "GyroscopeX";
static const char acName6000_05[] = "GyroscopeY";
static const char acName6000_06[] = "GyroscopeZ";
static const char acName6000_07[] = "SensorPresent";
static const char acName6001[] = "IMU1";
static const char acName6001_00[] = "Number of Elements";
static const char acName6001_01[] = "AccelerometerX";
static const char acName6001_02[] = "AccelerometerY";
static const char acName6001_03[] = "AccelerometerZ";
static const char acName6001_04[] = "GyroscopeX";
static const char acName6001_05[] = "GyroscopeY";
static const char acName6001_06[] = "GyroscopeZ";
static const char acName6001_07[] = "SensorPresent";
static const char acName7000[] = "Digital ouputs";
static const char acName7000_00[] = "Number of Elements";
static const char acName7000_01[] = "LED0";
static const char acName8000[] = "Sensitivity";
static const char acName8000_00[] = "Number of Elements";
static const char acName8000_01[] = "Accelerometer";
static const char acName8000_02[] = "Gyroscope";

const _objd SDO1000[] =
{
  {0x0, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1000_0, 0x01901389, NULL},
};
const _objd SDO1008[] =
{
  {0x0, DTYPE_VISIBLE_STRING, 136, ATYPE_RO, acName1008_0, 0, "DieBieSlave - IMU"},
};
const _objd SDO1009[] =
{
  {0x0, DTYPE_VISIBLE_STRING, 24, ATYPE_RO, acName1009_0, 0, "0.1"},
};
const _objd SDO100A[] =
{
  {0x0, DTYPE_VISIBLE_STRING, 24, ATYPE_RO, acName100A_0, 0, "0.5"},
};
const _objd SDO1018[] =
{
  {0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, acName1018_00, 4, NULL},
  {0x01, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1018_01, 0x959, NULL},
  {0x02, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1018_02, 0x01001202, NULL},
  {0x03, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1018_03, 0, NULL},
  {0x04, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1018_04, 0x00000002, NULL},
};
const _objd SDO1600[] =
{
  {0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, acName1600_00, 2, NULL},
  {0x01, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1600_01, 0x70000101, NULL},
  {0x02, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1600_02, 0x00000007, NULL},
};
const _objd SDO1A00[] =
{
  {0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, acName1A00_00, 8, NULL},
  {0x01, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A00_01, 0x60000120, NULL},
  {0x02, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A00_02, 0x60000220, NULL},
  {0x03, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A00_03, 0x60000320, NULL},
  {0x04, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A00_04, 0x60000420, NULL},
  {0x05, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A00_05, 0x60000520, NULL},
  {0x06, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A00_06, 0x60000620, NULL},
  {0x07, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A00_07, 0x60000701, NULL},
  {0x08, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A00_08, 0x00000007, NULL},
};
const _objd SDO1A01[] =
{
  {0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, acName1A01_00, 8, NULL},
  {0x01, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A01_01, 0x60010120, NULL},
  {0x02, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A01_02, 0x60010220, NULL},
  {0x03, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A01_03, 0x60010320, NULL},
  {0x04, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A01_04, 0x60010420, NULL},
  {0x05, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A01_05, 0x60010520, NULL},
  {0x06, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A01_06, 0x60010620, NULL},
  {0x07, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A01_07, 0x60010701, NULL},
  {0x08, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A01_08, 0x00000007, NULL},
};
const _objd SDO1C00[] =
{
  {0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, acName1C00_00, 4, NULL},
  {0x01, DTYPE_UNSIGNED8, 8, ATYPE_RO, acName1C00_01, 1, NULL},
  {0x02, DTYPE_UNSIGNED8, 8, ATYPE_RO, acName1C00_02, 2, NULL},
  {0x03, DTYPE_UNSIGNED8, 8, ATYPE_RO, acName1C00_03, 3, NULL},
  {0x04, DTYPE_UNSIGNED8, 8, ATYPE_RO, acName1C00_04, 4, NULL},
};
const _objd SDO1C12[] =
{
  {0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, acName1C12_00, 1, NULL},
  {0x01, DTYPE_UNSIGNED16, 16, ATYPE_RO, acName1C12_01, 0x1600, NULL},
};
const _objd SDO1C13[] =
{
  {0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, acName1C13_00, 2, NULL},
  {0x01, DTYPE_UNSIGNED16, 16, ATYPE_RO, acName1C13_01, 0x1A00, NULL},
  {0x02, DTYPE_UNSIGNED16, 16, ATYPE_RO, acName1C13_02, 0x1A01, NULL},
};
const _objd SDO6000[] =
{
  {0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, acName6000_00, 7, NULL},
  {0x01, DTYPE_REAL32, 32, ATYPE_RO, acName6000_01, 0, (void*)&middleSOESReadBuffer.IMU0.AccelerometerX},
  {0x02, DTYPE_REAL32, 32, ATYPE_RO, acName6000_02, 0, (void*)&middleSOESReadBuffer.IMU0.AccelerometerY},
  {0x03, DTYPE_REAL32, 32, ATYPE_RO, acName6000_03, 0, (void*)&middleSOESReadBuffer.IMU0.AccelerometerZ},
  {0x04, DTYPE_REAL32, 32, ATYPE_RO, acName6000_04, 0, (void*)&middleSOESReadBuffer.IMU0.GyroscopeX},
  {0x05, DTYPE_REAL32, 32, ATYPE_RO, acName6000_05, 0, (void*)&middleSOESReadBuffer.IMU0.GyroscopeY},
  {0x06, DTYPE_REAL32, 32, ATYPE_RO, acName6000_06, 0, (void*)&middleSOESReadBuffer.IMU0.GyroscopeZ},
  {0x07, DTYPE_BOOLEAN, 1, ATYPE_RO, acName6000_07, 0, &middleSOESReadBufferBooleansBuffer.IMU0SensorPresent},
};
const _objd SDO6001[] =
{
  {0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, acName6001_00, 7, NULL},
  {0x01, DTYPE_REAL32, 32, ATYPE_RO, acName6001_01, 0, (void*)&middleSOESReadBuffer.IMU1.AccelerometerX},
  {0x02, DTYPE_REAL32, 32, ATYPE_RO, acName6001_02, 0, (void*)&middleSOESReadBuffer.IMU1.AccelerometerY},
  {0x03, DTYPE_REAL32, 32, ATYPE_RO, acName6001_03, 0, (void*)&middleSOESReadBuffer.IMU1.AccelerometerZ},
  {0x04, DTYPE_REAL32, 32, ATYPE_RO, acName6001_04, 0, (void*)&middleSOESReadBuffer.IMU1.GyroscopeX},
  {0x05, DTYPE_REAL32, 32, ATYPE_RO, acName6001_05, 0, (void*)&middleSOESReadBuffer.IMU1.GyroscopeY},
  {0x06, DTYPE_REAL32, 32, ATYPE_RO, acName6001_06, 0, (void*)&middleSOESReadBuffer.IMU1.GyroscopeZ},
  {0x07, DTYPE_BOOLEAN, 1, ATYPE_RO, acName6001_07, 0, &middleSOESReadBufferBooleansBuffer.IMU1SensorPresent},
};
const _objd SDO7000[] =
{
  {0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, acName7000_00, 1, NULL},
  {0x01, DTYPE_BOOLEAN, 1, ATYPE_RO, acName7000_01, 0, &middleSOESReadBufferBooleansBuffer.LED0},
};
const _objd SDO8000[] =
{
  {0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, acName8000_00, 2, NULL},
  {0x01, DTYPE_INTEGER8, 8, ATYPE_RW, acName8000_01, 0, &middleSOESConfigBuffer.Sensitivity.Accelerometer},
  {0x02, DTYPE_INTEGER8, 8, ATYPE_RW, acName8000_02, 0, &middleSOESConfigBuffer.Sensitivity.Gyroscope},
};

const _objectlist SDOobjects[] =
{
  {0x1000, OTYPE_VAR, 0, 0, acName1000, SDO1000},
  {0x1008, OTYPE_VAR, 0, 0, acName1008, SDO1008},
  {0x1009, OTYPE_VAR, 0, 0, acName1009, SDO1009},
  {0x100A, OTYPE_VAR, 0, 0, acName100A, SDO100A},
  {0x1018, OTYPE_RECORD, 4, 0, acName1018, SDO1018},
  {0x1600, OTYPE_RECORD, 2, 0, acName1600, SDO1600},
  {0x1A00, OTYPE_RECORD, 8, 0, acName1A00, SDO1A00},
  {0x1A01, OTYPE_RECORD, 8, 0, acName1A01, SDO1A01},
  {0x1C00, OTYPE_ARRAY, 4, 0, acName1C00, SDO1C00},
  {0x1C12, OTYPE_ARRAY, 1, 0, acName1C12, SDO1C12},
  {0x1C13, OTYPE_ARRAY, 2, 0, acName1C13, SDO1C13},
  {0x6000, OTYPE_RECORD, 7, 0, acName6000, SDO6000},
  {0x6001, OTYPE_RECORD, 7, 0, acName6001, SDO6001},
  {0x7000, OTYPE_RECORD, 1, 0, acName7000, SDO7000},
  {0x8000, OTYPE_RECORD, 2, 0, acName8000, SDO8000},
  {0xffff, 0xff, 0xff, 0xff, NULL, NULL}
};
