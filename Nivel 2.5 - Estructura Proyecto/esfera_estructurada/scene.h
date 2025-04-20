#ifndef SCENE_H
#define SCENE_H

#include <GL/glut.h>
#include <vector>
#include "camera.h"
#include "sphere.h"

class Scene {
private:
    std::vector<TSphere*> spheres;
    Camera* camera;
    GLUquadric* quad;
    bool lighting_enabled;
    int quad_style;
    int window_width, window_height;
    bool mouse_dragging;
    int last_mouse_x, last_mouse_y;

    static Scene* instance; // Puntero a la instancia actual

    void initGL();
    void setupLighting();
    void checkGLError(const char* operation);

public:
    Scene(int width, int height);
    ~Scene();
    void display();
    void reshape(int width, int height);
    void idle();
    void keyboard(unsigned char key, int x, int y);
    void mouse(int button, int state, int x, int y);
    void motion(int x, int y);

    // Funciones estáticas para callbacks de GLUT
    static void displayCallback();
    static void reshapeCallback(int width, int height);
    static void idleCallback();
    static void keyboardCallback(unsigned char key, int x, int y);
    static void mouseCallback(int button, int state, int x, int y);
    static void motionCallback(int x, int y);

    static void setInstance(Scene* scene) { instance = scene; }
};

#endif