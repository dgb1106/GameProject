#include "object.h"

//Object::Object() : position({0, 0}) {}

Object::Object(Vector _position, SDL_Texture* _texture) : position(_position), texture(_texture) {}

void Object::setPosition(double _x, double _y) {
    position.x = _x;
    position.y = _y;
}

void Object::setAngle(double _angle) {
    angle = _angle;
}

