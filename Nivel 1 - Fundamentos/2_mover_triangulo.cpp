#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "utils.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define cyan RGBtoGLCOLOR(0, 255, 255)
#define magenta RGBtoGLCOLOR(255, 0, 255)
#define yellow RGBtoGLCOLOR(255, 255, 0)

void init(){
    glClearColor(0.0f, 0.0f, 0.0f, 0.1f);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
        glColor3fv(yellow.rgb);
        glVertex2f(-1.0f, 0.0f);
        glColor3fv(cyan.rgb);
        glVertex2f(0.0f, 0.0f);
        glColor3fv(magenta.rgb);
        glVertex2f(-0.5f, 1.0f);
    glEnd();

    glBegin(GL_TRIANGLES);
        glColor3fv(yellow.rgb);
        glVertex2f(0.0f, -1.0f);
        glColor3fv(cyan.rgb);
        glVertex2f(1.0f, -1.0f);
        glColor3fv(magenta.rgb);
        glVertex2f(0.5f, 0.0f);
    glEnd();

    glBegin(GL_TRIANGLES);
        glColor3fv(yellow.rgb);
        glVertex2f(-0.25f, -0.25f);
        glColor3fv(cyan.rgb);
        glVertex2f(0.25f, -0.25f);
        glColor3fv(magenta.rgb);
        glVertex2f(0.0f, 0.25f);
    glEnd();

    glFlush();
}

void reshape(int width, int height){
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(-1.0, 1.0, -1.0, 1.0); // Define el área de visualización
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Ejercicio 1. Triangulo CMY en OpenGL 1.1");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    init();

    glutMainLoop();
    return 0;
}