#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int use_aspect_ratio = 1;

void init(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(-0.5f, -0.5f);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(0.5f, -0.5f);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2f(0.0f, 0.5f);
    glEnd();

    glFlush();
}

void reshape(int width, int height){
    if (height == 0) height = 1;  
    float aspect = (float)width / (float)height; 

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    switch(use_aspect_ratio){
        case 0:
            gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
            break;
        case 1:
            if (width >= height) {
                gluOrtho2D(-1.0f * aspect, 1.0f * aspect, -1.0f, 1.0f); // Proyección para ancho mayor
            } else {
                gluOrtho2D(-1.0f, 1.0f, -1.0f / aspect, 1.0f / aspect); // Proyección para alto mayor
            }
            break;
        case 2:
            gluOrtho2D(-0.5, 0.5, -0.5, 0.5);
            break;
    }
    glMatrixMode(GL_MODELVIEW);
}

void input(unsigned char key, int x, int y){
    switch(key){
        case 27: // Tecla ESC
            exit(0);
            break;
        case '1':
            use_aspect_ratio = 1;
            glClearColor(0.5, 0.5, 0.5, 1.0); // Cambia el color de fondo a gris
            glutPostRedisplay(); // Redibuja la ventana
            break;
        case '2':
            use_aspect_ratio = 0;
            glClearColor(0.0, 0.0, 0.0, 1.0); 
            glutPostRedisplay(); // Redibuja la ventana
            break;
        case '3':
            use_aspect_ratio = 2;
            glClearColor(0.0, 1.0, 1.0, 1.0); // Cambia el color de fondo a cian
            glutPostRedisplay(); // Redibuja la ventana
            break;
        default:
            break;
    }
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Proyección Personalizada");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(input);
    glutMainLoop();
    return 0;
}