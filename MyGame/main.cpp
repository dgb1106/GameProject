#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "defs.h"
#include "graphics.h"
#include "object.h"
#include "ball.h"

using namespace std;

void waitUntilKeyPressed() {
    SDL_Event e;
    while (true) {
        if (SDL_PollEvent(&e) != 0 && (e.type == SDL_KEYDOWN || e.type == SDL_QUIT))
            return;
        SDL_Delay(100);
    }
}

int main(int argc, char* argv[])
{
    Graphics graphics;
    graphics.init();

    SDL_Texture* background = graphics.loadTexture(BACKGROUND_IMG);
    SDL_Texture* ball_img = graphics.loadTexture(BALL_IMG);

    Vector2D position(180 - 16, SCREEN_HEIGHT/2 - 16);
    Ball ball(2, 2);

    bool quit = false;
    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) quit = true;
        }

        graphics.prepareScene(background);
        graphics.renderTexture(ball_img, position.x, position.y);
        graphics.presentScene();

        ball.update(position);
    }

    graphics.quit();

    return 0;
}
