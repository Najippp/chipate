#include "processor.hpp"
#include "decoder.hpp"
#include <iostream>
#include <cstring>

uint8_t reverse_bits(uint8_t byte) {
    uint8_t result = 0;

    for (int i = 0; i < 8; i++) {
        uint8_t placeholder = byte & 1;
        placeholder <<= (7 - i);

        result |= placeholder;
        byte >>= 1;
    }

    return result;
}

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
            Instruction_Draw(ram, display, x, y, n);
            std::cout << "Draw" << std::endl;
            break;
        case INSTRUCTION_UNKNOWN:
        default:
            std::cout << "UNKNOWN" << std::endl;
            break;
    }
}

void Chip8_Processor::Instruction_Draw(Memory &ram, Display &display, uint16_t x, uint16_t y, uint16_t n) {
    uint16_t x_pos = v_reg[x] % 64;
    uint16_t y_pos = v_reg[y] % 32;
    
    uint8_t draw_buffer[n];
    for (int i = 0; i < n; i++) {
        draw_buffer[i] = ram.Fetch_Memory(index + i);
    }

    uint64_t screen[32];
    std::memcpy(screen, display.pixels, sizeof(screen));

    for (int i = 0; i < n; i++) {
        screen[y_pos + i] ^= (uint64_t) reverse_bits(draw_buffer[i]) << x_pos;
    }

    std::memcpy(display.pixels, screen, sizeof(screen));
}

