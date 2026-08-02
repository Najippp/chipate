#include <iostream>

#include "display.hpp"
#include "memory.hpp"
#include "decoder.hpp"

int main () {
    Display display;
    if (display.Init()) {    
        Memory memory;
        memory.Load_Program("../ROM/IBMLogo.ch8");
        SDL_Delay(2000);
    };

    unsigned char instruction[2] = {0xD1, 0x23};
    char result = Decoder::Decode(instruction);
    std::cout << static_cast<int>(result) << std::endl;
    display.Free();
}