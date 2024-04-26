#ifndef _MUSIC__H
#define _MUSIC__H

#include <SDL.h>
#include <SDL_mixer.h>
#include "defs.h"

struct Music
{
    void init();

    void logErrorAndExit(const char* msg, const char* error);

    Mix_Music* loadMusic(const char* filename);

    Mix_Chunk* loadSound(const char* filename);

    void play(Mix_Music* music);

    void play(Mix_Chunk* chunk);
};

#endif // _MUSIC__H
