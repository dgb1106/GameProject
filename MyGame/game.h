#ifndef _GAME__H
#define _GAME__H

#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

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

    SDL_Texture* menu;
    SDL_Texture* background;
    SDL_Texture* complete;

    SDL_Texture* ball_img;
    SDL_Texture* paint_img;
    SDL_Texture* hole_img;
    SDL_Texture* arrow_img;
    SDL_Texture* tile64_img;
    SDL_Texture* tile32_img;
    SDL_Texture* tileHorizontal_img;
    SDL_Texture* tileVertical_img;

    SDL_Surface* icon;
    SDL_Cursor* cursor;

    Mix_Music* bg_music;
    Mix_Chunk* hit_sound;
    Mix_Chunk* bounce_sound;
    Mix_Chunk* levelUp_sound;
    Mix_Chunk* finalWin_sound;

    TTF_Font* KaphFont24;
    TTF_Font* KaphFont36;
    TTF_Font* CrocanteFont;

    Ball ball;
    Object paint;
    Hole hole;

    std::vector <Tile> tiles;

    int status = 0;

    SDL_Texture* playText;
    SDL_Texture* guideText;
    SDL_Texture* exitText;

    int level = 1;
    SDL_Texture* levelText;
    int strokes = 0;
    SDL_Texture* strokesText;
    int lowestStrokes = 1000;
    SDL_Texture* lowestStrokesText;

    SDL_Texture* playAgainText;

    bool quit = false;
    bool mouseDown = false;
    bool mousePressed = false;

    Uint32 frameStart;
    int frameTime;

    void initializeGraphics();

    void initializeMusic();

    void initializeFont();

    void init();

    void handleEvents(bool& playedAgain);

    std::vector <Tile> loadTiles(int level);

    void loadLevel(int level);

    void renderGraphics();

    const char* getStrokesCount();

    const char* getLowestStrokes();

    const char* getLevelCount();

    void playAgain(bool& playedAgain, bool& musicPlayed);

    void running();

    void freeMemory();
};
#endif // _GAME__H
