#ifndef _SOES_H_
#define _SOES_H_

#include <stdbool.h>
#include <stdint.h>
#include "esc.h"
#include "esc_coe.h"
#include "objectlist.h"
#include "driverSWNunChuck.h"

#include "modEffect.h"

void middleSOESInit(void);
void middleSOESTask(void);
void middleSOESReadBufferUpdateEvent(void (*eventFunctionPointer)(void));
void middleSOESConfigBufferUpdateEvent(void (*eventFunctionPointer)(void));

#endif
