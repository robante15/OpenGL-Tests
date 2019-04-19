#include <iostream>
#include "dibujado.h"
#include "arrays.h"


void display(void) {
    std::string blanco = "#FFFFFF";
    std::string gris = "#858585";

    glClear(GL_COLOR_BUFFER_BIT);

    lineLoop(array1, 4,3,"FFFFFF",1);
    lineLoop(array2, 4,3,"FFFFFF",1);
    lineLoop(array3, 4,3,"FFFFFF",1);
    lineLoop(array4, 4,3,"FFFFFF",1);
    lineLoop(sabana, 4,3,"FFFFFF",1);
    lineLoop(almohadaDer, 4,3,"FFFFFF",1);
    lineLoop(almohadaIzq, 4,3,"FFFFFF",1);
    lineLoop(visorLampara, 4,3,"FFFFFF",1);
    lineLoop(gabetaSupMesitaDer, 4,3,"FFFFFF",1);
    lineLoop(gabetaInfMesitaDer, 4,3,"FFFFFF",1);
    lineLoop(marcoReloj, 4,3,"FFFFFF",1);
    lineLoop(centroReloj, 4,3,"FFFFFF",1);
    lineLoop(ACFrontal, 4,3,"FFFFFF",1);
    lineLoop(ACSuperior, 4,3,"FFFFFF",1);
    lineLoop(ACCostado, 4,3,"FFFFFF",1);
    lineLoop(ACInferior, 4,3,"FFFFFF",1);
    lineLoop(MarcoCuadro, 4,3,"FFFFFF",1);
    lineLoop(InteriorCuadro, 4,3,"FFFFFF",1);
    lineLoop(FondoVentana, 4,3,"FFFFFF",1);
    lineLoop(MarcoSuperiorVentana, 4,3,"FFFFFF",1);
    lineLoop(MarcoDerechoVentana, 4,3,"FFFFFF",1);
    lineLoop(MarcoInferiorVentana, 4,3,"FFFFFF",1);

    lineLoop(TopMuebleIzq, 4,3,"FFFFFF",1);
    lineLoop(FrontalMuebleIzq, 4,3,"FFFFFF",1);
    lineLoop(LateralMuebleIzq, 4,3,"FFFFFF",1);
    lineLoop(PuertaIzqMuebleIzq, 4,3,"FFFFFF",1);
    lineLoop(PuertaMidMuebleIzq, 4,3,"FFFFFF",1);
    lineLoop(PuertaDerMuebleIzq, 4,3,"FFFFFF",1);
    lineLoop(MarcoEspejoMuebleIzq, 4,3,"FFFFFF",1);
    lineLoop(EspejoMuebleIzq, 4,3,"FFFFFF",1);


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
    glutCreateWindow("-- Ejercicio 3 --");
    //std::cout << argc << std::endl;
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
