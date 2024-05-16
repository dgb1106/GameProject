#ifndef _BALL__H
#define _BALL__H

#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"
#include "object.h"
#include "hole.h"
#include "tile.h"
#include "music.h"

class Ball : public Object
{
public:
    Ball();

    Ball(Vector _position, SDL_Texture* _texture);

    Vector getArrowPosition() {
        return arrow.getPosition();
    }

    Vector getVelocity() {
        return velocity;
    }

    Vector getInitialMousePosition() {
        return initialMousePosition;
    }

    Vector getFinalMousePosition() {
        return finalMousePosition;
    }

    double getAngle() {
        return angle;
    }

    void setVelocity(double _x, double _y);

    void setInitialMousePosition(double _x, double _y);

    void setFinalMousePosition(double _x, double _y);

    void update(bool mouseDown, bool mousePressed, Hole hole, std::vector <Tile> tiles, std::vector <Tile> cactus, std::vector <Tile> slime, std::vector <Tile> movingTiles, std::vector <Sprite>& boxes, bool& extraTime, Mix_Chunk* hit, Mix_Chunk* bounce, int& strokes);

    void checkCollision(std::vector <Tile> tiles, std::vector <Tile> cactus, std::vector <Tile> slime, std::vector <Tile> movingTiles, std::vector <Sprite>& boxes, bool& extraTime, Mix_Chunk* bounce);

    bool checkWin(Hole hole);

    void setWin(bool _win) {
        win = _win;
    }

    bool getWinStatus() {
        return win;
    }

    void setGameOverStatus(bool _status) {
        gameOver = _status;
    }

    bool getGameOverStatus() {
        return gameOver;
    }

private:
    Vector velocity;

    double velocity1D;

    Vector initialMousePosition;
    Vector finalMousePosition;

    double angle = 0;

    Object arrow;

    bool moving = true;

    int directionX = 1;
    int directionY = 1;

    bool win = false;
    bool gameOver = false;
};
#endif // _BALL__H
