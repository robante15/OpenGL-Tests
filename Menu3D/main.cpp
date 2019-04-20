#include <GL/gl.h>
#include <GL/glut.h>

void menu_opciones(void);

void init(void) {

    GLfloat light_position[4] = {5.0, 5.0, 5.0, 0.0};

    //GLfloat light_position[] = {5.0, 5.0, 5.0, 0.0};

    glEnable(GL_LIGHTING); //activa la fuente de luz
    glEnable(GL_LIGHT0); //Activamos las luces en 0
    glDepthFunc(GL_LESS); //comparación de profundidad
    glEnable(GL_DEPTH_TEST); //activa GL_DEPTH_TES
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    // Queremos que se dibujen las caras frontales
    // y con un color solido de relleno.
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    menu_opciones();
    glLoadIdentity();
    glOrtho(-300, 300, -300, 300, -300, 300);
    // Activamos la matriz de modelado/visionado.
    glMatrixMode(GL_MODELVIEW);
    // "Limpiamos" la matriz
    glLoadIdentity();
}

void menu(int valor) {
    if (valor == 1) {
        glutWireTorus(0.5, 1.0, 20, 20);
    }
    if (valor == 2) {
        glutWireTeapot(1.0);
    }
    if (valor == 3) {
        exit(0);
    }
}

void menu_opciones(void) {
    glutCreateMenu(menu);
    glutAddMenuEntry("Torus", 1);
    glutAddMenuEntry("Tetera", 2);
    glutAddMenuEntry("Salir", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

static void display(void) {

    GLfloat light_ambient[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat light_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat light_position[] = {-20.0f, -50.0f, 50.0f, 0.0f};

    GLfloat mat_ambient[] = {0.7f, 0.7f, 0.7f, 1.0f};
    GLfloat mat_diffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
    GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat high_shininess[] = {100.0f};

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1, 0, 0);

    glMaterialfv(GL_FRONT, GL_AMBIENT, light_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, light_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, light_specular);
    glMaterialfv(GL_FRONT, GL_POSITION, light_position);


    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glPushMatrix();
    glutSolidSphere(100, 160, 160);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(25, 150, 0);
    glutSolidTeapot(160);
    glPopMatrix();

    /*glMatrixMode(GL_MODELVIEW_MATRIX);
    glLoadIdentity();
    glTranslatef(130, 130, 0);
    glutSolidSphere(125, 30, 10);*/
    glFlush();
}


int main(int argc, char **argv) {
// Inicializo OpenGL
    glutInit(&argc, argv);
// Activamos buffer simple y colores del tipo RGB
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
// Definimos una ventana de medidas 800 x 600 como ventana
// de visualizacion en pixels
    glutInitWindowSize(800, 600);
// Posicionamos la ventana en la esquina superior izquierda de
// la pantalla.
    glutInitWindowPosition(0, 0);
// Creamos literalmente la ventana y le adjudicamos el nombre que se
// observara en su barra de titulo.
    glutCreateWindow("Tetera");
// Inicializamos el sistema
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();

    return 0;
}
