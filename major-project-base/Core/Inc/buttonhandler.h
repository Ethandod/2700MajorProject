#ifndef BUTTONHANDLER_H
#define BUTTONHANDLER_H

#include "stm32f303xc.h"
#include <stddef.h>

void initButtonHandler(void (*callback)(void));
void EXTI0_IRQHandler(void);

#endif /* BUTTONHANDLER_H */
