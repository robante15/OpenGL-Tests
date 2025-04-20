#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <stdio.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int shape_type = 0; // 0: Triángulo, 1: Cuadrado
int use_aspect_ratio = 1; // 0: Sin relación de aspecto, 1: Con relación de aspecto, 2: Proyección personalizada
float triangle_pos_x = 0.0f; // Posición inicial del triángulo en el eje X
float triangle_pos_y = 0.0f; // Posición inicial del triángulo en el eje Y

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

    glPushMatrix(); // Guarda la matriz actual
    glTranslatef(triangle_pos_x, triangle_pos_y, 0.0f); // Aplica la traslación al triángulo
    if (shape_type == 0) {
        drawTriangle();
    } else {
        drawSquare();
    }
    glPopMatrix(); // Restaura la matriz anterior

    glFlush();
}

bool out_of_x_bounds(float x) {
    return (x < -1.0f || x > 1.0f);
}

bool out_of_y_bounds(float y) {
    return (y < -0.5f || y > 0.5f);
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

void print_info(){
    printf("Posición del objeto: (%.2f, %.2f)\n", triangle_pos_x, triangle_pos_y);
    printf("Tipo de forma: %s\n", shape_type == 0 ? "Triángulo" : "Cuadrado");
    printf("Relación de aspecto: %s\n", use_aspect_ratio == 0 ? "Sin relación" : (use_aspect_ratio == 1 ? "Con relación" : "Proyección personalizada"));
}

void input(unsigned char key, int x, int y){
    switch(key){
        case 27: // Tecla ESC
            exit(0);
            break;
        case '0':
            // Rotar entre proyecciones
            use_aspect_ratio = (use_aspect_ratio + 1) % 3; // Cambia entre 0, 1 y 2
            break;
        case 't':
            shape_type = 0; // Triángulo
            break;
        case 'q':
            shape_type = 1; // Cuadrado
            break;
        case 'w': // Tecla 'w'
            if (!out_of_y_bounds(triangle_pos_y + 0.1f)){
                triangle_pos_y += 0.1f; // Mueve el triángulo hacia arriba
                glutPostRedisplay();
            }
            break;
        case 's': // Tecla 's'
            if (!out_of_y_bounds(triangle_pos_y - 0.1f)){
                triangle_pos_y -= 0.1f; // Mueve el triángulo hacia abajo
                glutPostRedisplay();
            }
            break;
        case 'a': // Tecla 'a'
            if (!out_of_x_bounds(triangle_pos_x - 0.1f)){
                triangle_pos_x -= 0.1f; // Mueve el triángulo hacia la izquierda
                glutPostRedisplay();
            }
            break;
        case 'd': // Tecla 'd'
            if (!out_of_x_bounds(triangle_pos_x + 0.1f)){
                triangle_pos_x += 0.1f; // Mueve el triángulo hacia la derecha
                glutPostRedisplay();
            }
            break;
        case 'r':
            glClearColor(1.0, 0.0, 0.0, 1.0); // Cambia el color de fondo a gris
            glutPostRedisplay(); // Redibuja la ventana
            break;
        case 'g':
            glClearColor(0.0, 1.0, 0.0, 1.0); 
            glutPostRedisplay(); // Redibuja la ventana
            break;
        case 'b':
            glClearColor(0.0, 0.0, 1.0, 1.0); // Cambia el color de fondo a cian
            glutPostRedisplay(); // Redibuja la ventana
            break;
        case 'n':
            glClearColor(0.0, 0.0, 0.0, 1.0); // Cambia el color de fondo a cian
            glutPostRedisplay(); // Redibuja la ventana
            break;
    }
    glutPostRedisplay(); // Redibuja la ventana
    print_info(); // Imprime la información en la consola
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