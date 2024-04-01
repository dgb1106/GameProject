#ifndef _OBJECT__H
#define _OBJECT__H

struct Vector2D
{
    double x;
    double y;

    Vector2D() {
        x = 0;
        y = 0;
    }

    Vector2D(double _x, double _y) {
        x = _x;
        y = _y;
    }
};
#endif // _OBJECT__H
