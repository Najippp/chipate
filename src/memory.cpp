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
    
    unsigned int buffer_size = std::filesystem::file_size(path);    // Check file size for buffer size
    unsigned char rom[buffer_size];
    std::cout << "ROM Size: " << buffer_size << std::endl;
    file.read((char*) rom, buffer_size);

    for (int i = 0; i < buffer_size; i++) {
        ram[0x200 + i] = rom[i];
    }

    return true;
}

unsigned char Memory::Fetch_Memory(unsigned short location) {
    return ram[location];
}