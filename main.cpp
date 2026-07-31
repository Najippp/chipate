#include <iostream>

#include "display.hpp"
#include "memory.hpp"

int main () {
    Display display;
    if (display.Init()) {    
        Memory memory;
        memory.Load_Program("../ROM/IBMLogo.ch8");
        SDL_Delay(5000);
    };

    display.Free();
}