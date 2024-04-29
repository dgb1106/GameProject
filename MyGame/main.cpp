#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "defs.h"
#include "game.h"
#include "graphics.h"
#include "object.h"
#include "ball.h"
#include "hole.h"
#include "tile.h"
#include "music.h"

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
    Game game;
    game.init();

    play(game.bg_music);

    bool quit = false;
    Uint32 frameStart;
    int frameTime;

    game.loadLevel(1);

    while (!quit) {
        game.running();
    }

    game.freeMemory();

    return 0;
}
