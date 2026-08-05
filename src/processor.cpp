#include "processor.hpp"
#include "decoder.hpp"
#include <iostream>

void Chip8_Processor::Execute(Memory &ram, Display &display) {
    // Fetch instruction
    uint8_t instruction[2] = {ram.Fetch_Memory(pc), ram.Fetch_Memory(pc + 1)};
    pc += 2;

    // Setting the instruction arguments
    uint16_t opcode = (instruction[0] << 8) | instruction[1];
    uint16_t nnn = opcode & 0x0FFF;
    uint16_t nn = opcode & 0x00FF;
    uint16_t n = opcode & 0x000F;
    uint16_t x = (opcode & 0x0F00) >> 8;
    uint16_t y = (opcode & 0x00F0) >> 4;

    char decoded = Decoder::Decode(instruction);

    // Instruction implementations
    switch (decoded) {
        case INSTRUCTION_CLEAR:
            display.Clear_Screen();
            std::cout << "Clear" << std::endl;
            break;
        case INSTRUCTION_JUMP:
            pc = static_cast<unsigned short>(nnn);
            std::cout << "Jump to: 0x" << std::hex << static_cast<int>(pc) << std::dec << std::endl;
            break;
        case INSTRUCTION_ADDREG:
            v_reg[x] += static_cast<unsigned char>(nn);
            std::cout << std::dec << "Added register V" << static_cast<int>(x) << ": " << static_cast<int>(v_reg[x]) << std::endl;
            break;
        case INSTRUCTION_SETREG:
            v_reg[x] = static_cast<unsigned char>(nn);
            std::cout << std::dec << "Set register V" << static_cast<int>(x) << ": " << static_cast<int>(v_reg[x]) << std::endl;           
            break;
        case INSTRUCTION_SETINDEX:
            index = static_cast<unsigned short>(nnn);
            std::cout << "Set index register to: 0x" << std::hex << static_cast<int>(index) << std::dec << std::endl;
            break;
        case INSTRUCTION_DRAW:
            std::cout << "Draw" << std::endl;
            break;
        case INSTRUCTION_UNKNOWN:
        default:
            std::cout << "UNKNOWN" << std::endl;
            break;
    }
}