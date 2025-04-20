#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>

//Definimos variables
double rotate_y=0;
double rotate_x=0;
double rotate_z=0;

GLfloat X = 0.0f;
GLfloat Y = 0.0f;
GLfloat Z = 0.0f;
GLfloat scale = 1.0f;

//ancho y alto
GLint ancho=500;
GLint alto=500;

int perspectiva=1;

void cubo()
{

    glBegin(GL_POLYGON);
    glColor3f(1,1,1);
    gluLookAt(0,0,5,0,0,0,0,1,0);
    glScalef(1,2,3);
    glutWireSphere(0.8,10,10);
    glFlush();

/*    glColor3f( 1.0, 1.0, 1.0 );
    glVertex3f(  0.3, -0.3, -0.3 );      // V1 Blanco
    glColor3f( 1.0, 1.0, 0.0 );
    glVertex3f(  0.3,  0.3, -0.3 );      // V2 Amarillo
    glColor3f( 0.0, 0.0, 1.0 );
    glVertex3f( -0.3,  0.3, -0.3 );      // V3 es azul
    glColor3f( 1.0, 0.0, 0.0 );
    glVertex3f( -0.3, -0.3, -0.3 );      // V4 rojo

    glEnd();

    // LADO TRASERO: lado blanco
    glBegin(GL_POLYGON);
    glColor3f( 1.0,  1.0, 1.0 );
    glVertex3f( 0.3, -0.3, 0.3 );
    glVertex3f( 0.3,  0.3, 0.3 );
    glVertex3f(-0.3,  0.3, 0.3 );
    glVertex3f(-0.3, -0.3, 0.3 );
    glEnd();

    // LADO DERECHO: lado verde
    glBegin(GL_POLYGON);
    glColor3f( 0.0,  1.0,  0.0 );
    glVertex3f(0.3, -0.3, -0.3 );
    glVertex3f(0.3,  0.3, -0.3 );
    glVertex3f(0.3,  0.3,  0.3 );
    glVertex3f(0.3, -0.3,  0.3 );
    glEnd();

    // LADO IZQUIERDO: lado Amarillo
    glBegin(GL_POLYGON);
    glColor3f(1.0,  1.0,  0.0 );
    glVertex3f(-0.3, -0.3,  0.3 );
    glVertex3f(-0.3,  0.3,  0.3 );
    glVertex3f(-0.3,  0.3, -0.3 );
    glVertex3f(-0.3, -0.3, -0.3 );
    glEnd();

    // LADO SUPERIOR: lado azul
    glBegin(GL_POLYGON);
    glColor3f(0.0,  0.0,  1.0 );
    glVertex3f(0.3,  0.3,  0.3 );
    glVertex3f(0.3,  0.3, -0.3 );
    glVertex3f(-0.3,  0.3, -0.3 );
    glVertex3f(-0.3,  0.3,  0.3 );
    glEnd();

    // LADO INFERIOR: lado rojo
    glBegin(GL_POLYGON);
    glColor3f(1.0,  0.0,  0.0 );
    glVertex3f(0.3, -0.3, -0.3 );
    glVertex3f(0.3, -0.3,  0.3 );
    glVertex3f(-0.3, -0.3,  0.3 );
    glVertex3f(-0.3, -0.3, -0.3 ); */

}


void display()
{
    //  Borrar pantalla y Z-buffer
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    // Resetear transformaciones
    glLoadIdentity();
    // Rotar en el eje X,Y y Z
    glRotatef( rotate_x, 1.0, 0.0, 0.0 );
    glRotatef( rotate_y, 0.0, 1.0, 0.0 );
    glRotatef( rotate_z, 0.0, 0.0, 1.0 );
    glTranslatef(X, Y, Z); 	// Transladar en los 3 ejes
    // Otras transformaciones

    gluLookAt(1.0,2.0,3.0,//eye x,y,z
              0.0,1.0,1.0,//at x,y,z
              1.0,0.0,0.0);//up x,y,z

    glScalef(scale, scale, scale);
    // Primera cara, se identica por multiples colores

    cubo();
    glFlush();
    glutSwapBuffers();

}

void reshape(int ancho, int alto){

    glViewport(0,0,(GLsizei)ancho,(GLsizei)alto);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1,1,-1,1,1.5,20);
    glMatrixMode(GL_MODELVIEW);

    //glutReshapeFunc();
/*    glViewport(0,0,alto, ancho);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if(perspectiva)
        gluPerspective(60.0f,(GLfloat)ancho/(GLfloat)alto,0.2f,30.0f);
    else
        //glOrtho(-4,4,-4,4,-1,10);
        glFrustum(-1.0,1.0, -1.0,1.0,2.0,200);
    glMatrixMode(GL_MODELVIEW);*/
}


// Función para controlar teclas especiales
void specialKeys( int key, int x, int y )
{

    //  Flecha derecha: aumentar rotación 7 grados
    if (key == GLUT_KEY_RIGHT)
        rotate_y += 7;

        //  Flecha izquierda: rotación en eje Y negativo 7 grados
    else if (key == GLUT_KEY_LEFT)
        rotate_y -= 7;
        //  Flecha arriba: rotación en eje X positivo 7 grados
    else if (key == GLUT_KEY_UP)
        rotate_x += 7;
        //  Flecha abajo: rotación en eje X negativo 7 grados
    else if (key == GLUT_KEY_DOWN)
        rotate_x -= 7;
        //  Tecla especial F2 : rotación en eje Z positivo 7 grados
    else if (key == GLUT_KEY_F2)
        rotate_z += 7;
        //  Tecla especial F2 : rotación en eje Z negativo 7 grados
    else if (key == GLUT_KEY_F2)
        rotate_z -= 7;

    //  Solicitar actualización de visualización
    glutPostRedisplay();

}

// Función para controlar teclas normales del teclado.
void keyboard(unsigned char key, int x, int y)
{
    //control de teclas que hacen referencia a Escalar y transladar el cubo en los ejes X,Y,Z.
    switch (key)
    {
        case 's':
            scale=0.5;
            break;
        case 'd':
            scale=1.5;
            break;
        case 'x' :
            X += 0.1f;
            break;
        case 'X' :
            X -= 0.1f;
            break;
        case 'y' :
            Y += 0.1f;
            break;
        case 'Y' :
            Y -= 0.1f;
            break;
        case 'z':
            Z -= 0.1f;
            break;
        case 'Z':
            Z += 0.1f;
            break;
        case 'q':
            exit(0);			// exit
    }
    glutPostRedisplay();
}

//funcion init

void init()
{
    // Habilitar la prueba de profundidad de Z-buffer
    glEnable(GL_DEPTH_TEST);
    alto=800;
    ancho=600;
    glutInitWindowSize (alto, ancho);


}


int main(int argc, char* argv[])
{

    //  Inicializar los parámetros GLUT y de usuario proceso
    glutInit(&argc,argv);

    // Solicitar ventana con color real y doble buffer con Z-buffer
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition (0, 0);
    init();
    // Crear ventana
    glutCreateWindow("Cubo controlado por teclas");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    //llamando la funcion de reshape
    glutReshapeFunc(reshape);
    // Pasar el control de eventos a GLUT
    glutMainLoop();


    // Regresar al sistema operativo
    return 0;

}