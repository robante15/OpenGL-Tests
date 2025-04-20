#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

bool use_aspect_ratio = true; // Cambia a false para usar la función reshape normal

void init(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Establece el color de fondo a negro
}

/**
 * @brief Función que se encarga de renderizar un triángulo en la ventana.
 * 
 * Esta función limpia el buffer de color y dibuja un triángulo utilizando 
 * la biblioteca OpenGL. Cada vértice del triángulo tiene un color diferente, 
 * lo que permite un efecto de interpolación de colores entre los vértices.
 * 
 * Detalles del triángulo:
 * - Vértice inferior izquierdo: color rojo (1.0, 0.0, 0.0).
 * - Vértice inferior derecho: color verde (0.0, 1.0, 0.0).
 * - Vértice superior: color azul (0.0, 0.0, 1.0).
 * 
 * La función utiliza `glFlush` para asegurarse de que todas las operaciones 
 * de renderizado se ejecuten inmediatamente.
 */
void display(){
    glClear(GL_COLOR_BUFFER_BIT); // Limpia el buffer de color

    glBegin(GL_TRIANGLES); // Comienza a dibujar un triángulo
        glColor3f(1.0f, 0.0f, 0.0f); // Color rojo
        glVertex2f(-0.5f, -0.5f); // Vértice inferior izquierdo
        glColor3f(0.0f, 1.0f, 0.0f); // Color verde
        glVertex2f(0.5f, -0.5f); // Vértice inferior derecho
        glColor3f(0.0f, 0.0f, 1.0f); // Color azul
        glVertex2f(0.0f, 0.5f); // Vértice superior
    glEnd();

    glFlush(); // Fuerza a que se dibuje todo lo que se ha especificado
}

/**
 * @brief Ajusta la vista y establece la proyección ortográfica al cambiar el tamaño de la ventana.
 * 
 * Esta función se llama automáticamente cuando la ventana cambia de tamaño. 
 * Configura el área de visualización y la proyección para que los gráficos 
 * se adapten correctamente al nuevo tamaño de la ventana.
 * 
 * @param width Ancho actual de la ventana.
 * @param height Altura actual de la ventana.
 */
void reshape(int width, int height){
    // Evitar la división por cero
    if (height == 0) height = 1;  

    glViewport(0, 0, width, height); // Ajusta la vista al tamaño de la ventana

    
    glMatrixMode(GL_PROJECTION); // Establece la proyección ortográfica
    glLoadIdentity(); // Carga la matriz identidad
    
    

    if(use_aspect_ratio){
        float aspect = (float)width / (float)height; // Calcula la relación de aspecto
        if (width >= height) {
            gluOrtho2D(-1.0f * aspect, 1.0f * aspect, -1.0f, 1.0f); // Proyección para ancho mayor
        } else {
            gluOrtho2D(-1.0f, 1.0f, -1.0f / aspect, 1.0f / aspect); // Proyección para alto mayor
        }
    } else {
        gluOrtho2D(-1.0, 1.0, -1.0, 1.0); // Define el área de visualización
    }

    glMatrixMode(GL_MODELVIEW); // Regresa a la matriz de modelo
}



void input(unsigned char key, int x, int y){
    switch(key){
        case 27: // Tecla ESC
            exit(0); // Sale del programa
            break;
        case '0':
            // Alternar entre proyecciones
            use_aspect_ratio = !use_aspect_ratio;
            // Forzar redimensionado para aplicar la nueva proyección
            glutPostRedisplay();
            // Opcional: Imprimir estado para depuración
            printf("Proyección: %s\n", use_aspect_ratio ? "Corregida" : "Sin corrección");
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

/*
gluOrtho2D: 
    - Establece una proyección ortográfica 2D.
    - Los parámetros son los límites izquierdo, derecho, inferior y superior.
    - Permite definir un área de visualización en coordenadas de ventana.

    Para ajustar la proyección ortográfica a la relación de aspecto de la ventana,
    se puede calcular la relación de aspecto y ajustar los límites izquierdo/derecho
    o superior/inferior en consecuencia. Esto asegura que los gráficos no se distorsionen
    al cambiar el tamaño de la ventana.
    - Por ejemplo, si la ventana es más ancha que alta, se puede aumentar el rango
      izquierdo/derecho para mantener la proporción.
    - Si la ventana es más alta que ancha, se puede aumentar el rango superior/inferior.
    - Esto se logra utilizando la relación de aspecto calculada y ajustando los límites
      de la proyección ortográfica en consecuencia.
    - gluOrtho2D(-1.0f * aspect, 1.0f * aspect, -1.0f, 1.0f); // Proyección para ancho mayor
    - gluOrtho2D(-1.0f, 1.0f, -1.0f / aspect, 1.0f / aspect); // Proyección para alto mayor
    - Esto asegura que los gráficos se mantengan proporcionales y no se distorsionen
      al cambiar el tamaño de la ventana.

    Modificar los valores de GluOrtho2D es como cambiar los valores de un plano cartesiano
    en el que se grafican los puntos. Si hago más grande el rango del plano pero mantengo las coordenadas
    de mis puntos, los puntos se verán más pequeños. Si hago más pequeño el rango del plano, los puntos se verán más grandes.

    Al agregar una corrección de relación de aspecto este plano cartesiano se ajusta a la ventana
    y no se distorsiona. Si la ventana es más ancha que alta, el rango izquierdo/derecho se ajusta
    para mantener la proporción. Si la ventana es más alta que ancha, el rango superior/inferior se ajusta.
    Esto asegura que los gráficos se mantengan proporcionales y no se distorsionen
    al cambiar el tamaño de la ventana.

    glViewport:
        - Establece el área de visualización en la ventana.
        - Los parámetros son las coordenadas x, y y el ancho y alto del área de visualización.

*/