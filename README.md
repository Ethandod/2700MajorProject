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
  - `timerInitialise`: Initialises the timer module setting up the relevent bits for the timer to operate.
  - 'Delay': Creates a delay and calls a function when complete.


### Serial/Deactivation Module:
This module handles the serial so that when a flag get's triggered it will be either green on the computer screen or red on the computer screen using a python module. The serial moniter will also update the user by outputting either red or green. The is also integration of the deactivation module into the Serial module as we have used the space bar on the laptop as the deactivator
#### `LaptopInterface.c`
- **Key Functions:**
  - `laptopInterfaceInitialise`: Initialises the stop callback function and the serial module as required.
  - `setLaptopGreen`: The computer screen will turn Green when this is flagged.
  - `setLaptopRed`: The computer screen will turn red when this is flagged.
  - `checkStop`: If a spacebar is pressed, this callback function is called so it stops the whole game.

#### `Serial.c`
Primarily involved with interfacing between the board and external devices. 
- **Key Functions:**
  - `serialInitialise`: Initialising the serial so that it can transmit a string.
  - `serialTransmitString`: Transmits the inputted string via the selected serial port.

### Piezo Buzzer Module:
Handles the Piezo buzzer by setting in on using a button handler.
#### `buzzer.c`
- **Key Functions:**
  - `toggleBuzzer`: Toggles the buzzer on.


### Potentiometer Module:
It initializes the potentiometer and reads the value from the potentiometer which then is sent to a different module to change the speed of the game. 
#### `pot.c`
- **Key Functions:**
  - `Potentiometer_Init`: Initialize the potentiometer (starts the ADC)
  - `Potentiometer_Read`: Reads the value from the potentiometer


### Button Module (Activation):
This handles the buttons that are used for activation of the game, resetting the game when someone in the 'red' mode stops the game and when someone finishes the game.
#### `buttonhandler.c`
- **Key Functions:**
  - `initButtonHandler`: Initialising the button so that when a function is called to it, it activates that function.


### Game Flow Module
This cordinates how each module should be behaving, employing get/set functionality for a variable that indicates the game's current state.
#### 'sweep_flag'
  - `get_status`: Returns current state of game.
  - `set_setup`: Sets the current state to the setup phase.
  - `set_green`: Sets the current state to 'green light'.
  - `set_red`: Sets the current state to 'red light'.
  - `set_detected`: Set the current state to 'detected'.
  - `ser_finished`: Set the current state to 'finished'.

### Lidar/Sweeper Module:
This module handles the pan tilt unit and the lidar so that it is able to sweep the room, and is used to detect movement.
#### `lidar_sweep`
  - `setup_sweeper`: Takes the hardware timers for the servos in the pan tilt unit and Lidar
  - `sweep_routine`: Sweeps the Pan Servo through a given range, taking distance readings with the Lidar. 

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
`lidar_sweep.c` mainly focuses on managing the functionality of the Lidar sweeper. The hardware timers used to control the servo motor that operates the Lidar assembly are set up by the `setup_sweeper` function. 
If the user wishes to fine tune how the unit sweeps, they can change the constants defined in `sweep.h`.
`sweep_routine` repeatedly sweeps the area infront of the unit until the game state switches back to green or, movement is detected. 

#### `pot.c`
Within `pot.c`, the functionalities revolve around managing the potentiometer, a variable resistor commonly used for input control or measurement purposes. 

The `Potentiometer_Init` function serves the purpose of initializing the potentiometer, typically by starting the Analog-to-Digital Converter (ADC) module. This initialization process prepares the hardware for reading analog signals from the potentiometer and converting them into digital values that can be processed by the microcontroller or system.

Meanwhile, `Potentiometer_Read` is responsible for actually reading the current value from the potentiometer. This function likely interacts with the ADC module to capture the analog voltage level produced by the potentiometer's wiper position and converts it into a digital value representing the potentiometer's position or setting. This reading can then be utilized within the system for various purposes, such as controlling parameters, adjusting settings, or providing feedback based on user input.

#### `sweep_flag.c`
`sweep_flag.c` is mainly concerned with controlling the status of the program, which describes the current state that the program is in. `ProgrammeStatus` is an important routine in this module responsible for accessing the program’s current status. The function probably reads internal variables or flags that show whether the program is in GREEN, RED, DETECTED or FINISHED state. Essentially, `ProgrammeStatus` provides information about the condition of the whole system so as other parts in it can adjust accordingly, synchronize their activities and properly manage its performance.

#### `timer.c`
The main goal of the `timer.c` file is to manage timing operations that are used while conducting some tasks at regular intervals requiring precised timings thus imperative to time-sensitive tasks such as LED blinking or coordinating system events. This module comprises of vital functions such as `timerInitialise` which is utilized during the initialization of timer functionality. Here, the function is configuring timer hardware by setting parameters like the time interval that should trigger it and also specifying which function is to be called every time it reaches that point.

### User Instructions

- Ensure that the STM32 definition files are included in the project. These files contain crucial definitions and are essential for the application to function correctly.
- Set your serial communication to use a baud rate of 115200 for optimal performance to display if it is green or red.
- Setup up the python code for your laptop.
- Setup the STM32 with the potentiometer, lidar, pan tilt unit and buzzer (wiring for PTU commented in main.c).
- Run the STM32 program
- Adjust the potentiometer to the timing of the game for your liking.
- Press the user button on the STM32 to start the game.
- Can have as many players as you would like.
- When the computer screen is GREEN you can make your way to the laptop.
- When the computer screen is RED the lidar will scan the room and if there is any movement the buzzer will go off and the laser pointer ontop of the lidar will be pointing at the person who has moved. They will be eliminated from the game.
- Repeat the rpocess of the GREEN or RED screen until someone touches the space bar in which the screen will turn BLUE and that person is deemed the winenr of the game.

### Credits

Some parts of the code, definitions and initialisations for this assignment has been adapted and inspired from lecture examples. Thanks to Stewart, we were able to gather important and main information as well as vital clues which were needed for the project.

