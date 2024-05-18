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
4. Jono Tuite: Piezo Buzzer Module
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
This serves as the main hub of the application that manages setting up and handling of sending whatever comes in so that it can run through various modules based on different points within our system, for instance,`sweep_routine` is called immediately the timer hits RED also during system activation and also when the game has been switched off using a space bar through the Serial/Deactivation Module.

#### `Laptopinterface.c`
The interface functionality is determined by its primary methods. The game stopping function is prepared or initialised by `laptopInterfaceInitialise`. To cause the screen to appear green, use setLaptopGreen, on the other side, setLaptopRed will cause the screen to be red. monitor stop key the key functions drive the interface behavior. When space bar signal is found, call `laptopInterfaceInitialise` stops any continued progress in the game.

#### `buttonhandler.c`
What `initButtonHandler` does first is define how the button works. When called, set button such that it activates specific events. During initialization, what might be done is attaching some callback functions to this button such that if it s pressed then execute appropriate actions which are intended for the given occasion only. However, this is vital for making sure that responsiveness from this passed on as well as providing guidelines on how it should operate when employed by either an API or any other part of the system or application.

#### `buzzer.c`
At the core, the program involves setting up the timer and assigning triggers that will perform given tasks regularly or once when the timer goes off. An important function that is used in this file is `toggleBuzzer` that takes care of the buzzer’s activation and deactivation. Its behavior in this function is toggling on the buzzer so that audio is emitted and vice versa for turning it off.

#### `lidar_sweep.c`
`lidar_sweep.c` mainly focuses on managing the functionality of the Lidar sweeper. The hardware timers used to control the servo motor that operates the Lidar assembly are set up by the `setup_sweeper`function. These timers may specify the exact timing as well as position of the servo motor so as to allow accurate and controlled scanning motions.

On the other hand, `sweep_routine` is very beneficial when it comes to initializing the sweeper system hence it should be able to react properly when different statuses of program have been flagged out. This can include setting up necessary conditions and taking action upon encountering specific flags or indicators during program execution. `sweep_routine` helps in defining how the sweeper should react under various conditions for the whole process of scanning using Lidar to function effectively and dependably.

#### `pot.c`
Within `pot.c`, the functionalities revolve around managing the potentiometer, a variable resistor commonly used for input control or measurement purposes. 

The `Potentiometer_Init` function serves the purpose of initializing the potentiometer, typically by starting the Analog-to-Digital Converter (ADC) module. This initialization process prepares the hardware for reading analog signals from the potentiometer and converting them into digital values that can be processed by the microcontroller or system.

Meanwhile, `Potentiometer_Read` is responsible for actually reading the current value from the potentiometer. This function likely interacts with the ADC module to capture the analog voltage level produced by the potentiometer's wiper position and converts it into a digital value representing the potentiometer's position or setting. This reading can then be utilized within the system for various purposes, such as controlling parameters, adjusting settings, or providing feedback based on user input.

#### `serial.c`
To interact with the potentiometer, traditionally used for input control or measurement, `pot.c`’s functionalities have to be managed.

To achieve this initiation purpose, `Potentiometer_Init`’s responsibility is usually expressed in terms of the timing when it sets up Analog-to-Digital Converter (ADC) module unlike other related functions. This is done to make sure that hardware will be ready for reading an anlaog signal from potentiometer and eventually change it into a numeric form which is more convenient for the microcontroller or any other system processing logic.

On the other hand,`Potentiometer_Read` deals in actual measurement procedure of what current value a potentiometer holds as of the moment when called upon. During such an activity there might much interaction between this function and ADC module in order to capture an analog voltage level corresponding to the potentiometer wiper position before turning it into a digital value which represents the position or setting of a potentiometer itself. 

#### `sweep_flag.c`
`sweep_flag.c` is mainly concerned with controlling the status of the program, which describes the current state that the program is in. `ProgrammeStatus` is an important routine in this module responsible for accessing the program’s current status. The function probably reads internal variables or flags that show whether the program is in GREEN, RED, DETECTED or FINISHED state. Essentially, `ProgrammeStatus` provides information about the condition of the whole system so as other parts in it can adjust accordingly, synchronize their activities and properly manage its performance.

#### `timer.c`
The main goal of the `timer.c` file is to manage timing operations that are used while conducting some tasks at regular intervals requiring precised timings thus imperative to time-sensitive tasks such as LED blinking or coordinating system events. This module comprises of vital functions such as `timerInitialise` which is utilized during the initialization of timer functionality. Here, the function is likely configuring timer hardware by setting parameters like the time interval that should trigger it and also specifying which function is to be called every time it reaches that point.


An additional important one is `TIM4_IRQHandler` which plays the lead role in timing operation this is an Interrupt Service Routine (ISR) which is associated with the hardware interrupt of the timer. It is this ISR that triggers when the timer reaches its set interval and ensures that the callback function is called swiftly.With proper management of timing issues within the context of the entire system, the purpose of `TIM4_IRQHandler` is to enable execution of tasks requiring a high degree of temporal precision (Fermi et al., 1976), which should be synchronized with the general operation of the system


### User Instructions

- Ensure that the STM32 definition files are included in the project. These files contain crucial definitions and are essential for the application to function correctly.

- Set your serial communication to use a baud rate of 115200 for optimal performance to display if it is green or red.
- Setup up the python code for your laptop.
- Setup the STM32 with the potentiometer, lidar, pan tilt unit and buzzer.
- Run the STM32 program
- Adjust the potentiometer to the timing of the game for your liking.
- Press the user button on the STM32 to start the game.
- Can have as many players as you would like.
- When the computer screen is GREEN you can make your way to the laptop.
- When the computer screen is RED the lidar will scan the room and if there is any movement the buzzer will go off and the laser pointer ontop of the lidar will be pointing at the person who has moved. They will be eliminated from the game.
- Repeat the rpocess of the GREEN or RED screen until someone touches the space bar in which the screen will turn BLUE and that person is deemed the winenr of the game.

### Credits

Some parts of the code, definitions and initialisations for this assignment has been adapted and inspired from lecture examples. Thanks to Stewart, we were able to gather important and main information as well as vital clues which were needed for the project.

