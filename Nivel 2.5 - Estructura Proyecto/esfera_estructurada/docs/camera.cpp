#include "camera.h"
#include <GL/glut.h>
#include <GL/glu.h>
#include <cmath>

Camera::Camera(const Vec3& pos, float fov, float aspect, float near, float far)
    : position(pos), fov(fov), aspect(aspect), near(near), far(far),
      yaw(-45.0f), pitch(-20.0f) {
    forward = Vec3(0.0f, 0.0f, -1.0f);
    up = Vec3(0.0f, 1.0f, 0.0f);
    right = Vec3(1.0f, 0.0f, 0.0f);
    updateOrientation();
}

void Camera::updateOrientation() {
    float rad_yaw = yaw * M_PI / 180.0f;
    float rad_pitch = pitch * M_PI / 180.0f;
    forward.x = std::cos(rad_pitch) * std::sin(rad_yaw);
    forward.y = std::sin(rad_pitch);
    forward.z = std::cos(rad_pitch) * std::cos(rad_yaw);
    forward = forward.normalized();
    right = forward.cross(Vec3(0.0f, 1.0f, 0.0f)).normalized();
    up = right.cross(forward).normalized();
}

void Camera::moveForward(float distance) {
    position = position + forward * distance;
}

void Camera::moveRight(float distance) {
    position = position + right * distance;
}

void Camera::moveUp(float distance) {
    position = position + up * distance;
}

void Camera::rotateYaw(float angle) {
    yaw += angle;
    updateOrientation();
}

void Camera::rotatePitch(float angle) {
    pitch = std::max(-89.0f, std::min(89.0f, pitch + angle));
    updateOrientation();
}

void Camera::setAspect(float aspect) {
    this->aspect = aspect;
}

void Camera::applyView() {
    Vec3 target = position + forward;
    gluLookAt(position.x, position.y, position.z,
              target.x, target.y, target.z,
              up.x, up.y, up.z);
}

void Camera::applyProjection() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov, aspect, near, far);
    glMatrixMode(GL_MODELVIEW);
}