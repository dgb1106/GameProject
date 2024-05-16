#include <iostream>
#include <ctime>
#include <cstdlib>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "game.h"

void Game::initializeGraphics() {
    graphics.init();

    menu = graphics.loadTexture(MENU_IMG);
    background = graphics.loadTexture(BACKGROUND_IMG);
    guide = graphics.loadTexture(GUIDE_IMG);
    completed = graphics.loadTexture(COMPLETE_IMG);
    gameOver = graphics.loadTexture(GAMEOVER_IMG);
    endBackground = graphics.loadTexture(ENDBACKGROUND_IMG);
    endScrollingBackground.setTexture(endBackground);

    backButton_White = graphics.loadTexture(BACKBUTTON_WHITE);
    backButton_Gold = graphics.loadTexture(BACKBUTTON_GOLD);
    SoundButton_On = graphics.loadTexture(SOUNDBUTTON_ON);
    SoundButton_Off = graphics.loadTexture(SOUNDBUTTON_OFF);

    ball_img = graphics.loadTexture(BALL_IMG);
    paint_img = graphics.loadTexture(PAINT_IMG);
    hole_img = graphics.loadTexture(HOLE_IMG);
    arrow_img = graphics.loadTexture(ARROW_IMG);
    tile64_img = graphics.loadTexture(TILE64_IMG);
    tile32_img = graphics.loadTexture(TILE32_IMG);
    tileHorizontal_img = graphics.loadTexture(TILEHORIZONTAL_IMG);
    tileVertical_img = graphics.loadTexture(TILEVERTICAL_IMG);
    cactus_img = graphics.loadTexture(CACTUS_IMG);
    slime_img = graphics.loadTexture(SLIME_IMG);
    box_img = graphics.loadTexture(BOX_IMG);

    icon = IMG_Load(CURSOR_IMG);
    cursor = SDL_CreateColorCursor(icon, 18, 100);
    SDL_SetCursor(cursor);
}

void Game::initializeMusic() {
    initMusic();
    bg_music = loadMusic(BG_MUSIC);
    hit_sound = loadSound(HIT_SOUND);
    bounce_sound = loadSound(BOUNCE_SOUND);
    levelUp_sound = loadSound(LEVELUP_SOUND);
    finalWin_sound = loadSound(FINALWIN_SOUND);
    gameOver_sound = loadSound(GAMEOVER_SOUND);
}

void Game::initializeFont() {
    initFont();

    KaphFont24 = loadFont(FONT_KAPH, STROKES_TEXT_SIZE);
    KaphFont36 = loadFont(FONT_KAPH, PLAY_TEXT_SIZE);
    CrocanteFont = loadFont(FONT_CROCANTE, STROKES_TEXT_SIZE);
    WigglyeFont = loadFont(FONT_WIGGLYE, TITLE_TEXT_SIZE);
}

void Game::init() {
    initializeGraphics();
    initializeMusic();
    initializeFont();

    ball.setTexture(ball_img);
    paint.setTexture(paint_img);
    hole.setTexture(hole_img);
}

void Game::handleEvents(bool& playedAgain, bool& quit) {
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
            switch (status) {
            case MENU_STATUS:
                if (mouseX >= 99 && mouseX <= 230 && mouseY >= 420 && mouseY <= 474) {
                    status = GUIDE_STATUS;
                }
                if (mouseX >= 296 && mouseX <= 493 && mouseY >= 404 && mouseY <= 490) {
                    status = PLAYING_STATUS;
                    startTime = SDL_GetTicks();
                }
                if (mouseX >= 577 && mouseX <= 709 && mouseY >= 420 && mouseY <= 474) {
                    quit = true;
                }
                if (mouseX >= 32 && mouseX <= 64 && mouseY >= 32 && mouseY <= 64) {
                    soundOn = !soundOn;
                }
                break;
            case PLAYING_STATUS:
                if (mouseX >= 605 && mouseX <= 637 && mouseY >= 20 && mouseY <= 52) {
                    soundOn = !soundOn;
                }
                break;
            case GUIDE_STATUS:
                if (mouseX >= 84 && mouseX <= 116 && mouseY >= 70 && mouseY <= 102) {
                    status = MENU_STATUS;
                }
                break;
            case GAMEOVER_STATUS:
                if (mouseX >= 159 && mouseX <= 352 && mouseY >= 401 && mouseY <= 455) {
                    playedAgain = true;
                    startTime = SDL_GetTicks();
                }
                if (mouseX >= 445 && mouseX <= 638 && mouseY >= 401 && mouseY <= 455) {
                    quit = true;
                }
                break;
            case COMPLETED_STATUS:
                if (mouseX >= 159 && mouseX <= 352 && mouseY >= 401 && mouseY <= 455) {
                    playedAgain = true;
                    startTime = SDL_GetTicks();
                }
                if (mouseX >= 445 && mouseX <= 638 && mouseY >= 401 && mouseY <= 455) {
                    quit = true;
                }
                break;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            mouseDown = false;
            break;
        }
    }
}

