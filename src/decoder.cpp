#include "decoder.hpp"
#include <iostream>


char Decoder::Decode(unsigned char instruction[2]) {
    unsigned char first_byte = instruction[0];
    unsigned char second_byte = instruction[1];

    unsigned char first_nibble = (first_byte & 0xF0) >> 4;
    unsigned char second_nibble = (first_byte & 0x0F);
    unsigned char third_nibble = (second_byte & 0xF0) >> 4;
    unsigned char fourth_nibble = (second_byte & 0x0F);

    std::cout << "First nibble: " << std::hex << static_cast<int>(first_nibble) << std::endl;

    if (first_byte == 0x00 && second_byte == 0xE0) return INSTRUCTION_CLEAR;
    else if (first_nibble == 0x1) return INSTRUCTION_JUMP;
    else if (first_nibble == 0x6) return INSTRUCTION_SETREG;
    else if (first_nibble == 0x7) return INSTRUCTION_ADDREG;
    else if (first_nibble == 0xA) return INSTRUCTION_SETINDEX;
    else if (first_nibble == 0xD) return INSTRUCTION_DRAW;
    else return INSTRUCTION_UNKNOWN;
}  