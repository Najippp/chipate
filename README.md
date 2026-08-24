# 👾 Chipate

A simple Chip-8 emulator using C++ and SDL3

## About

Chip-8 is an interpreted programming language that can run in an 8-bit virtual machine. It was made to make writing 2D games easy. The Chip-8 is capable of accessing 4KB of memory, has 16 8-bit registers and one 16-bit register that is used to store memory addresses, and able to execute 36 instructions based on the Chip-8 ISA. 

## Usage

To run the program, follow these steps:
1. Clone this repo
```bash
git clone https://github.com/Najippp/chipate
```
1. Inside the repo, create a folder named build
```bash
mkdir build && cd build
```
1. Run this command to compile
```bash
cmake ..
make
```
1. Run the executable
```bash
./chipate
```
The program will run the Chip-8 ROM/binary file that is located in the "ROM" folder. Currently, the program only supports the standard IBM Logo test binaries.

## Progress Report

The core pillars of the Chip-8 have been implemented, which is the basic functions for memory management, processor, and display. At the moment, only 8 out of 36 instruction of the Chip-8 instructions have been implemented. Other functionalities will be added as soon as possible.

## To Do
- Keyboard inputs
- Delay and sound timers
- The other 15 instructions

## AI Usage Disclosure

AI is used ONLY in finding logical bugs in the code and helping me to understand concepts that I didn't understand. There is NO AI USED in making/writing code.
