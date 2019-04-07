#include <iostream>
#include "dibujado.h"

void display(void) {
    std::string blanco = "#FFFFFF";
    std::string gris = "#858585";

    glClear(GL_COLOR_BUFFER_BIT);

    GLfloat array1[7][3] = {
            {2.67, 1.29, 0.0},
            {2.67, 4.49, 0.0},
            {5.85, 4.49, 0.0},
            {5.85, 2.88, 0.0},
            {8.57, 2.88, 0.0},
            {8.57, 2.47, 0.0},
            {9.68, 2.47, 0.0}
    };

    GLfloat array2[4][3] = {
            {2.79, 4.20, 0.0},
            {5.70, 4.20, 0.0},
            {5.70, 3.76, 0.0},
            {2.79, 3.76, 0.0}
    };

    GLfloat array3[4][3] = {
            {6.16, 2.55, 0.0},
            {8.22, 2.55, 0.0},
            {8.22, 2.21, 0.0},
            {6.16, 2.21, 0.0}
    };

    GLfloat array4[4][3] = {
            {8.80, 2.15, 0.0},
            {9.20, 2.15, 0.0},
            {9.20, 0.22, 0.0},
            {8.80, 0.22, 0.0}
    };

    GLfloat array5[5][3] = {
            {-9.74, 4.22, 0.0},
            {-6.31, 4.22, 0.0},
            {-6.31, 3.61, 0.0},
            {-0.04, 3.61, 0.0},
            {-0.04, 2.54, 0.0}
    };

    GLfloat array6[3][3] = {
            {0.29, 5.54, 0.0},
            {0.96, 5.54, 0.0},
            {0.96, 2.47, 0.0}
    };

    GLfloat array7[4][3] = {
            {0.5,  5.3,  0.0},
            {0.69, 5.3,  0.0},
            {0.71, 2.72, 0.0},
            {0.5,  2.72, 0.0}
    };

    GLfloat array8[4][3] = {
            {-9.56, 3.82, 0.0},
            {-6.61, 3.82, 0.0},
            {-6.61, 3.40, 0.0},
            {-9.56, 3.40, 0.0}
    };

    GLfloat array9[4][3] = {
            {-6.07, 3.37, 0.0},
            {-0.39, 3.37, 0.0},
            {-0.39, 2.99, 0.0},
            {-6.07, 2.99, 0.0}
    };

    GLfloat array10[4][3] = {
            {-6.07, 2.69, 0.0},
            {-4.95, 2.69, 0.0},
            {-4.95, 2.23, 0.0},
            {-6.07, 2.23, 0.0}
    };

    GLfloat array11[4][3] = {
            {3.37, -0.91, 0.0},
            {4.15, -0.91, 0.0},
            {4.38, 0.00, 0.0},
            {3.63, 0.00, 0.0}
    };

    GLfloat array12[4][3] = {
            {3.70, 0.25, 0.0},
            {4.44, 0.25, 0.0},
            {4.41, 0.12, 0.0},
            {3.65, 0.12, 0.0}
    };

    //Lineas del suelo
    linea(-8.75, -4.64, 4.98, -4.64, blanco, 2);
    linea(7.81, -5.10, -5.83, -5.10, blanco, 2);
    linea(-9.74, -3.64, -6.89, -3.64, blanco, 2);
    linea(-5.4, -3.64, 5.45, -3.64, blanco, 2);
    linea(-5.4, -3.64, 5.45, -3.64, blanco, 2);
    linea(9.67, -3.64, 6.95, -3.64, blanco, 2);

    /* ------------------ Edificios Derecha ------------------*/
    lineStrip(array1, 7, 3, blanco, 2);
    for (int i = 0; i < 4; ++i) {
        lineLoop(array2, 4, 3, blanco, 2);
        linea(3.25, 4.2, 3.25, 3.76, blanco, 2);
        linea(4.17, 4.2, 4.17, 3.76, blanco, 2);
        linea(5.25, 4.2, 5.25, 3.76, blanco, 2);
        glTranslatef(0, -0.76, 0);
    }

    glTranslatef(0, 0.76 * 4, 0); //Reseteo la translación que habia realizado para ubicar las ventanas
    linea(5.85, 2.88, 5.85, 0.73, blanco, 2);

    for (int i = 0; i < 3; ++i) {
        lineLoop(array3, 4, 3, blanco, 2);
        linea(7.17, 2.21, 7.17, 2.55, blanco, 2);
        glTranslatef(0, -0.61, 0);
    }
    glTranslatef(0, 0.61 * 3, 0); //Reseteo la translación que habia realizado para ubicar las ventanas


    lineLoop(array4, 4, 3, blanco, 2);
    linea(9.00, 0.22, 9.00, 2.15, blanco, 2);

    /* ------------------ Edificios Izquierda ------------------*/
    lineStrip(array5, 5, 3, blanco, 2);
    linea(0.3, 5.88, 0.3, 2.53, blanco, 2);
    linea(-0.2, 5.82, -0.2, 3.60, blanco, 2);
    linea(-0.87, 3.62, -0.87, 5.05, blanco, 2);
    linea(-6.31, 3.61, -6.31, 1.66, blanco, 2);
    lineStrip(array6, 3, 3, blanco, 2);
    lineLoop(array7, 4, 3, blanco, 2);
    linea(-0.68, 4.44, -0.38, 4.93, blanco, 1);
    linea(-0.63, 4.26, -0.44, 4.57, blanco, 1);

    for (int i = 0; i < 3; ++i) {
        lineLoop(array8, 4, 3, blanco, 2);
        linea(-9.06, 3.82, -9.06, 3.40, blanco, 2);
        linea(-8.0, 3.82, -8.0, 3.40, blanco, 2);
        glTranslatef(0, -0.75, 0);
    }
    glTranslatef(0, 0.75 * 3, 0);

    lineLoop(array9, 4, 3, blanco, 2);
    lineLoop(array10, 4, 3, blanco, 2);

    arcoCirculoLinea(0.14, 4.87, 1.02956, blanco, 25, 2, 80.5, 88.23);

    /*-------------- Carro ---------------*/
    lineLoop(array11, 4, 3, blanco, 1);
    linea(4.35,-0.14,3.59,-0.14,blanco,1);
    lineLoop(array12, 4, 3, blanco, 1);

    circuloLineas(-6.14,-1.95,1.8303,blanco,25,2);
    arcoCirculoLinea(-6.14,-1.95,1.6431,blanco,25,2,130,270);

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
