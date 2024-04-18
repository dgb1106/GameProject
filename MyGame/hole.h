#ifndef _HOLE__H
#define _HOLE__H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "defs.h"
#include "object.h"

class Hole : public Object
{
public:
    Hole(Vector _position, SDL_Texture* _texture) : Object(_position, _texture) {
        textureSize.w = 32;
        textureSize.h = 32;
    }

    SDL_Rect getTextureSize() {
        return textureSize;
    }
private:
    SDL_Rect textureSize;
};
#endif // _HOLE__H
