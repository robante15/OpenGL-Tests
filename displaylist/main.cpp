#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>

GLuint listName;
GLuint listName2;
GLuint listName3;
GLuint listName4;
static void init (void)
{
    listName = glGenLists (1);
    glNewList (listName, GL_COMPILE);
    glColor3f (1.0, 0.0, 0.0);  /*  configuramos el color rojo  */
    glBegin (GL_TRIANGLES);
    glVertex2f (0.0, 0.0);
    glVertex2f (1.0, 0.0);
    glVertex2f (0.0, 1.0);
    glEnd ();
    glTranslatef (3.5, 0.0, 0.0); /*  movemos el objeto  */
    glEndList ();

    listName2 = glGenLists (1);
    glNewList (listName2, GL_COMPILE);
    glColor3f (1.0, 0.0, 0.0);  /*  configuramos el color rojo  */
    glBegin (GL_TRIANGLES);
    glVertex2f (-0.5, 1.0);
    glVertex2f (0.5, 1.0);
    glVertex2f (0.0, 0.0);
    glEnd ();
    glTranslatef (3.5, 0.0, 0.0); /*  movemos el objeto  */
    glEndList ();

    listName3 = glGenLists (1);
    glNewList (listName3, GL_COMPILE);
    glColor3f (1.0, 0.0, 0.0);  /*  configuramos el color rojo  */
    glutWireTeapot(1);
    glEnd ();
    glTranslatef (3.5, 0.0, 0.0); /*  movemos el objeto  */
    glEndList ();

    listName4 = glGenLists (1);
    glNewList (listName4, GL_COMPILE);
    glColor3f (1.0, 0.0, 0.0);  /*  configuramos el color rojo  */
    glutWireTorus(0.2, 1, 25, 25);
    glEnd ();
    glTranslatef (3.5, 0.0, 0.0); /*  movemos el objeto  */
    glEndList ();

    glShadeModel (GL_FLAT);
}

static void drawLine (void)
{
    glBegin (GL_LINES);
    glVertex2f (0.0, 0.5);
    glVertex2f (15.0, 0.5);
    glEnd ();
}

void display(void)
{
    GLuint i;

    glClear (GL_COLOR_BUFFER_BIT);
    glColor3f (0.0, 1.0, 0.0);
    for (i = 0; i < 2; i++)    /*  dibujamos cuatro triangulos    */
        glCallList (listName);

    for (i = 0; i < 2; i++)    /*  dibujamos cuatro triangulos    */
        glCallList (listName2);

    for (i = 0; i < 2; i++)    /*  dibujamos cuatro triangulos    */
        glCallList (listName3);

    for (i = 0; i < 2; i++)    /*  dibujamos cuatro triangulos    */
        glCallList (listName4);
    drawLine ();  /*  Complementamos con lineas */

    glFlush ();
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        gluOrtho2D (0.0, 2.0, -0.5 * (GLfloat) h/(GLfloat) w,
                    1.5 * (GLfloat) h/(GLfloat) w);
    else
        gluOrtho2D (0.0, 2.0*(GLfloat) w/(GLfloat) h, -0.5, 1.5);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 27:
            exit(0);
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(850, 50);
    glutCreateWindow(argv[0]);
    init ();
    glutReshapeFunc (reshape);
    glutKeyboardFunc (keyboard);
    glutDisplayFunc (display);
    glutMainLoop();
    return 0;
}