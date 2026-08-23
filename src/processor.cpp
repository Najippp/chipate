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
        case INSTRUCTION_00E0:
            // Clear screen instruction
            display.Clear_Screen();
            std::cout << "Clear" << std::endl;
            break;
        case INSTRUCTION_1NNN:
            // Jump to address
            pc = static_cast<unsigned short>(nnn);
            break;
        case INSTRUCTION_7XNN:
            // Add NN to vx
            v_reg[x] += static_cast<unsigned char>(nn);
            break;
        case INSTRUCTION_6XNN:
            // Set vx to NN
            v_reg[x] = static_cast<unsigned char>(nn);         
            break;
        case INSTRUCTION_ANNN:
            // Set index register to NNN
            index = static_cast<unsigned short>(nnn);
            break;
        case INSTRUCTION_DXYN:
            // Draw instruction
            Instruction_Draw(ram, display, x, y, n);
            break;
        case INSTRUCTION_3XNN:
            // Skip if vx is equal to NN
            if (nn == v_reg[x]) pc += 2;
            break;
        case INSTRUCTION_4XNN:
            // Skip if vx is not equal to NN
            if (nn != v_reg[x]) pc += 2;
            break;
        case INSTRUCTION_5XY0:
            // Skip if vx is equal to vy
            if (v_reg[x] == v_reg[y]) pc += 2;
            break;
        case INSTRUCTION_9XY0:
            // Skip if vx is not equal to vy
            if (v_reg[x] != v_reg[y]) pc += 2;
            break;
        case INSTRUCTION_8XY0:
            v_reg[x] = v_reg[y];
            break;
        case INSTRUCTION_8XY1:
            // OR operation
            v_reg[x] |= v_reg[y];
            break;
        case INSTRUCTION_8XY2:
            // AND operation
            v_reg[x] &= v_reg[y];
            break;
        case INSTRUCTION_8XY3:
            // XOR operation
            v_reg[x] ^= v_reg[y];
            break;
        case INSTRUCTION_8XY4:
            // add operation
            v_reg[x] += v_reg[y];
            break;
        case INSTRUCTION_UNKNOWN:
        default:
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

