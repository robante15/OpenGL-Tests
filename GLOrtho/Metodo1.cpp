#include <GL/glut.h>

double centerX = 0, centerY = 0;
double width = 0, height = 0;

void mouse(int button, int state, int mx, int my) {
    // flip mouse y axis so up is +y
    my = glutGet(GLUT_WINDOW_HEIGHT) - my;

    // convert mouse coords to (-1/2,-1/2)-(1/2, 1/2) box
    double x = (mx / (double) glutGet(GLUT_WINDOW_WIDTH)) - 0.5;
    double y = (my / (double) glutGet(GLUT_WINDOW_HEIGHT)) - 0.5;

    if (GLUT_UP == state) {
        double preX = (x * width);
        double preY = (y * height);

        double zoomFactor = 1.5;
        if (button == GLUT_LEFT_BUTTON) {
            // zoom in
            width /= zoomFactor;
            height /= zoomFactor;
        }
        if (button == GLUT_RIGHT_BUTTON) {
            // zoom out
            width *= zoomFactor;
            height *= zoomFactor;
        }

        double postX = (x * width);
        double postY = (y * height);

        // recenter
        centerX += (preX - postX);
        centerY += (preY - postY);
    }

    glutPostRedisplay();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho
            (
                    centerX - (width / 2.0),
                    centerX + (width / 2.0),
                    centerY - (height / 2.0),
                    centerY + (height / 2.0),
                    -1,
                    1
            );

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3ub(255, 0, 0);
    glBegin(GL_TRIANGLES);
    glVertex2i(0, 0);
    glVertex2i(150, 0);
    glVertex2i(0, 150);
    glVertex2i(0, 0);
    glVertex2i(-150, 0);
    glVertex2i(0, -150);
    glEnd();

    glutSwapBuffers();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(1366, 768);
    glutCreateWindow("GLUT");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);

    width = glutGet(GLUT_WINDOW_WIDTH);
    height = glutGet(GLUT_WINDOW_HEIGHT);

    glutMainLoop();
    return 0;
}
