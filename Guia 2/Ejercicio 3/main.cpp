#include <iostream>
#include "dibujado.h"
#include "arrays.h"


void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    ObjectPoly(array1, 4, amb_rojoOscuro,dif_rojoOscuro,spec_rojoOscuro,shine_rojoOscuro);
    ObjectPoly(array2, 4, amb_Marron,dif_Marron,spec_Marron,shine_Marron);
    ObjectPoly(array3, 4, amb_MarronClaro,dif_MarronClaro,spec_MarronClaro,shine_MarronClaro);
    ObjectPoly(array4, 4, amb_rojoClaro,dif_rojoClaro,spec_rojoClaro,shine_rojoClaro);
    ObjectPoly(sabana, 4, amb_Morado,dif_Morado,spec_Morado,shine_Morado);
    ObjectPoly(almohadaDer, 4, amb_Lima,dif_Lima,spec_Lima,shine_Lima);
    ObjectPoly(almohadaIzq, 4, amb_Lima,dif_Lima,spec_Lima,shine_Lima);
    ObjectPoly(visorLampara, 4, amb_rojoClaro,dif_rojoClaro,spec_rojoClaro,shine_rojoClaro);
    ObjectPoly(gabetaSupMesitaDer, 4, amb_MarronClaro,dif_MarronClaro,spec_MarronClaro,shine_MarronClaro);
    ObjectPoly(gabetaInfMesitaDer, 4, amb_MarronClaro,dif_MarronClaro,spec_MarronClaro,shine_MarronClaro);
    ObjectPoly(marcoReloj, 4, amb_GrisOscuro,dif_GrisOscuro,spec_GrisOscuro,shine_GrisOscuro);
    ObjectPoly(centroReloj, 4, amb_Blanco,dif_Blanco,spec_Blanco,shine_Blanco);
    ObjectPoly(ACFrontal, 4, amb_GrisClaro,dif_GrisClaro,spec_GrisClaro,shine_GrisClaro);
    ObjectPoly(ACSuperior, 4, amb_GrisOscuro,dif_GrisOscuro,spec_GrisOscuro,shine_GrisOscuro);
    ObjectPoly(ACInferior, 4, amb_GrisOscuro,dif_GrisOscuro,spec_GrisOscuro,shine_GrisOscuro);
    ObjectPoly(ACCostado, 4, amb_CasiNegro,dif_CasiNegro,spec_CasiNegro,shine_CasiNegro);
    ObjectPoly(FondoVentana, 4, amb_Blanco,dif_Blanco,spec_Blanco,shine_Blanco);
    ObjectPoly(MarcoSuperiorVentana, 4, amb_GrisMarron,dif_GrisMarron,spec_GrisMarron,shine_GrisMarron);
    ObjectPoly(MarcoInferiorVentana, 4, amb_GrisMarron,dif_GrisMarron,spec_GrisMarron,shine_GrisMarron);
    ObjectPoly(TopMuebleIzq, 4, amb_MarronClaro,dif_MarronClaro,spec_MarronClaro,shine_MarronClaro);
    ObjectPoly(FrontalMuebleIzq, 4, amb_MarronClaro,dif_MarronClaro,spec_MarronClaro,shine_MarronClaro);
    ObjectPoly(LateralMuebleIzq, 4, amb_MarronOscuro,dif_MarronOscuro,spec_MarronOscuro,shine_MarronOscuro);
    ObjectPoly(PuertaIzqMuebleIzq, 4, amb_MarronOscuro,dif_MarronOscuro,spec_MarronOscuro,shine_MarronOscuro);
    ObjectPoly(PuertaMidMuebleIzq, 4, amb_MarronOscuro,dif_MarronOscuro,spec_MarronOscuro,shine_MarronOscuro);
    ObjectPoly(PuertaDerMuebleIzq, 4, amb_MarronOscuro,dif_MarronOscuro,spec_MarronOscuro,shine_MarronOscuro);
    ObjectPoly(MarcoEspejoMuebleIzq, 4, amb_MarronClaro,dif_MarronClaro,spec_MarronClaro,shine_MarronClaro);
    ObjectPoly(EspejoMuebleIzq, 4, amb_Blanco,dif_Blanco,spec_Blanco,shine_Blanco);
    /*
    ObjectPoly(MarcoCuadro, 4,3,"FFFFFF",1);
    ObjectPoly(InteriorCuadro, 4,3,"FFFFFF",1);
    ObjectPoly(MarcoDerechoVentana, 4,3,"FFFFFF",1);

    */


    glEnd();
    glFlush();

}

void init(void) {
    GLfloat light_position[4] = {5.0, 5.0, 5.0, 0.0};
    glEnable(GL_LIGHTING); //activa la fuente de luz
    glEnable(GL_LIGHT0); //Activamos las luces en 0
    glDepthFunc(GL_LESS); //comparación de profundidad
    glEnable(GL_DEPTH_TEST); //activa GL_DEPTH_TES
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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
