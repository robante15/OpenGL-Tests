#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    //glPointSize(60);
    glPointSize(60);
    glBegin(GL_POINTS);
    glVertex3f(0.5f,0.5f,0.0f);
    glVertex3f(-0.5f,-0.5f,0.0f);
    glVertex3f(0.7f,0.7f,0.0f);
    glVertex3f(-0.7f,-0.7f,0.0f);
    glEnd();
    glFlush ();

}
void init (void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (600, 600);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("-- Ejemplo Puntos --");
    std::cout << "Hola" << std::endl;
    init ();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
