#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"

#include "game.h"


void Mouse::move() {
    x += dx;
    y += dy;
}

void Mouse::turnNorth() {
    dy = -speed;
    dx = 0;
}

void Mouse::turnSouth() {
    dy = speed;
    dx = 0;
}

void Mouse::turnWest() {
    dx = -speed;
    dy = 0;
}

void Mouse::turnEast() {
    dx = speed;
    dy = 0;
}

void Mouse::render(const Mouse& mouse, const Graphics& graphics) {
        SDL_Rect filled_rect;
        filled_rect.x = mouse.x;
        filled_rect.y = mouse.y;
        filled_rect.w = 10;
        filled_rect.h = 10;

        SDL_SetRenderDrawColor(graphics.renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(graphics.renderer, &filled_rect);
    }

bool Mouse::gameOver(const Mouse& mouse) {
    return mouse.x < 0 || mouse.x >= SCREEN_WIDTH || mouse.y < 0 || mouse.y >= SCREEN_HEIGHT;
}
