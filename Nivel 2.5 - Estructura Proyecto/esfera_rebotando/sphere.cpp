#include "sphere.h"
#include <random>

static std::random_device rd;
static std::mt19937 gen(rd());
static bool initialized = false;

/**
 * @brief Constructor de la clase TSphere.
 * Inicializa la posición y dirección de la esfera aleatoriamente.
 * @param maxpos Valor máximo para las coordenadas de posición.
 * @param speed Velocidad inicial de la esfera.
 */
TSphere::TSphere(float maxpos, float speed) : maxpos(maxpos), speed(speed) {
    std::uniform_real_distribution<float> pos_dist(-maxpos / 2, maxpos / 2);
    std::uniform_real_distribution<float> dir_dist(-1.0f, 1.0f);
    std::uniform_real_distribution<float> color_dist(0.0f, 1.0f);

    pos[0] = pos_dist(gen);
    pos[1] = pos_dist(gen);
    pos[2] = pos_dist(gen);

    dir[0] = dir_dist(gen);
    dir[1] = dir_dist(gen);
    dir[2] = dir_dist(gen);

    color[0] = color_dist(gen);
    color[1] = color_dist(gen);
    color[2] = color_dist(gen);

    float dirmod = sqrt(dir[0] * dir[0] + dir[1] * dir[1] + dir[2] * dir[2]);
    if (dirmod > 0) {
        original_dir[0] = dir[0] / dirmod;
        original_dir[1] = dir[1] / dirmod;
        original_dir[2] = dir[2] / dirmod;
        dir[0] = original_dir[0] * speed;
        dir[1] = original_dir[1] * speed;
        dir[2] = original_dir[2] * speed;
    } else {
        original_dir[0] = original_dir[1] = original_dir[2] = 0.0f;
        dir[0] = dir[1] = dir[2] = 0.0f;
    }
}

/**
 * @brief Actualiza la posición de la esfera y cambia su dirección si excede los límites.
 */
void TSphere::updatePosition() {
    if (pos[0] < -maxpos || pos[0] > maxpos) dir[0] *= -1;
    if (pos[1] < -maxpos || pos[1] > maxpos) dir[1] *= -1;
    if (pos[2] < -maxpos || pos[2] > maxpos) dir[2] *= -1;
    pos[0] += dir[0];
    pos[1] += dir[1];
    pos[2] += dir[2];
}

void TSphere::setSpeed(float speed) {
    this->speed = speed;
    float dirmod = sqrt(dir[0] * dir[0] + dir[1] * dir[1] + dir[2] * dir[2]);
    if (dirmod > 0) {
        dir[0] = (dir[0] / dirmod) * speed;
        dir[1] = (dir[1] / dirmod) * speed;
        dir[2] = (dir[2] / dirmod) * speed;
    }
}

/**
 * @brief Modifica la velocidad de la esfera y ajusta la dirección proporcionalmente.
 * @param inc Incremento de velocidad.
 */
void TSphere::modifySpeed(float inc) {
    float factor = (speed + inc) / speed;
    speed += inc;
    dir[0] *= factor;
    dir[1] *= factor;
    dir[2] *= factor;
}

/**
 * @brief Restaura la velocidad y dirección originales, o asigna una nueva velocidad.
 * @param new_speed Si es >= 0, usa esta velocidad; si es -1, usa original_speed.
 */
void TSphere::restoreSpeed(float new_speed) {
    float target_speed = (new_speed >= 0.0f) ? new_speed : original_speed;
    speed = target_speed;
    dir[0] = original_dir[0] * speed;
    dir[1] = original_dir[1] * speed;
    dir[2] = original_dir[2] * speed;
}

/**
 * @brief Obtiene un puntero a la posición actual de la esfera.
 * @return float* Puntero al arreglo de posición.
 */
float *TSphere::getPosv() {
    return pos;
}

/**
 * @brief Obtiene un puntero al color de la esfera.
 * @return float* Puntero al arreglo de color.
 */
float *TSphere::getColorv() {
    return color;
}