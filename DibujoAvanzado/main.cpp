#include <iostream>
#include "dibujado.h"

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    GLfloat array1[11][3] = {
            {4.54,  -4.00, 0.0},
            {0.92,  3.24,  0.0},
            {-2.18, -4.04, 0.0},
            {-3.8,  -4.76, 0.0},
            {-4.74, -3.82, 0.0},
            {-5.78, -4.28, 0.0},
            {-7.6,  -2.24, 0.0},
            {-7.58, 1.26,  0.0},
            {-6.26, 1.58,  0.0},
            {-6.26, 2.28,  0.0},
            {-5.24, 2.52,  0.0}
    };

    GLfloat array2[6][3] = {
            {-1.68, 5.32, 0.0},
            {-0.58, 5.46, 0.0},
            {0.38,  5.3,  0.0},
            {0.4,   4.16, 0.0},
            {-0.68, 3.98, 0.0},
            {-1.68, 4.22, 0.0}
    };

    GLfloat array3[3][3] = {
            {-2.46, 2.24, 0.0},
            {-1.12, 1.7,  0.0},
            {-1.08, -1.5, 0.0}
    };

    GLfloat array4[3][3] = {
            {-3.78, -4.78, 0.0},
            {-3.78, 1.04,  0.0},
            {-1.12, 1.7, 0.0}
    };

    GLfloat array5[5][3] = {
            {-6.26, 1.58, 0.0},
            {-5.8, 1.64,  0.0},
            {-3.78, 0.46, 0.0},
            {-5.78, -0.12, 0.0},
            {-7.58, 1.26,  0.0}
    };

    GLfloat array6[3][3] = {
            {-0.68, 3.98, 0.0},
            {-0.7, 5.14,  0.0},
            {0.38, 5.30, 0.0}
    };

    GLfloat array7[9][3] = {
            {6.84, -3.04, 0.0},
            {6.18, -2.78,  0.0},
            {6.06, -2.52, 0.0},
            {6.1, -1.78, 0.0},
            {6.22, -1.58,  0.0},
            {6.84, -1.22, 0.0},
            {7.5, -1.44, 0.0},
            {7.58, -1.78,  0.0},
            {7.56, -2.64, 0.0}
    };

    std::string blanco = "#FFFFFF";
    std::string gris = "#858585";

    lineStrip(array1, 11, 3, blanco, 1);
    circuloLineas(-3.73, 3.49, 1.7916, blanco, 25, 1);
    lineLoop(array2, 6, 3, blanco, 1);
    elipseLineas(3.91, 1.04, 1.7860, 0.3605, blanco, 25, 1);
    linea(3.52, 1.39, 3.50, 4.50, blanco, 1);
    linea(7.14, -0.84, 7.14, 4.50, blanco, 1);
    elipseLineas(5.32, 4.5, 1.8330, 0.2236, blanco, 25, 1);
    linea(5.7, 1.04, 5.72, -3.5, blanco, 1);
    arcoCirculoLinea(4.48, -2.23, 1.7748, blanco, 25, 1, -88, 42.41);
    arcoCirculoLinea(5.91, 0.54, 1.8411, blanco, 25, 1, -96, 47.68);
    arcoElipseLinea(1.18, -4.00, 3.3496, 1.3601, blanco, 50, 1, 180, 180);
    lineStrip(array3, 3, 3, blanco, 1);
    lineStrip(array4, 3, 3, gris, 1);
    linea(-3.78,1.04,-6.24,2.28,gris,1);
    lineStrip(array5, 5, 3, gris, 1);
    linea(-5.78, -0.12,-5.78, -4.28,gris,1);
    linea(-4.74, -3.82,-3.78,-3.44,gris,1);
    lineStrip(array6, 3, 3, gris, 1);
    linea(-0.7, 5.14, -1.68, 5.32, gris, 1);
    linea(2.14, 0.76, 2.14, 1.08, blanco,1);
    lineLoop(array7, 9, 3, blanco, 1);



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
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("-- Ejemplo Circulo --");
    //std::cout << argc << std::endl;
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
