# MTRX2700

Welcome to the MTRX 2700 repository!


## Project Details: 
### Group Members: 
1. Jeremy Fox
2. Krish Singh
3. Ethan Dodson
4. Jono Tuite
5. Sean Sun

### Roles & Responsibilities
1. Jeremy Fox: Lidar and Pan tilt Modules
2. Krish Singh: Potentiometer Module
3. Ethan Dodson: Button Activation Module, Minutes and README
4. Jono Tuite: Piezo Buzzer Module and README
5. Sean Sun: Timer, Serial and Button Deactivation Modules


## Modules of our Program:

### Timer Module:
**`timer.c`**
Handles timing operations, allowing callbacks to be executed at regular intervals set during initialization. This is crucial for tasks that need precise timing like blinking LEDs or handling time-sensitive operations.
- **Key Functions:**
  - `timerInitialise`: Starts the timer with a specified interval and callback.
  - `TIM4_IRQHandler`: The heart of the timing operation, it calls the set callback whenever the timer hits the specified interval.


### Serial/Deactivation Module:
This module handles the serial so that when a flag get's triggered it will be either green on the computer screen or red on the computer screen using a python module. The serial moniter will also update the user by outputting either red or green. The is also integration of the deactivation module into the Serial module as we have used the space bar on the laptop as the deactivator
#### `LaptopInterface.c`
- **Key Functions:**
  - `laptopInterfaceInitialise`: Initialises the callback for a function that will be a stopping game function.
  - `setLaptopGreen`: The computer screen will turn Green when this is flagged.
  - `setLaptopRed`: The computer screen will turn red when this is flagged.
  - `checkStop`: Checks if the space bar has been pressed, if so it goes through the `laptopInterfaceInitialise` function and stops the whole game.

#### `Serial.c`
Primarily involved with interfacing between the system’s hardware capabilities and the application-level code, especially related to system call operations. 
- **Key Functions:**
  - `serialInitialise`: Initialising the serial so that it can transmit a string.
  - `serialTransmitString`: Sending the string either 'red' or 'green to the serial




### Piezo Buzzer Module:
Handles the Piezo buzzer by setting in on using a button handler.
#### `buzzer.c`
It initializes the timer and sets up callbacks that are executed at regular intervals or for one-shot events based on timer configurations.
- **Key Functions:**
  - `toggleBuzzer`: Toggles the buzzer on.


### Potentiometer Module:
#### `buzzer.c`
It initializes the timer and sets up callbacks that are executed at regular intervals or for one-shot events based on timer configurations.
- **Key Functions:**
  - `Potentiometer_Init`: Initialize the potentiometer (starts the ADC)
  - `Potentiometer_Read`: Reads the value from the potentiometer


### Button Module (Activation):
This handles the buttons that are used for activation of the game, resetting the game when someone in the 'red' mode stops the game and when someone finishes the game.
#### `buttonhandler.c`
- **Key Functions:**
  - `initButtonHandler`: Initialising the button so that when a function is called to it, it activates that function.



### Integration


#### `main.h`
Contains declarations and static variables used across the main application, particularly for managing the state of initialization and timer modes. Includes flags for initialization status and timer modes to manage application flow and interactions.

#### `main.c`
Acts as the central hub of the application, orchestrating the initialization and handling of Passes incoming serial data to execute commands like setting LED patterns, echoing strings, and configuring timers.



### Description of Application Behavior Based on Commands:

1. **LED Pattern Command (`"led 10001010"`):**
   - 


### User Instructions

- Ensure that the STM32 definition files are included in the project. These files contain crucial definitions and are essential for the application to function correctly.

- Set your serial communication to use a baud rate of 115200 for optimal performance.

- The command strings sent over the serial port should end with the terminating character, which is Control-Shift-2 on both macOS and Windows

### Credits

Some parts of the code, definitions and initialisations for this assignment has been adapted and inspired from lecture examples. Thanks to Stewart, we were able to gather important and main information as well as vital clues which were needed for the project.

