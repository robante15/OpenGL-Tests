#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "camera.h"
#include "dibujado.h"
#include "objetos.h"

// Initialize the OpenGL window
void init(void)
{
    GLfloat light_position[4] = {5.0, 5.0, 5.0, 0.0};
    glEnable(GL_LIGHTING); //activa la fuente de luz
    glEnable(GL_LIGHT0); //Activamos las luces en 0
    glDepthFunc(GL_LESS); //comparación de profundidad
    glEnable(GL_DEPTH_TEST); //activa GL_DEPTH_TES
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glClearColor (0.0, 0.0, 0.0, 0.0); // Clear the color
    glShadeModel (GL_FLAT); // Set the shading model to GL_FLAT
    glEnable (GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST); // Set Line Antialiasing

}

// Draw the lines (x,y,z)
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW_MATRIX);
    glPushMatrix(); 	// It is important to push the Matrix before calling
    // glRotatef and glTranslatef
    glRotatef(rotX,1.0,0.0,0.0); // Rotate on x
    glRotatef(rotY,0.0,1.0,0.0); // Rotate on y
    glRotatef(rotZ,0.0,0.0,1.0); // Rotate on z
    glTranslatef(X, Y, Z); 	// Translates the screen left or right,
    // up or down or zoom in zoom out
    PlanoCarte();


    generadorObjetos(techoVertices,techoFaces,6,amb_GrisClaro,dif_GrisClaro,spec_GrisClaro,shine_GrisClaro);
    glFlush();
    generadorObjetos(paredFrontalVertices,paredFrontalFaces,6,amb_GrisClaro,dif_GrisClaro,spec_GrisClaro,shine_GrisClaro);
    generadorObjetos(paredIzquierdaVertices, paredIzquierdaFaces, 6,amb_GrisClaro,dif_GrisClaro,spec_GrisClaro,shine_GrisClaro);
    generadorObjetos(paredFondoVertices, paredFondoFaces, 6,amb_GrisClaro,dif_GrisClaro,spec_GrisClaro,shine_GrisClaro);
    generadorObjetos(paredDerechaVertices, paredDerechaFaces, 6,amb_GrisClaro,dif_GrisClaro,spec_GrisClaro,shine_GrisClaro);
    generadorObjetos(sueloVertices, sueloFaces, 6,amb_GrisClaro,dif_GrisClaro,spec_GrisClaro,shine_GrisClaro);
    generadorObjetos(interIzqVertices, interIzqFaces, 6,amb_GrisClaro,dif_GrisClaro,spec_GrisClaro,shine_GrisClaro);
    generadorObjetos(interDerVertices, interDerFaces, 6,amb_GrisClaro,dif_GrisClaro,spec_GrisClaro,shine_GrisClaro);


    glPopMatrix(); 		// Don't forget to pop the Matrix
    glutSwapBuffers();
}



// Main entry point of the program
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
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