#include <stdio.h>
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include <SOIL/SOIL.h>
#include <SDL2/SDL.h>
#include "SDL2/SDL_mixer.h"

void suelo();

void pared1();
void pared2();
void paredGris();
void paredDesnivel();

int frameNumber; // Numero de frames

//Definimos variables
double rotateWorld_y = 0;
double rotateWorld_x = 15;
double rotateWorld_z = 0;

GLfloat WorldX = 0.0f;
GLfloat WorldY = -1.0f;
GLfloat WorldZ = -1.5f;
GLfloat scale = 0.1f;

//Parametros Globales del personaje
GLfloat step = 1.75;
GLfloat RotPersoAngle = 180.0f, RotPersoX = 0.0f, RotPersoY = 1.0f, RotPersoZ = 0.0f;
GLfloat PosPersoX = 0.0f, PosPersoY = 0.0f, PosPersoZ = 0.0f;

//Parametros

GLuint ListPared1, ListPared2, ListParedGris, ListDesnivel, ListSuelo;

//Arreglo de imagenes
GLuint texture[0];


//parametros de la fuente de luz
GLfloat LightAmbient[] = {0.5f, 0.5f, 0.5f, 1.0f};
GLfloat LightDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat LightPosition[] = {1.0f, 1.0f, 1.0f, 0.0f};

void init(void) {
    //Carga la textura
    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);
    glClearColor(0.046f, 0.714f, 0.945f, 0.5f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    //glEnable(GL_LIGHTING);
    glDepthFunc(GL_LESS); //comparación de profundidad
    glEnable(GL_DEPTH_TEST); //activa GL_DEPTH_TEST
    glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
    //activa la luz
    glEnable(GL_LIGHT0);

    ListSuelo = glGenLists(1);
    glNewList(ListSuelo, GL_COMPILE);
    suelo();
    glEndList();

    ListPared1 = glGenLists(1);
    glNewList(ListPared1, GL_COMPILE);
    pared1();
    glEndList();

    ListPared2 = glGenLists(1);
    glNewList(ListPared2, GL_COMPILE);
    pared2();
    glEndList();

    ListParedGris = glGenLists(1);
    glNewList(ListParedGris, GL_COMPILE);
    paredGris();
    glEndList();

    ListDesnivel = glGenLists(1);
    glNewList(ListDesnivel, GL_COMPILE);
    paredDesnivel();
    glEndList();

}

void suelo() {
    texture[0] = SOIL_load_OGL_texture // cargamos la imagen
            (
                    "suelo.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


    glColor3f(1, 1, 1);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-400.0f, 00.0f, -400.0f);
    glTexCoord2f(32.0f, 0.0f);
    glVertex3f(400.0f, 00.0f, -400.0f);
    glTexCoord2f(32.0f, 32.0f);
    glVertex3f(400.0f, 00.0f, 400.0f);
    glTexCoord2f(0.0f, 32.0f);
    glVertex3f(-400.0f, 00.0f, 400.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);

}


