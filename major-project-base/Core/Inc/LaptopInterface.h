#ifndef LAPTOP_INTERFACE_HEADER
#define LAPTOP_INTERFACE_HEADER

#include <stdint.h>
#include "stm32f303xc.h"

// Initialise the laptop interface
void laptopInterfaceInitialise(void (*stopGameFunction)());
// Transmit the string "green" to the laptop
void setLaptopGreen();
// Transmit the string "red" to the laptop
void setLaptopRed();

#endif
