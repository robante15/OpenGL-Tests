#include <iostream>
#include "dibujado.h"

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    GLfloat array1[4][3] = {
            {-1.0, 0.0,  0.0},
            {0.0,  -1.0, 0.0},
            {1.0,  0.0,  0.0},
            {0.0,  1.0,  0.0}
    };

    GLfloat array2[4][3] = {
            {1.0,  0.0,  0.0},
            {0.0,  1.0,  0.0},
            {-1.0, 0.0,  0.0},
            {0.0,  -1.0, 0.0}
    };

    lineStrip(array1, 4, 3, "00FFF0", 1);
    sectorCirculoLinea(5.5, 5.5, 4, "00FF00", 15, 1, 315, 90);
    sectorCirculoPoly(-5.5, 5.5, 4, "00FF00", 15, 35, 125);
    circuloPoligono(1, 7.5, 2, "00FF00", 15);
    circuloLineas(-7.5, 3, 2, "00FF00", 15, 2);
    segmentoCirculoPoly(-2.5, 2.5, 2.5, "FF0000", 25, 0, 270);
    segmentoCirculoLinea(3, 2.5, 2.5, "0000FF", 25, 1, 180, 270);

    //circuloTeselado(0.5, 15);

    glEnd();
    glFlush();

}

void init(void) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("-- Ejemplo Circulo --");
    //std::cout << argc << std::endl;
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
