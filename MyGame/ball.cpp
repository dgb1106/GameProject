#include <iostream>
#include <cmath>
#include <SDL.h>
#include <SDL_image.h>

#include "defs.h"
#include "ball.h"
#include "object.h"

Ball::Ball(Vector _position, SDL_Texture* _texture) : Object(_position, _texture) {}

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

double Ball::getDistance(Vector a, Vector b) {
    return (sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2)));
}

void Ball::checkCollision() {
    static bool xCollided = false;
    static bool yCollided = false;

    if (getPosition().x + BALL_SIZE >= SCREEN_WIDTH - BORDER_SIZE_HORIZONTAL || getPosition().x <= BORDER_SIZE_HORIZONTAL) {
        if (!xCollided) {
            velocity.x *= -1;
            xCollided = true;
        }
    } else {
        xCollided = false;
    }
    if (getPosition().y + BALL_SIZE >= SCREEN_HEIGHT - BORDER_SIZE_VERTICAL || getPosition().y <= BORDER_SIZE_VERTICAL) {
        if (!yCollided) {
            velocity.y *= -1;
            yCollided = true;
        }
    } else {
        yCollided = false;
    }
}

void Ball::update(bool mouseDown, bool mousePressed, Hole hole) {
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

        velocity1D = getDistance(initialMousePosition, finalMousePosition);

        double dx = finalMousePosition.x - initialMousePosition.x;
        double dy = finalMousePosition.y - initialMousePosition.y;

        setAngle(atan2(dy, dx));

        if (dx < 0 && dy < 0) {
            directionX = 1;
            directionY = 1;
        } else if (dx < 0 && dy > 0) {
            directionX = 1;
            directionY = -1;
        } else if (dx > 0 && dy > 0) {
            directionX = -1;
            directionY = -1;
        } else if (dx > 0 && dy < 0) {
            directionX = -1;
            directionY = 1;
        }

        setVelocity(abs(velocity1D * cos(getAngle())) * directionX / 20, abs(velocity1D * sin(getAngle())) * directionY / 20);

    } else {
        moving = false;
        setPosition(getPosition().x + getVelocity().x, getPosition().y + getVelocity().y);
        if (getVelocity().x > 0.1 || getVelocity().x < -0.1 || getVelocity().y > 0.1 || getVelocity().y < -0.1) {
            if (velocity1D > 0) {
                velocity1D *= FRICTION;
                velocity.x *= FRICTION;
                velocity.y *= FRICTION;
            }
        } else {
            setVelocity(0,0);
            moving = true;
        }
        checkCollision();
    }

    if (getPosition().x >= hole.getPosition().x && getPosition().x + BALL_SIZE <= hole.getPosition().x + hole.getTextureSize().w && getPosition().y >= hole.getPosition().y && getPosition().y + BALL_SIZE <= hole.getPosition().y + hole.getTextureSize().h) {
        win = true;
    }
    if (win) {
        velocity.x = 0;
        velocity.y = 0;
        return;
    }
}
