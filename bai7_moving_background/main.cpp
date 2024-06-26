#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"
#include "graphics.h"

using namespace std;

int main(int argc, char* argv[])
{
    Graphics graphics;
    graphics.init();

    ScrollingBackground background;
    background.setTexture(graphics.loadTexture(BACKGROUND_IMG));

    bool quit = false;

    SDL_Event event;

    while (!quit) {
        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) quit = true;
        }

        background.scroll(3);

        graphics.render(background);

        graphics.presentScene();

        SDL_Delay(1);
    }

    SDL_DestroyTexture(background.texture);
    graphics.quit();

    return 0;
}
