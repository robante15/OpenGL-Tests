#include "scene.h"
#include <GL/glu.h>
#include <chrono>
#include <thread>
#include <stdio.h>

// Inicializar el puntero estático
Scene *Scene::instance = nullptr;

Scene::Scene(int width, int height) : window_width(width), window_height(height > 0 ? height : 1),
                                      lighting_enabled(true), quad_style(0), mouse_dragging(false)
{
    camera = new Camera(Vector3(3.0f, 3.0f, 14.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));
    spheres.push_back(new TSphere(5.0f, 0.1f));
    initGL();
    setInstance(this); // Establecer esta instancia como la actual
}

Scene::~Scene()
{
    for (auto *sphere : spheres)
        delete sphere;
    delete camera;
    if (quad)
        gluDeleteQuadric(quad);
    setInstance(nullptr);
}

void Scene::initGL()
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    quad = gluNewQuadric();
    gluQuadricDrawStyle(quad, GLU_FILL);
    gluQuadricNormals(quad, GLU_SMOOTH);
    setupLighting();
}

void Scene::setupLighting()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat light_pos[] = {0.0f, 5.0f, 5.0f, 1.0f};
    GLfloat light_ambient[] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat light_diffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
    GLfloat light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat mat_shininess[] = {50.0f};
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

void Scene::checkGLError(const char *operation)
{
    GLenum error;
    while ((error = glGetError()) != GL_NO_ERROR)
    {
        printf("Error después de %s: %s (código: 0x%x)\n",
               operation, gluErrorString(error), error);
    }
}

void Scene::display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    checkGLError("glClear");

    glMatrixMode(GL_MODELVIEW); // Establecer qué la matriz a modificar es la de modelo-vista
    glLoadIdentity();
    float view_matrix[16];
    camera->getViewMatrix().getOpenGLMatrix(view_matrix);
    glMultMatrixf(view_matrix);
    // gluLookAt(3.0f, 3.0f, 14.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    checkGLError("glMultMatrixf");

    if (!lighting_enabled)
        glDisable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 1.0f);
    glutWireCube(10.0f);
    if (lighting_enabled)
        glEnable(GL_LIGHTING);

    for (auto *sphere : spheres)
    {
        glPushMatrix();
        Vector3 pos = sphere->getPos();
        Vector3 color = sphere->getColor();
        glColor3fv(&color.x);
        glTranslatef(pos.x, pos.y, pos.z);
        gluSphere(quad, 1.0f, 20, 20);
        glPopMatrix();
    }

    glutSwapBuffers();
    checkGLError("glutSwapBuffers");
}

void Scene::reshape(int width, int height)
{
    window_width = width;
    window_height = height > 0 ? height : 1;
    glViewport(0, 0, width, window_height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f, (float)width / window_height, 1.0f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    checkGLError("reshape");
}

void Scene::idle()
{
    for (auto *sphere : spheres)
    {
        sphere->test();
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(33));
    glutPostRedisplay();
}

void Scene::keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27: // ESC
        // glutLeaveMainLoop();
        exit(0);
        break;
    case 'w':
        camera->moveForward(1.0f);
        break;
    case 's':
        camera->moveForward(-1.0f);
        break;
    case 'a':
        camera->moveRight(-1.0f);
        break;
    case 'd':
        camera->moveRight(1.0f);
        break;
    case 'q':
        camera->moveUp(1.0f);
        break;
    case 'e':
        camera->moveUp(-1.0f);
        break;
    case '+':
        for (auto *sphere : spheres)
            sphere->modifySpeed(0.05f);
        break;
    case '-':
        for (auto *sphere : spheres)
            sphere->modifySpeed(-0.05f);
        break;
    case 't':
        spheres.push_back(new TSphere(5.0f, 0.1f));
        break;
    case 'r':
        if (!spheres.empty())
        {
            delete spheres.back();
            spheres.pop_back();
        }
        break;
    case '0':
        for (auto *sphere : spheres)
            sphere->modifySpeed(-sphere->getSpeed());
        break;
    case 'p':
        for (auto *sphere : spheres)
            sphere->restoreSpeed();
        break;
    case 'l':
        lighting_enabled = !lighting_enabled;
        break;
    case 'c':
        quad_style = (quad_style + 1) % 3;
        if (quad_style == 0)
            gluQuadricDrawStyle(quad, GLU_FILL);
        else if (quad_style == 1)
            gluQuadricDrawStyle(quad, GLU_LINE);
        else
            gluQuadricDrawStyle(quad, GLU_POINT);
        break;
    }
    glutPostRedisplay();
}

void Scene::mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        mouse_dragging = (state == GLUT_DOWN);
        last_mouse_x = x;
        last_mouse_y = y;
    }
}

void Scene::motion(int x, int y)
{
    if (mouse_dragging)
    {
        float delta_x = (x - last_mouse_x) * 0.01f;
        float delta_y = (y - last_mouse_y) * -0.01f;
        camera->rotate(-delta_x, -delta_y);
        last_mouse_x = x;
        last_mouse_y = y;
        glutPostRedisplay();
    }
}

// Implementación de callbacks estáticos
void Scene::displayCallback()
{
    if (instance)
        instance->display();
}

void Scene::reshapeCallback(int width, int height)
{
    if (instance)
        instance->reshape(width, height);
}

void Scene::idleCallback()
{
    if (instance)
        instance->idle();
}

void Scene::keyboardCallback(unsigned char key, int x, int y)
{
    if (instance)
        instance->keyboard(key, x, y);
}

void Scene::mouseCallback(int button, int state, int x, int y)
{
    if (instance)
        instance->mouse(button, state, x, y);
}

void Scene::motionCallback(int x, int y)
{
    if (instance)
        instance->motion(x, y);
}