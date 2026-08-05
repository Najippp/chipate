#pragma once

#include <cstdint>

class Memory {
private:
    uint8_t ram[4096] = {0};

public: 
    bool Load_Program(const char *path);
    uint8_t Fetch_Memory(uint16_t location);
};