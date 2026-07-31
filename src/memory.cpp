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
    file.read((char*) ram, buffer_size);

    for (int i = 0; i < 4; i++) {                                   // Output the first four bytes for debugging purposes
        std::cout << std::hex << static_cast<int>(static_cast<unsigned char>(ram[i])) << " ";           
    }
    std::cout << std::endl << std::dec;

    return true;
}