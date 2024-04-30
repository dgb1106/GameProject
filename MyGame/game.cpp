#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "game.h"

void Game::initializeGraphics() {
    graphics.init();
    background = graphics.loadTexture(BACKGROUND_IMG);
    ball_img = graphics.loadTexture(BALL_IMG);
    paint_img = graphics.loadTexture(PAINT_IMG);
    hole_img = graphics.loadTexture(HOLE_IMG);
    tile64_img = graphics.loadTexture(TILE64_IMG);
    tile32_img = graphics.loadTexture(TILE32_IMG);
    tileHorizontal_img = graphics.loadTexture(TILEHORIZONTAL_IMG);
    tileVertical_img = graphics.loadTexture(TILEVERTICAL_IMG);
}

void Game::initializeMusic() {
    initMusic();
    bg_music = loadMusic(BG_MUSIC);
    hit_sound = loadSound(HIT_SOUND);
    bounce_sound = loadSound(BOUNCE_SOUND);
    levelUp_sound = loadSound(LEVELUP_SOUND);
    finalWin_sound = loadSound(FINALWIN_SOUND);
}

void Game::initializeFont() {
    initFont();
    KaphFont = loadFont(FONT_KAPH, STROKES_SIZE);
}

void Game::init() {
    initializeGraphics();
    initializeMusic();
    initializeFont();

    ball.setTexture(ball_img);
    paint.setTexture(paint_img);
    hole.setTexture(hole_img);

    frameStart = SDL_GetTicks();
}

void Game::handleEvents() {
    mousePressed = false;

    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type)
        {
        case SDL_QUIT:
            quit = true;
            break;
        case SDL_MOUSEBUTTONDOWN:
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            if ((mouseX >= ball.getPosition().x && mouseX <= ball.getPosition().x + BALL_SIZE && mouseY >= ball.getPosition().y && mouseY <= ball.getPosition().y + BALL_SIZE)
                && ball.getVelocity().x == 0 && ball.getVelocity().y == 0) {
                mousePressed = true;
                mouseDown = true;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            mouseDown = false;
            break;
        }
    }
}

std::vector <Tile> Game::loadTiles(int level) {
    std::vector <Tile> tiles;
    switch (level) {
    case 1:
        tiles.push_back(Tile(Vector(368, 268), tile64_img));
        break;
    case 2:
        tiles.push_back(Tile(Vector(368, 110), tile64_img));
        tiles.push_back(Tile(Vector(368, 269), tile64_img));
        tiles.push_back(Tile(Vector(368, 430), tile64_img));
        tiles.push_back(Tile(Vector(272, 205), tile32_img));
        tiles.push_back(Tile(Vector(495, 205), tile32_img));
        tiles.push_back(Tile(Vector(272, 364), tile32_img));
        tiles.push_back(Tile(Vector(495, 364), tile32_img));
        break;
    case 3:
        tiles.push_back(Tile(Vector(113, 109), tileVertical_img));
        tiles.push_back(Tile(Vector(304, 46), tile32_img));
        tiles.push_back(Tile(Vector(336, 173), tile64_img));
        tiles.push_back(Tile(Vector(208, 301), tile32_img));
        tiles.push_back(Tile(Vector(463, 78), tileHorizontal_img));
        tiles.push_back(Tile(Vector(463, 237), tileVertical_img));
        tiles.push_back(Tile(Vector(591, 300), tile64_img));
        tiles.push_back(Tile(Vector(272, 396), tile64_img));
        tiles.push_back(Tile(Vector(463, 396), tileVertical_img));
        tiles.push_back(Tile(Vector(272, 522), tile32_img));
        break;
    case 4:
        tiles.push_back(Tile(Vector(272, 14), tile64_img));
        tiles.push_back(Tile(Vector(208, 77), tileVertical_img));
        tiles.push_back(Tile(Vector(400, 172), tileHorizontal_img));
        tiles.push_back(Tile(Vector(623, 77), tileVertical_img));
        tiles.push_back(Tile(Vector(208, 205), tileHorizontal_img));
        tiles.push_back(Tile(Vector(591, 269), tile32_img));
        tiles.push_back(Tile(Vector(80, 269), tile64_img));
        tiles.push_back(Tile(Vector(208, 269), tileVertical_img));
        tiles.push_back(Tile(Vector(591, 332), tile64_img));
        tiles.push_back(Tile(Vector(272, 396), tileHorizontal_img));
        tiles.push_back(Tile(Vector(400, 364), tileHorizontal_img));
        tiles.push_back(Tile(Vector(145, 492), tile32_img));
        tiles.push_back(Tile(Vector(591, 460), tileHorizontal_img));
        break;
    case 5:
        //tiles.push_back(Tile(Vector(114, 14), tileVertical_img));
        tiles.push_back(Tile(Vector(241, 14), tileVertical_img));
        tiles.push_back(Tile(Vector(463, 46), tile32_img));
        tiles.push_back(Tile(Vector(592, 46), tile32_img));
        tiles.push_back(Tile(Vector(655, 109), tile64_img));
        tiles.push_back(Tile(Vector(495, 141), tile64_img));
        tiles.push_back(Tile(Vector(368, 173), tile32_img));
        tiles.push_back(Tile(Vector(241, 141), tileVertical_img));
        tiles.push_back(Tile(Vector(112, 141), tileVertical_img));
        tiles.push_back(Tile(Vector(241, 269), tileVertical_img));
        tiles.push_back(Tile(Vector(431, 269), tileHorizontal_img));
        tiles.push_back(Tile(Vector(655, 429), tile64_img));
        tiles.push_back(Tile(Vector(495, 332), tileVertical_img));
        tiles.push_back(Tile(Vector(304, 396), tileHorizontal_img));
        tiles.push_back(Tile(Vector(117, 396), tile64_img));
        tiles.push_back(Tile(Vector(21, 396), tile32_img));
        tiles.push_back(Tile(Vector(18, 522), tile64_img));
        tiles.push_back(Tile(Vector(117, 522), tile32_img));
        tiles.push_back(Tile(Vector(495, 460), tileVertical_img));
        break;
    }
    return tiles;
}

