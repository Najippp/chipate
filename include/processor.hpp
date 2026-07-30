#pragma once

class Chip8_Processor {
private:
    unsigned char v_reg[16];         // General purpose registers
    unsigned short index;           // 'I' register used for pointing to a memory location
    unsigned short pc;              // Program counter
    unsigned char delay_timer;
    unsigned char sound_timer;

public:
    bool Execute();
};
