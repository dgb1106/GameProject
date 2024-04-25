#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "defs.h"
#include "graphics.h"

using namespace std;

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if (SDL_PollEvent(&e) != 0 && (e.type == SDL_KEYDOWN || e.type == SDL_QUIT)) {
            return;
        }
        SDL_Delay(100);
    }
}

int main(int argc, char* argv[])
{
    Graphics graphics;
    graphics.init();

    Mix_Music* gMusic = graphics.loadMusic("assets\\RunningAway.mp3");
    graphics.play(gMusic);

    Mix_Chunk* gJump = graphics.loadSound("assets\\jump.wav");

    bool quit = false;

    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) quit = true;
        }

        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

        if (currentKeyStates[SDL_SCANCODE_UP]) {
            cerr << " Up";
            graphics.play(gJump);
        }
        if (currentKeyStates[SDL_SCANCODE_DOWN]) cerr << " Down";
        if (currentKeyStates[SDL_SCANCODE_LEFT]) cerr << " Left";
        if (currentKeyStates[SDL_SCANCODE_RIGHT]) cerr << " Right";

        cerr << "." << endl;

        SDL_Delay(100);
    }

    if (gMusic != nullptr) Mix_FreeMusic(gMusic);
    if (gJump != nullptr) Mix_FreeChunk(gJump);


    graphics.quit();

    return 0;
}
