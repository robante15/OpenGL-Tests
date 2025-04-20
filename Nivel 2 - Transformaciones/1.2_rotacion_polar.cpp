#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

float angle_1_cube1 = 0.0f; // Rotación del cubo padre
float angle_1_cube2 = 0.0f; // Rotación propia del cubo hijo
float angle_2_cube2 = 0.0f; // Ángulo para traslación polar
float cube2_x = 0.0f; // Coordenada x del cubo hijo
float cube2_z = 0.0f; // Coordenada z del cubo hijo

void checkGLError(const char* operation) {
    GLenum error;
    while ((error = glGetError()) != GL_NO_ERROR) {
        printf("Error después de %s: %s (código: 0x%x)\n", 
               operation, gluErrorString(error), error);
    }
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
}

void drawCube() {
    glBegin(GL_QUADS);
        // Cara frontal (z = 0.5)
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(-0.5, -0.5, 0.5);
        glVertex3f(0.5, -0.5, 0.5);
        glVertex3f(0.5, 0.5, 0.5);
        glVertex3f(-0.5, 0.5, 0.5);
        // Cara trasera (z = -0.5)
        glColor3f(0.0, 1.0, 0.0);
        glVertex3f(-0.5, -0.5, -0.5);
        glVertex3f(-0.5, 0.5, -0.5);
        glVertex3f(0.5, 0.5, -0.5);
        glVertex3f(0.5, -0.5, -0.5);
        // Cara izquierda (x = -0.5)
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(-0.5, -0.5, -0.5);
        glVertex3f(-0.5, -0.5, 0.5);
        glVertex3f(-0.5, 0.5, 0.5);
        glVertex3f(-0.5, 0.5, -0.5);
        // Cara derecha (x = 0.5)
        glColor3f(1.0, 1.0, 0.0);
        glVertex3f(0.5, -0.5, -0.5);
        glVertex3f(0.5, 0.5, -0.5);
        glVertex3f(0.5, 0.5, 0.5);
        glVertex3f(0.5, -0.5, 0.5);
        // Cara superior (y = 0.5)
        glColor3f(1.0, 0.0, 1.0);
        glVertex3f(-0.5, 0.5, -0.5);
        glVertex3f(-0.5, 0.5, 0.5);
        glVertex3f(0.5, 0.5, 0.5);
        glVertex3f(0.5, 0.5, -0.5);
        // Cara inferior (y = -0.5)
        glColor3f(0.0, 1.0, 1.0);
        glVertex3f(-0.5, -0.5, -0.5);
        glVertex3f(0.5, -0.5, -0.5);
        glVertex3f(0.5, -0.5, 0.5);
        glVertex3f(-0.5, -0.5, 0.5);
    glEnd();
    checkGLError("drawCube");
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    checkGLError("glClear");

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    checkGLError("gluLookAt");

    // Cubo padre
    glPushMatrix();
    glTranslatef(2.0f, 0.0f, 0.0f); // Ejercicio 1
    glScalef(2.0f, 0.5f, 1.0f); // Ejercicio 3
    glRotatef(angle_1_cube1, 0.0f, 1.0f, 0.0f); // Ejercicio 2 y 5
    drawCube();
    glPopMatrix();

    // Cubo hijo
    glPushMatrix();
    glRotatef(angle_1_cube2, 0.0f, 1.0f, 0.0f); // Rotación propia
    glTranslatef(cube2_x, 0.0f, cube2_z); // Traslación polar (Ejercicio 5)
    glScalef(0.5f, 0.5f, 0.5f); // Cubo más pequeño
    drawCube();
    glPopMatrix();

    glutSwapBuffers();
    checkGLError("glutSwapBuffers");
}

void reshape(int width, int height) {
    if (height == 0) height = 1;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)width / height, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    checkGLError("reshape");
}

void idle() {
    angle_1_cube1 += 0.5f;
    if (angle_1_cube1 >= 360.0f) angle_1_cube1 -= 360.0f;

    cube2_x = 1.5f * cos(angle_2_cube2);
    cube2_z = 1.5f * sin(angle_2_cube2);
    angle_2_cube2 += 0.05f;
    if (angle_2_cube2 >= 360.0f) angle_2_cube2 -= 360.0f;

    angle_1_cube2 -= 1.0f;
    if (angle_1_cube2 <= -360.0f) angle_1_cube2 += 360.0f;

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Cubo 3D en OpenGL 1.1");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    init();
    glutMainLoop();
    return 0;
}