#ifndef CAMERA_H
#define CAMERA_H

#include "math.h"

class Camera {
private:
    Vector3 pos;    // Posición de la cámara
    Vector3 forward; // Dirección hacia donde mira
    Vector3 up;     // Vector arriba
    float yaw;      // Rotación horizontal (radianes)
    float pitch;    // Rotación vertical (radianes)
    float speed;    // Velocidad de traslación

public:
    Camera(const Vector3& pos, const Vector3& target, const Vector3& up);
    void update();
    void moveForward(float delta);
    void moveRight(float delta);
    void moveUp(float delta);
    void rotate(float delta_yaw, float delta_pitch);
    Matrix4 getViewMatrix() const;
    Vector3 getPosition() const { return pos; }
};

#endif