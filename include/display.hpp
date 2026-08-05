#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "memory.hpp"

class Display {
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;
    SDL_Texture *texture;

    unsigned char pixels[32][8] = {0};         // 1 bit per pixel, 0 is black 1 is white
    bool is_running = true;

    bool Update_Texture();
public:
    bool Init();
    void Free();
    void Render();
    void Handle_Event();
    bool Is_Running();
    void Clear_Screen();
};