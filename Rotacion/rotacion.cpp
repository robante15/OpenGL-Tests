
//ROBERTO HERBERTH MALTEZ GUARDADO - MG16071

//EJERCICO #1 - COLUMPIO MECEDOR

#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>

#include "tools/Materials.h"
#include "tools/Lighting.h"

static int girox = 0;
Materials materials;

void init(void){

    //GLfloat light_position[] = {1,0,0,0}; //luz derecha
    GLfloat light_position[] = {1,0,5,0};
    glEnable(GL_LIGHTING); //activa la fuente de luz
    glEnable(GL_LIGHT0); //Activamos las luces en 0
    glEnable(GL_LIGHT1);

    glDepthFunc(GL_LESS); //comparación de profundidad
    glEnable(GL_DEPTH_TEST); //activa GL_DEPTH_TES
    // Queremos que se dibujen las caras frontales
    // y con un color solido de relleno.
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void reshape(int w, int h){
    glViewport(0, 0,  (GLsizei) w, (GLsizei) h);
    // Activamos la matriz de proyeccion.
    glMatrixMode(GL_PROJECTION);
    // "limpiamos" esta con la matriz identidad.
    glLoadIdentity();
    // Usamos proyeccion ortogonal
    glOrtho(-300, 300, -300, 300, -300, 300);
    // Activamos la matriz de modelado/visionado.
    glMatrixMode(GL_MODELVIEW);
    // "Limpiamos" la matriz
    glLoadIdentity();
}

void columpio(){

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //rotacion
    glRotated(45.0, 1.0, 0.0, 0.0);
    glRotated(30.0, 0.0, 1.0, 0.0);

    glBegin(GL_QUADS);

    //para el techo flotante
    //cara de arriba (arriba)
    glVertex3f(200.0f, 280.0f, -10.0f);
    glVertex3f(-200.0f, 280.0f, -10.0f);
    glVertex3f(-200.0f, 280.0f, 10.0f);
    glVertex3f(200.0f, 280.0f, 10.0f);

    //cara de arriba (abajo)
    glVertex3f(200.0f, 250.0f, -10.0f);
    glVertex3f(-200.0f, 250.0f, -10.0f);
    glVertex3f(-200.0f, 250.0f, 10.0f);
    glVertex3f(200.0f, 250.0f, 10.0f);

    //cara de arriba (enfrente)
    glVertex3f(200.0f, 280.0f, 10.0f);
    glVertex3f(-200.0f, 280.0f, 10.0f);
    glVertex3f(-200.0f, 250.0f, 10.0f);
    glVertex3f(200.0f, 250.0f, 10.0f);


    //cara de arriba (izquierda)
    glVertex3f(-200.0f, 280.0f, 10.0f);
    glVertex3f(-200.0f, 280.0f, -10.0f);
    glVertex3f(-200.0f, 250.0f, -10.0f);
    glVertex3f(-200.0f, 250.0f, 10.0f);

    //cara de arriba (derecha)
    glVertex3f(200.0f, 280.0f, -10.0f);
    glVertex3f(200.0f, 280.0f, 10.0f);
    glVertex3f(200.0f, 250.0f, 10.0f);
    glVertex3f(200.0f, 250.0f, -10.0f);

    //cara de arriba (atras)
    glVertex3f(200.0f, 280.0f, -10.0f);
    glVertex3f(-200.0f, 280.0f, -10.0f);
    glVertex3f(-200.0f, 250.0f, -10.0f);
    glVertex3f(200.0f, 250.0f, -10.0f);
    //fin del techo flotante


    // cara izquierda
    //cara izquierda (adelante)
    materials.setMaterialColor(88, 90, 103, 10);
    //barra izquierda
    glVertex3f(-200.1f, 20.0f, 40.0f);
    glVertex3f(-200.1f, 20.0f, -40.0f);
    glVertex3f(-200.1f, -20.0f, -50.0f);
    glVertex3f(-200.1f, -20.0f, 50.0f);


    glVertex3f(-185.0f, 250.0f, 10.0f);
    glVertex3f(-185.0f, 250.0f, -10.0f);
    glVertex3f(-185.0f, -250.0f, -80.0f);
    glVertex3f(-185.0f, -250.0f, 80.0f);


    //cara izquierda (atras)
    glVertex3f(-200.0f, 250.0f, 10.0f);
    glVertex3f(-200.0f, 250.0f, -10.0f);
    glVertex3f(-200.0f, -250.0f, -80.0f);
    glVertex3f(-200.0f, -250.0f, 80.0f);

    //cara izquierda (enfrente)
    glVertex3f(-185.0f, 250.0f, 10.0f);
    glVertex3f(-200.0f, 250.0f, 10.0f);
    glVertex3f(-200.0f, -250.0f, 80.0f);
    glVertex3f(-185.0f, -250.0f, 80.0f);
    //fin de cara izquierda

    // cara derecha
    materials.setMaterialColor(148, 148, 148, 100);

    //barra derecha
    glVertex3f(183.0f, 20.0f, -40.0f);
    glVertex3f(183.0f, 20.0f, 40.0f);
    glVertex3f(183.0f, -20.0f, 50.0f);
    glVertex3f(183.0f, -20.0f, -50.0f);

    glVertex3f(200.0f, 250.0f, -10.0f);
    glVertex3f(200.0f, 250.0f, 10.0f);
    glVertex3f(200.0f, -250.0f, 100.0f);
    glVertex3f(200.0f, -250.0f, -100.0f);

    //cara derecha (adelante)
    glVertex3f(185.0f, 250.0f, -10.0f);
    glVertex3f(185.0f, 250.0f, 10.0f);
    glVertex3f(185.0f, -250.0f, 100.0f);
    glVertex3f(185.0f, -250.0f, -100.0f);

    //cara derecha (enfrente)
    glVertex3f(185.0f, 250.0f, 10.0f);
    glVertex3f(200.0f, 250.0f, 10.0f);
    glVertex3f(200.0f, -250.0f, 100.0f);
    glVertex3f(185.0f, -250.0f, 100.0f);
    //fin de la cara derecha


    //tipo sombra (izquiera )
    materials.setMaterial(materials.BLACK_PLASTIC);
    glVertex3f(-200.1f, 230.0f, 0.0f);
    glVertex3f(-200.1f, 230.0f, -0.0f);
    glVertex3f(-200.1f, -249.0f, -50.0f);
    glVertex3f(-200.1f, -249.0f, 50.0f);

    //tipo sombra (derecha)
    glVertex3f(184.0f, 230.0f, -0.0f);
    glVertex3f(184.0f, 230.0f, 0.0f);
    glVertex3f(184.0f, -249.0f, 50.0f);
    glVertex3f(184.0f, -249.0f, -50.0f);
    glPopMatrix();

    glPopMatrix();
    glEnd();


}

//esta es la pare que se mueve
void banca(){
    glBegin(GL_QUADS);

    //banca
    materials.setMaterial(materials.BRONZE);
    glVertex3f(50.0f, -50.0f, 50.0f);
    glVertex3f(-100.0f, -50.0f, 50.0f);
    glVertex3f(-100.0f, -50.0f, -0.0f);
    glVertex3f(50.0f, -50.0f, -0.0f);
    //fin de la banca

    // respaldo
    materials.setMaterial(materials.GOLD);
    glVertex3f(50.0f, -50.0f, -0.0f);
    glVertex3f(-100.0f, -50.0f, -0.0f);
    glVertex3f(-100.0f, 50.0f, -0.0f);
    glVertex3f(50.0f, 50.0f, -0.0f);


    materials.setMaterial(materials.BRONZE);
    //cuerda dereca
    glVertex3f(5.0f, -0.0f, -0.0f);
    glVertex3f(-0.0f, -0.0f, -0.0f);
    glVertex3f(-0.0f, 250.0f, -0.0f);
    glVertex3f(5.0f, 250.0f, -0.0f);

    //cuerda izquierda
    glVertex3f(-50.0f, 250.0f, 10.0f);
    glVertex3f(-50.0f, 250.0f, -0.0f);
    glVertex3f(-50.0f, -0.0f, -0.0f);
    glVertex3f(-50.0f, -0.0f, 10.0f);
    glPopMatrix();
    glEnd();
}

void display(void){

// Propiedades del material

    GLfloat mat_ambient[] = { 0.329412f, 0.223529f, 0.027451f};
    GLfloat mat_diffuse[] = { 0.780392f, 0.568627f, 0.113725f};
    GLfloat mat_specular[] = { 0.992157f, 0.941176f, 0.807843f};
    GLfloat shine[] = {27.8974f};

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode( GL_MODELVIEW_MATRIX );
    glLoadIdentity();

    glPushMatrix();
//setMaterial
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shine);

    columpio();

    glPushMatrix ();
    
    
    //aqui es donde se comienza a move
    //tenes que poner la parte mas alta en y donde comienza tu codigo
    //y de la misma forma que tengo

    glTranslated(+0,+250,0);
    glRotated ((GLdouble) girox, 1.0, 0.0, 0.0);
    glTranslated(-0,-250,0);
    banca();

    glPopMatrix();
    glFlush();
}

//se mueve en rotacion a x
void keyboard (unsigned char key, int x, int y){
    switch (key) {   // x,X,y,Y,z,Z uses the glRotatef() function
        case 'a': // Rotates screen on x axis
        case 'A':
            girox = (girox - 1);
            if(girox == -40){
                girox = girox + 1;

            }
            glutPostRedisplay();
            break;
        case 'b': // Opposite way
        case 'B':
            girox = (girox + 1);
            if(girox == 10){
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

int main(int argc, char **argv){
// Inicializo OpenGL
    glutInit(&argc, argv);
// Activamos buffer simple y colores del tipo RGB
    glutInitDisplayMode (GLUT_RGB | GLUT_DEPTH);
// Definimos una ventana de medidas 800 x 600 como ventana
// de visualizacion en pixels
    glutInitWindowSize (800, 600);
// Posicionamos la ventana en la esquina superior izquierda de
// la pantalla.
    glutInitWindowPosition (0, 0);
// Creamos literalmente la ventana y le adjudicamos el nombre que se
// observara en su barra de titulo.
    glutCreateWindow ("COLUMPIO");
// Inicializamos el sistema
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutKeyboardFunc(keyboard); // set window's key callback

    glutMainLoop();
    return 0;
}
