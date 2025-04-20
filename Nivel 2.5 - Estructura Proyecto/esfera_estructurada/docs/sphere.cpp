#ifndef SPHERE_H
#define SPHERE_H

class TSphere {
private:
    float maxpos;
    float pos[3];
    float dir[3];
    float original_dir[3];
    float speed;
    float original_speed;
    float color[3];

public:
    TSphere(float maxpos, float speed);
    void test();
    void modifySpeed(float inc);
    void restoreSpeed(float new_speed = -1.0f);
    float *getPosv