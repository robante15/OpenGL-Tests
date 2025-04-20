#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "utils.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define CYAN RGBtoGLCOLOR(0, 255, 255)
#define MAGENTA RGBtoGLCOLOR(255, 0, 255)
#define YELLOW RGBtoGLCOLOR(255, 255, 0)

void init(){
    glClearColor(0.0f, 0.0f, 0.0f, 0.1f);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
        glColor3fv(YELLOW.rgb);
        glVertex2f(-0.5f, -0.5f);
        glColor3fv(CYAN.rgb);
        glVertex2f(0.5f, -0.5f);
        glColor3fv(MAGENTA.rgb);
        glVertex2f(0.0f, 0.5f);
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