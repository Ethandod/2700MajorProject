#ifndef LAPTOP_INTERFACE_HEADER
#define LAPTOP_INTERFACE_HEADER

#include <stdint.h>
#include "stm32f303xc.h"


void laptopInterfaceInitialise(void (*stopGameFunction)());
void setLaptopGreen();
void setLaptopRed();

#endif
