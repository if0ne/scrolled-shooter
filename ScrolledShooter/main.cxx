#include <SDL.h>
#include "spdlog/spdlog.h"

int main(int argc, char* argv[]) {
    SDL_Window* window = nullptr;
    SDL_Surface* surface = nullptr;
    bool isRunning = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        spdlog::error("Occurs error while SDL initialization");
        return -1;
    }

    spdlog::info("Initializing game");

    window = SDL_CreateWindow(
        "Scrolled Shooter", 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        800, 
        640, 
        SDL_WINDOW_SHOWN
    );

    surface = SDL_GetWindowSurface(window);

    SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format, 0xFF, 0x33, 0xC2));
    SDL_UpdateWindowSurface(window);

    while (isRunning) {
        SDL_Event e;

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                isRunning = false;
            }
        }
    }

    spdlog::info("Closing game");

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}