#include <iostream>
#include <cmath>
#include <SDL.h>
#include <SDL_image.h>

#include "defs.h"
#include "ball.h"
#include "object.h"

Ball::Ball(Vector _pos) : Object(_pos) {}

void Ball::setVelocity(double _x, double _y) {
    velocity.x = _x;
    velocity.y = _y;
}

void Ball::setLaunchedVelocity(double _x, double _y) {
    launchedVelocity.x = _x;
    launchedVelocity.y = _y;
}

void Ball::setInitialMousePosition(double _x, double _y) {
    initialMousePosition.x = _x;
    initialMousePosition.y = _y;
}

void Ball::setFinalMousePosition(double _x, double _y) {
    finalMousePosition.x = _x;
    finalMousePosition.y = _y;
}

void Ball::update(bool mouseDown, bool mousePressed) {
    if (mousePressed && moving) {
        int mouseX = 0;
        int mouseY = 0;
        SDL_GetMouseState(&mouseX, &mouseY);
        setInitialMousePosition(mouseX, mouseY);
    }
    if (mouseDown && moving) {
        int mouseX = 0;
        int mouseY = 0;
        SDL_GetMouseState(&mouseX, &mouseY);
        setFinalMousePosition(mouseX, mouseY);

        setVelocity((finalMousePosition.x - getInitialMousePosition().x)/-50, (finalMousePosition.y - getInitialMousePosition().y)/-50);
        setLaunchedVelocity((finalMousePosition.x - getInitialMousePosition().x)/-50, (finalMousePosition.y - getInitialMousePosition().y)/-50);

        velocity1D = SDL_sqrt(SDL_pow(abs(velocity.x), 2) + SDL_pow(abs(velocity.y), 2));
        launchedVelocity1D = velocity1D;

        directionX = velocity.x / abs(velocity.x);
        directionY = velocity.y / abs(velocity.y);

    } else {
        moving = false;
        setPosition(getPosition().x + getVelocity().x, getPosition().y + getVelocity().y);
        if (getVelocity().x > 0.1 || getVelocity().x < -0.1 || getVelocity().y > 0.1 || getVelocity().y < -0.1) {
            if (velocity1D > 0) {
                velocity1D *= FRICTION;
            }

            velocity.x = (velocity1D/launchedVelocity1D) * abs(launchedVelocity.x) * 10 * directionX;
            velocity.y = (velocity1D/launchedVelocity1D) * abs(launchedVelocity.y) * 10 * directionY;
        } else {
            setVelocity(0,0);
            moving = true;
        }

        if (getPosition().x + BALL_SIZE >= SCREEN_WIDTH) {
            setVelocity(-abs(getVelocity().x), getVelocity().y);
            directionX = -1;
        } else if (getPosition().x <= 0) {
            setVelocity(abs(getVelocity().x), getVelocity().y);
            directionX = 1;
        } else if (getPosition().y + BALL_SIZE >= SCREEN_HEIGHT) {
            setVelocity(getVelocity().x, -abs(getVelocity().y));
            directionY = -1;
        } else if (getPosition().y <= 0) {
            setVelocity(getVelocity().x, abs(getVelocity().y));
            directionY = 1;
        }
    }
}
