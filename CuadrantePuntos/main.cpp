#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(2);
    
    glBegin(GL_LINES);
    glVertex2f(0, 0);
    glVertex2f(5, 5);
    
    glBegin(GL_LINES);
    glVertex2f(0, 0);
    glVertex2f(5, -5);
    
    glBegin(GL_POINTS);
    //Linea a puro punto, en cruz
    for(float i = 0; i <= 5; i = i + 0.001){
		//glVertex3f(i,i,0.0f);
		glVertex3f(-1.0*i,i,0.0f);
		//glVertex3f(i,-1.0*i,0.0f);
		glVertex3f(-1.0*i,-1.0*i,0.0f);
	}
	
	//Funcion cuadratica
    /*for(float i = -500; i <= 500; i = i + 0.01){
		float x = i;
		float y = i*i+8*i+15;
		std::cout << y << std::endl;
		glVertex3f(x,y,0.0f);
	}*/
	
    
    //glVertex3f(0.5f,0.5f,0.0f); //Es un punto en el primer cuadrante, en X = 0.5 Y = 0.5
    //glVertex3f(-0.5f,0.5f,0.0f); //Es un punto en el segundo cuadrante, en X = -0.5 Y = 0.5
    //glVertex3f(-0.5f,-0.5f,0.0f); //Es un punto en el tercero cuadrante, en X = -0.5 Y = -0.5
    //glVertex3f(0.5f,-0.5f,0.0f); //Es un punto en el cuarto cuadrante, en X = 0.5 Y = -0.5
    //glVertex3f(0.0f,0.0f,0.0f);
    glEnd();
    glFlush ();

}
void init (void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-5.0, 5.0, -5.0, 5.0, -5.0, 5.0);
    //glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); // Por defecto
    //glOrtho(0.0, 1.0, 0.0, 1.0, 1.0, 0.0);  //Primer cuadrante
    //glOrtho(1.0, 0.0, 0.0, 1.0, 1.0, 0.0);  //Segundo cuadrante
    //glOrtho(1.0, 0.0, 1.0, 0.0, 1.0, 0.0);  //Tercero cuadrante
    //glOrtho(0.0, 1.0, 1.0, 0.0, 1.0, 0.0);  //Cuarto cuadrante
    
    
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (400, 400);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("-- Ejemplo Puntos --");
    //std::cout << argc << std::endl;
    init ();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
