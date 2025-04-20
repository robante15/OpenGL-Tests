#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>

float angle_y = 0.0f; // Ángulo de rotación

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
    gluLookAt(0.0, 0.0, 5.0,  // Posición de la cámara
              0.0, 0.0, 0.0,  // Punto al que mira
              0.0, 1.0, 0.0); // Vector arriba
    checkGLError("gluLookAt");

    glPushMatrix();
    glRotatef(angle_y, 0.0f, 1.0f, 0.0f); // Rotar alrededor del eje y
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
    angle_y += 0.5f; // Incrementar ángulo para animación
    if (angle_y >= 360.0f)
        angle_y -= 360.0f;
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