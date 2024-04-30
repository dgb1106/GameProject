#include "text.h"

void initFont() {
    if (TTF_Init() == -1) {
        logErrorAndExit("SDL_ttf could not initialize! SDL_ttf Error: ", TTF_GetError());
    }
}

TTF_Font* loadFont(const char* filename, int fontSize) {
    TTF_Font* font = TTF_OpenFont(filename, fontSize);
    if (font == nullptr) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,"Load font %s", TTF_GetError());
    }
    return font;
}

void quitFont() {
    TTF_Quit();
}
