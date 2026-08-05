#include "memory.hpp"
#include <fstream>
#include <filesystem>
#include <iostream>

bool Memory::Load_Program(const char *path) {
    std::ifstream file(path, std::ios::binary);                 // Create a read file stream

    if (!file.is_open()) {                                      // Open file error handling
        std::cerr << "Error opening ROM file" << std::endl;
        return false; 
    }
    
    // Read binary file
    int buffer_size = std::filesystem::file_size(path);    
    uint8_t rom[buffer_size];
    std::cout << "ROM Size: " << buffer_size << std::endl;
    file.read((char*) rom, buffer_size);                            
    
    // Move binary instructions to ram 
    for (int i = 0; i < buffer_size; i++) {
        ram[0x200 + i] = rom[i];
    }

    return true;
}

uint8_t Memory::Fetch_Memory(uint16_t location) {
    return ram[location];
}