#ifndef _TIMER__H
#define _TIMER__H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "defs.h"
#include "graphics.h"
#include "ball.h"

inline int getTime(Uint32 startTime, bool win, bool gameOver, int level) {
    Uint32 elapsedTime = (SDL_GetTicks() - startTime) / 1000;
    static int extraTime = 0;
    int remainingTime = STANDARD_DURATION - elapsedTime + extraTime;

    if (remainingTime <= 0) {
        remainingTime = 0;
    }

    static bool timeAdded = false;
    if (win && !timeAdded) {
        extraTime += STANDARD_DURATION * 2/3;
        timeAdded = true;
    }

    if (!win) {
        timeAdded = false;
    }

    if (gameOver == true || (level == 5 && win == true)) {
        extraTime = 0;
    }

    return remainingTime;
}

inline const char* getTimeText(int playingTime) {
    std::string s = "TIME: ";
    s += std::to_string(playingTime);
    return s.c_str();
}

#endif // _TIMER__H
