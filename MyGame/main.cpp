#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "defs.h"
#include "graphics.h"
#include "object.h"
#include "ball.h"

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

Vector samplePosition(180 - BALL_SIZE/2, SCREEN_HEIGHT/2 - BALL_SIZE/2);
Ball ball(samplePosition);

bool quit = false;
bool mouseDown = false;
bool mousePressed = false;

void initializeGraphics() {
    graphics.init();
    background = graphics.loadTexture(BACKGROUND_IMG);
    ball_img = graphics.loadTexture(BALL_IMG);
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

        ball.update(mouseDown, mousePressed);

        graphics.prepareScene(background);
        graphics.renderTexture(ball_img, ball.getPosition().x, ball.getPosition().y);
        graphics.presentScene();
    }

    graphics.quit();

    return 0;
}
