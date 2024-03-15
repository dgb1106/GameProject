#ifndef _GAME__H
#define _GAME__H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"
#include "graphics.h"

#define INITIAL_SPEED 3;

struct Mouse
{
    int x, y;
    int dx = 0;
    int dy = 0;
    int speed = INITIAL_SPEED;

    void move();

    void turnNorth();
    void turnSouth();
    void turnWest();
    void turnEast();

    void render(const Mouse& mouse, const Graphics& graphics);

    bool gameOver(const Mouse& mouse);
};
#endif // _GAME__H
