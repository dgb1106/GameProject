#include "object.h"

Object::Object() {
    setPosition(0, 0);
    //texture = nullptr;
}

Object::Object(Vector _position, SDL_Texture* _texture) : position(_position), texture(_texture) {}

void Object::setPosition(double _x, double _y) {
    position.x = _x;
    position.y = _y;
}

void Object::setTexture(SDL_Texture* _texture) {
    texture = _texture;
}

double getDistance(Vector a, Vector b) {
    return (sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2)));
}
