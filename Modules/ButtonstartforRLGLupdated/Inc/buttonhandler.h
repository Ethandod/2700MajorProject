#ifndef BUTTONHANDLER_H
#define BUTTONHANDLER_H

#include <stdint.h>
#include <stdbool.h>

// Function pointer type for the callback
typedef void (*ButtonCallback)(void);

// Initialize the button handler
void initButtonHandler(ButtonCallback callback);

// Update button state
void updateButtonState(uint32_t buttonState);

#endif
