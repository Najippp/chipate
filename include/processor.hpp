#pragma once
#include "memory.hpp"

class Chip8_Processor {
private:
    unsigned char v_reg[16];         // General purpose registers
    unsigned short index;            // 'I' register used for pointing to a memory location
    unsigned short pc = 0x200;           // Program counter
    unsigned char delay_timer;
    unsigned char sound_timer;

public:
    void Execute(Memory ram);
};
