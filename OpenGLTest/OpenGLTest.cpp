#include <GL/gl.h>
#include <GL/glut.h>

void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT);
    glColor3f (1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3f (0.25, 0.25,0.0);
    glVertex3f (0.75, 0.25,0.0);
    glVertex3f (0.50, 0.75,0.0);
    //glVertex3f (0.25, 0.75,0.0);
    glEnd();
    glFlush();

}
void init (void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (600, 400);
    glutInitWindowPosition (200, 200);
    glutCreateWindow ("Cuadrado OpenGL");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
