#ifndef BUTTON_HANDLER_H
#define BUTTON_HANDLER_H

#include <stdint.h>

// Define the callback function type
typedef void (*ButtonPressCallback)(void);

void enable_interrupt();

// Function to initialize the button handler module
void initButtonHandler(ButtonPressCallback callback);

// Function to handle the button press interrupt
void EXTI0_IRQHandler(void);

#endif /* BUTTON_HANDLER_H */
