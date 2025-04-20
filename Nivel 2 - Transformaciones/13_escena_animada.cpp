#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

float angle_1_cube1 = 0.0f; // Rotación de objetos
float angle_1_cube2 = 0.0f; // Rotación propia de la esfera
float angle_2_cube2 = 0.0f; // Ángulo para traslación polar
float cube2_x = 0.0f;       // Coordenada x de la esfera
float cube2_z = 0.0f;       // Coordenada z de la esfera
float camera_x = 0.0f;      // Posición de la cámara
float camera_y = 0.0f;      // Posición de la cámara
float camera_z = 3.0f;      // Posición de la cámara
bool depth_test = true;     // Estado del búfer de profundidad
GLUquadric *quad = NULL;    // Objeto GLUquadric reutilizable

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
    glEnable(GL_DEPTH_TEST);

    quad = gluNewQuadric();
    gluQuadricDrawStyle(quad, GLU_FILL);
    gluQuadricNormals(quad, GLU_SMOOTH);
}

void drawCube()
{
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

void drawCubeWireframe()
{
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3f(1.0, 1.0, 1.0);
    // Cara frontal
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(-0.5, -0.5, 0.5);
    // Cara trasera
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    glVertex3f(-0.5, -0.5, -0.5);
    // Conexiones
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    glEnd();
    checkGLError("drawCubeWireframe");
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    checkGLError("glClear");

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camera_x, camera_y, camera_z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    checkGLError("gluLookAt");

    // Cilindro
    glPushMatrix();
    glRotatef(angle_1_cube1, 0.0f, 0.707f, 0.707f);
    glColor3f(1.0, 0.0, 0.0);
    gluCylinder(quad, 0.3f, 0.3f, 1.0f, 20, 10);
    checkGLError("gluCylinder");
    glPopMatrix();

    // Cubo
    glPushMatrix();
    glRotatef(angle_1_cube1, 0.707f, 0.0f, 0.707f);
    glTranslatef(-2.0f, 0.0f, 0.0f);
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1.0, 1.0);
    drawCube();
    glDisable(GL_POLYGON_OFFSET_FILL);
    drawCubeWireframe();
    glPopMatrix();

    // Esfera
    glPushMatrix();
    glRotatef(angle_1_cube2, 0.0f, 1.0f, 0.0f);
    glTranslatef(cube2_x, 0.0f, cube2_z);
    glScalef(0.5f, 0.5f, 0.5f);
    glColor3f(0.0, 1.0, 0.0);
    gluSphere(quad, 0.5, 20, 20);
    checkGLError("gluSphere");
    glPopMatrix();

    glutSwapBuffers();
    checkGLError("glutSwapBuffers");
}

void reshape(int width, int height)
{
    if (height == 0)
        height = 1;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)width / height, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    checkGLError("reshape");
}

void input(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
    case 'w':
        if (camera_z > 1.5f)
        {
            camera_z -= 0.1f;
            glutPostRedisplay();
        }
        break;
    case 's':
        camera_z += 0.1f;
        glutPostRedisplay();
        break;
    case 'a':
        camera_x -= 0.1f;
        glutPostRedisplay();
        break;
    case 'd':
        camera_x += 0.1f;
        glutPostRedisplay();
        break;
    case 't':
        depth_test = !depth_test;
        if (depth_test)
            glEnable(GL_DEPTH_TEST);
        else
            glDisable(GL_DEPTH_TEST);
        glutPostRedisplay();
        break;
    }
}

void idle()
{
    angle_1_cube1 += 0.5f;
    if (angle_1_cube1 >= 360.0f)
        angle_1_cube1 -= 360.0f;

    cube2_x = 1.5f * cos(angle_2_cube2);
    cube2_z = 1.5f * sin(angle_2_cube2);
    angle_2_cube2 += 0.05f;
    if (angle_2_cube2 >= 360.0f)
        angle_2_cube2 -= 360.0f;

    angle_1_cube2 -= 1.0f;
    if (angle_1_cube2 <= -360.0f)
        angle_1_cube2 += 360.0f;

    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Escena 3D en OpenGL 1.1");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(input);
    glutIdleFunc(idle);
    init();
    glutMainLoop();
    return 0;
}