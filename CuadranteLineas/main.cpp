#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    //Creación de una linea, que va a comenzar en (-5,5) y termina en (5,-5)
    glBegin(GL_LINES);
    glVertex2f(-5, 5);
    glVertex2f(5, -5);
    
    glBegin(GL_LINES);
    glVertex2f(-5, -5);
    glVertex2f(5, 5);
	glEnd();
    glFlush ();

}
void init (void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-5.0, 5.0, -5.0, 5.0, -5.0, 5.0);
    //glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); // Por defecto
    //glOrtho(0.0, 1.0, 0.0, 1.0, 1.0, 0.0);  //Primer cuadrante
    //glOrtho(1.0, 0.0, 0.0, 1.0, 1.0, 0.0);  //Segundo cuadrante
    //glOrtho(1.0, 0.0, 1.0, 0.0, 1.0, 0.0);  //Tercero cuadrante
    //glOrtho(0.0, 1.0, 1.0, 0.0, 1.0, 0.0);  //Cuarto cuadrante
    
    
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (400, 400);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("-- Ejemplo Lineas --");
    //std::cout << argc << std::endl;
    init ();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
