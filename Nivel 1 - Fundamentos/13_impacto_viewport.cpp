#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

void init(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Establece el color de fondo a negro
}

float triangle_pos_x = 0.0f; // Posición inicial del triángulo en el eje X
float triangle_pos_y = 0.0f; // Posición inicial del triángulo en el eje Y

void drawTriangle(){
    glBegin(GL_TRIANGLES); // Comienza a dibujar un triángulo
        glColor3f(1.0f, 0.0f, 0.0f); // Color rojo
        glVertex2f(-0.5f, -0.5f); // Vértice inferior izquierdo
        glColor3f(0.0f, 1.0f, 0.0f); // Color verde
        glVertex2f(0.5f, -0.5f); // Vértice inferior derecho
        glColor3f(0.0f, 0.0f, 1.0f); // Color azul
        glVertex2f(0.0f, 0.5f); // Vértice superior
    glEnd();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT); // Limpia el buffer de color

    glPushMatrix(); // Guarda la matriz actual
    glTranslatef(triangle_pos_x, triangle_pos_y, 0.0f); // Aplica la traslación al triángulo
    drawTriangle(); // Dibuja el triángulo
    glPopMatrix(); // Restaura la matriz anterior

    glFlush(); // Fuerza a que se dibuje todo lo que se ha especificado
}

void reshape(int width, int height){
    // Evitar la división por cero
    if (height == 0) height = 1;  

    glViewport(0, height/2, width, height/2); // Ajusta la vista al tamaño de la ventana

    glMatrixMode(GL_PROJECTION); // Establece la proyección ortográfica
    glLoadIdentity(); // Carga la matriz identidad

    float aspect = (float)width / (float)height; // Calcula la relación de aspecto
    if (width >= height) {
        gluOrtho2D(-1.0f * aspect, 1.0f * aspect, -1.0f, 1.0f); // Proyección para ancho mayor
    } else {
        gluOrtho2D(-1.0f, 1.0f, -1.0f / aspect, 1.0f / aspect); // Proyección para alto mayor
    }

    glMatrixMode(GL_MODELVIEW); // Regresa a la matriz de modelo
}

bool out_of_x_bounds(float x) {
    return (x < -1.0f || x > 1.0f);
}

bool out_of_y_bounds(float y) {
    return (y < -0.5f || y > 0.5f);
}

void input(unsigned char key, int x, int y){
    switch(key){
        case 27: // Tecla ESC
            exit(0); // Sale del programa
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

