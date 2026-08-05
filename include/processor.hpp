#pragma once
#include "memory.hpp"
#include "display.hpp"

class Chip8_Processor {
private:
    uint8_t v_reg[16];         // General purpose registers
    uint16_t index;            // 'I' register used for pointing to a memory location
    uint16_t pc = 0x200;           // Program counter
    uint8_t delay_timer;
    uint8_t sound_timer;

public:
    void Execute(Memory &ram, Display &display);
};
