# Snake Game Console – Bare-Metal STM32

A bare-metal Snake game implemented on STM32 using direct register-level programming (no HAL, no RTOS).
This project focuses on deterministic timing, interrupt-driven design, and finite state machines for game logic.

## 1. Learning Objectives

Practice bare-metal programming on STM32 without using HAL or RTOS

Understand ADC, AFIO, GPIO, I2C, RCC, TIMERS, and interrupts at the register level

Apply finite state machines to structure embedded game logic

Design a non-blocking main loop using time-driven events

Improve documentation and system-level thinking for embedded projects

## 2. Hardware Overview

MCU: STM32F103C8T6

Clock: 8 MHz internal clock (default, stable mode) and 72 MHz PLL-based clock (experimental configuration)

Display: OLED SH1106 (I2C) and 4-Bit 7 segments LED 74HC595 (GPIO)

Input: Joystick HW-504 and push buttons with software debounce

Programming: ST-Link

Development style: Bare metal (direct register access)

## 3. Pinout Schematic

The following schematic shows the pin mapping between the STM32, OLED display, and buttons.

## 4. Software Architecture

The software is structured around a non-blocking main loop and multiple state machines.
Timing-critical tasks are driven by timer interrupts, while game logic remains deterministic and easy to follow.
This separation improves maintainability and makes system behavior easier to reason about.

### 4.1 Overall System State Machine

This diagram describes the overall execution flow of the system.

Legend:

Main Loop Flow – primary execution path of the program

Game State Transition – transitions between game states

Button Debounce Processing – software debounce handled by timing logic

Random Food Generation – food placement logic triggered by game events

Layers are visually separated to distinguish:

Main loop layer

State selection layer

Side service layer (button debounce, random generation)

### 4.2 Game Logic State Machine

This diagram focuses on the internal game logic and gameplay states.

Each state block represents a group of related instructions responsible for a specific game behavior (e.g. movement, collision check, score update).

## 5. Timing and Interrupt Design

A hardware timer interrupt is used as the game tick

Joystick inputs are sampled periodically to ensure responsive and real-time control

Button inputs are sampled periodically and processed using software debounce

The main loop remains non-blocking and reacts to state changes

Gamespace display updates and game logic are decoupled from input handling

The score is rendered on the display and updated continuously during runtime

This approach ensures predictable timing and avoids blocking delays.

## 6. Demo Video

A short demo video showing gameplay and button interaction:

▶️ (link will be added)

## 7. Build and Flash

Toolchain: arm-none-eabi-gcc

Build system: Makefile

Programmer: ST-Link

No vendor libraries or code generators are used.

## 8. Why Bare Metal?

This project intentionally avoids HAL and RTOS in order to:

Understand STM32 peripherals at register level

Gain full control over timing and execution flow

Avoid hidden abstractions and unnecessary overhead

Build a solid foundation for embedded system debugging

## 9. Performance & Timing Trade-offs:

The system prioritizes deterministic behavior by using the default 8 MHz internal clock.
An experimental 72 MHz PLL-based configuration was evaluated and found to improve display refresh performance, but at the cost of reduced system stability.

The game score is displayed using a multiplexed 4-digit 7-segment LED, while the game field is rendered on an OLED display.
Under the 8 MHz configuration, limited CPU bandwidth results in a perceptibly low LED refresh rate, causing digits to appear sequentially rather than as a stable 4-digit display.

This behavior illustrates a practical trade-off between display refresh performance and overall system determinism in a bare-metal design.

## 10. Limitations and Future Improvements

This project is primarily intended as a learning exercise and therefore has several limitations:

Game logic and hardware drivers are still partially coupled

No power-saving modes are used between game ticks

High score is stored in RAM only and is lost after reset

State machine design can be further generalized for scalability

Planned improvements and learning directions include:

Refactoring the code to better separate hardware abstraction and game logic

Adding low-power sleep modes between timer interrupts

Storing high scores in non-volatile memory (Flash / EEPROM)

Improving the scalability and reusability of the state machine framework

## 11. Author

Author: Vo Phuc Thinh
