#include <GL/gl.h>
#include <GL/glut.h>
#include "dibujado.h"
#include "objetos.h"

static int girox = 0;
static GLfloat translate[2] = {0, 0};
static int pasos = 0;

void init(void) {

    //GLfloat light_position[4] = {5.0, 10.0, -10.0, 0.0};

    //glEnable(GL_LIGHTING); //activa la fuente de luz
    //glEnable(GL_LIGHT0); //Activamos las luces en 0
    glDepthFunc(GL_LESS); //comparación de profundidad
    glEnable(GL_DEPTH_TEST); //activa GL_DEPTH_TES
    //glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    // Activamos la matriz de proyeccion.
    glMatrixMode(GL_PROJECTION);
    // "limpiamos" esta con la matriz identidad.
    glLoadIdentity();
    // Usamos proyeccion ortogonal
    glOrtho(-10, 10, -10, 10, -10, 10);
    // Activamos la matriz de modelado/visionado.
    glMatrixMode(GL_MODELVIEW);
    // "Limpiamos" la matriz
    glLoadIdentity();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW_MATRIX);
    glLoadIdentity();

    setlight();
    //setmaterial();

// Rotacion de 25 grados en torno al eje x
    glRotated(25.0, 1.0, 0.0, 0.0);
// Rotacion de -30 grados en torno al eje y
    glRotated(-30.0, 0.0, 1.0, 0.0);
// Dibujamos una "Tetera" y le aplico el material
    glPushMatrix();

    generadorObjetos(baseVertices, cubeFaces, 6, amb_GrisClaro, dif_GrisClaro, spec_GrisClaro, shine_GrisClaro);
    generadorObjetos(mastilVertices, cubeFaces, 6, amb_GrisClaro, dif_GrisClaro, spec_GrisClaro, shine_GrisClaro);
    generadorObjetos(pivoteVertices, cubeFaces, 6, amb_GrisClaro, dif_GrisClaro, spec_GrisClaro, shine_GrisClaro);
    //generadorObjetos(palitoVertices, cubeFaces, 6, amb_GrisClaro, dif_GrisClaro, spec_GrisClaro, shine_GrisClaro);

    glTranslated(+0, +250, 0);
    glRotated((GLdouble) girox, 0.0, 1.0, 0.0);
    glTranslated(-0, -250, 0);

    arcoCirculoLinea(0,0,5,"#FFFFFF",25,5,180,180);

    generadorObjetos(palitoVertices, cubeFaces, 6, amb_GrisClaro, dif_GrisClaro, spec_GrisClaro, shine_GrisClaro);
    glTranslatef(0.50, -2.25, 4.50);
    glutSolidSphere(1, 15, 15);
    glFlush();
}

//se mueve en rotacion a x
void keyboard(unsigned char key, int x, int y) {
    switch (key) {   // x,X,y,Y,z,Z uses the glRotatef() function
        case 'a': // Rotates screen on x axis
        case 'A':
            girox = (girox - 1);
            if (girox == -60) {
                girox = girox + 1;
            }
            glutPostRedisplay();
            break;
        case 'b': // Opposite way
        case 'B':
            girox = (girox + 1);
            if (girox == 60) {
                girox = girox - 1;
            }
            glutPostRedisplay();
            break;
        case 'm':
        case 'M':
            break;
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
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}
