#ifndef MATH_UTILS_H
#define MATH_UTILS_H
#include <cmath>

struct Vec3 {
    float x, y, z;
    Vec3(float x = 0.0f, float y = 0.0f, float z = 0.0f) : x(x), y(y), z(z) {}
    Vec3 operator+(const Vec3& other) const { return Vec3(x + other.x, y + other.y, z + other.z); }
    Vec3 operator-(const Vec3& other) const { return Vec3(x - other.x, y - other.y, z - other.z); }
    Vec3 operator*(float scalar) const { return Vec3(x * scalar, y * scalar, z * scalar); }
    float dot(const Vec3& other) const { return x * other.x + y * other.y + z * other.z; }
    Vec3 cross(const Vec3& other) const {
        return Vec3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
    }
    float length() const { return std::sqrt(x * x + y * y + z * z); }
    Vec3 normalized() const {
        float len = length();
        return len > 0 ? Vec3(x / len, y / len, z / len) : *this;
    }
};

struct Mat4 {
    float m[4][4];
    Mat4() {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                m[i][j] = (i == j) ? 1.0f : 0.0f;
    }
    static Mat4 perspective(float fov, float aspect, float near, float far) {
        Mat4 mat;
        float tan_half_fov = std::tan(fov * 0.5f);
        mat.m[0][0] = 1.0f / (aspect * tan_half_fov);
        mat.m[1][1] = 1.0f / tan_half_fov;
        mat.m[2][2] = -(far + near) / (far - near);
        mat.m[2][3] = -1.0f;
        mat.m[3][2] = -(2.0f * far * near) / (far - near);
        mat.m[3][3] = 0.0f;
        return mat;
    }
    void toOpenGL() const {
        float flat[16] = {
            m[0][0], m[1][0], m[2][0], m[3][0],
            m[0][1], m[1][1], m[2][1], m[3][1],
            m[0][2], m[1][2], m[2][2], m[3][2],
            m[0][3], m[1][3], m[2][3], m[3][3]
        };
        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf(flat);
    }
};

#endif