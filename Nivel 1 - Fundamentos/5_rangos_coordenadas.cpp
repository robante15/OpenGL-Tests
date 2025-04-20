#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

void init(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT); 

    glBegin(GL_TRIANGLES); 
        glColor3f(1.0f, 0.0f, 0.0f); 
        glVertex2f(-0.5f, -0.5f); 
        glColor3f(0.0f, 1.0f, 0.0f); 
        glVertex2f(0.5f, -0.5f); 
        glColor3f(0.0f, 0.0f, 1.0f); 
        glVertex2f(0.0f, 0.5f); 
    glEnd();

    glFlush(); 
}

void reshape(int width, int height){
    glViewport(0, 0, width, height); 

    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity(); 

    gluOrtho2D(-1.0, 2.0, -2.0, 1.0);

    glMatrixMode(GL_MODELVIEW); 
}

int main(int argc, char** argv){
    glutInit(&argc, argv); 
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); 
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT); 
    glutCreateWindow("Rango de Coordenadas en OpenGL 1.1"); 

    glutDisplayFunc(display); 
    glutReshapeFunc(reshape); 

    init(); 

    glutMainLoop(); 
    return 0;
}