#ifndef _LOGIC__H
#define _LOGIC__H

#define BOARD_SIZE 3
#define EMPTY_CELL ' '
#define X_CELL 'x'
#define O_CELL 'o'

struct TicTacToe
{
    char board[BOARD_SIZE][BOARD_SIZE];
    char nextMove = X_CELL;

    void init() {
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                board[i][j] = EMPTY_CELL;
            }
        }
    }

    void move(int row, int col) {
        if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE) {
            board[row][col] = nextMove;
            nextMove = (nextMove == X_CELL) ? O_CELL : X_CELL;
        }
    }

};
#endif // _LOGIC__H