std::vector <Tile> Game::loadTiles(std::vector <Tile>& tiles, int level) {
    tiles.clear();
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
        //tiles.push_back(Tile(Vector(400, 172), tileHorizontal_img));
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
        //tiles.push_back(Tile(Vector(368, 173), tile32_img));
        tiles.push_back(Tile(Vector(241, 141), tileVertical_img));
        //tiles.push_back(Tile(Vector(112, 141), tileVertical_img));
        tiles.push_back(Tile(Vector(241, 269), tileVertical_img));
        //tiles.push_back(Tile(Vector(431, 269), tileHorizontal_img));
        tiles.push_back(Tile(Vector(655, 429), tile64_img));
        tiles.push_back(Tile(Vector(495, 332), tileVertical_img));
        tiles.push_back(Tile(Vector(304, 396), tileHorizontal_img));
        tiles.push_back(Tile(Vector(112, 396), tile64_img));
        tiles.push_back(Tile(Vector(176, 396), tileHorizontal_img));
        tiles.push_back(Tile(Vector(18, 396), tile32_img));
        tiles.push_back(Tile(Vector(18, 522), tile64_img));
        tiles.push_back(Tile(Vector(112, 522), tile32_img));
        tiles.push_back(Tile(Vector(495, 460), tileVertical_img));
        break;
    }
    return tiles;
}

std::vector <Tile> Game::loadCactus(std::vector <Tile>& cactus, int level) {
    cactus.clear();

    switch (level) {
    case 4:
        cactus.push_back(Tile(Vector(81, 396), cactus_img));
        cactus.push_back(Tile(Vector(464, 172), cactus_img));
        break;
    case 5:
        cactus.push_back(Tile(Vector(112, 173), cactus_img));
        cactus.push_back(Tile(Vector(337, 142), cactus_img));
        cactus.push_back(Tile(Vector(432, 523), cactus_img));
        break;
    }

    return cactus;
}

std::vector <Tile> Game::loadSlime(std::vector <Tile>& slime, int level) {
    slime.clear();

    switch (level) {
    case 2:
        slime.push_back(Tile(Vector(273, 46), slime_img));
        slime.push_back(Tile(Vector(464, 46), slime_img));
        slime.push_back(Tile(Vector(273, 493), slime_img));
        slime.push_back(Tile(Vector(464, 493), slime_img));
        break;
    case 3:
        slime.push_back(Tile(Vector(209, 333), slime_img));
        slime.push_back(Tile(Vector(400, 174), slime_img));
        slime.push_back(Tile(Vector(400, 14), slime_img));
        slime.push_back(Tile(Vector(464, 523), slime_img));
        break;
    case 4:
        slime.push_back(Tile(Vector(528, 397), slime_img));
        break;
    case 5:
        slime.push_back(Tile(Vector(496, 206), slime_img));
        slime.push_back(Tile(Vector(432, 397), slime_img));
        slime.push_back(Tile(Vector(82, 458), slime_img));
        break;
    }

    return slime;
}

std::vector <Tile> Game::loadMovingTiles(std::vector <Tile>& movingTiles, int level) {
    movingTiles.clear();
    if (level == 5) {
        movingTiles.push_back(Tile(Vector(432, 268), tileHorizontal_img));
    }
    return movingTiles;
}

