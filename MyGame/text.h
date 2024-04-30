#ifndef _TEXT__H
#define _TEXT__H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "defs.h"
#include "graphics.h"

void initFont();

TTF_Font* loadFont(const char* filename, int fontSize);

void quitFont();
#endif // _TEXT__H
