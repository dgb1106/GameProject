#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "ball.h"

void Ball::update(Vector2D& position) {
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
