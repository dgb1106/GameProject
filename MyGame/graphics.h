#ifndef _GRAPHICS__H
#define _GRAPHICS__H

#include <iostream>
#include <cmath>
#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"
#include "text.h"

void logErrorAndExit(const char* msg, const char* error);

struct Graphics
{
    SDL_Window* window;
    SDL_Renderer* renderer;

    void init();

    void prepareScene();

    void prepareScene(SDL_Texture* background);

    void presentScene();

    SDL_Texture* loadTexture(const char* filename);

    void renderTexture(SDL_Texture* texture, int x, int y);

    void renderTexture(SDL_Texture* texture, int x, int y, double angle);

    SDL_Texture* renderText(const char* text, TTF_Font* font, SDL_Color color);

    void quit();
};
#endif // _GRAPHICS__H
