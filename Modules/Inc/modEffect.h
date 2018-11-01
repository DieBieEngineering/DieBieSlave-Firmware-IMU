#include "modDelay.h"
#include "driverHWStatus.h"

// Public functions:
void modEffectInit(void);
void modEffectTask(void);
void modEffectChangeState(STATIDTypedef id, STATStateTypedef status);

// Private functions:
STATStateTypedef modEffectTaskFlash(void);
STATStateTypedef modEffectTaskFlashFast(void);
STATStateTypedef modEffectTaskBlinkShort(uint32_t LEDPointer, uint32_t blinkTime);
STATStateTypedef modEffectTaskBlinkLong(uint32_t LEDPointer, uint32_t blinkTime);
