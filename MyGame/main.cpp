#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>

#include "defs.h"
#include "graphics.h"
#include "object.h"
#include "ball.h"
#include "hole.h"
#include "tile.h"

using namespace std;

void waitUntilKeyPressed() {
    SDL_Event e;
    while (true) {
        if (SDL_PollEvent(&e) != 0 && (e.type == SDL_KEYDOWN || e.type == SDL_QUIT))
            return;
        SDL_Delay(100);
    }
}

Graphics graphics;
SDL_Texture* background;
SDL_Texture* ball_img;
SDL_Texture* paint_img;
SDL_Texture* hole_img;
SDL_Texture* tile64_img;
SDL_Texture* tile32_img;
SDL_Texture* tileHorizontal_img;
SDL_Texture* tileVertical_img;

Vector samplePosition(176 - BALL_SIZE/2, SCREEN_HEIGHT/2 - BALL_SIZE/2);
Ball ball(samplePosition, ball_img);

Object paint(samplePosition, paint_img);

Vector sampleHole(608, 284);
Hole hole(sampleHole, hole_img);

vector <Tile> tiles;

int level = 1;

bool quit = false;
bool mouseDown = false;
bool mousePressed = false;

void initializeGraphics() {
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

void handleEvents() {
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
            if (mouseX >= ball.getPosition().x && mouseX <= ball.getPosition().x + BALL_SIZE && mouseY >= ball.getPosition().y && mouseY <= ball.getPosition().y + BALL_SIZE) {
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

vector <Tile> loadTiles(int level) {
    vector <Tile> tiles;
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
        tiles.push_back(Tile(Vector(114, 14), tileVertical_img));
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

void loadLevel(int level) {
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

int main(int argc, char* argv[])
{
    initializeGraphics();

    while (!quit) {
        tiles = loadTiles(level);

        handleEvents();

        ball.update(mouseDown, mousePressed, hole, tiles);

        if (ball.getWinStatus() == true) {
            SDL_Delay(500);
            level++;
            loadLevel(level);
        }

        graphics.prepareScene(background);
        graphics.renderTexture(hole_img, hole.getPosition().x, hole.getPosition().y);
        graphics.renderTexture(paint_img, paint.getPosition().x - 4, paint.getPosition().y - 4);
        for (Tile t : tiles) {
            graphics.renderTexture(t.getTexture(), t.getPosition().x, t.getPosition().y);
        }
        graphics.renderTexture(ball_img, ball.getPosition().x, ball.getPosition().y);
        graphics.presentScene();
    }

    graphics.quit();

    return 0;
}
