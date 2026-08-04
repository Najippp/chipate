#include "display.hpp"
#include <iostream>

bool Display::Init() {
    // Initialize everything needed for SDL

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

    // Make the 960 x 480 window be treated as a 64 x 32 pixel screen
    SDL_SetRenderLogicalPresentation(renderer, 64, 32, SDL_LOGICAL_PRESENTATION_STRETCH);

    std::cout << "SDL Initialized" << std::endl;
    return true;
}

void Display::Free() {
    // Call to free memory
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

void Display::Render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderPoint(renderer, 0, 0);
    SDL_RenderPresent(renderer);
}

void Display::Handle_Event() {
    if (SDL_PollEvent(&event)) {

        switch(event.type) {
            case SDL_EVENT_QUIT:
                is_running = false;
                break;
            default:
                break;
        }
    }
}