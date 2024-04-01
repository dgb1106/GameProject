#ifndef _BALL__H
#define _BALL__H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"
#include "object.h"

class Ball
{
public:
    Ball(double initialVelocityX, double initialVelocityY) {
        velocity.x = initialVelocityX;
        velocity.y = initialVelocityY;
    }

    void update(Vector2D& position);
private:
    Vector2D velocity;

};
#endif // _BALL__H
