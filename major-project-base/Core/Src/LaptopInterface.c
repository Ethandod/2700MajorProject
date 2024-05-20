#include <stdint.h>
#include <stdlib.h>
#include "serial.h"
#include <string.h>


// Callback to stop the game
void (*stopGame)();

// Strings to transmit to the laptop
char green[] = "green";
char red[] = "red";

void checkStop(volatile uint8_t* string_buffer, uint32_t size) {
	// Calls the stopgame callback if the string is "stop"
	if (strncmp("stop", (char*)string_buffer, 4) == 0) {
		stopGame();
	}
}

void laptopInterfaceInitialise(void (*stopGameFunction)()) {
	// Initialise the serial port and set the stopGame callback
	stopGame = stopGameFunction;
	serialInitialise(10, BAUD_115200, &USART1_PORT, &checkStop);
}

void setLaptopGreen() {
	// Transmit the string "green" to the laptop
	 volatile uint8_t* ptr = (volatile uint8_t*) green;
	 serialTransmitString(ptr, &USART1_PORT);
}

void setLaptopRed() {
	// Transmit the string "red" to the laptop
	 volatile uint8_t* ptr = (volatile uint8_t*) red;
	 serialTransmitString(ptr, &USART1_PORT);
}
