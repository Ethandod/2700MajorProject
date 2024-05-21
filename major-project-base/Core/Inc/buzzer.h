#ifndef __BUZZER_H
#define __BUZZER_H

#include "ptu_i2c.h"

uint32_t get_buzzer();
void toggleBuzzer(DAC_HandleTypeDef hdac);


#endif /* __MAIN_H */
