#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <math.h>

float radio = 0.5;
int numPuntos = 100;

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(2.0f);
	glColor3f(1.0f, 1.0f, 1.0f); //Color azul
	glBegin(GL_POINTS);
	
	
	for(int i = 0; i <= numPuntos; i++){
		float Angulo = i * (2.0*M_PI/numPuntos);
		float X = cos( Angulo )*radio;
		float Y = sin( Angulo )*radio;
		glVertex2f(X,Y);
	}
		

	glEnd();
    glFlush ();

}

void init (void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

float Grados2Radianes(float grados){
	float radianes = grados * (3.14159265359/180);
	return radianes;
}

float CalculoY(float X, float radio){
	float Y = sqrt(radio*radio - X*X);
	return Y;
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (400, 400);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("-- Ejemplo Poligono --");
    //std::cout << argc << std::endl;
    init ();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
