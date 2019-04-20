#include <iostream>
#include "dibujado.h"
#include "arrays.h"

static void llanta(std::string color) {
    circuloLineas(-6.14, -1.95, 1.8303, color, 25, 2);
    arcoCirculoLinea(-6.14, -1.95, 1.6431, color, 25, 1, 130, 270);
    circuloLineas(-6.14, -1.95, 1.1401, color, 25, 1);
    circuloLineas(-6.14, -1.95, 1.2688, color, 25, 2);
    circuloLineas(-6.14, -1.95, 0.1500, color, 25, 2);
    arcoCirculoLinea(-6.17, -1.85, 1.9416, color, 25, 2, 4, 186.59);
    lineStrip(array23, 5, 3, color, 2);
    circuloLineas(-5.86, -1.68, 0.1000, color, 15, 1);
    circuloLineas(-6.29, -1.62, 0.1000, color, 15, 1);
    circuloLineas(-6.50, -2.08, 0.1000, color, 15, 1);
    circuloLineas(-5.74, -2.08, 0.1000, color, 15, 1);
    circuloLineas(-6.09, -2.33, 0.1000, color, 15, 1);
    lineStrip(array27, 3, 3, color, 2);
    lineStrip(array28, 3, 3, color, 2);
    linea(-5.06, -1.53, -5.4, -1.75, color, 2);
    linea(-5.89, -0.83, -6.09, -1.25, color, 2);
    lineStrip(array29, 3, 3, color, 2);
    lineStrip(array30, 3, 3, color, 2);
    linea(-5.34, -2.81, -5.73, -2.48, color, 2);
    lineStrip(array31, 3, 3, color, 2);
    linea(-6.96, -2.69, -6.52, -2.51, color, 2);
    linea(-7.25, -1.92, -6.68, -1.80, color, 2);
    lineStrip(array32, 7, 3, color, 2);
    lineStrip(array33, 7, 3, color, 2);
    lineStrip(array34, 7, 3, color, 2);
    lineStrip(array35, 7, 3, color, 2);
    lineStrip(array36, 7, 3, color, 2);
}

void display(void) {
    std::string blanco = "#FFFFFF";
    std::string gris = "#858585";

    glClear(GL_COLOR_BUFFER_BIT);

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
    lineLoop(array11, 4, 3, blanco, 2);
    linea(4.35, -0.14, 3.59, -0.14, blanco, 2);
    lineLoop(array12, 4, 3, blanco, 2);

    //Llantas
    llanta(blanco);
    linea(-4.23, -1.73, -4.14, -3.08, blanco, 2);
    linea(-8.08, -2.19, -8.03, -2.74, blanco, 2);
    glTranslatef(12.35,0,0);
    llanta(blanco);
    linea(-8.08, -2.19, -8.03, -3.00, blanco, 2);
    linea(-4.23, -1.73, -4.14, -3.00, blanco, 2);
    glTranslatef(-12.35,0,0);
    linea(4.15,-3.05,4.63,-2.94,blanco,2);

    linea(-4.64, -3.06, 4.17, -3.06, blanco, 2);
    lineStrip(array14, 45, 3, blanco, 2);
    lineLoop(array15, 27, 3, blanco, 2);
    lineStrip(array16, 10, 3, blanco, 1);
    lineStrip(array17, 4, 3, blanco, 1);
    lineStrip(array18, 3, 3, blanco, 1);
    lineStrip(array19, 4, 3, blanco, 1);
    lineStrip(array20, 8, 3, blanco, 1);
    linea(-6.41, 0.917, -3.16, 0.95, blanco, 1);
    lineStrip(array21, 25, 3, blanco, 1);
    linea(2.64, 0.64, 6.8, 0.5, blanco, 1);
    lineStrip(array22, 8, 3, blanco, 1);
    linea(-9.21, -1.64, -8.45, -1.93, blanco, 1);
    linea(-2.9, 0.99, -2.52, 1.89, blanco, 1);
    linea(-3.13, 1.01, -2.73, 1.89, blanco, 1);
    lineStrip(array24, 3, 3, blanco, 1);
    linea(-2.88, -2.3, 2.89, -2.57, blanco, 1);
    linea(-1.72, -0.83, 2.61, -0.8, blanco, 1);
    linea(8.55153, -1.68057, 9.27972, -0.52142, blanco, 1);
    linea(7.79363, -0.65517, 8.47723, -0.25392, blanco, 1);
    lineStrip(array25, 4, 3, blanco, 1);
    linea(-1.14, 0.56, 2.27, 0.53, blanco, 1);
    lineLoop(array26, 6, 3, blanco, 2);
    lineStrip(array37, 3, 3, blanco, 1);

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
    glutCreateWindow("-- Ejercicio 4 --");
    //std::cout << argc << std::endl;
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
