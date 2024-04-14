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

class Object
{
public:
    Object();

    Object(Vector _position);

    Vector getPosition() {
        return position;
    }

    double getAngle() {
        return angle;
    }

    void setPosition(double _x, double _y);

    void setAngle(double _angle);

private:
    Vector position;
    double angle = 0;
};
#endif // _OBJECT__H
