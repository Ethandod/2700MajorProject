#include <stdbool.h>
#include "stm32f303xc.h"
#include "timer.h"

// "Private" function declarations
void enableTimer(DelayTIM *delay_timer);
void triggerPrescaler(DelayTIM *delay_timer);
void enableInterrupts(DelayTIM *delay_timer);
void timerHandler(DelayTIM *delay_timer);
void resetTimer(DelayTIM *delay_timer, uint32_t delay_ms);

struct _DelayTIM {
	TIM_TypeDef *TIM;
	volatile uint32_t MaskAPB2ENR;	// mask to enable RCC APB2 bus registers
	volatile uint32_t MaskAPB1ENR;	// mask to enable RCC APB1 bus registers
	volatile uint32_t TIM_IRQn;		// IRQN for the specific timer
	void (*callback_ptr)(void);     // Function pointer for callback
	bool is_loop;                   // Flag indicating if the current timer should loop
	bool enabled;					// Flag indicating if TIM is used in this code section
};

//void TIM2_IRQHandler() {if (DelayTIM2.enabled) {timerHandler(&DelayTIM2);}}
DelayTIM DelayTIM2 = {
		.TIM = TIM2,
		.MaskAPB2ENR = 0x00,
		.MaskAPB1ENR = RCC_APB1ENR_TIM2EN,
		.TIM_IRQn = TIM2_IRQn,
		.callback_ptr = NULL,
		.is_loop = NULL,
		.enabled = false
	};


void TIM3_IRQHandler() {if (DelayTIM3.enabled) {timerHandler(&DelayTIM3);}}
DelayTIM DelayTIM3 = {
		.TIM = TIM3,
		.MaskAPB2ENR = 0x00,
		.MaskAPB1ENR = RCC_APB1ENR_TIM3EN,
		.TIM_IRQn = TIM3_IRQn,
		.callback_ptr = NULL,
		.is_loop = NULL,
		.enabled = false
	};


void TIM4_IRQHandler() {if (DelayTIM4.enabled) {timerHandler(&DelayTIM4);}}
DelayTIM DelayTIM4 = {
		.TIM = TIM4,
		.MaskAPB2ENR = 0x00,
		.MaskAPB1ENR = RCC_APB1ENR_TIM4EN,
		.TIM_IRQn = TIM4_IRQn,
		.callback_ptr = NULL,
		.is_loop = NULL,
		.enabled = false
	};

void timerHandler(DelayTIM *delay_timer) {
    delay_timer->TIM->SR &= ~TIM_SR_UIF;
	if (delay_timer->callback_ptr == NULL) {
		stopTimer(delay_timer);
		return;
	}
	if (delay_timer->is_loop) {
		delay_timer->callback_ptr();
		return;
	}
	if (!delay_timer->is_loop){
		stopTimer(delay_timer);
		delay_timer->callback_ptr();
		return;
	}
}

void timerInitialise(DelayTIM *delay_timer)
{
	// Enable appropriate functions
	enableTimer(delay_timer);
	enableInterrupts(delay_timer);
}

void enableTimer(DelayTIM *delay_timer)
{
	// Enable the clock for timer
	RCC->APB1ENR |= delay_timer->MaskAPB1ENR;
	delay_timer->TIM->PSC = 0x1F3F; // 7999
	delay_timer->TIM->CR1 |= TIM_CR1_CEN;
	triggerPrescaler(delay_timer);
	delay_timer->enabled = true;
}

// Pre-scaler updates only upon "events" so this triggers an overflow
void triggerPrescaler(DelayTIM *delay_timer)
{
	delay_timer->TIM->ARR = 0x01;
	delay_timer->TIM->CNT = 0x00;
	delay_timer->TIM->ARR = 0xFFFFFFFF;
}

void enableInterrupts(DelayTIM *delay_timer)
{
	__disable_irq();

    // Enable the update interrupt
    delay_timer->TIM->DIER |= TIM_DIER_UIE;

	// Set priority and enable interrupts
	NVIC_SetPriority(delay_timer->TIM_IRQn, 1);
	NVIC_EnableIRQ(delay_timer->TIM_IRQn);

	__enable_irq();
}

uint32_t get_delay(DelayTIM *delay_timer)
{
    return delay_timer->TIM->ARR;
}

void resetTimer(DelayTIM *delay_timer, uint32_t delay_ms) {
	stopTimer(delay_timer);
    delay_timer->TIM->ARR = delay_ms;
	delay_timer->TIM->CR1 |= TIM_CR1_CEN;
	delay_timer->TIM->SR &= ~TIM_SR_UIF;
}

void stopTimer(DelayTIM *delay_timer) {
	delay_timer->TIM->CR1 &= ~TIM_CR1_CEN;
	delay_timer->TIM->CNT = 0x00;
}

void setDelayLoop(DelayTIM *delay_timer, uint32_t delay_ms, void (*callback)(void)) {
	delay_timer->callback_ptr = callback;
	delay_timer->is_loop = true;
	resetTimer(delay_timer, delay_ms);
}

void setDelay(DelayTIM *delay_timer, uint32_t delay_ms, void (*callback)(void)) {
	delay_timer->callback_ptr = callback;
	delay_timer->is_loop = false;
	resetTimer(delay_timer, delay_ms);
}
