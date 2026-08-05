# 👾 Chipate

A simple Chip-8 emulator using C++ and SDL3

## About

Chip-8 is an interpreted programming language that can run in an 8-bit virtual machine. It was made to make writing 2D games easy. The Chip-8 is capable of accessing 4KB of memory, has 16 8-bit registers and one 16-bit register that is used to store memory addresses, and able to execute 36 instructions based on the Chip-8 ISA. 

## Usage

To run the program, follow these steps:
1. Clone this repo
`git clone https://github.com/Najippp/chipate`
1. Inside the repo, create a folder named build
`mkdir build && cd build`
1. Run this command to compile
```cmake ..
    make```
1. Run the executable
`./chipate`