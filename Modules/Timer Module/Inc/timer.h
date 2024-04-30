#ifndef TIMER_H_
#define TIMER_H_

#include <stdint.h>
#include <stddef.h>
#include "stm32f303xc.h"

// Initialise functions
void timerInitialise();
void setDelayLoop(uint32_t delay_ms, void (*callback)(void));
void setDelay(uint32_t delay_ms, void (*callback)(void));
void stopTimer();

#endif
