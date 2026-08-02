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

    if (display.Init()) {    
        SDL_Delay(2000);
    };

    for (int i = 0; i < 37; i++) {
        processor.Execute(memory);
    }

    display.Free();
}