#ifndef _TILE__H
#define _TILE__H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "defs.h"
#include "object.h"

class Tile : public Object
{
public:
    Tile(Vector _position, SDL_Texture* _texture) : Object(_position, _texture) {
        SDL_QueryTexture(_texture, nullptr, nullptr, &textureSize.w, &textureSize.h);
    }

    SDL_Rect getTextureSize() {
        return textureSize;
    }

private:
    SDL_Rect textureSize;
};
#endif // _TILE__H
