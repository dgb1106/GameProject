#ifndef _GRAPHICS__H
#define _GRAPHICS__H

#include <iostream>
#include <cmath>
#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"
#include "text.h"

void logErrorAndExit(const char* msg, const char* error);

struct ScrollingBackground {
    SDL_Texture* texture;

    int scrollingOffset = 0;
    int width;
    int height;

    void setTexture(SDL_Texture* _texture);

    void scroll(int distance);
};

struct Graphics
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Surface* windowIcon;

    void init();

    void prepareScene();

    void prepareScene(SDL_Texture* background);

    void presentScene();

    SDL_Texture* loadTexture(const char* filename);

    void renderTexture(SDL_Texture* texture, int x, int y);

    void renderTexture(SDL_Texture* texture, int x, int y, double angle);

    SDL_Texture* renderText(const char* text, TTF_Font* font, SDL_Color color);

    void render(const ScrollingBackground& bgr);

    void quit();
};
#endif // _GRAPHICS__H
