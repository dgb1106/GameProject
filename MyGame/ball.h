#ifndef _BALL__H
#define _BALL__H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"
#include "object.h"

class Ball : public Object
{
public:
    Ball(Vector _pos);

    Vector getVelocity() {
        return velocity;
    }

    Vector getInitialMousePosition() {
        return initialMousePosition;
    }

    Vector getFinalMousePosition() {
        return finalMousePosition;
    }

    void setVelocity(double _x, double _y);

    void setLaunchedVelocity(double _x, double _y);

    void setInitialMousePosition(double _x, double _y);

    void setFinalMousePosition(double _x, double _y);

    void update(bool mouseDown, bool mousePressed);

    double getDistance(Vector a, Vector b);

private:
    Vector velocity;
    Vector launchedVelocity;

    double velocity1D;
    double launchedVelocity1D;

    Vector initialMousePosition;
    Vector finalMousePosition;

    bool moving = true;

    int directionX = 1;
    int directionY = 1;
};
#endif // _BALL__H
