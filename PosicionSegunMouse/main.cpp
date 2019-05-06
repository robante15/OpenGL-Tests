#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>

int value = 0;
float pos_x = 0;
float pos_y = 0;
float ancho = 1000.0;
float alto = 700.0;
double trasladar_y = 0.0;

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

//definimos al menu
void menu(int valor) {
    value = valor;
    switch (valor) {
        case 1: {
            glutWireTorus(0.5, 1.0, 20, 20); //dona
            break;
        }
        case 2: {
            glutWireTeapot(1); //tetera
            break;
        }
        case 3: {
            glutWireIcosahedron(); //isosahedro
            break;
        }
        case 4: {
            glutWireCone(1.0, 1.0, 10, 10); //cono
            break;
        }
        case 5: {
            glutWireOctahedron(); //octahedro
            break;
        }
        case 6: {
            glutWireTetrahedron(); //tetrahedro
            break;
        }
        case 7: {
            glutWireSphere(1.0, 20, 20); //sfera
            break;
        }
        case 8: {
            glutWireCube(1); //cubo
            break;
        }
        case 9:
            exit(0);
    }
    glutSwapBuffers();
}

//aqui llamamos la redibujacion de las figuras
void tiempo_real(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    switch (value) //se evalua variable global value para saber cual era la figura que se llamo al menu
    {
        case 1: {
            glutWireTorus(0.5, 1.0, 20, 20); //dona
            break;
        }
        case 2: {
            glutWireTeapot(1); //tetera
            break;
        }
        case 3: {
            glutWireIcosahedron(); //isosahedro
            break;
        }
        case 4: {
            glutWireCone(1.0, 1.0, 10, 10); //cono
            break;
        }
        case 5: {
            glutWireOctahedron(); //octahedro
            break;
        }
        case 6: {
            glutWireTetrahedron(); //tetrahedro
            break;
        }
        case 7: {
            glutWireSphere(1.0, 20, 20); //cubo
            break;
        }
        case 8: {
            glutWireCube(1); //cubo
            break;
        }
    }
    glutSwapBuffers();
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0, 0.0, 1.0);
    // Resetear transformaciones
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 3.0, //eye
              0.0, 0.0, 0.0, //at
              0.0, 1.0, 0.0); //up
    glTranslatef(pos_x, pos_y, 0.0f); //aqui hacemos el traslamiento de las figuras
    glRotatef(25.0, 1.0, 0.0, 0.0);
    glRotatef(-20.0, 0.0, 1.0, 0.0);
    glScalef(0.3, 0.3, 0.3);
    glFlush();
}

//definimos las opciones del menu
void menu_opciones(void) {
    glutCreateMenu(menu);
    glutAddMenuEntry("Torus", 1);
    glutAddMenuEntry("Tetera", 2);
    glutAddMenuEntry("Cono", 4);
    glutAddMenuEntry("Isosaedro", 3);
    glutAddMenuEntry("Octahedro", 5);
    glutAddMenuEntry("Tetrahedro", 6);
    glutAddMenuEntry("Esfera", 7);
    glutAddMenuEntry("Cubo", 8);
    glutAddMenuEntry("Salir", 9);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

//funcion llamada para el raton en movimiento
void posicion_raton(int x, int y) {
    pos_x = (GLfloat) x / (ancho / 2);
    pos_y = 2 - (GLfloat) y / (alto / 2);
    glutPostRedisplay();
}

//funcion llamada para acciones del click y otros del raton
void manejador_raton(int button, int state, int x, int y) {
    //si se clicke el click izquierdo, entonces capturar la posicion del cursor y trasladar alli
    if (button == GLUT_LEFT_BUTTON) {
        pos_x = (GLfloat) x / (ancho / 2);
        pos_y = 2 - (GLfloat) y / (alto / 2);
    }

    if (button == 3) //button 3 es la traslacion de la rueda del raton hacia arriba
    {
        pos_y += 0.1;
    }

    if (button == 4) //button 4 es la traslacion de la rueda del raton hacia arriba
    {
        if (state == GLUT_DOWN) {
            pos_y -= 0.1;
        }
    }
    glutPostRedisplay();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    menu_opciones();
    glLoadIdentity();
    //configurando glortho para una vista total de las figuras
    glOrtho(0.0, 2.0, 0.0, 2.0, -10.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char *argv[]) {
    //  Inicializar los parámetros GLUT y de usuario proceso
    glutInit(&argc, argv);
    // Solicitar ventana con color real y doble buffer con Z-buffer
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(ancho, alto);
    glutInitWindowPosition(100, 100);
    // Crear ventana
    glutCreateWindow("Menu");
    init();
    // Funciones de retrollamada
    glutDisplayFunc(display);
    glutIdleFunc(tiempo_real);
    glutReshapeFunc(reshape);
    glutMotionFunc(
            posicion_raton); //asignamos funcion de movimiento del ratn a glutMotionFunc para que sea llamada al mover el raton
    glutMouseFunc(
            manejador_raton); //asignamos funcion de acciones del ratn a glutMouseFunc para que sea llamada al controlar el raton
    // Pasar el control de eventos a GLUT
    glutMainLoop();
    // Regresar al sistema operativo
    return 0;
}