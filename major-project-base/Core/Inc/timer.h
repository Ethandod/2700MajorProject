#ifndef TIMER_H_
#define TIMER_H_

#include <stdint.h>
#include <stddef.h>
#include "stm32f303xc.h"

struct _DelayTIM;
typedef struct _DelayTIM DelayTIM;

extern DelayTIM DelayTIM2;
extern DelayTIM DelayTIM3;
extern DelayTIM DelayTIM4;

// Initialise functions
void timerInitialise(DelayTIM *delay_timer);
void setDelayLoop(DelayTIM *delay_timer, uint32_t delay_ms, void (*callback)(void));
void setDelay(DelayTIM *delay_timer, uint32_t delay_ms, void (*callback)(void));
void stopTimer(DelayTIM *delay_timer);

#endif
