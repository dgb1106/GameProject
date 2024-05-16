#ifndef _MUSIC__H
#define _MUSIC__H

#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>

#include "defs.h"
#include "graphics.h"

void initMusic();

Mix_Music* loadMusic(const char* filename);

Mix_Chunk* loadSound(const char* filename);

void play(Mix_Music* music);

void play(Mix_Chunk* chunk);

void pauseMusic();

void resumeMusic();

void pauseAll();

void resumeAll();

void quitMusic();

#endif // _MUSIC__H
