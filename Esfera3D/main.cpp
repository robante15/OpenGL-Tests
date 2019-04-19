#include <GL/gl.h>
#include <GL/glut.h>

static void plano(GLfloat grid) {
    glColor3f(1, 1, 1);
    glLineWidth(1);
    glBegin(GL_LINES);


    glVertex3f(0, -10, 0);
    glVertex3f(0, 10, 0);

    glVertex3f(10, 0, 0);
    glVertex3f(-10, 0, 0);

    for (GLfloat i = -10; i <= 10; ++i) {

        glVertex3f(i, -1 * grid, 0);
        glVertex3f(i, grid, 0);

        glVertex3f(grid, i, 0);
        glVertex3f(-1 * grid, i, 0);
    }

    glEnd();
}

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 1.0);
    glLoadIdentity();             /* clear the matrix */
    /* viewing transformation  */
    gluLookAt(1.0, 2.0, 3.0,
              0.0, 0.0, 0.0,
              1.0, 0.0, 0.0);

    glScalef(1.0, 1.0, 1.0);      /* modeling transformation */
    //glutSolidCone(1, 1, 10, 10);
    //glutWireCone(1, 1, 10, 10);
    plano(0.1);
    //glutWireTorus(0.5,1,10,10);
    //glutWireTeapot(1);
    //glutWireSphere(0.8, 10, 10);
    glFlush();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
    glMatrixMode(GL_MODELVIEW);
}


int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
