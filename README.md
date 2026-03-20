# STM32_BareMetalMetronome

Metronome made on STM32F401RE nucleo using bare-metal(No HAL/LL). 

Metronome is a device that dictates the steady tempo most commonly used to help with music practice. This particular prototype generates tempo in range 60-140 BPM through a buzzer, displays it on 7-segment display and stores the last used value in EEPROM module.

## Features 

- Made on STM32F401 Nucleo Board
- GPIO for pulse output on buzzer.
- 5641AS 7 segment display for current BPM(Beats Per Minute) indicator.
- Tempo controlled through ACD + DMA(potentiometer)
- Analog signal filtered through EMA and Deadzone stabilization
- 24AA01 EEPROM, connected through I2C to stor last used tempo value
- 2 Operating modes: Play and Config

## Hardware

- STM32F401RE Nucleo Board
- 5641AS 7 segment display with 330ohm resistors for each segment, using BC546 transistors for multiplexing
- Potentiometer for ADC input
- 24AA01 EEPROM I2C module
- 2 push buttons for state changes
- Buzzer

## Software

- ADC + DMA
- Filtering: EMA + Deadzone
- Timer for multiplexing 7segment display
- Timer for Pulse generation
- State machine: Play and config modes controlled via buttons

## DEMO

![image.png](attachment:e2519398-b9db-46df-9e8c-c0232dc1221c:image.png)
Screen from logic analyzer - It displays one operation of writing the value 120 to EEPROM.
