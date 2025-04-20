#include <GL/gl.h> 
#include <GL/glu.h>
#include <GL/glut.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

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
        gluOrtho2D(-1.0f * aspect, 1.0f * aspect, -1.0f, 1.0f); 
    } else {
        gluOrtho2D(-1.0f, 1.0f, -1.0f / aspect, 1.0f / aspect); 
    }

    glMatrixMode(GL_MODELVIEW); 
}

void input(unsigned char key, int x, int y){
    switch(key){
        case 27: 
            exit(0); 
            break;
        case 'r':
            glClearColor(1.0f, 0.0f, 0.0f, 1.0f); // Cambia el color de fondo a rojo
            glutPostRedisplay(); // Redibuja la ventana
            break;
        case 'b':
            glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // Cambia el color de fondo a azul
            glutPostRedisplay(); // Redibuja la ventana
            break;
        case 'n':
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glutPostRedisplay(); // Redibuja la ventana
            break;
        default:
            break;
    }
}

int main(int argc, char** argv){
    glutInit(&argc, argv); 
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); 
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT); 
    glutCreateWindow("Interactividad basica en OpenGL 1.1"); 

    glutDisplayFunc(display); 
    glutReshapeFunc(reshape); 
    glutKeyboardFunc(input); 

    init(); 

    glutMainLoop(); 
    return 0;
}