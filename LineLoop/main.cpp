#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <cstring>

void circuloTeselado(float radio, int numPuntos) {
    glColor3f(1, 1, 1);
    glBegin(GL_LINES);

    for (int i = 0; i <= numPuntos; i++) {
        float Angulo = i * (2.0 * M_PI / numPuntos);
        float X = cos(Angulo) * radio;
        float Y = sin(Angulo) * radio;
        glVertex2f(X, Y);

        float Angulo2 = (i + 1) * (2.0 * M_PI / numPuntos);
        float X2 = cos(Angulo2) * radio;
        float Y2 = sin(Angulo2) * radio;
        glVertex2f(X2, Y2);
    }
}

void canasta(float radio, int numPuntos) {
    glColor3f(1, 1, 1);
    glBegin(GL_LINES);

    for (int i = 0; i <= numPuntos; i++) {
        float Angulo = i * (2.0 * M_PI / numPuntos);
        float X = 87-cos(Angulo) * radio;
        float Y = sin(Angulo) * radio;
        glVertex2f(X, Y);

        float Angulo2 = (i + 1) * (2.0 * M_PI / numPuntos);
        float X2 = 87-cos(Angulo2) * radio;
        float Y2 = sin(Angulo2) * radio;
        glVertex2f(X2, Y2);
    }
}

void canasta2(float radio, int numPuntos) {
    glColor3f(1, 1, 1);
    glBegin(GL_LINES);

    for (int i = 0; i <= numPuntos; i++) {
        float Angulo = i * (2.0 * M_PI / numPuntos);
        float X = -87-cos(Angulo) * radio;
        float Y = sin(Angulo) * radio;
        glVertex2f(X, Y);

        float Angulo2 = (i + 1) * (2.0 * M_PI / numPuntos);
        float X2 = -87-cos(Angulo2) * radio;
        float Y2 = sin(Angulo2) * radio;
        glVertex2f(X2, Y2);
    }
}

void semiCirculo(float radio,int numPuntos) {

    for (int i = 0; i < numPuntos; i++){
        glBegin(GL_POINTS);
        float angulo1 = i * (0.5*M_PI/1000);
        float angulo2 = i * (-0.5*M_PI/1000);
        float x = -cos (angulo1)*50;
        float y = -sin (angulo2)*50;
        glVertex3f(x,y,0.0f);
        glEnd();
    }

 /*for(int i = 0; i <= numPuntos; i++){
		float Angulo = i * (2.0*M_PI/numPuntos);
		float X = cos( Angulo )*radio;
		float Y = sin( Angulo )*radio;
		glVertex2f(X,Y);
	}*/
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    circuloTeselado(15, 50);

    //semiCirculo(5,300);

    glBegin(GL_LINES);
    glVertex2f(0, 100);
    glVertex2f(0, -100);

    //Area exterior
    glVertex2f(-99.0f, 99.0f);
    glVertex2f(99.0f, 99.0f);
    glVertex2f(99.0f, -99.0f);
    glVertex2f(-99.0f, -99.0f);
    glVertex2f(-99.0f, -99.0f);
    glVertex2f(-99.0f, 99.0f);
    glVertex2f(99.0f, 99.0f);
    glVertex2f(99.0f, -99.0f);

    //Area izquierda
    glVertex2f(-100.0f, -80.0f);
    glVertex2f(-80.0f, -80.0f);

    glVertex2f(-100.0f, 80.0f);
    glVertex2f(-80.0f, 80.0f);

    glVertex2f(-100.0f, 20.0f);
    glVertex2f(-60.0f, 20.0f);

    glVertex2f(-60.0f, 20.0f);
    glVertex2f(-60.0f, -20.0f);

    glVertex2f(-60.0f, -20.0f);
    glVertex2f(-100.0f, -20.0f);

    glVertex2f(-90.0f, -5.0f);
    glVertex2f(-90.0f, 5.0f);

    canasta2(3,35);

    //Area derecha
    glVertex2f(100.0f, 80.0f);
    glVertex2f(80.0f, 80.0f);

    glVertex2f(100.0f, -80.0f);
    glVertex2f(80.0f, -80.0f);

    glVertex2f(100.0f, -20.0f);
    glVertex2f(60.0f, -20.0f);

    glVertex2f(60.0f, -20.0f);
    glVertex2f(60.0f, 20.0f);

    glVertex2f(60.0f, 20.0f);
    glVertex2f(100.0f, 20.0f);

    glVertex2f(90.0f, 5.0f);
    glVertex2f(90.0f, -5.0f);
    canasta(3,35);

    glEnd();
    glFlush();

}

void init(void) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-100.0, 100.0, -100.0, 100.0, -100.0, 100.0);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("-- Cancha de Futbol --");
    //std::cout << argc << std::endl;
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
