#pragma once
#include <vector>
#include "memory.hpp"
#include "io.hpp"

class Chip8_Processor {
private:
    uint8_t v_reg[16];         // General purpose registers
    uint16_t index;            // 'I' register used for pointing to a memory location
    uint16_t pc = 0x200;           // Program counter
    uint8_t delay_timer = 255;
    uint8_t sound_timer;
    std::vector<uint16_t> stack;

    void Instruction_Draw(Memory &ram, IO &io, uint16_t x, uint16_t y, uint16_t n);

public:
    // GETTER AND SETTER
    uint8_t Get_Delay_Timer();
    void Set_Delay_Timer(uint8_t new_time);

    void Execute(Memory &ram, IO &io);
};
