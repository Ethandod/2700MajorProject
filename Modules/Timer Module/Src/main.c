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

void toggleLEDs() {
	*(((uint8_t*)&(GPIOE->ODR)) + 1) = ~(*(((uint8_t*)&(GPIOE->ODR)) + 1));
}

void timer_callback(void){
	toggleLEDs();
}


int main(void)
{
	timerInitialise();
	enableLEDs();
	toggleLEDs();
 
	//setDelayLoop(2000, &timer_callback);
	setDelay(2000, &timer_callback);
	while(1)
	{
	}
}