void Game::loadLevel(int level) {
    ball.setVelocity(0, 0);
    ball.setWin(false);

    tiles = loadTiles(level);

    switch (level) {
    case 1:
        ball.setPosition(176 - BALL_SIZE/2, SCREEN_HEIGHT/2 - BALL_SIZE/2);
        paint.setPosition(ball.getPosition().x, ball.getPosition().y);
        hole.setPosition(608, 284);
        break;
    case 2:
        ball.setPosition(176 - BALL_SIZE/2, SCREEN_HEIGHT/2 - BALL_SIZE/2);
        paint.setPosition(ball.getPosition().x, ball.getPosition().y);
        hole.setPosition(608, 284);
        break;
    case 3:
        ball.setPosition(101, 480);
        paint.setPosition(ball.getPosition().x, ball.getPosition().y);
        hole.setPosition(671, 93);
        break;
    case 4:
        ball.setPosition(101, 97);
        paint.setPosition(ball.getPosition().x, ball.getPosition().y);
        hole.setPosition(384, 284);
        break;
    case 5:
        ball.setPosition(674, 288);
        paint.setPosition(ball.getPosition().x, ball.getPosition().y);
        hole.setPosition(96, 284);
        break;
    }
}

void Game::renderGraphics() {
    graphics.prepareScene(background);

    SDL_Color BLACK_COLOR = {0, 0, 0, 255};
    strokesText = graphics.renderText(getStrokesCount(), KaphFont, BLACK_COLOR);
    graphics.renderTexture(strokesText, 20, 18);
    levelText = graphics.renderText(getLevelCount(), KaphFont, BLACK_COLOR);
    graphics.renderTexture(levelText, 20, 50);

    graphics.renderTexture(hole_img, hole.getPosition().x, hole.getPosition().y);

    graphics.renderTexture(paint_img, paint.getPosition().x - 4, paint.getPosition().y - 4);

    for (Tile t : tiles) {
        graphics.renderTexture(t.getTexture(), t.getPosition().x, t.getPosition().y);
    }

    graphics.renderTexture(ball_img, ball.getPosition().x, ball.getPosition().y);

    graphics.presentScene();
}

const char* Game::getStrokesCount() {
    std::string s = "STROKES: ";
    s += std::to_string(strokes);
    return s.c_str();
}

const char* Game::getLevelCount() {
    std::string s = "LEVEL: ";
    s += std::to_string(level);
    return s.c_str();
}

void Game::running() {
    frameTime = SDL_GetTicks() - frameStart;
    frameTime = frameStart;

    tiles = loadTiles(level);

    handleEvents();

    ball.update(mouseDown, mousePressed, hole, tiles, hit_sound, bounce_sound, strokes);

    renderGraphics();

    if (ball.getWinStatus() == true) {
        if (level <= 4) play(levelUp_sound);
        SDL_Delay(1000);
        level++;
        loadLevel(level);
    }

    static bool played = false;

    if (level > 5 && !played) {
        pauseMusic();
        play(finalWin_sound);
        played = true;
    }

    if (frameDelay > frameTime) {
        SDL_Delay(frameDelay - frameTime);
    }
}

void Game::freeMemory() {
    graphics.quit();
    quitMusic();
    quitFont();

    SDL_DestroyTexture(background);
    background = nullptr;
    SDL_DestroyTexture(ball_img);
    ball_img = nullptr;
    SDL_DestroyTexture(paint_img);
    paint_img = nullptr;
    SDL_DestroyTexture(hole_img);
    hole_img = nullptr;
    SDL_DestroyTexture(tile32_img);
    tile32_img = nullptr;
    SDL_DestroyTexture(tile64_img);
    tile64_img = nullptr;
    SDL_DestroyTexture(tileHorizontal_img);
    tileHorizontal_img = nullptr;
    SDL_DestroyTexture(tileVertical_img);
    tileVertical_img = nullptr;

    Mix_FreeMusic(bg_music);
    bg_music = nullptr;
    Mix_FreeChunk(hit_sound);
    hit_sound = nullptr;
    Mix_FreeChunk(bounce_sound);
    bounce_sound = nullptr;
    Mix_FreeChunk(levelUp_sound);
    levelUp_sound = nullptr;
    Mix_FreeChunk(finalWin_sound);
    finalWin_sound = nullptr;

    SDL_DestroyTexture(strokesText);
    strokesText = nullptr;
    TTF_CloseFont(KaphFont);
}
