#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"
#include "graphics.h"
#include "logic.h"

using namespace std;

void processClick(int x, int y, TicTacToe& game)
{
    int clickedCol = (x - BOARD_X) / CELL_SIZE;
    int clickedRow = (y - BOARD_Y) / CELL_SIZE;
    game.move(clickedRow, clickedCol);
}

int main(int argc, char* argv[])
{
    Graphics graphics;
    graphics.init();

    TicTacToe game;
    game.init();
    graphics.render(game);

    int x, y;
    SDL_Event event;
    bool quit = false;

    while (!quit) {
        SDL_PollEvent(&event);
        switch (event.type) {
        case SDL_QUIT:
            quit = true;
            break;
        case SDL_MOUSEBUTTONDOWN:
            SDL_GetMouseState(&x, &y);
            cerr << "Mouse at: (" << x << "," << y << ")" << endl;
            processClick(x, y, game);
            graphics.render(game);
            break;
        }
        SDL_Delay(100);
    }

    graphics.quit();

    return 0;
}
