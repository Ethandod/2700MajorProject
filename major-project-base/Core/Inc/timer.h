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

// Initialise function for the timer use &DelayTIMx depending on which timer you want to initialise
void timerInitialise(DelayTIM *delay_timer);
// Create a recurring timer (calls the callback every delay_ms milliseconds)
void setDelayLoop(DelayTIM *delay_timer, uint32_t delay_ms, void (*callback)(void));
// Create a one-shot timer (calls the callback once and then stops the timer)
void setDelay(DelayTIM *delay_timer, uint32_t delay_ms, void (*callback)(void));
// Stop the timer
void stopTimer(DelayTIM *delay_timer);

#endif
