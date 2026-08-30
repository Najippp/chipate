#pragma once

#include <cstdint>
#include <string>

class Memory {
private:
    uint8_t ram[4096] = {0};

public: 
    bool Load_Program(std::string path);
    void Update_Memory(uint16_t address, uint8_t value);
    uint8_t Fetch_Memory(uint16_t location);
};