#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int shape_type = 0; // 0: Triángulo, 1: Cuadrado

void init(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void drawTriangle(){
    glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(-0.5f, -0.5f);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(0.5f, -0.5f);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2f(0.0f, 0.5f);
    glEnd();
}

void drawSquare(){
    glBegin(GL_QUADS);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(-0.5f, -0.5f);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(0.5f, -0.5f);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2f(0.5f, 0.5f);
        glColor3f(1.0f, 1.0f, 0.0f);
        glVertex2f(-0.5f, 0.5f);
    glEnd();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    if (shape_type == 0) {
        drawTriangle();
    } else {
        drawSquare();
    }

    glFlush();
}

void reshape(int width, int height){
    if (height == 0) height = 1;  
    float aspect = (float)width / (float)height; 

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0f * aspect, 1.0f * aspect, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
}

void input(unsigned char key, int x, int y){
    switch(key){
        case 27: // Tecla ESC
            exit(0);
            break;
        case '1':
            shape_type = 0; // Triángulo
            break;
        case '2':
            shape_type = 1; // Cuadrado
            break;
    }
    glutPostRedisplay(); // Redibuja la ventana
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Alternar Formas");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(input);
    glutMainLoop();
    return 0;
}