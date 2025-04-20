#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

#define BODY_HEIGHT 4.0f
#define BODY_WIDTH 2.5f
#define BODY_LENGTH 1.0f
#define ARM_HEIGHT 3.5f
#define ARM_WIDTH 1.0f
#define ARM_LENGTH 1.0f
#define LEG_HEIGHT 4.5f
#define LEG_WIDTH 1.0f
#define LEG_LENGTH 1.0f
#define HEAD_RADIUS 1.1f

void init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Establece el color de fondo
}

void drawGuy()
{
    // Dibujamos el cuerpo
    glTranslatef(0, BODY_HEIGHT / 2, 0);
    glPushMatrix();
    glScalef(BODY_WIDTH, BODY_HEIGHT, BODY_LENGTH);
    glColor3f(0.0, 0.3, 0.8);
    glutSolidCube(1);
    glPopMatrix();
    // Dibujamos el brazo derecho
    glPushMatrix();
    glTranslatef(-(BODY_WIDTH) / 2, (BODY_HEIGHT - ARM_HEIGHT) / 2, 0);
    glTranslatef(0, ARM_HEIGHT / 2, 0);
    glRotatef(-30, 0, 0, 1);
    glTranslatef(0, -ARM_HEIGHT / 2, 0);
    glPushMatrix();
    glScalef(ARM_WIDTH, ARM_HEIGHT, ARM_LENGTH);
    glutSolidCube(1);
    glPopMatrix();
    // ya tenemos el brazo... la mano
    glTranslatef(0, -(ARM_HEIGHT + ARM_WIDTH) / 2, 0);
    glColor3f(1, 0.6, 0.6);
    glScalef(ARM_WIDTH, ARM_WIDTH, ARM_LENGTH);
    glutSolidCube(1);
    glPopMatrix();
    // Dibujamos el brazo izquierdo
    glColor3f(0.0, 0.3, 0.8);
    glPushMatrix();
    glTranslatef((BODY_WIDTH) / 2, (BODY_HEIGHT - ARM_HEIGHT) / 2, 0);
    glTranslatef(0, ARM_HEIGHT / 2, 0);
    glRotatef(30, 0, 0, 1);
    glTranslatef(0, -ARM_HEIGHT / 2, 0);
    glPushMatrix();
    glScalef(ARM_WIDTH, ARM_HEIGHT, ARM_LENGTH);
    glutSolidCube(1);
    glPopMatrix();
    glTranslatef(0, -(ARM_HEIGHT + ARM_WIDTH) / 2, 0);
    glColor3f(1, 0.6, 0.6);
    glScalef(ARM_WIDTH, ARM_WIDTH, ARM_LENGTH);
    glutSolidCube(1);
    glPopMatrix();
    // Dibujamos la pierna derecha
    glColor3f(0.0, 0.3, 0.8);
    glPushMatrix();
    glTranslatef(-(BODY_WIDTH - LEG_WIDTH) / 2, -(BODY_HEIGHT + LEG_HEIGHT) / 2, 0);
    glPushMatrix();
    glScalef(LEG_WIDTH, LEG_HEIGHT, LEG_LENGTH);
    glutSolidCube(1);
    glPopMatrix();
    // ahora el píe
    glTranslatef(0, -(LEG_HEIGHT + LEG_WIDTH) / 2, LEG_LENGTH);
    glColor3f(0.3, 0.4, 0.4);
    glScalef(LEG_WIDTH, LEG_WIDTH, LEG_LENGTH * 2);
    glutSolidCube(1);
    glPopMatrix();
    // Dibujamos la pierna izquierda
    glColor3f(0.0, 0.3, 0.8);
    glPushMatrix();
    glTranslatef((BODY_WIDTH - LEG_WIDTH) / 2, -(BODY_HEIGHT + LEG_HEIGHT) / 2, 0);
    glPushMatrix();
    glScalef(LEG_WIDTH, LEG_HEIGHT, LEG_LENGTH);
    glutSolidCube(1);
    glPopMatrix();
    // ahora el píe
    glTranslatef(0, -(LEG_HEIGHT + LEG_WIDTH) / 2, LEG_LENGTH);
    glColor3f(0.3, 0.4, 0.4);
    glScalef(LEG_WIDTH, LEG_WIDTH, LEG_LENGTH * 2);
    glutSolidCube(1);
    glPopMatrix();
    // Dibujamos la cabeza
    glColor3f(1, 0.6, 0.6);
    glPushMatrix();
    glTranslatef(0, BODY_HEIGHT / 2 + HEAD_RADIUS * 3 / 4, 0);
    glutSolidSphere(HEAD_RADIUS, 10, 10);
    glPopMatrix();
}

void display()
{
    glDepthFunc(GL_LEQUAL);                             // Establece la función de comparación de profundidad
    glEnable(GL_DEPTH_TEST);                            // Habilita el test de profundidad
    glClearDepth(1.0f);                                 // Limpia el buffer de profundidad
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpia el buffer de color y profundidad

    glTranslatef(0.0f, 0.0f, -16.0f);
    drawGuy(); // Dibuja el personaje

    glFlush();
}

void reshape(int width, int height)
{
    if (height == 0)
        height = 1;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float aspect = (float)width / (float)height;
    gluPerspective(60.0f, aspect, 0.1f, 100.0f); // Proyección perspectiva
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    // Inicializa GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);    // Establece el modo de visualización
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT); // Establece el tamaño de la ventana
    glutCreateWindow("Simple Guy");                  // Crea la ventana

    init(); // Inicializa OpenGL

    glutDisplayFunc(display); // Registra la función de visualización
    glutReshapeFunc(reshape); // Registra la función de cambio de tamaño

    glutMainLoop(); // Entra en el bucle principal de GLUT

    return 0;
}