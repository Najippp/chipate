#include "display.hpp"
#include <iostream>

bool Display::Init() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "Error Initializing SDL: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("Chipate", 960, 480, 0);
    if (!window) {
        std::cerr << "Error creating window: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        std::cerr << "Error creating renderer: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_SetRenderLogicalPresentation(renderer, 64, 32, SDL_LOGICAL_PRESENTATION_STRETCH);

    std::cout << "SDL Initialized" << std::endl;
    return true;
}

void Display::Free() {
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }

    SDL_Quit();
}