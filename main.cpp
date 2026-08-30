#include <iostream>
#include <chrono>
#include <thread>
#include <string>

#include "display.hpp"
#include "memory.hpp"
#include "decoder.hpp"
#include "processor.hpp"

int main () {
    Display display;
    Memory memory;
    Chip8_Processor processor;

    std::string user_input;
    std::cout << "Enter ROM file name: ";
    if (!std::getline(std::cin, user_input)) return 1;

    std::string filepath = "../ROM/" + user_input;
    memory.Load_Program(filepath);

    if (!display.Init()) {
        std::cerr << "Error initializing SDL" << SDL_GetError() << std::endl;
        return 1;
    }

    while (display.Is_Running()) {
        display.Render();
        display.Handle_Event();

        processor.Execute(memory, display);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000/60));
    }

    display.Free();
    return 0;
}