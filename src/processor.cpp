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
    uint8_t vx_val;
    uint8_t digits;
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
        case INSTRUCTION_2NNN:
            // Call subroutine, push return address to stack
            stack.push_back(pc + 2);
            pc = static_cast<unsigned short>(nnn);
            break;
        case INSTRUCTION_00EE:
            // Return from subroutine
            pc = stack.back();
            stack.pop_back();
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

            // reset vf
            v_reg[0xF] = 0;
            break;
        case INSTRUCTION_8XY2:
            // AND operation
            v_reg[x] &= v_reg[y];

            // reset vf
            v_reg[0xF] = 0;
            break;
        case INSTRUCTION_8XY3:
            // XOR operation
            v_reg[x] ^= v_reg[y];

            // reset vf
            v_reg[0xF] = 0;
            break;
        case INSTRUCTION_8XY4:
            // add operation
            if (int(v_reg[x] + v_reg[y] > 255)) v_reg[0xF] = 1;         // Set flag according to overflow condition
            else v_reg[0xF] = 0;   

            v_reg[x] += v_reg[y];
            break;
        case INSTRUCTION_8XY5:
            // subtract operation
            if (v_reg[x] >= v_reg[y]) v_reg[0xF] = 1;                   // Set flag according to borrow condition
            else v_reg[0xF] = 0; 

            v_reg[x] -= v_reg[y];
            break;
        case INSTRUCTION_8XY6:
            // Copy vy to vx, put the LSB of vx to vf, shift right vx by one
            v_reg[x] = v_reg[y];
            v_reg[0xF] = v_reg[x] & 1;
            v_reg[x] >>= 1;
            break;
        case INSTRUCTION_8XY7:
            // vx = vy - vx, set vf according to borrow condition
            if (v_reg[y] >= v_reg[x]) v_reg[0xF] = 1;
            else v_reg[0xF] = 0; 

            v_reg[x] = v_reg[y] - v_reg[x];
            break;
        case INSTRUCTION_8XYE:
            // Copy vy to vx, put the MSB of vx to vf, shift left vx by one
            v_reg[x] = v_reg[y];
            v_reg[0xF] = (v_reg[x] & 0x10) >> 7;
            v_reg[x] <<= 1; 
            break;
        case INSTRUCTION_FX65:
            // fills register v0 to vx with I + 0, I + 1, . . ., I + x
            for (int i = 0; i <= x; i++) {
                v_reg[i] = ram.Fetch_Memory(index + i);
            }
            index += x + 1;
            break;
        case INSTRUCTION_FX55:
            // fills memory at address I + 0, I + 1, . . ., I + x with v0 to vx
            for (int i = 0; i <= x; i++) {
                ram.Update_Memory(index + i, v_reg[i]);
            }
            index += x + 1;
            break;
        case INSTRUCTION_FX33:
            // Stores the digits on vx (hundreds, tens, and ones) into I + 0, I + 1, I + x 
            vx_val = v_reg[x];
            for (int i = 2; i >= 0; i--) {
                digits = vx_val % 10;
                vx_val = (vx_val - digits)/10;
                ram.Update_Memory(index + i, digits);
            }
            break;
        case INSTRUCTION_FX1E:
            // Change I register to I + vx
            index += v_reg[x];
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

