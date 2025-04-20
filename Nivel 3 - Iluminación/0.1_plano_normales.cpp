#include <GL/glut.h>
#include <stdlib.h>

#define SINGLE_NORMAL

void init(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void display(void)
{
    GLfloat mat_color[] = {0.0, 1.0, 1.0, 1.0};
    GLfloat light_color[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_ambient[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat normal[] = {0.0, 1.0, 0.0};
    GLfloat light_dir[] = {0.0, 1.0, 0.0, 0.0};
    
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_LIGHTING);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_color);
    glEnable(GL_LIGHT0);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_color);
    glTranslatef(-0.3, -0.6, -4.0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_dir);
    glBegin(GL_QUADS);
#ifdef SINGLE_NORMAL
    glNormal3fv(normal);
#else
    glNormal3f(1.0, 1.0, -1.0);
#endif
    glVertex3f(-1.0, 0.0, -1.0);
    glNormal3fv(normal);
    glVertex3f(-1.0, 0.0, 1.0);
#ifdef SINGLE_NORMAL
    glNormal3fv(normal);
#else
    glNormal3f(-1.0, 1.0, -1.0);
#endif
    glVertex3f(1.0, 0.0, 1.0);
    glNormal3fv(normal);
    glVertex3f(1.0, 0.0, -1.0);
    glEnd();
    glFlush();
    //sleep(20);
    //exit(0);
}

void reshape(int width, int height)
{
    if (height == 0) height = 1;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)width / (GLfloat)height, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Normales en OpenGL");
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    init();

    glutMainLoop();
    return 0;
}