#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "utils.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

void init(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_QUADS);
        glColor3f(1.0f, 0.0f, 0.0f); // Color rojo
        glVertex2f(-0.5f, -0.5f); // Vértice inferior izquierdo
        glColor3f(0.0f, 1.0f, 0.0f); // Color verde
        glVertex2f(0.5f, -0.5f); // Vértice inferior derecho
        glColor3f(0.0f, 0.0f, 1.0f); // Color azul
        glVertex2f(0.5f, 0.5f); // Vértice superior derecho
        glColor3f(1.0f, 1.0f, 0.0f); // Color amarillo
        glVertex2f(-0.5f, 0.5f); // Vértice superior izquierdo
    glEnd();

    glBegin(GL_LINES);
        glColor3f(1.0f, 1.0f, 1.0f); // Color blanco
        glVertex2f(-0.75f, -0.75f); // Vértice inferior izquierdo
        glVertex2f(-0.75f, 0.75f); // Vértice superior derecho
    glEnd();

    glBegin(GL_POINTS);
        glColor3f(1.0f, 0.0f, 1.0f); // Color magenta
        glVertex2f(0.75f, 0.75f); // Punto en el centro
    glEnd();

    glFlush();
}

void reshape(int width, int height){
    if (height == 0) height = 1;  
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    float aspect = (float)width / (float)height;
    if (width >= height) {
        gluOrtho2D(-1.0f * aspect, 1.0f * aspect, -1.0f, 1.0f);
    } else {
        gluOrtho2D(-1.0f, 1.0f, -1.0f / aspect, 1.0f / aspect);
    }

    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv){
    // Inicializa GLUT
    glutInit(&argc, argv); 
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // Establece el modo de visualización
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT); // Establece el tamaño de la ventana
    glutCreateWindow("Cuadrado en OpenGL 1.1"); // Crea la ventana

    glutDisplayFunc(display); // Registra la función de visualización
    glutReshapeFunc(reshape); // Registra la función de cambio de tamaño

    init(); // Inicializa OpenGL

    glutMainLoop(); // Entra en el bucle principal de GLUT
    return 0;
}