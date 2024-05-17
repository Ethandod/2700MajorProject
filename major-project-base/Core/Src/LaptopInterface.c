#include <stdint.h>
#include <stdlib.h>
#include "serial.h"
#include <string.h>


void (*stopGame)();

char green[] = "green";
char red[] = "red";

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
	 volatile uint8_t* ptr = (volatile uint8_t*) green;
	 serialTransmitString(ptr, &USART1_PORT);
}

void setLaptopRed() {
	 volatile uint8_t* ptr = (volatile uint8_t*) red;
	 serialTransmitString(ptr, &USART1_PORT);
}
