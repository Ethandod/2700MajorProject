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
It initializes the potentiometer and reads the value from the potentiometer which then is sent to a different module to change the speed of the game. 
#### `pot.c`
  - `Potentiometer_Init`: Initialize the potentiometer (starts the ADC)
  - `Potentiometer_Read`: Reads the value from the potentiometer


### Button Module (Activation):
This handles the buttons that are used for activation of the game, resetting the game when someone in the 'red' mode stops the game and when someone finishes the game.
#### `buttonhandler.c`
- **Key Functions:**
  - `initButtonHandler`: Initialising the button so that when a function is called to it, it activates that function.


### Lidar/Sweeper Module:
This module handles the pan tilt unit and the lidar so that it is able to sweep the room, then using the lidar it can detect movement.
#### `sweep_flag.c`
- **Key Functions:**
  - `ProgrammeStatus`: Retreives the status of the program whether it is GREEN, RED, DETECTED or FINISHED
#### `lidar_sweep.c`
  - `setup_sweeper`: Inputs hardware timers for the servo  
  - `sweep_routine`: This initialises the sweeper so that it knows what to do when any of the program status's are flagged


### Integration


#### `main.c`
Acts as the central hub of the application, orchestrating the initialization and handling of Passes incoming data to execute the different modules that are setup for different points in our system like when the timer sets the status to RED this calls the `sweep_routine` also when the system activates and then when someone presses the spacebar to deactivate the game. 

#### `Laptopinterface.c`
The key functions drive the interface behavior. laptopInterfaceInitialise sets up a callback for a game-stopping function. setLaptopGreen flags the screen to turn green, while setLaptopRed flags it to turn red. The checkStop function monitors space bar input; if detected, it triggers laptopInterfaceInitialise, halting the game's progression.

#### `buttonhandler.c`
The primary function is initButtonHandler, which sets up the button functionality. When this function is invoked, it configures the button to trigger specific actions upon activation. This initialization likely involves assigning callback functions to the button, so when pressed, it executes the corresponding actions or functions designated for that particular event. This initialization process is crucial for ensuring the button's responsiveness and defining its behavior within the system or application it interacts with.

#### `buzzer.c`
The primary task revolves around initializing a timer and establishing callbacks to execute specific actions at predetermined intervals or for one-shot events, depending on the configured timer settings. A significant function within this module is `toggleBuzzer`, which handles the activation and deactivation of the buzzer. This function likely manages the state of the buzzer, enabling it to produce sound when toggled on and silencing it when toggled off. The toggling mechanism controlled by `toggleBuzzer` plays a pivotal role in integrating auditory feedback into the system's functionality, enhancing user interaction and providing alerts or notifications when necessary.

#### `lidar_sweep.c`
In `lidar_sweep.c`, the focus lies on managing the Lidar sweeper functionality. The `setup_sweeper` function is responsible for configuring hardware timers specifically tailored for controlling the servo motor associated with the Lidar unit. These timers likely dictate the precise timing and positioning of the servo motor to facilitate accurate and controlled scanning motions.

On the other hand, `sweep_routine` plays a crucial role in initializing the sweeper system, ensuring it responds appropriately to various program statuses being flagged. This function likely sets up the necessary conditions and actions to be taken when specific flags or indicators are raised within the program. By defining how the sweeper should behave under different circumstances, `sweep_routine` contributes to the overall functionality and reliability of the Lidar scanning process.

#### `pot.c`
Within `pot.c`, the functionalities revolve around managing the potentiometer, a variable resistor commonly used for input control or measurement purposes. 

The `Potentiometer_Init` function serves the purpose of initializing the potentiometer, typically by starting the Analog-to-Digital Converter (ADC) module. This initialization process prepares the hardware for reading analog signals from the potentiometer and converting them into digital values that can be processed by the microcontroller or system.

Meanwhile, `Potentiometer_Read` is responsible for actually reading the current value from the potentiometer. This function likely interacts with the ADC module to capture the analog voltage level produced by the potentiometer's wiper position and converts it into a digital value representing the potentiometer's position or setting. This reading can then be utilized within the system for various purposes, such as controlling parameters, adjusting settings, or providing feedback based on user input.

#### `serial.c`
In `Serial.c`, the main focus lies in facilitating communication between the system's hardware and the application-level code, particularly concerning system call operations. 

At the core of this module are key functions like `serialInitialise`, which is responsible for initializing the serial communication interface. This initialization likely involves configuring parameters such as baud rate, parity, and stop bits to establish a reliable communication channel between the system and external devices.

Another vital function is `serialTransmitString`, which handles the transmission of strings over the serial interface. This function specifically deals with sending either 'red' or 'green' strings over the serial connection. By providing this capability, the module enables the system to communicate predefined messages or status updates to external devices or other components within the system architecture, enhancing overall system interoperability and functionality.

#### `sweep_flag.c`
In `sweep_flag.c`, the functionality revolves around managing the program status, which indicates the current state or condition of the program's operation. A significant function within this module is `ProgrammeStatus`, responsible for retrieving and providing information regarding the program's status. This function likely accesses and reads internal variables or flags that denote whether the program state is categorized as GREEN, RED, DETECTED, or FINISHED. By offering insights into the program's status, `ProgrammeStatus` enables other components or modules within the system to adapt their behavior or processes accordingly, ensuring synchronized operation and effective management of the overall system functionality.

#### `timer.c`
In `timer.c`, the primary focus is on managing timing operations essential for executing tasks at precise intervals, crucial for time-sensitive operations such as LED blinking or coordinating system events. 

At the core of this module are key functions like `timerInitialise`, responsible for initializing the timer functionality. This function likely configures the timer hardware, specifying parameters such as the interval at which the timer should trigger and the callback function to execute when that interval is reached. 

Another critical function is `TIM4_IRQHandler`, which serves as the central component of the timing operation. This function is likely an Interrupt Service Routine (ISR) associated with the timer's hardware interrupt. When the timer reaches its specified interval, this ISR is triggered, allowing the set callback function to be executed promptly. By efficiently managing the timing aspects of the system, `TIM4_IRQHandler` ensures that tasks requiring precise timing are executed reliably and in synchronization with the system's overall operation.


### User Instructions

- Ensure that the STM32 definition files are included in the project. These files contain crucial definitions and are essential for the application to function correctly.

- Set your serial communication to use a baud rate of 115200 for optimal performance.

- 

### Credits

Some parts of the code, definitions and initialisations for this assignment has been adapted and inspired from lecture examples. Thanks to Stewart, we were able to gather important and main information as well as vital clues which were needed for the project.

