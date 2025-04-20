#include "scene.h"

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Esferas rebotando con cámara modular");
    Scene scene(800, 600);
    glutDisplayFunc(Scene::displayCallback);
    glutReshapeFunc(Scene::reshapeCallback);
    glutKeyboardFunc(Scene::keyboardCallback);
    glutMouseFunc(Scene::mouseCallback);
    glutMotionFunc(Scene::motionCallback);
    glutIdleFunc(Scene::idleCallback);
    glutMainLoop();
    return 0;
}