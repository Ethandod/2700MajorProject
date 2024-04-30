#include <stdbool.h>
#include "stm32f303xc.h"
#include "timer.h"

// "Private" function declarations
void enableTimer();
void triggerPrescaler();
void enableInterrupts();
void timerHandler();
void resetTimer(uint32_t delay_ms);

//  Variable definitions
void (*callback_ptr)(void) = NULL;
bool is_loop = NULL;

void timerInitialise()
{
	// Enable appropriate functions
	enableTimer();
	enableInterrupts();
}

void enableTimer()
{
	// Enable the clock for Timer 2
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOCEN | RCC_AHBENR_GPIOEEN;
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	TIM2->PSC = 0x1F3F; // 7999
	TIM2->CR1 |= TIM_CR1_CEN;
	triggerPrescaler();
}

// Pre-scaler updates only upon "events" so this triggers an overflow
void triggerPrescaler()
{
	TIM2->ARR = 0x01;
	TIM2->CNT = 0x00;
	TIM2->ARR = 0xFFFFFFFF;
}

void enableInterrupts()
{
	__disable_irq();

    // Enable the update interrupt
	TIM2->CR1 |=
    TIM2->DIER |= TIM_DIER_UIE;

	// Set priority and enable interrupts
	NVIC_SetPriority(TIM2_IRQn, 1);
	NVIC_EnableIRQ(TIM2_IRQn);

	__enable_irq();
}

void TIM2_IRQHandler()
{
	if ((TIM2->SR & TIM_SR_UIF) != 0) {
		timerHandler();
	}
}

void timerHandler() {
    TIM2->SR &= ~TIM_SR_UIF;
	if (callback_ptr == NULL) {
		stopTimer();
		return;
	}
	if (is_loop) {
		callback_ptr();
		return;
	}
	if (!is_loop){
		stopTimer();
		callback_ptr();
		return;
	}
}

uint32_t get_delay()
{
    return TIM2->ARR;
}

void resetTimer(uint32_t delay_ms) {
	stopTimer();
    TIM2->ARR = delay_ms;
	TIM2->CR1 |= TIM_CR1_CEN;
	TIM2->SR &= ~TIM_SR_UIF;
}

void stopTimer() {
	TIM2->CR1 &= ~TIM_CR1_CEN;
	TIM2->CNT = 0x00;
}

void setDelayLoop(uint32_t delay_ms, void (*callback)(void)) {
	callback_ptr = callback;
	is_loop = true;
	resetTimer(delay_ms);
}

void setDelay(uint32_t delay_ms, void (*callback)(void)) {
	callback_ptr = callback;
	is_loop = false;
	resetTimer(delay_ms);
}