std::vector <Sprite> Game::loadBoxes(std::vector <Sprite>& boxes) {
    boxes.clear();
    srand(time(NULL));
    boxes.push_back(Sprite(box_img, Vector(rand() % (SCREEN_WIDTH - 17 - 30) + 17, rand() % (SCREEN_HEIGHT - 13 - 30) + 13)));
    boxes.push_back(Sprite(box_img, Vector(rand() % (SCREEN_WIDTH - 17 - 30) + 17, rand() % (SCREEN_HEIGHT - 13 - 30) + 13)));
    boxes.push_back(Sprite(box_img, Vector(rand() % (SCREEN_WIDTH - 17 - 30) + 17, rand() % (SCREEN_HEIGHT - 13 - 30) + 13)));
    return boxes;
}

void Game::loadLevel(int level) {
    ball.setVelocity(0, 0);
    ball.setWin(false);

    tiles = loadTiles(tiles, level);
    cactus = loadCactus(cactus, level);
    slime = loadSlime(slime, level);
    movingTiles = loadMovingTiles(movingTiles, level);
    boxes = loadBoxes(boxes);

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
    if (status == MENU_STATUS) {
        graphics.prepareScene(menu);

        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        SDL_Color color1 = WHITE_COLOR;
        if (mouseX >= 296 && mouseX <= 493 && mouseY >= 404 && mouseY <= 490) {
            color1 = GOLD_COLOR;
        }
        playText = graphics.renderText("Play!", KaphFont36, color1);
        graphics.renderTexture(playText, 332, 428);
        SDL_DestroyTexture(playText);

        SDL_Color color2 = WHITE_COLOR;
        if (mouseX >= 99 && mouseX <= 230 && mouseY >= 420 && mouseY <= 474) {
            color2 = GOLD_COLOR;
        }
        guideText = graphics.renderText("Guide", KaphFont24, color2);
        graphics.renderTexture(guideText, 120, 434);
        SDL_DestroyTexture(guideText);

        SDL_Color color3 = WHITE_COLOR;
        if (mouseX >= 577 && mouseX <= 709 && mouseY >= 420 && mouseY <= 474) {
            color3 = GOLD_COLOR;
        }
        exitText = graphics.renderText("Exit", KaphFont24, color3);
        graphics.renderTexture(exitText, 612, 434);
        SDL_DestroyTexture(exitText);

        if (soundOn) {
            graphics.renderTexture(SoundButton_On, 32, 32);
            resumeAll();
        } else {
            graphics.renderTexture(SoundButton_Off, 32, 32);
            pauseAll();
        }

        graphics.presentScene();
    }

    if (status == GUIDE_STATUS) {
        graphics.prepareScene(guide);

        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        if (mouseX >= 84 && mouseX <= 116 && mouseY >= 70 && mouseY <= 102) {
            graphics.renderTexture(backButton_Gold, 84, 70);
        } else {
            graphics.renderTexture(backButton_White, 84, 70);
        }

        graphics.presentScene();
    }

    if (status == PLAYING_STATUS) {
        static int countTicks = 0;
        countTicks++;
        if (countTicks == 4) {
            for (Sprite& s : boxes) {
                s.tick();
            }
            countTicks = 0;
        }

        graphics.prepareScene(background);

        if (soundOn) {
            graphics.renderTexture(SoundButton_On, 605, 20);
            Mix_PauseAudio(0);
        } else {
            graphics.renderTexture(SoundButton_Off, 605, 20);
            Mix_PauseAudio(1);
        }

        for (Tile s : slime) {
            graphics.renderTexture(s.getTexture(), s.getPosition().x, s.getPosition().y);
        }

        for (Sprite s : boxes) {
            graphics.render(s.position.x, s.position.y, s);
        }

        strokesText = graphics.renderText(getStrokesCount(), CrocanteFont, WHITE_COLOR);
        graphics.renderTexture(strokesText, 30, 27);
        SDL_DestroyTexture(strokesText);

        levelText = graphics.renderText(getLevelCount(), CrocanteFont, WHITE_COLOR);
        graphics.renderTexture(levelText, 30, 58);
        SDL_DestroyTexture(levelText);

        playingTimeText = graphics.renderText(getTimeText(playingTime), CrocanteFont, WHITE_COLOR);
        graphics.renderTexture(playingTimeText, 655, 27);
        SDL_DestroyTexture(playingTimeText);

        graphics.renderTexture(hole_img, hole.getPosition().x, hole.getPosition().y);

        graphics.renderTexture(paint_img, paint.getPosition().x - 4, paint.getPosition().y - 4);

        if (level == 5) {
            for (Tile m : movingTiles) {
                m.moving();
                graphics.renderTexture(tileHorizontal_img, m.getPosition().x, m.getPosition().y);
            }
        }

        for (Tile t : tiles) {
            graphics.renderTexture(t.getTexture(), t.getPosition().x, t.getPosition().y);
        }

        for (Tile c : cactus) {
            graphics.renderTexture(c.getTexture(), c.getPosition().x, c.getPosition().y);
        }

        graphics.renderTexture(arrow_img, ball.getArrowPosition().x, ball.getArrowPosition().y, ball.getAngle());

        graphics.renderTexture(ball_img, ball.getPosition().x, ball.getPosition().y);

        graphics.presentScene();
    }

    if (status == GAMEOVER_STATUS) {
        graphics.prepareScene();

        endScrollingBackground.scroll(1);
        graphics.render(endScrollingBackground);

        graphics.renderTexture(gameOver, 0, 0);

        SDL_Texture* lastestLevelText = graphics.renderText(getLastestLevelCount(), CrocanteFont, GOLD_COLOR);
        graphics.renderTexture(lastestLevelText, 300, 280);
        SDL_DestroyTexture(lastestLevelText);

        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        SDL_Color color1 = WHITE_COLOR;
        if (mouseX >= 159 && mouseX <= 352 && mouseY >= 401 && mouseY <= 455) {
            color1 = BRIGHT_PINK_COLOR;
        }
        playAgainText = graphics.renderText("Play Again!", KaphFont24, color1);
        graphics.renderTexture(playAgainText, 162, 414);
        SDL_DestroyTexture(playAgainText);

        SDL_Color color2 = WHITE_COLOR;
        if (mouseX >= 445 && mouseX <= 638 && mouseY >= 401 && mouseY <= 455) {
            color2 = BRIGHT_PINK_COLOR;
        }
        exitText = graphics.renderText("Exit", KaphFont24, color2);
        graphics.renderTexture(exitText, 510, 414);
        SDL_DestroyTexture(exitText);

        graphics.presentScene();
    }

    if (status == COMPLETED_STATUS) {
        graphics.prepareScene();

        endScrollingBackground.scroll(1);
        graphics.render(endScrollingBackground);

        graphics.renderTexture(completed, 0, 0);

        lowestStrokesText = graphics.renderText(getLowestStrokes(), CrocanteFont, GOLD_COLOR);
        graphics.renderTexture(lowestStrokesText, 275, 280);
        SDL_DestroyTexture(lowestStrokesText);

        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        SDL_Color color1 = WHITE_COLOR;
        if (mouseX >= 159 && mouseX <= 352 && mouseY >= 401 && mouseY <= 455) {
            color1 = BRIGHT_PINK_COLOR;
        }
        playAgainText = graphics.renderText("Play Again!", KaphFont24, color1);
        graphics.renderTexture(playAgainText, 162, 414);
        SDL_DestroyTexture(playAgainText);

        SDL_Color color2 = WHITE_COLOR;
        if (mouseX >= 445 && mouseX <= 638 && mouseY >= 401 && mouseY <= 455) {
            color2 = BRIGHT_PINK_COLOR;
        }
        exitText = graphics.renderText("Exit", KaphFont24, color2);
        graphics.renderTexture(exitText, 510, 414);
        SDL_DestroyTexture(exitText);

        graphics.presentScene();
    }
}

