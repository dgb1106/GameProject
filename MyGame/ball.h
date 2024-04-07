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
    Ball(double initialVelocityX, double initialVelocityY, Vector initialPosition) {
        velocity.x = initialVelocityX;
        velocity.y = initialVelocityY;
        position = initialPosition;
    }

    void update(Vector& position);

    void setVelocity(double _x, double _y);

    Vector getPosition();

    void startMoving();

    bool clicked(int mouseX, int mouseY);

private:
    Vector velocity;
    Vector position;
    bool moving = false;
    const int ballSize = 32;
};
#endif // _BALL__H
