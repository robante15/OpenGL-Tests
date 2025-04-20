#include "camera.h"
#include <cmath>

Camera::Camera(const Vector3 &pos, const Vector3 &target, const Vector3 &up)
    : pos(pos), up(up.normalized()), speed(0.1f), yaw(0.0f), pitch(0.0f)
{
    forward = (target - pos).normalized();
    // Inicializar yaw y pitch basados en forward
    yaw = std::atan2(forward.x, forward.z);
    pitch = std::asin(-forward.y);
}

void Camera::update()
{
    // Actualizar forward basado en yaw y pitch
    forward.x = std::cos(pitch) * std::sin(yaw);
    forward.y = -std::sin(pitch);
    forward.z = std::cos(pitch) * std::cos(yaw);
    forward = forward.normalized();
    // Recalcular up para mantener ortogonalidad
    Vector3 right = forward.cross(Vector3(0.0f, 1.0f, 0.0f)).normalized();
    up = right.cross(forward).normalized();
}

void Camera::moveForward(float delta)
{
    pos = pos + forward * (delta * speed);
    if (pos.z < 6.0f)
        pos.z = 6.0f; // Evitar atravesar el cubo
}

void Camera::moveRight(float delta)
{
    Vector3 right = forward.cross(up).normalized();
    pos = pos + right * (delta * speed);
}

void Camera::moveUp(float delta)
{
    pos = pos + up * (delta * speed);
}

void Camera::rotate(float delta_yaw, float delta_pitch)
{
    yaw += delta_yaw;
    pitch += delta_pitch;
    // Limitar pitch para evitar giros completos
    if (pitch > 1.57f)
        pitch = 1.57f;
    if (pitch < -1.57f)
        pitch = -1.57f;
    update();
}

Matrix4 Camera::getViewMatrix() const
{
    return Matrix4::lookAt(pos, pos + forward, up);
}