const char* Game::getStrokesCount() {
    std::string s = "STROKES: ";
    s += std::to_string(strokes);
    return s.c_str();
}

const char* Game::getLowestStrokes() {
    std::string s = "LOWEST STROKES: ";
    if (lowestStrokes < strokes) {
        s += std::to_string(lowestStrokes);
    } else {
        s += std::to_string(strokes);
    }
    return s.c_str();
}

const char* Game::getLevelCount() {
    std::string s = "LEVEL: ";
    s += std::to_string(level);
    return s.c_str();
}

const char* Game::getLastestLevelCount() {
    std::string s = "LASTEST LEVEL: ";
    s += std::to_string(level);
    return s.c_str();
}

void Game::playAgain(bool& playedAgain, bool& musicPlayed) {
    status = PLAYING_STATUS;
    level = 1;
    loadLevel(level);
    strokes = 0;
    ball.setWin(false);
    ball.setGameOverStatus(false);
    musicPlayed = false;
    playedAgain = false;
}

void Game::running(bool& quit) {
    frameStart = SDL_GetTicks();

    static bool playedAgain = false;
    static bool musicPlayed = false;
    static bool extraTime = false;

    handleEvents(playedAgain, quit);

    ball.update(mouseDown, mousePressed, hole, tiles, cactus, slime, movingTiles, boxes, extraTime, hit_sound, bounce_sound, strokes);

    if (status == PLAYING_STATUS) {
        playingTime = getTime(startTime, ball.getWinStatus(), ball.getGameOverStatus(), extraTime, level);
        if (playingTime == 0) {
            ball.setGameOverStatus(true);
        }
    }

    renderGraphics();

    if (playedAgain) playAgain(playedAgain, musicPlayed);

    if (ball.getGameOverStatus() == true && !musicPlayed) {
        status = GAMEOVER_STATUS;
        strokes = lowestStrokes;
        pauseMusic();
        play(gameOver_sound);
        musicPlayed = true;
    }

    if (ball.getWinStatus() == true && level <= 5) {
        if (level <= 4) play(levelUp_sound);
        SDL_Delay(1000);
        level++;
        loadLevel(level);
    }

    if (level > 5 && !musicPlayed) {
        status = COMPLETED_STATUS;
        pauseMusic();
        play(finalWin_sound);
        musicPlayed = true;
    }

    if (level <= 5 && ball.getGameOverStatus() == false) {
        resumeMusic();
    }

    /*frameTime = SDL_GetTicks() - frameStart;
    if (frameDelay > frameTime) {
        SDL_Delay(frameDelay - frameTime);
    }*/
}

