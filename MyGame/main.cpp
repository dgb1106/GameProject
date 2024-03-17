#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"

using namespace std;

int main(int argc, char* argv[])
{
    SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_RenderClear(renderer);

    SDL_Rect box;
    box.x = 0;
    box.y = 430;
    box.w = 50;
    box.h = 50;

    double speed = 0;

    bool quit = false;
    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) quit = true;
            if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
                speed = -5;
            }
        }
        box.y += speed;
        if (box.y <= 350) speed = -speed;
        if (box.y == 430) speed = 0;

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &box);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        SDL_RenderPresent(renderer);

        SDL_RenderClear(renderer);

        box.x += 5;

        if (box.x >= SCREEN_WIDTH) quit = true;
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    window = nullptr;
    renderer = nullptr;

    SDL_Quit();

    return 0;
}
