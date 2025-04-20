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

float camera_x = 0.0f;
float camera_y = 0.0f;
float camera_z = 5.0f;

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

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    checkGLError("glClear");

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camera_x, camera_y, camera_z,  // Posición de la cámara
              0.0, 0.0, 0.0,  // Punto al que mira
              0.0, 1.0, 0.0); // Vector arriba
    checkGLError("gluLookAt");

    glPushMatrix();
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f); // Rotación alrededor del eje X
    glTranslatef(1.0f, 0.0f, 0.0f); // Traslación del cilindro
    glColor3f(1.0, 0.0, 0.0); // Color rojo
    gluCylinder ( gluNewQuadric(), 0.3f, 0.3f, 1.0f, 20, 10); // Dibuja un cilindro
    glPopMatrix();

    glPushMatrix();
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f); // Rotación alrededor del eje X
    glTranslatef(-1.0f, 0.0f, 0.0f); // Traslación del cilindro
    glColor3f(0.0, 1.0, 0.0); // Color rojo
    gluCylinder ( gluNewQuadric(), 0.3f, 0.0f, 1.0f, 20, 10); // Dibuja un cono
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

void input(unsigned char key, int x, int y){
    switch(key){
        case 27: // Tecla ESC
            exit(0); // Sale del programa
            break;
        case 'w': // Tecla 'w'
            if(camera_z > 1.0f) {
                camera_z -= 0.1f; // Mueve la cámara hacia adelante
                glutPostRedisplay();
            }
            break;
        case 's': // Tecla 's'
            camera_z += 0.1f;
            glutPostRedisplay();
            break;
        case 'a': // Tecla 'a'
            camera_x -= 0.1f; // Mueve la cámara hacia la izquierda
            glutPostRedisplay();
            break;
        case 'd': // Tecla 'd'
            camera_x += 0.1f; // Mueve la cámara hacia la derecha
            glutPostRedisplay();
            break;
    }

}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // Doble búfer y profundidad
    glutInitWindowSize(800, 600);
    glutCreateWindow("Cubo 3D en OpenGL 1.1");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(input);
    init();
    glutMainLoop();
    return 0;
}