#include "buttonhandler.h"
#include <stddef.h>

// Function pointer to hold the callback function
static ButtonCallback buttonCallback = NULL;

// Flag to indicate whether the game is initialized
static bool gameInitialized = false;

// Initialize the button handler
void initButtonHandler(ButtonCallback callback)
{
    buttonCallback = callback;
}

// Update button state
void updateButtonState(uint32_t buttonState)
{
    // Check if the button is pressed
    if (buttonState == 1)
    {
            // Start the game
            if (buttonCallback != NULL)
            {
                buttonCallback();
            }
            gameInitialized = true;
    }
}
