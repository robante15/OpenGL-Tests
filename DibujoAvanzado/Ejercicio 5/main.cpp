#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include "points.h"
#include "dibujado.h"

void display(void) {
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3fv(Hex2RGB("#FFFFFF"));
    dibujo();

    circuloLineas(-2.21, 5.79, 0.05, "#FFFFFF", 25, 1);
    circuloLineas(2.21, 5.79, 0.05, "#FFFFFF", 25, 1);
    circuloLineas(0.00, 8.22, 0.05, "#FFFFFF", 25, 1);
    circuloLineas(0.00, 8.45, 0.05, "#FFFFFF", 25, 1);
    circuloLineas(0.00, 8.22, 0.1, "#FFFFFF", 25, 1);
    circuloLineas(0.00, 8.45, 0.1, "#FFFFFF", 25, 1);

    glFlush();
}

void init(void) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-6.0, 6.0, -1.0, 9.0, -1.0, 1.0);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(300, 500);
    glutCreateWindow("---- Ejercicio 5 -----");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