void pared1() {
//Definicion de texturas
    texture[0] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "brick.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );

    // Frente
    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-45.0f, -25.0f, 5.0f);
    glTexCoord2f(8.0f, 0.0f); glVertex3f(45.0f, -25.0f, 5.0f);
    glTexCoord2f(8.0f, 8.0f); glVertex3f(45.0f, 25.0f, 5.0f);
    glTexCoord2f(0.0f, 8.0f); glVertex3f(-45.0f, 25.0f, 5.0f);
    glEnd();

    // parte de Atras
    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(8.0f, 0.0f); glVertex3f(-45.0f, -25.0f, -5.0f);
    glTexCoord2f(8.0f, 8.0f); glVertex3f(-45.0f, 25.0f, -5.0f);
    glTexCoord2f(0.0f, 8.0f); glVertex3f(45.0f, 25.0f, -5.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(45.0f, -25.0f, -5.0f);
    glEnd();
    // Arriba
    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 4.0f); glVertex3f(-45.0f, 25.0f, -5.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-45.0f, 25.0f, 5.0f);
    glTexCoord2f(4.0f, 0.0f); glVertex3f(45.0f, 25.0f, 5.0f);
    glTexCoord2f(4.0f, 4.0f); glVertex3f(45.0f, 25.0f, -5.0f);
    glEnd();

    // Abajo
    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(4.0f, 4.0f); glVertex3f(-45.0f, -25.0f, -5.0f);
    glTexCoord2f(0.0f, 4.0f); glVertex3f(45.0f, -25.0f, -5.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(45.0f, -25.0f, 5.0f);
    glTexCoord2f(4.0f, 0.0f); glVertex3f(-45.0f, -25.0f, 5.0f);
    glEnd();

    // lado Derecho
    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(45.0f, -25.0f, -5.0f);
    glTexCoord2f(1.0f, 4.0f); glVertex3f(45.0f, 25.0f, -5.0f);
    glTexCoord2f(0.0f, 4.0f); glVertex3f(45.0f, 25.0f, 5.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(45.0f, -25.0f, 5.0f);
    glEnd();

    // Lado Izquierdo
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-45.0f, -25.0f, -5.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-45.0f, -25.0f, 5.0f);
    glTexCoord2f(1.0f, 4.0f); glVertex3f(-45.0f, 25.0f, 5.0f);
    glTexCoord2f(0.0f, 4.0f); glVertex3f(-45.0f, 25.0f, -5.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void pared2() {
//Definicion de texturas
    texture[0] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "brick.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );

    // Frente
    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-45.0f, -1.0f, 5.0f);
    glTexCoord2f(8.0f, 0.0f); glVertex3f(45.0f, -1.0f, 5.0f);
    glTexCoord2f(8.0f, 0.25f); glVertex3f(45.0f, 1.0f, 5.0f);
    glTexCoord2f(0.0f, 0.25f); glVertex3f(-45.0f, 1.0f, 5.0f);
    glEnd();

    // parte de Atras
    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(8.0f, 0.0f); glVertex3f(-45.0f, -1.0f, -5.0f);
    glTexCoord2f(8.0f, 0.25f); glVertex3f(-45.0f, 1.0f, -5.0f);
    glTexCoord2f(0.0f, 0.25f); glVertex3f(45.0f, 1.0f, -5.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(45.0f, -1.0f, -5.0f);
    glEnd();
    // Arriba
    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-45.0f, 1.0f, -5.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-45.0f, 1.0f, 5.0f);
    glTexCoord2f(8.0f, 0.0f); glVertex3f(45.0f, 1.0f, 5.0f);
    glTexCoord2f(8.0f, 1.0f); glVertex3f(45.0f, 1.0f, -5.0f);
    glEnd();

    // Abajo
    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(8.0f, 1.0f); glVertex3f(-45.0f, -1.0f, -5.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(45.0f, -1.0f, -5.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(45.0f, -1.0f, 5.0f);
    glTexCoord2f(8.0f, 0.0f); glVertex3f(-45.0f, -1.0f, 5.0f);
    glEnd();

    // lado Derecho
    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(45.0f, -1.0f, -5.0f);
    glTexCoord2f(1.0f, 0.25f); glVertex3f(45.0f, 1.0f, -5.0f);
    glTexCoord2f(0.0f, 0.25f); glVertex3f(45.0f, 1.0f, 5.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(45.0f, -1.0f, 5.0f);
    glEnd();

    // Lado Izquierdo
    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-45.0f, -1.0f, -5.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-45.0f, -1.0f, 5.0f);
    glTexCoord2f(1.0f, 0.25f); glVertex3f(-45.0f, 1.0f, 5.0f);
    glTexCoord2f(0.0f, 0.25f); glVertex3f(-45.0f, 1.0f, -5.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void paredGris() {
//Definicion de texturas
    texture[0] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "stonebrick.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );

    // Frente
    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);

    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-44.0f, -5.0f, 4.0f);
    glTexCoord2f(8.0f, 0.0f); glVertex3f(44.0f, -5.0f, 4.0f);
    glTexCoord2f(8.0f, 1.0f); glVertex3f(44.0f, 5.0f, 4.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-44.0f, 5.0f, 4.0f);
    glEnd();

    // parte de Atras
    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(8.0f, 0.0f); glVertex3f(-44.0f, -5.0f, -4.0f);
    glTexCoord2f(8.0f, 1.0f); glVertex3f(-44.0f, 5.0f, -4.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(44.0f, 5.0f, -4.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(44.0f, -5.0f, -4.0f);
    glEnd();
    // Arriba
    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-44.0f, 5.0f, -4.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-44.0f, 5.0f, 4.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(44.0f, 5.0f, 4.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(44.0f, 5.0f, -4.0f);
    glEnd();

    // Abajo
    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-44.0f, -5.0f, -4.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(44.0f, -5.0f, -4.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(44.0f, -5.0f, 4.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-44.0f, -5.0f, 4.0f);
    glEnd();

    // lado Derecho
    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(44.0f, -5.0f, -4.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(44.0f, 5.0f, -4.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(44.0f, 5.0f, 4.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(44.0f, -5.0f, 4.0f);
    glEnd();

    // Lado Izquierdo
    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-44.0f, -5.0f, -4.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-44.0f, -5.0f, 4.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-44.0f, 5.0f, 4.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-44.0f, 5.0f, -4.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void paredDesnivel() {
//Definicion de texturas
    texture[0] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "brick.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );

    // Frente
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);

    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-45.0f, -1.0f, 5.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(45.0f, -1.0f, 5.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(45.0f, 1.0f, 5.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-45.0f, 1.0f, 5.0f);
    glEnd();

    // parte de Atras
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-45.0f, -1.0f, -5.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-45.0f, 1.0f, -5.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(45.0f, 1.0f, -5.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(45.0f, -1.0f, -5.0f);
    glEnd();

    // lado Derecho
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(45.0f, -1.0f, -5.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(45.0f, 1.0f, -5.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(45.0f, 1.0f, 5.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(45.0f, -1.0f, 5.0f);
    glEnd();

    // Lado Izquierdo
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-45.0f, -1.0f, -5.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-45.0f, -1.0f, 5.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-45.0f, 1.0f, 5.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-45.0f, 1.0f, -5.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //Transladar el cubo a las siguientes coordenadas
    glTranslatef(0.0f, 0.0f, -5.5f);

    // Rotar la camara en el eje X,Y y Z
    glRotatef(rotateWorld_x, 1.0, 0.0, 0.0);
    glRotatef(rotateWorld_y, 0.0, 1.0, 0.0);
    glRotatef(rotateWorld_z, 0.0, 0.0, 1.0);
    glTranslatef(WorldX, WorldY, WorldZ);    // Transladar la camara en los 3 ejes
    // Otras transformaciones
    glScalef(scale, scale, scale); //Configurar la escala de la escena

    glTranslatef(0.0, -22.5, 0.0);
    glCallList(ListSuelo);
    glTranslatef(0.0, 22.5, 0.0);

    //PERSONAJE
    glRotatef(RotPersoAngle, RotPersoX, RotPersoY, RotPersoZ); //Coordina la rotación del personaje
    glTranslatef(PosPersoX, PosPersoY, PosPersoZ); //Para coordinar la posición del personaje

    glCallList(ListPared1);
    glTranslatef(0,26,0);
    glCallList(ListDesnivel);
    glTranslatef(0,6,0);
    glCallList(ListParedGris);
    glTranslatef(0,6,0);
    glCallList(ListPared2);


    //glFlush();
    glutSwapBuffers();

}

// Función para controlar teclas especiales
void specialKeys(int key, int x, int y) {

    //  Flecha derecha: aumentar rotación 7 grados
    if (key == GLUT_KEY_UP)
        rotateWorld_x += 5;

        //  Flecha abajo: rotación en eje X negativo 7 grados
    else if (key == GLUT_KEY_DOWN)
        rotateWorld_x -= 5;
        //  Tecla especial F2 : rotación en eje Z positivo 7 grados
    else if (key == GLUT_KEY_F2)
        rotateWorld_z += 7;
        //  Tecla especial F2 : rotación en eje Z negativo 7 grados
    else if (key == GLUT_KEY_F2)
        rotateWorld_z -= 7;

    //  Solicitar actualización de visualización
    glutPostRedisplay();

}


void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float) w / (float) h, 1.0, 200.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


}

int saltandoAnimation = 0;

void pauseAnimation() {
    // Llamamo a la función para detener la animación
    saltandoAnimation = 0;
}

void updateFrame() {
    // En esta funcion agregamos el codigo que hara la secuencia de cada escena como si fuera un fotograma

    for (int i = 0; i < 15; ++i) {
        PosPersoY += 0.01;
    }

    /*for (int j = 0; j < 15; ++j) {
        PosPersoY -= 0.01;
    }*/

    //Verificamos el numero de frames para detener animación
    if (frameNumber == 200) {
        pauseAnimation();
        frameNumber = 0;
    }
    //Almacenamos el numero de frames
    frameNumber++;
    printf("Numero de Frame: %d \n", frameNumber);
}

void timerFunction(int timerID) {
    // Invocamos la funcion para controlar el tiempo de la ejecucion de funciones
    if (saltandoAnimation) {
        updateFrame();
        glutTimerFunc(30, timerFunction, 0);
        glutPostRedisplay();
    }
}

void startAnimation() {
    // llamamos la función para iniciar la animación
    if (!saltandoAnimation) {
        saltandoAnimation = 1;
        glutTimerFunc(30, timerFunction, 1);
    }
}


// Función para controlar teclas normales del teclado.
void keyboard(unsigned char key, int x, int y) {
    //control de teclas que hacen referencia a Escalar y transladar el cubo en los ejes X,Y,Z.
    GLfloat temp;
    switch (key) {
        case 'w':
            if (RotPersoAngle != 180) {

                //Corrige las coordenadas cuando proviene de 270
                if (RotPersoAngle == 270) {
                    temp = PosPersoX;
                    PosPersoX = -1 * PosPersoZ;
                    PosPersoZ = temp;
                }

                //Corrige las coordenadas cuando proviene de 0
                if (RotPersoAngle == 90) {
                    temp = PosPersoX;
                    PosPersoX = PosPersoZ;
                    PosPersoZ = -1 * temp;
                }

                RotPersoAngle = 180;
                RotPersoY = 1;
                PosPersoX *= -1;
                PosPersoZ *= -1;
            }
            PosPersoZ += step;
            break;

        case 'a':
            if (RotPersoAngle != 270) {

                if (RotPersoAngle == 180) {
                    temp = PosPersoX;
                    PosPersoX = PosPersoZ;
                    PosPersoZ = -1 * temp;
                }

                if (RotPersoAngle == 0) {
                    temp = PosPersoX;
                    PosPersoX = -1 * PosPersoZ;
                    PosPersoZ = temp;
                }

                RotPersoAngle = 270;
                RotPersoY = 1;
                PosPersoX *= -1;
                PosPersoZ *= -1;
            }
            PosPersoZ += step;
            break;

        case 's' :

            if (RotPersoAngle != 0) {

                //Corrige las coordenadas cuando proviene de 270
                if (RotPersoAngle == 270) {
                    temp = PosPersoX;
                    PosPersoX = PosPersoZ;
                    PosPersoZ = -1 * temp;
                }

                //Corrige las coordenadas cuando proviene de 0
                if (RotPersoAngle == 90) {
                    temp = PosPersoX;
                    PosPersoX = -1*PosPersoZ;
                    PosPersoZ = temp;
                }

                RotPersoAngle = 0;
                RotPersoY = 1;
                PosPersoX *= -1;
                PosPersoZ *= -1;
            }
            PosPersoZ += step;
            break;

        case 'd' :
            if (RotPersoAngle != 90) {

                if (RotPersoAngle == 180) {
                    temp = PosPersoX;
                    PosPersoX = -1 * PosPersoZ;
                    PosPersoZ = temp;
                }

                if (RotPersoAngle == 0) {
                    temp = PosPersoX;
                    PosPersoX = PosPersoZ;
                    PosPersoZ = -1 * temp;
                }

                RotPersoAngle = 90;
                RotPersoY = 1;
                PosPersoX *= -1;
                PosPersoZ *= -1;
            }
            PosPersoZ += step;
            break;
        case '8' :
            WorldY -= 0.1f;
            break;
        case '5' :
            WorldY += 0.1f;
            break;
        case '4':
            WorldX -= 0.1f;
            break;
        case '6':
            WorldX += 0.1f;
            break;
        case '7':
            rotateWorld_y += 5;
            break;
        case '9':
            rotateWorld_y -= 5;
            break;
        case '-':
            WorldZ -= 0.1f;
            break;
        case '+':
            WorldZ += 0.1f;
            break;
        case 'r':
            if(step == 1.75){
                step = 5.75;
            }else{
                step = 1.75;
            }
            break;
        case 'q':
            exit(0);            // exit
    }
    glutPostRedisplay();
}


void update(int value) {
    rotateWorld_y += 5;
    rotateWorld_x += 6;
    rotateWorld_z += 7;

    glutPostRedisplay();
    glutTimerFunc(25, update, 0);
}

int main(int argc, char *argv[]) {

    //  Inicializar los parámetros GLUT y de usuario proceso
    glutInit(&argc, argv);

    // Solicitar ventana con color real y doble buffer con Z-buffer
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(800, 600);
    glutInitWindowPosition(0, 0);
    // Crear ventana
    glutCreateWindow("Cubo con texturas");
    init();
    // Habilitar la prueba de profundidad de Z-buffer
    glEnable(GL_DEPTH_TEST);

    // Funciones de retrollamada
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    //glutTimerFunc(30, update, 0);
    // Pasar el control de eventos a GLUT
    glutMainLoop();

    // Regresar al sistema operativo
    return 0;

}
