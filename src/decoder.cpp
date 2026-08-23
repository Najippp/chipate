#include "decoder.hpp"
#include <cstdint>
#include <iostream>


char Decoder::First_Nibble(uint8_t byte) {
    return (byte & 0xF0) >> 4;
}

char Decoder::Second_Nibble(uint8_t byte) {
    return (byte & 0x0F);
}

char Decoder::Decode(uint8_t instruction[2]) {
    uint8_t first_byte = instruction[0];
    uint8_t second_byte = instruction[1];

    uint8_t first_nibble = Decoder::First_Nibble(first_byte);
    uint8_t second_nibble = Decoder::Second_Nibble(first_byte);
    uint8_t third_nibble = Decoder::First_Nibble(second_byte);
    uint8_t fourth_nibble = Decoder::Second_Nibble(second_byte);

    if (first_byte == 0x00 && second_byte == 0xE0) return INSTRUCTION_00E0;
    else if (first_nibble == 0x1) return INSTRUCTION_1NNN;
    else if (first_nibble == 0x6) return INSTRUCTION_6XNN;
    else if (first_nibble == 0x7) return INSTRUCTION_7XNN;
    else if (first_nibble == 0xA) return INSTRUCTION_ANNN;
    else if (first_nibble == 0xD) return INSTRUCTION_DXYN;
    else if (first_nibble == 0x5) return INSTRUCTION_5XY0;
    else if (first_nibble == 0x9) return INSTRUCTION_9XY0; 
    else if (first_nibble == 0x3) return INSTRUCTION_3XNN;
    else if (first_nibble == 0x4) return INSTRUCTION_4XNN;
    else return INSTRUCTION_UNKNOWN;
}  