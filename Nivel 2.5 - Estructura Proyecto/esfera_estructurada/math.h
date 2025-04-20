#ifndef MATH_H
#define MATH_H

#include <cmath>

class Vector3
{
public:
    float x, y, z;

    Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

    Vector3 operator+(const Vector3 &other) const
    {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    Vector3 operator-(const Vector3 &other) const
    {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    Vector3 operator*(float scalar) const
    {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }

    float dot(const Vector3 &other) const
    {
        return x * other.x + y * other.y + z * other.z;
    }

    Vector3 cross(const Vector3 &other) const
    {
        return Vector3(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x);
    }

    float length() const
    {
        return std::sqrt(x * x + y * y + z * z);
    }

    Vector3 normalized() const
    {
        float len = length();
        if (len > 0.0f)
        {
            return Vector3(x / len, y / len, z / len);
        }
        return *this;
    }
};

class Vector4
{
public:
    float x, y, z, w;

    Vector4() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}
    Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

    Vector4 operator+(const Vector4 &other) const
    {
        return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
    }
};

class Matrix4
{
public:
    float m[4][4];

    Matrix4()
    {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                m[i][j] = (i == j) ? 1.0f : 0.0f;
    }

    /**
     * @brief Genera una matriz de vista (lookAt) utilizada para transformar coordenadas del mundo
     *        a coordenadas de vista en gráficos 3D.
     * 
     * @param eye Vector3 que representa la posición de la cámara (o el ojo) en el espacio.
     * @param center Vector3 que indica el punto al que la cámara está mirando.
     * @param up Vector3 que define la dirección "arriba" para la cámara.
     * 
     * @return Matrix4 La matriz de transformación de vista resultante.
     * 
     * @details Esta función calcula una matriz de vista basada en la posición de la cámara (eye),
     *          el punto de enfoque (center) y el vector "arriba" (up). Utiliza los vectores
     *          normalizados para definir los ejes de la cámara y construye la matriz de vista
     *          que puede ser utilizada para transformar coordenadas del mundo a coordenadas
     *          relativas a la cámara.
     */
    static Matrix4 lookAt(const Vector3& eye, const Vector3& center, const Vector3& up) {
        Vector3 f = (center - eye).normalized();
        Vector3 u = up.normalized();
        Vector3 s = f.cross(u).normalized();
        u = s.cross(f);

        Matrix4 result;
        result.m[0][0] = s.x;
        result.m[0][1] = s.y;
        result.m[0][2] = s.z;
        result.m[0][3] = 0.0f;
        result.m[1][0] = u.x;
        result.m[1][1] = u.y;
        result.m[1][2] = u.z;
        result.m[1][3] = 0.0f;
        result.m[2][0] = -f.x;
        result.m[2][1] = -f.y;
        result.m[2][2] = -f.z;
        result.m[2][3] = 0.0f;
        result.m[3][0] = -s.dot(eye);
        result.m[3][1] = -u.dot(eye);
        result.m[3][2] = f.dot(eye);
        result.m[3][3] = 1.0f;
        return result;
    }

    /**
     * @brief Llena una matriz unidimensional con los valores de una matriz 4x4 en formato OpenGL.
     * 
     * Esta función convierte una matriz 4x4 almacenada internamente en un formato adecuado
     * para ser utilizado con OpenGL. Los valores se copian en un arreglo unidimensional
     * de tamaño 16, siguiendo el orden de las filas.
     * 
     * @param[out] out Puntero a un arreglo de 16 elementos donde se almacenarán los valores
     *                 de la matriz en formato OpenGL.
     */
    void getOpenGLMatrix(float* out) const {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                out[i * 4 + j] = m[i][j];
    }
};

#endif