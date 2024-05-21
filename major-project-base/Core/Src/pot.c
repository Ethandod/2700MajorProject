#include "pot.h"

// Reference to the ADC handle declared in main.c
extern ADC_HandleTypeDef hadc1;

// Initializes the ADC for potentiometer readings
//void Potentiometer_Init(void) {
//    HAL_ADC_Start(&hadc1);
//}

// Reads the ADC value for the potentiometer
uint32_t Potentiometer_Read(void) {
    // Wait for ADC conversion to complete
    HAL_ADC_PollForConversion(&hadc1, 1000);
    // Return the converted value
    return HAL_ADC_GetValue(&hadc1);
}
