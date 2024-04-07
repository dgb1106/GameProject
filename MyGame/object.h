#ifndef _OBJECT__H
#define _OBJECT__H

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
#endif // _OBJECT__H
