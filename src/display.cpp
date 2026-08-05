#include "display.hpp"
#include <iostream>
#include <cstring>

bool Display::Init() {
    // Initialize everything needed for SDL
    pixels[20][10] = 1;

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

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX8, 
        SDL_TEXTUREACCESS_STREAMING, 64, 32);
    if (!texture) {
        std::cerr << "Error creating texture: " << SDL_GetError() << std::endl;
        return false;
    }

    // Link texture with a black and white color palette
    SDL_Palette *color_palette = SDL_CreatePalette(2);
    if (!color_palette) {
        std::cerr << "Error creating color palette: " << SDL_GetError() << std::endl;
        return false;
    }
    
    SDL_Color colors[2] = {
        {0, 0, 0, 255},
        {255, 255, 255, 255}
    };

    SDL_SetPaletteColors(color_palette, colors, 0, 2);
    SDL_SetTexturePalette(texture, color_palette);

    SDL_DestroyPalette(color_palette);
    color_palette = nullptr;

    // Set scalemode so SDL does't smooth corners
    SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_PIXELART);           

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

    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    SDL_Quit();
}

void Display::Render() {
    void *draw_loc;             // Address that CPU and GPU can access
    int pitch;

    if (SDL_LockTexture(texture, NULL, &draw_loc, &pitch)) {
        SDL_memcpy(draw_loc, pixels, sizeof(pixels));
        SDL_UnlockTexture(texture);
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderTexture(renderer, texture, NULL, NULL);
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

bool Display::Is_Running() {
    return is_running;
}