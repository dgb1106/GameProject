#include "music.h"

void Music::logErrorAndExit(const char* msg, const char* error) {
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
    SDL_Quit();
}

void Music::init() {
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        logErrorAndExit( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
    }
}

Mix_Music* Music::loadMusic(const char* filename) {
    Mix_Music* music = Mix_LoadMUS(filename);
    if (music == nullptr) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Could not load music! SDL_mixer Error: %s", Mix_GetError());
    }
    return music;
}

Mix_Chunk* Music::loadSound(const char* filename) {
    Mix_Chunk* chunk = Mix_LoadWAV(filename);
    if (chunk == nullptr) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Could not load sound! SDL_mixer Error: %s", Mix_GetError());
    }
    return chunk;
}

void Music::play(Mix_Music* music) {
    if (music == nullptr) return;

    if (Mix_PlayingMusic() == 0) {
        Mix_PlayMusic(music, -1 );
    }
    else if( Mix_PausedMusic() == 1 ) {
        Mix_ResumeMusic();
    }
}

void Music::play(Mix_Chunk* chunk) {
    if (chunk != nullptr) {
        Mix_PlayChannel(-1, chunk, 0);
    }
}
