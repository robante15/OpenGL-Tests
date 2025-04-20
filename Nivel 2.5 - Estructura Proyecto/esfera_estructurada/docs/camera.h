#ifndef CAMERA_H
#define CAMERA_H
#include "math_utils.h"

class Camera {
private:
    Vec3 position;
    Vec3 forward;
    Vec3 up;
    Vec3 right;
    float fov;
    float aspect;
    float near;
    float far;
    float yaw;
    float pitch;

public:
    Camera(const Vec3& pos = Vec3(3.0f, 3.0f, 14.0f), float fov = 60.0f,
           float aspect = 4.0f / 3.0f, float near = 1.0f, float far = 100.0f);
    void updateOrientation();
    void moveForward(float distance);
    void moveRight(float distance);
    void moveUp(float distance);
    void rotateYaw(float angle);
    void rotatePitch(float angle);
    void setAspect(float aspect);
    void applyView();
    void applyProjection();
};

#endif