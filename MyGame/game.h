#ifndef _GAME__H
#define _GAME__H

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

struct Game
{
    Graphics graphics;

    SDL_Texture* background;
    SDL_Texture* ball_img;
    SDL_Texture* paint_img;
    SDL_Texture* hole_img;
    SDL_Texture* tile64_img;
    SDL_Texture* tile32_img;
    SDL_Texture* tileHorizontal_img;
    SDL_Texture* tileVertical_img;

    Mix_Music* bg_music;
    Mix_Chunk* hit_sound;
    Mix_Chunk* bounce_sound;
    Mix_Chunk* levelUp_sound;
    Mix_Chunk* finalWin_sound;

    Ball ball;
    Object paint;
    Hole hole;

    std::vector <Tile> tiles;

    int level = 1;

    bool quit = false;
    bool mouseDown = false;
    bool mousePressed = false;

    Uint32 frameStart;
    int frameTime;

    void initializeGraphics();

    void initializeMusic();

    void init();

    void handleEvents();

    std::vector <Tile> loadTiles(int level);

    void loadLevel(int level);

    void renderGraphics();

    void running();

    void freeMemory();
};
#endif // _GAME__H
