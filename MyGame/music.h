#ifndef _MUSIC__H
#define _MUSIC__H

#include <SDL.h>
#include <SDL_mixer.h>
#include "defs.h"

void initMusic();

void logErrorAndExit(const char* msg, const char* error);

Mix_Music* loadMusic(const char* filename);

Mix_Chunk* loadSound(const char* filename);

void play(Mix_Music* music);

void play(Mix_Chunk* chunk);

void pauseMusic();

void quitMusic();

#endif // _MUSIC__H
