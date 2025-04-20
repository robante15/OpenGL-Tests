#ifndef SPHERE_H
#define SPHERE_H

class TSphere {
private:
    float maxpos; // Máxima posición de la esfera
    float pos[3]; // Posición de la esfera
    float dir[3]; // Dirección de la esfera
    float color[3]; // Color de la esfera
    float speed;  // Velocidad de la esfera
    float original_dir[3]; // Dirección original de la esfera
    float original_speed; // Velocidad original de la esfera]

public:
    TSphere(float maxpos, float speed); // Constructor
    void updatePosition();
    void modifySpeed(float inc);
    void setSpeed(float speed);
    void restoreSpeed(float new_speed = -1.0f);
    float *getPosv();
    float *getColorv();
};

#endif