#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"
#include "graphics.h"

using namespace std;

void waitUntilKeyPressed() {
    SDL_Event e;
    while (true) {
        if (SDL_PollEvent(&e) != 0 && (e.type == SDL_KEYDOWN || e.type == SDL_QUIT))
            return;
        SDL_Delay(100);
    }
}

int main(int argc, char* argv[]) {
    Graphics graphics;
    graphics.init();

    SDL_Texture* background = graphics.loadTexture("bikiniBottom.jpg");
    graphics.prepareScene(background);

    graphics.presentScene();
    waitUntilKeyPressed();

    SDL_Texture* SpongeBob = graphics.loadTexture("Spongebob.png");
    graphics.renderTexture(SpongeBob, 200, 200);

    graphics.presentScene();
    waitUntilKeyPressed();

    SDL_DestroyTexture(SpongeBob);
    SpongeBob = NULL;
    SDL_DestroyTexture(background);
    background = NULL;

    graphics.quit();
    return 0;
}
