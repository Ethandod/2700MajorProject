#include <stdint.h>
#include <stdlib.h>
#include "serial.h"
#include <string.h>


void (*stopGame)();

void checkStop(volatile uint8_t* string_buffer, uint32_t size) {
	if (strncmp("stop", (char*)string_buffer, 4) == 0) {
		stopGame();
	}
}

void laptopInterfaceInitialise(void (*stopGameFunction)()) {
	stopGame = stopGameFunction;
	serialInitialise(10, BAUD_115200, &USART1_PORT, &checkStop);
}

void setLaptopGreen() {
	 char str[] = "green";
	 volatile uint8_t* ptr = (volatile uint8_t*) str;
	 serialTransmitString(ptr, &USART1_PORT);
}

void setLaptopRed() {
	 char str[] = "red";
	 volatile uint8_t* ptr = (volatile uint8_t*) str;
	 serialTransmitString(ptr, &USART1_PORT);
}
