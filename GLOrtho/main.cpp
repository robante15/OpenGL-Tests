// g++ main.cpp -o main -lglut -lGL && ./main
#include <iostream>
#include <GL/glut.h>
#include <cmath>

int btn;
double baseX, baseY;
double baseWidth, baseHeight;

double centerX = 0, centerY = 0;
double width = 0, height = 0;

void getMouseCoords(int mx, int my, double &x, double &y) {
    // flip mouse y axis so up is +y
    my = glutGet(GLUT_WINDOW_HEIGHT) - my;

    // convert mouse coords to (-1/2,-1/2)-(1/2, 1/2) box
    x = (mx / (double) glutGet(GLUT_WINDOW_WIDTH)) - 0.5;
    y = (my / (double) glutGet(GLUT_WINDOW_HEIGHT)) - 0.5;

}

void mouse(int button, int state, int mx, int my) {
    baseWidth = width;
    baseHeight = height;
    btn = button;
    getMouseCoords(mx, my, baseX, baseY);
}

void motion(int mx, int my) {
    if (btn == GLUT_LEFT_BUTTON) {
        double x, y;
        getMouseCoords(mx, my, x, y);

        double preX = (baseX * width);
        double preY = (baseY * height);

        double zoomFactor = exp(baseY - y);
        width = baseWidth * zoomFactor;
        height = baseHeight * zoomFactor;

        double postX = (baseX * width);
        double postY = (baseY * height);

        // recenter
        centerX += (preX - postX);
        centerY += (preY - postY);
    }

    if (btn == GLUT_RIGHT_BUTTON) {
        width = glutGet(GLUT_WINDOW_WIDTH);
        height = glutGet(GLUT_WINDOW_HEIGHT);
        centerX = 0;
        centerY = 0;
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
    glutInitWindowSize(1366, 720);
    glutCreateWindow("GLUT");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);

    width = glutGet(GLUT_WINDOW_WIDTH);
    height = glutGet(GLUT_WINDOW_HEIGHT);

    glutMainLoop();
    return 0;
}
