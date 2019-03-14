#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 1.0f); //Color azul
    glBegin(GL_TRIANGLES);
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(0.0f, 0.8f, 0.0f);
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(-0.6f, -0.2f, 0.0f);
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(0.6f, -0.2f, 0.0f);

	glEnd();
    glFlush ();

}
void init (void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    
    
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (400, 400);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("-- Ejemplo Poligono --");
    //std::cout << argc << std::endl;
    init ();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
