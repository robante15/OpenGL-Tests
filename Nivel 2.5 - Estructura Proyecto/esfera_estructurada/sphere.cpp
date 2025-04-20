#include "sphere.h"
#include <random>

static std::random_device rd;
static std::mt19937 gen(rd());

TSphere::TSphere(float maxpos, float speed) : maxpos(maxpos), speed(speed), original_speed(speed) {
    std::uniform_real_distribution<float> pos_dist(-maxpos / 2, maxpos / 2);
    std::uniform_real_distribution<float> dir_dist(-1.0f, 1.0f);
    std::uniform_real_distribution<float> color_dist(0.0f, 1.0f);

    pos = Vector3(pos_dist(gen), pos_dist(gen), pos_dist(gen));
    dir = Vector3(dir_dist(gen), dir_dist(gen), dir_dist(gen));
    color = Vector3(color_dist(gen), color_dist(gen), color_dist(gen));

    float dirmod = dir.length();
    if (dirmod > 0) {
        original_dir = dir.normalized();
        dir = original_dir * speed;
    } else {
        original_dir = Vector3(0.0f, 0.0f, 0.0f);
        dir = Vector3(0.0f, 0.0f, 0.0f);
    }
}

void TSphere::test() {
    if (pos.x < -maxpos || pos.x > maxpos) dir.x *= -1;
    if (pos.y < -maxpos || pos.y > maxpos) dir.y *= -1;
    if (pos.z < -maxpos || pos.z > maxpos) dir.z *= -1;
    pos = pos + dir;
}

void TSphere::modifySpeed(float inc) {
    float factor = (speed + inc) / (speed > 0.0f ? speed : 1.0f);
    speed += inc;
    dir = dir * factor;
}

void TSphere::restoreSpeed(float new_speed) {
    float target_speed = (new_speed >= 0.0f) ? new_speed : original_speed;
    speed = target_speed;
    dir = original_dir * speed;
}