# SNAKE Game Console – Bare-Metal STM32

A bare-metal Snake game implemented on STM32 using direct register-level programming (no HAL, no RTOS).
This project focuses on deterministic timing, interrupt-driven design, and finite state machines for game logic.

## 1. Project Overview

This project implements a bare-metal Snake game on STM32.
The system receives directional input from an analog joystick, renders the game field on an OLED display, and continuously updates the score on a multiplexed 4-Bit 7 segments LED.

User interaction is handled via two buttons:
the Left Button is used to start or restart the game,
while the Right Button toggles pause and resume during gameplay.

## 2. Learning Objectives

Practice bare-metal programming on STM32 without using HAL or RTOS

Understand ADC, AFIO, GPIO, I2C, RCC, TIMERS, and interrupts at the register level

Apply finite state machines to structure embedded game logic

Design a non-blocking main loop using time-driven events

Improve documentation and system-level thinking for embedded projects

## 3. Hardware Overview

MCU: STM32F103C8T6

Clock: 8 MHz internal clock (default, stable mode) and 72 MHz PLL-based clock (experimental configuration)

Display: OLED SH1106 (I2C) and 4-Bit 7 segments LED 74HC595 (GPIO)

Input: Joystick HW-504 and push buttons with software debounce

Programming: ST-Link

Development style: Bare metal (direct register access)

## 4. Pinout Schematic

The following schematic shows the pin mapping between the STM32, OLED display, 4-Bit 7 segments LED display, joystick, and buttons.

<p align="center">
  <img src="docs/images/SNAKE_Game_Console_schematic.svg" alt="SNAKE Game Console - Pinout Schematic" width="700">
</p>

## 5. Software Architecture

The software is structured around a non-blocking main loop and multiple state machines.
Timing-critical tasks are driven by timer interrupts, while game logic remains deterministic and easy to follow.
This separation improves maintainability and makes system behavior easier to reason about.

### 5.1 Overall System State Machine

This diagram describes the overall execution flow of the system.

<p align="center">
  <img src="docs/images/SNAKE_Game_Console_general.svg" alt="SNAKE Game Console - General System State Machine" width="700">
</p>

### 5.2 Game Logic State Machine

This diagram focuses on the internal game logic and gameplay states.

Each state block represents a group of related instructions responsible for a specific game behavior (e.g. movement, collision check, score update).

<p align="center">
  <img src="docs/images/SNAKE_Game_Console_detail.svg" alt="SNAKE Game Console - Detail System State Machine" width="1000">
</p>

## 6. Timing and Interrupt Design

A hardware timer interrupt is used as the game tick

Joystick inputs are sampled periodically to ensure responsive and real-time control

Button inputs are sampled periodically and processed using software debounce

The main loop remains non-blocking and reacts to state changes

Gamespace display updates and game logic are decoupled from input handling

The score is rendered on the display and updated continuously during runtime

This approach ensures predictable timing and avoids blocking delays.

## 7. Demo Video

A short demo video showing gameplay and button interaction:

▶️ [SNAKE Game Console - Demo Video](https://drive.google.com/file/d/1Ac2z-I8ll0Reda7CBXcM6twJafuE7RoA/view?usp=drive_link)

## 8. Build and Flash

Toolchain: arm-none-eabi-gcc

Build system: Makefile

Programmer: ST-Link

No vendor libraries or code generators are used.

## 9. Why Bare Metal?

This project intentionally avoids HAL and RTOS in order to:

Understand STM32 peripherals at register level

Gain full control over timing and execution flow

Avoid hidden abstractions and unnecessary overhead

Build a solid foundation for embedded system debugging

## 10. Performance & Timing Trade-offs

The system prioritizes deterministic behavior by using the default 8 MHz internal clock.
An experimental 72 MHz PLL-based configuration was evaluated and found to improve display refresh performance, but at the cost of reduced system stability.

The game score is displayed using a multiplexed 4-digit 7-segment LED, while the game field is rendered on an OLED display.
Under the 8 MHz configuration, limited CPU bandwidth results in a perceptibly low LED refresh rate, causing digits to appear sequentially rather than as a stable 4-digit display.

This behavior illustrates a practical trade-off between display refresh performance and overall system determinism in a bare-metal design.

## 11. Limitations and Future Improvements

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

## 12. Author

Author: Vo Phuc Thinh
