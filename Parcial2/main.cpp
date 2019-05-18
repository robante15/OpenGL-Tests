#include <GL/gl.h>
#include <GL/glut.h>
#include "dibujado.h"
#include "objetos.h"
#include <time.h>

static int girox = 0;
static GLfloat translatez = -2.25;

void init(void) {


    glDepthFunc(GL_LESS); //comparación de profundidad
    glEnable(GL_DEPTH_TEST); //activa GL_DEPTH_TES
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10, 10, -10, 10, -10, 10);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW_MATRIX);
    glLoadIdentity();

    setlight();

// Rotacion de 25 grados en torno al eje x
    glRotated(25.0, 1.0, 0.0, 0.0);
// Rotacion de -30 grados en torno al eje y
    glRotated(-30.0, 0.0, 1.0, 0.0);
// Dibujamos una "Tetera" y le aplico el material
    glPushMatrix();
    generadorObjetos(baseVertices, cubeFaces, 6, amb_GrisClaro, dif_GrisClaro, spec_GrisClaro, shine_GrisClaro);
    glPopMatrix();

    glPushMatrix();
    generadorObjetos(mastilVertices, cubeFaces, 6, amb_GrisClaro, dif_GrisClaro, spec_GrisClaro, shine_GrisClaro);
    glPopMatrix();

    glPushMatrix();
    generadorObjetos(pivoteVertices, cubeFaces, 6, amb_GrisClaro, dif_GrisClaro, spec_GrisClaro, shine_GrisClaro);
    glPopMatrix();

    glRotated(girox, 0, 0.799, 1.0);

    glPushMatrix();
    generadorObjetos(palitoVertices, cubeFaces, 6, amb_GrisClaro, dif_GrisClaro, spec_GrisClaro, shine_GrisClaro);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.50, translatez, 4.50);
    glutSolidSphere(1, 15, 15);
    glPopMatrix();

    //glutSolidTeapot(5);

    glFlush();
}

//se mueve en rotacion a x
void keyboard(int key, int x, int y) {

    if(key == GLUT_KEY_LEFT){
        girox = (girox - 1);
        if (girox == -100) {
            girox = girox + 1;
        }
        glutPostRedisplay();
    }else if (key == GLUT_KEY_RIGHT){
        girox = (girox + 1);
        if (girox == 100) {
            girox = girox - 1;
        }
        glutPostRedisplay();
    }else if(key == GLUT_KEY_UP){
        if(translatez < 1.75){
            translatez = translatez +0.15;
        }
        glutPostRedisplay();
    }else if(key == GLUT_KEY_DOWN){
        if(translatez >= -2.25){
            translatez = translatez -0.15;
        }
        glutPostRedisplay();
    }

    glutPostRedisplay(); // Redraw the scene
}



int main(int argc, char **argv) {
// Inicializo OpenGL
    glutInit(&argc, argv);
// Activamos buffer simple y colores del tipo RGB
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
// Definimos una ventana de medidas 800 x 600 como ventana
// de visualizacion en pixels
    glutInitWindowSize(800, 600);
// Posicionamos la ventana en la esquina superior izquierda de
// la pantalla.
    glutInitWindowPosition(0, 0);
// Creamos literalmente la ventana y le adjudicamos el nombre que se
// observara en su barra de titulo.
    glutCreateWindow("Parcial #2");
// Inicializamos el sistema
    init();
    setlight();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(keyboard);
    glutMainLoop();

    return 0;
}
