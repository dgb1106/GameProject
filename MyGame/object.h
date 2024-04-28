#ifndef _OBJECT__H
#define _OBJECT__H

#include <iostream>
#include <cmath>
#include <SDL.h>
#include <SDL_image.h>

#include "defs.h"

struct Vector
{
    double x;
    double y;

    Vector() {
        x = 0;
        y = 0;
    }

    Vector(double _x, double _y) {
        x = _x;
        y = _y;
    }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
        }
        return *this;
    }
};

double getDistance(Vector a, Vector b);

class Object
{
public:
    Object();

    Object(Vector _position, SDL_Texture* _texture);

    Vector getPosition() {
        return position;
    }

    SDL_Texture* getTexture() {
        return texture;
    }

    void setPosition(double _x, double _y);

    void setTexture(SDL_Texture* _texture);

private:
    Vector position;
    SDL_Texture* texture;
};
#endif // _OBJECT__H
