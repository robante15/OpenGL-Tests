#ifndef SPHERE_H
#define SPHERE_H

#include "math.h"

class TSphere {
private:
    float maxpos;
    Vector3 pos;
    Vector3 dir;
    Vector3 original_dir;
    float speed;
    float original_speed;
    Vector3 color;

public:
    TSphere(float maxpos, float speed);
    void test();
    void modifySpeed(float inc);
    void restoreSpeed(float new_speed = -1.0f);
    Vector3 getPos() const { return pos; }
    Vector3 getColor() const { return color; }
    float getSpeed() const { return speed; }
};

#endif