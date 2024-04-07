#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "ball.h"
#include "object.h"

void Ball::update(Vector& position) {
    const double friction = 0.98;
    const double velocityThreshold = 0.2;

    double absVelocityX = std::abs(velocity.x);
    double absVelocityY = std::abs(velocity.y);

    velocity.x *= friction;
    velocity.y *= friction;

    if (absVelocityX < velocityThreshold && absVelocityY < velocityThreshold) {
            velocity.x = 0;
            velocity.y = 0;
    }

    position.x += velocity.x;
    position.y += velocity.y;
}

void Ball::setVelocity(double _x, double _y) {
    velocity.x = _x;
    velocity.y = _y;
}

Vector Ball::getPosition() {
    return position;
}

void Ball::startMoving() {
    moving = true;
}

bool Ball::clicked(int mouseX, int mouseY) {
    return (mouseX >= position.x && mouseX <= position.x + ballSize && mouseY >= position.y && mouseY <= position.y + ballSize);
}