void Game::freeMemory() {
    graphics.quit();
    quitMusic();
    quitFont();

    SDL_DestroyTexture(background);
    background = nullptr;
    SDL_DestroyTexture(menu);
    menu = nullptr;
    SDL_DestroyTexture(guide);
    guide = nullptr;
    SDL_DestroyTexture(backButton_Gold);
    backButton_Gold = nullptr;
    SDL_DestroyTexture(backButton_White);
    backButton_White = nullptr;
    SDL_DestroyTexture(SoundButton_On);
    SoundButton_On = nullptr;
    SDL_DestroyTexture(SoundButton_Off);
    SoundButton_Off = nullptr;
    SDL_DestroyTexture(completed);
    completed = nullptr;
    SDL_DestroyTexture(gameOver);
    gameOver = nullptr;
    SDL_DestroyTexture(endBackground);
    endBackground = nullptr;
    SDL_DestroyTexture(ball_img);
    ball_img = nullptr;
    SDL_DestroyTexture(paint_img);
    paint_img = nullptr;
    SDL_DestroyTexture(hole_img);
    hole_img = nullptr;
    SDL_DestroyTexture(arrow_img);
    arrow_img = nullptr;
    SDL_DestroyTexture(tile32_img);
    tile32_img = nullptr;
    SDL_DestroyTexture(tile64_img);
    tile64_img = nullptr;
    SDL_DestroyTexture(tileHorizontal_img);
    tileHorizontal_img = nullptr;
    SDL_DestroyTexture(tileVertical_img);
    tileVertical_img = nullptr;
    SDL_DestroyTexture(slime_img);
    slime_img = nullptr;
    SDL_DestroyTexture(cactus_img);
    cactus_img = nullptr;
    SDL_DestroyTexture(box_img);
    box_img = nullptr;

    SDL_FreeSurface(icon);
    icon = nullptr;
    SDL_FreeCursor(cursor);
    cursor = nullptr;

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
    SDL_DestroyTexture(levelText);
    levelText = nullptr;
    SDL_DestroyTexture(lowestStrokesText);
    lowestStrokesText = nullptr;
    SDL_DestroyTexture(playText);
    playText = nullptr;
    SDL_DestroyTexture(exitText);
    exitText = nullptr;
    SDL_DestroyTexture(guideText);
    guideText = nullptr;
    SDL_DestroyTexture(playAgainText);
    playAgainText = nullptr;
    TTF_CloseFont(KaphFont24);
    TTF_CloseFont(KaphFont36);
    TTF_CloseFont(CrocanteFont);
    TTF_CloseFont(WigglyeFont);
}
