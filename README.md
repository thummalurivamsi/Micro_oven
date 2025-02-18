⚡MICRO OVEN⚡
👉Project Overview:
Purpose: Simulate the basic operations of a microwave oven using a PIC microcontroller and display the process on a CLCD screen.
Scope: The simulation replicates essential microwave oven functionalities like power-on, cooking mode selection, time setting, and temperature input, without actual hardware cooking.
Functional Modules:
Power ON Message Screen:

Displays a welcome message on the CLCD when the system is powered on.
Cooking Mode Selection:

Options: Macro, Grill, Convection, Start (quick start with 30s timer).
Input through a matrix keypad (SW1 to SW4).
Macro Mode:

Allows setting cooking power and time.
Time entry using keys 0-9, start with #, clear with *.
Pause, Resume, and Stop controls available.
Grill Mode:

Similar to Macro mode but specific to grilling.
Set cooking time and control the process (start, pause, resume, stop).
Convection Mode:

Requires temperature setting before setting cooking time.
Pre-heating phase before the cooking starts.
Start (Quick Start) Mode:

Starts the microwave with a default 30s timer.
Extend time in 30s increments by pressing Start/Resume.
User Interface:
Matrix keypad for input.
CLCD display to show system state, timer, and error messages.
Buzzer for alerts.
Hardware Integration:
PIC Microcontroller for control logic.
CLCD for displaying messages and status.
Matrix Keypad for user input.
Fan and Buzzer for simulation purposes.
Software Development:
Programmed in C using the XC8 compiler within MPLAB IDE.
State-machine-like approach to handle various modes and user inputs.
Timer module used for countdowns and cooking time management.
Key Features:
User-friendly interface with clear on-screen prompts.
Robust input validation and error handling.
Modular structure for easy enhancement and maintenance.
Possible Enhancements:
Implementing a real heating element and temperature sensor.
Adding more safety features like door status checking.
Introducing preset cooking programs.
