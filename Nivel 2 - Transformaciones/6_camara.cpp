#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

float angle_1_cube1 = 0.0f; // Ángulo de rotación

float angle_1_cube2 = 0.0f;
float angle_2_cube2 = 0.0f;
float cube2_x = 0.0f;
float cube2_z = 0.0f;

void checkGLError(const char *operation)
{
    GLenum error;
    while ((error = glGetError()) != GL_NO_ERROR)
    {
        printf("Error después de %s: %s (código: 0x%x)\n",
               operation, gluErrorString(error), error);
    }
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST); // Habilitar búfer de profundidad
}

void drawCube()
{
    glBegin(GL_QUADS);
    // Cara frontal (z = 0.5)
    glColor3f(1.0, 0.0, 0.0); // Rojo
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    // Cara trasera (z = -0.5)
    glColor3f(0.0, 1.0, 0.0); // Verde
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(0.5, -0.5, -0.5);
    // Cara izquierda (x = -0.5)
    glColor3f(0.0, 0.0, 1.0); // Azul
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    // Cara derecha (x = 0.5)
    glColor3f(1.0, 1.0, 0.0); // Amarillo
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(0.5, -0.5, 0.5);
    // Cara superior (y = 0.5)
    glColor3f(1.0, 0.0, 1.0); // Magenta
    glVertex3f(-0.5, 0.5, -0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(0.5, 0.5, -0.5);
    // Cara inferior (y = -0.5)
    glColor3f(0.0, 1.0, 1.0); // Cian
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(-0.5, -0.5, 0.5);
    glEnd();
    checkGLError("drawCube");
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    checkGLError("glClear");

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(3.0, 3.0, 3.0,  // Posición de la cámara
              0.0, 0.0, 0.0,  // Punto al que mira
              0.0, 1.0, 0.0); // Vector arriba
    checkGLError("gluLookAt");

    glPushMatrix();
    glRotatef(angle_1_cube1, 0.0f, 1.0f, 0.0f); // Rotación alrededor del eje Y
    drawCube();
    glPopMatrix();

    glPushMatrix();
    glRotatef(angle_1_cube2, 0.0f, 1.0f, 0.0f); // Rotación alrededor del eje Y
    glTranslatef(cube2_x, -1.5f, cube2_z); // Traslación del segundo cubo
    glScalef(0.5f, 0.5f, 0.5f); // Escalado del primer cubo
    drawCube();
    glPopMatrix();

    glutSwapBuffers(); // Usar doble búfer
    checkGLError("glutSwapBuffers");
}

void reshape(int width, int height)
{
    if (height == 0)
        height = 1;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)width / height, 0.1, 100.0); // Proyección perspectiva
    glMatrixMode(GL_MODELVIEW);
    checkGLError("reshape");
}

void idle()
{
    angle_1_cube1 += 0.5f; // Incrementar ángulo para animación
    if (angle_1_cube1 >= 360.0f)
        angle_1_cube1 -= 360.0f;

    cube2_x = 1.5f * cos(angle_2_cube2);
    cube2_z = 1.5f * sin(angle_2_cube2);
    angle_2_cube2 += 0.05f; // Incrementar ángulo para animación
    if (angle_2_cube2 >= 360.0f)
        angle_2_cube2 -= 360.0f;

    angle_1_cube2 -= 1.0f; // Incrementar ángulo para animación
    if (angle_1_cube2 <= -360.0f)
        angle_1_cube2 += 360.0f;
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // Doble búfer y profundidad
    glutInitWindowSize(800, 600);
    glutCreateWindow("Cubo 3D en OpenGL 1.1");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    init();
    glutMainLoop();
    return 0;
}