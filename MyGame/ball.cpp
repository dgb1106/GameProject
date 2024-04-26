#include <iostream>
#include <cmath>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>

#include "defs.h"
#include "ball.h"
#include "object.h"
#include "hole.h"
#include "tile.h"
#include "music.h"

Ball::Ball(Vector _position, SDL_Texture* _texture) : Object(_position, _texture) {}

void Ball::setVelocity(double _x, double _y) {
    velocity.x = _x;
    velocity.y = _y;
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

void Ball::checkCollision(std::vector <Tile> tiles, Music music, Mix_Chunk* bounce) {
    static bool xCollided = false;
    static bool yCollided = false;

    if (getPosition().x + BALL_SIZE >= SCREEN_WIDTH - BORDER_SIZE_HORIZONTAL || getPosition().x <= BORDER_SIZE_HORIZONTAL) {
        if (!xCollided) {
            velocity.x *= -1;
            xCollided = true;
            music.play(bounce);
        }
    } else {
        xCollided = false;
    }
    if (getPosition().y + BALL_SIZE >= SCREEN_HEIGHT - BORDER_SIZE_VERTICAL || getPosition().y <= BORDER_SIZE_VERTICAL) {
        if (!yCollided) {
            velocity.y *= -1;
            yCollided = true;
            music.play(bounce);
        }
    } else {
        yCollided = false;
    }

    for (Tile t : tiles) {
        double newX = getPosition().x + velocity.x;
        double newY = getPosition().y;
        if (newX + BALL_SIZE >= t.getPosition().x && newX <= t.getPosition().x + t.getTextureSize().w && newY + BALL_SIZE >= t.getPosition().y && newY <= t.getPosition().y + t.getTextureSize().h) {
            velocity.x *= -1;
            music.play(bounce);
        }
        newX = getPosition().x;
        newY = getPosition().y + velocity.y;
        if (newX + BALL_SIZE >= t.getPosition().x && newX <= t.getPosition().x + t.getTextureSize().w && newY + BALL_SIZE >= t.getPosition().y && newY <= t.getPosition().y + t.getTextureSize().h) {
            velocity.y *= -1;
            music.play(bounce);
        }
    }
}

void Ball::checkWin(Hole hole) {
    int centerX = getPosition().x + BALL_SIZE/2;
    int centerY = getPosition().y + BALL_SIZE/2;
    if (centerX >= hole.getPosition().x + 6 && centerX <= hole.getPosition().x + hole.getTextureSize().w - 6 && centerY >= hole.getPosition().y + 6 && centerY <= hole.getPosition().y + hole.getTextureSize().h - 6) {
        setPosition(hole.getPosition().x + 4, hole.getPosition().y + 4);
        win = true;
    }
}

void Ball::update(bool mouseDown, bool mousePressed, Hole hole, std::vector <Tile> tiles, Music music, Mix_Chunk* hit, Mix_Chunk* bounce) {
    if (mousePressed && moving) {
        int mouseX = 0;
        int mouseY = 0;
        SDL_GetMouseState(&mouseX, &mouseY);
        setInitialMousePosition(mouseX, mouseY);
    }

    static bool played = false;
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

        setVelocity(abs(velocity1D * cos(getAngle())) * directionX / 50, abs(velocity1D * sin(getAngle())) * directionY / 50);
        if (!played) {
            music.play(hit);
            played = true;
        }
    } else {
        moving = false;
        played = false;
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
        checkCollision(tiles, music, bounce);
    }
    checkWin(hole);
    if (win) {
        velocity.x = 0;
        velocity.y = 0;
        return;
    }
}
