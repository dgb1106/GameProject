#ifndef _GRAPHICS__H
#define _GRAPHICS__H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"

struct Background
{
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

    void logErrorAndExit(const char* msg, const char* error);

    void init();

    void prepareScene();

    void prepareScene(SDL_Texture* background);

    void presentScene();

    SDL_Texture* loadTexture(const char* filename);

    void renderTexture(SDL_Texture* texture, int x, int y);

    void render(const Background& bgr);

    void quit();
};
#endif // _GRAPHICS__H
