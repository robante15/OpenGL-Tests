#include <GL/glut.h>
#include <stdio.h>
#include <chrono>
#include <thread>
#include "sphere.h"
#include <vector>

float *pos = nullptr; // Posición de la esfera
float *col = nullptr; // Color de la esfera

GLUquadric *quad = nullptr;
std::vector<TSphere *> spheres;
bool stop = false;
std::vector<float> previous_speed;

float camera_x = 3.0f, camera_y = 3.0f, camera_z = 14.0f; // Posición de la cámara

void lightning(){
    // Configurar iluminación
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    // Luz puntual en (0, 5, 5)
    GLfloat light_pos[] = {0.0f, 5.0f, 5.0f, 1.0f}; // w=1 para luz puntual
    GLfloat light_ambient[] = {0.2f, 0.2f, 0.2f, 1.0f}; // Luz ambiente suave
    GLfloat light_diffuse[] = {0.8f, 0.8f, 0.8f, 1.0f}; // Luz difusa fuerte
    GLfloat light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f}; // Reflejo especular blanco
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    // Habilitar GL_COLOR_MATERIAL para usar glColor* como material
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE); // Colores afectan ambiente y difusa

    // Configurar material especular y shininess
    GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat mat_shininess[] = {50.0f}; // Rango de 0 a 128
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

void initgl()
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    // Inicializa el quadric
    quad = gluNewQuadric();
    gluQuadricDrawStyle(quad, GLU_FILL);
    gluQuadricNormals(quad, GLU_SMOOTH);
    // Configura la iluminación
    lightning();
    // Inicializa la esfera
    spheres.push_back(new TSphere(5.0f, 0.1f));
    spheres.push_back(new TSphere(5.0f, 0.15f));
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
    gluLookAt(camera_x, camera_y, camera_z, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    checkGLError("gluLookAt");

    // Dibuja el cubo de referencia sin iluminación (Wireframe)
    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 1.0f);
    glutWireCube(10.0f);
    glEnable(GL_LIGHTING);

    // Dibujar las esferas rebotando
    for (auto *sphere : spheres)
    {
        glPushMatrix();
        col = sphere->getColorv();
        pos = sphere->getPosv();
        if (pos && col)
        {
            glColor3fv(col);
            glTranslatef(pos[0], pos[1], pos[2]);
            gluSphere(quad, 1.0f, 20, 20);
        }
        glPopMatrix();
    }

    glutSwapBuffers();
    checkGLError("glutSwapBuffers");
}
void idle(void)
{
    for (auto *s : spheres)
    {
        s->updatePosition();
    }
    // Espera 33 ms (aproximadamente 30 FPS)
    std::this_thread::sleep_for(std::chrono::milliseconds(33));
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27: // Tecla ESC
        for (auto *s : spheres)
        {
            delete s; // Libera la memoria de las esferas
        }
        exit(0);
        break;
    case 'w':
        if (camera_z > 6.0f)
            camera_z -= 0.1f;
        break;
    case 's':
        camera_z += 0.1f;
        break;
    case 'a':
        camera_x -= 0.1f;
        break;
    case 'd':
        camera_x += 0.1f;
        break;
    case 'q':
        camera_y += 0.1f;
        break;
    case 'e':
        camera_y -= 0.1f;
        break;
    case '+':
        for (auto *s : spheres)
        {
            s->modifySpeed(0.05f);
        }
        break;
    case '-':
        for (auto *s : spheres)
        {
            s->modifySpeed(-0.05f);
        }
        break;
    case 'r': // Eliminar última esfera
        if (!spheres.empty())
        {
            delete spheres.back();
            spheres.pop_back();
        }
        break;
    case 'p':
        for (auto *s : spheres)
        {
            s->setSpeed(0.0f);
        }
        break;
    case 'o':
            for (auto* sphere : spheres) sphere->restoreSpeed();
            break;
    case 't':
        spheres.push_back(new TSphere(4.0f, 0.35f));
        break;
    default:
        break;
    }
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
    for (auto *s : spheres)
    {
        delete s; // Libera la memoria de las esferas
    }
    return 0;
}