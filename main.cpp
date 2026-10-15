#include <iostream>
#include <chrono>
#include <thread>
#include <string>

#include "io.hpp"
#include "memory.hpp"
#include "decoder.hpp"
#include "processor.hpp"

int main () {
    IO io;
    Memory memory;
    Chip8_Processor processor;

    std::string user_input;
    std::cout << "Enter ROM file name: ";
    if (!std::getline(std::cin, user_input)) return 1;

    std::string filepath = "../ROM/" + user_input;
    memory.Load_Program(filepath);

    if (!io.Init()) {
        std::cerr << "Error initializing SDL" << SDL_GetError() << std::endl;
        return 1;
    }

    while (io.Is_Running()) {
        io.Render();

        processor.Execute(memory, io);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000/60));
    }

    io.Free();
    return 0;
}