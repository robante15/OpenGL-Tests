#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

void init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void drawQuad(){
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0f);    // Color rojo
    glVertex3f(-0.5f, 0.5f, -0.5f); // Vértice inferior izquierdo
    glColor3f(0.0f, 1.0f, 0.0f);    // Color verde
    glVertex3f(-0.5f, -0.5f, 0.5f); // Vértice inferior derecho
    glColor3f(0.0f, 0.0f, 1.0f);    // Color azul
    glVertex3f(0.5f, -0.5f, 0.5f);   // Vértice superior derecho
    glColor3f(1.0f, 1.0f, 0.0f);    // Color amarillo
    glVertex3f(0.5f, 0.5f, -0.5f); // Vértice superior izquierdo
    glEnd();
}

void drawTriangle(){
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f); // Color rojo
    glVertex3f(0.0f, 0.5f, 0.0f); // Vértice inferior izquierdo
    glVertex3f(-0.7f, -0.5f, 0.0f);
    glVertex3f(0.7f, -0.5f, 0.0f);
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpia el buffer de color y profundidad

    glDepthFunc(GL_LEQUAL); // Establece la función de comparación de profundidad
    glEnable(GL_DEPTH_TEST); // Habilita el test de profundidad
    glClearDepth(1.0f); // Limpia el buffer de profundidad

    drawQuad(); // Dibuja el cuadrado
    drawTriangle(); // Dibuja el triángulo

    glBegin(GL_LINES);
    glColor3f(1.0f, 1.0f, 1.0f); // Color blanco
    glVertex2f(-0.75f, -0.75f);  // Vértice inferior izquierdo
    glVertex2f(-0.75f, 0.75f);   // Vértice superior derecho
    glEnd();

    glBegin(GL_POINTS);
    glColor3f(1.0f, 0.0f, 1.0f); // Color magenta
    glVertex2f(0.75f, 0.75f);    // Punto en el centro
    glEnd();

    glFlush();
}

void reshape(int width, int height)
{
    // Evitar la división por cero
    if (height == 0) height = 1;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(60.0f, (float)width / (float)height, 0.1f, 100.0f); // Proyección perspectiva
    glTranslatef(0.0f, 0.0f, -2.0f);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    // Inicializa GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);    // Establece el modo de visualización (Single buffer, RGBA y profundidad)
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT); // Establece el tamaño de la ventana
    glutCreateWindow("Cuadrado en OpenGL 1.1");      // Crea la ventana

    glutDisplayFunc(display); // Registra la función de visualización
    glutReshapeFunc(reshape); // Registra la función de cambio de tamaño

    init(); // Inicializa OpenGL

    glutMainLoop(); // Entra en el bucle principal de GLUT
    return 0;
}