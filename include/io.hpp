#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "memory.hpp"

class IO {
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;
    SDL_Texture *texture;

    bool is_running = true;

    bool Update_Texture();
public:
    uint64_t pixels[32] = {0};         // 1 bit per pixel, 0 is black and 1 is white

    // INITIALIZE AND DELETE IO
    bool Init();
    void Free();

    // PREDICATES
    bool Is_Running();

    // DISPLAY IO METHODS
    void Render();
    void Clear_Screen();

    // INPUT IO METHODS
    int Get_Event();
};