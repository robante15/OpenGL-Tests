#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

float scale = 1.0f; // Factor de escala inicial

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

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float aspect = (float)width / (float)height; 
    if (width >= height) {
        gluOrtho2D(-aspect * scale, aspect * scale, -scale, scale);
    } else {
        gluOrtho2D(-scale, scale, -scale / aspect, scale / aspect);
    }

    glMatrixMode(GL_MODELVIEW);
}

void input(unsigned char key, int x, int y){
    switch(key){
        case 27: // Tecla ESC
            exit(0);
            break;
        case '+':
            scale += 0.25f; // Aumenta la escala
            break;
        case '-':
            scale -= 0.25f; // Disminuye la escala
            break;
        default:
            break;
    }
}

int main(int argc, char** argv){
    // Inicializa GLUT
    glutInit(&argc, argv); 
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // Establece el modo de visualización
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT); // Establece el tamaño de la ventana
    glutCreateWindow("Triángulo en OpenGL 1.1"); // Crea la ventana

    glutDisplayFunc(display); // Registra la función de visualización
    glutReshapeFunc(reshape); // Registra la función de cambio de tamaño
    glutKeyboardFunc(input); // Registra la función de entrada del teclado

    init(); // Inicializa OpenGL

    glutMainLoop(); // Entra en el bucle principal de GLUT
    return 0;
}