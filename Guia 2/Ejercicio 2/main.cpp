#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "camera.h"
#include "dibujado.h"
#include "dibujos.h"

// Initialize the OpenGL window
void init(void)
{

    glClearColor (0.0, 0.0, 0.0, 0.0); // Clear the color
    glShadeModel (GL_FLAT); // Set the shading model to GL_FLAT
    glEnable (GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST); // Set Line Antialiasing

}

// Draw the lines (x,y,z)
void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT); // Clear the Color Buffer
    glPushMatrix(); 	// It is important to push the Matrix before calling
    // glRotatef and glTranslatef
    glRotatef(rotX,1.0,0.0,0.0); // Rotate on x
    glRotatef(rotY,0.0,1.0,0.0); // Rotate on y
    glRotatef(rotZ,0.0,0.0,1.0); // Rotate on z
    glTranslatef(X, Y, Z); 	// Translates the screen left or right,
    // up or down or zoom in zoom out
    PlanoCarte();


    generadorObjetos(techoVertices,techoFaces,6);
    generadorObjetos(lamparaTechoVertices,lamparaTechoFaces,1);
    generadorObjetos(paredIzquierdaVertices, paredIzquierdaFaces, 6);
    generadorObjetos(paredFondoVertices, paredFondoFaces, 6);
    generadorObjetos(paredDerechaVertices, paredDerechaFaces, 6);
    generadorObjetos(sueloVertices, sueloFaces, 6);
    generadorObjetos(interIzqVertices, interIzqFaces, 6);
    generadorObjetos(interDerVertices, interDerFaces, 6);

    glPopMatrix(); 		// Don't forget to pop the Matrix
    glutSwapBuffers();
}



// Main entry point of the program
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB); 	// Setup display mode to
    // double buffer and RGB color
    glutInitWindowSize (800,800); // Set the screen size
    glutCreateWindow("Ejercicio 1");
    init();
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard); // set window's key callback
    glutSpecialFunc(specialKey); // set window's to specialKey callback
    glutMainLoop();
    return 0;
}