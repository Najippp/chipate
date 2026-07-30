#include <iostream>

#include "display.hpp"

int main () {
    Display display;
    if (display.Init()) {
        SDL_Delay(5000);
    };

    display.Free();
}