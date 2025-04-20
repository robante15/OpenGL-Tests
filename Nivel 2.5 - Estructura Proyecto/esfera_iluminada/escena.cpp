#include <GL/glut.h>
#include <stdio.h>
#include <chrono>
#include <thread>
#include "sphere.h"

float *pos = nullptr;
TSphere *sphere = nullptr;
GLUquadric* quad = nullptr;

void initgl()
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    quad = gluNewQuadric();
    gluQuadricDrawStyle(quad, GLU_FILL);
    gluQuadricNormals(quad, GLU_SMOOTH);

    // Inicializa la esfera
    sphere = new TSphere(5.0f, 0.1f); // maxpos = 5.0f (Mitad del cubo de referencia), speed = 0.1f
}

void checkGLError(const char *operation)
{
    GLenum error;
    while ((error = glGetError()) != GL_NO_ERROR)
    {
        printf("Error después de %s: %s (código: 0x%x)\n",
               operation, gluErrorString(error), error);
    }
}

void reshape(int width, int height)
{
    if (height == 0)
        height = 1;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f, (float)width / height, 1.0f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    checkGLError("reshape");
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    checkGLError("glClear");

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(3.0f, 3.0f, 14.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    checkGLError("gluLookAt");

    // Dibuja el cubo de referencia (Wireframe)
    glColor3f(1.0f, 1.0f, 1.0f);
    glutWireCube(10.0f);

    // Dibujar la esfera rebotando
    if (sphere) // Verifica si la esfera está inicializada
    {
        glPushMatrix();
        glColor3f(0.0f, 0.0f, 1.0f);
        pos = sphere->getPosv();
        if (pos)
        {
            glTranslatef(pos[0], pos[1], pos[2]);
            gluSphere(quad, 1.0f, 10, 10);
        }
        else
        {
            printf("Error: Posición de la esfera no válida\n");
        }
        glPopMatrix();
    }
    else
    {
        printf("Error: Esfera no inicializada\n");
    }

    glutSwapBuffers();
    checkGLError("glutSwapBuffers");
}
void idle(void)
{
    if (sphere)
    {
        sphere->updatePosition();
    }
    else
    {
        printf("Error: Esfera no inicializada\n");
    }
    // Espera 33 ms (aproximadamente 30 FPS)
    std::this_thread::sleep_for(std::chrono::milliseconds(33));
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 27: // ESC
            delete sphere;
            exit(0);
        case '+':
            if (sphere) sphere->modifySpeed(0.05f);
            break;
        case '-':
            if (sphere) sphere->modifySpeed(-0.05f);
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Esfera rebotando");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutKeyboardFunc(keyboard);
    initgl();
    glutMainLoop();
    delete sphere; // Libera la memoria de la esfera
    return 0;
}