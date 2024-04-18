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
SDL_Texture* tile64_img;
SDL_Texture* hole_img;

Vector samplePosition(176 - BALL_SIZE/2, SCREEN_HEIGHT/2 - BALL_SIZE/2);
Ball ball(samplePosition, ball_img);
Vector sampleHole(608, 284);
Hole hole(sampleHole, hole_img);

bool quit = false;
bool mouseDown = false;
bool mousePressed = false;

vector <Tile> loadTiles() {
    vector <Tile> result;

    result.push_back(Tile(Vector(368, 289), tile64_img));

    return result;
}

vector <Tile> tiles = loadTiles();

void initializeGraphics() {
    graphics.init();
    background = graphics.loadTexture(BACKGROUND_IMG);
    ball_img = graphics.loadTexture(BALL_IMG);
    tile64_img = graphics.loadTexture(TILE64_IMG);
    hole_img = graphics.loadTexture(HOLE_IMG);
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

int main(int argc, char* argv[])
{
    initializeGraphics();

    while (!quit) {
        handleEvents();

        ball.update(mouseDown, mousePressed, hole);

        graphics.prepareScene(background);
        graphics.renderTexture(hole_img, 608, 284);
        graphics.renderTexture(ball_img, ball.getPosition().x, ball.getPosition().y);
        graphics.presentScene();
    }

    graphics.quit();

    return 0;
}
