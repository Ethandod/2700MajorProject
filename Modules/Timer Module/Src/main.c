#include <stdint.h>
#include <stddef.h>
#include "stm32f303xc.h"
#include "timer.h"

void enableLEDs()
{
	RCC->AHBENR |= RCC_AHBENR_GPIOEEN;

	uint16_t *led_output_registers = ((uint16_t *)&(GPIOE->MODER)) + 1;
	*led_output_registers = 0x5555;
}

void toggleLEDs(uint8_t bitmap) {
	*(((uint8_t*)&(GPIOE->ODR)) + 1) = (*(((uint8_t*)&(GPIOE->ODR)) + 1)) ^ bitmap;
}

void timer_callback1(void){
	toggleLEDs(0b00000001);
}

void timer_callback2(void){
	toggleLEDs(0b00000010);
}

void timer_callback3(void){
	toggleLEDs(0b00000100);
}

int main(void)
{
	DelayTIM *timer1 = &DelayTIM2;
	DelayTIM *timer2 = &DelayTIM3;
	DelayTIM *timer3 = &DelayTIM4;

	timerInitialise(timer1);
	timerInitialise(timer2);
	timerInitialise(timer3);

	enableLEDs();
	toggleLEDs(0b11111111);
 
	setDelayLoop(timer1, 1000, &timer_callback1);
	setDelayLoop(timer2, 2000, &timer_callback2);
	setDelayLoop(timer3, 3000, &timer_callback3);
	while(1)
	{
	}
}
