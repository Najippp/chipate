#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

class Display {
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;
    SDL_Texture *texture;

    unsigned char pixels[32][64] = {0};

public:
    bool is_running = true;

    bool Init();
    void Free();
    void Render();
    void Handle_Event();
};