#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"
#include "graphics.h"

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
    graphics.prepareScene(background);
    graphics.presentScene();

    SDL_Texture* ball = graphics.loadTexture(BALL_IMG);
    graphics.renderTexture(ball, 172, 292);
    graphics.presentScene();

    bool quit = false;
    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) quit = true;
        }


    }

    graphics.quit();

    return 0;
}
