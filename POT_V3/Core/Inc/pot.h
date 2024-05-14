#ifndef POT_H
#define POT_H

#include "main.h"

// Function to initialize the potentiometer (starts the ADC)
void Potentiometer_Init(void);

// Function to read the value from the potentiometer
uint32_t Potentiometer_Read(void);

#endif // POT_H
