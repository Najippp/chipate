#pragma once

#include <SDL3/SDL.h>

class Display {
private:
    SDL_Window *window;
    SDL_Renderer *renderer;

    bool is_running;

public:
    bool Init();
    void Free();
};