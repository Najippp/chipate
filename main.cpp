#include <iostream>

#include "display.hpp"
#include "memory.hpp"
#include "decoder.hpp"
#include "processor.hpp"

int main () {
    Display display;
    Memory memory;
    Chip8_Processor processor;
    memory.Load_Program("../ROM/IBMLogo.ch8");

    if (!display.Init()) {
        std::cerr << "Error initializing SDL" << SDL_GetError() << std::endl;
        return 1;
    }

    while (display.is_running) {
        display.Render();
        display.Handle_Event();
    }

    return 0;
}