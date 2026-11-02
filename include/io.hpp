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

    // States
    bool is_running = true;
    bool waiting_for_input = false;

    // Input states
    bool keys[16] = {};     // true if pressed
    int8_t pressed_key = -1;
    int8_t released_key = -1;

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
    int8_t Get_Event();
    int8_t Wait_Event();
    bool Is_Key_Down(int8_t key);
};