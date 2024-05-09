#ifndef _TILE__H
#define _TILE__H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <cmath>
#include "defs.h"
#include "object.h"

class Tile : public Object
{
public:
    Tile() {
        setPosition(0, 0);
        //texture = nullptr;
    }

    Tile(Vector _position, SDL_Texture* _texture) : Object(_position, _texture) {
        SDL_QueryTexture(_texture, nullptr, nullptr, &textureSize.w, &textureSize.h);
    }

    void moving() {
        double time = SDL_GetTicks() / 1000.0f;
        double newX = 432 + AMPLITUDE * sin(2 * M_PI * FREQUENCY * time);
        setPosition((int)newX, getPosition().y);
    }

    SDL_Rect getTextureSize() {
        return textureSize;
    }

private:
    SDL_Rect textureSize;
};
#endif // _TILE__H
